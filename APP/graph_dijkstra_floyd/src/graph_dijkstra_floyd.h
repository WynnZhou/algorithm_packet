/*
 * @Description:
 * @FilePath: /graph_dijkstra_floyd/src/graph_dijkstra_floyd.h
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-14 00:41:55
 * @LastEditTime: 2020-09-20 14:58:32
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */

#ifndef _GRAPH_DIJKSTRA_FLOYD_H_
#define _GRAPH_DIJKSTRA_FLOYD_H_

#define MAX_VERTEX 100
#define INF        0x3f3f3f3f

/**
 * @brief           使用Dijkstra算法计算单源最短路径
 * @param[in]       graph       图的邻接矩阵
 * @param[in]       vertex_num  顶点数量
 * @param[in]       src         源点索引
 * @param[out]      dist        存储最短距离的数组
 * @retval          void
 * @version         1.0.0
 */
void dijkstra(int graph[MAX_VERTEX][MAX_VERTEX], int vertex_num, int src, int dist[MAX_VERTEX]);

#endif // _GRAPH_DIJKSTRA_FLOYD_H_
