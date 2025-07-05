/*
Cô giáo Trang chuẩn bị kẹo để phát cho các bé mà cô đang giữ. Dĩ nhiên môi bé đều có một tên gọi rất dễ thương ví dụ: Mạnh Phát, Diễm Quỳnh, Đăng Khoa, ... 
 Tuy nhiên, để đơn giản vấn đề ta có thể giả sử các em được đánh số từ 1 đến n.
 Cô giáo muốn rằng tất cả các em đều phải có kẹo. Cô lại biết thêm rằng có một số bé có ý muốn hơn bạn mình một chút vì thế các em ấy muốn kẹo của mình nhiều hơn của bạn.
 
Hãy viết chương trình giúp cô tính xem mỗi em cần được chia ít nhất bao nhiêu kẹo và tổng số kẹo ít nhất mà cô phải chuẩn bị là bao nhiêu.

Đầu vào (Input):
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:
-Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số bé và số cặp bé mà trong đó có 1 bé muốn có kẹo hơn bạn mình.
-m dòng tiếp theo mỗi dòng chứa 2 số nguyên a, b nói rằng bé a muốn có kẹo nhiều hơn bé b.
Đầu ra (Output)
-In ra màn hình số kẹo ít nhất của từng em, mỗi em trên một dòng.
-Dòng cuối cùng in tổng số kẹo ít nhất mà cô giáo Trang cần phải chuẩn bị.
Xem thêm các ví dụ để hiểu thêm về đầu vào và đầu ra.
For example:

Input	    Result
3 2         3
1 3         1
3 2         2
            6
*/

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
    pG->A[u][v]++;
    pG->m++;
}

typedef int ElementType;
typedef struct {
    ElementType data[MAX_N];
    int size;
} List;

void make_null_list(List *pL) {
    pL->size = 0;
}

void push_back(List *pL, ElementType x) {
    pL->data[pL->size++] = x;
}

ElementType element_at(List *pL, int i) {
    return pL->data[i - 1];
}

void copy_list(List *pS1, List *pS2) {
    make_null_list(pS1);
    for (int i = 0; i < pS2->size; i++)
        push_back(pS1, pS2->data[i]);
}

int rank[MAX_N];

void assign_candies(Graph *pG) {
    int d[MAX_N];
    for (int u = 1; u <= pG->n; u++) {
        d[u] = 0;
        for (int x = 1; x <= pG->n; x++) {
            d[u] += pG->A[x][u]; // Tổng số cung vào u
        }
    }

    List S1, S2;
    make_null_list(&S1);

    for (int u = 1; u <= pG->n; u++)
        if (d[u] == 0)
            push_back(&S1, u);

    int k = 0;
    while (S1.size > 0) {
        make_null_list(&S2);
        for (int i = 1; i <= S1.size; i++) {
            int u = element_at(&S1, i);
            rank[u] = k;

            for (int v = 1; v <= pG->n; v++) {
                if (pG->A[u][v] != 0) {
                    d[v] -= pG->A[u][v];
                    if (d[v] == 0)
                        push_back(&S2, v);
                }
            }
        }
        copy_list(&S1, &S2);
        k++;
    }
}

int main() {
    Graph G;
    int n, m;
    scanf("%d %d", &n, &m);
    init_graph(&G, n);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(&G, b, a); 
    }

    assign_candies(&G);

    int total = 0;
    for (int u = 1; u <= n; u++) {
        int candies = rank[u] + 1;
        printf("%d\n", candies);
        total += candies;
    }

    printf("%d\n", total);
    return 0;
}
