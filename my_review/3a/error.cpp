#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    try     这里面的代码“可能出错”
    {
        if (argc < 2)
            throw std::runtime_error("expected argument");      我发现情况不对，现在制造一个错误并交给外面处理
    }
    catch (std::exception& err)     如果 try 里面真的出错了，就来这里接住错误.  err 就是这个错误对象。
    {
        std::cerr << "ERROR: " << err.what() << "\n";       把错误信息文字取出来
        return 1;
    }

    return 0;
}

try 里面可能出错
如果出错，就 catch 住
然后打印错误信息并退出

expected argument 你想告诉用户：到底缺了什么
throw std::runtime_error("expected filename"); 要文件名
throw std::runtime_error("expected two numbers"); 要两个 numbers
throw std::runtime_error("expected age"); 要输入年龄


example1    题目要一个文件名
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            throw std::runtime_error("expected filename");
        }

        std::cout << "File name is " << argv[1] << "\n";
    }
    catch (std::exception& err)
    {
        std::cerr << "ERROR: " << err.what() << "\n";
        return 1;
    }

    return 0;
}


example2    题目要两个数字
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 3)
        {
            throw std::runtime_error("expected two numbers");
        }

        double a = std::stod(argv[1]);
        double b = std::stod(argv[2]);

        std::cout << "Sum = " << a + b << "\n";
    }
    catch (std::exception& err)
    {
        std::cerr << "ERROR: " << err.what() << "\n";
        return 1;
    }

    return 0;
}

example3    题目要年龄参数
#include <iostream>
#include <stdexcept>
#include <string>

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2)
        {
            throw std::runtime_error("expected age");
        }

        int age = std::stoi(argv[1]);

        if (age >= 18)
        {
            std::cout << "Adult\n";
        }
        else
        {
            std::cout << "Not adult\n";
        }
    }
    catch (std::exception& err)
    {
        std::cerr << "ERROR: " << err.what() << "\n";
        return 1;
    }

    return 0;
}
