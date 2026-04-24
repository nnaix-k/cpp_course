#include <iostream>
#include <fstream>

int main()
{
    std::ofstream outfile("out.txt");

    if (!outfile)
    {
        std::cerr << "ERROR: failed to open file\n";
        return 1;
    }

    outfile << "Hello\n";
    return 0;
}

创建一个“写文件工具” outfile，
准备把内容写进 out.txt
如果失败就报错退出
如果成功，就往里面写一行文字
