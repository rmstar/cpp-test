#include "pimpl.h"
#include "pimpl_impl.h"
#include <iostream>

Widget::Widget(int serial)
{
    pimpl_.reset(new WidgetImpl(serial));
}

Widget::~Widget()
{
}

int Widget::get_serial()
{
    return pimpl_->get_serial();
}
