#include <iostream>
#include <list>
#include <chrono>

using namespace std;

typedef std::list<std::string> slist_t;

using hr_clock_t = std::chrono::high_resolution_clock;
using second_t = std::chrono::duration<double, std::ratio<1> >;

void move_list_check(slist_t& src, slist_t& dst)
{
    size_t size = src.size();
    std::chrono::time_point<hr_clock_t> time_begin(hr_clock_t::now());
    
    dst = std::move(src);

    cout << "Moving lists: [size = " << size 
         << ", time_elapsed = " << std::chrono::duration_cast<second_t>(hr_clock_t::now() - time_begin).count() << "]" << endl;
}

void fill(size_t size, slist_t& l)
{
    for(size_t i = 0; i < size; ++i)
    l.push_back("aaaaaaa");
}

int main()
{
    slist_t l1, l2;
    fill(100, l1);
    move_list_check(l1, l2);

    fill(1000000, l1);
    move_list_check(l1, l2);

    
    return 0;
}
