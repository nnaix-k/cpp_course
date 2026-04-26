#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

template <typename Key, typename Value>
struct KeyValuePair {
    Key key;
    Value value;
};

template <typename Key, typename Value>
class LookupTable {
public:
    LookupTable& add(const KeyValuePair<Key, Value>& kv)
    {
        data.push_back(kv);
        return *this;
    }

    const Value& get(const Key& key) const
    {
        for (const auto& item : data)
        {
            if (item.key == key)
            {
                return item.value;
            }
        }

        throw std::runtime_error("item not found");
    }

private:
    std::vector<KeyValuePair<Key, Value>> data;
};

int main()
{
    LookupTable<std::string, float> parameters;

    parameters.add({"sampling interval", 0.2f})
              .add({"sampling duration", 12.0f})
              .add({"maximum voltage", 5.0f});

    std::cout << parameters.get("sampling interval") << "\n";
    std::cout << parameters.get("maximum voltage") << "\n";

    return 0;
}

这个类有两个模板参数
一个是 key 的类型
一个是 value 的类型

LookupTable<std::string, float>
key 是 string
value 是 float
