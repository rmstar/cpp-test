#include <iostream>

struct Thing
{
    virtual ~Thing() {}
    virtual Thing *clone() const = 0;
};

struct Widget: public Thing
{
    Widget() {}

    // NOTE: covariant return type. overriden method can return more derived type  
    Widget* clone() const override
    {
        std::cout << "Widget::clone()\n";
        return new Widget(*this);
    }
};

int main()
{
    Widget w;
    Widget *w2 = w.clone();
} 
