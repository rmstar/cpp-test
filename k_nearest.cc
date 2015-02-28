// Find the k nearest points to the origin
#include <algorithm>
#include <iostream>
#include <vector>

struct Point
{
    int x;
    int y;
};

std::vector<Point> k_nearest(const std::vector<Point> &v, int k)
{
    std::vector<Point> ret(v);
    if (v.size() < k) {
        return v;
    }

    std::nth_element(ret.begin(), ret.begin() + k, ret.end(),
                     [] (const Point &p1, const Point &p2)
                     {
                        return ( (p1.x*p1.x) + (p1.y*p1.y) < 
                                
                                 (p2.x*p2.x) + (p2.y*p2.y));
                     });
    ret.erase(ret.begin() + k, ret.end());
    return ret;
}

void print(const std::vector<Point> &v)
{
    for (auto &i: v) {
        std::cout << "(" << i.x << "," << i.y << ") ";
    }
    std::cout << std::endl;
}

int main()
{
    auto v = k_nearest({ {1, 1} , {5, 6} , {2, 4}, {3, 3}, {0, 3}}, 2);
    print(v);
    v = k_nearest({ {1, 1} , {5, 6} , {2, 4}, {3, 3}, {0, 3}}, 3);
    print(v);
    v = k_nearest({{ 5, 6} , {0, 3}}, 3);
    print(v);
    v = k_nearest({}, 3);
    print(v);
}

