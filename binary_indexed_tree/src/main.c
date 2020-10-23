/*
 * @Description: 
 * @FilePath: /binary_indexed_tree/src/main.c
 * @Author: Wei Zhou
 * @Github: https://github.com/zromyk
 * @Date: 2020-09-14 00:41:55
 * @LastEditors: Wei Zhou
 * @LastEditTime: 2020-09-20 18:49:58
 * @Copyright: Copyright © 2017 muyiro. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_indexed_tree.h"

#define MAXN 50005

int tree[MAXN];

int main(int argc, char const *argv[])
{
    memset(tree, 0, sizeof(tree));
    int n, x, a, b;
    char opr[10];
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &x);
        update(tree, MAXN, i, x);
    }
    printf("Command: ");
    while (scanf("%s", opr), opr[0] != 'E')
    {
        switch (opr[0])
        {
        case 'A':
            scanf("%d%d", &a, &b);
            update(tree, MAXN, a, b);
            break;
        case 'S':
            scanf("%d%d", &a, &b);
            update(tree, MAXN, a, -b);
            break;
        case 'Q':
            scanf("%d%d", &a, &b);
            printf("%d\n", sum_range(tree, a, b));
        }
    }
    return 0;
}