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

/**
 * @brief           检查一个数是否为质数
 * @param[in]       x       要检查的数字
 * @retval          int     1:是质数 0:不是质数
 * @version         1.0.0
 */
int is_prime(const int x);

/**
 * @brief           获取大于等于x的下一个质数
 * @param[in]       x       起始数字
 * @retval          int     下一个质数
 * @version         1.0.0
 */
int next_prime(int x);

#endif // _PRIME_H_
