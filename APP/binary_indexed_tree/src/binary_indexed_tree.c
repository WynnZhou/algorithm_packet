/*
 * @Description:
 * @FilePath: /binary_indexed_tree/src/binary_indexed_tree.c
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-14 00:41:55
 * @LastEditTime: 2020-09-20 14:56:43
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include "binary_indexed_tree.h"

#define lowbit(x) ((x) & (-x))

/**
 * @brief           更新树状数组中指定位置的值
 * @param[in]       tree    树状数组的首地址
 * @param[in]       len     树状数组的长度
 * @param[in]       i       要更新的元素下标(从1开始)
 * @param[in]       x       要增加/减少的值
 * @retval          void
 * @version         1.0.0
 */
void update(int *tree, int len, int i, int x)
{
    for (int pos = i; pos < len; pos += lowbit(pos)) {
        tree[pos] += x;
    }
}

/**
 * @brief           计算树状数组前i项的和
 * @param[in]       tree    树状数组的首地址
 * @param[in]       i       结束下标(从1开始)
 * @retval          int     前i项的和
 * @version         1.0.0
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
 * @brief           计算树状数组指定区间的和
 * @param[in]       tree    树状数组的首地址
 * @param[in]       left    起始下标(从1开始)
 * @param[in]       right   结束下标(从1开始)
 * @retval          int     区间和
 * @version         1.0.0
 */
int sum_range(int *tree, int left, int right)
{
    return sum(tree, right) - sum(tree, left - 1);
}
