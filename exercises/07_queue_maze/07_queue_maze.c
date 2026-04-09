#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

typedef struct {
	int row;
	int col;
} Pos;

Pos queue[MAX_ROW * MAX_COL];
Pos parent[MAX_ROW][MAX_COL];

int front = 0;
int rear = 0;


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

	//起点入队
	visited[0][0] = 1;
	queue[rear++] = (Pos) {0, 0};
	int found = 0;
	Pos cur;
	while(front != rear) {
		cur = queue[front++];

		if( cur.col == MAX_COL - 1 && cur.row == MAX_ROW - 1) {
			found = 1;
			break;
		}


		if( (cur.row - 1 >= 0) && (maze[cur.row - 1][cur.col] == 0) && (visited[cur.row - 1][cur.col] == 0)) {
			visited[cur.row - 1][cur.col] = 1;
			parent[cur.row - 1][cur.col] = cur;
			queue[rear++] = (Pos) {cur.row - 1, cur.col};
		}
		if( (cur.col + 1 < MAX_COL) && (maze[cur.row][cur.col + 1] == 0) && (visited[cur.row][cur.col + 1] == 0)) {
			visited[cur.row][cur.col + 1] = 1;
			parent[cur.row][cur.col + 1] = cur;
			queue[rear++] = (Pos) {cur.row, cur.col + 1};
		}
		if( (cur.row + 1 < MAX_ROW) && (maze[cur.row + 1][cur.col] == 0) && (visited[cur.row + 1][cur.col] == 0)) {
			visited[cur.row + 1][cur.col] = 1;
			parent[cur.row + 1][cur.col] = cur;
			queue[rear++] = (Pos) {cur.row + 1, cur.col};
		}
		if( (cur.col - 1 >= 0 ) && (maze[cur.row][cur.col - 1] == 0) && (visited[cur.row][cur.col-1] == 0)) {
			visited[cur.row][cur.col - 1] = 1;
			parent[cur.row][cur.col - 1] = cur;
			queue[rear++] = (Pos) {cur.row, cur.col - 1};
		}
	}

	Pos path[MAX_COL * MAX_ROW] = {(Pos) {0,0}};
	int length = 0;
	if(found) {
		while(cur.col != 0 || cur.row != 0) {
			path[length++] = cur;
			cur = parent[cur.row][cur.col]; 
		}
		path[length++] = (Pos) {0,0};
	} else {
		;
	}
	
	for(int i = 0; i < length; i++) {
		printf("(%d,%d)\n", path[i].row, path[i].col);
		
	}
	return 0;
}