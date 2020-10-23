> 学习自：https://www.swack.cn/wiki/001558681974020669b912b0c994e7090649ac4846e80b2000/001572849111298ae30696043604e45a4c83f0e9842b818000

# 【C_Algorithm】哈希表

hash表中存储的每一项key-value的数据结构：

```c
typedef struct {
    char* key;
    char* value;
} hash_item;
```

我们的hash表中保存着一个指向每一项的指针数组，里面还包括hash表的大小，结构如下：

```c
typedef struct {
    int size_index;
    int size;
    int count;
    hash_item** items;
} hash_table;
```

### 初始化

在hash表中，我们需要定义一个函数来初始化一条记录(hash_item)，这个函数会为每一条记录(hash_item)申请内存，然后将k和v保存在这个内存中。为了让该函数只能在我们的hash table中使用，我们用static来修饰。

```c
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
```

hash_new_table初始化一个新的hash表，table->size表示这个hash表可以存储多少条记录。我们使用next_prime函数获取当前数的下一个质数，并将它作为hash的大小。`table->size = next_prime(base_size); // 默认哈希表容量`

```c
// "prime.c"
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
```

```c
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
```

### 删除

我们还需要额外的函数来删除ht_item和ht_hash_table，这个函数会释放(free)我们之前申请的内存空间，以至于不会造成内存泄漏：

```c
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
```

现在，我们已经完成定义一个hash表，现在我们可以试着创建一个hash表并试着销毁它，尽管现在并没有做太多东西。

```c
// main.c
#include "hash_table.h"

int main() {
    ht_hash_table* ht = ht_new();
    ht_del_hash_table(ht);
}
```

### Hash函数

本教程中我们实现的Hash函数将会实现如下操作：

- 输入一个字符串，然后返回一个0到m(Hash表的大小)的数字
- 为一组平常的输入返回均匀的bucket索引。如果Hash函数不是均匀分布的，就会将多个记录插入到相同的bucket中，这就回提高冲突的几率，而这个冲突就会影响到我们的Hash表的效率。

### 什么是冲突？

理想中的散列函数返回的结果都是均匀分布的，但是，对于任意一个散列函数，总会有一些输入经过散列后，得到相同的值。如果要找到这组输入，我们就需要测试大量的输入数据。

因为上面提到的有不好的输入存在，意味着所有输入都没有完美的散列函数。所以在设计散列函数时，针对预期输入，我们的散列函数需要表现最好。

不好的输入也存在安全问题，如果某个恶意用户向哈希表提供了一组冲突密钥，那么搜索这些密钥将比正常情况（`O(1)`）花费更长时间（`O(n)`）。这可以用作针对以哈希表为基础的系统（例如DNS和某些Web服务）的拒绝服务攻击。

### 处理碰撞

hash函数中将无限大的输入映射到有限的输出中，当不同的输入映射到相同的输出时，就会发生碰撞，每个的hash表都会采用不同的方法来处理碰撞。

我们的哈希表将使用一种称为开放地址的双重哈希的技术来处理冲突。双重哈希使用两个散列函数来计算在发生碰撞后存储记录的索引。

### 双重哈希

当i发生碰撞后我们使用如下方式来获取索引：

```c
index = hash_a(string) + i * hash_b(string) % num_buckets
```

当没有发生碰撞时，i=0，所以索引就是hash_a的值，发生碰撞后，hash_a的结果就需要经过一次hash_b的处理。

hash_b可能会返回0，将第二项减少到0，这就导致hash表会将多个记录插入到同一个bucket中，我们可以在hash_b的结果后加1来处理这种情况，确保它永远不会为0：

```c
index = hash_a(string) + i * (hash_b(string) + 1) % num_buckets
```

```c
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
```

### Insert函数

在hash表中插入一条记录时，我们需要遍历整个hash表知道找到一个空的位置，然后执行插入并将hash表的大小加1。hash表中的count属性代表hash表的大小，在下一章缩放hash表大小中很有用：

```c
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
    // Resize if load > 0.5
    const int load = table->count * 100 / table->size;
    if (load > 50) {
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
```

### delete函数

从开放的地址hash表中删除比插入或搜索更复杂，因为存在碰撞，我们希望删除的记录可能是碰撞链的一部分。从表中删除它会破坏该链，并且无法在链的尾部找到记录。要解决此问题，我们只需将其标记为已删除，而不是真的删除该记录。

我们将记录替换为指向全局哨兵的指针，再将其标记为已删除，该全局哨兵表示包含已删除的记录的bucket：

```c
// // HT_DELETED_ITEM is used to mark a bucket containing a deleted item
// static hash_item HT_DELETED_ITEM = {NULL, NULL};

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
```

删除后，我们需要将hash表的count属性减1。

### Search函数

search和insert有点相似，但是在while循环中，我们会检查记录的key是否与我们正在搜索的key匹配。如果匹配，就会返回这条记录的value，没有匹配到就会返回`NULL`：

```c
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
```

### 调整表的大小

随着更多的项被插入，表开始填满。这是有问题的，原因有二:

1. 哈希表的性能随着高碰撞率而降低
2. 我们的哈希表只能存储固定数量的项。如果我们试图存储更多的数据，插入函数就会失败。

为了缓解这个问题，我们可以在项目数组太满时增加它的大小。我们将散列表中存储的项数存储在表的`count`属性中。在每次插入和删除操作中，我们都要计算表的“负载”，即满桶与总桶的比率。如果它高于或低于某些值，我们将调整桶的大小。

我们将调整:

- up, if load > 0.7
- down, if load < 0.1

为了调整大小，我们创建一个新的哈希表，其大小大约是当前哈希表的一半或两倍，并将所有未删除的项插入其中。

```c
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
```

