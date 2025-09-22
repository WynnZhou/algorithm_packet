/*
 * @Description:
 * @FilePath: /src/prime.h
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-15 08:37:02
 * @LastEditTime: 2020-09-15 08:37:16
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */
#ifndef _PRIME_H_
#define _PRIME_H_

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief           检查是否为质数（使用6k±1优化）
 * @param[in]       n       要检查的数字
 * @retval          int     true:是质数 false:不是质数
 * @version         1.0.0
 */
bool is_prime(uint64_t n);

/**
 * @brief           寻找大于等于n的最小质数
 * @param[in]       n       起始数字
 * @retval          int     下一个质数
 * @version         1.0.0
 */
uint64_t next_prime(uint64_t n);

/**
 * @brief           带缓存的质数查找（寻找常用2倍扩容哈希值表中的下一个质数）
 * @param[in]       n       起始数字
 * @retval          int     下一个质数
 * @version         1.0.0
 */
uint64_t smart_next_prime(uint64_t n);

#endif // _PRIME_H_
