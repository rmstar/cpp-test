#include <iostream>

using namespace std;

template <typename T>
class counter
{
public:
    counter()
    {
        ++count_;
    }

    counter(const counter&)
    {
        ++count_;
    }
    static int get_count()
    {
        return count_;
    }

protected:
    ~counter() // protected so that counter<T> can't be instantiated
    {
        --count_;
    }

private:
    static int count_;
};

template <typename T> int counter<T>::count_(0);

class X: public counter<X>
{
};

class Y: public counter<Y>
{
};


void counter_test()
{
    X x, y;
    Y b;
    {
        X z = x;

        Y a;
        cout << counter<X>::get_count()<< " " << counter<Y>::get_count()<< endl;
    }
    cout << counter<X>::get_count()<< " " << counter<Y>::get_count()<< endl;

    //counter<X> val;
}

//==============================================================================

template <typename T>
struct Intf
{
    void func()
    {
        cout << "Intf::func()\n";
        static_cast<T*>(this)->func();
    }

    static void static_func()
    {
        cout << "Intf::static_func()\n";
        T::static_func();
    }
    void foo()
    {
        cout << "Intf::foo()\n";
    }
};

struct Impl: Intf<Impl>
{
    void func()
    {
        cout << "Impl::func()\n";
    }

    static void static_func()
    {
        cout << "Impl::static_func()\n";
    }

    void bar()
    {
        cout << "Impl::bar()\n";
    }
};

void crtp_test()
{
    Impl i;
    i.func();
    i.static_func();
    i.foo();
    i.bar();

    cout << endl;

    Intf<Impl> j;
    j.func();
    j.static_func();
    j.foo();
}
    
int main()
{
    counter_test();
    crtp_test();
}
