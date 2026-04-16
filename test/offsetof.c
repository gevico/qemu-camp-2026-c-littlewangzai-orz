#include <stdio.h>
#include <stddef.h>
struct Test {
    int  a;   // 偏移量 0（假设）
    char b;   // 偏移量 4（int 之后）
};

int main() {

    struct Test test;

    printf("Test 结构中的 a 偏移 = %ld 字节。\n", offsetof(struct Test, a));
    printf("Test 结构中的 b 偏移 = %ld 字节。\n", offsetof(struct Test, b));

    printf("Test 结构的地址 = %p \n", &test);
    printf("Test 结构 a的地址 = %p \n", &test.a);
    printf("Test 结构 b的地址 = %p \n", &test.b);

    return 0;
}