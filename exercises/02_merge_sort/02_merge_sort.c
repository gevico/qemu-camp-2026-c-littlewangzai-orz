#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int score;
} Student;

Student students[MAX_STUDENTS];
Student temp[MAX_STUDENTS];

void merge(int left, int mid, int right) {
    // 左右两个有序区间分别是 [left, mid] 和 [mid+1, right]
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Student left_arr[n1];
    Student right_arr[n2];

    for(int i = 0; i < n1; i++) {
        left_arr[i] = students[left + i];
    }

    for(int j = 0; j < n2; j++) {
        right_arr[j] = students[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    // 逐个比较两个子数组，按成绩从高到低写入 temp
    while(i < n1 && j < n2) {
        if(left_arr[i].score > right_arr[j].score) {
            temp[k] = left_arr[i];
            k++;
            i++;
        }
        else {
            temp[k] = right_arr[j];
            k++;
            j++;
        }
    }

    // 把尚未处理完的一侧直接追加到 temp
    while(i < n1) {
        temp[k] = left_arr[i];
        k++;
        i++;
    }

    while(j < n2) {
        temp[k] = right_arr[j];
        k++;
        j++;
    }

    // 将合并结果拷回原数组对应区间
    for(int p = left; p <= right; p++) {
        students[p] = temp[p];
    }
}

void merge_sort(int left, int right) {
    // 分治：先递归排好左右两半，再调用 merge 合并
    if( left < right) {
        int mid = left + (right - left) / 2;
        merge_sort(left, mid);
        merge_sort(mid + 1, right);
        merge(left, mid, right);
    }
}

int main(void) {
    FILE *file = fopen("02_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 02_students.txt\n");
        return 1;
    }

    int n;
    fscanf(file, "%d", &n);

    if (n <= 0 || n > MAX_STUDENTS) {
        printf("学生人数无效：%d\n", n);
        fclose(file);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        fscanf(file, "%s %d", students[i].name, &students[i].score);
    }
    fclose(file);

    merge_sort(0, n - 1);

    printf("\n归并排序后按成绩从高到低排序的学生名单：\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }

    return 0;
} 