#include <iostream>
#include "ideal_cache.h"

int main()
{
    size_t cache_size  = 0;
    size_t data_amount = 0;

    std::cin >> cache_size >> data_amount;

    IdealCache Cache(cache_size, data_amount);

    // int element = 0;
    // for (size_t index = 0; index < data_amount; index++)
    // {
    //     std::cin >> element;
    //     Cache.push_back(element);
    // }

    Cache.read_data();
    // Cache.data_frequency_dump();

    size_t hits = Cache.optimal_page();

    std::cout << hits << std::endl;

    return 0;
}
