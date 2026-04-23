# 练习进度笔记

> 统计时间：`2026-04-23` | 总题数：`40` | 已通过：`38` | 未完成：`2` | 得分：`190 / 200`
>
> 进度：`██████████████████████████████████████░░` 95%

---

## 一、总览

### ✅ 已通过（38 / 40）

| 题号 | 题目 | 分类 | 核心要点 |
| :--: | --- | :--: | --- |
| 01 | `01_insert_sort` | 排序 | 保持前段有序，把当前元素向前插入 |
| 02 | `02_merge_sort` | 排序 | 分治递归拆分，合并时双指针保证有序 |
| 03 | `03_quick_sort` | 排序 | 分区（partition）后递归处理左右子区间 |
| 04 | `04_linear_search` | 查找 | 从头扫到尾，找到即返回 |
| 05 | `05_binary_search` | 查找 | 只对有序数据有效，边界更新用 `mid±1` |
| 06 | `06_stack_maze` | 数据结构 | DFS，栈保存当前路径，走不通弹栈回退 |
| 07 | `07_queue_maze` | 数据结构 | BFS，第一次到终点即最短路，`parent` 倒推路径 |
| 08 | `08_circular_queue` | 数据结构 | 取模回绕，判空判满定义与实现必须一致 |
| 09 | `09_word_counter` | 字符串 | 明确"何时开始 / 结束一个单词"，空白字符都是分隔符 |
| 10 | `10_my_strcpy` | 字符串 | 逐字符拷贝，最后补 `\0` |
| 11 | `11_command_interpreter` | 字符串 | 状态机（`OUT_WORD`/`IN_WORD`），`\0` 也是边界 |
| 12 | `12_student_management` | 数据结构 | 结构体数组，删除时后续元素前移 |
| 13 | `13_universal_sorter` | 排序 | 比较函数参数化，返回值语义（负/零/正）全程一致 |
| 14 | `14_calculator` | 数据结构 | `switch` 分发运算，注意除零处理 |
| 15 | `15_url_parser` | 字符串 | 先拆协议/主机/路径，再处理端口和边界分支 |
| 16 | `16_mysed` | 文件 | 按行读取并执行替换，是否全局替换按题意来 |
| 17 | `17_myfile` | 文件 | 文件读写检查返回值，失败时不能继续用无效句柄 |
| 18 | `18_mywc` | 文件 | 字符/单词/行计数状态清晰；最后一行无换行符时行数要对 |
| 19 | `19_mytrans` | 字符串 | 逐字符转换，`toupper`/`tolower`，非字母保持不变 |
| 21 | `21_singly_linked_list_josephus` | 链表 | 删节点前先保存 `next`，再 `free`，再移动 |
| 22 | `22_doubly_circular_queue` | 链表 | 双向环形队列，入队出队时前后指针同步更新 |
| 23 | `23_circular_linked_list_josephus` | 链表 | `prev->next = next` 维护链路，`prev` 必须跟着 `current` 走 |
| 24 | `24_prev_binary_tree` | 树 | 前序：根 → 左 → 右；`NULL` 是递归终止条件 |
| 25 | `25_counter_letter` | 字符串 | 26 个桶 `count[ch - 'a']`，非字母跳过 |
| 26 | `26_hash_counter` | 数据结构 | 哈希表统计词频；⚠️ `strdup` 需要 `#define _POSIX_C_SOURCE 200809L` |
| 27 | `27_asm_gcd` | 底层 | 内联汇编约束：输入/输出/破坏寄存器要写全 |
| 28 | `28_operator_overflow` | 底层 | 加：`a+b < a`；减：`a-b > a`；乘：`a*b/b != a`；除零溢出 |
| 29 | `29_swap_endian` | 底层 | 位操作四段组合翻转字节序 |
| 30 | `30_debug_print` | 底层 | `__FILE__`/`__LINE__`/`__func__`；宏体用 `do { } while(0)` 包裹 |
| 31 | `31_event_handler` | 底层 | `typedef void (*Handler)(void)` 函数指针数组做事件分发 |
| 32 | `32_container_of_macro` | 底层 | `(type *)((char*)(ptr) - offsetof(type, member))`；`offsetof` 在 `<stddef.h>` |
| 33 | `33_garray_dynamic_array` | 数据结构 | `realloc` 扩容，`void*` 泛型，`memcpy` 追加元素 |
| 34 | `34_protocol_header_parser` | 底层 | 按固定偏移读取二进制字段，`ntohs`/`ntohl` 转字节序 |
| 35 | `35_elf_info_parser` | 二进制 | ELF 节头表按偏移解析，注意字节序和 `e_shoff`/`e_shentsize`/`e_shnum` |
| 37 | `37_bitmap_operations` | 底层 | `set`（`\|=`）、`clear`（`&= ~`）、`test`（`&`）；字节下标 `i/8`，位下标 `i%8` |
| 38 | `38_thread_safe_ring_buffer` | 并发 | mutex + 条件变量；`cond_wait` 用 `while` 防虚假唤醒；push/pop 封装临界区 |
| 39 | `39_strtok_r_thread_safe` | 字符串 | `saveptr` 由调用者保存状态；先跳过分隔符，再原地写入 `\0` 截断 token |
| 40 | `40_bloom_filter_bitmap` | 位图 | 多哈希映射到多个 bit；查询时只要有一位为 0 就一定不存在 |

### ⏳ 待完成（2 / 40）

| 题号 | 题目 | 分类 | 关键前置知识 |
| :--: | --- | :--: | --- |
| 20 | `20_mybash` | 系统 | `fork` / `exec` / `pipe` / `waitpid` |
| 36 | `36_lru_cache` | 数据结构 | 哈希表 + 双向链表组合 |

---

## 二、每题详细笔记

### 01 插入排序

内层循环是在**挪位置**，不是直接交换，最后再填入 `key`。

```c
for (int i = 1; i < n; i++) {
    int key = arr[i], j = i - 1;
    while (j >= 0 && arr[j] > key) { arr[j + 1] = arr[j]; j--; }
    arr[j + 1] = key;
}
```

### 02 归并排序

合并后要把剩余元素补进去，临时数组边界别写错。

### 03 快速排序

先分区，再递归；基准值取 `arr[right]`，交换后基准落定，递归不包含基准。

```c
int pivot = arr[right], i = left - 1;
for (int j = left; j < right; j++)
    if (arr[j] < pivot) { i++; swap(&arr[i], &arr[j]); }
swap(&arr[i + 1], &arr[right]);
// 递归：[left, i]  [i+2, right]
```

### 04 线性查找

```c
for (int i = 0; i < n; i++) if (arr[i] == target) return i;
return -1;
```

### 05 二分查找

边界更新用 `mid±1`；字符串比较用 `strcmp`，不能用 `==`。

```c
int left = 0, right = n - 1;
while (left <= right) {
    int mid = (left + right) / 2;
    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) left = mid + 1;
    else right = mid - 1;
}
return -1;
```

### 06 栈迷宫（DFS）

`visited` 防重复，走不通弹栈；注意测试可能要求特定方向顺序。

```c
visited[0][0] = 1; stack[++top] = (Pos){0, 0};
while (top != -1) {
    int found = 0;
    if (/* 到终点 */) break;
    // 按顺序试探方向
    if (/* 下一点可走 */) { stack[++top] = next; visited[r][c] = 1; found = 1; break; }
    if (!found) top--;  // 回退
}
```

### 07 队列迷宫（BFS）

队列存待处理的**点**，不是路径；`parent` 记录每个点怎么来的，最后倒推。

```c
queue[rear++] = start; visited[0][0] = 1;
while (front != rear) {
    Pos cur = queue[front++];
    if (/* 到终点 */) { found = 1; break; }
    // 扩展四方向，parent[nr][nc] = cur，入队
}
// 回溯路径
while (cur != start) { path[len++] = cur; cur = parent[cur.r][cur.c]; }
```

### 08 环形队列

判空：`front == rear`；判满：`(rear + 1) % cap == front`（预留一个空位）。

### 09 词计数

```c
if (isspace(ch)) in_word = 0;
else if (!in_word) { count++; in_word = 1; }
```

### 10 my_strcpy

```c
int i = 0;
while (src[i]) { dest[i] = src[i]; i++; }
dest[i] = '\0';
```

### 11 命令解析器

状态机：`OUT_WORD` / `IN_WORD`；`\0` 也要当作分隔符处理，结束单词。

```c
if (state == OUT_WORD) {
    if (ch && ch != ' ' && ch != '\t') { argv[argc++] = &buf[i]; state = IN_WORD; }
} else {
    if (!ch || ch == ' ' || ch == '\t') { buf[i] = '\0'; state = OUT_WORD; }
}
```

### 12 学生管理

删除时后续元素前移：

```c
for (int i = pos; i < count - 1; i++) students[i] = students[i + 1];
count--;
```

### 13 通用排序

`qsort` 的比较函数返回负/零/正，语义要全程一致；泛型用 `void *` 接收再强转。

### 14 计算器

`switch` 分发四则运算；除法必须先判 `b == 0`，否则是 UB。

### 15 URL 解析

先用 `strstr` 找 `://` 拆出协议，再找第一个 `/` 分隔主机和路径，端口在主机里用 `:` 再次拆分。

### 16 mysed / 17 myfile / 18 mywc / 19 mytrans

> 逻辑较直接，参见总览表格中的核心要点即可。

### 21 单链表约瑟夫

删节点顺序：**先存 next → 再 free → 再移动**，不要在 free 之后读 `current->next`。

### 22 双向环形队列

入队出队时前后指针（`prev`/`next`）必须**同步**更新，漏掉其中一个就断链。

### 23 环形链表约瑟夫

`prev` 要跟着 `current` 每步同步移动，不能只在删除时才更新。

```c
for (int i = 0; i < m - 1; i++) { prev = current; current = current->next; }
Node *nxt = current->next;
prev->next = nxt;
free(current);
current = nxt;
```

### 24 前序二叉树

递归前先判 `NULL`；顺序严格是 根 → 左 → 右。

### 25 字母计数

```c
if (isalpha(ch)) count[tolower(ch) - 'a']++;
```

### 26 哈希词频统计

⚠️ **`strdup` 坑**：`-std=c11` 下 `strdup` 未声明，返回值被隐式当 `int`，导致指针截断段错误。
修复：文件顶部加 `#define _POSIX_C_SOURCE 200809L`。

### 27 汇编 GCD

内联汇编输入/输出/破坏寄存器约束三者都要写完整，否则编译器优化出错。

### 28 无符号整数溢出检测

| 运算 | 溢出条件 |
| --- | --- |
| `a + b` | `a + b < a` |
| `a - b` | `a - b > a` |
| `a * b` | `b != 0 && a * b / b != a` |
| `a / b` | `b == 0` |

### 29 字节序交换

```c
uint32_t swap32(uint32_t x) {
    return ((x & 0xFF) << 24) | ((x & 0xFF00) << 8)
         | ((x >> 8) & 0xFF00) | ((x >> 24) & 0xFF);
}
```

### 30 调试打印宏

```c
#define DBG(fmt, ...) \
    do { fprintf(stderr, "[%s:%d %s] " fmt "\n", \
         __FILE__, __LINE__, __func__, ##__VA_ARGS__); } while(0)
```

`do { } while(0)` 避免 if-else 下宏展开产生语法歧义。

### 31 事件处理器

```c
typedef void (*Handler)(void);
Handler handlers[MAX_EVENT] = { handler_a, handler_b, ... };
handlers[event]();  // 直接下标分发
```

### 32 container_of 宏

```c
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - offsetof(type, member)))
```

`offsetof` 来自 `<stddef.h>`；强转为 `char *` 后做字节级减法。

### 33 泛型动态数组

偏移计算：`(char *)arr->data + arr->len * arr->elem_size`。
扩容：`realloc`，失败时原指针仍有效，不要直接覆盖。

### 34 协议头解析

结构体可能有对齐 padding，直接用字节偏移比强转结构体指针更可靠；`ntohs`/`ntohl` 转网络字节序。

### 35 ELF 文件解析

读取 ELF 文件头（`Elf64_Ehdr`）获取 `e_shoff`（节头表偏移）、`e_shentsize`（每项大小）、`e_shnum`（项数）；再读节头字符串表（`e_shstrndx`）定位节名；结构体字段有字节序问题时用 `le16toh`/`le32toh`。

### 37 位图操作

```c
bitmap[i / 8] |=  (1 << (i % 8));  // set
bitmap[i / 8] &= ~(1 << (i % 8));  // clear
bitmap[i / 8] &   (1 << (i % 8));  // test
```

### 38 线程安全环形缓冲区

**数据结构**：数组 + `head`/`tail`/`count`，`tail` 写入，`head` 读出，下标取模回绕。

**临界区**：所有对 `buf`/`head`/`tail`/`count` 的读写都必须在 `mutex_lock` / `mutex_unlock` 之间。

**条件变量使用规范**：
- 满则等 `not_full`，空则等 `not_empty`
- 等待条件**必须用 `while`**，不能用 `if`（防虚假唤醒 + 多消费者竞争）
- `cond_wait` = 原子释放锁 → 睡眠 → 被唤醒 → 重新加锁 → 返回

```c
// push 骨架
pthread_mutex_lock(&rb->mtx);
while (rb->count == rb->capacity)
    pthread_cond_wait(&rb->not_full, &rb->mtx);
rb->buf[rb->tail] = val;
rb->tail = (rb->tail + 1) % rb->capacity;
rb->count++;
pthread_cond_signal(&rb->not_empty);
pthread_mutex_unlock(&rb->mtx);
```

**producer / consumer 本身极简**：只需循环调用 `rb_push` / `rb_pop`，加锁逻辑全被封装在内部，线程函数记得 `return NULL`。

**`rb_init` 资源泄漏陷阱**：`mutex_init` 成功后若 `cond_init` 失败，需要销毁已初始化的 mutex；`free` 后记得 `rb->buf = NULL`。

### 39 线程安全字符串分割器

关键在于 **不使用静态全局状态**，而是把“切到哪里了”交给调用者传入的 `saveptr` 保存。

实现顺序固定为：
- 如果 `str != NULL`，从新字符串开始；否则从 `*saveptr` 继续
- 先跳过连续分隔符，避免返回空 token
- 记录 token 起点
- 继续扫描到下一个分隔符或 `\0`
- 若遇到分隔符，把它改成 `\0`，并把 `*saveptr` 指向下一个字符
- 若到达结尾，返回最后一个 token，并把 `*saveptr` 设为当前末尾位置

```c
while (*p && is_delim(*p, delim)) p++;
if (*p == '\0') return NULL;

char *token = p;
while (*p && !is_delim(*p, delim)) p++;
if (*p) {
    *p = '\0';
    *saveptr = p + 1;
}
```

### 40 位图实现 Bloom 过滤器

Bloom Filter 的特点：**无假阴性，但可能假阳性**。

- 插入元素：用 3 个哈希函数分别算位置，把对应 bit 置 1
- 查询元素：再次算出这 3 个位置，只要有任意一个 bit 为 0，就一定不存在
- 位图的字节数要按 `(m + 7) / 8` 分配

位操作模板：

```c
bm[idx / 8] |=  (1u << (idx % 8));
bm[idx / 8] &   (1u << (idx % 8));
```

简单哈希可按题意写成：

```c
size_t sum = 0;
while (*s) {
    sum += (unsigned char)(*s) * (size_t)k;
    s++;
}
return sum % m;
```

---

## 三、开始新题前的 Checklist



- [ ] 测试期望什么**输出格式**（换行、空格、顺序）？
- [ ] 核心数据结构是什么：数组 / 栈 / 队列 / 链表 / 哈希 / 树？
- [ ] 有哪些**边界条件**：空输入、长度为 0/1、`\0`、越界、起点 = 终点？
- [ ] 链表题：删节点时有没有**维护前驱**？
- [ ] BFS 题：队列存的是**点**，`parent` 怎么记？
- [ ] DFS 题：栈里装的是**当前路径**，回退逻辑对不对？
- [ ] 二分查找：数据**有序**了吗？`left`/`right`/`mid` 更新方式？
- [ ] 用了 POSIX 扩展函数（`strdup` 等）吗？需要加 `_POSIX_C_SOURCE` 吗？
- [ ] 并发题：`cond_wait` 用 `while` 了吗（不是 `if`）？
- [ ] 并发题：所有共享变量的读写都在锁保护内吗？
- [ ] 并发题：线程函数返回 `NULL` 了吗？
- [ ] 并发题：`init` 失败时有没有清理已成功初始化的资源？
