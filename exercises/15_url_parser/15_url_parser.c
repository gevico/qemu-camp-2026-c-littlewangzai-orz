#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    // TODO: 在这里添加你的代码
    const char ch = '?';
    char *ptr;
    // 找到查询参数起点，URL 中 ? 后面是 key=value&key=value...
    ptr = strchr(url, ch);

    char buf[256];
    if(ptr != NULL) {
        ptr++;
        // strtok 会修改字符串，先拷贝到可写缓冲区
        strcpy(buf, ptr);

        // 先按 & 拆分每一个参数项
        char *token = strtok(buf, "&");
        char *eq = strchr(token, '=');
        if (eq != NULL) {
            // 把 key=value 在 = 处分成两个字符串
            *eq = '\0';
            char *key = token;
            char *value = eq + 1;
            printf("key = %s, value = %s\n", key, value);
        }

        while (token != NULL) {
            // printf("%s\n", token);
            token = strtok(NULL, "&");
            if (token != NULL) {
                eq = strchr(token, '=');
                if (eq != NULL) {
                    // 再次拆分并输出剩余参数
                    *eq = '\0';
                    char *key = token;
                    char *value = eq + 1;
                    printf("key = %s, value = %s\n", key, value);
                }
            }
        }
    } else {
        goto exit;
    }

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}