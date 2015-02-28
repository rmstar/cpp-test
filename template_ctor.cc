template <typename T>
class Widget
{
public:
    template<typename U>
    Widget(Widget<U> &w): data_(w.get_value()) {}

    Widget() : data_{T{}}  {}

    T get_value()
    {
        return data_;
    }

private:
    T data_;
};

int main()
{
    Widget<int> i;
    Widget<float> f;
    Widget<double> d = i;
}
