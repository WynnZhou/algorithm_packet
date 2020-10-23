/*
 * @Description: 
 * @FilePath: /src/prime.c
 * @Author: Wei Zhou
 * @Github: https://github.com/zromyk
 * @Date: 2020-09-15 08:32:05
 * @LastEditors: Wei Zhou
 * @LastEditTime: 2020-09-15 09:19:32
 * @Copyright: Copyright © 2017 muyiro. All rights reserved.
 */
#include <math.h>
#include "prime.h"

/*
 * Return whether x is prime or not
 *
 * Returns:
 *   1  - prime
 *   0  - not prime
 *   -1 - undefined (i.e. x < 2)
 */
int is_prime(const int x) 
{
    if (x < 2) { return -1; }
    if (x < 4) { return 1; }
    if ((x % 2) == 0) { return 0; }
    for (int i = 3; i <= floor(sqrt((double) x)); i += 2) {
        if ((x % i) == 0) {
            return 0;
        }
    }
    return 1;
}

/*
 * Return the next prime after x, or x if x is prime
 */
int next_prime(int x) 
{
    if ((x & 0x01) == 0)  { ++x; } // 保证是奇数
    while (is_prime(x) != 1) {
        x += 2;
    }
    return x;
}
