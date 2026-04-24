## 9. 一个很多 cpp 一起用的完整例子

如果我有很多功能，比如：
- add
- multiply
- square

那么我可以把它们分别写成不同的 .h 和 .cpp 文件，然后在 main.cpp 里一起使用。

add.h
#pragma once

int add(int a, int b);

add.cpp
#include "add.h"

int add(int a, int b)
{
    return a + b;
}

multiply.h
#pragma once

int multiply(int a, int b);

multiply.cpp
#include "multiply.h"

int multiply(int a, int b)
{
    return a * b;
}

square.h
#pragma once

int square(int x);

square.cpp
#include "square.h"

int square(int x)
{
    return x * x;
}

main.cpp
#include <iostream>
#include "add.h"
#include "multiply.h"
#include "square.h"

int main()
{
    std::cout << add(2, 3) << "\n";
    std::cout << multiply(4, 5) << "\n";
    std::cout << square(6) << "\n";
    return 0;
}

编译命令
g++ main.cpp add.cpp multiply.cpp square.cpp -o main
./main

这段例子说明什么

main.cpp 不是直接使用很多个 .cpp 文件。

main.cpp 的做法是：
1. #include 很多个 .h
2. 通过这些 .h 知道有哪些函数可以用
3. 编译时再把所有相关的 .cpp 一起编译

最短总结

main 用多个 cpp 的方法：
main.cpp include 多个 .h
编译时把对应的多个 .cpp 一起写上

例子：
g++ main.cpp add.cpp multiply.cpp square.cpp -o main
