/*
 * @Description: 
 * @FilePath: /src/hash_table.c
 * @Github: https://github.com/zromyk
 * @Date: 2020-09-14 00:41:55
 * @LastEditors: Wei Zhou
 * @LastEditTime: 2020-09-15 09:40:52
 * @Copyright: Copyright © 2017 muyiro. All rights reserved.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"
#include "prime.h"

// HT_DELETED_ITEM is used to mark a bucket containing a deleted item
static hash_item HT_DELETED_ITEM = {NULL, NULL};

/**
 * @description: 创建一个键值对
 * @param {type}    key {const char*} 键
 *                  value {const char*} 值
 * @return {type} 键值对信息的地址
 */
static hash_item* new_item(const char* key, const char* value)
{
    hash_item* item = (hash_item*)malloc(sizeof(hash_item));

    if (item == NULL) { return NULL; }

    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

/**
 * @description: 删除一个键值对
 * @param {type}    item {hash_item*} 键值对信息的地址
 */
static void delete_item(hash_item* item)
{
    free(item->key);
    free(item->value);
    free(item);
}

/**
 * @description: 调整哈希表的大小
 * @return {type} 哈希表的地址
 */
static hash_table* new_table_sized(int size_index)
{
    hash_table* table = (hash_table*)malloc(sizeof(hash_table));

    if (table == NULL) { return NULL; }

    table->size_index = size_index;
    const int base_size = 6 << table->size_index;
    table->size = next_prime(base_size); // 默认哈希表容量
    table->count = 0; // 初始化哈希表长度
    table->items = (hash_item**)calloc((size_t)table->size, sizeof(hash_item*));

    if (table->items == NULL) { free(table); return NULL; }
    
    return table;
}

/**
 * @description: 创建一张哈希表
 * @return {type} 哈希表的地址
 */
hash_table* hash_new_table(void)
{
    return new_table_sized(0);
}

/**
 * @description: 删除一张哈希表
 * @param {type}    table {hash_table*} 哈希表的地址
 */
void hash_delete_table(hash_table* table)
{
    for (int i = 0; i < table->size; i++) {
        hash_item* item = table->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            delete_item(item);
        }
    }
    free(table->items);
    free(table);
}

/**
 * @description: 重新调整哈希表的容量
 * @param {type}    table {hash_table*} 哈希表的地址
 *                  direction {const int} 1 扩大两倍, -1 减小一半
 */
static void resize(hash_table* table, const int direction)
{
    const int new_size_index = table->size_index + direction;
    if (new_size_index < 0) {
        // Don't resize down the smallest hash table
        return;
    }
    // Create a temporary new hash table to insert items into
    hash_table* new_table = new_table_sized(new_size_index);
    // Iterate through existing hash table, add all items to new
    for (int i = 0; i < table->size; i++) {
        hash_item* item = table->items[i];
        if (item != NULL && item != &HT_DELETED_ITEM) {
            hash_insert(new_table, item->key, item->value);
        }
    }

    // Pass new_table and table's properties. Delete new_table
    table->size_index = new_table->size_index;
    table->count = new_table->count;

    // To delete new_table, we give it table's size and items 
    const int tmp_size = table->size;
    table->size = new_table->size;
    new_table->size = tmp_size;

    hash_item** tmp_items = table->items;
    table->items = new_table->items;
    new_table->items = tmp_items;

    hash_delete_table(new_table);
}

/**
 * @description: 哈希函数
 * @param {type}    key {const char*} 键
 *                  a {const int} 常数，左移位数
 *                  size {const int} 表的大小
 * @return {type} 哈希值
 */
static int generic_hash(const char* key, const int a, const int size) {
    unsigned long hash_val = 0;

    while (*key != '\0') {
        hash_val += (hash_val << a) | *(key++);
    }
    return (int)(hash_val % size);
}

/**
 * @description: 双散列，双重哈希函数
 * @param {type}    key {const char*} 键
 *                  size {const int} 表的大小
 *                  attempt {const int} 尝试解决碰撞的次数
 * @return {type} 哈希值
 */
static int hash(const char* key, const int size, const int attempt) {
    const int hash_a = generic_hash(key, 6, size);
    const int hash_b = generic_hash(key, 7, size);
    return (hash_a + (attempt * (hash_b + 1))) % size;
}

/**
 * @description: 插入一个键值对
 * @param {type}    table {hash_table*} 哈希表的地址
 *                  key {const char*} 键
 *                  value {const char*} 值
 * @return {type}  0 失败 : 1 成功
 */
int hash_insert(hash_table* table, const char* key, const char* value)
{
    if (table == NULL) { return 0; }
    // Resize if load > 0.7
    const int load = table->count * 100 / table->size;
    if (load > 70) {
        resize(table, 1);
    }
    
    hash_item* item = new_item(key, value);

    if (item == NULL) { return 0; }

    int index = hash(item->key, table->size, 0);
    hash_item* cur_item = table->items[index];
    int i = 1;
    while (cur_item != NULL && cur_item != &HT_DELETED_ITEM) { // 产生碰撞
        if (strcmp(cur_item->key, key) == 0) { // key 值相同，更新key值
            delete_item(cur_item);
            table->items[index] = item;
            return 1;
        }
        index = hash(item->key, table->size, i); // 解决冲突
        cur_item = table->items[index];
        i++;
    }
    table->items[index] = item;
    table->count++;
    return 1;
}

/**
 * @description: 删除一个键值对
 * @param {type}    table {hash_table*} 哈希表的地址
 *                  key {const char*} 键
 *                  value {const char*} 值
 * @return {type} NULL 失败 : else 成功
 */
void hash_delete(hash_table* table, const char* key)
{
    if (table == NULL) { return; }
    
    // Resize if load < 0.1
    const int load = table->count * 100 / table->size;
    if (load < 10) {
        resize(table, -1);
    }
    
    int index = hash(key, table->size, 0);
    hash_item* item = table->items[index];
    int i = 1;
    while (item != NULL && item != &HT_DELETED_ITEM) {
        if (strcmp(item->key, key) == 0) {
            delete_item(item);
            table->items[index] = &HT_DELETED_ITEM; // 伪删除
        }
        index = hash(key, table->size, i); // 解决冲突
        item = table->items[index];
        i++;
    } 
    table->count--;
}

/**
 * @description: 查找一个键值对
 * @param {type}    table {hash_table*} 哈希表的地址
 *                  key {const char*} 键
 *                  value {const char*} 值
 * @return {type} NULL 失败 : else 成功
 */
char* hash_search(hash_table* table, const char* key) 
{
    if (table == NULL) { return NULL; }

    int index = hash(key, table->size, 0);
    hash_item* item = table->items[index];
    hash_item* first_item = item;
    int i = 1;
    while (item != NULL) { // 存在键值对
        if (item != &HT_DELETED_ITEM) {
            if (strcmp(item->key, key) == 0) { // 判断键值是否正确
                // printf("index: %d\n", index);
                return item->value;
            }
        }
        index = hash(key, table->size, i); // 解决冲突
        item = table->items[index];
        i++;
    } 
    return NULL;
}