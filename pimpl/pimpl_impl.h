#pragma once
#include "pimpl.h"
class Widget::WidgetImpl
{
public:
    // does not compile if constructor is defined in pimpl_impl.cc
    WidgetImpl(int serial) : serial_(serial) {}
    int get_serial();
private:
    int serial_;
};
