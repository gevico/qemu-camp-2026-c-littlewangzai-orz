# 练习记录

这份文件用来记录当前已经通过的练习、各题核心知识点，以及继续做题前值得先看的提醒。

## 当前状态

- 统计时间：`2026-04-20`
- 总题数：`40`
- 已通过：`34`
- 未完成：`6`
- 当前得分：`170 / 200`

## 当前已通过练习

| 题号 | 题目 | 我应该记住什么 |
| --- | --- | --- |
| 01 | `01_insert_sort` | 插入排序的核心是"前面保持有序，把当前元素插进去" |
| 02 | `02_merge_sort` | 先拆分再合并，合并时用双指针保证有序 |
| 03 | `03_quick_sort` | 快速排序的关键是分区，递归处理左右子区间 |
| 04 | `04_linear_search` | 线性查找就是从头到尾逐个比较 |
| 05 | `05_binary_search` | 只对有序数据生效，关键是正确更新边界 |
| 06 | `06_stack_maze` | DFS 用栈，栈里存当前路径，走不通就回退 |
| 07 | `07_queue_maze` | BFS 用队列，`parent` 用来回溯最短路径 |
| 08 | `08_circular_queue` | 环形队列用取模回绕，重点是判空判满条件 |
| 09 | `09_word_counter` | 核心是逐字符扫描并统计 |
| 10 | `10_my_strcpy` | 指针或下标拷贝字符串，记得补 `\0` |
| 11 | `11_command_interpreter` | 状态机解析参数时，开始位置和结束位置都要想清楚 |
| 12 | `12_student_management` | 结构体数组 + 查找/增加/删除逻辑 |
| 13 | `13_universal_sorter` | 把"比较逻辑"抽出来，排序流程可复用 |
| 14 | `14_calculator` | 输入解析和运算分发要稳定 |
| 15 | `15_url_parser` | 先切协议/主机/路径，再处理端口和边界 |
| 16 | `16_mysed` | 按规则逐行处理，替换时注意匹配范围 |
| 17 | `17_myfile` | 文件操作要检查返回值，错误路径也要覆盖 |
| 18 | `18_mywc` | 统计逻辑与输入边界（空文件、最后一行）要一致 |
| 19 | `19_mytrans` | 字符转换逐字符处理，注意大小写和特殊字符边界 |
| 21 | `21_singly_linked_list_josephus` | 单链表模拟约瑟夫环，删节点时先保存 next，再 free |
| 22 | `22_doubly_circular_queue` | 双向环形队列，注意前后指针的更新顺序 |
| 23 | `23_circular_linked_list_josephus` | 环形链表删节点必须用 prev 维护前驱，否则链表断链 |
| 24 | `24_prev_binary_tree` | 二叉树前序遍历，注意递归边界和空节点处理 |
| 25 | `25_counter_letter` | 字母频率统计，26个桶分别计数 |
| 26 | `26_hash_counter` | 哈希表统计词频；`strdup` 在 `-std=c11` 下需要 `#define _POSIX_C_SOURCE 200809L` |
| 27 | `27_asm_gcd` | 内联汇编实现辗转相除法，注意寄存器约束 |
| 28 | `28_operator_overflow` | 无符号整数加减乘除的溢出检测 |
| 29 | `29_swap_endian` | 位操作交换字节序，`((x >> 24) & 0xFF)` 等四段组合 |
| 30 | `30_debug_print` | 宏实现调试打印，`__FILE__`、`__LINE__`、`__func__` 的使用 |
| 31 | `31_event_handler` | 函数指针数组实现事件回调分发 |
| 32 | `32_container_of_macro` | `container_of` 宏：通过成员指针反推结构体指针，用 `offsetof` 计算偏移 |
| 33 | `33_garray_dynamic_array` | `realloc` 扩容，`void*` 泛型，`memcpy` 拷贝元素 |
| 34 | `34_protocol_header_parser` | 按字段偏移解析二进制协议头，注意字节序和位域 |
| 37 | `37_bitmap_operations` | 位图操作：`set/clear/test` 用位运算，注意字节下标和位下标 |

## 当前未通过 / 未完成练习

| 题号 | 题目 | 备注 |
| --- | --- | --- |
| 20 | `20_mybash` | 未开始 |
| 35 | `35_elf_info_parser` | 未开始 |
| 36 | `36_lru_cache` | 未开始 |
| 38 | `38_thread_safe_ring_buffer` | 未开始 |
| 39 | `39_strtok_r_thread_safe` | 未开始 |
| 40 | `40_bloom_filter_bitmap` | 未开始 |

## 每题简记

### 01_insert_sort

- 重点：把当前元素插入到前面已经有序的部分。
- 容易忘：内层循环是在"挪位置"，不是直接乱换。

```c
for (int i = 1; i < n; i++) {
  int key = arr[i];
  int j = i - 1;
  while (j >= 0 && arr[j] > key) {
    arr[j + 1] = arr[j];
    j--;
  }
  arr[j + 1] = key;
}
```

### 02_merge_sort

- 重点：分治，递归拆分后在线性时间内合并两个有序段。
- 容易忘：合并后把剩余元素补齐，临时数组边界别写错。

### 03_quick_sort

- 重点：先分区，再递归。
- 容易忘：基准值、左右指针移动、递归边界。

```c
int pivot = arr[right];
int i = left - 1;
for (int j = left; j < right; j++) {
  if (arr[j] < pivot) { i++; swap(&arr[i], &arr[j]); }
}
swap(&arr[i + 1], &arr[right]);
```

### 04_linear_search

- 重点：从头扫到尾，找到就返回，找不到返回失败值。

```c
for (int i = 0; i < n; i++) {
  if (arr[i] == target) return i;
}
return -1;
```

### 05_binary_search

- 重点：只能用于有序数据，每次把范围砍一半。
- 容易忘：边界更新要排除 `mid`（用 `mid+1` / `mid-1`），名字比较用 `strcmp`。

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

### 06_stack_maze

- 重点：`visited` 防重复，栈保存当前路径，走不通弹栈回退。
- 容易忘：测试可能要求特定方向顺序。

```c
visited[0][0] = 1;
stack[++top] = (Pos){0, 0};
while (top != -1) {
    if (/* 到终点 */) break;
    if (/* 下一个点可走 */) { stack[++top] = next; visited[...] = 1; found = 1; }
    if (!found) top--;
}
```

### 07_queue_maze

- 重点：BFS 第一次到终点就是最短路，路径靠 `parent` 倒推。
- 容易忘：队列里放的是"待处理的点"，不是路径本身。

```c
queue[rear++] = (Pos){0, 0};
visited[0][0] = 1;
while (front != rear) {
    Pos cur = queue[front++];
    if (/* 到终点 */) { found = 1; break; }
    // 扩展四方向，记录 parent，入队
}
// 从终点沿 parent 回溯
while (cur.row != 0 || cur.col != 0) {
    path[length++] = cur;
    cur = parent[cur.row][cur.col];
}
```

### 08_circular_queue

- 重点：用取模实现首尾相接，`front/rear` 更新要统一。
- 容易忘：判空判满定义必须和实现一致（通常预留一个空位）。

### 09_word_counter

- 重点：明确"何时开始一个单词，何时结束"。
- 容易忘：空格、换行、制表符都是分隔符。

```c
if (isspace(ch)) in_word = 0;
else if (!in_word) { count++; in_word = 1; }
```

### 10_my_strcpy

- 重点：逐字符拷贝，最后补 `\0`。

```c
int i = 0;
while (src[i] != '\0') { dest[i] = src[i]; i++; }
dest[i] = '\0';
```

### 11_command_interpreter

- 重点：状态机解析，`OUT_WORD` / `IN_WORD` 两个状态。
- 容易忘：`\0` 也是边界，结束单词时把分隔符改成 `\0`。

```c
if (state == OUT_WORD) {
  if (ch != ' ' && ch != '\t' && ch != '\0') { argv[argc++] = &buf[i]; state = IN_WORD; }
} else {
  if (ch == ' ' || ch == '\t') { buf[i] = '\0'; state = OUT_WORD; }
}
```

### 12_student_management

- 重点：结构体数组管理，删除时后面的元素要前移。

```c
for (int i = pos; i < count - 1; i++) students[i] = students[i + 1];
count--;
```

### 13_universal_sorter

- 重点：比较函数参数化，返回值语义（负/零/正）全程一致。

### 14_calculator

- 重点：`switch` 分发运算，注意除零。

### 15_url_parser

- 重点：先按结构拆字段，再校验每段；注意无端口、无路径等分支。

### 16_mysed

- 重点：按行读取并执行替换，是否替换全部匹配按题意来。

### 17_myfile

- 重点：文件读写、定位、错误处理返回码要完整，失败时不能继续用无效句柄。

### 18_mywc

- 重点：字符/单词/行计数状态清晰；最后一行无换行符时行数要对。

### 19_mytrans

- 重点：字符转换逐字符处理，明确转换规则的覆盖范围。
- 容易忘：大小写互转用 `toupper`/`tolower`，非字母字符保持不变。

### 21_singly_linked_list_josephus

- 重点：单链表约瑟夫环，删节点前先 `link next = next_wrap(current)`，再 `delete(current)`，再 `current = next`。
- 容易忘：`next_wrap` 依赖 `traverse` 找头节点，删完节点后链表结构变化但仍能正确找头。

### 22_doubly_circular_queue

- 重点：双向环形队列，入队/出队时前后指针都要同步更新。

### 23_circular_linked_list_josephus

- 重点：环形链表，删节点时 `prev->next = next` 维护链路，`prev` 必须始终是 `current` 的前驱。
- 容易忘：`prev` 要跟着 `current` 一起走，每步报数都要同步移动。

```c
for (int i = 0; i < m - 1; ++i) { prev = current; current = current->next; }
Node* next = current->next;
prev->next = next;
free(current);
current = next;
```

### 24_prev_binary_tree

- 重点：前序遍历顺序是 根 → 左 → 右，递归时先处理当前节点再向下走。
- 容易忘：空节点（`NULL`）是递归终止条件，必须检查。

### 25_counter_letter

- 重点：26 个桶 `count['z'-'a']`，字母转小写后统一计数。
- 容易忘：非字母字符跳过，不要计入任何桶。

### 26_hash_counter

- 重点：哈希表统计词频，`insert` 时先查找是否存在，存在则 `count++`，不存在才创建新节点（`count=1`）。
- 坑：`strdup` 不是 C11 标准函数，用 `-std=c11` 编译时需要在文件顶部加 `#define _POSIX_C_SOURCE 200809L`，否则返回值被当 `int` 处理导致段错误。

### 27_asm_gcd

- 重点：内联汇编 `asm` 实现辗转相除，注意输入/输出/破坏寄存器约束。

### 28_operator_overflow

- 重点：无符号整数各运算的溢出判断条件。
  - 加法：`a + b < a`
  - 减法：`a - b > a`
  - 乘法：`b != 0 && a * b / b != a`
  - 除法：除零视为溢出

### 29_swap_endian

- 重点：位操作字节序翻转。

```c
uint32_t swap = ((x & 0xFF) << 24) | ((x & 0xFF00) << 8)
              | ((x >> 8) & 0xFF00) | ((x >> 24) & 0xFF);
```

### 30_debug_print

- 重点：用宏实现调试输出，`__FILE__`、`__LINE__`、`__func__` 是编译器内置宏。
- 容易忘：`do { ... } while(0)` 包裹宏体，避免 if-else 时出现语法问题。

### 31_event_handler

- 重点：函数指针数组做事件分发，用 `typedef void (*Handler)(void)` 等定义类型。

### 32_container_of_macro

- 重点：`container_of(ptr, type, member)` = `(type *)((char*)(ptr) - offsetof(type, member))`。
- 容易忘：`offsetof` 在 `<stddef.h>` 中，强转为 `char*` 再减偏移是关键。

### 33_garray_dynamic_array

- 重点：`realloc` 扩容，`void*` + 元素字节大小实现泛型，`memcpy` 追加元素。
- 容易忘：偏移计算 `(char*)arr->data + arr->len * arr->elem_size`。

### 34_protocol_header_parser

- 重点：按固定偏移读取二进制字段，注意网络字节序转换（`ntohs`/`ntohl`）。
- 容易忘：结构体可能有对齐 padding，直接强转指针比结构体更可靠。

### 37_bitmap_operations

- 重点：位图的三个核心操作：`set`（`|=`）、`clear`（`&= ~`）、`test`（`&`）。
- 容易忘：字节下标 `index / 8`，位下标 `index % 8`，两者不要搞混。

## 做题前提醒

每次开始新题前，先问自己：

1. 测试到底要什么输出格式？
2. 核心数据结构是什么：数组、栈、队列、链表、哈希还是树？
3. 有没有明显边界条件：空输入、越界、`\0`、起点终点、数组长度？
4. 如果是链表题：删节点时有没有维护前驱？
5. 如果是 BFS：队列不是路径，`parent` 怎么存？
6. 如果是 DFS：栈里装的是当前路径，不是所有访问点。
7. 如果是二分查找：先确认数据有序，再写 `left/right/mid`。

## 建议下一批练习

1. `20_mybash`（shell 实现，难度较高，建议先搞清楚 `fork`/`exec`/`pipe`）
2. `35_elf_info_parser`（ELF 文件格式解析）
3. `36_lru_cache`（哈希表 + 双向链表）
4. `38_thread_safe_ring_buffer`（环形缓冲 + 互斥锁）
5. `39_strtok_r_thread_safe`（线程安全字符串分割）
6. `40_bloom_filter_bitmap`（布隆过滤器，位图应用）
