#include <tuple>
#include <map>
#include <iostream>

template <typename Ret, typename ...Args>
auto
memoize(std::function<Ret (Args...)> func)
{
	std::map<std::tuple<Args...>, Ret> cache;
	return (
	[=] (Args... args) mutable
	{
		std::tuple<Args...> t(args...);
        if (cache.find(t) == cache.end()) {
            cache[t] = func(args...);
        }
        return cache[t];
	});
}

int main()
{
	auto add = [](int i, int j) {
				return i + j;
			   };
	auto f = memoize(std::function<int (int, int)>(add));
			
    std::cout << f(1, 2) << std::endl;
    std::cout << f(3, 4) << std::endl;
    std::cout << f(1, 2) << std::endl;
}
