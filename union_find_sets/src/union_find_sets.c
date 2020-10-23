/*
 * @Description: 
 * @FilePath: /Union_find_Sets/src/UnionFindSets.c
 * @Github: https://github.com/zromyk
 * @Date: 2020-09-14 00:41:55
 * @LastEditors: Wei Zhou
 * @LastEditTime: 2020-09-18 22:26:34
 * @Copyright: Copyright © 2017 muyiro. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include "union_find_sets.h"

/**
 * @description: 并查集初始化
 * @Author: Wei Zhou
 * @param {type} n {int} 设置初始大小 n
 * @return {type} 指向并查集的指针
 */
union_find_set* ufs_init(int n)
{
    union_find_set* ufs = (union_find_set*)malloc(sizeof(union_find_set));
    
    ufs->maxSize = n + 1;
    ufs->pre  = (int*)malloc(sizeof(int) * ufs->maxSize);
    ufs->rank = (int*)malloc(sizeof(int) * ufs->maxSize);
    
    for (int i = 1; i < ufs->maxSize; ++i) {
        ufs->pre[i]  = i; // 每一个的根节点都是其本身
        ufs->rank[i] = 1;
    }
    return ufs;
}

/**
 * @description: 删除并查集
 * @Author: Wei Zhou
 * @param {type}    ufs {union_find_set*} 指向并查集的指针
 */
void ufs_clear(union_find_set* ufs)
{
    for (int i = 1; i < ufs->maxSize; ++i) {
        ufs->pre[i]  = i; // 每一个的根节点都是其本身
        ufs->rank[i] = 1;
    } 
}

/**
 * @description: 查询根节点
 * @Author: Wei Zhou
 * @param {type}    ufs {union_find_set*} 指向并查集的指针
 *                  x {int} 当前节点
 * @return {type} 根节点
 */
int ufs_find(union_find_set* ufs, int x)
{
    return x == ufs->pre[x] ? x : (ufs->pre[x] = ufs_find(ufs, ufs->pre[x]));
}

/**
 * @description: 合并两个节点
 * @Author: Wei Zhou
 * @param {type}    ufs {union_find_set*} 指向并查集的指针
 *                  i {int} 当前节点, j {int} 当前节点
 */
void ufs_merge(union_find_set* ufs, int i, int j)
{
    int x = ufs_find(ufs, i), y = ufs_find(ufs, j); //先找到两个根节点
    if (ufs->rank[x] <= ufs->rank[y]) {
        ufs->pre[x] = y;
    }
    else {
        ufs->pre[y] = x;
    }
    if (ufs->rank[x] == ufs->rank[y] && x != y) {
        ufs->rank[y]++; //如果深度相同且根节点不同，则新的根节点的深度+1
    }
}

/**
 * @description: 删除并查集
 * @Author: Wei Zhou
 * @param {type}    ufs {union_find_set*} 指向并查集的指针
 */
void ufs_delete(union_find_set* ufs)
{
    free(ufs->pre);
    free(ufs->rank);
    free(ufs);
}