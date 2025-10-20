#include <iostream>
#include <unordered_map>
#include <fstream>
#include "LFU_cache.h"
#include "utils.h"
#include "driver.h"

int return_page(size_t key)
{
    return key;
}

int main(int argc, char* argv[]) {
    std::ifstream input_file;
    std::ofstream output_file;
    std::streambuf* cin_buf  = std::cin.rdbuf();
    std::streambuf* cout_buf = std::cout.rdbuf();

    if (argc > 1)
    {
        input_file.open(argv[1]);

        if (input_file.is_open())
        {
            std::cin.rdbuf(input_file.rdbuf());
        }
    }

    if (argc > 2)
    {
        output_file.open(argv[2]);
        if (output_file.is_open())
        {
            std::cout.rdbuf(output_file.rdbuf());
        }
    }

    size_t cache_capacity = 0;
    size_t data_amount    = 0;

    std::cin >> cache_capacity;
    if (!check_input("Invalid cache capacity input")) return -1;
    std::cin >> data_amount;
    if (!check_input("Invalid data amount input")) return -1;

    Driver<size_t, int> CacheDriver(cache_capacity);
    CacheDriver.cache_driver(data_amount, return_page);
    size_t hits = CacheDriver.return_hits();

    std::cout << hits << std::endl;

    if (input_file.is_open())
    {
        input_file.close();
        std::cin.rdbuf(cin_buf);
    }

    if (output_file.is_open())
    {
        output_file.close();
        std::cout.rdbuf(cout_buf);
    }

    return 0;
}
