#include <iostream>
#include <string>
#include <functional>
#include <vector>

using namespace std;
using namespace std::placeholders;

struct Container
{
    using callback_f = std::function<void (const std::string&)>;
    using callback_f_arg_t = callback_f*;
    
    struct Element
    {
        callback_f_arg_t    callback_f;    
    };
    
    std::vector<Element> storage;
    
    void push(callback_f_arg_t callback)
    {
        Element e;
        e.callback_f = callback;
        storage.push_back(e);    
    }
    
    void pop(const std::string& message)
    {
        auto it_begin = storage.begin();
        if (it_begin != storage.end())
        {
            cout << "pop: sizeof(f) = " << sizeof(*it_begin) << ", ";
            
            if (it_begin->callback_f)
            {
                callback_f_arg_t callback_f = (it_begin->callback_f);
                (*(it_begin->callback_f))(message);
            }

            storage.erase(it_begin);  
        }
    }
};

struct A
{
    Container container;
    Container::callback_f fb;
    
    A()
    {
        fb = std::bind(&A::f, this, _1);
    }

    void f(const std::string& s)
    {
        int n = 32 + 12;
        n++;
        cout << "A::f() : " << s << ", n = " << ++n << endl;
    }
    
    void test_push()
    {
        container.push(&fb);
    }
    
    void test_push_nullptr()
    {
        Container::callback_f fb = nullptr;
        container.push(&fb);
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

