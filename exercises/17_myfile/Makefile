CC = gcc
CFLAGS = -Wall -g -O2 -fPIE

TARGET := 17_myfile
OBJ_FILE := 17_myfile.o
SRCS := 17_myfile.c

filepath_OBJ := ./17_myfile.o
filepath_EXEC := ./17_myfile

all: $(filepath_EXEC)  # 最终生成指定路径的可执行文件

# 编译生成目标文件（.o）
$(filepath_OBJ): $(SRCS)
	$(CC) $(CFLAGS) -c $< -o $@
# 	# -c 只编译不链接，生成.o文件

# 链接生成可执行文件
$(filepath_EXEC): $(filepath_OBJ)
	$(CC) $(CFLAGS) $< -o $@
# 	# 链接.o文件生成可执行文件

clean:
	rm -f $(filepath_EXEC) $(filepath_OBJ)
# 	清理指定的文件

.PHONY: all clean