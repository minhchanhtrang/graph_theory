void add_edge(Graph *pG, int u, int v) { 
    for (int i = 0; i < pG->m; i++) {
        int x = pG->edges[i].u;
        int y = pG->edges[i].v;

        if ((x == u && y == v) || (x == v && y == u)) {
            return;
        }
    }
