#include <stdio.h>
#include <stdbool.h>

#define MAX_PEOPLE 50

typedef struct {
    int id;
} People;

typedef struct {
    People data[MAX_PEOPLE];
    int head;
    int tail;
    int count;
} Queue;

int main() {
    Queue q;
    int total_people=50;
    int report_interval=5;

    // TODO: 在这里添加你的代码
    // 初始化循环队列状态
    q.head = 0;
    q.tail = 0;
    q.count = 0;

    // 1~50 号按顺序入队
    for (int id = 1; id <= total_people; id++) {
        q.data[q.tail].id = id;
        q.tail = (q.tail + 1) % MAX_PEOPLE;
        q.count++;
    }

    People p;
    while(q.count > 1) {
        // 前 report_interval-1 个人仅轮转：出队后立刻入队
        for(int i = 0; i < report_interval - 1; i++) {
            p = q.data[q.head];
            q.head = (q.head + 1) % MAX_PEOPLE;
            q.count = q.count - 1;

            q.data[q.tail] = p;
            q.tail = (q.tail + 1) % MAX_PEOPLE;
            q.count = q.count + 1;
        }

        // 第 report_interval 个人淘汰：出队且不再入队
        p = q.data[q.head];
        q.head = (q.head + 1) % MAX_PEOPLE;
        q.count = q.count - 1;

        printf("淘汰: %d\n", p.id);    
    }

    printf("最后剩下的人是: %d\n", q.data[q.head].id);

    return 0;
}