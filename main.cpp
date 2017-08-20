#include <iostream>
#define TABLE_SIZE 997
using namespace std;

template <typename V>
struct hash_table
{
private:
    struct hash_node
    {
        string key;
        V value;
        hash_node* next;

        hash_node(string key, V value): key(key), value(value)
        {
            next = nullptr;
        }
    };
    hash_node* m_table[TABLE_SIZE];
    int get_hash(string key)
    {
        int value = 0;
        for (auto c : key)
            value = (value + c) % TABLE_SIZE;
        return value;
    }
public:
    hash_table()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            m_table[i] = nullptr;
    }
    void put(string key, V value)
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

    V get(string key)
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
    auto person = hash_table<string>();

    person.put("name", "Alex Dumitru");
    person.put("age", "20");

    cout << person.get("name") << " " << person.get("age") << "\n";

    cout << "Max depth: " << person._max_depth() << "\n";

    return 0;
}
