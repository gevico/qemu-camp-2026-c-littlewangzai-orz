# 链表总结

---

## 0. C 里修改头指针的三种写法

| 写法 | 方式 | 特点 |
|---|---|---|
| A | `void f(Node **head)` 传二级指针 | 最绕，`*head` 到处都是 |
| B | `Node *f(Node *head)` 返回新头 | 直观，调用处 `head = f(head, ...)` |
| C | 哨兵 dummy head | 最舒服，永远不需要动 head 本身 |

后续每个操作都给出这三个版本，C++ 版用 `class` 封装（天然是写法 C 的思路）。

---

## 1. 单链表

### 结构

```c
// C
typedef struct Node { int val; struct Node *next; } Node;

// C++
struct Node { int val; Node *next; Node(int v) : val(v), next(nullptr) {} };
```

---

### 头插

**写法 A（二级指针）**
```c
void push_front(Node **head, int v) {
    Node *p = malloc(sizeof(Node));
    p->val = v;
    p->next = *head;
    *head = p;
}
// 调用：push_front(&head, v);
```

**写法 B（返回新头）**
```c
Node *push_front(Node *head, int v) {
    Node *p = malloc(sizeof(Node));
    p->val = v;
    p->next = head;
    return p;
}
// 调用：head = push_front(head, v);
```

**写法 C（dummy 哨兵）**
```c
// dummy 节点不存数据，dummy.next 才是真正的第一个节点
void push_front(Node *dummy, int v) {
    Node *p = malloc(sizeof(Node));
    p->val = v;
    p->next = dummy->next;
    dummy->next = p;
}
```

**C++ class 版**
```cpp
class LinkedList {
    Node *head = nullptr;
public:
    void push_front(int v) {
        Node *p = new Node(v);
        p->next = head;
        head = p;
    }
};
```

---

### 尾插

**写法 A**
```c
void push_back(Node **head, int v) {
    Node *p = malloc(sizeof(Node));
    p->val = v; p->next = NULL;
    if (!*head) { *head = p; return; }
    Node *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = p;
}
```

**写法 B**
```c
Node *push_back(Node *head, int v) {
    Node *p = malloc(sizeof(Node));
    p->val = v; p->next = NULL;
    if (!head) return p;
    Node *cur = head;
    while (cur->next) cur = cur->next;
    cur->next = p;
    return head;
}
```

**写法 C**
```c
void push_back(Node *dummy, int v) {
    Node *p = malloc(sizeof(Node));
    p->val = v; p->next = NULL;
    Node *cur = dummy;
    while (cur->next) cur = cur->next;
    cur->next = p;
}
```

**C++ class 版**
```cpp
void push_back(int v) {
    Node *p = new Node(v);
    if (!head) { head = p; return; }
    Node *cur = head;
    while (cur->next) cur = cur->next;
    cur->next = p;
}
```

---

### 删除指定值

**写法 A**
```c
void remove_val(Node **head, int v) {
    if (!*head) return;
    if ((*head)->val == v) {           // 特判头节点
        Node *del = *head;
        *head = (*head)->next;
        free(del); return;
    }
    Node *cur = *head;
    while (cur->next && cur->next->val != v) cur = cur->next;
    if (cur->next) {
        Node *del = cur->next;
        cur->next = del->next;
        free(del);
    }
}
```

**写法 B**
```c
Node *remove_val(Node *head, int v) {
    if (!head) return NULL;
    if (head->val == v) {              // 特判头节点
        Node *del = head;
        head = head->next;
        free(del); return head;
    }
    Node *cur = head;
    while (cur->next && cur->next->val != v) cur = cur->next;
    if (cur->next) {
        Node *del = cur->next;
        cur->next = del->next;
        free(del);
    }
    return head;
}
```

**写法 C（dummy 完全消除头节点特判）**
```c
void remove_val(Node *dummy, int v) {
    Node *cur = dummy;
    while (cur->next && cur->next->val != v) cur = cur->next;
    if (cur->next) {
        Node *del = cur->next;
        cur->next = del->next;
        free(del);
    }
}
```

**C++ class 版**
```cpp
void remove_val(int v) {
    Node dummy(0); dummy.next = head;
    Node *cur = &dummy;
    while (cur->next && cur->next->val != v) cur = cur->next;
    if (cur->next) {
        Node *del = cur->next;
        cur->next = del->next;
        delete del;
    }
    head = dummy.next;
}
```

> ✅ 写法 A 和 B 都要单独处理头节点；写法 C / class 用 dummy 彻底消除这个特判

---

### 查找

```c
// 三种写法的查找逻辑完全一样，只是传参不同
// 写法 A/B：传 Node *head
// 写法 C：传 dummy->next
Node *find(Node *head, int v) {
    while (head && head->val != v) head = head->next;
    return head;   // NULL 表示没找到
}
```

---

### 遍历 / 释放

```c
void traverse(Node *head) {
    while (head) { printf("%d ", head->val); head = head->next; }
}

void free_list(Node *head) {
    while (head) { Node *nxt = head->next; free(head); head = nxt; }
}
```

**C++ class 析构**
```cpp
~LinkedList() {
    while (head) { Node *nxt = head->next; delete head; head = nxt; }
}
```

---

## 2. 双向链表

### 结构

```c
// C
typedef struct DNode { int val; struct DNode *prev, *next; } DNode;

// C++
struct DNode { int val; DNode *prev, *next; DNode(int v):val(v),prev(nullptr),next(nullptr){} };
```

---

### 头插

**写法 A**
```c
void dpush_front(DNode **head, int v) {
    DNode *p = malloc(sizeof(DNode));
    p->val = v; p->prev = NULL; p->next = *head;
    if (*head) (*head)->prev = p;
    *head = p;
}
```

**写法 B**
```c
DNode *dpush_front(DNode *head, int v) {
    DNode *p = malloc(sizeof(DNode));
    p->val = v; p->prev = NULL; p->next = head;
    if (head) head->prev = p;
    return p;
}
```

**写法 C**
```c
// dummy 节点作为永久头，dummy.next 是第一个真实节点
void dpush_front(DNode *dummy, int v) {
    DNode *p = malloc(sizeof(DNode));
    p->val = v;
    p->next = dummy->next;
    p->prev = dummy;
    if (dummy->next) dummy->next->prev = p;
    dummy->next = p;
}
```

**C++ class 版**
```cpp
class DoublyList {
    DNode *head = nullptr;
public:
    void push_front(int v) {
        DNode *p = new DNode(v);
        p->next = head;
        if (head) head->prev = p;
        head = p;
    }
};
```

---

### 删除（已知节点，O(1)）

**写法 A**
```c
void ddelete(DNode **head, DNode *p) {
    if (p->prev) p->prev->next = p->next;
    else         *head = p->next;
    if (p->next) p->next->prev = p->prev;
    free(p);
}
```

**写法 B**
```c
DNode *ddelete(DNode *head, DNode *p) {
    if (p->prev) p->prev->next = p->next;
    else         head = p->next;
    if (p->next) p->next->prev = p->prev;
    free(p);
    return head;
}
```

**写法 C**
```c
// 用了 dummy 之后，p->prev 永远不为 NULL（最坏也指向 dummy），不再需要特判
void ddelete(DNode *p) {
    p->prev->next = p->next;
    if (p->next) p->next->prev = p->prev;
    free(p);
}
```

**C++ class 版**
```cpp
void remove(DNode *p) {
    if (p->prev) p->prev->next = p->next;
    else         head = p->next;
    if (p->next) p->next->prev = p->prev;
    delete p;
}
```

> ⚠️ prev 和 next 两个方向都要改，漏一个就断链

---

## 3. 环形单链表

尾节点的 `next` 指向头节点，不是 `NULL`。

### 创建

```c
Node *create_circular(int n) {
    if (n <= 0) return NULL;
    Node *head = malloc(sizeof(Node)); head->val = 1;
    Node *tail = head;
    for (int i = 2; i <= n; i++) {
        Node *p = malloc(sizeof(Node)); p->val = i;
        tail->next = p; tail = p;
    }
    tail->next = head;   // 成环
    return head;
}
```

### 删除节点（prev 版，无 dummy）

```c
// prev 始终是 current 的前驱，每步都要同步移动
Node *nxt = current->next;
prev->next = nxt;
free(current);
current = nxt;
```

### 释放

```c
void free_circular(Node *head) {
    if (!head) return;
    Node *cur = head;
    do {
        Node *nxt = cur->next;
        free(cur); cur = nxt;
    } while (cur != head);   // ⚠️ 不能用 while(cur != NULL)，会死循环
}
```

---

## 4. 双向循环队列（FIFO）

入队 = 头插，出队 = 删尾

**C 写法 B**
```c
DNode *enqueue(DNode *head, int v) { return dpush_front(head, v); }

int dequeue(DNode **head, int *out) {
    if (!*head) return 0;
    DNode *cur = *head;
    while (cur->next) cur = cur->next;
    *out = cur->val;
    *head = ddelete(*head, cur);
    return 1;
}
```

**C++ class 版（用 std::deque）**
```cpp
#include <deque>
deque<int> q;
q.push_back(v);                        // 入队
int v = q.front(); q.pop_front();      // 出队
```

---

## 5. 约瑟夫环

### 环形链表解法（C）

```c
// prev 初始化为尾节点（current 的前驱）
Node *prev = head;
while (prev->next != head) prev = prev->next;

for (int out = 0; out < n; out++) {
    for (int i = 0; i < m - 1; i++) {   // 走 m-1 步，prev 跟着走
        prev = current;
        current = current->next;
    }
    printf("%d ", current->val);
    Node *nxt = current->next;
    prev->next = nxt;
    free(current);
    current = nxt;
}
```

---

## 6. 力扣经典题

### LeetCode 206 — 反转链表

```c
// C（写法 B）
Node *reverse(Node *head) {
    Node *prev = NULL, *cur = head;
    while (cur) {
        Node *nxt = cur->next;
        cur->next = prev;
        prev = cur; cur = nxt;
    }
    return prev;
}
```
```cpp
// C++ class 版
void reverse() {
    Node *prev = nullptr, *cur = head;
    while (cur) { Node *nxt = cur->next; cur->next = prev; prev = cur; cur = nxt; }
    head = prev;
}
```

---

### LeetCode 21 — 合并两个有序链表

```c
// C（写法 C，用 dummy）
Node *merge(Node *l1, Node *l2) {
    Node dummy = {0, NULL};
    Node *cur = &dummy;
    while (l1 && l2) {
        if (l1->val <= l2->val) { cur->next = l1; l1 = l1->next; }
        else                    { cur->next = l2; l2 = l2->next; }
        cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    return dummy.next;
}
```

---

### LeetCode 141 — 判断有无环

```c
// C — 快慢指针，有环必相遇
bool has_cycle(Node *head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) return true;
    }
    return false;
}
```

---

### LeetCode 19 — 删除倒数第 N 个节点

```c
// C（写法 C，用 dummy）
// 快指针先走 n+1 步，快慢同步走，快到 NULL 时慢指针的 next 就是目标
Node *remove_nth(Node *head, int n) {
    Node dummy = {0, head};
    Node *fast = &dummy, *slow = &dummy;
    for (int i = 0; i <= n; i++) fast = fast->next;
    while (fast) { fast = fast->next; slow = slow->next; }
    Node *del = slow->next;
    slow->next = del->next;
    free(del);
    return dummy.next;
}
```

---

### LeetCode 160 — 找两链表交点

```c
// C — 双指针换链表，路径等长时相遇
Node *get_intersection(Node *a, Node *b) {
    Node *pa = a, *pb = b;
    while (pa != pb) {
        pa = pa ? pa->next : b;
        pb = pb ? pb->next : a;
    }
    return pa;   // NULL 表示不相交
}
```

---

### LeetCode 234 — 回文链表

```c
// C — 找中点 → 反转后半 → 比较
bool is_palindrome(Node *head) {
    Node *slow = head, *fast = head;
    while (fast && fast->next) { slow = slow->next; fast = fast->next->next; }
    // 反转后半段
    Node *prev = NULL, *cur = slow;
    while (cur) { Node *nxt = cur->next; cur->next = prev; prev = cur; cur = nxt; }
    // 逐一比较
    Node *left = head, *right = prev;
    while (right) {
        if (left->val != right->val) return false;
        left = left->next; right = right->next;
    }
    return true;
}
```

---

## 7. 常见边界条件

| 场景 | 容易出的 bug |
|---|---|
| 链表为空时操作 | 没判 `head == NULL` 直接解引用 |
| 删除头节点（写法A/B） | 忘了更新 `head` 指针 |
| 删除唯一节点 | 删完后 `head` 应变 `NULL` |
| 释放环形链表 | 用 `while(cur != NULL)` 死循环，应用 `do-while(cur != head)` |
| 环形链表删节点 | `prev` 没跟着 `current` 走，`prev->next` 仍指向已 free 的内存 |
| 删除前取后继 | 先 `nxt = p->next`，再 `free(p)`，顺序反了找不到后继 |
| 双向链表删节点 | 只改了一个方向，漏了另一个方向 |
| 约瑟夫环 k > n | 需回绕，不能直接走 k 步 |
| 快慢指针找中点 | 奇偶节点数不同，中点定义要提前确认 |

---

## 8. 操作复杂度速查

| 操作 | 单链表 | 双向链表 | 环形链表 |
|---|---|---|---|
| 头插 | O(1) | O(1) | O(1) |
| 尾插 | O(n)，带 tail 则 O(1) | O(n)，带 tail 则 O(1) | O(n)，带 tail 则 O(1) |
| 删除（已知节点） | O(n) 找前驱 | **O(1)** | O(n) 找前驱 |
| 查找 | O(n) | O(n) | O(n) |
| 遍历 | O(n) | O(n) | O(n)，注意终止条件 |
