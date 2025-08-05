#include <stdio.h>

#define MAXN 100
#define oo 999999
#define NO_EDGE 0

typedef struct {
    int u, v, w;
} Edge;

typedef struct {
    int A[MAXN][MAXN]; // Ma trận kề (0/1)
    int W[MAXN][MAXN]; // Ma trận trọng số
    int n, m;
} Graph;

int pi[MAXN];
int p[MAXN];
int mark[MAXN];

// Hàm khởi tạo đồ thị
void init_graph(Graph *G, int n) {
    G->n = n;
    G->m = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            G->A[i][j] = NO_EDGE;
            G->W[i][j] = oo; // Khởi tạo trọng số vô cùng
        }
}

// Hàm thêm cạnh vào đồ thị
void add_edge(Graph *G, int u, int v, int w) {
    G->A[u][v] = 1;
    G->A[v][u] = 1;
    G->W[u][v] = w;
    G->W[v][u] = w;
    G->m++;
}

// Hàm Prim (bạn đã cung cấp)
int Prim(Graph *pG, Graph *pT, int s) {
    int i, u, v, x;

    for (u = 1; u <= pG->n; u++) {
        pi[u] = oo;
        p[u]  = -1;
        mark[u] = 0;
    }
    pi[s] = 0;

    for (i = 1; i < pG->n; i++) {
        int min_dist = oo;
        for (x = 1; x <= pG->n; x++)
            if (mark[x] == 0 && pi[x] < min_dist) {
                min_dist = pi[x];
                u = x;
            }
        mark[u] = 1;

        for (v = 1; v <= pG->n; v++)
            if (pG->A[u][v] != NO_EDGE)
                if (mark[v] == 0 && pi[v] > pG->W[u][v]) {
                    pi[v] = pG->W[u][v];
                    p[v]  = u;
                }
    }

    init_graph(pT, pG->n);
    int sum_w = 0;

    for (u = 1; u <= pG->n; u++) {
        if (p[u] != -1) {
            int w = pG->W[p[u]][u];
            add_edge(pT, p[u], u, w);
            sum_w += w;
        }
    }

    return sum_w;
}

// Danh sách cạnh cây khung nhỏ nhất để sắp xếp in
Edge mst_edges[MAXN];
int mst_size = 0;

void extract_edges(Graph *T) {
    mst_size = 0;
    for (int u = 1; u <= T->n; u++) {
        for (int v = u + 1; v <= T->n; v++) {
            if (T->A[u][v]) {
                mst_edges[mst_size].u = u;
                mst_edges[mst_size].v = v;
                mst_edges[mst_size].w = T->W[u][v];
                mst_size++;
            }
        }
    }
}

void swap(Edge *a, Edge *b) {
    Edge t = *a; *a = *b; *b = t;
}

void sort_edges() {
    for (int i = 0; i < mst_size - 1; i++) {
        for (int j = i + 1; j < mst_size; j++) {
            if (mst_edges[i].u > mst_edges[j].u ||
               (mst_edges[i].u == mst_edges[j].u && mst_edges[i].v > mst_edges[j].v)) {
                swap(&mst_edges[i], &mst_edges[j]);
            }
        }
    }
}

int main() {
    Graph G, T;
    int n, m;
    scanf("%d%d", &n, &m);
    init_graph(&G, n);
    G.m = m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_edge(&G, u, v, w);
    }

    int total_weight = Prim(&G, &T, 1); // Tìm MST từ đỉnh 1
    extract_edges(&T);
    sort_edges();

    printf("%d\n", total_weight);
    for (int i = 0; i < mst_size; i++) {
        printf("%d %d %d\n", mst_edges[i].u, mst_edges[i].v, mst_edges[i].w);
    }

    return 0;
}
