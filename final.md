# 综合大题保命模板

这份文件只放一件事：

```text
结合 ECG、SpO2、Assessment2 Image Metrics、Infusion Pump
总结老师综合题的出题思路
并给我一套拿到卷子可以先无脑复制的保命模板
```

重点参考：

- Assessment2 Image Metrics
- Infusion Pump

同时结合：

- ECG
- SpO2

---

## 1. 老师这类综合题的统一出题思路

不管背景怎么变，老师这类题本质上都很像：

```text
load
-> preprocess
-> compute
-> check / classify / alarm
-> output
```

### ECG

```text
load ECG
-> detect peaks
-> compute RR intervals
-> compute metrics
-> classify stress level
-> write report
```

### SpO2

```text
load PPG
-> filter
-> extract features
-> compute ratio of ratios
-> compute SpO2
-> classify
-> write report
```

### Image Metrics

```text
load image
-> compute histogram
-> find threshold
-> make mask
-> segment image
-> compute metrics
-> write report
```

### Infusion Pump

```text
load drug database
-> load patient
-> load treatment plan
-> for each drug compute concentration
-> check toxicity threshold
-> print safe or alarm
```

### 所以拿到卷子先默认

```text
这题一定是：
load -> process -> compute -> check -> output
```

---

## 2. 你拿到卷子先写这 6 句中文

```text
1. 输入是什么文件？
2. 输出是什么？
3. 核心对象是什么？
4. 中间分几步？
5. main 最后按什么顺序调用？
6. 哪一步要检查错误 / 分类 / 报警？
```

---

## 3. 标准三文件结构先这样写

先默认：

```text
topic.h
topic.cpp
main.cpp
```

如果你有余力，再扩成：

```text
topic.h
topic.cpp
utils.h
utils.cpp
report.h
report.cpp
debug.h
debug.cpp
main.cpp
```

---

## 4. `.h` / `.cpp` / `main.cpp` 各写什么

### `topic.h`

写：

```text
struct / class
函数声明
```

模板：

```cpp
#pragma once

#include <string>
#include <vector>

struct DataA {
    // 按题目改
};

struct IntermediateResult {
    // 按题目改
};

struct FinalResult {
    // 按题目改
};

DataA load_data_a(const std::string& filename);

IntermediateResult compute_intermediate(const DataA& data);

FinalResult compute_final_result(const IntermediateResult& mid);

std::string classify_result(const FinalResult& result);
```

---

### `topic.cpp`

写：

```text
真正实现函数
```

模板：

```cpp
#include "topic.h"

#include <fstream>
#include <stdexcept>

DataA load_data_a(const std::string& filename)
{
    std::ifstream infile(filename);

    if (!infile)
    {
        throw std::runtime_error("failed to open input file");
    }

    DataA data;

    // TODO: 按题目格式读取

    return data;
}

IntermediateResult compute_intermediate(const DataA& data)
{
    IntermediateResult mid;

    // TODO: 按题目要求做第一步处理

    return mid;
}

FinalResult compute_final_result(const IntermediateResult& mid)
{
    FinalResult result;

    // TODO: 按题目公式 / 统计逻辑计算

    return result;
}

std::string classify_result(const FinalResult& result)
{
    // TODO: 按题目阈值判断
    return "OK";
}
```

---

### `main.cpp`

写：

```text
参数检查
主流程
try/catch
调用函数
```

模板：

```cpp
#include <iostream>
#include <stdexcept>
#include <string>

#include "debug.h"
#include "topic.h"
#include "report.h"
#include "utils.h"

int main(int argc, char* argv[])
{
    debug::set_verbose_mode(argc, argv);

    if (argc < 3)
    {
        std::cerr << "ERROR: invalid number of arguments\n";
        std::cerr << "usage: program [options] input_file output_file\n";
        return 1;
    }

    try
    {
        std::string input_file = argv[1];
        std::string output_file = argv[2];

        // 如果题目需要多个输入文件：
        // std::string input_file2 = argv[2];
        // std::string input_file3 = argv[3];
        // std::string output_file = argv[4];

        // 1. load
        DataA data_a = load_data_a(input_file);

        // 如果有多个输入对象：
        // DataB data_b = load_data_b(input_file2);
        // DataC data_c = load_data_c(input_file3);

        // 2. preprocess
        IntermediateResult mid = compute_intermediate(data_a);

        // 3. compute
        FinalResult result = compute_final_result(mid);

        // 4. check / classify
        std::string status = classify_result(result);

        // 5. output
        write_report(output_file, result, status);

        if (debug::verbose_mode)
        {
            std::cout << "[debug] status = " << status << "\n";
        }
    }
    catch (const std::exception& err)
    {
        std::cerr << "ERROR: " << err.what() << "\n";
        return 1;
    }

    return 0;
}
```

---

## 5. 先无脑复制的 `report` 模块

### `report.h`

```cpp
#pragma once

#include <string>

#include "topic.h"

void write_report(const std::string& filename,
                  const FinalResult& result,
                  const std::string& status);
```

### `report.cpp`

```cpp
#include "report.h"

#include <fstream>
#include <stdexcept>

void write_report(const std::string& filename,
                  const FinalResult& result,
                  const std::string& status)
{
    std::ofstream outfile(filename);

    if (!outfile)
    {
        throw std::runtime_error("failed to open output file");
    }

    // TODO: 按题目要求写格式
    outfile << "Status: " << status << "\n";
}
```

如果题目不是写 report，而是只要求 print safe / alarm，  
那就把这个模块删掉，直接在 `main.cpp` 里 `std::cout`。

---

## 6. 先无脑复制的 `debug` 模块

这是加分结构，不是必写。

### `debug.h`

```cpp
#pragma once

#include <string>

namespace debug {

extern bool verbose_mode;

void set_verbose_mode(int& argc, char* argv[]);

void log(const std::string& message);

}
```

### `debug.cpp`

```cpp
#include "debug.h"

#include <iostream>

namespace debug {

bool verbose_mode = false;

void set_verbose_mode(int& argc, char* argv[])
{
    int write_index = 1;

    for (int read_index = 1; read_index < argc; read_index++)
    {
        std::string arg = argv[read_index];

        if (arg == "-v")
        {
            verbose_mode = true;
        }
        else
        {
            argv[write_index] = argv[read_index];
            write_index++;
        }
    }

    argc = write_index;
}

void log(const std::string& message)
{
    if (verbose_mode)
    {
        std::cout << "[debug] " << message << "\n";
    }
}

}
```

---

## 7. 四类题怎么往这套里套

### A. ECG

#### `topic.h` 里的核心 struct

```cpp
struct ECG {
    double sampling_interval;
    std::vector<double> V;
};
```

#### 套法

```text
DataA -> ECG
IntermediateResult -> peaks / RR intervals
FinalResult -> rr_stats / rmssd
classify_result -> low / moderate / high
```

#### 常见函数名

```text
load_ecg
detect_r_peaks
compute_RR_intervals
compute_min_mean_max
compute_RMSSD
stress_level
write_report
```

---

### B. SpO2

#### `topic.h` 里的核心 struct

```cpp
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
```

#### 套法

```text
DataA -> PPG
IntermediateResult -> filtered signals / features
FinalResult -> RR / SpO2
classify_result -> Normal / Low / Critical
```

#### 常见函数名

```text
load_ppg
moving_average_filter
extract_features
compute_ratio_of_ratios
compute_spo2
classify_spo2
write_report
```

---

### C. Image Metrics

#### `topic.h` 里的核心 struct

```cpp
struct Image {
    int width;
    int height;
    std::vector<int> pixels;
};

struct Metrics {
    int area;
    double mean;
    double variance;
};
```

#### 套法

```text
DataA -> Image
IntermediateResult -> histogram / threshold / mask
FinalResult -> area / mean / variance
classify_result -> 可以不要，或者改成结果说明
```

#### 常见函数名

```text
load_image
compute_histogram
compute_threshold
make_binary_mask
segment_image
compute_metrics
write_report
```

---

### D. Infusion Pump

#### `topic.h` 里的核心 struct

```cpp
struct Drug {
    std::string name;
    double half_life;
    double distribution_coefficient;
    double toxicity_threshold;
};

struct Patient {
    std::string name;
    double weight;
};

struct Dose {
    std::string drug_name;
    double time;
    double amount;
};
```

#### 套法

```text
DataA -> DrugDatabase / Patient / TreatmentPlan
IntermediateResult -> 某个药物的浓度结果
FinalResult -> safe / unsafe + first breach time
classify_result -> SAFE / ALARM
```

#### 常见函数名

```text
load_drug_database
load_patient
load_treatment_plan
list_drugs_in_plan
find_drug
extract_doses_for_drug
compute_concentration
first_time_threshold_exceeded
```

---

## 8. 重点参考最后两个卷子后总结出的“最常见格式”

这是最重要的一段。

Assessment2 和 Pump 最像老师想要的格式是：

```text
1. main 很短
2. 有清楚的数据结构
3. 输入单独写 load_xxx
4. 中间处理单独写 compute / extract / check
5. 输出单独写 report 或 print
6. 有 error handling
7. 有 modularity
```

所以你拿到卷子时，最应该先做的不是想算法细节，  
而是先把这几个位置占住：

```text
load_xxx
compute_xxx
check_xxx
write_report / print_alarm
```

只要主流程先出来，后面就不会乱。

---

## 9. 关键词 -> 该用什么模板

### 关键词：`input file`, `output file`, `command-line`

用：

```text
argc / argv
ifstream
ofstream
```

模板：

```cpp
if (argc < 3)
{
    std::cerr << "ERROR: expected input and output filenames\n";
    return 1;
}

std::string input_file = argv[1];
std::string output_file = argv[2];
```

---

### 关键词：`many values`, `samples`, `pixels`, `intervals`, `doses`

用：

```text
std::vector
```

模板：

```cpp
std::vector<double> data;
double x;

while (infile >> x)
{
    data.push_back(x);
}
```

---

### 关键词：`classify`, `alarm`, `normal/abnormal`, `low/high`

用：

```text
if / else if / else
```

模板：

```cpp
if (value > high_threshold)
{
    return "high";
}
else if (value >= mid_threshold)
{
    return "moderate";
}
else
{
    return "low";
}
```

---

### 关键词：`mean`, `sum`, `average`

用：

```text
求和循环
```

模板：

```cpp
double sum = 0.0;

for (const auto& x : data)
{
    sum += x;
}

double mean = sum / data.size();
```

---

### 关键词：`minimum`, `maximum`, `peak`, `valley`

用：

```text
min/max loop
```

模板：

```cpp
double min_value = data[0];
double max_value = data[0];

for (int i = 1; i < data.size(); i++)
{
    if (data[i] < min_value)
    {
        min_value = data[i];
    }

    if (data[i] > max_value)
    {
        max_value = data[i];
    }
}
```

---

### 关键词：`group related data`, `patient info`, `drug info`, `signal data`

用：

```text
struct
```

模板：

```cpp
struct Patient {
    std::string name;
    double weight;
};
```

---

### 关键词：`write a class`, `constructor`, `methods`

用：

```text
class
```

模板：

```cpp
class Image {
public:
    Image(int w, int h)
    {
        width = w;
        height = h;
    }

private:
    int width;
    int height;
};
```

---

### 关键词：`allow image(i,j)`, `cout << obj`, `obj1 + obj2`

用：

```text
operator overloading
```

模板：

```cpp
T& operator()(int i, int j)
{
    ...
}
```

```cpp
friend std::ostream& operator<<(std::ostream& out, const ClassName& obj)
{
    ...
    return out;
}
```

```cpp
friend ClassName operator+(const ClassName& a, const ClassName& b)
{
    return ClassName(...);
}
```

---

### 关键词：`generic function`, `works for int/float/double`

用：

```text
template function
```

模板：

```cpp
template <typename T>
T function_name(T x)
{
    ...
}
```

---

### 关键词：`generic class`, `Image<T>`, `Vector<T>`

用：

```text
template class
```

模板：

```cpp
template <typename T>
class ClassName {
    ...
};
```

---

## 10. Pump 题的专门保命主流程

这个单独给你，因为它最容易慌。

```cpp
int main(int argc, char* argv[])
{
    try
    {
        if (argc < 4)
        {
            std::cerr << "ERROR: expected database, patient file, and treatment plan\n";
            return 1;
        }

        DrugDatabase db = load_drug_database(argv[1]);
        Patient patient = load_patient(argv[2]);
        TreatmentPlan plan = load_treatment_plan(argv[3]);

        std::vector<std::string> drug_names = list_drugs_in_plan(plan);

        for (const auto& name : drug_names)
        {
            Drug drug = find_drug(db, name);
            std::vector<Dose> doses = extract_doses_for_drug(plan, name);

            double first_exceed_time = 0.0;

            if (first_time_threshold_exceeded(first_exceed_time, doses, drug, patient))
            {
                std::cout << "ALARM: " << name
                          << " exceeds threshold at time "
                          << first_exceed_time << "\n";
                return 0;
            }
        }

        std::cout << "Treatment plan is safe\n";
    }
    catch (const std::exception& err)
    {
        std::cerr << "ERROR: " << err.what() << "\n";
        return 1;
    }

    return 0;
}
```

这段你可以直接拿来改。

---

## 11. 最后的总做题顺序

### 第 1 步

先写中文：

```text
输入是什么？
输出是什么？
核心对象是什么？
整题分几步？
```

### 第 2 步

先写 `main.cpp`

```text
把整题流程串起来
```

### 第 3 步

根据 `main` 反推 `.h`

```text
左边接什么 -> 返回什么
括号里传什么 -> 参数什么
```

### 第 4 步

最后补 `.cpp`

```text
先写最简单函数
再写读取
再写核心计算
最后写 report / alarm
```

---

## 12. 最短一句保命总结

```text
看到卷子先别慌
先贴 main 骨架
再写 .h
最后补 .cpp
老师这类题本质都是：
load -> process -> compute -> check -> output
```