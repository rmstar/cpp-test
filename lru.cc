#include <list>
#include <unordered_map>
#include <initializer_list>
#include <stdexcept>
#include <cassert>
#include <iostream>


template <class T>
class LRU 
{
public:
    LRU(std::initializer_list<T> l): list_(l)
    {
        for (auto i = list_.begin(); i != list_.end(); ++i) {
            hash_.emplace(*i, i);
        }
    }

    // most recently accessed element is placed at the beginning of the list
    void access(T elem)
    {
        auto i = hash_.find(elem);
        if (i == hash_.end()) {
            throw std::invalid_argument("Element not found");
        }
        list_.splice(list_.begin(), list_, i->second);
    }

    void insert(T val)
    {
        auto i = hash_.find(val);
        if (i != hash_.end()) {
            throw std::invalid_argument("Element already present");
        }
        list_.push_front(val);
        hash_.emplace(val, list_.begin());
    }

    void remove_oldest()
    {
        auto elem = list_.back();
        if(list_.empty()) {
            assert(hash_.empty());
            return;
        }
        hash_.erase(elem);
        list_.pop_back();
    }

    void print()
    {
        std::cout << "List: ";
        for (auto &elem: list_) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

private:
    std::list<T> list_;
    std::unordered_map<T, typename std::list<T>::iterator> hash_;
};

int main()
{
    LRU<int> lru{1, 3, 4, 5, 7, 8, 9};
    lru.print();
    lru.access(9);
    lru.access(4);
    lru.access(8);
    lru.insert(10);
    lru.print();
    lru.remove_oldest();
    lru.remove_oldest();
    lru.remove_oldest();
    lru.access(1);
    lru.remove_oldest();
    lru.print();
    try {
        lru.insert(10);
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
    try {
        lru.access(42);
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
    }
}

