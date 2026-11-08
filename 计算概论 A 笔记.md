# 计算概论A 期中笔记

## 结构体

### 结构体的定义

```c++
struct Sample { //注意sample(小写)可能与C++内置函数名重合
    int num;       // 培养皿编号
    int before;    // 试验前细菌数量
    int after;     // 试验后细菌数量
    double rate;   // 繁殖率
};
```

### 结构体的自定义排序

```c++
bool cmp(Sample a, Sample b) {
    return a.rate < b.rate;
}
```

#### 延伸

| 写法              | 含义         | 是否复制 | 能否修改原数据 |
| ----------------- | ------------ | -------- | -------------- |
| `Sample a`        | 值传递       | 是       | 否             |
| `Sample& a`       | 引用传递     | 否       | 是             |
| `const Sample& a` | 常量引用传递 | 否       | 否             |

常量引用传递

```c++
bool cmp(const Sample& a, const Sample& b) {
    return a.rate < b.rate;
}
```



## 数据的读取

### 未知数据组数，读取直到EOF

```c++
while (cin >> x)
while (cin >> dx >> dy) //一次输入两个数据
```

Note: 地终端测试时，输入"EOF"结束输入



### 未知数据组数，给定结束标记

e.g. 以 0 0 为结束标记

```c++
while (cin >> x >> y && (x != 0 || y != 0))
```



## `scanf()` 格式化读取

需调用头文件 `<cstdio>`

**Example**

```c++
// 输入：2026-11-08
scanf("%d-%d-%d", &year, &month, &day);
```

| 数据类型    | 格式说明符 | 示例                 |
| ----------- | ---------- | -------------------- |
| `int`       | `%d`       | `scanf("%d", &a);`   |
| `long long` | `%lld`     | `scanf("%lld", &x);` |
| `float`     | `%f`       | `scanf("%f", &x);`   |
| `double`    | `%lf`      | `scanf("%lf", &x);`  |
| `char`      | `%c`       | `scanf("%c", &c);`   |
| `char[]`    | `%s`       | `scanf("%19s", s);`  |



#### 进阶用法

##### 1. 读取到换行符之前

```
char s[100];

scanf("%99[^\n]", s);
```

`[^\n]` 的意思是：读取所有不是换行符的字符。

因此它可以读取包含空格的一行文字。

但注意：它不会消耗末尾的换行符；若一开始就遇到换行符，转换会失败。平时读取整行，更建议使用 `getline()`。

##### 2. 只读取数字字符

```
char s[100];

scanf("%99[0-9]", s);
```

##### 3. 读取到指定分隔符之前

例如：

```
char s[100];

scanf("%99[^,]", s);
```

输入：

```
apple,banana
```

读取结果是 `"apple"`。

注意：逗号没有被消耗，如果接下来还要读取，需要另外处理它。



## `printf()` 格式化输出

有一个容易和 `scanf` 混淆的区别：

| 类型     | `scanf` | `printf` |
| -------- | ------- | -------- |
| `float`  | `%f`    | `%f`     |
| `double` | `%lf`   | `%f`     |

#### 科学计数法

```c++
//%e
//printf("%e", x);

double x = 1234.567;
printf("%.2e\n", x);
```

#### 输出 string

```c++
string s = "hello";
printf("%s", s.c_str()); // 正确
```

不能直接把 `std::string` 对象传给 `%s`。

### 控制小数位

`%.nf`：保留 n 位小数

```c++
double x = 3.1415926;

printf("%.2f\n", x);
printf("%.3f\n", x);
printf("%.0f\n", x);
```



## vector

### vector元素去重

```c++
v.sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());
```

unique()返回一个迭代器（iterator），指向去重后有效区间的末尾

| 函数       | 含义                                           |
| ---------- | ---------------------------------------------- |
| `sort()`   | 排序，让相同元素相邻                           |
| `unique()` | 将相邻重复元素移到有效区间之后，返回新逻辑结尾 |
| `erase()`  | 真正删除多余元素，缩短 vector                  |



## 字符串

| 输入方式            | 读取到哪里停止 | 能读取空格吗？ |
| ------------------- | -------------- | -------------- |
| `cin >> s`          | 遇到空白字符   | 否             |
| `getline(cin, s)`   | 遇到换行符     | 是             |
| `cin.getline(a, n)` | 遇到换行符     | 是             |
| `cin.get(c)`        | 读取一个字符   | 是             |

### 输入一个单词/无空格的字符串

```c++
string s;
cin >> s;

/* Example
Input: hello world
Output: hello
*/
```

### 输入一行，包括空格

```C++
string s;
getline(cin, s);

char s[100]; 
cin.getline(s, 100); //100 是字符数组的容量，通常最多读取 99 个普通字符，最后保留一个位置给 '\0'
```

### 读取单个字符

```c++
char c;
cin.get(c);
```



### `cin` 和 `getline` 混用时需特别注意

```C++
int n;
string s;

cin >> n;
getline(cin, s);

//cin.ignore(); //丢弃下一个字符，即遗留的换行符 (先当这一行没加)

cout << "[" << s << "]";

/*
Input:
3
Hello World

Output: EmptyOutput
*/
```

 `cin >> n` 读取 `3` 后，换行符还留在输入缓冲区中。

接下来的 `getline()` 直接遇到换行符，于是读取到空字符串。

解决方法：在 `cin >> n` 后面加上 `cin.ignore()`

相关题目：判断是否为C语言的合法标识符(期中)



### 连续读取多行字符串

```c++
string s;

while (getline(cin, s)) {
    cout << s << endl;
}
```



### `getline()` 进阶用法

它实际上有第三个参数 `getline(cin, s, delimiter);`

其中 `delimiter` 是一个 `char` 类型的分隔符。

```c++
//读取到逗号就停止
string s;
getline(cin, s, ',');
cout << s << endl;

//getline() 遇到逗号就停止。
//逗号会被读取并丢弃，不会存进 s。
```

#### 使用 `getline()` 分割字符串
例如：

```c++
string a, b, c;
getline(cin, a, ',');
getline(cin, b, ',');
getline(cin, c);
```



### 字符串的分割

#### 按空格分割

需要使用stringstream，调用头文件 `<sstream>`

```c++
string line, word;
getline(cin, line);
stringstream ss(line);

while(line >> word){
	cout << word << endl;
}
```

#### 按其他字符分割，如逗号

```c++
string s = "apple,banana,orange";

stringstream ss(s);
string word;

while (getline(ss, word, ',')) {
    cout << word << endl;
}
```



### string数组

| 写法                                             | 存储内容     | 元素类型            |
| ------------------------------------------------ | ------------ | ------------------- |
| `string a[3][4]`                                 | 3×4 个字符串 | `string`            |
| `vector<vector<string>> a(n, vector<string>(m))` | n×m 个字符串 | `string`            |
| `vector<string> a(n)`                            | n 行字符序列 | `a[i][j]` 为 `char` |



### string相关的函数

| 功能         | 函数 / 写法                      | 作用                         |
| ------------ | -------------------------------- | ---------------------------- |
| 长度         | `s.size()` / `s.length()`        | 返回字符串长度               |
| 查找         | `s.find("abc")`                  | 返回第一次出现的下标         |
| 截取         | `s.substr(pos, len)`             | 从 `pos` 开始取 `len` 个字符 |
| 删除         | `s.erase(pos, len)`              | 删除指定位置的字符           |
| 插入         | `s.insert(pos, "abc")`           | 在指定位置插入字符串         |
| 替换         | `s.replace(pos, len, "abc")`     | 替换指定区间                 |
| 追加         | `s.append("abc")` / `s += "abc"` | 在末尾添加字符串             |
| 判空         | `s.empty()`                      | 判断是否为空                 |
| 清空         | `s.clear()`                      | 清空字符串                   |
| 查找最后一次 | `s.rfind("abc")`                 | 返回最后一次匹配的起始位置   |
| 交换         | `s.swap(t)`                      | 交换两个字符串               |

#### 查找子串

```c++
string s = "abcabc";
cout << s.find("bc");     // 1
cout << s.find("bc", 2);  // 4
```

`find(目标, 起始位置)` 从指定下标开始搜索。找不到时返回 `string::npos`，千万别用 `> 0` 判断是否找到。



### 字符串 - 大小写字母转换

`tolower()` `toupper()` 函数，需调用头文件 `<cctype>`

```c++
for (char &c : s) { //使用引用传递，修改c就能修改s
    c = tolower(c); //改成小写
}
```



## `sort` 函数

```c++
//数组array
int a[] = {5, 2, 8, 1, 3};
int n = 5;

//vector
sort(a, a + n);
sort(a, a + n, greater<int>());

vector<int> v = {5, 2, 8, 1, 3};

sort(v.begin(), v.end()); //默认升序
sort(v.begin(), v.end(), greater<int>()); //降序
sort(v.begin() + 1, v.begin() + 4); //只排部分区间，左闭右开

//string
string s = "dbca";
sort(s.begin(), s.end());
sort(s.begin(), s.end(), greater<char>());
```

注意排序区间是左闭右开：
$$
[\text{begin}+1,\ \text{begin}+4)
$$
因此只排序下标 `1、2、3`



### `sort()` 与 `stable_sort()` 

当两个元素的排序优先级相同时，是否保证它们保持原来的先后顺序？

`sort()`：不保证原来的相对顺序。

`stable_sort()`：保证原来的相对顺序。



### 对元素为pair的vector进行排序

`pair` 默认先比较 `first`，如果相同，再比较 `second`！使用 `stable_sort()` 也一样



## 高精度乘法

```c++
#include <iostream>
#include <cstring>
using namespace std;

int main() {
    // 使用字符数组读取两个超大整数
    // 这里假设每个整数最多 1000 位
    char sa[1005], sb[1005];
    cin >> sa >> sb;

    // 倒序存储两个乘数
    int a[1005] = {0};
    int b[1005] = {0};

    // 结果最多 2000 位，留出额外空间
    int c[2010] = {0};

    int n = strlen(sa);
    int m = strlen(sb);

    // 1. 将字符数组转成 int 数组
    // 个位放在下标 0
    for (int i = 0; i < n; i++) {
        a[i] = sa[n - 1 - i] - '0';
    }

    for (int i = 0; i < m; i++) {
        b[i] = sb[m - 1 - i] - '0';
    }

    // 2. 逐位相乘，累加到对应的位置
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c[i + j] += a[i] * b[j];
        }
    }

    // 3. 统一处理进位
    for (int i = 0; i < n + m; i++) {
        c[i + 1] += c[i] / 10;
        c[i] %= 10;
    }

    // 4. 找到结果的最高非零位
    int len = n + m;

    while (len > 1 && c[len - 1] == 0) {
        len--;
    }

    // 5. 从最高位向最低位输出
    for (int i = len - 1; i >= 0; i--) {
        cout << c[i];
    }

    cout << '\n';

    return 0;
}
```

