/*
 * @Description:
 * @FilePath: /graph_dijkstra_floyd/src/graph_dijkstra_floyd.c
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-14 00:41:55
 * @LastEditTime: 2020-09-20 14:56:43
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "graph_dijkstra_floyd.h"

/**
 * @brief           使用Dijkstra算法计算单源最短路径
 * @param[in]       graph       图的邻接矩阵
 * @param[in]       vertex_num  顶点数量
 * @param[in]       src         源点索引
 * @param[out]      dist        存储最短距离的数组
 * @retval          void
 * @version         1.0.0
 */
void dijkstra(int graph[MAX_VERTEX][MAX_VERTEX], int vertex_num, int src, int dist[MAX_VERTEX])
{
    bool visited[MAX_VERTEX] = {false};

    // 初始化距离数组
    for (int i = 0; i < vertex_num; i++) {
        dist[i] = graph[src][i];
    }
    dist[src]    = 0;
    visited[src] = true;

    // 主循环，每次找出一个顶点的最短距离
    for (int i = 1; i < vertex_num; i++) {
        int min_dist = INF;
        int u        = src;

        // 找出当前未访问顶点中距离最小的
        for (int j = 0; j < vertex_num; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                u        = j;
            }
        }

        visited[u] = true;

        // 更新邻接顶点距离
        for (int v = 0; v < vertex_num; v++) {
            if (!visited[v] && graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}
