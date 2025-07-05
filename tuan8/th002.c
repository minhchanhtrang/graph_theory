/*
Viết chương trình đọc vào một đồ thị có hướng không chu trình G, in các đỉnh của G ra màn hình theo thứ tự topo. Nếu có nhiều thứ tự topo, in một thứ tự bất kỳ.
Đầu vào (Input)
  Dữ liệu đầu vào được nhập từ bàn phím với định dạng:
    -Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.
    -m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).
Đầu ra (Output)
  In các đỉnh ra màn hình theo thứ tự topo. In các đỉnh trên một dòng, cách nhau 1 khoảng trắng.
Gợi ý
Ngoài giải thuật sắp xếp topo dựa trên phương pháp duyệt theo chiều rộng, ta cũng có thể sắp xếp topo dựa trên duyệt theo chiều sâu.
void dfs(G, u, L) {
    mark[u] = 1;
    for (v là kề của u)
        if (mark[v] == 0)
            dfs(G, v, L);
    push_back(L, u);
}
Khởi tạo mark[u] = 0 với mọi u = 1,n
for (u = 1; u <= n; u++)
    if (mark[u] == 0)
        dfs(G, u, L);
In ngược các phần tử của L
*/

#include <stdio.h>

#define MAX_N 100
typedef struct{
    int n, m;
    int A[MAX_N][MAX_N];
} Graph;

void init_graph(Graph *pG, int n) {
    pG->n=n;
    pG->m=0;
    
    for(int u=1; u <=n; u++)
        for(int v=1; v<=n; v++)
            pG->A[u][v] = 0;
}

void add_edge(Graph *pG, int u, int v) {
    pG->A[u][v] +=1;
    pG->m++;
}

/*List*/
#define MAX_ELEMENTS 100
typedef int ElementType;
typedef struct {
    ElementType data[MAX_ELEMENTS];
    int size;
} List;

//Tạo danh sách rỗng
void make_null_list(List *pL) {
    pL->size = 0;
}

//Thêm một phần tử vào cuối danh sách
void push_back(List *pL, ElementType x) {
    pL->data[pL->size] = x;
    pL->size++;
}

//Lấy phần tử thứ i, phần tử bắt đầu có vị trí 1
ElementType element_at(List *pL, int i) {
    return pL->data[i-1];
}

//Trả về số phần tử của danh sách
int count_list(List *pL) {
    return pL->size;
}

int mark[MAX_N]; // đánh dấu các đỉnh đã duyệt

void dfs(Graph *pG, int u, List *pL) {
    mark[u] = 1;
    for (int v = 1; v <= pG->n; v++) {
        if (pG->A[u][v] != 0 && mark[v] == 0) {
            dfs(pG, v, pL);
        }
    }
    push_back(pL, u);
}

void topo_sort(Graph *pG, List *pL) {
    make_null_list(pL);
    for (int i = 1; i <= pG->n; i++) {
        mark[i] = 0;
    }

    for (int u = 1; u <= pG->n; u++) {
        if (mark[u] == 0)
            dfs(pG, u, pL);
    }
}
int main() {
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);

    init_graph(&G, n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    List L;
    topo_sort(&G, &L);

    // In ngược danh sách kết quả để được thứ tự topo
    for (int i = count_list(&L); i >= 1; i--) {
        printf("%d ", element_at(&L, i));
    }

    return 0;
}
