#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[20];
    int score;
} Student;

void insertion_sort(Student students[], int n) {
    // 插入排序的思路：
    // 1. 把 students[0] 看成已经排好序的“有序区”
    // 2. 从 students[1] 开始，每次取无序区的第一个元素
    // 3. 把这个元素插入前面合适的位置，这样有序区就会不断扩大
    printf("%d \n", n);
    for (int i = 1; i < n; i++) {
        // key 表示当前要插入的分数，也就是“无序区的第一个分数”
        int key = students[i].score;
        // 把当前学生整体保存下来，最后要插回正确位置
        Student s_tmp = students[i];
        // j 从有序区的最后一个位置开始，向前寻找插入点
        int j = i - 1;
        // 如果前面的学生分数更低，就把它整体向后挪一位
        // 这样可以给当前学生空出一个插入位置
        while( j >= 0 && students[j].score < key) {
            students[j + 1] = students[j];
            j--;
        }
        // 循环结束后，j+1 就是当前学生应该插入的位置
        students[j+1] = s_tmp;
    }
}

int main(void) {
    FILE *file;
    Student students[50];
    int n = 0;
    
    // 打开文件（从命令行参数获取文件名）
    file = fopen("01_students.txt", "r");
    if (!file) {
        printf("错误：无法打开文件 01_students.txt\n");
        return 1;
    }
    
    // 从文件读取学生信息
    while (n < 50 && fscanf(file, "%s %d", students[n].name, &students[n].score) == 2) {
        n++;
    }
    fclose(file);
    
    if (n == 0) {
        printf("文件中没有学生信息\n");
        return 1;
    }
    
    insertion_sort(students, n);
    
    printf("\n按成绩从高到低排序后的学生信息:\n");
    for (int i = 0; i < n; i++) {
        printf("%s %d\n", students[i].name, students[i].score);
    }
    
    return 0;
}

