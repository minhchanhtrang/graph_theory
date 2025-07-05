/*
Viết chương trình đọc vào một đơn đồ thị có hướng không chu trình, xếp hạng các đỉnh và in hạng của các đỉnh ra màn hình.
Đầu vào (Input)
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:
  -Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đỉnh và số cung.
  -m dòng tiếp theo mỗi dòng chứa 2 số nguyên u, v mô tả cung (u, v).
Đầu ra (Output)
In ra màn hình hạng của các đỉnh theo thứ tự của đỉnh, mỗi đỉnh trên 1 dòng theo mẫu:

r[1] = abc
r[2] = xyz
...

Xem thêm ví dụ bên dưới. Trong ví dụ đầu tiên ta có: hạng của 1 = 0, hạng của 2 = 2 và hạng của 3 = 1.
For example:

Input	    Result
3 2      r[1] = 0
1 3      r[2] = 2
3 2      r[3] = 1
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
//copy các phần tử của pS2 vào pS1
void copy_list(List *pS1, List *pS2) {
    make_null_list(pS1); // làm rỗng pS1 trước
    for (int i = 0; i < pS2->size; i++) {
        push_back(pS1, pS2->data[i]);
    }
}

// Lưu hạng của các đỉnh 
int r[MAX_N];
//Hàm xếp hạng
void rank (Graph *pG) {
    int d[MAX_N];//Lưu bậc các đỉnh

    //Tính bậc vào của các đỉnh d[u]
    for (int u = 1; u <= pG->n; u++) {
        d[u] = 0;
            for(int x = 1; x <=pG->n; x++)
                if (pG->A [x][u] !=0 )
                    d[u]++;
}

//Sử dụng 2 danh sách S1, S2
List S1, S2;

//Tìm gốc, đưa vào S1 
make_null_list(&S1);
for (int u = 1; u <= pG->n; u++)
    if (d[u] == 0)
        push_back(&S1, u);
        
//Vòng Lặp chính, Lặp đến khi S1 rỗng thì dừng
int k = 0;  //hạng tính từ 0. Tùy theo bài toán có thể cho k = 1
while (S1.size > 0) {
 make_null_list(&S2);
  for (int i = 1; i <= S1.size; i++) {
   int u = element_at(&S1, i); //Lấy các gốc u trong S1 ra
   r[u] = k; //Xếp hạng cho u

//Xoá đỉnh u <=> giảm bậc vào của các đỉnh kề v của u
for (int v = 1; v <= pG->n; v++)
if (pG->A[u][v] != 0) {
    d[v]--;
    if (d[v] == 0)
        push_back(&S2, v);
        }
    }
copy_list(&S1, &S2) ; //Copy S2 vào S1
k++; // Tăng hạng kế tiếp cho các gốc mới
    }
}
int main() {
    Graph G;
    int n, m;
    scanf("%d %d", &n, &m);
    init_graph(&G, n);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(&G, u, v);
    }

    rank(&G); // Gọi hàm xếp hạng

    for (int u = 1; u <= G.n; u++) {
        printf("r[%d] = %d\n", u, r[u]);
    }

    return 0;
}


