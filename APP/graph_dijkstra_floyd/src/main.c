/*
 * @Description:
 * @FilePath: /graph_dijkstra_floyd/src/main.c
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-14 00:41:55
 * @LastEditTime: 2020-09-20 18:49:58
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */

#include <stdio.h>
#include "graph_dijkstra_floyd.h"

int main(int argc, char const *argv[])
{
    // 示例图 (邻接矩阵表示)
    int graph[MAX_VERTEX][MAX_VERTEX] = {
        {0, 4, INF, 2, INF},
        {4, 0, 3, 1, INF},
        {INF, 3, 0, 1, 5},
        {2, 1, 1, 0, 7},
        {INF, INF, 5, 7, 0}};
    int vertex_num = 5;
    int dist[MAX_VERTEX];

    // 计算从顶点0到其他顶点的最短路径
    dijkstra(graph, vertex_num, 0, dist);

    // 打印结果
    printf("Vertex\tDistance\n");
    for (int i = 0; i < vertex_num; i++) {
        if (dist[i] == INF) {
            printf("%d\tUnreachable\n", i);
        } else {
            printf("%d\t%d\n", i, dist[i]);
        }
    }

    return 0;
}
