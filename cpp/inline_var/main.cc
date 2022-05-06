// Example program
#include <iostream>
#include <string>

struct foo_t
{
    inline static std::string _s_default;

    virtual std::string& s() { return _s_default; }
};

struct bar_t : public foo_t
{
    std::string s_;

    std::string& s() const { return s_; }
};

int main()
{
    bar_t bar; 
    bar.s() = "aaa";
    std::cout << bar.s() << "\n";
}

