#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

typedef struct {
	int row;
	int col;
} Pos;

Pos stack[MAX_ROW * MAX_COL];
int top = -1;

int visited[MAX_ROW][MAX_COL] = {0};
int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int main(void)
{
	// TODO: 在这里添加你的代码
	visited[0][0] = 1;
	stack[++top] = (Pos){0, 0};
	int found = 0;
	while(top!=-1) 
	{
		if(stack[top].row == MAX_ROW - 1 && stack[top].col == MAX_COL - 1) {
			//找到路径
			for (int i = top; i >= 0; i--) {
    			printf("(%d, %d)\n", stack[i].row, stack[i].col);
			}
			break;
		}

		found = 0;
		int row_cur = stack[top].row;
		int col_cur = stack[top].col;


		if( (row_cur - 1 >= 0) && (maze[row_cur - 1][col_cur] == 0) && (visited[row_cur - 1][col_cur] == 0)) {
			stack[++top] = (Pos){row_cur - 1, col_cur};
			found = 1;
			visited[row_cur - 1][col_cur] = 1;
		}
		else if( (col_cur + 1 < MAX_COL) && (maze[row_cur][col_cur + 1] == 0) && (visited[row_cur][col_cur + 1] == 0)) {
			stack[++top] = (Pos){row_cur, col_cur + 1};
			visited[row_cur][col_cur + 1] = 1;
			found = 1;
		}
		else if( (row_cur + 1 < MAX_ROW) && (maze[row_cur + 1][col_cur] == 0) && (visited[row_cur + 1][col_cur] == 0)) {
			stack[++top] = (Pos){row_cur + 1, col_cur};
			found = 1;
			visited[row_cur + 1][col_cur] = 1;
		}
		else if( (col_cur - 1 >= 0 ) && (maze[row_cur][col_cur - 1] == 0) && (visited[row_cur][col_cur-1] == 0)) {
			stack[++top] = (Pos){row_cur, col_cur - 1};
			found = 1;
			visited[row_cur][col_cur - 1] = 1;
		}

		if(!found) {
			top--;
		}
	}

	return 0;
}