#include <iostream>
#include <string>
#include <type_traits>


template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
foo(T t)
{
    std::cout <<"foo(T t)\n";
    return t;
}

std::string foo(std::string)
{
    return "string";
}

template <typename T>
void bar(T t, typename std::enable_if<std::is_arithmetic<T>::value>::type* = 0)
{
   std::cout << "bar(T)\n";
}

void bar(float)
{
    std::cout << "bar(float)\n";
}

void bar(std::string)
{
    std::cout << "bar(string)\n";
}

int main()
{
    std::cout << foo(5.000) << std::endl;
    std::cout << foo("hello") << std::endl;
    bar(1);
    bar(1.0f);
    bar("hello");
}
