#include <iostream>
#include <fstream>

int main()
{
    std::ifstream infile("data.txt");   打开 data.txt，准备读取


    if (!infile)   如果文件没有打开成功
    {
        std::cerr << "ERROR: failed to open file\n";
        return 1;
    }

    int x;    创建一个整数变量 x，等会儿用来装从文件里读出来的数字。

    while (infile >> x)    只要还能从文件里成功读到一个整数到 x，就继续循环

    {
        std::cout << x << "\n";
    }

    return 0;
}

return 0  成功结束
return 1  出错结束

打开 data.txt
如果打不开就报错退出
如果打开成功，就把里面的整数一个一个读出来并打印
