#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }
    // TODO: 在这里添加你的代码

    char buf[256];
    strcpy(buf, cmd + 2);

    char *token = strtok(buf, "/");
    *old_str = (char*)malloc(strlen(token) + 1);
    strcpy(*old_str, token);

    token = strtok(NULL, "/");
    *new_str = (char*)malloc(strlen(token) + 1);
    strcpy(*new_str, token);
    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // TODO: 在这里添加你的代码
    char *pos;
    char buf[256];

    if( (pos = strstr(str, old)) != NULL) {
        size_t prefix = pos - str;
        strncpy(buf, str, prefix);
        strcpy(buf + prefix, new);
        strcpy(buf + prefix + strlen(new), pos + strlen(old));
        strcpy(str, buf);
    }

}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
