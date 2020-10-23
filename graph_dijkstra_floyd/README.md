# 最短路径问题

### 1. 最短路径问题介绍

问题解释：
从图中的某个顶点出发到达另外一个顶点的所经过的边的权重和最小的一条路径，称为最短路径

解决问题的算法：

- **迪杰斯特拉算法（Dijkstra算法）**
- 弗洛伊德算法（Floyd算法）
- SPFA算法

### 2. Dijkstra算法（单源最短路径问题）

> 不适用于含有**负边**的图

Dijkstra基于一种**贪心**的思想，我们假定有一张没有**负边**的图。首先，起点到起点的距离为0，这是没有疑问的。现在我们对起点和它能直接到达的所有点进行松弛。

![54654213215](/Users/zhouwei/Desktop/algorithm_packet/graph_dijkstra_floyd/54654213215.png)

![13213211052](/Users/zhouwei/Desktop/algorithm_packet/graph_dijkstra_floyd/13213211052.png)

