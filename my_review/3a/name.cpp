#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    if (argc < 2)       如果参数太少

    {
        std::cerr << "ERROR: expected filename\n";  你没有给文件名，所以程序报错退出
        return 1;
    }

    std::ifstream infile(argv[1]);      用用户输入的文件名去打开文件

    if (!infile)
    {
        std::cerr << "ERROR: failed to open file\n";
        return 1;
    }

    return 0;
}

argc = 参数个数 看题目要求 如果要两个数字那就是argc<3
argv = 参数内容
argv[0] = "./main"      不是用户输入的文件名 是程序名
argv[1] = "data.txt"    才通常是第一个真正参数 文件名
argc = 2

运行程序时，让用户自己给文件名
如果没给，就报错
如果给了，就尝试打开这个文件
