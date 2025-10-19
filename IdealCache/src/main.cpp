#include <iostream>
#include "utils.h"
#include "ideal_cache.h"

int main()
{
    size_t cache_size  = 0;
    size_t data_amount = 0;

    std::cin >> cache_size;
    if (!check_input("Invalid cache size input"))
    {
        return -1;
    }
    std::cin >> data_amount;
    if (!check_input("Invalid data amount input"))
    {
        return -1;
    }

    IdealCache Cache(cache_size, data_amount);
    Cache.read_data();
    size_t hits = Cache.optimal_page();
    std::cout << hits << std::endl;

    return 0;
}
