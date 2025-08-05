// vo huong don, BFS
#include <stdio.h>

/* Khai báo CTDL Graph*/
#define MAX_N 100
typedef struct {
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1 ; u <= n; u++)
        for (int v = 1 ; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] += 1;
    if (u != v)
        pG->A[v][u] += 1;
    
    pG->m++;
}

int adjacent(Graph *pG, int u, int v) {
    return pG->A[u][v] > 0;
}

/* Khai báo CTDL Queue */

#define MAX_SIZE 100
typedef struct {
    int u, p;
} ElementType;

typedef struct {
	ElementType data[MAX_SIZE];
	int front, rear;
} Queue;

/* Khởi tạo hàng đợi rỗng */
void make_null_queue(Queue *pQ) {
	pQ->front = 0;
	pQ->rear = -1;
}
/* Đưa phần tử u vào cuối hàng đợi */
void enqueue(Queue *pQ, ElementType u) {
	pQ->rear++;
	pQ->data[pQ->rear] = u;
}

/* Xem phần tử đầu hàng đợi */
ElementType front(Queue *pQ) {
	return pQ->data[pQ->front];
}

/* Xoá bỏ phần bỏ đầu hàng đợi */
void dequeue(Queue *pQ) {
	pQ->front++;
}

/* Kiểm tra hàng đợi rỗng */
int empty(Queue *pQ) {
	return pQ->front > pQ->rear;
}


//Biến hỗ trợ dùng để lưu trạng thái của đỉnh: đã duyệt/chưa duyệt
int mark[MAX_N];
int parent[MAX_N];

void BFS(Graph *pG, int s) {
	//1. Khai báo hàng đợi Q, khởi tạo rỗng
	Queue Q;
	make_null_queue(&Q);
	//2. Đưa s vào Q, bắt đầu duyệt từ đỉnh s */
	ElementType pair; 									
	pair.u = s; pair.p = -1; 								
	enqueue(&Q, pair); 									
	//3. Vòng lặp chính dùng để duyệt
	while (!empty(&Q)) {
		//3a. Lấy phần tử ở đầu hàng đợi
		ElementType pair = front(&Q); dequeue(&Q); 				
		int u = pair.u, p = pair.p; 							
		if (mark[u] != 0) 		//u đã duyệt rồi, bỏ qua
			continue;

		//printf("Duyet %d\n", u);	//Làm gì đó trên u
		mark[u] = 1; 			//Đánh dấu nó đã duyệt
		parent[u] = p; 			//Đánh dấu nó đã duyệt			

		//3b. Xét các đỉnh kề của u, đưa vào hàng đợi Q
		for (int v = 1; v <= pG->n; v++)
			if (adjacent(pG, u, v)) {
				ElementType pair; 						
				pair.u = v; pair.p = u; 					
				enqueue(&Q, pair); 						
			}
	}
}



int main() {
	//1. Khai báo đồ thị G
	Graph G;
	//2. Đọc dữ liệu và dựng đồ thị
	int n, m, u, v;
	scanf("%d%d", &n, &m);
	init_graph(&G, n);
	for (int e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
	    add_edge(&G, u, v);
	}

	//3. Khởi tạo mảng mark[u] = 0, với mọi u = 1, 2, ..., n
	for (int u = 1; u <= G.n; u++) {
		mark[u] = 0;
	    parent[u] = -1;
	}

	//4. Gọi hàm DFS
	for (int u = 1; u <= G.n; u++)
        if (mark[u] == 0)
            BFS(&G, u);
	

    for (int u = 1; u <= G.n; u++)
        printf("%d %d\n", u, parent[u]);

    
    return 0;
}

