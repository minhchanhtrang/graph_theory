int adjacent(Graph *pG, int u, int v){
    int e;
    for(e=0; e<pG->m; e++)
        if((pG->edges[e].u==u && pG->edges[e].v==v) || (pG->edges[e].u==v && pG->edges[e].v==u))
            return 1;
    return 0;
}
