#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include <ctime>
#include <cassert>
#include <unordered_map>
#include <cstdlib>
#include <cstdint>


constexpr std::size_t plus_one(std::size_t i)
{
    return i + 1;
}

template <typename K, typename V, std::size_t (*f) (std::size_t) = plus_one, typename H=std::hash<K>>
class HashTbl
{
public:
    HashTbl(int capacity = 3)
    {
        sz_ = 0;
        capacity_ = capacity;
        buckets_.resize(capacity_);
    }

    bool get(const K&k, V*v)
    {
        auto index = get_index(k);
        int i = 0;
        while (i++ < buckets_.size() && buckets_[index].inuse) {

            if (buckets_[index].key == k) {
                *v = buckets_[index].val;
                return true;
            }
            index = f(index) % capacity_;
        }

        return false;
    }


    void put(const K& k, const V& v)
    {
        if (capacity_ < sz_ * 2) {
            rehash();
        }
        put_internal(buckets_, k, v);
    }

private:
    struct HashBucket {
        K key{};
        V val{};
        bool inuse = false;
    };

    void put_internal(std::vector<HashBucket> &buckets, const K& k, const V& v)
    {
        auto index = get_index(k);
        while (buckets[index].inuse) {
            index = f(index) % capacity_;
        }

        buckets[index].inuse = true;
        buckets[index].key = k;
        buckets[index].val = v;
        ++sz_;
    }


    std::size_t get_index(const K&k)
    {
        return h_(k) % capacity_;
    }

    void rehash()
    {
        capacity_ *= 2;
        std::vector<HashBucket> tmp(capacity_);
        sz_ = 0;
        for (auto &b: buckets_) {
            if (b.inuse) {
                put_internal(tmp, b.key, b.val);
            }
        }
        buckets_ = tmp;
    }

    size_t sz_;
    size_t capacity_;
    std::vector<HashBucket> buckets_;
    H h_;
};

constexpr std::size_t mult_two(std::size_t i)
{
    return i * 2;
}

int main()
{
    HashTbl<std::string, std::string> t;
    std::string s;
    std::cout << t.get("hi", &s) << "\n";
    t.put("hi", "there");
    std::cout << t.get("hi", &s) << " " << s << "\n";

}
