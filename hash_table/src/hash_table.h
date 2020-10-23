/*
 * @Description: 
 * @FilePath: /src/hash_table.h
 * @Author: Wei Zhou
 * @Github: https://github.com/zromyk
 * @Date: 2020-09-14 00:41:55
 * @LastEditors: Wei Zhou
 * @LastEditTime: 2020-09-15 09:18:40
 * @Copyright: Copyright © 2017 muyiro. All rights reserved.
 */

#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "stdlib.h"
#include "string.h"

typedef struct {
    char* key;
    char* value;
} hash_item;

typedef struct {
    int size_index;
    int size;
    int count;
    hash_item** items;
} hash_table;

/**
 * @description: 创建一张哈希表
 * @Author: Wei Zhou
 * @return {type} 哈希表的地址
 */
extern hash_table* hash_new_table(void);

/**
 * @description: 删除一张哈希表
 * ！！使用过hash_new_table函数后，必须调用此函数删除哈希表 ！！
 * @Author: Wei Zhou
 * @param {type}    table {hash_table*} 哈希表的地址
 */
extern void hash_delete_table(hash_table* table);

/**
 * @description: 插入一个键值对
 * @Author: Wei Zhou
 * @param {type}    table {hash_table*} 哈希表的地址
 *                  key {const char*} 键
 *                  value {const char*} 值
 * @return {type}  0 失败 : 1 成功
 */
extern int hash_insert(hash_table* table, const char* key, const char* value);

/**
 * @description: 删除一个键值对
 * @Author: Wei Zhou
 * @param {type}    table {hash_table*} 哈希表的地址
 *                  key {const char*} 键
 *                  value {const char*} 值
 * @return {type} NULL 失败 : else 成功
 */
extern void hash_delete(hash_table* table, const char* key);

/**
 * @description: 查找一个键值对
 * @Author: Wei Zhou
 * @param {type}    table {hash_table*} 哈希表的地址
 *                  key {const char*} 键
 *                  value {const char*} 值
 * @return {type} NULL 失败 : else 成功
 */
extern char* hash_search(hash_table* table, const char* key);

#endif // _HASH_TABLE_H_