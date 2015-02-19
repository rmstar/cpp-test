#pragma once
#include <memory>

class Widget
{
public:
    Widget(int serial);
    // does not compile without the destructor
    ~Widget();
    int get_serial();
private:
    class WidgetImpl;
    std::unique_ptr<WidgetImpl> pimpl_;
};
