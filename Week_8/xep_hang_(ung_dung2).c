/* Đề bài:
Trong một giải đấu bóng đá gồm n đội bóng, đánh số từ 1 đến n. Mỗi trận đấu có hai đội thi đấu với nhau cho đến khi phân biệt thắng thua (ví dụ: hiệp phụ, đá luân lưu).
Sau khi giải đấu kết thúc, ban tổ chức muốn xếp hạng các đội theo quy tắc sau:
-Hạng được tính từ 1, 2, 3, ...
-Đội không thua trận nào xếp hạng 1
-Nếu đội A đá thắng đội B thì hạng của đội A nhỏ hơn hạng của đội B.
-Nếu một đội có thể nhận nhiều hạng khác nhau thì chọn hạng nhỏ nhất.

Hoặc bạn cũng có thể sử dụng định nghĩa sau:
Hạng(v) = max {Hạng(u) } + 1
với u là đội thắng v.
Hãy giúp ban tổ chức viết chương trình xếp hạng cho các đội. Giả sử không xảy ra trường hợp A thắng B, B thắng C ,..., Z thắng A.

Đầu vào (Input):
Dữ liệu đầu vào được nhập từ bàn phím với định dạng:
-Dòng đầu tiên chứa 2 số nguyên n và m, tương ứng là số đội và số trận đấu.
-m dòng tiếp theo mỗi dòng chứa 2 số nguyên u v mô tả kết quả trận đấu: u thắng, v thua.

Đầu ra (Output):
- In ra màn hình hạng của các đội bóng theo số thứ tự của đội trên cùng 1 dòng, mỗi đội cách nhau 1 khoảng trắng.
<Hạng đội 1> <Hạng đội 2> ... <Hạng đội n>
Xem thêm ví dụ bên dưới. Trong ví dụ đầu tiên ta có: hạng của 1 = 1, hạng của 2 = 3 và hạng của 3 = 2.
Trong ví dụ 2: đội 2 có thể nhận hạng 2 hoặc 3 nên xếp hạng 2, tương tự như thế cho đội 4.
For example:
Input    | 	  Result
----------------------------
3 2      |    1 3 2
1 3      | 
3 2      |
----------------------------
7 10     |   1 2 4 2 3 3 5
1 2      |
1 3      |
1 4      |
2 3      |
2 6      |
3 7      |
4 5      |
5 3      |
5 7      |
6 7      |
---------------------------
*/

/*CODE*/
#include <stdio.h>

#define MAX_N 1005

typedef struct {
    int data[MAX_N];
    int size;
} List;

void make_null_list(List *L) {
    L->size = 0;
}

void push_back(List *L, int x) {
    L->data[L->size++] = x;
}

int element_at(List *L, int i) {
    return L->data[i];
}

int n, m;
List adj[MAX_N];      // Danh sách kề: adj[u] chứa các đỉnh v sao cho u thắng v
int in_deg[MAX_N];    // Bậc vào của mỗi đỉnh
int rank[MAX_N];      // rank[i] là hạng của đội i (bắt đầu từ 1)

void topological_sort() {
    List queue;
    make_null_list(&queue);

    // Đội không bị ai thắng sẽ có bậc vào = 0 -> hạng = 1
    for (int i = 1; i <= n; i++) {
        rank[i] = 1;
        if (in_deg[i] == 0)
            push_back(&queue, i);
    }

    // Duyệt theo topo để cập nhật rank
    for (int i = 0; i < queue.size; i++) {
        int u = element_at(&queue, i);
        for (int j = 0; j < adj[u].size; j++) {
            int v = adj[u].data[j]; // u thắng v
            if (rank[v] < rank[u] + 1)
                rank[v] = rank[u] + 1;
            in_deg[v]--;
            if (in_deg[v] == 0)
                push_back(&queue, v);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    // Khởi tạo danh sách kề và bậc vào
    for (int i = 1; i <= n; i++) {
        make_null_list(&adj[i]);
        in_deg[i] = 0;
    }

    // Đọc các cạnh: u thắng v → có cạnh từ u → v
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        push_back(&adj[u], v);
        in_deg[v]++;
    }

    // Gọi hàm sắp xếp và tính hạng
    topological_sort();

    // In kết quả
    for (int i = 1; i <= n; i++) {
        printf("%d ", rank[i]);
    }

    return 0;
}



