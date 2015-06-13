#include <iostream>
#include <set>
#include <stdexcept>
#include <memory>

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
    void register_observer(shared_ptr<ObserverInterface> o)
    {
        obs_.insert(o);
    }

    void remove_observer(shared_ptr<ObserverInterface> o)
    {
        obs_.erase(o);
    }
    
    void update_widget(int widget_count)
    {
        cout << "update_widget: " << widget_count << "\n";
        widget_count_ = widget_count;
        notify_observers();
    }
    
protected:
    void notify_observers()
    {
        for (auto &i: obs_) {
            auto ptr = i.lock();
            if (ptr) {
                ptr->update(widget_count_);
                auto d = dynamic_pointer_cast<DisplayInterface>(ptr);
                if (d == nullptr) {
                    throw runtime_error("Object doesn't have a display interface");
                 }
                 d->show();
            }
        }
    }

private:
    int widget_count_;
    set<weak_ptr<ObserverInterface>, owner_less<weak_ptr<ObserverInterface>>> obs_;
};

class WidgetObserver: public ObserverInterface, public DisplayInterface, public enable_shared_from_this<WidgetObserver>
{
public:
    WidgetObserver(Widget &w): widget_count_(0), w_(w)
    { }

    // we need a start() method because we can't use shared_from_this until the
    // object is actually managed by a shared_ptr. We can't use shared_from_this
    // in a constructor because the object won't be placed into the shared_ptr
    // until the object is completely constructed.
    void start()
    {
        w_.register_observer(shared_from_this());
    }

    void show() override
    {
        cout << "WidgeObserver: Widget count: " << widget_count_ << endl;
    }

    void update(int widget_count) override
    {
        widget_count_ = widget_count;
    }

private:
    Widget &w_;
    int widget_count_;
};

class AggregateObserver: public ObserverInterface, public DisplayInterface, public enable_shared_from_this<AggregateObserver>
{
public:
    AggregateObserver(Widget &w): widget_count_(0), w_(w)
    { }

    // we need a start() method because we can't use shared_from_this until the
    // object is actually managed by a shared_ptr. We can't use shared_from_this
    // in a constructor because the object won't be placed into the shared_ptr
    // until the object is completely constructed.
    void start()
    {
        w_.register_observer(shared_from_this());
    }

    void show() override
    {
        cout << "AggregateObserver: Widget count: " << widget_count_ << endl;
    }

    void update(int widget_count) override
    {
        widget_count_ += widget_count;
    }

private:
    Widget &w_;
    int widget_count_;
};

class DontCareObserver: public ObserverInterface, public DisplayInterface, public enable_shared_from_this<DontCareObserver>
{
public:
    DontCareObserver()
    { }

    void set_widget(Widget &w)
    {
        w_ = &w;
        w_->register_observer(shared_from_this());
    }
    void show() override
    {
        cout << "got some widget\n";
    }

    void update(int) override
    {
        // meh
    }

private:
    Widget *w_;

};

int main()
{
    Widget w;
    auto wo1 = make_shared<WidgetObserver>(w);
    wo1->start();

    auto wo2 = make_shared<DontCareObserver>();
    wo2->set_widget(w);

    auto wo3 = make_shared<AggregateObserver>(w);
    wo3->start();

    w.update_widget(10);
    cout << "\n";
    w.update_widget(20);
    cout << "\n";

    w.remove_observer(wo1);
    cout << "\nremoved WidgetObserver\n";
    w.update_widget(30);

    wo3.reset();
    cout << "\nreset AggregateObserver\n";
    w.update_widget(40);
}
