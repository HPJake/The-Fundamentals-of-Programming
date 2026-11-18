---
title: "C++ 编程日志｜2026-10-22｜vector · 字符串 · OJ排错"
date: 2026-10-22
type: programming-log
language: C++
tags:
  - 学习日志
  - 计算概论
  - C++
  - Debug
  - STL
  - vector
  - 字符串
  - 数组
  - 排序
  - OJ排错
---

# C++ 编程日志｜2026-10-22

> [!summary] 今日主题
> **数组与 `vector`、去重与删除、ASCII 与字符串、`reverse` / `sort` / `find`、OJ 输出格式与错误排查。** 这份日志根据当天的提问、代码截图和评测报错整理；“实际错误”与“学习中提出的问题”分别标明。

## 0. 今日问题索引

1. **输出不重复数字**：保留首次出现的元素，输出顺序不变。
2. **Wrong Answer：末尾空格**：`Std: '99'`，`Out: '99 '`。
3. **`vector` 基础**：创建、追加、访问、遍历、删除、长度。
4. **删除 `vector` 中指定值**：删所有 `0`，以及删指定的非零常数（如 `5`）；如何仅删第一个。
5. **CompileError：`remove()` 被解释为文件删除函数**。
6. **ASCII 与字符相互转换**。
7. **拼写错误**：`namesapce` / `namespace`。
8. **1079 统计字符数**：找到最高频小写字母，相同时取 ASCII 最小的。
9. **普通数组逆序**：`reverse()` 和 `swap()`。
10. **`sort()` 排序**：数组、`vector`、升序、降序、区间。
11. **字符数组和 `string` 逆序**。
12. **查找子串**：`string::find()`、`npos`、`substr()`、`erase()`。
13. **Wrong Answer：错误判断 `find() > 0`**。

---

## 1. 输出不重复的数字（习题 13-9）

**我问：** 输入 `n` 个整数，按输入顺序输出不重复的数字；重复时只保留首次出现的元素，怎么写最简单？

**解法：** 题目中的数字范围很小（10～99），可用布尔数组记录某个数是否出现过。每个数字只需检查一次，时间复杂度为 `O(n)`。

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, x;
    cin >> n;
    bool seen[101] = {false};
    bool first = true;

    for (int i = 0; i < n; i++) {
        cin >> x;
        if (!seen[x]) {
            if (!first) cout << " ";
            cout << x;
            seen[x] = true;
            first = false;
        }
    }
    cout << '\n';
    return 0;
}
```

测试：

```text
输入：
5
10 12 93 12 75

输出：
10 12 93 75
```

**原理：** `seen[x] == false` 说明数字 `x` 第一次出现；输出后设置 `seen[x] = true`。不能排序，因为排序会破坏题目要求的原输入顺序。

### 实际报错①：Wrong Answer（输出末尾多空格）

评测截图出现：

```text
Wrong Answer
Std: '99'
Out: '99 '
Input:
5
99 99 99 99 99
```

**原因：** 先前给出的简化代码采用了 `cout << x << " ";`，因此最后一个数字后面仍然输出一个空格。该评测环境对这一点进行了比较。这里的空格问题也来自先前建议的输出写法，不是去重思路本身错了。

**改法：** `if (!first) cout << " ";`，先输出*元素之间*的分隔符，再输出元素。这样开头和结尾都不会出现多余空格。

**易错点：** 不应简单用 `i == n - 1` 来判断最后一个待输出数字，因为最后一个*输入*不一定是最后一个*不重复的输出*。

---

## 2. `vector` 的基本操作

**我问：** `vector` 这个数据类型怎么用？

**回答：** `vector` 是大小可动态变化的数组，需要 `#include <vector>`。

```cpp
#include <vector>
using namespace std;

vector<int> a;               // 空 vector
vector<int> b(5);            // 5 个 0
vector<int> c(5, 10);        // 5 个 10
vector<int> d = {1, 2, 3};   // 列表初始化

a.push_back(10);            // 末尾加入 10
a.push_back(20);
// a[0] 是 10，a[1] 是 20
a.pop_back();               // 删除最后一个
// a.size() 返回元素个数；a.empty() 判断是否为空
// a.clear() 清空所有元素
```

常用删除操作：

```cpp
a.erase(a.begin() + i);   // 删除下标为 i 的元素；前提是 i 有效
```

**注意：** `a.size()` 是元素数量，最后一个有效下标为 `a.size() - 1`（仅当非空）。中间 `erase` 后后续元素左移，下标和迭代器可能失效。

---

## 3. 删除 `vector` 中的指定值

**我先问：** 怎么删除所有值为 `0` 的元素？

**推荐写法：** `erase` + 算法 `remove`。

```cpp
#include <vector>
#include <algorithm>
using namespace std;

vector<int> a = {1, 0, 2, 0, 3, 0, 4};
a.erase(remove(a.begin(), a.end(), 0), a.end());
// 得到 {1, 2, 3, 4}
```

**理解：** `std::remove` 并不真正缩短 `vector`；它把需要保留的元素移到前方，并返回新的逻辑结尾。随后 `erase` 才真正删除尾部元素。

### 我进一步澄清的问题

我说“非 0 元素”时，真正想问的是：**删除某个指定的、不等于 0 的常数**，例如把全部 `5` 删除，而不是删除“所有非零数”。此前回答一度将这两种需求混淆。

```cpp
vector<int> a = {1, 5, 2, 5, 3, 5, 4};
int x = 5;
a.erase(remove(a.begin(), a.end(), x), a.end());
// 得到 {1, 2, 3, 4}
```

通用模板：

```cpp
v.erase(std::remove(v.begin(), v.end(), x), v.end());
```

若只想删除**第一个**等于 `x` 的元素：

```cpp
#include <algorithm>
auto it = find(a.begin(), a.end(), x);
if (it != a.end()) a.erase(it);
```

若真的是删除“**所有非零元素**，仅保留 0”，则用条件删除：

```cpp
a.erase(remove_if(a.begin(), a.end(), [](int x) {
    return x != 0;
}), a.end());
```

### 实际报错②：CompileError（`remove` 重名）

出错代码：

```cpp
stu.erase(remove(stu.begin(), stu.end(), stu[j]), stu.end());
```

编译器的关键提示：

```text
error: cannot convert 'std::vector::iterator' to 'const char*'
note: initializing argument 1 of 'int remove(const char*)'
```

**原因：** 很可能缺少 `#include <algorithm>`，使编译器识别到的是 `<cstdio>` 里用于**删除文件**的 `remove(const char*)`，而不是 `<algorithm>` 的移除元素算法。

**改正：**

```cpp
#include <vector>
#include <algorithm>
using namespace std;

// 确保 0 <= j && j < stu.size()
int x = stu[j];
stu.erase(std::remove(stu.begin(), stu.end(), x), stu.end());
```

**额外防坑：** 先用 `int x = stu[j]` 保存待删除值，避免 `remove` 移动元素时改变传入的引用值；之后 `stu.size()` 会变化，使用 `j` 时须重新检查是否越界。

如不使用 `<algorithm>`，也可手动循环删除：

```cpp
for (int i = 0; i < (int)a.size(); ) {
    if (a[i] == 0) {
        a.erase(a.begin() + i); // 删除后不递增 i
    } else {
        i++;
    }
}
```

此法最坏 `O(n^2)`；`erase-remove` 通常为 `O(n)`。

---

## 4. ASCII 码与字符转换

**我问：** ASCII 码怎么转字符？

```cpp
cout << char(65);                // A
cout << static_cast<char>(97);   // a
cout << int('A');                // 65
```

小写字母对应 `97`～`122`，大写字母对应 `65`～`90`，数字字符 `'0'`～`'9'` 对应 `48`～`57`。

**更实用的写法：**

```cpp
int index = 'f' - 'a';       // 5
char c = char('a' + index);  // 'f'
```

区分：`'A'` 是一个字符，`"A"` 是字符串。

### 实际报错③：拼写错误

我问过：

```text
expected nested-name-specifier before 'namesapce'
```

错误写法：

```cpp
using namesapce std;
```

正确写法：

```cpp
using namespace std;
```

**原因：** `namespace` 拼成了 `namesapce`，属于语法/拼写错误。

---

## 5. 1079「统计字符数」

**我问：** 一个只包含 `a`～`z` 的字符串，输出出现次数最多的字母及次数；如果最高次数相同，取 ASCII 最小的字符，怎么写？

**解法：** 用长度为 26 的数组，`cnt[s[i] - 'a']++` 统计字符出现次数，然后从 `a` 到 `z` 扫描最大值。

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        int cnt[26] = {0};  // 每组测试数据都重新清零

        for (char c : s) cnt[c - 'a']++;

        int best = 0;
        for (int i = 1; i < 26; i++) {
            if (cnt[i] > cnt[best]) best = i;
        }
        cout << char('a' + best) << ' ' << cnt[best] << '\n';
    }
    return 0;
}
```

```text
输入：
2
abbccc
adfadffasdf

输出：
c 3
f 4
```

**为什么使用 `>`，而不是 `>=`？** 从 `a` 到 `z` 依次扫描，遇到并列最高次数时不更新 `best`，便会保留 ASCII 更小的那个字符。用 `>=` 则可能错误地选中后面的字母。

**易错点：** `cnt` 要在每一轮测试数据中重新初始化，而不是累计上一组的统计。

---

## 6. 逆序：普通数组、`vector`、字符数组、`string`

**我问：** 怎么把数组元素顺序调转？之后又问字符数组/字符串怎样反转？

### 普通数组

```cpp
#include <algorithm>
int a[] = {1, 2, 3, 4, 5};
reverse(a, a + 5);  // {5, 4, 3, 2, 1}
```

### `vector`

```cpp
vector<int> a = {1, 2, 3, 4, 5};
reverse(a.begin(), a.end());
```

### `string`

```cpp
string s = "abcdef";
reverse(s.begin(), s.end()); // "fedcba"
```

### C 风格字符数组 `char[]`

```cpp
#include <cstring>
#include <algorithm>
char s[] = "abcdef";
reverse(s, s + strlen(s));  // "fedcba"
```

**注意：** `strlen(s)` 不包括末尾的 `\0`；不要把字符串结束符也参与反转。

### 不用 `reverse` 时的交换写法

```cpp
for (int i = 0; i < n / 2; i++) {
    swap(a[i], a[n - 1 - i]);
}
```

只想倒序**输出**而不改变原数据：

```cpp
for (int i = n - 1; i >= 0; i--) cout << a[i];
```

---

## 7. `sort()` 函数

**我问：** `sort` 怎么用？

```cpp
#include <algorithm>
#include <functional>
using namespace std;

int a[] = {5, 2, 8, 1, 3};
sort(a, a + 5);                       // 升序：1 2 3 5 8
sort(a, a + 5, greater<int>());      // 降序：8 5 3 2 1

vector<int> v = {5, 2, 8, 1, 3};
sort(v.begin(), v.end());            // vector 升序
sort(v.begin(), v.end(), greater<int>()); // vector 降序
```

局部排序：

```cpp
int a[] = {9, 5, 3, 8, 1, 7};
sort(a + 1, a + 4); // 只排下标 1、2、3
// 得到 {9, 3, 5, 8, 1, 7}
```

记住：`sort(first, last)` 处理**左闭右开**区间 `[first, last)`；会修改原数组/容器。普通数组的 `a + n` 是尾后位置，不是最后一个元素。

与 `reverse` 区分：

- `reverse`：把原顺序反过来（`cab` → `bac`）。
- `sort`：按大小或字符编码重新排列（`cab` → `abc`）。

---

## 8. `string` 查找子串

**我问：** `string` 如何查找子串？

```cpp
string s = "helloworld";
cout << s.find("world"); // 5
```

**查找结果约定：**

- 返回 `0`：在开头找到。
- 返回 `1`、`2`……：在对应下标找到。
- 返回 `string::npos`：**不存在**。

正确的存在性判断：

```cpp
if (s.find("abc") != string::npos) {
    cout << "Found";
}
```

指定搜索开始位置：

```cpp
s.find("abc", 3);
```

其他相关功能：

```cpp
s.rfind("abc");  // 最后一次出现的位置
s.substr(2, 3);   // 从下标 2 开始，截取 3 个字符
s.erase(2, 3);    // 从下标 2 开始，删除 3 个字符
```

---

## 9. 实际报错④：Wrong Answer（`find() > 0`）

我提交的逻辑（截图）核心是：

```cpp
if (s2.find(s1) > 0)
    cout << s1 << " is substring of " << s2;
else if (s1.find(s2) > 0)
    cout << s2 << " is substring of " << s1;
else if (s1 == s2)
    cout << s1 << " is substring of " << s2;
else
    cout << "No substring";
```

评测给出：

```text
Input:
abc
bca

Std: 'No substring'
Out: 'abc is substring of bca'
```

**根本原因：** `find()` 找不到时返回 `string::npos`，它不是“0”，通常是一个很大的无符号数。所以 `npos > 0` 反而成立。另外，即使子串存在于下标 `0`，`find(...) > 0` 也会错误地认为没找到。

**正确代码：**

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s1, s2;
    cin >> s1 >> s2;

    if (s2.find(s1) != string::npos)
        cout << s1 << " is substring of " << s2;
    else if (s1.find(s2) != string::npos)
        cout << s2 << " is substring of " << s1;
    else
        cout << "No substring";

    return 0;
}
```

**为什么可以删掉 `else if (s1 == s2)`？** 两个字符串相等时，`s2.find(s1)` 返回 `0`，第一条正确条件已经覆盖此情况。

**关键记忆：** 判断存在用 `!= string::npos`；判断不存在用 `== string::npos`；不要写 `> 0`。

---

## 10. 今日错误复盘表

| 类型 | 当时的代码/问题 | 直接原因 | 修正原则 |
|---|---|---|---|
| Wrong Answer | `cout << x << " ";` | 尾部多一个空格 | 先输出分隔符再输出数字；使用 `first` |
| CompileError | `remove(stu.begin(), stu.end(), stu[j])` 报 `const char*` | 大概率没 `#include <algorithm>`，解析到了文件删除函数 | 包含头文件，并用 `std::remove`；复制待删值 |
| 拼写/语法 | `using namesapce std;` | `namespace` 拼错 | 改为 `using namespace std;` |
| Wrong Answer | `s2.find(s1) > 0` | 未找到时 `npos` 是大数；找到开头时返回 0 | 使用 `!= string::npos` |
| 概念澄清 | “删除非 0 元素” | 最初被理解成删全部非零数 | 区分“某个非零常数”与“所有非零元素” |
| 潜在下标问题 | 在 `vector` 中删元素后继续使用 `j` | 删除后元素移动，原下标可能失效 | 检查 `j < size()`，必要时调整索引 |
| 潜在并列问题 | 字母计数最大值用 `>=` | 并列会保留后面的较大字母 | 从小到大扫描，更新条件用 `>` |

## 11. 以后写 OJ 题的检查清单

- [ ] 先读清**输出顺序**要求：保留原顺序还是排序？
- [ ] 分隔符是否只出现在元素**之间**，没有末尾空格？
- [ ] `vector` 删除后，下标和长度有没有发生变化？
- [ ] `remove` / `sort` / `reverse` 是否包含 `<algorithm>`？
- [ ] `find()` 是否用 `string::npos` 判断查找失败？
- [ ] `string` 的下标从 0 开始，返回 0 也是**查找成功**。
- [ ] 多组测试数据时，统计数组是否每组重置？
- [ ] 并列最大值时，是否按题目要求处理？
- [ ] 对关键边界做测试：所有数字相同、没有匹配、匹配位置为 0、空容器、删除连续元素。

## 12. 随手可复制的 C++ 速查模板

```cpp
// 去重并按输入顺序输出（数字范围小）
bool seen[101] = {false};
bool first = true;
// 每读取到 x：
if (!seen[x]) {
    if (!first) cout << ' ';
    cout << x;
    first = false;
    seen[x] = true;
}

// 删除 vector 中所有等于 x 的元素
v.erase(std::remove(v.begin(), v.end(), x), v.end());

// 反转
std::reverse(v.begin(), v.end());
std::reverse(s.begin(), s.end());

// 排序
std::sort(v.begin(), v.end());
std::sort(v.begin(), v.end(), std::greater<int>());

// 字符与下标互转
int i = c - 'a';
char c2 = char('a' + i);

// 子串查找
bool found = (s.find(target) != std::string::npos);
```

> [!note] 一句话总结
> 今天最值得记住的不是某个函数名，而是三个思维习惯：**分清值与位置（`erase` / `remove`）、分清下标 0 与未找到（`find` / `npos`）、认真处理评测的输入输出边界（空格、重复、并列）。**
