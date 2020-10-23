/*
 * @Description: 
 * @FilePath: /binary_indexed_tree/src/binary_indexed_tree.h
 * @Author: Wei Zhou
 * @Github: https://github.com/zromyk
 * @Date: 2020-09-14 00:41:55
 * @LastEditors: Wei Zhou
 * @LastEditTime: 2020-09-20 14:58:32
 * @Copyright: Copyright © 2017 muyiro. All rights reserved.
 */

#ifndef _BINARY_INDEXED_TREE_H_
#define _BINARY_INDEXED_TREE_H_

/**
 * @description: 更新：在 i 位置 +(-) x
 * @param {type}    tree {int *} 树状数组的首地址
 *                  len {int} 树状数组的长度
 *                  i {int} 树状数组元素的下标，** i从1开始 **
 *                  x {int} 增/减 的值
 */
extern void update(int *tree, int len, int i, int x);

/**
 * @description: 求：1 到 i 项的和
 * @param {type}    tree {int *} 树状数组的首地址
 *                  i {int} 树状数组元素的下标，** i从1开始 **
 */
extern int sum(int *tree, int i);

/**
 * @description: 求：left 到 right 项的和
 * @param {type}    tree {int *} 树状数组的首地址
 *                  left {int}  树状数组元素的下标，** i从1开始 **
 *                  right {int} 树状数组元素的下标，** i从1开始 **
 */
extern int sum_range(int *tree, int left, int right);

#endif // _BINARY_INDEXED_TREE_H_