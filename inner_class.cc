#include <iostream>

struct Base1
{
    virtual void do_stuff() const = 0;
    // NOTE: no virtual destructor
};

struct Base2
{
    virtual void do_stuff() const = 0;
    // NOTE: no virtual destructor
};

class Derived
{
public:
    Derived(): b1_(this), b2_(this) {}
    // convert from type 'Derived' to type 'Base1&'
    operator Base1&()
    {
       return b1_;
    }

    // convert from type 'Derived' to type 'Base2&'
    operator Base2&()
    {
       return b2_;
    }

private:

    class Base1Impl: public Base1
    {
    public:
        Base1Impl(Derived *d): d_(d) {}
        void do_stuff() const override
        {
            std::cout << "Base1Impl::do_stuff()\n";
            d_->base1_func();
        }
    private:
        Derived *d_;
    } b1_;

    class Base2Impl: public Base2
    {
    public:
        Base2Impl(Derived *d): d_(d) {}
        void do_stuff() const override
        {
            std::cout << "Base2Impl::do_stuff()\n";
            d_->base2_func();
        }
    private:
        Derived *d_;
    } b2_;

    void base1_func() const
    {
        std::cout << "Base1 func\n";
    }

    void base2_func() const
    {
        std::cout << "Base2 func\n";
    }

};
         
void base1_do_stuff(Base1 &base)
{
    base.do_stuff();
}

void base2_do_stuff(Base2 &base)
{
    base.do_stuff();
}

template <typename Base>
void do_stuff(Base &base)
{
    base.do_stuff();
}

int main()
{
    Derived d;
    // these works because of the operator overload
    base1_do_stuff(d);
    base2_do_stuff(d);
    do_stuff(static_cast<Base1&>(d));
    do_stuff(static_cast<Base2&>(d));
}
