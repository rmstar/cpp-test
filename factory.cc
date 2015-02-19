#include <memory>
#include <iostream>

class Widget
{
public:
    static std::shared_ptr<Widget> make_widget(const std::string &name)
    {
        return std::make_shared<Widget>(name);
#if 0
        std::shared_ptr<Widget> w;
        w.reset(new Widget(name));
        return w;
#endif
    }
    std::string get_name() { return name_; }
private:
    Widget(const std::string n) : name_(n) {}
    std::string name_;
};



int main()
{
    auto ptr = Widget::make_widget("thing");
    std::cout << ptr->get_name() << std::endl;
}



