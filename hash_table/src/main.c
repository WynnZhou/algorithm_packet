/*
 * @Description: 
 * @FilePath: /src/main.c
 * @Author: Wei Zhou
 * @Github: https://github.com/zromyk
 * @Date: 2020-09-14 00:41:55
 * @LastEditors: Wei Zhou
 * @LastEditTime: 2020-09-15 10:14:51
 * @Copyright: Copyright © 2017 muyiro. All rights reserved.
 */
#include <stdio.h>
#include "hash_table.h"

int main(int argc, char const *argv[])
{
    hash_table* table = hash_new_table();
    
    const char *str[][2] = {
        {"Hello",   "What"}, 
        {"What",    "When"}, 
        {"C++",     "Java"}, 
        {"Mac",     "Windows"}, 
        {"QQ",      "WeChet"}, 
        {"Word",    "Excel"}, 
        {"Mail",    "Message"}, 
    };
    
    for (size_t i = 0; i < (sizeof(str) / sizeof(str[0][0])) / 2; i++) {
        if (hash_insert(table, str[i][0], str[i][1])) { 
            printf("[%-8s : %-8s] Insert!\n", str[i][0], str[i][1]); 
        }
    }

    printf("\nFinding first...\n");

    char* temp;
    for (size_t i = 0; i < (sizeof(str) / sizeof(str[0][0])) / 2; i++) {
        if ((temp = hash_search(table, str[i][0])) == NULL) { 
            printf("%s: Not Found!\n", str[i][0]); 
        }
        else {
            printf("Found: %s\n", temp);
        }
    }

    hash_delete(table, "C++");
    printf("\nFinding second...\n");

    for (size_t i = 0; i < (sizeof(str) / sizeof(str[0][0])) / 2; i++) {
        if ((temp = hash_search(table, str[i][0])) == NULL) { 
            printf("%s: Not Found!\n", str[i][0]); 
        }
        else {
            printf("Found: %s\n", temp);
        }
    }
    
    hash_delete_table(table);
    return 0;
}