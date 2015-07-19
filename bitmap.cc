#include <bitset>
#include <iostream>

template <std::size_t N>
void iterate_bits(const std::bitset<N> &bs)
{
    for(int i = 0; i < bs.size(); ++i) {
        std::cout << bs[i];
    }
    std::cout << "\n";
}

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
    std::cout << "iterate_bits: ";
    iterate_bits(bitmap);

    std::bitset<4> bs("1110");
    // prints MSB-> LSB
    std::cout << bs << "\n";
    // prints 0111,LSB->MSB
    iterate_bits(bs);
}
