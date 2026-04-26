# C++ 题目情况 -> 该用什么结构

这份笔记不是讲新知识点，而是帮你判断：

```text
题目里出现什么需求
-> 应该想到什么代码结构
```

---

## 1. 题目说“让用户输入”

### 你应该想到

```text
std::cin
```

### 常见题目词

```text
enter
input
type a number
ask the user
```

### 模板

```cpp
int x;
std::cin >> x;
```

### 例子

题目说：

```text
Ask the user to enter two integers
```

你就写：

```cpp
int a, b;
std::cin >> a >> b;
```

---

## 2. 题目说“输出结果到屏幕”

### 你应该想到

```text
std::cout
```

### 常见题目词

```text
print
display
output
show
```

### 模板

```cpp
std::cout << result << "\n";
```

---

## 3. 题目说“从文件读取数据”

### 你应该想到

```text
ifstream
文件读取模板
错误检查
```

### 常见题目词

```text
read from file
load data
input file
read signal
read image
read measurements
```

### 模板

```cpp
std::ifstream infile(filename);

if (!infile)
{
    std::cerr << "ERROR: failed to open file\n";
    return 1;
}
```

### 为什么

因为题目不是让你从键盘输，而是让程序自己打开文件读。

---

## 4. 题目说“把结果写到文件 / 写 report”

### 你应该想到

```text
ofstream
写文件模板
```

### 常见题目词

```text
write report
save output
output file
write results
generate report
```

### 模板

```cpp
std::ofstream outfile(filename);

if (!outfile)
{
    std::cerr << "ERROR: failed to open output file\n";
    return 1;
}

outfile << "Result: " << value << "\n";
```

### 为什么

如果题目说：

```text
Write a report
```

你就应该第一时间想到：

```text
ofstream
```

不是 `cout`，因为 `cout` 是输出到屏幕，不是写进文件。

---

## 5. 题目说“输入文件名 / 输出文件名 / threshold”

### 你应该想到

```text
argc argv
命令行参数
```

### 常见题目词

```text
command-line arguments
input filename
output filename
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
}
```

### 为什么

因为这些值不是程序运行时让用户一个个输入，而是运行命令时直接给程序。

---

## 6. 题目里有“很多数据 / 一串样本 / 一列数字”

### 你应该想到

```text
vector
```

### 常见题目词

```text
sequence
samples
data points
measurements
pixels
values
RR intervals
voltages
```

### 模板

```cpp
std::vector<double> data;
double x;

while (infile >> x)
{
    data.push_back(x);
}
```

### 为什么

因为你不知道有多少个值，或者值很多，不适合一个个变量去存。

---

## 7. 题目里有“固定数量的数据”

### 你应该想到

```text
array
```

### 常见题目词

```text
3 coordinates
RGB
3 values only
fixed-size
```

### 模板

```cpp
std::array<double, 3> data;
```

### 为什么

因为数量固定，比如 3 个坐标、3 个颜色值。

---

## 8. 题目里说“这些信息属于同一个东西”

### 你应该想到

```text
struct 或 class
```

### 常见题目词

```text
student has id, name, gpa
ECG has sampling interval and values
image has width, height, pixels
patient has name and age
```

### 先判断用哪个

#### 如果只是打包数据

用：

```text
struct
```

#### 如果还要加方法、private/public

用：

```text
class
```

---

## 9. 什么情况用 struct

### 题目表现

```text
我只是想把几个相关变量放一起
```

### 模板

```cpp
struct Student {
    int id;
    std::string name;
    float gpa;
};
```

### 典型题目

```text
Define a type to store ECG data
Define a type to store student information
```

---

## 10. 什么情况用 class

### 题目表现

```text
这个对象不只是存数据
还要自己有功能
```

### 模板

```cpp
class Student {
public:
    void print() const
    {
        ...
    }

private:
    int id;
    std::string name;
};
```

### 常见题目词

```text
write a class
constructor
methods
private data
getter / setter
```

---

## 11. 题目说“分很多步骤完成”

### 你应该想到

```text
函数拆分
```

### 常见题目词

```text
load data
detect peaks
compute mean
calculate metric
write report
```

### 模板思路

```cpp
load_data(...)
process_data(...)
compute_result(...)
write_report(...)
```

### 为什么

因为如果题目步骤多，不能全塞进 `main()`。

---

## 12. 题目很长，像小项目

### 你应该想到

```text
.h / .cpp / main.cpp
多文件
```

### 常见题目词

```text
design
maintainability
modularity
split into files
```

### 结构

```text
xxx.h      声明
xxx.cpp    定义
main.cpp   串流程
```

### 为什么

因为老师这类题很看重结构分。

---

## 13. 题目说“重复做某件事”

### 你应该想到

```text
for / while
```

### 先怎么选

#### 如果“循环次数明确”

用：

```text
for
```

#### 如果“读到结束 / 满足条件一直做”

用：

```text
while
```

### 例子

#### 明确次数

```cpp
for (int i = 0; i < data.size(); i++)
{
    ...
}
```

#### 读到文件结束

```cpp
while (infile >> x)
{
    ...
}
```

---

## 14. 题目说“判断 / 分类”

### 你应该想到

```text
if / else if / else
```

### 常见题目词

```text
classify
if above threshold
normal / abnormal
low / moderate / high
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

---

## 15. 题目说“求平均值 / 最大值 / 最小值 / 总和”

### 你应该想到

```text
vector + loop + accumulator variables
```

### 模板

```cpp
double sum = 0.0;
for (const auto& x : data)
{
    sum += x;
}
double mean = sum / data.size();
```

### 最大值

```cpp
double max_value = data[0];
for (int i = 1; i < data.size(); i++)
{
    if (data[i] > max_value)
    {
        max_value = data[i];
    }
}
```

---

## 16. 题目说“检查错误 / 文件打不开 / 参数不对”

### 你应该想到

```text
error handling
if (...) { cerr ...; return 1; }
```

### 模板

```cpp
if (!infile)
{
    std::cerr << "ERROR: failed to open file\n";
    return 1;
}
```

### 参数不够

```cpp
if (argc < 3)
{
    std::cerr << "ERROR: expected input and output filenames\n";
    return 1;
}
```

---

## 17. 题目说“允许 a + b / cout << obj / a == b”

### 你应该想到

```text
operator overloading
```

### 对应关系

#### 题目要“相加”

```text
operator+
```

#### 题目要“输出对象”

```text
operator<<
```

#### 题目要“比较是否相等”

```text
operator==
```

#### 题目要“a += b”

```text
operator+=
```

#### 题目要“obj[i]”

```text
operator[]
```

---

## 18. 题目说“同一个函数适用于 int / float / double”

### 你应该想到

```text
template function
```

### 常见题目词

```text
generic function
work for several types
avoid duplication
```

### 模板

```cpp
template <typename T>
T function_name(T x)
{
    ...
}
```

---

## 19. 题目说“同一个类适用于多种类型”

### 你应该想到

```text
template class
```

### 常见题目词

```text
generic class
class should work for multiple types
```

### 模板

```cpp
template <typename T>
class ClassName {
    ...
};
```

---

## 最后给你一个最重要的判断表

### 题目说……

### 你就想到……

```text
用户输入            -> cin
屏幕输出            -> cout
读文件              -> ifstream
写 report           -> ofstream
输入文件名参数       -> argc argv
很多数据            -> vector
固定数量数据         -> array
几个信息属于同一对象  -> struct / class
步骤很多            -> 函数拆分
题目像小项目         -> .h / .cpp / main.cpp
要分类判断          -> if / else
要重复处理数据       -> for / while
要支持 a+b          -> operator+
要支持 cout<<obj    -> operator<<
要支持 obj1==obj2   -> operator==
一个函数支持很多类型  -> template function
一个类支持很多类型    -> template class
```

---

## 做大题前先写这 7 句

```text
1. 输入是什么？
2. 输出是什么？
3. 数据要怎么存？
4. 这题分几步？
5. 每一步用什么结构？
6. main 最后怎么串起来？
7. 哪些地方要做 error checking？
```
