# SpO2 题：如何按做题思路一步一步搭结构

这份笔记不是直接给最终答案，而是训练：

```text
看到题目
-> 先想最后 main 想长什么样
-> 再反推 .h
-> 最后补 .cpp
```

---

## 1. 第一步：先把题目翻译成中文步骤

看到题目，我先写：

```text
输入：
- input file
- output file

输出：
- report file

步骤：
1. 读 PPG 文件
2. 对 red 和 ir 做 3-point moving average
3. 找 peak / valley
4. 算 AC / DC
5. 算 ratio of ratios
6. 算 SpO2
7. 分类 status
8. 写 report
```

这一步的目的：

```text
先把题目从一大段英文，变成一条处理流水线
```

---

## 2. 第二步：先想数据要怎么存

一份 PPG 数据至少有两条信号：

- red signal
- ir signal

所以第一反应应该是：

```text
这不是一个单独数字，要打包起来
```

所以想到：

```cpp
struct PPG {
    std::vector<double> red;
    std::vector<double> ir;
};
```

---

## 3. 第三步：再想特征值要怎么存

题目说每条 signal 最后都要得到：

- peak
- valley
- AC
- DC

所以再定义一个：

```cpp
struct SignalFeatures {
    double peak;
    double valley;
    double ac;
    double dc;
};
```

这样后面会清楚很多。

---

## 4. 第四步：先想我希望 main 长什么样

我不先写细节，我先想 main 最后想长成：

```cpp
PPG ppg = load_ppg(input_file);

PPG filtered = filter_ppg(ppg);

SignalFeatures red_features = extract_features(filtered.red);
SignalFeatures ir_features = extract_features(filtered.ir);

double rr = compute_ratio_of_ratios(red_features, ir_features);
double spo2 = compute_spo2(rr);
std::string status = classify_spo2(spo2);

write_report(output_file, input_file, filtered, red_features, ir_features, rr, spo2, status);
```

这一步的意义：

```text
先决定我要“得到什么”
```

---

## 5. 第五步：根据 main 反推 .h

现在我不急着写函数内容。

我先把 `ppg.h` 里的内容列出来：

```cpp
#pragma once
#include <string>
#include <vector>

struct PPG {
    std::vector<double> red;
    std::vector<double> ir;
};

struct SignalFeatures {
    double peak;
    double valley;
    double ac;
    double dc;
};

PPG load_ppg(const std::string& filename);

std::vector<double> moving_average_filter(const std::vector<double>& data);

PPG filter_ppg(const PPG& ppg);

SignalFeatures extract_features(const std::vector<double>& data);

double compute_ratio_of_ratios(const SignalFeatures& red_features,
                               const SignalFeatures& ir_features);

double compute_spo2(double rr);

std::string classify_spo2(double spo2);

void write_report(const std::string& output_file,
                  const std::string& input_file,
                  const PPG& filtered,
                  const SignalFeatures& red_features,
                  const SignalFeatures& ir_features,
                  double rr,
                  double spo2,
                  const std::string& status);
```

---

## 6. 第六步：先搭 main.cpp 骨架

先把 main 串起来：

```cpp
#include <iostream>
#include <string>
#include "ppg.h"

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "ERROR: expected input and output filenames\n";
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    PPG ppg = load_ppg(input_file);

    PPG filtered = filter_ppg(ppg);

    SignalFeatures red_features = extract_features(filtered.red);
    SignalFeatures ir_features = extract_features(filtered.ir);

    double rr = compute_ratio_of_ratios(red_features, ir_features);
    double spo2 = compute_spo2(rr);
    std::string status = classify_spo2(spo2);

    write_report(output_file, input_file, filtered, red_features, ir_features, rr, spo2, status);

    return 0;
}
```

这一步的目标：

```text
先让 main 看起来像一条完整流程
```

---

## 7. 第七步：现在才开始写 .cpp

这时候才开始真正实现函数。

我建议先写最简单的：

1. `compute_spo2`
2. `classify_spo2`
3. `moving_average_filter`
4. `extract_features`
5. `load_ppg`
6. `write_report`
7. `filter_ppg`
8. `compute_ratio_of_ratios`

原因：

```text
先拿最稳、最基础的分
再写稍微长一点的函数
```

---

## 8. 示例：先写 compute_spo2

题目直接给了公式：

```text
SpO2 = 110 - 25 * RR
```

所以先写：

```cpp
double compute_spo2(double rr)
{
    return 110 - 25 * rr;
}
```

---

## 9. 示例：再写 classify_spo2

题目给了分类规则：

- `>= 95` -> Normal
- `90 - 95` -> Low
- `< 90` -> Critical

所以写：

```cpp
std::string classify_spo2(double spo2)
{
    if (spo2 >= 95.0)
    {
        return "Normal";
    }
    else if (spo2 >= 90.0)
    {
        return "Low";
    }
    else
    {
        return "Critical";
    }
}
```

---

## 10. 示例：moving_average_filter

题目要求：

```text
每个点 = (前一个 + 当前 + 后一个) / 3
第一和最后一个不算
```

所以写：

```cpp
std::vector<double> moving_average_filter(const std::vector<double>& data)
{
    std::vector<double> filtered;

    for (int i = 1; i < data.size() - 1; i++)
    {
        filtered.push_back((data[i - 1] + data[i] + data[i + 1]) / 3.0);
    }

    return filtered;
}
```

---

## 11. 示例：filter_ppg

因为 red 和 ir 都要做同样的滤波，所以再包一层：

```cpp
PPG filter_ppg(const PPG& ppg)
{
    PPG filtered;
    filtered.red = moving_average_filter(ppg.red);
    filtered.ir = moving_average_filter(ppg.ir);
    return filtered;
}
```

---

## 12. 示例：extract_features

题目说：

- peak = max
- valley = min
- AC = peak - valley
- DC = valley

所以写：

```cpp
SignalFeatures extract_features(const std::vector<double>& data)
{
    SignalFeatures f;

    f.peak = data[0];
    f.valley = data[0];

    for (int i = 1; i < data.size(); i++)
    {
        if (data[i] > f.peak)
        {
            f.peak = data[i];
        }

        if (data[i] < f.valley)
        {
            f.valley = data[i];
        }
    }

    f.ac = f.peak - f.valley;
    f.dc = f.valley;

    return f;
}
```

---

## 13. 示例：compute_ratio_of_ratios

题目公式：

```text
RR = (AC_red / DC_red) / (AC_IR / DC_IR)
```

所以写：

```cpp
double compute_ratio_of_ratios(const SignalFeatures& red_features,
                               const SignalFeatures& ir_features)
{
    return (red_features.ac / red_features.dc) /
           (ir_features.ac / ir_features.dc);
}
```

---

## 14. 示例：load_ppg

题目文件格式：

```text
RED IR
1025.3 1550.8
1030.1 1548.2
...
```

所以写：

```cpp
PPG load_ppg(const std::string& filename)
{
    std::ifstream infile(filename);

    if (!infile)
    {
        throw std::runtime_error("failed to open file");
    }

    std::string red_label, ir_label;
    infile >> red_label >> ir_label;

    if (red_label != "RED" || ir_label != "IR")
    {
        throw std::runtime_error("invalid file format");
    }

    PPG ppg;
    double red_value, ir_value;

    while (infile >> red_value >> ir_value)
    {
        ppg.red.push_back(red_value);
        ppg.ir.push_back(ir_value);
    }

    return ppg;
}
```

---

## 15. 示例：write_report

题目要求输出：

- 输入文件名
- filtered sample 数量
- red/ir 的 peak, valley, AC, DC
- RR
- SpO2
- status

所以写：

```cpp
void write_report(const std::string& output_file,
                  const std::string& input_file,
                  const PPG& filtered,
                  const SignalFeatures& red_features,
                  const SignalFeatures& ir_features,
                  double rr,
                  double spo2,
                  const std::string& status)
{
    std::ofstream outfile(output_file);

    if (!outfile)
    {
        throw std::runtime_error("failed to open output file");
    }

    outfile << "PPG file: " << input_file << "\n";
    outfile << "Samples available after filtering: " << filtered.red.size() << "\n";

    outfile << "Red signal: Peak = " << red_features.peak
            << " Valley = " << red_features.valley
            << " AC = " << red_features.ac
            << " DC = " << red_features.dc << "\n";

    outfile << "IR signal: Peak = " << ir_features.peak
            << " Valley = " << ir_features.valley
            << " AC = " << ir_features.ac
            << " DC = " << ir_features.dc << "\n";

    outfile << "Ratio of Ratios (RR): " << rr << "\n";
    outfile << "Estimated SpO2: " << spo2 << "%\n";
    outfile << "Status: " << status << "\n";
}
```

---

## 16. 这道题你真正要学会的顺序

```text
题目
-> 先写中文步骤
-> 先想 main 想长什么样
-> 根据 main 反推 struct 和函数声明
-> 最后一个函数一个函数补
```

---

## 17. 三部分关系

### ppg.h

负责：

```text
struct PPG
struct SignalFeatures
所有函数声明
```

### ppg.cpp

负责：

```text
把每个函数真正写出来
```

### main.cpp

负责：

```text
参数检查
调用函数
串流程
```

---

## 18. 最重要的一句话

```text
先决定 main 想要什么
然后让 .h 和 .cpp 去服务 main
```
