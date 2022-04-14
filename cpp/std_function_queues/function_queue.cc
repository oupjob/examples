#include <iostream>
#include <string>
#include <functional>
#include <vector>

using namespace std;
using namespace std::placeholders;

struct Container
{
    using callback_f = std::function<void (const std::string&)>;
    using callback_f_arg_t = callback_f&;

    std::vector<callback_f> v_callbacks;
    
    void push(callback_f_arg_t callback)
    {
        v_callbacks.push_back(callback);    
    }
    
    void pop(const std::string& message)
    {
        auto it_begin = v_callbacks.begin();
        if (it_begin != v_callbacks.end())
        {
            cout << "pop: sizeof(f) = " << sizeof(*it_begin) << ", ";
            if (*it_begin != nullptr)
                (*it_begin)(message);
            v_callbacks.erase(it_begin);  
        }
    }
};

struct A
{
    Container container; 

    void f(const std::string& s)
    {
        int n = 32 + 12;
        n++;
        cout << "A::f() : " << s << ", n = " << ++n << endl;
    }
    
    void test_push()
    {
        Container::callback_f fb = std::bind(&A::f, this, _1);
        container.push(fb);
    }
    
    void test_push_nullptr()
    {
        Container::callback_f fb = nullptr;
        container.push(fb);
    };
    
    void test_pop(const std::string& message)
    {
        container.pop(message);
    }
};



int main()
{
    A a;
    a.test_push();
    a.test_push_nullptr();
    a.test_pop("sss1");
    a.test_pop("sss2");
}

