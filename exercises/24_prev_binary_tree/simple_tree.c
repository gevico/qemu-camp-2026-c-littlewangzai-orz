#include "simple_tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, TreeNode *tree_node) {
    // TODO: 在这里添加你的代码
    QueueNode* new_node = (QueueNode*) malloc(sizeof(QueueNode));
    new_node->tree_node = tree_node;
    new_node->next = NULL;
    if(is_empty(q)) {
        q->front = new_node;
        q->rear = new_node;
    }
    else {
        q->rear->next = new_node;
        q->rear = new_node;
    }
}

TreeNode* dequeue(Queue *q) {
    // TODO: 在这里添加你的代码
    if(is_empty(q)){
        return NULL;
    }
    else {
        QueueNode* queuenode_tmp = q->front;
        TreeNode* tree_tmp = queuenode_tmp->tree_node;
        q->front = q->front->next;
        if (q->front == NULL) {
            q->rear = NULL;
        }
        free(queuenode_tmp);
        return tree_tmp;
    }

}

bool is_empty(Queue *q) {
    return q->front == NULL;
}

void free_queue(Queue *q) {
    while (!is_empty(q)) {
        dequeue(q);
    }
    free(q);
}

TreeNode* build_tree_by_level(int *level_order, int size) {
    // TODO: 在这里添加你的代码
    if (size <= 0 || level_order[0] == INT_MIN) {
        return NULL;
    }

    Queue* q = create_queue();
    TreeNode* root = (TreeNode*) malloc(sizeof(TreeNode));
    root->val = level_order[0];
    root->left = NULL;
    root->right = NULL;

    enqueue(q,root);

    int i = 1;
    while(!is_empty(q) && i < size) {
        TreeNode* parent = dequeue(q);

        if (i < size && level_order[i] != INT_MIN) {
            TreeNode *left_node = (TreeNode *)malloc(sizeof(TreeNode));
            left_node->val = level_order[i];
            left_node->left = NULL;
            left_node->right = NULL;

            parent->left = left_node;
            enqueue(q, left_node);
        } else {
            parent->left = NULL;
        }

        i++;

        if (i < size && level_order[i] != INT_MIN) {
            TreeNode *right_node = (TreeNode *)malloc(sizeof(TreeNode));
            right_node->val = level_order[i];
            right_node->left = NULL;
            right_node->right = NULL;

            parent->right = right_node;
            enqueue(q, right_node);
        } else {
            parent->right = NULL;
        }
        i++;
    }

    return root;
}

void preorder_traversal(TreeNode *root) {
    // TODO: 在这里添加你的代码
    if(root == NULL) {
        return;
    }
    else {
        printf("%d ", root->val);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void preorder_traversal_iterative(TreeNode *root) {
    // TODO: 在这里添加你的代码
    TreeNode* stack[1000];
    int top = -1;

    if(root == NULL) return ;

    stack[++top] = root;

    while(top != -1) {
        TreeNode* cur = stack[top--];
        printf("%d ", cur->val);
        if(cur->right != NULL) stack[++top] = cur->right;
        if(cur->left != NULL) stack[++top] = cur->left;
    }

}

void free_tree(TreeNode *root) {
    if (root == NULL) {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}
