#include <iostream>
#define TABLE_SIZE 997
using namespace std;

template <typename KeyType, typename ValueType>
struct hash_table
{
private:
    struct hash_node
    {
        KeyType key;
        ValueType value;
        hash_node* next;

        hash_node(KeyType key, ValueType value): key(key), value(value)
        {
            next = nullptr;
        }
    };
    std::hash<KeyType> key_hash;
    hash_node* m_table[TABLE_SIZE];
    int get_hash(KeyType key)
    {
        int value = 0;

        value = key_hash(key) % TABLE_SIZE;
        //for (auto c : key)
        //    value = (value + c) % TABLE_SIZE;
        return value;
    }
public:
    hash_table()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            m_table[i] = nullptr;
    }
    ~hash_table()
    {
        auto delete_list = [](hash_node* node) {
            auto p = node;

            while (p != nullptr)
            {
                auto next = p->next;
                delete p;
                p = next;
            }
        };

        for (int i = 0; i < TABLE_SIZE; i++)
            delete_list(m_table[i]);
    }
    void put(KeyType key, ValueType value)
    {
        int hash_code = get_hash(key);
        if (m_table[hash_code] == nullptr) {
            m_table[hash_code] = new hash_node(key, value);
        }
        else {
            hash_node* p = m_table[hash_code];
            while (p->key != key && p->next != nullptr)
                p = p->next;

            if (p->key == key)
                p->value = value;
            else
            {
                auto new_node = new hash_node(key, value);
                p->next = new_node;
            }
        }
    }

    ValueType get(KeyType key)
    {
        int hash_code = get_hash(key);
        if (m_table[hash_code] == nullptr)
            throw "No such key";
        else {
            auto p = m_table[hash_code];
            while (p != nullptr && p->key != key)
                p = p->next;
            if (p == nullptr)
                throw "No such key";
            return p->value;
        }
    }

    int _max_depth()
    {
        int _max = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            int _depth = 0;
            auto p = m_table[i];

            while (p != nullptr)
            {
                _depth += 1;
                p = p->next;
            }

            if (_depth > _max)
                _max = _depth;
        }

        return _max;
    }
};

int main()
{
    auto person = hash_table<string, string>();

    person.put("name", "Alex Dumitru");
    person.put("age", "20");
    person.put("education", "University of Manchester");

    cout << person.get("name") << " " << person.get("age") << " " << person.get("education") << "\n";

    cout << "Max depth: " << person._max_depth() << "\n";

    class Unhashable
    {
        int x;

    public:
        Unhashable(int x = 0): x(x)
        {

        }
    };

    auto x = Unhashable(1);
    auto y = Unhashable(2);
    //auto table = hash_table<Unhashable, string>();

    //table.put(x, "x");
    //table.put(y, "y");

    //cout << table.get(x) << table.get(y) << "\n";
    return 0;
}
