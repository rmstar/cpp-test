#include <iostream>
#include <set>
#include <stdexcept>

using namespace std;

struct ObserverInterface
{
    virtual void update(int data) = 0;
};


struct DisplayInterface
{
    virtual void show() = 0;
};

class Widget
{
public:
    void register_observer(ObserverInterface *o)
    {
        obs_.insert(o);
    }

    void remove_observer(ObserverInterface *o)
    {
        obs_.erase(o);
    }
    
    void update_widget(int widget_count)
    {
        widget_count_ = widget_count;
        notify_observers();
    }
    
protected:
    void notify_observers()
    {
        for (auto &i: obs_) {
            i->update(widget_count_);
            auto d = dynamic_cast<DisplayInterface*>(i);
            if (d == nullptr) {
                throw runtime_error("Object doesn't have a display interface");
             }
             d->show();
        }
    }

private:
    int widget_count_;
    set<ObserverInterface *> obs_;
};

class WidgetObserver: public ObserverInterface, public DisplayInterface
{
public:
    WidgetObserver(Widget &w): widget_count_(0)
    {
        w.register_observer(this);
    }
    void show() override
    {
        cout << "Widget count: " << widget_count_ << endl;
    }

    void update(int widget_count) override
    {
        widget_count_ = widget_count;
    }

private:
    int widget_count_;
};

class DontCareObserver: public ObserverInterface, public DisplayInterface
{
public:
    DontCareObserver(Widget &w)
    {
        w.register_observer(this);
    }
    void show() override
    {
        cout << "got some widget\n";
    }

    void update(int) override
    {
        // meh
    }

};

int main()
{
    Widget w;
    WidgetObserver wo1(w);
    DontCareObserver wo2(w);

    w.update_widget(10);
    w.update_widget(20);

    w.remove_observer(&wo1);
    cout << "removed WidgetObserver\n";
    w.update_widget(30);
}
