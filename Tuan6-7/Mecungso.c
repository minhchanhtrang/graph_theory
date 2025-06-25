#include <stdio.h>
#include <limits.h>

#define MAX 100
#define oo 1000000000

typedef struct {
    int x, y;
} Point;

int M, N;
int maze[MAX][MAX];
int dist[MAX][MAX];
int visited[MAX][MAX];

// 4 hướng di chuyển: lên, xuống, trái, phải
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

// Kiểm tra ô có hợp lệ không
int is_valid(int x, int y) {
    return x >= 0 && x < M && y >= 0 && y < N;
}

// Hàm tìm đường đi ngắn nhất bằng Dijkstra trên lưới
int dijkstra() {
    // Khởi tạo khoảng cách
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++) {
            dist[i][j] = oo;
            visited[i][j] = 0;
        }

    dist[0][0] = 0;

    while (1) {
        int min_dist = oo;
        int ux = -1, uy = -1;

        // Tìm ô chưa xét có dist nhỏ nhất
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                if (!visited[i][j] && dist[i][j] < min_dist) {
                    min_dist = dist[i][j];
                    ux = i;
                    uy = j;
                }

        if (ux == -1) break; // Không còn ô để xét

        visited[ux][uy] = 1;

        // Duyệt các ô kề
        for (int dir = 0; dir < 4; dir++) {
            int vx = ux + dx[dir];
            int vy = uy + dy[dir];

            if (is_valid(vx, vy) && !visited[vx][vy]) {
                int new_dist = dist[ux][uy] + maze[vx][vy];
                if (new_dist < dist[vx][vy]) {
                    dist[vx][vy] = new_dist;
                }
            }
        }
    }

    return dist[M - 1][N - 1];
}

int main() {
    scanf("%d%d", &M, &N);
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &maze[i][j]);

    int result = dijkstra();
    printf("%d\n", result);
    return 0;
}
