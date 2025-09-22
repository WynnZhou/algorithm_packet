/*
 * @Description:
 * @FilePath: /src/prime.c
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-15 08:32:05
 * @LastEditTime: 2020-09-15 09:19:32
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */
#include "prime.h"

// 扩展的质数表（适用于32位和64位环境）
static const uint64_t extended_prime_sizes[] = {
    // 小规模（< 10,000）
    53,
    97,
    193,
    389,
    769,
    1543,
    3079,
    6151,
    12289,
    24593,

    // 中等规模（10,000 - 1,000,000）
    49157,
    98317,
    196613,
    393241,
    786433,
    1572869,
    3145739,
    6291469,
    12582917,
    25165843,

    // 大规模（1,000,000 - 100,000,000）
    50331653,
    100663319,
    201326611,
    402653189,
    805306457,
    1610612741,
    3221225473ULL,
    6442450939ULL,
    12884901893ULL,

    // 超大规模（> 100,000,000）
    2576980373ULL,
    51539607551ULL,
    103079215111ULL,
    206158430209ULL,
    412316860441ULL,
    824633720831ULL,
    1649267441651ULL,
    3298534883309ULL,
    6597069766657ULL
};

#define extended_prime_count (sizeof(extended_prime_sizes) / sizeof(extended_prime_sizes[0]))

/**
 * @brief           检查是否为质数（使用6k±1优化）
 * @param[in]       n       要检查的数字
 * @retval          int     true:是质数 false:不是质数
 * @version         1.0.0
 */
bool is_prime(uint64_t n)
{
    if (n <= 1)
        return false;
    if (n <= 3)
        return true;
    if (n % 2 == 0 || n % 3 == 0)
        return false;

    // 检查6k±1形式的因子
    for (uint64_t i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

/**
 * @brief           寻找大于等于n的最小质数
 * @param[in]       n       起始数字
 * @retval          int     下一个质数
 * @version         1.0.0
 */
uint64_t next_prime(uint64_t n)
{
    if (n <= 2)
        return 2;
    if (n % 2 == 0)
        n++; // 确保从奇数开始

    while (!is_prime(n)) {
        n += 2;
        // 避免整数溢出
        if (n < 2)
            return UINT64_MAX;
    }
    return n;
}

/**
 * @brief           带缓存的质数查找（寻找常用2倍扩容哈希值表中的下一个质数）
 * @param[in]       n       起始数字
 * @retval          int     下一个质数
 * @version         1.0.0
 */
uint64_t smart_next_prime(uint64_t n)
{
    // 首先检查预计算表
    for (size_t i = 0; i < extended_prime_count; i++) {
        if (extended_prime_sizes[i] >= n) {
            return extended_prime_sizes[i];
        }
    }

    // 如果在表中找不到，动态计算
    return next_prime(n);
}
