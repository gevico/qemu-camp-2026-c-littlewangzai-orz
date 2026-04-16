# 调试宏 DEBUG_PRINT 笔记

## 一、编译选项 `-D`

`-DNAME=VALUE` 在命令行传入宏定义，等价于代码里写 `#define NAME VALUE`：

```bash
gcc -DDEBUG_LEVEL=2 ...
# 等价于代码里写: #define DEBUG_LEVEL 2
```

在 Makefile 里可以设默认值，也可以外部覆盖：

```makefile
DEBUG_LEVEL ?= 3              # 默认值 3
CPPFLAGS += -DDEBUG_LEVEL=$(DEBUG_LEVEL)
```

```bash
make DEBUG_LEVEL=1            # 覆盖为 1
```

---

## 二、条件编译

### `#ifdef`：只判断是否定义

```c
#ifdef DEBUG_LEVEL    // 只要定义了，不管值是多少
    ...
#endif
```

### `#if / #elif / #else`：判断值

```c
#if DEBUG_LEVEL == 1
    // LEVEL=1 的代码
#elif DEBUG_LEVEL == 2
    // LEVEL=2 的代码
#elif DEBUG_LEVEL == 3
    // LEVEL=3 的代码
#else
    // 没定义或其他值
#endif
```

**预处理阶段完成，不产生运行时开销。** 未被选中的分支完全不参与编译。

---

## 三、预定义宏

编译器内置，不需要自己定义：

| 宏 | 类型 | 内容 |
|----|------|------|
| `__func__` | `const char *` | 当前函数名字符串 |
| `__LINE__` | `int` | 当前行号 |
| `__FILE__` | `const char *` | 当前文件名字符串 |

### 关键特性：展开在**调用处**，不是定义处

```c
#define LOG() printf("%s %d\n", __func__, __LINE__)

void test() {
    LOG();   // 输出: test 3   ← test 函数的信息
}
int main() {
    LOG();   // 输出: main 6   ← main 函数的信息
}
```

这是调试宏必须用**宏**而不是**函数**的根本原因——函数里 `__func__` 永远是函数自己的名字。

---

## 四、可变参数宏

### 语法

```c
#define 宏名(固定参数, ...)   使用(__VA_ARGS__)
```

- `...` 是入口，接收不定数量的额外参数
- `__VA_ARGS__` 是出口，展开为那些参数

```c
#define LOG(fmt, ...)  printf(fmt, __VA_ARGS__)

LOG("x=%d, y=%d", 1, 2)
// 展开: printf("x=%d, y=%d", 1, 2)
```

### 没有额外参数时的问题

```c
LOG("hello")
// 展开: printf("hello", )   // ❌ 多余的逗号
```

用 `##__VA_ARGS__` 解决（GCC 扩展），无额外参数时连前面逗号一起吃掉：

```c
#define LOG(fmt, ...)  printf(fmt, ##__VA_ARGS__)

LOG("hello")
// 展开: printf("hello")     // ✅
```

---

## 五、字符串字面量自动拼接

C 语言中相邻的字符串字面量在编译期**自动合并**：

```c
"hello " "world"   →   "hello world"
```

利用这个特性，把固定前缀和用户的 `fmt` 拼成一个完整格式串：

```c
#define DEBUG_PRINT(fmt, ...) \
    printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)

DEBUG_PRINT("x=%d", 42)
// 格式串拼接: "DEBUG: func=%s, line=%d, " "x=%d" "\n"
//          → "DEBUG: func=%s, line=%d, x=%d\n"
// 展开为:   printf("DEBUG: func=%s, line=%d, x=%d\n", __func__, __LINE__, 42)
// 输出:     DEBUG: func=test, line=48, x=42
```

**注意：`fmt` 和前缀之间没有逗号，是字符串拼接，不是两个参数。**

---

## 六、`printf` 格式串与参数必须一一对应

```
printf("func=%s, line=%d, x=%d",  __func__,  __LINE__,  42)
//      %s            %d     %d    ^^^^^^^^   ^^^^^^^^   ^^
//      对应            对应   对应
```

常见错误：

```c
// ❌ 错误：fmt 当成参数传，而不是格式串的一部分
printf("prefix ", fmt, __func__, __LINE__, __VA_ARGS__)
//      只有0个占位符，但传了4个参数 → too many arguments 警告

// ✅ 正确：字符串拼接，fmt 是格式串的一部分
printf("prefix " fmt, __func__, __LINE__, ##__VA_ARGS__)
```

---

## 七、`do { } while(0)` 包装

让宏在任何语法场景下都安全（尤其是 `if-else` 场景）：

```c
// 假设宏展开成两条语句，不用 do-while：
if (cond)
    MACRO();    // 展开成两条，只有第一条在 if 里！
else
    ...

// 用 do-while 包装后，整体是一条语句：
#define MACRO() do { stmt1; stmt2; } while(0)
```

空宏（关闭调试时）也用它，保证语法正确：

```c
#define DEBUG_PRINT(fmt, ...) do {} while(0)
```

---

## 八、`backtrace`：打印调用栈（LEVEL=3）

需要 `<execinfo.h>`，**Linux/glibc 特有**。

### 三步流程

```c
void *buffer[10];

// 1. 获取调用栈地址，返回实际层数
int n = backtrace(buffer, 10);

// 2. 把地址翻译成可读字符串（内部 malloc）
char **symbols = backtrace_symbols(buffer, n);

// 3. 打印
for (int i = 0; i < n; i++) {
    printf("%s\n", symbols[i]);
}

// 4. 只 free 外层数组，不要 free symbols[i]
free(symbols);
```

### 显示函数名需要 `-rdynamic`

```bash
gcc -rdynamic -o program program.c
```

不加 `-rdynamic` 只能看到地址，看不到函数名：

```
# 没有 -rdynamic
./program() [0x4005fe]

# 有 -rdynamic
./program(test+0x12) [0x4005cc]
./program(main+0x1a) [0x4005fe]
```

### `backtrace` vs `backtrace_symbols`

| 函数 | 返回 | 说明 |
|------|------|------|
| `backtrace` | `void *[]` | 函数地址（数字） |
| `backtrace_symbols` | `char **` | 地址翻译成可读字符串 |

---

## 九、完整实现结构

```c
#if DEBUG_LEVEL == 1
    #define DEBUG_PRINT(fmt, ...) \
        printf("DEBUG: func=%s, line=%d\n", __func__, __LINE__)

#elif DEBUG_LEVEL == 2
    #define DEBUG_PRINT(fmt, ...) \
        printf("DEBUG: func=%s, line=%d, " fmt "\n", __func__, __LINE__, ##__VA_ARGS__)

#elif DEBUG_LEVEL == 3
    #define DEBUG_PRINT(fmt, ...) do {          \
        void *_buf[10];                         \
        int _n = backtrace(_buf, 10);           \
        char **_sym = backtrace_symbols(_buf, _n); \
        for (int _i = 0; _i < _n; _i++)        \
            printf("%s\n", _sym[_i]);           \
        free(_sym);                             \
    } while(0)

#else
    #define DEBUG_PRINT(fmt, ...) do {} while(0)
#endif
```

### 临时变量用下划线前缀 `_` 的原因

防止和调用处的局部变量名冲突（宏展开后共享同一作用域）。
