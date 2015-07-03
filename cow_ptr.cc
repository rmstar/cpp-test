#include <iostream>
#include <memory>

template <class T>
class CowPtr
{
public:
    CowPtr(T *ptr): ptr_(ptr) {}

    CowPtr(const std::shared_ptr<T> &ptr): ptr_(ptr) {}

    CowPtr(const CowPtr<T> &p): ptr_(p.ptr_) {}

    CowPtr& operator=(const CowPtr& rhs)
    {
        ptr_(rhs.ptr_);
        return *this;
    }

    const T& operator*() const
    {
        return *ptr_;
    }

    T& operator*()
    {
        detach();
        return *ptr_;
    }

    const T* operator->() const
    {
        return ptr_.operator->();
    }

    T* operator->()
    {
        detach();
        return ptr_.operator->();
    }
private:
    void detach()
    {
        if (ptr_ != nullptr && !ptr_.unique()) {
            std::cout <<"detaching!\n";
            auto tmp = ptr_.get();
            ptr_.reset(new T(*tmp));
        }
    }
    std::shared_ptr<T> ptr_;
};

int main()
{
    auto p = std::make_shared<int>(200);
    CowPtr<int> p1 = p;
    CowPtr<int> p2 = p;
    *p1 = 2;
    CowPtr<int> p3 = p;
    const CowPtr<int> p4 = p3;
    const int &ref = *p4;
    /*
     * Don't do this, ptr won't be copied
     *int &ref2 = const_cast<int&>(*p4);
     *ref2 = 100;
     */
}
