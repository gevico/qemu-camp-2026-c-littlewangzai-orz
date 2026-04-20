#define _POSIX_C_SOURCE 200809L 
// -std=c11 下 strdup 不是标准 C11 函数（它是 POSIX 扩展），所以编译器把 strdup 的返回值当成 int，赋值给 char * 指针后，指针值就变成了一个无效的垃圾地址，之后访问 node->word 就段错误了
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1024  // 哈希表大小

// 哈希表节点结构
typedef struct HashNode {
    char *word;
    int count;
    struct HashNode *next;
} HashNode;

// 哈希表结构
typedef struct {
    HashNode **table;
    int size;
} HashTable;

// djb2哈希函数
unsigned long djb2_hash(const char *str) {
    // TODO: 在这里添加你的代码
    unsigned long hash = 5381;
    while(*str) {
        hash = hash * 33 + *str;
        str++;
    }
    return hash;
}

// 创建哈希表
HashTable *create_hash_table(int size) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->table = calloc(size, sizeof(HashNode *));
    ht->size = size;
    return ht;
}

// 向哈希表中插入单词
void hash_table_insert(HashTable *ht, const char *word) {
    unsigned long hash = djb2_hash(word) % ht->size;
    if ( !ht || !word) {
        return;
    }
    // TODO: 在这里添加你的代码
    HashNode *node = ht->table[hash];
    HashNode *cur = node;
    while(cur != NULL) {
        if(strcmp(cur->word, word) == 0) {
            cur->count++;
            return;
        }
        else 
            cur = cur->next;
    }
    HashNode *new_node = malloc(sizeof(HashNode));
    new_node->word = strdup(word);
    new_node->count = 1;
    new_node->next = node;
    ht->table[hash] = new_node;

}

// 从哈希表中获取所有单词及其计数
void get_all_words(HashTable *ht, HashNode **nodes, int *count) {
    // TODO: 在这里添加你的代码
    for(int i = 0; i < ht->size; i++) {
        HashNode *node = ht->table[i];
        while(node != NULL) {
            nodes[*count] = node;
            (*count)++;
            node = node->next;
        }
    }
}

// 比较函数用于排序
int compare_nodes(const void *a, const void *b) {
    HashNode *node_a = *(HashNode **)a;
    HashNode *node_b = *(HashNode **)b;
    
    // 先按计数降序，再按字母升序
    // TODO: 在这里添加你的代码
    if(node_a->count != node_b->count) {
        return node_b->count - node_a->count;
    }
    else {
        if(strcmp(node_a->word, node_b->word) > 0) 
            return 1;
        else if(strcmp(node_a->word, node_b->word) < 0) 
            return -1;
        else 
            return 0;
    }
}

// 释放哈希表内存
void free_hash_table(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        HashNode *node = ht->table[i];
        while (node != NULL) {
            HashNode *temp = node;
            node = node->next;
            free(temp->word);
            free(temp);
        }
    }
    free(ht->table);
    free(ht);
}

// 从字符串中获取下一个单词
char *get_next_word(const char **text) {
    // TODO: 在这里添加你的代码
    const char *p = *text;
    
    while(*p && !isalpha(*p)) p++;
    if(*p == '\0') return NULL;
    const char *start = p;
    while (*p && isalpha(*p)) p++;
    int len = p - start;

    char* word = malloc(len + 1);
    for (int i = 0; i < len; i++)
        word[i] = tolower((unsigned char)start[i]);
    word[len] = '\0';
    *text = p;
    return word;
    
}

int main(int argc, char *argv[]) {
    const char* file_path = "paper.txt";

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }

    HashTable *ht = create_hash_table(TABLE_SIZE);
    char buffer[4096];
    
    printf("正在读取文件: %s\n", file_path);
    
    // 从文件读取直到EOF
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        const char *ptr = buffer;
        char *word;
        
        while ((word = get_next_word(&ptr)) != NULL) {
            hash_table_insert(ht, word);
            free(word);
        }
    }
    
    fclose(file);
    
    // 收集所有单词节点
    HashNode **nodes = malloc(TABLE_SIZE * sizeof(HashNode *));
    int node_count = 0;
    get_all_words(ht, nodes, &node_count);
    
    // 排序
    qsort(nodes, node_count, sizeof(HashNode *), compare_nodes);
    
    // 输出结果
    printf("\n单词统计结果（按频率降序排列）:\n");
    printf("%-20s %s\n", "单词", "出现次数");
    printf("-------------------- ----------\n");
    for (int i = 0; i < node_count; i++) {
        printf("%s:%d\n", nodes[i]->word, nodes[i]->count);
    }
    
    // 释放内存
    free(nodes);
    free_hash_table(ht);
    
    return 0;
}