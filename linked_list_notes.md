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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
// C
typedef struct Node { int val; struct Node *next; } Node;

// C++
struct Node { int val; Node *next; Node(int v) : val(v), next(nullptr) {} };
```

---

### 头插

**写法 A（二级指针）**
```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判 nullptr/空容器；头尾节点更新要同步。
// 判断条件：循环退出条件要明确，删除节点后不要再访问已释放对象。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判 nullptr/空容器；头尾节点更新要同步。
// 判断条件：循环退出条件要明确，删除节点后不要再访问已释放对象。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判 nullptr/空容器；头尾节点更新要同步。
// 判断条件：循环退出条件要明确，删除节点后不要再访问已释放对象。
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

### 删除所有等于 `v` 的节点（补充）

```c
// 边界条件：空链表直接返回；可能连续删除多个头节点。
// 判断条件：每次都看 cur->next，命中就删，不命中才后移 cur。
Node *remove_all(Node *head, int v) {
    Node dummy = {0, head};
    Node *cur = &dummy;
    while (cur->next) {
        if (cur->next->val == v) {
            Node *del = cur->next;
            cur->next = del->next;
            free(del);
        } else {
            cur = cur->next;
        }
    }
    return dummy.next;
}
```

---

### 查找

```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
void traverse(Node *head) {
    while (head) { printf("%d ", head->val); head = head->next; }
}

void free_list(Node *head) {
    while (head) { Node *nxt = head->next; free(head); head = nxt; }
}
```

**C++ class 析构**
```cpp
// 边界条件：先判 nullptr/空容器；头尾节点更新要同步。
// 判断条件：循环退出条件要明确，删除节点后不要再访问已释放对象。
~LinkedList() {
    while (head) { Node *nxt = head->next; delete head; head = nxt; }
}
```

### 反转链表模板（补充）

```c
// 边界条件：空链表/单节点链表都应直接正确返回。
// 判断条件：改 cur->next 前先保存 nxt，避免后继丢失。
Node *reverse_iter(Node *head) {
    Node *prev = NULL, *cur = head;
    while (cur) {
        Node *nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}

// 递归版：回溯时翻转指针方向
Node *reverse_rec(Node *head) {
    if (!head || !head->next) return head;
    Node *new_head = reverse_rec(head->next);
    head->next->next = head;
    head->next = NULL;
    return new_head;
}
```

---

## 2. 双向链表

### 结构

```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
// C
typedef struct DNode { int val; struct DNode *prev, *next; } DNode;

// C++
struct DNode { int val; DNode *prev, *next; DNode(int v):val(v),prev(nullptr),next(nullptr){} };
```

---

### 头插

**写法 A**
```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
void dpush_front(DNode **head, int v) {
    DNode *p = malloc(sizeof(DNode));
    p->val = v; p->prev = NULL; p->next = *head;
    if (*head) (*head)->prev = p;
    *head = p;
}
```

**写法 B**
```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
DNode *dpush_front(DNode *head, int v) {
    DNode *p = malloc(sizeof(DNode));
    p->val = v; p->prev = NULL; p->next = head;
    if (head) head->prev = p;
    return p;
}
```

**写法 C**
```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判 nullptr/空容器；头尾节点更新要同步。
// 判断条件：循环退出条件要明确，删除节点后不要再访问已释放对象。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
void ddelete(DNode **head, DNode *p) {
    if (p->prev) p->prev->next = p->next;
    else         *head = p->next;
    if (p->next) p->next->prev = p->prev;
    free(p);
}
```

**写法 B**
```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
// 用了 dummy 之后，p->prev 永远不为 NULL（最坏也指向 dummy），不再需要特判
void ddelete(DNode *p) {
    p->prev->next = p->next;
    if (p->next) p->next->prev = p->prev;
    free(p);
}
```

**C++ class 版**
```cpp
// 边界条件：先判 nullptr/空容器；头尾节点更新要同步。
// 判断条件：循环退出条件要明确，删除节点后不要再访问已释放对象。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
// prev 始终是 current 的前驱，每步都要同步移动
Node *nxt = current->next;
prev->next = nxt;
free(current);
current = nxt;
```

### 释放

```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
void free_circular(Node *head) {
    if (!head) return;
    Node *cur = head;
    do {
        Node *nxt = cur->next;
        free(cur); cur = nxt;
    } while (cur != head);   // ⚠️ 不能用 while(cur != NULL)，会死循环
}
```

### 单节点环删除特判（补充）

```c
// 边界条件：空环直接返回；单节点环删除后应返回 NULL。
// 判断条件：head->next == head 时，说明环里只有一个节点。
Node *delete_one_in_circular(Node *head, Node *target) {
    if (!head || !target) return head;
    if (head == target && head->next == head) {
        free(head);
        return NULL;
    }
    return head;
}
```

---

## 4. 双向循环队列（FIFO）

入队 = 头插，出队 = 删尾

**C 写法 B**
```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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
// 边界条件：先判 nullptr/空容器；头尾节点更新要同步。
// 判断条件：循环退出条件要明确，删除节点后不要再访问已释放对象。
#include <deque>
deque<int> q;
q.push_back(v);                        // 入队
int v = q.front(); q.pop_front();      // 出队
```

---

## 5. 约瑟夫环

### 环形链表解法（C）

```c
// 边界条件：先判空链表/空指针；涉及头结点插入或删除要单独处理。
// 判断条件：循环终止看 NULL（或回到 head）；改指针前先保存 next，避免断链。
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

## 6. 常见边界条件

### 错误处理约定（建议统一）

- `malloc/new` 失败：返回原链表或 `NULL`，不要继续改指针。
- 删除失败（目标不存在）：返回原链表，不报错也不崩溃。
- 查询失败：统一返回 `NULL`（或 C++ 返回 `nullptr`）。

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

### `cur != NULL` vs `cur->next != NULL` 什么时候用

- 用 `cur != NULL`：当你要访问的是当前节点成员（如 `cur->val`、`cur->next`）。
- 用 `cur->next != NULL`：当你要访问的是下一个节点成员（如 `cur->next->val`）。
- 删除常用写法：`while (cur->next != NULL && cur->next->val != x)`，因为目标通常是删 `cur->next`。

```c
// 边界条件：访问 cur->val 前必须保证 cur 非空。
// 判断条件：只访问当前节点成员时，用 cur != NULL。
while (cur != NULL) {
    printf("%d ", cur->val);
    cur = cur->next;
}

// 边界条件：访问 cur->next->val 前必须保证 cur->next 非空。
// 判断条件：要看“下一个节点”时，用 cur->next != NULL。
while (cur->next != NULL && cur->next->val != x) {
    cur = cur->next;
}
```

### 快慢指针中点定义对照（补充）

| 目标中点 | 循环条件 | 偶数长度示例 `[1,2,3,4]` 返回 |
|---|---|---|
| 左中点 | `while (fast->next && fast->next->next)` | `2` |
| 右中点 | `while (fast && fast->next)` | `3` |

---

## 7. 操作复杂度速查

| 操作 | 单链表 | 双向链表 | 环形链表 |
|---|---|---|---|
| 头插 | O(1) | O(1) | O(1) |
| 尾插 | O(n)，带 tail 则 O(1) | O(n)，带 tail 则 O(1) | O(n)，带 tail 则 O(1) |
| 删除（已知节点） | O(n) 找前驱 | **O(1)** | O(n) 找前驱 |
| 查找 | O(n) | O(n) | O(n) |
| 遍历 | O(n) | O(n) | O(n)，注意终止条件 |

---

## 8. 最小测试用例清单（建议）

- 空链表：插入/删除/查找/反转都不崩溃。
- 单节点：删头、删尾、删不存在值、反转后不变。
- 双节点：删除第一个/第二个后指针仍正确。
- 删除不存在值：链表结构不应变化。
- 环形链表：1 节点环和多节点环都能正确遍历与释放。
- 快慢指针：奇偶长度都验证一次中点定义是否符合预期。
