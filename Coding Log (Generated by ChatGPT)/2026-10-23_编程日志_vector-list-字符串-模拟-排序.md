---
date: 2026-10-23
type: 编程日志
course: 计算概论
language: C++
tags:
  - 编程日志
  - C++
  - vector
  - list
  - 迭代器
  - 循环访问
  - 模拟
  - 字符串
  - 输入输出
  - 排序
  - 结构体
  - 计算几何
  - 调试
---

# 2026-10-23 编程日志｜vector · list · 字符串 · 模拟与排序

> **今天的主线：** 从“`vector` 为什么输出奇怪的大整数”开始，逐步掌握边遍历边删除、循环访问与链表迭代器；随后练习结构体排序、数位处理、分组、计算几何、字符数组、按行读取与字符串排序。
>
> **记录方式：** 问题 → 原因 → 正确写法 → 可迁移的思路。代码以 C++11 及以上为基础。

## 目录

1. [今日重点与踩坑速览](#1-今日重点与踩坑速览)
2. [`vector` 异常大数、越界与删除](#2-vector-异常大数越界与删除)
3. [逢 7 淘汰：动态模拟与状态管理](#3-逢-7-淘汰动态模拟与状态管理)
4. [循环访问、取模与边界](#4-循环访问取模与边界)
5. [`list`：定义、赋值、迭代器、插删](#5-list定义赋值迭代器插删)
6. [环状数据结构的几种实现](#6-环状数据结构的几种实现)
7. [结构体与 `sort`：成绩排名](#7-结构体与-sort成绩排名)
8. [整数位数和数位和](#8-整数位数和数位和)
9. [`scanf` / `printf` 的常见用法](#9-scanf--printf-的常见用法)
10. [整数筛选与按数位和分组](#10-整数筛选与按数位和分组)
11. [叉积判断严格凸四边形](#11-叉积判断严格凸四边形)
12. [区间标记：校门外的树](#12-区间标记校门外的树)
13. [三维点对枚举与距离排序](#13-三维点对枚举与距离排序)
14. [二维字符数组、`string` 与字典序](#14-二维字符数组string-与字典序)
15. [一行输入、单词倒序和 `stringstream`](#15-一行输入单词倒序和-stringstream)
16. [链接错误与常用调试习惯](#16-链接错误与常用调试习惯)
17. [知识卡片、复杂度与后续练习](#17-知识卡片复杂度与后续练习)

---

## 1. 今日重点与踩坑速览

| 今日问题 | 根本原因 / 核心方法 | 以后如何检查 |
|---|---|---|
| `vector` 输出 `26844...` 一类大数 | 可能访问了 `stu[-1]`、`stu[stu.size()]` 等非法位置，属未定义行为 | 先打印下标和 `size()`，调试时用 `.at()` |
| 淘汰学生后该不该 `j++` | `erase()` 后，后续元素自动前移 | **删除时不增加 `j`，未删除时才增加** |
| `judge(71)` 判断失误 | `while (x > 10)` 漏检最高位的 `7` | 应逐位检查直到 `x == 0` |
| 按回合报数和按学生位置混淆 | 报数 `num` 与位置 `j` 是两种不同状态 | 一轮结束始终 `num++`，仅按情况更新 `j` |
| 最后一个学生被删除后越界 | `vector` 已为空，不能再访问/取模 | 使用 `!stu.empty()` 判断 |
| 数位和分组题选错数字 | 把“`i` 是 `k` 的倍数”误写成“数位和是 `k` 的倍数” | 分开写 `i % k == 0` 与 `digit_sum(i) == t` |
| 校门外的树答案不对 | `int a[N] = {1}` 仅第 0 项是 1；统计漏了坐标 0 | 用 `fill()`，遍历 `0..L` |
| `while (cin >> word)` 按 Enter 不停止 | `>>` 会跳过换行并继续等输入 | 整行读取用 `getline()` |
| 链接器 `ld returned 1 exit status` | 只是链接失败的最后总结，并非完整原因 | 重点看上面的 `undefined reference` / `Permission denied` 等信息 |

> **本日最重要的程序设计原则：** 每次修改容器后，立刻重新思考“现在谁是当前元素、下标/迭代器是否仍有效、容器是否为空”。

## 2. `vector` 异常大数、越界与删除

### 2.1 为什么出现异常大数？

原程序中曾存在这样的结构：

```cpp
stu.erase(remove(stu.begin(), stu.end(), out), stu.end());
j--;
cout << stu[j] << endl;
```

如果删除时 `j == 0`，则 `j--` 得到 `-1`。`stu[-1]` 是**越界访问**，`operator[]` 不负责检查范围，结果为**未定义行为**：可能输出奇怪整数、崩溃，或者偶尔看似正常。

还有一种越界：删除最后一名学生后 `j` 恰好等于新的 `stu.size()`，此时 `stu[j]` 也不合法；若 `stu` 为空，任何 `stu[j]` 都不合法。

**建议的调试方式：**

```cpp
cout << "j=" << j << ", size=" << stu.size() << '\n';
cout << stu.at(j) << '\n'; // 越界时抛出 out_of_range
```

只有确认 `0 <= j && j < stu.size()` 后才能读取 `stu[j]`。

### 2.2 两种删除语法要区分

```cpp
vector<int> v = {1, 2, 3, 2, 4};

v.erase(v.begin() + 2); // 按下标删除：删掉 3
```

如果想按数值删除**所有** `2`：

```cpp
#include <algorithm>
v.erase(remove(v.begin(), v.end(), 2), v.end());
```

- `v.erase(v.begin() + j)`：已知当前位置，要删除**一个元素**，更直接。
- `erase(remove(...), end())`：按**数值**删掉所有匹配元素；`std::remove` 本身只是移动/重排元素，不缩短容器长度。
- `vector::erase()` 之后，删除位置及其后的迭代器/引用可能失效；若使用下标，应重新检查大小与边界。

**复杂度：** 已知位置的 `vector.erase()` 通常仍是 `O(n)`，因为后续元素要左移。

## 3. 逢 7 淘汰：动态模拟与状态管理

### 3.1 题目模型

学生编号 `1..n`，围成一圈依次报数。报数为 7 的倍数，或十进制表示中含数字 `7` 时，淘汰当前学生；继续报数，直到没有学生。

**最少维护三类状态：**

| 变量 | 含义 | 变化时机 |
|---|---|---|
| `stu` | 目前仍在场的学生 | 淘汰时删元素 |
| `j` | 当前学生在容器中的位置 | 未淘汰则往后走；淘汰后沿用当前位置（必要时回绕） |
| `num` | 本轮报数 | **每一轮**结束都加 1 |

无需额外用 `cnt` 统计淘汰人数：`stu.empty()` 已经能表示结束。

### 3.2 `judge` 的修正

错误版本：

```cpp
while (x > 10) { // 错：最高位可能没有被检查
    if (x % 10 == 7) return true;
    x /= 10;
}
```

例如 `71 -> 7` 后循环退出，漏掉最高位 `7`。

正确版本：

```cpp
bool judge(int x) {
    if (x % 7 == 0) return true;
    while (x > 0) {
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}
```

### 3.3 一份精简、稳妥的 `vector` 解法

```cpp
#include <iostream>
#include <vector>
using namespace std;

bool judge(int x) {
    if (x % 7 == 0) return true;
    while (x > 0) {
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

int main() {
    int n;
    cin >> n;

    vector<int> stu;
    for (int x = 1; x <= n; ++x) stu.push_back(x);

    int num = 1, j = 0;
    while (!stu.empty()) {
        if (judge(num)) {
            cout << stu[j] << '\n';
            stu.erase(stu.begin() + j);
            // 删除后，后面的学生已补到当前位置，不要 j++
        } else {
            ++j;
        }

        if (!stu.empty() && j >= (int)stu.size()) j = 0;
        ++num;
    }
}
```

**边界自测：** 淘汰第一个、淘汰最后一个、仅剩一人时被淘汰。在线评测前删掉 `cout << num << ' ' << stu[j]` 一类调试输出。

## 4. 循环访问、取模与边界

对于非空、长度为 `n` 的容器，下一位的下标可以写成：

```cpp
j = (j + 1) % n;
```

更一般地，向前移动 `k` 步：

```cpp
j = (j + k) % n;
```

`% n` 使结果落在 `0..n-1` 之间，适用于约瑟夫环、游戏回合、时钟与循环队列。

**重要限制：**

1. `n` 必须大于 0；`% 0` 非法。
2. 删除当前位置时，不能无条件执行 `(j + 1) % size()`，否则会跳过自动前移的下一个元素。
3. 删除最后一个元素后，旧下标可能变成 `j == size()`，须回到 0。

举例：

```text
原来: [1, 2, 3, 4, 5], j=2（值为3）
删除3: [1, 2, 4, 5],   j=2（值为4）
```

此时保持 `j=2` 才对。

## 5. `list`：定义、赋值、迭代器、插删

`std::list` 是**双向链表**，它适合已知位置时频繁插删，不支持 `a[i]` 随机访问。

### 5.1 定义和初始化

```cpp
#include <list>
#include <string>
using namespace std;

list<int> a;                 // 空链表
list<int> b = {1, 2, 3};   // 三个整数
list<int> c(5);             // 5 个 0
list<int> d(5, 10);         // 5 个 10
list<int> e{5, 10};         // 两个元素 5、10
list<string> words = {"hi", "C++"};
```

### 5.2 赋值和基本操作

```cpp
list<int> a = {1, 2, 3};
list<int> b = a;     // 复制元素
b = {4, 5};         // 整体重新赋值
b.assign(3, 7);     // b 变成 7,7,7

b.push_front(1);    // 头插
b.push_back(9);     // 尾插
b.pop_front();      // 头删（必须非空）
b.pop_back();       // 尾删（必须非空）

b.size();
b.empty();
b.front();          // 第一个元素（必须非空）
b.back();           // 最后一个元素（必须非空）
b.sort();           // list 的成员排序函数
b.reverse();
b.remove(7);        // 删除所有值为7的元素
b.clear();
```

### 5.3 迭代器核心语法

```cpp
list<int> a = {10, 20, 30};
auto it = a.begin();

cout << *it << '\n'; // 10：解引用，读取当前值
++it;
cout << *it << '\n'; // 20
```

- `begin()`：第一个元素的位置。
- `end()`：**尾后位置**，不能 `*a.end()`。
- `++it`：移动到下一个节点。
- `it = a.erase(it)`：删除当前位置，并返回后继位置；删除最后一个元素时可能返回 `a.end()`。

**安全遍历删除模板：**

```cpp
for (auto it = a.begin(); it != a.end(); ) {
    if (*it % 2 == 0)
        it = a.erase(it);   // 删除后不再 ++it
    else
        ++it;
}
```

### 5.4 用 `list` 改写逢 7 淘汰

```cpp
#include <iostream>
#include <list>
using namespace std;

bool judge(int x) {
    if (x % 7 == 0) return true;
    while (x > 0) {
        if (x % 10 == 7) return true;
        x /= 10;
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    list<int> stu;
    for (int i = 1; i <= n; ++i) stu.push_back(i);

    auto it = stu.begin();
    int num = 1;
    while (!stu.empty()) {
        if (judge(num)) {
            cout << *it << '\n';
            it = stu.erase(it);
        } else {
            ++it;
        }
        if (!stu.empty() && it == stu.end()) it = stu.begin();
        ++num;
    }
}
```

`list.erase(it)` 在**已知迭代器**时删除为 `O(1)`；`vector.erase()` 通常为 `O(n)`。但 `list` 需要更多节点内存，也不能 `stu[j]`，小数据不一定比 `vector` 快。

## 6. 环状数据结构的几种实现

**标准 C++ 没有自带 `circular_list` 容器。** 常见选择：

| 实现 | 如何回到开头 | 优点 |
|---|---|---|
| `vector` | `j = (j + 1) % size()` | 简单、支持下标 |
| `list` | `if (it == end()) it = begin()` | 当前位置删改方便 |
| 自实现循环链表 | 尾节点的 `next = head` | 节点天然连成环 |
| 环形缓冲区 | 用固定容量的环状下标 | 适合队列/缓冲数据 |

真正的**单向循环链表**节点形式：

```cpp
struct Node {
    int data;
    Node* next;
};
// 构造完整链表后令 tail->next = head;
```

手写时还需正确管理内存分配、删除、空链表和仅一个节点的情况。对这次模拟题，`std::list` 更省事。

## 7. 结构体与 `sort`：成绩排名

当每个学生既有学号，又有成绩时，需要**把相关字段绑定在一起排序**：

```cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;

struct Student {
    int id;
    double score;
};

bool cmp(const Student& a, const Student& b) {
    return a.score > b.score; // 成绩降序
}

int main() {
    int n, k;
    cin >> n >> k;
    Student stu[105];
    for (int i = 0; i < n; ++i)
        cin >> stu[i].id >> stu[i].score;

    sort(stu, stu + n, cmp);
    printf("%d %g\n", stu[k - 1].id, stu[k - 1].score);
}
```

**关键：** 第 `k` 名的数组下标是 `k-1`。`cmp` 中 `>` 表示降序，`<` 表示升序。若成绩相等时还要求按学号排序，必须补充次级比较条件；如果题目未规定并列名次顺序，不能自行断言唯一答案。

`sort` 时间复杂度一般为 `O(n log n)`；只求第 `k` 个元素时还可以研究 `nth_element()`（平均线性时间）。

## 8. 整数位数和数位和

### 8.1 求整数的位数

**方法 A：转字符串，最省事**

```cpp
int n = -12345;
string s = to_string(n);
int digits = (int)s.size() - (n < 0); // 5
```

**方法 B：循环除以 10，最稳妥**

```cpp
int n = 12345;
int digits = 0;
do {
    n /= 10;
    ++digits;
} while (n != 0);
```

`do...while` 能正确处理 `n=0`，得到 1 位。`(int)log10(n)+1` 只适用于正数，并可能受浮点误差影响，不是整数题的首选。

### 8.2 求各位数字之和

```cpp
int digit_sum(int x) {
    int sum = 0;
    while (x > 0) {
        sum += x % 10; // 取末位
        x /= 10;       // 去末位
    }
    return sum;
}
```

这是**数位处理母题**：可推广至“是否包含某数字”“数字出现次数”“逆序数字”“回文数”等。

## 9. `scanf` / `printf` 的常见用法

### 9.1 格式符速查

| 类型 | `scanf` | `printf` |
|---|---|---|
| `int` | `%d` | `%d` |
| `long long` | `%lld` | `%lld` |
| `float` | `%f` | `%f`（`float` 实参会提升为 `double`） |
| `double` | `%lf` | `%f` 或 `%g` |
| `char` | `%c` | `%c` |
| `char[]`（C 字符串） | `%s`（注意容量） | `%s` |

```cpp
int a;
double b;
scanf("%d,%lf", &a, &b); // 适用于如 12,3.5 的输入
printf("%d %.2f\n", a, b); // 保留2位小数
printf("%d %g\n", a, b);   // %g 使用较简洁的数字格式
```

- `scanf()` 给普通变量传**地址**：`&a`、`&b`。
- 逗号是字面字符：`scanf("%d,%d",...)` 期望输入中出现逗号。
- `scanf(" %c", &ch)`：`%c` 前加空格可以跳过换行等空白。
- `scanf("%s", buf)`：字符数组名本身可作为地址，**不用 `&buf`**；实际应用应限制最大宽度，如 `char buf[100]; scanf("%99s", buf);`。
- 混用 `cin`/`scanf` 时注意缓冲与同步设置；采用 `ios::sync_with_stdio(false)` 后不要再混用两套输入系统。

### 9.2 多组输入直到 EOF

```cpp
int x;
while (scanf("%d", &x) == 1) {
    // 每成功读到一个整数，处理一次
}
```

`scanf()` 返回成功赋值的项数。比仅检查 `!= EOF` 更适合避免遇到无效字符时原地重复读取。

## 10. 整数筛选与按数位和分组

题目要求：寻找严格位于 `m` 与 `n` 之间、且为 `k` 的倍数的整数；再按**各位数字之和**分组，每组内部数字升序，组间按数位和升序。

### 10.1 自己原来的错误

```cpp
if (digit_sum(i) == k * t) // 错误：变成判断数位和是k的倍数
```

应该拆成两个独立条件：

```cpp
if (i % k == 0 && digit_sum(i) == t)
```

另外，严格在 `m` 与 `n` 之间，起点是 `m+1`，终点条件是 `i<n`。当 `k=3` 时，数字与数位和模 3 同余，可能**恰好掩盖错误**，因此要换 `k=2` 等数据测试。

### 10.2 保留双层循环的简洁写法

```cpp
#include <iostream>
#include <cstdio>
using namespace std;

int digit_sum(int x) {
    int ans = 0;
    while (x > 0) {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

int main() {
    int m, n, k;
    scanf("%d,%d,%d", &m, &n, &k);

    // 在题目 1 <= m < n <= 10000、k>0 的约束下
    for (int t = 1; t <= 36; ++t) {
        bool first = true;
        for (int i = m + 1; i < n; ++i) {
            if (i % k == 0 && digit_sum(i) == t) {
                if (!first) cout << ',';
                cout << i;
                first = false;
            }
        }
        if (!first) cout << '\n';
    }
}
```

**为什么不需要排序？** 外层 `t` 升序保证组间有序；内层 `i` 升序保证组内有序。`bool first` 避免多余逗号。题目上界为 `10000` 时，候选数不超过 `9999`，最大数位和是 36。

也可以用 `vector<int> group[37]` 桶分组：单次扫描数字，按数位和加入对应桶，然后按桶下标输出。双重循环省空间、直观；桶分组避免重复扫描。

## 11. 叉积判断严格凸四边形

### 11.1 几何变成符号判断

按顶点顺序给出四边形 `A,B,C,D`，严格凸四边形沿边走一圈时，应当**四次都向左转或四次都向右转**；三点共线（叉积为 0）不能算严格凸。

对三点 `a,b,c`：

\[
\operatorname{cross}(a,b,c)=(b_x-a_x)(c_y-b_y)-(b_y-a_y)(c_x-b_x).
\]

- 正数：左转；负数：右转；零：共线。
- 顺序检查 `ABC`、`BCD`、`CDA`、`DAB`，四个结果严格同号即满足判断。

### 11.2 代码模板

```cpp
#include <iostream>
using namespace std;

struct Point {
    long long x, y;
};

long long cross(Point a, Point b, Point c) {
    return (b.x - a.x) * (c.y - b.y)
         - (b.y - a.y) * (c.x - b.x);
}

int main() {
    Point a, b, c, d;
    while (cin >> a.x >> a.y >> b.x >> b.y
               >> c.x >> c.y >> d.x >> d.y) {
        long long s1 = cross(a, b, c);
        long long s2 = cross(b, c, d);
        long long s3 = cross(c, d, a);
        long long s4 = cross(d, a, b);

        bool pos = s1 > 0 && s2 > 0 && s3 > 0 && s4 > 0;
        bool neg = s1 < 0 && s2 < 0 && s3 < 0 && s4 < 0;
        cout << ((pos || neg) ? "yes" : "no") << '\n';
    }
}
```

这里使用 `long long` 降低坐标差及乘法溢出的风险（仍需符合题目坐标范围）。这是经典的“**几何关系 → 叉积 → 整数符号**”转换，可迁移到共线、左右侧判断、凸包等题。

## 12. 区间标记：校门外的树

**题目特点：** 在坐标 `0,1,...,L` 处各有一棵树，若干闭区间 `[a,b]` 内的树被移走，统计剩余棵数。

### 12.1 本次两个关键错误

```cpp
int t[10005] = {1};
```

不是全为 1；只有 `t[0]=1`，其余元素会被初始化为 0。

```cpp
for (int i = 1; i <= L; ++i) // 漏掉第0棵树
```

正确范围是 `0..L`，一共 `L+1` 棵树。

### 12.2 修正版

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int L, M;
    cin >> L >> M;
    int tree[10005];
    fill(tree, tree + L + 1, 1);

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        for (int j = a; j <= b; ++j) tree[j] = 0;
    }

    int sum = 0;
    for (int i = 0; i <= L; ++i)
        if (tree[i]) ++sum;
    cout << sum << '\n';
}
```

重复标记为 0 不会造成重复扣除，因此不用 `if (tree[j] != 0)`。可迁移到区间覆盖、占用标记、座位状态等题。

## 13. 三维点对枚举与距离排序

给出 `n` 个三维点，枚举全部**无序点对**，按距离从大到小输出。

### 13.1 枚举每一对恰好一次

```cpp
for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j) {
        // 处理第 i、j 个点
    }
```

总计 `n(n-1)/2` 个点对。`j=i+1` 避免重复 `AB/BA`，也避免 `AA`。

### 13.2 用距离平方比较

\[
d^2=(x_1-x_2)^2+(y_1-y_2)^2+(z_1-z_2)^2.
\]

因为 `sqrt()` 在非负数上单调递增，按 `d²` 排序等价于按 `d` 排序，输出时再开平方即可。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

struct Point { long long x, y, z; };
struct PairInfo { int i, j; long long d2; };

int main() {
    int n;
    cin >> n;
    vector<Point> p(n);
    for (auto& x : p) cin >> x.x >> x.y >> x.z;

    vector<PairInfo> pairs;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long dx = p[i].x - p[j].x;
            long long dy = p[i].y - p[j].y;
            long long dz = p[i].z - p[j].z;
            pairs.push_back({i, j, dx*dx + dy*dy + dz*dz});
        }
    }

    stable_sort(pairs.begin(), pairs.end(),
        [](const PairInfo& a, const PairInfo& b) {
            return a.d2 > b.d2;
        });

    for (const auto& e : pairs) {
        const Point& a = p[e.i];
        const Point& b = p[e.j];
        printf("(%lld, %lld, %lld)-(%lld, %lld, %lld)=%.2f\n",
               a.x, a.y, a.z, b.x, b.y, b.z,
               sqrt((double)e.d2));
    }
}
```

`stable_sort()` 允许**距离相同时保持原枚举顺序**；若题目有明确的同距离排序规则，则应按要求设计比较函数。注意平方和仍须落在 `long long` 有效范围内。

## 14. 二维字符数组、`string` 与字典序

### 14.1 `char` 二维数组

```cpp
char a[3][4] = {
    {'a','b','c','d'},
    {'e','f','g','h'},
    {'i','j','k','l'}
};
cout << a[1][2]; // g
```

如果每行当作 C 字符串使用，必须给结尾 `\0` 留空间：

```cpp
char words[3][10] = {"hello", "world", "C++"};
cout << words[0];    // hello
cout << words[0][1]; // e
```

### 14.2 `string` 数组也可以使用两个下标

```cpp
string s[3] = {"abc", "def", "ghi"};
cout << s[1][2]; // f
```

这里 `s[1]` 是字符串 `"def"`，第二个下标选它的字符。这不等于 `string a[3][4]`（真正的二维**字符串**数组，每个格子都是一个完整的字符串）。

动态字符矩阵常用：

```cpp
vector<string> grid(n);
for (int i = 0; i < n; ++i) cin >> grid[i];
```

### 14.3 字典序排序

```cpp
#include <algorithm>
#include <string>
#include <vector>

string a[3] = {"banana", "apple", "cat"};
sort(a, a + 3); // apple, banana, cat

vector<string> v = {"dog", "apple", "cat"};
sort(v.begin(), v.end());
sort(v.rbegin(), v.rend()); // 逆序字典序

string s = "dcba";
sort(s.begin(), s.end()); // "abcd"，这是字符内部排序
```

**字典序规则：** 从左到右比较第一个不同字符；如果一方是另一方的前缀，短的排前面。默认比较区分大小写，通常大写英文字母排在小写字母前；如果要求忽略大小写，要自定义比较规则。

`char[][]` 不适合直接用普通 `sort(a,a+n)` 排序整行；若需要排序多个单词，优先用 `string[]` 或 `vector<string>`。

## 15. 一行输入、单词倒序和 `stringstream`

### 15.1 为什么 `while (cin >> word)` 不会按 Enter 结束？

```cpp
while (cin >> word) {
    // 持续读到 EOF 或出错
}
```

`operator>>` 会跳过空格、换行、Tab，所以 Enter 只是提供一个分隔符；程序还会等待下一个单词。

手动输入 EOF：Windows 常用 `Ctrl+Z` 后 Enter；Linux/macOS 终端常用 `Ctrl+D`。在线评测输入通常自动到达 EOF。

### 15.2 只读一行，使用 `getline`

```cpp
string line;
getline(cin, line); // 遇到换行就结束本次读取
```

如果前面先写了 `cin >> n`，残留的换行会影响 `getline`，稳妥写法：

```cpp
#include <limits>
cin >> n;
cin.ignore(numeric_limits<streamsize>::max(), '\n');
getline(cin, line);
```

不要依赖 `cin.peek() == '\n'` 来判断一行结束：行末若有空格，就会判断失误。

### 15.3 `stringstream`：把字符串当作输入流

```cpp
#include <sstream>
#include <string>

string line = "I love C++";
stringstream ss(line);
string word;
while (ss >> word) {
    // 依次得到 I、love、C++
}
```

- `stringstream` 可读可写；`istringstream` 专门读，`ostringstream` 专门写。
- `ss >> word` 自动跳过连续空白；若必须保留原空格数量，不宜直接用它拆词。

### 15.4 单词倒序：`getline + stringstream + vector`

```cpp
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

int main() {
    string line, word;
    getline(cin, line);
    stringstream ss(line);

    vector<string> words;
    while (ss >> word) words.push_back(word);

    for (int i = (int)words.size() - 1; i >= 0; --i) {
        if (i != (int)words.size() - 1) cout << ' ';
        cout << words[i];
    }
}
```

原先常见错误：

```cpp
for (int i = s.size(); i > 0; --i) cout << s[i];
```

`size()` 是**个数**，最后有效下标是 `size()-1`；`i>0` 还会漏掉第 0 项。反向遍历时注意空容器和无符号 `size_t` 的问题。

### 15.5 用 `char` 数组倒序也可以

最直观的方法是先用 `cin.getline()` 读一行，再从字符串末尾往前定位每个单词；倒序的是**单词顺序**，单词内部字符顺序不变。也可以用二维 `char` 数组储存拆出的单词，但要留足 `\0` 和单词长度空间。

```cpp
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    char s[10005];
    cin.getline(s, sizeof(s));
    int i = (int)strlen(s) - 1;
    bool first = true;

    while (i >= 0) {
        while (i >= 0 && s[i] == ' ') --i;
        if (i < 0) break;
        int r = i;
        while (i >= 0 && s[i] != ' ') --i;

        if (!first) cout << ' ';
        for (int j = i + 1; j <= r; ++j) cout << s[j];
        first = false;
    }
}
```

这个示例以普通空格为单词分隔符，输入行长度不能超过缓冲区容量；若题目规定了 Tab 等分隔符，则要相应修改条件。

## 16. 链接错误与常用调试习惯

### 16.1 `[Error] ld returned 1 exit status`

它意味着**链接失败**，不是根因。要往上找更早的提示：

| 提示 | 常见原因 |
|---|---|
| `undefined reference to ...` | 只有函数声明没有定义，或未链接相应代码 |
| `multiple definition of ...` | 同一全局符号被定义多次 |
| `cannot open output file ... Permission denied` | Windows 上 `.exe` 仍被占用或没有写入权限 |
| `undefined reference to WinMain` | 入口或编译/项目配置不匹配等 |

联系此前的 `while(cin >> word)`：如果旧程序仍在等待输入，Windows 上可能导致下一次编译无法覆盖正在运行的 `.exe`。先关闭旧程序，再看具体链接报错。

### 16.2 本日总结的调试顺序

1. **检查输入是否成功：** 分隔符是逗号还是空格？一组还是多组？按 Enter 还是 EOF？
2. **检查循环边界：** `0..L`、`m+1..n-1`、`i<size()`、`while(x>0)`。
3. **检查结构是否改变：** `erase()` 后 `size()`、下标和迭代器是否有效。
4. **检查输出格式：** 有没有额外调试行、行末多逗号、精度不符合要求。
5. **设计反例：** `judge(71)`、`k=2`、仅剩一个学生、删除最后一个、空行、行末有多个空格。
6. **最后分析效率：** 先有正确的小规模解，再考虑 `list`、桶分组、`nth_element` 等优化。

## 17. 知识卡片、复杂度与后续练习

### 17.1 常用写法速查

| 目标 | 典型写法 |
|---|---|
| 删除 `vector` 当前下标 | `v.erase(v.begin()+j)` |
| 遍历中删 `list` 当前节点 | `it = lst.erase(it)` |
| 循环访问下一位 | `j=(j+1)%n`（要求 `n>0`） |
| `list` 到尾后回头 | `if(it==lst.end()) it=lst.begin();`（要求非空） |
| 判断数字是否含 `7` | 逐位 `%10`、`/10` |
| 数位和 | `sum+=x%10; x/=10;` |
| `string` 字典序排序 | `sort(a,a+n)` / `sort(v.begin(),v.end())` |
| 按分数降序 | `sort(..., cmp)`，`cmp` 返回 `a.score>b.score` |
| 填充数组 | `fill(a, a+n, 1)` |
| 读取完整一行 | `getline(cin,line)` |
| 对一行逐词提取 | `stringstream ss(line); while(ss>>word)` |
| 逐对枚举 | `for(i=0;i<n;i++) for(j=i+1;j<n;j++)` |
| 两点三维距离排序 | 比较 `d²`，输出 `sqrt(d²)` |
| 三点转向 | `cross(a,b,c)` 的正负 |
| 按 EOF 读一个整数 | `while(scanf("%d", &x)==1)` |

### 17.2 复杂度直觉

| 操作 | 典型时间复杂度 |
|---|---|
| `vector` 按下标访问 | `O(1)` |
| `vector` 已知位置删除 | `O(n)` |
| `list` 已知迭代器删除 | `O(1)` |
| 线性查找一个值 | `O(n)` |
| `sort` / `stable_sort` | `O(n log n)` |
| 枚举所有无序点对 | `O(n²)` |
| 本次校门外的树逐区间标记 | `O(L + 区间长度之和)` |
| 固定最多 36 种数位和，双层扫描 | `O(36(n-m))`，本题上界下相当于线性 |

### 17.3 复习建议（按优先级）

- [ ] **高优先级：** 不看笔记，手写“逢 7 淘汰”的 `vector` 版；解释删除时为何不 `j++`。
- [ ] **高优先级：** 写出 `list` 版，并解释 `end()`、`*it`、`it = erase(it)`。
- [ ] **高优先级：** 对 71、107、140、98 测试 `judge()`，理解数位处理的边界。
- [ ] **中优先级：** 用 `getline + stringstream` 完成一行单词倒序，再尝试只用一个 `char` 数组。
- [ ] **中优先级：** 重做“数位和分组”，分别用双重循环和桶分组实现。
- [ ] **中优先级：** 不看答案写出二维叉积函数，并解释正、负、零三种几何含义。
- [ ] **中优先级：** 用 `struct + sort` 完成成绩排名和三维点对距离排序。
- [ ] **低优先级：** 查阅 `std::list::splice()`、`std::rotate()`、`std::nth_element()` 的使用场景。

---

## 一句话复盘

今天真正反复出现的主题不是某一个 STL 函数，而是：**先明确“数据是什么、位置在哪里、顺序如何变化”，再选数组 / `vector` / `list` / 字符串 / 结构体表达它。** 编写模拟题时，输入范围、下标合法性、删除后的状态和输出格式，比单纯记忆语法更重要。
