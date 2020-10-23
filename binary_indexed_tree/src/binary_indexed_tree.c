/*
 * @Description: 
 * @FilePath: /binary_indexed_tree/src/binary_indexed_tree.c
 * @Github: https://github.com/zromyk
 * @Date: 2020-09-14 00:41:55
 * @LastEditors: Wei Zhou
 * @LastEditTime: 2020-09-20 14:56:43
 * @Copyright: Copyright © 2017 muyiro. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include "binary_indexed_tree.h"

#define lowbit(x) ((x) & (-x))

/**
 * @description: 更新：在 i 位置 +(-) x
 * @param {type}    tree {int *} 树状数组的首地址
 *                  len {int} 树状数组的长度
 *                  i {int} 树状数组元素的下标，** i从1开始 **
 *                  x {int} 增/减 的值
 */
void update(int *tree, int len, int i, int x)
{
    for (int pos = i; pos < len; pos += lowbit(pos)) {
        tree[pos] += x;
    }
}

/**
 * @description: 求：1 到 i 项的和
 * @param {type}    tree {int *} 树状数组的首地址
 *                  i {int} 树状数组元素的下标，** i从1开始 **
 */
int sum(int *tree, int i)
{
    int ans = 0;
    for (int pos = i; pos; pos -= lowbit(pos)) {
        ans += tree[pos];
    }
    return ans;
}

/**
 * @description: 求：left 到 right 项的和
 * @param {type}    tree {int *} 树状数组的首地址
 *                  left {int}  树状数组元素的下标，** i从1开始 **
 *                  right {int} 树状数组元素的下标，** i从1开始 **
 */
int sum_range(int *tree, int left, int right)
{
    return sum(tree, right) - sum(tree, left - 1);
}