/*
 * @Description: 
 * @FilePath: /src/UnionFindSets.h
 * @Author: Wei Zhou
 * @Github: https://github.com/zromyk
 * @Date: 2020-09-14 00:41:55
 * @LastEditors: Wei Zhou
 * @LastEditTime: 2020-09-18 20:37:34
 * @Copyright: Copyright © 2017 muyiro. All rights reserved.
 */

#ifndef _UNION_FIND_SETS_H_
#define _UNION_FIND_SETS_H_

typedef struct {
    int  maxSize;
    int* pre;
    int* rank;
} union_find_set;

/**
 * @description: 并查集初始化
 * @Author: Wei Zhou
 * @param {type} n {int} 设置初始大小 n
 * @return {type} 指向并查集的指针
 */
union_find_set* ufs_init(int n);

/**
 * @description: 删除并查集
 * @Author: Wei Zhou
 * @param {type}    ufs {union_find_set*} 指向并查集的指针
 */
void ufs_clear(union_find_set* ufs);

/**
 * @description: 查询根节点
 * @Author: Wei Zhou
 * @param {type}    ufs {union_find_set*} 指向并查集的指针
 *                  x {int} 当前节点
 * @return {type} 根节点
 */
int ufs_find(union_find_set* ufs, int x);

/**
 * @description: 合并两个节点
 * @Author: Wei Zhou
 * @param {type}    ufs {union_find_set*} 指向并查集的指针
 *                  i {int} 当前节点, j {int} 当前节点
 */
void ufs_merge(union_find_set* ufs, int i, int j);

/**
 * @description: 删除并查集
 * @Author: Wei Zhou
 * @param {type}    ufs {union_find_set*} 指向并查集的指针
 */
void ufs_delete(union_find_set* ufs);

#endif // _UNION_FIND_SETS_H_