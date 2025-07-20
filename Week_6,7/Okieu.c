#include <stdio.h>
#define MAX 100
#define oo 1000000000

int n, m;
int W[MAX][MAX];
int pi[MAX];
int visited[MAX];

void MooreDijkstra(int start) {
    for (int i = 1; i <= n; i++) {
        pi[i] = oo;
        visited[i] = 0;
    }

    pi[start] = 0;

    for (int i = 1; i <= n; i++) {
        int u = -1, min_dist = oo;
        for (int j = 1; j <= n; j++) {
            if (!visited[j] && pi[j] < min_dist) {
                min_dist = pi[j];
                u = j;
            }
        }

        if (u == -1) break;

        visited[u] = 1;

        for (int v = 1; v <= n; v++) {
            if (W[u][v] > 0 && !visited[v]) {
                if (pi[u] + W[u][v] < pi[v]) {
                    pi[v] = pi[u] + W[u][v];
                }
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);

    // Khởi tạo ma trận kề
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            W[i][j] = 0;

    // Đọc dữ liệu các cạnh
    for (int i = 0; i < m; i++) {
        int u, v, q;
        scanf("%d%d%d", &u, &v, &q);
        W[u][v] = q;
        W[v][u] = q; // vì đồ thị vô hướng
    }

    MooreDijkstra(1);

    // In kết quả
    printf("%d\n", pi[n]);
    return 0;
}
