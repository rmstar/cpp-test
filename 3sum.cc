#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template <typename It, typename T>
bool two_sum_internal(It start,
                      It end,
                      T val)
                       
{
    for (auto it = start; it != end;) {
        int num = val - *it;
        auto i = find(++it, end, num);
        if(i != end) {
            return true;
        }
    }
    return false;
}

template <typename C, typename T>
bool two_sum(C v, T val)
{
    sort(v.begin(), v.end());
    return two_sum_internal(v.begin(), v.end(), val);
}

template <typename C, typename T>
bool three_sum(C v, T val)
{
    sort(v.begin(), v.end());
    for (auto it = v.begin(); it != v.end();) {
        int num = val - *it;
         if (two_sum_internal(++it, v.end(), num)) {
             return true;
         }
    }
    return false;
}


int main()
{
    vector<int> v {3, 2, 5, 7};

    cout << two_sum(v, 4) << endl;
    cout << two_sum(v, 9) << endl;
    cout << three_sum(v, 9) << endl;
    cout << three_sum(v, 7) << endl;
    cout << three_sum(v, 15) << endl;
    cout << three_sum(v, 10) << endl;
    cout << three_sum(v, 17) << endl;
}

