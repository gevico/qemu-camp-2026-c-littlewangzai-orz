# C 语言宏完全笔记

## 一、基础：`#define`

### 对象宏（常量）

```c
#define PI 3.14159
#define MAX_SIZE 1024
```

纯文本替换，编译前由预处理器处理，**不占内存，没有类型**。

### 函数宏（带参数）

```c
#define SQUARE(x)  ((x) * (x))
#define MAX(a, b)  ((a) > (b) ? (a) : (b))
```

---

## 二、参数保护：为什么每个参数都要加括号

宏是**纯文本替换**，不是函数调用，不会自动处理运算符优先级。

```c
#define SQUARE(x)  x * x         // ❌ 危险

SQUARE(1 + 2)
// 展开: 1 + 2 * 1 + 2 = 5      // 错误！应该是 9
```

```c
#define SQUARE(x)  ((x) * (x))   // ✅ 安全

SQUARE(1 + 2)
// 展开: ((1 + 2) * (1 + 2)) = 9
```

**规则：宏定义里每个参数都加 `()`，整个表达式也加 `()`。**

---

## 三、分号规则

### 普通表达式宏：定义里不加分号

```c
#define SQUARE(x) ((x) * (x))    // 不加分号

int a = SQUARE(3);   // 分号由调用者加
```

如果定义里加了分号：

```c
#define SQUARE(x) ((x) * (x));   // ❌ 加了分号

int a = SQUARE(3);
// 展开: int a = ((3) * (3));;   // 语法错误！
```

### 语句表达式 `({ })`：里面每行都加分号

```c
#define FOO(x) ({      \
    int _a = (x);      \    // ✅ 加分号
    _a * _a;           \    // ✅ 最后一行也加分号（这是返回值）
})
```

---

## 四、多副作用问题

宏参数可能被**展开多次**，导致副作用执行多次：

```c
#define SQUARE(x) ((x) * (x))

int i = 3;
SQUARE(i++)
// 展开: ((i++) * (i++))   // i 自增了两次！结果不可预期
```

解决方法：用**语句表达式**把参数先存入临时变量：

```c
#define SQUARE(x) ({     \
    typeof(x) _x = (x); \    // x 只求值一次
    _x * _x;             \
})
```

---

## 五、GCC 扩展：`typeof`

获取变量或表达式的**类型**，用于宏内部声明同类型临时变量：

```c
int a = 5;
typeof(a)   b = 10;   // 等价于 int b = 10
typeof(&a)  p;        // 等价于 int *p

typeof(((struct Test *)0)->member)  // 推导结构体成员的类型（不会真正解引用）
```

**常见用途：** 声明临时变量时保持类型一致，并借助赋值触发编译器的类型不匹配警告。

---

## 六、GCC 扩展：语句表达式 `({ })`

允许宏内部写多条语句，并返回**最后一条语句的值**：

```c
int result = ({
    int x = 3;
    int y = 4;
    x + y;      // 整个语句表达式的值为 7
});
```

**使用场景：**
- 宏内需要声明临时变量
- 防止参数多次求值
- 做类型安全检查

---

## 七、续行符 `\`

`#define` 默认只占一行，多行宏每行末尾加 `\`：

```c
#define container_of(ptr, type, member) ({              \
    typeof(((type *)0)->member) *_tmp = (ptr);          \
    (type *)((char *)_tmp - offsetof(type, member));    \
})
```

注意：`\` 后面**不能有任何字符（包括空格）**，否则续行失败。

---

## 八、`offsetof` 宏

来自 `<stddef.h>`，获取结构体成员的**字节偏移量**：

```c
struct Test { int a; char b; };

offsetof(struct Test, a)   // 0
offsetof(struct Test, b)   // 4（int 占 4 字节后）
```

原理：把 `0` 强转为结构体指针，取成员地址，地址值就等于偏移量：

```c
#define offsetof(type, member) ((size_t)&((type *)0)->member)
```

---

## 九、`container_of` 完整解析

**目标：** 已知结构体某成员的指针，反推出结构体自身的指针。

**数学关系：**

$$\text{结构体地址} = \text{成员地址} - \text{成员偏移量}$$

**实现要点：**

| 步骤 | 技术 | 作用 |
|------|------|------|
| 类型检查 | `typeof` + 赋值 | 传错类型时编译器报警告 |
| 字节级指针运算 | 转 `char *` 再减 | `char *` 步长为 1 字节，精确控制偏移 |
| 获取偏移量 | `offsetof` | 成员距结构体起点的字节数 |
| 多语句宏 | 语句表达式 `({ })` | 允许声明临时变量 |

```c
#define container_of(ptr, type, member) ({              \
    typeof(((type *)0)->member) *_tmp = (ptr);          \
    (type *)((char *)_tmp - offsetof(type, member));    \
})
```

**为什么用 `((type *)0)->member` 而不直接写类型？**  
宏参数里只有 `member` 的名字，不知道它的类型。通过"空指针访问成员"这个表达式，编译器能自动推导出成员类型，`typeof` 再提取它——值为 `0` 但**永远不会被解引用**，只用于类型推导。

---

## 十、侵入式数据结构

`container_of` 的经典使用场景：Linux 内核侵入式链表。

```c
// 链表节点直接嵌入业务结构体
struct list_node { struct list_node *next; };

struct Person {
    int age;
    struct list_node node;   // 挂钩
};
```

链表只操作 `node`，需要访问 `Person` 时用 `container_of` 反推：

```c
struct list_node *p = head;
struct Person *person = container_of(p, struct Person, node);
```

**优势：**
- 零额外内存分配（节点就是结构体的一部分）
- 一个结构体可同时挂在多条链表上（嵌入多个 `list_node`）
- 类型安全，无需 `void *` 强转
