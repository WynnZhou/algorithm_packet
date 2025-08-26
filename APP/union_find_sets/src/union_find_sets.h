/*
 * @Description:
 * @FilePath: /src/UnionFindSets.h
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-14 00:41:55
 * @LastEditTime: 2020-09-18 20:37:34
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */

#ifndef _UNION_FIND_SETS_H_
#define _UNION_FIND_SETS_H_

typedef struct {
    int  maxSize;
    int *pre;
    int *rank;
} union_find_set;

/**
 * @brief           初始化并查集
 * @param[in]       n       初始大小
 * @retval          union_find_set*  指向并查集的指针
 * @version         1.0.0
 * @code
 * union_find_set* ufs = ufs_init(10); // 初始化大小为10的并查集
 * @endcode
 */
union_find_set *ufs_init(int n);

/**
 * @brief           清空并查集资源
 * @param[in]       ufs     指向并查集的指针
 * @retval          void
 * @version         1.0.0
 */
void ufs_clear(union_find_set *ufs);

/**
 * @brief           查询节点的根节点
 * @param[in]       ufs     指向并查集的指针
 * @param[in]       x       当前节点
 * @retval          int     根节点索引
 * @version         1.0.0
 * @code
 * int root = ufs_find(ufs, 5); // 查询节点5的根节点
 * @endcode
 */
int ufs_find(union_find_set *ufs, int x);

/**
 * @brief           合并两个节点
 * @param[in]       ufs     指向并查集的指针
 * @param[in]       i       第一个节点
 * @param[in]       j       第二个节点
 * @retval          void
 * @version         1.0.0
 * @code
 * ufs_merge(ufs, 3, 5); // 合并节点3和节点5
 * @endcode
 */
void ufs_merge(union_find_set *ufs, int i, int j);

/**
 * @brief           释放并查集内存
 * @param[in]       ufs     指向并查集的指针
 * @retval          void
 * @version         1.0.0
 */
void ufs_delete(union_find_set *ufs);

#endif // _UNION_FIND_SETS_H_
