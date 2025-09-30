#include <iostream>
#include "ideal_cache.h"
#include "main.h"

void check_input(std::string error_message)
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cout << error_message << std::endl;
        exit(0);
    }
}

int main()
{
    size_t cache_size  = 0;
    size_t data_amount = 0;

    std::cin >> cache_size;
    check_input("Invalid cache size input");
    std::cin >> data_amount;
    check_input("Invalid data amount input");

    IdealCache Cache(cache_size, data_amount);
    Cache.read_data();
    size_t hits = Cache.optimal_page();
    std::cout << hits << std::endl;

    return 0;
}
