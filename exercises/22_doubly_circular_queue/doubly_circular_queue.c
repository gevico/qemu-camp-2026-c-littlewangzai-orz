#include "doubly_circular_queue.h"

#include <stdlib.h>

// 头尾哨兵
static struct node tailsentinel;
static struct node headsentinel = {0, NULL, &tailsentinel};
static struct node tailsentinel = {0, &headsentinel, NULL};

static link head = &headsentinel;
static link tail = &tailsentinel;

link make_node(int data) {
    // TODO: 在这里添加你的代码
    link new_node = (link) malloc(sizeof(struct node));
    if(new_node == NULL) {
        return NULL;
    }
    new_node->data = data;
    new_node->prev = NULL;
    new_node->next =  NULL;
    
    return new_node;
}

void free_node(link p) {
    // TODO: 在这里添加你的代码
    if(p != NULL && p != head && p != tail)
        free(p);
}

link search(int key) {
    // TODO: 在这里添加你的代码
    link cur = head->next;
    while(cur!= tail) {
        if(cur->data == key) {
            return cur;
        }
        else 
            cur = cur->next;
    }
    return NULL;
}

void insert(link p) {
    // TODO: 在这里添加你的代码
    if(p) {
        p->next = head->next;
        p->prev = head;
        p->next->prev = p;
        head->next = p;
    }
}

void delete(link p) {
    // TODO: 在这里添加你的代码
    if(p != NULL && p != head && p != tail) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }

}

void traverse(void (*visit)(link)) {
    // TODO: 在这里添加你的代码
    link cur = head->next;
    while(cur != tail) {
        if(visit) 
            visit(cur);
        cur = cur->next;
    }
}

void destroy(void) {
    // TODO: 在这里添加你的代码
    link cur = head->next;
    while(cur != tail) {
        link next = cur->next;
        free(cur);
        cur = next;
    }
    head->next = tail;
    tail->prev = head;
}
