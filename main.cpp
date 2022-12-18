#include <iostream>

#include "bidirectional_list.hpp"

template <typename T>
using list_type = ctnr::BidirectionalList<T>;

int main()
{
    list_type<double> l;
    l.push_front(11);
    l.push_front(32);
    l.push_front(22);
    l.push_front(42);
    l.push_front(55);
    l.push_front(44);
    l.erase(4);
    l.out();
    std::cout << 42 << std::endl;
    return 0;
}
