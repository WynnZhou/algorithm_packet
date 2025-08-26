/*
 * @Description:
 * @FilePath: /src/main.c
 * @Github: https://github.com/wynnzhou
 * @Date: 2020-09-14 00:41:55
 * @LastEditTime: 2020-09-20 11:19:34
 * @Copyright: Copyright © 2017 wynnzhou. All rights reserved.
 */

/*

亲戚

题目背景
若某个家族人员过于庞大，要判断两个是否是亲戚，确实还很不容易，现在给出某个亲戚关系图，求任意给出的两个人是否具有亲戚关系。

题目描述
规定：x和y是亲戚，y和z是亲戚，那么x和z也是亲戚。如果x,y是亲戚，那么x的亲戚都是y的亲戚，y的亲戚也都是x的亲戚。

输入格式
第一行：三个整数n,m,p，（n<=5000,m<=5000,p<=5000），分别表示有n个人，m个亲戚关系，询问p对亲戚关系。
以下m行：每行两个数Mi，Mj，1<=Mi，Mj<=N，表示Mi和Mj具有亲戚关系。
接下来p行：每行两个数Pi，Pj，询问Pi和Pj是否具有亲戚关系。

输出格式
P行，每行一个’Yes’或’No’。表示第i个询问的答案为“具有”或“不具有”亲戚关系。

*/

#include <stdio.h>
#include "union_find_sets.h"

int main(int argc, char const *argv[])
{
    int n, m, p, x, y;

    scanf("%d%d%d", &n, &m, &p);
    union_find_set *ufs = ufs_init(n);
    for (int i = 0; i < m; ++i) {
        scanf("%d%d", &x, &y);
        ufs_merge(ufs, x, y);
    }
    for (int i = 0; i < p; ++i) {
        scanf("%d%d", &x, &y);
        printf("%s\n", ufs_find(ufs, x) == ufs_find(ufs, y) ? "Yes" : "No");
    }
    ufs_delete(ufs);
    return 0;
}