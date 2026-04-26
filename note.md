# C++ 全课程万能模板总表

这份笔记不是按章节背，而是按题型找模板。  
考试时先判断题目属于哪一类，再翻对应模板。

---

## 1. 输入输出题

### 题目特征

```text
print / display / output
ask user to enter
input two numbers
output result
```

### 模板

```cpp
#include <iostream>

int main()
{
    int x;
    std::cin >> x;
    std::cout << x << "\n";
    return 0;
}
```

### 你要会改什么

```text
变量类型：int / double / string
输入几个变量
输出内容
```

---

## 2. 判断题

### 题目特征

```text
positive / negative / zero
pass / fail
odd / even
adult / not adult
classify
```

### 模板

```cpp
if (condition)
{
    ...
}
else if (condition)
{
    ...
}
else
{
    ...
}
```

### 常见例子

```cpp
if (x % 2 == 0)
{
    std::cout << "Even\n";
}
else
{
    std::cout << "Odd\n";
}
```

### 你要会改什么

```text
条件
输出文字
if / else if / else 的顺序
```

---

## 3. 循环题

### 题目特征

```text
repeat
print 1 to n
sum all values
scan through data
count / search / detect
```

### for 模板

```cpp
for (int i = 0; i < n; i++)
{
    ...
}
```

### while 模板

```cpp
while (condition)
{
    ...
}
```

### 你要会改什么

```text
起点
终点
每轮做什么
```

---

## 4. vector / array 题

### 题目特征

```text
store many values
sequence of data
list of samples
pixels / signal / intervals
compute mean / min / max
```

### vector 模板

```cpp
#include <vector>

std::vector<double> data;
double x;

while (input >> x)
{
    data.push_back(x);
}
```

### 遍历模板

```cpp
for (int i = 0; i < data.size(); i++)
{
    ...
}
```

或

```cpp
for (const auto& x : data)
{
    ...
}
```

### 求和模板

```cpp
double sum = 0.0;
for (const auto& x : data)
{
    sum += x;
}
```

### 你要会改什么

```text
元素类型：int / double / string
push_back
循环里的计算逻辑
```

---

## 5. 文件读取题

### 题目特征

```text
read data from file
input filename
load signal / image / table
output report file
```

### 读文件模板

```cpp
#include <fstream>
#include <iostream>

std::ifstream infile(filename);

if (!infile)
{
    std::cerr << "ERROR: failed to open file\n";
    return 1;
}
```

### 一直读模板

```cpp
double x;
while (infile >> x)
{
    data.push_back(x);
}
```

### 写文件模板

```cpp
std::ofstream outfile(filename);

if (!outfile)
{
    std::cerr << "ERROR: failed to open output file\n";
    return 1;
}

outfile << "result\n";
```

### 你要会改什么

```text
文件名变量
读入的数据类型
报告格式
```

---

## 6. 命令行参数题

### 题目特征

```text
command-line arguments
input file and output file
optional threshold
optional parameter
```

### 模板

```cpp
int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "ERROR: expected input and output filenames\n";
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    return 0;
}
```

### 可选参数模板

```cpp
double threshold = 0.5;

if (argc > 3)
{
    threshold = std::stod(argv[3]);
}
```

### 你要会改什么

```text
至少要几个参数
默认值
argv[1] / argv[2] / argv[3] 分别代表什么
```

---

## 7. 函数拆分题

### 题目特征

```text
program should perform several steps
compute X, detect Y, write report
large problem
avoid long main
```

### 模板

```cpp
ReturnType function_name(Parameters)
{
    ...
}
```

### 大题常见做法

```cpp
load_data(...)
process_data(...)
compute_metrics(...)
write_report(...)
```

### main 骨架

```cpp
int main(int argc, char* argv[])
{
    ...
    auto data = load_data(...);
    auto result = process_data(...);
    write_report(...);
    return 0;
}
```

### 你要会改什么

```text
每一步单独起函数名
参数类型
返回值类型
```

---

## 8. struct 题

### 题目特征

```text
group related values
student / patient / signal / image metadata
several fields belong together
```

### 模板

```cpp
struct Student {
    int id;
    std::string name;
    float gpa;
};
```

### 使用

```cpp
Student s;
s.id = 1;
s.name = "Alice";
s.gpa = 3.8;
```

### 你要会改什么

```text
struct 名字
成员变量
成员类型
```

---

## 9. class 题

### 题目特征

```text
write a class
store data privately
provide methods
constructor
getter / setter
```

### 模板

```cpp
class Student {
public:
    Student(int id_value, std::string name_value)
    {
        id = id_value;
        name = name_value;
    }

    void print() const
    {
        std::cout << id << " " << name << "\n";
    }

private:
    int id;
    std::string name;
};
```

### 使用

```cpp
Student s(1, "Alice");
s.print();
```

### 你要会改什么

```text
类名
private 数据
public 方法
constructor 参数
```

---

## 10. 多文件题

### 题目特征

```text
split project into files
declaration / definition
modularity
maintainability
```

### .h

```cpp
#pragma once

int add(int a, int b);
```

### .cpp

```cpp
#include "add.h"

int add(int a, int b)
{
    return a + b;
}
```

### main.cpp

```cpp
#include <iostream>
#include "add.h"

int main()
{
    std::cout << add(3, 5) << "\n";
    return 0;
}
```

### 编译

```bash
g++ main.cpp add.cpp -o main
```

### 你要会改什么

```text
文件名
声明
定义
编译命令
```

---

## 11. operator overloading 题

### 题目特征

```text
allow a + b
allow cout << obj
allow a == b
allow a += b
allow v[0]
```

### operator+

```cpp
friend ClassName operator+(const ClassName& a, const ClassName& b)
{
    return ClassName(...);
}
```

### operator<<

```cpp
friend std::ostream& operator<<(std::ostream& out, const ClassName& obj)
{
    out << ...;
    return out;
}
```

### operator==

```cpp
bool operator==(const ClassName& other) const
{
    return ...;
}
```

### operator+=

```cpp
ClassName& operator+=(const ClassName& other)
{
    ...
    return *this;
}
```

### operator[]

```cpp
type& operator[](int i)
{
    return data[i];
}
```

### 你要会改什么

```text
类名
运算规则
输出格式
成员访问方式
```

---

## 12. template function 题

### 题目特征

```text
generic function
work for int / float / double
avoid duplication
```

### 单值模板

```cpp
template <typename T>
T pow3(T x)
{
    return x * x * x;
}
```

### vector 模板

```cpp
template <typename T>
double compute_mean(const std::vector<T>& data)
{
    double sum = 0.0;
    for (const auto& x : data)
    {
        sum += x;
    }
    return sum / data.size();
}
```

### 你要会改什么

```text
模板参数名 T
函数逻辑
参数类型
```

---

## 13. template class 题

### 题目特征

```text
generic class
class should work for multiple types
vector of X / array of X
```

### 模板

```cpp
template <typename X>
class Vector3D {
public:
    X& operator[](int i)
    {
        return data[i];
    }

private:
    std::array<X, 3> data;
};
```

### 使用

```cpp
Vector3D<double> a;
Vector3D<int> b;
```

### 你要会改什么

```text
类名
类型参数名
内部数据结构
```

---

## 14. 大题总骨架

### 题目特征

```text
file input
process data
compute metrics
output report
many steps
```

### 通用骨架

```cpp
int main(int argc, char* argv[])
{
    // 1. check arguments
    // 2. load data
    // 3. process data
    // 4. compute results
    // 5. write report
    return 0;
}
```

### 更完整一点

```cpp
int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "ERROR: expected input and output filenames\n";
        return 1;
    }

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    auto data = load_data(input_file);
    auto result = process_data(data);
    write_report(output_file, result);

    return 0;
}
```

---

## 考试时统一思考顺序

每道题先写这 6 句：

```text
1. 输入是什么？
2. 输出是什么？
3. 数据该用什么存？
4. 中间分几步？
5. 每一步对应哪个模板？
6. main 最后怎么调用？
```

---

## 这份笔记最重要的一句话

```text
模板不是整题答案
模板是零件
真正得分靠：题目 -> 模板选择 -> 模板拼装
```
