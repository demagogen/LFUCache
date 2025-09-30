#include <iostream>
#include "ideal_cache.h"

int main()
{
    size_t cache_size  = 0;
    size_t data_amount = 0;

    std::cin >> cache_size >> data_amount;

    // try
    // {
        IdealCache Cache(cache_size, data_amount);
        Cache.read_data();
        size_t hits = Cache.optimal_page();
        std::cout << hits << std::endl;
    // }
    // catch(...)
    // {
        // std::cout << "Invalid input" << std::endl;
    // }

    return 0;
}
