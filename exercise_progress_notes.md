# 练习记录

这份文件用来记录当前已经通过的练习、各题核心知识点，以及继续做题前值得先看的提醒。

## 当前状态

- 统计时间：`2026-04-09T07:13:39Z`
- 总题数：`40`
- 已通过：`10`
- 未完成：`30`
- 当前得分：`50 / 200`

## 当前已通过练习

| 题号 | 题目 | 状态 | 我应该记住什么 |
| --- | --- | --- | --- |
| 01 | `01_insert_sort` | 已通过 | 插入排序的核心是“前面保持有序，把当前元素插进去” |
| 03 | `03_quick_sort` | 已通过 | 快速排序的关键是分区，递归处理左右子区间 |
| 04 | `04_linear_search` | 已通过 | 线性查找就是从头到尾逐个比较 |
| 06 | `06_stack_maze` | 已通过 | DFS 用栈，栈里存当前路径，走不通就回退 |
| 07 | `07_queue_maze` | 已通过 | BFS 用队列，`parent` 用来回溯最短路径 |
| 09 | `09_word_counter` | 已通过 | 核心是逐字符扫描并统计 |
| 10 | `10_my_strcpy` | 已通过 | 指针或下标拷贝字符串，记得补 `\0` |
| 11 | `11_command_interpreter` | 已通过 | 状态机解析参数时，开始位置和结束位置都要想清楚 |
| 12 | `12_student_management` | 已通过 | 结构体数组 + 查找/增加/删除逻辑 |
| 14 | `14_calculator` | 已通过 | 输入解析和运算分发要稳定 |

## 每题简记

### 01_insert_sort

- 已通过。
- 重点：把当前元素插入到前面已经有序的部分。
- 容易忘：内层循环是在“挪位置”，不是直接乱换。
- 实现记忆：

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

### 03_quick_sort

- 已通过。
- 重点：先分区，再递归。
- 容易忘：基准值、左右指针移动、递归边界。
- 实现记忆：

```c
int pivot = arr[right];
int i = left - 1;
for (int j = left; j < right; j++) {
  if (arr[j] < pivot) {
    i++;
    swap(&arr[i], &arr[j]);
  }
}
swap(&arr[i + 1], &arr[right]);
```

### 04_linear_search

- 已通过。
- 重点：从头扫到尾，找到就返回，找不到返回失败值。
- 容易忘：最坏情况要比较完整个数组。
- 实现记忆：

```c
for (int i = 0; i < n; i++) {
  if (arr[i] == target) {
    return i;
  }
}
return -1;
```

### 06_stack_maze

- 已通过。
- 重点：
  - `visited` 防止重复走。
  - 栈保存当前路径。
  - 找不到下一步就弹栈回退。
- 容易忘：测试可能会要求特定的方向顺序和路径输出顺序。
- 实现思路：
  - 起点先入栈并标记访问。
  - 每轮只看栈顶位置。
  - 按固定方向顺序找下一个可走点。
  - 找到就压栈，找不到就 `top--` 回退。
  - 终点到达后，直接从栈顶往栈底打印路径。
- 代码记忆：

```c
visited[0][0] = 1;
stack[++top] = (Pos){0, 0};

while (top != -1) {
    int row_cur = stack[top].row;
    int col_cur = stack[top].col;
    int found = 0;

    if (stack[top].row == MAX_ROW - 1 && stack[top].col == MAX_COL - 1) {
        break;
    }

    if (/* 下一个点可走 */) {
        stack[++top] = next;
        visited[next.row][next.col] = 1;
        found = 1;
    }

    if (!found) {
        top--;
    }
}
```
- 我自己的记忆句：
  - 栈里装的是“当前路径”。
  - DFS 是“能前进就压栈，不能前进就弹栈”。

### 07_queue_maze

- 已通过。
- 重点：
  - 队列保存待扩展节点。
  - BFS 第一次到终点就是最短路。
  - `parent` 记录前驱，用来回溯路径。
- 容易忘：队列不是路径本身，路径要靠 `parent` 倒推。
- 实现思路：
  - 起点入队，`visited` 标记起点。
  - 每次从队头取一个点，扩展它的四个方向。
  - 只要是合法新点，就立刻标记访问、记录 `parent`、然后入队。
  - 第一次取到终点时，就已经保证是最短路。
  - 最后从终点沿 `parent` 一路回溯到起点。
- 代码记忆：

```c
queue[rear++] = (Pos){0, 0};
visited[0][0] = 1;

while (front != rear) {
    Pos cur = queue[front++];

    if (cur.row == MAX_ROW - 1 && cur.col == MAX_COL - 1) {
        found = 1;
        break;
    }

    if (/* next 合法且未访问 */) {
        visited[next.row][next.col] = 1;
        parent[next.row][next.col] = cur;
        queue[rear++] = next;
    }
}
```
- 回溯记忆：

```c
while (cur.row != 0 || cur.col != 0) {
    path[length++] = cur;
    cur = parent[cur.row][cur.col];
}
path[length++] = (Pos){0, 0};
```
- 我自己的记忆句：
  - 队列里放的是“待处理的点”，不是路径。
  - BFS 的路径要靠 `parent` 倒着找回来。

### 09_word_counter

- 已通过。
- 重点：扫描文本时明确“什么时候开始计数，什么时候结束一个单词”。
- 容易忘：空格、换行、制表符这些边界。
- 实现记忆：

```c
if (isspace(ch)) {
  in_word = 0;
} else if (!in_word) {
  count++;
  in_word = 1;
}
```

### 10_my_strcpy

- 已通过。
- 重点：一个字符一个字符复制。
- 容易忘：最后必须补字符串结束符 `\0`。
- 实现记忆：

```c
int i = 0;
while (src[i] != '\0') {
  dest[i] = src[i];
  i++;
}
dest[i] = '\0';
```

### 11_command_interpreter

- 已通过。
- 重点：命令解析常常可以看成状态机。
- 容易忘：字符串结束符 `\0` 也是一个边界条件。
- 实现思路：
  - `OUT_WORD` 状态：跳过空格，等待新单词开始。
  - `IN_WORD` 状态：扫描当前单词，直到遇到空格或 `\0`。
  - 开始单词时记录 `argv[argc++] = &buf[i]`。
  - 结束单词时把分隔符改成 `\0`。
- 代码记忆：

```c
if (state == OUT_WORD) {
  if (ch != ' ' && ch != '\t' && ch != '\0') {
    argv[argc++] = &buf[i];
    state = IN_WORD;
  }
} else {
  if (ch == ' ' || ch == '\t') {
    buf[i] = '\0';
    state = OUT_WORD;
  }
}
```

### 12_student_management

- 已通过。
- 重点：结构体管理、遍历查找、插入删除。
- 容易忘：删除时后面的元素要前移。
- 实现记忆：

```c
for (int i = pos; i < count - 1; i++) {
  students[i] = students[i + 1];
}
count--;
```

### 14_calculator

- 已通过。
- 重点：根据输入选择运算分支。
- 容易忘：输入合法性和除零这种边界。
- 实现记忆：

```c
switch (op) {
case '+': printf("%d\n", a + b); break;
case '-': printf("%d\n", a - b); break;
case '*': printf("%d\n", a * b); break;
case '/':
  if (b != 0) printf("%d\n", a / b);
  break;
}
```

## 当前未通过练习

还没通过的题目：

- `02_merge_sort`
- `05_binary_search`
- `08_circular_queue`
- `13_universal_sorter`
- `15_url_parser`
- `16_mysed`
- `17_myfile`
- `18_mywc`
- `19_mytrans`
- `20_mybash`
- `21_singly_linked_list_josephus`
- `22_doubly_circular_queue`
- `23_circular_linked_list_josephus`
- `24_prev_binary_tree`
- `25_counter_letter`
- `26_hash_counter`
- `27_asm_gcd`
- `28_operator_overflow`
- `29_swap_endian`
- `30_debug_print`
- `31_event_handler`
- `32_container_of_macro`
- `33_garray_dynamic_array`
- `34_protocol_header_parser`
- `35_elf_info_parser`
- `36_lru_cache`
- `37_bitmap_operations`
- `38_thread_safe_ring_buffer`
- `39_strtok_r_thread_safe`
- `40_bloom_filter_bitmap`

## 做题前提醒

每次开始新题前，先问自己这几件事：

1. 测试到底要什么输出格式。
2. 这题核心数据结构是什么：数组、栈、队列、链表、哈希还是树。
3. 有没有明显边界条件：空输入、越界、`\0`、起点终点、数组长度。
4. 如果是路径题：测试要的是起点到终点，还是终点到起点。
5. 如果是 BFS：队列不是路径，记得想清楚 `parent` 怎么存。
6. 如果是 DFS：栈里装的是当前路径，不是所有访问点。

## 建议下一批练习

按现在的学习连续性，下一批最适合继续做的是：

1. `08_circular_queue`
2. `05_binary_search`
3. `02_merge_sort`
4. `13_universal_sorter`

## 之后继续更新的方法

以后每过一题，就补这几行：

```md
### 题号_题目

- 已通过。
- 重点：
- 容易忘：
```