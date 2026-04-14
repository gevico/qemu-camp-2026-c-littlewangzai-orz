#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 创建新节点
link make_node(unsigned char item) {
    link new_node = malloc(sizeof(struct node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->item = item;
    new_node->next = NULL;
    return new_node;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    link cur = head;
    while (cur != NULL) {
        if (cur->item == key) {
            return cur;
        }
        cur = cur->next;
    }

    return NULL;
}

// 在链表头部插入节点
void insert(link p) {
    if (p == NULL) {
        return;
    }
    p->next = head;
    head = p;
}

// 删除指定节点
void delete(link p) {
    if (head == NULL || p == NULL) {
        return;
    }
    link cur = head;
    if (p == head) {
        head = head->next;
        free_node(p);
        return;
    } else {
        while (cur != NULL && cur->next != NULL) {
            if (cur->next == p) {
                cur->next = cur->next->next;
                free_node(p);
                return;
            }
            cur = cur->next;
        }
    }
}

// 遍历链表
void traverse(void (*visit)(link)) {
    if (visit == NULL) {
        return;
    }
    link cur = head;
    while (cur != NULL) {
        visit(cur);
        cur = cur->next;
    }
}

// 销毁整个链表
void destroy(void) {
    free_list(head);
    head = NULL;
}

// 在链表头部推入节点
void push(link p) {
    if (p == NULL) {
        return;
    }
    p->next = head;
    head = p;
}

// 从链表头部弹出节点
link pop(void) {
    if (head == NULL) {
        return NULL;
    }

    link head_node = head;
    head = head->next;
    head_node->next = NULL;
    return head_node;
}

// 释放链表内存
void free_list(link list_head) {
    link cur = list_head;
    while (cur != NULL) {
        link next = cur->next;
        free_node(cur);
        cur = next;
    }
}
