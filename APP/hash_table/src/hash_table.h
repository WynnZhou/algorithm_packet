/*
 * @Description:
 * @FilePath: /src/hash_table.h
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-14 00:41:55
 * @LastEditTime: 2020-09-15 09:18:40
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "stdlib.h"
#include "string.h"

typedef struct {
    char *key;
    char *value;
} hash_item;

typedef struct {
    int         size_index;
    int         size;
    int         count;
    hash_item **items;
} hash_table;

/**
 * @brief           创建新的哈希表
 * @retval          hash_table*  新哈希表指针
 * @version         1.0.0
 * @code
 * hash_table* table = hash_new_table(); // 创建新哈希表
 * @endcode
 */
extern hash_table *hash_new_table(void);

/**
 * @brief           删除哈希表并释放内存
 * @param[in]       table   要删除的哈希表指针
 * @retval          void
 * @version         1.0.0
 * @note           使用过hash_new_table后必须调用此函数
 */
extern void hash_delete_table(hash_table *table);

/**
 * @brief           插入键值对到哈希表
 * @param[in]       table   哈希表指针
 * @param[in]       key     键字符串
 * @param[in]       value   值字符串
 * @retval          int     0:失败 1:成功
 * @version         1.0.0
 * @code
 * hash_insert(table, "name", "John"); // 插入键值对
 * @endcode
 */
extern int hash_insert(hash_table *table, const char *key, const char *value);

/**
 * @brief           从哈希表删除键值对
 * @param[in]       table   哈希表指针
 * @param[in]       key     要删除的键
 * @retval          void
 * @version         1.0.0
 * @code
 * hash_delete(table, "name"); // 删除键为"name"的项
 * @endcode
 */
extern void hash_delete(hash_table *table, const char *key);

/**
 * @brief           查找键对应的值
 * @param[in]       table   哈希表指针
 * @param[in]       key     要查找的键
 * @retval          char*   找到的值指针，NULL表示未找到
 * @version         1.0.0
 * @code
 * char* value = hash_search(table, "name"); // 查找键为"name"的值
 * @endcode
 */
extern char *hash_search(hash_table *table, const char *key);

#endif // _HASH_TABLE_H_
