#include <iostream>

using namespace std;

struct WidgetIntf
{
    virtual void derp() const = 0;
};

struct Widget: public WidgetIntf
{
    virtual void derp() const override
    {
        cout << "Widget::derp()\n";
    }
};

struct GadgetIntf 
{
    virtual void beep() const = 0;
};

struct Gadget: public GadgetIntf 
{
    virtual void beep() const override
    {
        cout << "Gadget::beep()\n";
    }
};

class GadgetAdapter: public GadgetIntf {
public:
    GadgetAdapter(Widget w): widget_(w) {}

    void beep() const override
    {
        widget_.derp();
    }
private:
    Widget widget_;
};

int main()
{
    Widget w;
    w.derp();
    Gadget g;
    g.beep();
    //GadgetAdapter ga = GadgetAdapter(Widget()); -> this is ok
    //GadgetAdapter ga(Widget()); -> does not compile, "most vexing parse"
    GadgetAdapter ga{Widget{}};
    ga.beep();
}
