/* 
Viết chương trình đọc vào một đồ thị có hướng không chu trình G. Áp dụng thuật toán sắp xếp topo theo phương pháp duyệt theo chiều rộng để sắp xếp các đỉnh của G. In các đỉnh ra màn hình theo thứ tự topo.
Đầu vào (Input)
  Dữ liệu đầu vào được nhập từ bàn phím với định dạng:
  Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.
  m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).
Đầu ra (Output)
  In các đỉnh ra màn hình theo thứ tự topo. In các đỉnh trên một dòng, cách nhau 1 khoảng trắng. 
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

/*Queue*/
/* Khai báo CTDL Queue*/
#define MAX_SIZE 100
typedef int ElementType;
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
int empty_queue(Queue *pQ) {
    return pQ->front > pQ->rear;
}

void topo_sort(Graph *pG, List *pL){
    int d[MAX_N];

    //tinh bac vao cua u
    for(int u = 1; u <= pG->n; u++) {
        d[u] = 0;
        for(int x = 1; x <=pG->n; x++)
            if(pG->A[x][u] != 0)
                d[u]++;
    }

Queue Q;

make_null_queue(&Q);

//dua cac dinh co d[u] = 0 vao hang doi
for(int u = 1; u <=pG->n; u++)
    if(d[u] == 0)
        enqueue(&Q, u);

make_null_list(pL);

//vong lap chinh, lap den khi Q rong thi dung
while (!empty_queue(&Q)) {
    int u = front(&Q);
    dequeue(&Q);
    push_back(pL, u);

    //xoa dinh u <=> giam bac vao cua cac dinh ke v cua u
    for(int v = 1; v <= pG-> n; v++)
    if(pG->A[u][v] != 0){
        d[v]--;
            if(d[v] == 0)
                enqueue(&Q, v);
    }

    }
}

int main(){
    Graph G;
    int n, m;
    scanf("%d%d", &n, &m);

    init_graph(&G, n);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(&G, u, v);
    }

    List L;
    topo_sort(&G, &L);

    for(int i = 1; i <= count_list(&L); i++) {
        printf("%d ", element_at(&L, i));
    }

    return 0;
}
