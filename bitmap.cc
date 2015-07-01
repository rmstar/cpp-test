#include <bitset>
#include <iostream>

int main()
{
    std::bitset<8> bitmap("1001");
    std::cout << bitmap << '\n';
    bitmap>>=3;
    std::cout << bitmap << '\n';
    bitmap<<=3;
    std::cout << bitmap << '\n';
    std::cout << bitmap.test(3) << '\n';
    bitmap.set(2);
    std::cout << bitmap << '\n';
    bitmap.reset(3);
    std::cout << bitmap << '\n';
    bitmap.flip(0);
    std::cout << bitmap << '\n';
    bitmap &= ~std::bitset<8>("1110");
    std::cout << bitmap << '\n';

}
