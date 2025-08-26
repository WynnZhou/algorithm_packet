/*
 * @Description:
 * @FilePath: /src/prime.c
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-15 08:32:05
 * @LastEditTime: 2020-09-15 09:19:32
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */
#include <math.h>
#include "prime.h"

/**
 * @brief           检查一个数是否为质数
 * @param[in]       x       要检查的数字
 * @retval          int     1:是质数 0:不是质数 -1:无效输入(x < 2)
 * @version         1.0.0
 */
int is_prime(const int x)
{
    if (x < 2) {
        return -1;
    }
    if (x < 4) {
        return 1;
    }
    if ((x % 2) == 0) {
        return 0;
    }
    for (int i = 3; i <= floor(sqrt((double)x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief           获取大于等于x的下一个质数
 * @param[in]       x       起始数字
 * @retval          int     下一个质数
 * @version         1.0.0
 */
int next_prime(int x)
{
    if ((x & 0x01) == 0) {
        ++x;
    } // 保证是奇数
    while (is_prime(x) != 1) {
        x += 2;
    }
    return x;
}
