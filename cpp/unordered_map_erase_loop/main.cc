#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

typedef std::unordered_map<uint32_t, uint32_t> map_t;

void erase(map_t& map)
{
    auto it = map.begin();
    while(it != map.end())
    {
        if (it->second == 0)
            it = map.erase(it);
        else
            ++it;
    }
}

void print(const map_t& map)
{
    cout << "print map:" << endl;
    for (auto it : map)
        cout << it.first << " -> " << it.second << endl;
}

int main()
{
    map_t map = { {1, 1}, {2, 0}, {3, 1}, {4, 0} };
    
    print(map);
    erase(map);
    print(map);
}

