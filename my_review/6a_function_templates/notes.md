template_single.cpp   -> template <typename T> T function_name(T x)
template_vector.cpp   -> template <typename T> double function_name(const std::vector<T>& data)
template_example.h    -> 模板函数写在头文件里
template_main.cpp     -> include 头文件后在 main 里调用
notes.md              -> 笔记

6A Template programming: function templates

核心：
template function = 一个函数模板可以给很多类型用

最基础模板：
template <typename T>
T function_name(T x)
{
    ...
}

例子：
template <typename T>
T pow3(T x)
{
    return x * x * x;
}

vector 模板：
template <typename T>
double function_name(const std::vector<T>& data)
{
    ...
}

例子：
template <typename T>
double compute_mean(const std::vector<T>& data)
{
    ...
}

重要规则：
普通函数：
.h 放声明
.cpp 放定义

模板函数：
定义通常直接放在 .h 里


template_single.cpp
-> 测试单个值模板函数 pow3
-> 输出：
   8
   15.625
   27

template_vector.cpp
-> 测试 vector 模板函数 compute_mean
-> 输出：
   2.5
   2.5
   20

template_example.h
-> 头文件，不能单独运行

template_main.cpp
-> 调用 template_example.h 里的模板函数
-> 输出：
   2.5
   3.5
