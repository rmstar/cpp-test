#include <memory>
#include <iostream>


template <typename T>
bool points_to_valid_or_expired_object(const std::weak_ptr<T> &ptr)
{
    return (ptr.owner_before(std::weak_ptr<T> {}) ||
            std::weak_ptr<T>{}.owner_before(ptr));
} 

int main()
{
    std::weak_ptr<int> wp;
    std::cout << points_to_valid_or_expired_object(wp) << std::endl;

    {
        auto sp = std::make_shared<int>();
        wp = sp;
        std::cout << points_to_valid_or_expired_object(wp) << std::endl;
    }

    std::cout << points_to_valid_or_expired_object(wp) << std::endl;

    wp = std::shared_ptr<int>{};
    std::cout << points_to_valid_or_expired_object(wp) << std::endl;

    std::weak_ptr<int> wp2;
    std::cout << (wp.owner_before(wp2) || wp2.owner_before(wp)) << std::endl;

    auto sp2 = std::make_shared<int>(3);
    std::weak_ptr<int> wp3 = sp2;
    std::cout << (wp.owner_before(wp3) || wp3.owner_before(wp)) << std::endl;

    std::shared_ptr<int> sp3;
    std::cout << (wp.owner_before(sp3) || sp3.owner_before(wp)) << std::endl;
}
