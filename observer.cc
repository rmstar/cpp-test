#include <iostream>
#include <set>
#include <stdexcept>
#include <memory>
#include <string>

using namespace std;

template <typename T>
struct ObserverInterface
{
    virtual void update(T data) = 0;
};


struct DisplayInterface
{
    virtual void show() = 0;
};

template <typename T>
class Widget
{
public:
    void register_observer(shared_ptr<ObserverInterface<T>> o)
    {
        obs_.insert(o);
    }

    void remove_observer(shared_ptr<ObserverInterface<T>> o)
    {
        obs_.erase(o);
    }
    
    void update_widget(T val)
    {
        cout << "update_widget: " << val << "\n";
        widget_val_ = val;
        notify_observers();
    }
    
protected:
    void notify_observers()
    {
        for (auto &i: obs_) {
            auto ptr = i.lock();
            if (ptr) {
                ptr->update(widget_val_);
                auto d = dynamic_pointer_cast<DisplayInterface>(ptr);
                if (d == nullptr) {
                    throw runtime_error("Object doesn't have a display interface");
                 }
                 d->show();
            }
        }
    }

private:
    T widget_val_;
    set<weak_ptr<ObserverInterface<T>>, owner_less<weak_ptr<ObserverInterface<T>>>> obs_;
};

template <typename T>
class WidgetObserver: public ObserverInterface<T>, public DisplayInterface, public enable_shared_from_this<WidgetObserver<T>>
{
public:
    WidgetObserver(Widget<T> &w): w_(w)
    { }

    // we need a start() method because we can't use shared_from_this until the
    // object is actually managed by a shared_ptr. We can't use shared_from_this
    // in a constructor because the object won't be placed into the shared_ptr
    // until the object is completely constructed.
    void start()
    {
        w_.register_observer(enable_shared_from_this<WidgetObserver<T>>::shared_from_this());
    }

    void show() override
    {
        cout << "WidgeObserver: Widget contains: " << widget_val_ << endl;
    }

    void update(T val) override
    {
        widget_val_ = val;
    }

private:
    Widget<T> &w_;
    T widget_val_{};
};

template <typename T>
class AggregateObserver: public ObserverInterface<T>, public DisplayInterface, public enable_shared_from_this<AggregateObserver<T>>
{
public:
    AggregateObserver(Widget<T> &w): w_(w)
    { }

    // we need a start() method because we can't use shared_from_this until the
    // object is actually managed by a shared_ptr. We can't use shared_from_this
    // in a constructor because the object won't be placed into the shared_ptr
    // until the object is completely constructed.
    void start()
    {
        w_.register_observer(enable_shared_from_this<AggregateObserver<T>>::shared_from_this());
    }

    void show() override
    {
        cout << "AggregateObserver: Widget contains: " << widget_val_ << endl;
    }

    void update(T val) override
    {
        widget_val_ += val;
    }

private:
    Widget<T> &w_;
    T widget_val_;
};

template <typename T>
class DontCareObserver: public ObserverInterface<T>, public DisplayInterface, public enable_shared_from_this<DontCareObserver<T>>
{
public:
    DontCareObserver()
    { }

    void set_widget(Widget<T> &w)
    {
        w_ = &w;
        w_->register_observer(enable_shared_from_this<DontCareObserver<T>>::shared_from_this());
    }
    void show() override
    {
        cout << "got some widget\n";
    }

    void update(T) override
    {
        // meh
    }

private:
    Widget<T> *w_;

};

int main()
{
    Widget<string> w;
    auto wo1 = make_shared<WidgetObserver<string>>(w);
    wo1->start();

    auto wo2 = make_shared<DontCareObserver<string>>();
    wo2->set_widget(w);

    auto wo3 = make_shared<AggregateObserver<string>>(w);
    wo3->start();

    w.update_widget("Hello ");
    cout << "\n";
    w.update_widget("world ");
    cout << "\n";

    w.remove_observer(wo1);
    cout << "\nremoved WidgetObserver\n";
    w.update_widget("foo");

    wo3.reset();
    cout << "\nreset AggregateObserver\n";
    w.update_widget("bar");
}
