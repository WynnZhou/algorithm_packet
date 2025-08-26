/*
 * @Description:
 * @FilePath: /binary_indexed_tree/src/binary_indexed_tree.h
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-14 00:41:55
 * @LastEditTime: 2020-09-20 14:58:32
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */

#ifndef _BINARY_INDEXED_TREE_H_
#define _BINARY_INDEXED_TREE_H_

/**
 * @brief           更新树状数组中指定位置的值
 * @param[in]       tree    树状数组的首地址
 * @param[in]       len     树状数组的长度
 * @param[in]       i       要更新的元素下标(从1开始)
 * @param[in]       x       要增加/减少的值
 * @retval          void
 * @version         1.0.0
 * @code
 * int tree[10] = {0};
 * update(tree, 10, 2, 5);  // 第2个元素增加5
 * @endcode
 */
extern void update(int *tree, int len, int i, int x);

/**
 * @brief           计算树状数组前i项的和
 * @param[in]       tree    树状数组的首地址
 * @param[in]       i       结束下标(从1开始)
 * @retval          int     前i项的和
 * @version         1.0.0
 * @code
 * int tree[10] = {0};
 * int total = sum(tree, 5);  // 计算前5项和
 * @endcode
 */
extern int sum(int *tree, int i);

/**
 * @brief           计算树状数组指定区间的和
 * @param[in]       tree    树状数组的首地址
 * @param[in]       left    起始下标(从1开始)
 * @param[in]       right   结束下标(从1开始)
 * @retval          int     区间和
 * @version         1.0.0
 * @code
 * int tree[10] = {0};
 * int range_sum = sum_range(tree, 2, 5);  // 计算第2到第5项的和
 * @endcode
 */
extern int sum_range(int *tree, int left, int right);

#endif // _BINARY_INDEXED_TREE_H_
