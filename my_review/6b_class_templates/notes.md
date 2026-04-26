6B Template programming: class templates

核心：
template class = 一个类模板，可以给很多类型用

最基础模板：
template <typename X>
class Vector3D
{
    ...
};

使用：
Vector3D<double> a;
Vector3D<int> b;

多个类型参数：
template <typename Key, typename Value>
class LookupTable
{
    ...
};

使用：
LookupTable<std::string, float> table;

非类型模板参数：
template <typename X, int D>
class Vector
{
    ...
};

使用：
Vector<double,2> a;
Vector<int,4> b;

最重要理解：
6A 是 template function
6B 是 template class
