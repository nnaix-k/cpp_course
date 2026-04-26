# SpO2 题：按照老师标准答案的模块思路来理解

这份笔记解决的问题是：

```text
为什么老师的标准答案会拆成：
debug
ppg
utils
report
main
```

也就是：

```text
不只是“把题做出来”
还要“把题拆得清楚、好维护、好调试”
```

参考：

- [SpO2 solution 目录](https://github.com/jdtournier/cpp_assignment1_spo2/tree/solution/solution)

---

## 1. 老师这份答案一共分成了什么

老师标准答案里主要有这些文件：

```text
debug.h
debug.cpp

ppg.h
ppg.cpp

utils.h
utils.cpp

report.h
report.cpp

spo2.cpp
```

你可以把它理解成：

```text
debug   -> 调试和日志
ppg     -> 读入原始 PPG 数据
utils   -> 通用小工具函数
report  -> 生成输出报告
spo2.cpp -> main，负责串流程
```

---

## 2. 每个模块到底负责什么

---

## 3. `spo2.cpp`：主程序入口

这个文件就是：

```text
main.cpp 的角色
```

它负责：

```text
1. 检查命令行参数
2. 设置 debug 模式
3. 调用 load_PPG()
4. 调用滤波函数
5. 调用 write_report()
6. 用 try/catch 统一处理错误
```

所以你要把它理解成：

```text
主控文件
```

它不负责写所有细节算法，而是：

```text
把整个程序流程串起来
```

---

## 4. `ppg.h / ppg.cpp`：原始数据模块

这个模块负责：

```text
PPG 是什么
怎么从文件里把 PPG 数据读进来
```

### `ppg.h`

这里放：

```cpp
struct PPG {
    std::vector<double> red, ir;
};

PPG load_PPG(const std::string& filename);
```

意思：

```text
告诉别人：
有一个 PPG 类型
还有一个 load_PPG 函数
```

### `ppg.cpp`

这里真正写：

```cpp
PPG load_PPG(const std::string& filename)
{
    ...
}
```

作用：

```text
真正实现：
怎么打开文件
怎么检查第一行是 RED IR
怎么一行行读 red 和 ir
怎么存进 PPG struct
```

### 为什么要单独分这个模块

因为：

```text
“读文件”本身就是一个完整的小任务
```

如果把它塞进 main，会让 main 变长、变乱。

---

## 5. `utils.h / utils.cpp`：通用工具模块

这个模块负责：

```text
那些不是“只属于 PPG 文件格式”
也不是“只属于报告输出”
但程序里反复会用到的小工具
```

老师答案里这里面主要有：

### 1. `filter_moving_average()`

```cpp
std::vector<double> filter_moving_average(const std::vector<double>& vec);
```

作用：

```text
对任意一串 double 数据做 3-point moving average
```

为什么放在 `utils`？

因为它既可以给 red 用，也可以给 ir 用。  
它不是“只属于 red”，也不是“只属于 ir”。

---

### 2. `get_min_max()`

```cpp
struct MinMax { double min, max; };
MinMax get_min_max(const std::vector<double>& data);
```

作用：

```text
给一串数据，返回最小值和最大值
```

为什么放在 `utils`？

因为它是一个非常通用的小功能。

以后很多题都可能复用：

- ECG
- PPG
- image data

---

## 6. `report.h / report.cpp`：输出报告模块

这个模块负责：

```text
把最终结果写到文件里
```

### `report.h`

声明：

```cpp
void write_report(...);
```

### `report.cpp`

实现：

```text
1. 打开输出文件
2. 算 red 的 peak / valley / AC / DC
3. 算 ir 的 peak / valley / AC / DC
4. 算 RR
5. 算 SpO2
6. 分类 status
7. 按要求格式写进 report
```

### 为什么要单独拆出来

因为：

```text
“输出报告”本身也是一个独立任务
```

如果把这些格式化输出都塞进 main，main 会很长。

---

## 7. `debug.h / debug.cpp`：调试模块

这个是你刚刚特别提到的。

老师这里拆一个 `debug` 模块，不是因为题目硬性要求，而是因为：

```text
它能让程序更容易调试、更专业，也更有设计感
```

---

## 8. `debug` 模块到底在做什么

### 1. 开关 verbose mode

老师的 `debug.h` 里有：

```cpp
namespace debug {
    inline bool verbose_mode = false;
}
```

意思：

```text
程序平时默认不输出调试信息
如果开启 verbose mode，就输出更多信息
```

---

### 2. 解析 `-v`

`debug.cpp` 里主要有：

```cpp
void set_verbose_mode (int& argc, char* argv[])
```

它会做的事情是：

```text
如果用户命令里写了 -v
就打开 verbose mode
并把这个 -v 从 argv 里移掉
```

这就是为什么老师 main 一开始写：

```cpp
debug::set_verbose_mode(argc, argv);
```

### 你怎么理解

比如用户运行：

```bash
./spo2 -v input.txt report.txt
```

那 debug 模块会：

```text
1. 发现 -v
2. 打开 debug::verbose_mode
3. 把参数列表整理好
```

这样 main 后面继续用 `argv[1]`、`argv[2]` 时就不会乱。

---

### 3. 输出调试日志

`debug.h` 里还有：

```cpp
inline void log (const std::string& text)
{
    if (verbose_mode)
        std::cerr << "[DEBUG] " << text << "\n";
}
```

这表示：

```text
只有 verbose mode 打开时
debug::log(...) 才真的打印
```

例如：

```cpp
debug::log("loading PPG file ...");
```

作用就是：

```text
在调试时告诉你程序现在进行到哪一步了
```

---

### 4. `VAR(x)` 宏

老师还写了：

```cpp
#define VAR(x) std::cerr << ... << #x << " = " << x << "\n"
```

你现在可以把它理解成：

```text
一个快速查看变量值的小工具
```

例如你写：

```cpp
VAR(rr);
```

它会打印出：

```text
rr = 0.83
```

而且还会带文件名、函数名、行号。

这非常适合调试。

---

## 9. 你考试时需不需要也写 debug 模块？

### 短答案

```text
不一定必须
```

### 更准确地说

如果是考试时间很紧，你完全可以先不单独拆 `debug`，先把题做出来。

但如果题目是 coursework / assignment / take-home / 设计分很重，那：

```text
debug 模块是加分项
```

因为它体现了：

- modularity
- maintainability
- error tracing
- professional style

---

## 10. 你以后自己怎么决定要不要拆 debug

### 情况 A：短题 / 考场限时

可以不拆。

直接用：

```cpp
std::cerr << ...
```

或者临时打印变量。

---

### 情况 B：大题 / assignment / 想拿设计分

可以拆。

你最小可以写成这样：

#### `debug.h`

```cpp
#pragma once
#include <iostream>
#include <string>

namespace debug {
    inline bool verbose_mode = false;

    inline void log(const std::string& text)
    {
        if (verbose_mode)
        {
            std::cerr << "[DEBUG] " << text << "\n";
        }
    }
}
```

#### `debug.cpp`

```cpp
#include "debug.h"
```

然后在 main 里：

```cpp
debug::verbose_mode = true;
debug::log("starting program");
```

这已经够你在自己的作业里用了。

---

## 11. 所以老师这份 SpO2 答案，为什么要拆成这些模块

你可以这样理解：

### `spo2.cpp`

```text
主流程控制
```

### `ppg.*`

```text
负责原始数据读取
```

### `utils.*`

```text
负责通用的小工具函数
```

### `report.*`

```text
负责最后报告输出
```

### `debug.*`

```text
负责调试和 verbose 日志
```

这其实就是在做：

```text
一个模块只负责一种工作
```

这就是老师很喜欢的“结构清楚”。

---

## 12. 你以后可以怎么模仿这个思路

如果以后再遇到综合题，你可以先想：

```text
哪些部分是：
1. 主流程
2. 原始数据读入
3. 通用工具
4. 报告输出
5. 调试支持
```

然后按这个思路拆。

不一定每题都要全拆出来，但这个思路你要有。

---

## 13. 最后给你一个超短版

```text
spo2.cpp   = main，串流程
ppg.*      = 读 PPG 数据
utils.*    = 通用小函数
report.*   = 写报告
debug.*    = 调试输出、verbose 模式
```

---

## 14. 最重要的一句话

```text
老师把题拆成很多模块，不是为了复杂化，
而是为了让每个文件只做一件事。
```

