//vo huong


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




//Biến hỗ trợ dùng để lưu trạng thái của đỉnh: đã duyệt/chưa duyệt
int mark[MAX_N];
int parent[MAX_N];

void DFS(Graph *pG, int u, int p) {								
	//1. Đánh dấu u đã duyệt
	//printf("Duyet %d\n", u);	//Làm gì đó trên u
	mark[u] = 1; 			//Đánh dấu nó đã duyệt
	parent[u] = p; 			//Cho cha của u là p				

	//2. Xét các đỉnh kề của u
	for (int v = 1; v <= pG->n; v++)
		if (adjacent(pG, u, v) && mark[v] == 0) //Nếu v chưa duyệt
			DFS(pG, v, u); 			    //gọi đệ quy duyệt nó	

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
            DFS(&G, u, -1);
	

    for (int u = 1; u <= G.n; u++)
        printf("%d %d\n", u, parent[u]);

    
    return 0;
}

