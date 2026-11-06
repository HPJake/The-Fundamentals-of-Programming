计算概论 A 笔记

构体的定义

```c++
struct Sample { //注意sample可能与C++内置函数名重合
    int num;       // 培养皿编号
    int before;    // 试验前细菌数量
    int after;     // 试验后细菌数量
    double rate;   // 繁殖率
};
```

结构体的自定义排序

```c++
bool cmp(Sample a, Sample b) {
    return a.rate < b.rate;
}
```

延伸

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



未知数据组数，读取直到EOF

```c++
while (cin >> x)
while (cin >> dx >> dy) //一次输入两个数据
```

Note: 地终端测试时，输入"EOF"结束输入



未知数据组数，给定结束标记

e.g. 以 0 0 为结束标记

```c++
while (cin >> x >> y && (x != 0 || y != 0))
```

