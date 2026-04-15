#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    // TODO: 在这里添加你的代码
    if (n <= 0)
    {
        return NULL;
    }
    Node *head= (Node*) malloc(sizeof(Node));
    if(head == NULL) {
        return NULL;
    }
    head->id = 1;
    head->next=NULL;
    Node *tail = head;
    Node *p = head;
    for(int i = 1; i < n; i++){
        p = (Node*) malloc(sizeof(Node));
        if(p == NULL) {
            return NULL;
        }
        p->id = i + 1;
        tail->next = p;
        tail = p;
    }

    tail->next = head;
    return head;
}

void free_list(Node* head) {
    if (head == NULL) return;
    Node *cur = head;
    do {
        Node *next = cur->next;
        free(cur);
        cur = next;
    } while (cur != head);
}
