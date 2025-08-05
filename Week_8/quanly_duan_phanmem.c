#include <stdio.h>

#define MAX_N 100
typedef struct {
	int n, m;
	int A[MAX_N][MAX_N];
} Graph;


void init_graph(Graph *pG, int n) {
    pG->n = n;
    pG->m = 0;
    for (int u = 1; u <= n; u++)
        for (int v = 1; v <= n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] += 1;
}


typedef struct {
    int data[MAX_N];
    int size;
} List;

void make_null_list(List *pL) {
    pL->size = 0;
}

void push_back(List *pL, int x) {
    pL->data[pL->size++] = x;
}

int element_at(List *pL, int i) {
    return pL->data[i-1];
}

void copy_list(List *pS1, List *pS2) {
    make_null_list(pS1);
    for (int i = 1; i <= pS2->size; i++)
        push_back(pS1, element_at(pS2, i));
}

typedef struct {
    int data[MAX_N];
    int front, rear;
} Queue;

void make_null_queue(Queue *pQ) {
    pQ->front = -1;
    pQ->rear  = -1;
}

void enqueue(Queue *pQ, int x) {
    pQ->rear = (pQ->rear + 1)%MAX_N;
    pQ->data[pQ->rear] = x;
    if (pQ->front == -1)
        pQ->front = 0;
}

int empty_queue(Queue *pQ) {
    return pQ->rear == -1;
}

int front(Queue *pQ) {
    return pQ->data[pQ->front];
}

void dequeue(Queue *pQ) {
    if (pQ->front == pQ->rear)
        make_null_queue(pQ);
    else
        pQ->front = (pQ->front + 1)%MAX_N;
}

void topo_sort(Graph *pG, List *pL) {
	int d[MAX_N];
	//Tính bậc vào của u
	for (int u = 1; u <= pG->n; u++) {
		d[u] = 0;
		for (int x = 1; x <= pG->n; x++)
			if (pG->A[x][u] != 0)
				d[u]++;
	}

	Queue Q;
	//Làm rỗng hàng đợi Q
	make_null_queue(&Q);
	//Đưa các đỉnh có d[u] = 0 vào hàng đợi
	for (int u = 1; u <= pG->n; u++)
		if (d[u] == 0)
			enqueue(&Q, u);
	//Làm rỗng danh sách pL
	make_null_list(pL);
	//Vòng lặp chính, lặp đến khi Q rỗng thì dừng
	while (!empty_queue(&Q)) {
		int u = front(&Q);
		dequeue(&Q);
		push_back(pL, u);
		//Xoá đỉnh u <=> giảm bậc vào của các đỉnh kề v của u
		for (int v = 1; v <= pG->n; v++)
			if (pG->A[u][v] != 0) {
				d[v]--;
				if (d[v] == 0)
					enqueue(&Q, v);
			}
	}
}

#define oo 9999999

int max(int a, int b) {
    return a > b ? a: b;
}

int min(int a, int b) {
    return a < b ? a: b;
}

int d[MAX_N];
//Đọc danh sách các công việc và tạo đồ thị
int main() {
	Graph G;
	int n, u, x, v, j;
	//1. Đọc đồ thị
	scanf("%d", &n);
	//1a. Tạo đồ thị có n + 2 đỉnh (alpha = n+1 và beta = n + 2)
	init_graph(&G, n+2);
	int alpha = n + 1, beta = n + 2;
	d[alpha] = 0; //thời gian hoàn thành alpha là 0.
	//1b. Đọc danh sách các công việc
	for (u = 1; u <= n; u++) {
		scanf("%d", &d[u]); 	//Thời gian hoàn thành công việc u
	}

    int m, e;
	scanf("%d", &m);
    for (e = 0; e < m; e++) {
	    scanf("%d%d", &u, &v);
		add_edge(&G, u, v);
	}

	//2. Thêm cung nối alpha với các đỉnh có bậc vào = 0
	for (u = 1; u <= n; u++) {
		int deg_neg = 0;
		for (x = 1; x <= n; x++)
			if (G.A[x][u] > 0)
				deg_neg++;              //deg_neg là bậc vào của u
		
		if (deg_neg == 0)
			add_edge(&G, alpha, u);
	}
	//3. Thêm cung nối các đỉnh có bậc ra = 0 vào beta
	for (u = 1; u <= n; u++) {
		int deg_pos = 0;
		for (v = 1; v <= n; v++)
			if (G.A[u][v] > 0)
                deg_pos++;        //deg_neg là bậc ra của u
		
		if (deg_pos == 0)
			add_edge(&G, u, beta);
	}
	
	List L;
	topo_sort(&G, &L);
	//5. Tính t[u]
	int t[MAX_N];
	t[alpha] = 0;
	//alpha chắc chắn nằm đầu danh sách, các đỉnh còn lại đi từ 2 đến L.size
	for (j = 2; j <= L.size; j++) { 
		int u = element_at(&L, j);
		t[u] = -oo; //vô cùng bé, ví dụ: -999999
		for (x = 1; x <= G.n; x++)
			if (G.A[x][u] > 0)
				t[u] = max(t[u], t[x] + d[x]);
	}
	//6. tính T[u]
	int T[MAX_N];
	T[beta] = t[beta];
	//beta chắc chắn nằm cuối danh sách, đi ngược lại từ L.size – 1 về 1
	for (j = L.size - 1; j >= 1; j--) {
		int u = element_at(&L, j);
		T[u] = +oo; //vô cùng lớn, ví dụ: 999999
		for (v = 1; v <= G.n; v++)
			if (G.A[u][v] > 0)
				T[u] = min(T[u], T[v] - d[u]);
	}
	//7. In kết quả: in t[u] và T[u] ra màn hình
    printf("%d\n", t[beta]);

    return 0;
}

