#include <iostream>
#include <unordered_map>
#include <fstream>
#include "main.h"
#include "LFU_cache.h"

void check_input(std::string error_message)
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cout << error_message << std::endl;
        exit(0);
    }
}

// /*
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
    check_input("Invalid cache capacity input");
    std::cin >> data_amount;
    check_input("Invalid data amount input");

    LFUCache<size_t, int> Cache(cache_capacity);
    size_t hits = Cache.driver(data_amount);

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
// */

/*
int main()
{
    size_t cache_capacity = 0;
    size_t data_amount    = 0;

    std::cin >> cache_capacity;
    check_input("Invalid cache capacity input");
    std::cin >> data_amount;
    check_input("Invalid data amount input");

    LFUCache<std::string, std::string> Cache(cache_capacity);
    size_t hits = Cache.driver(data_amount);

    std::cout << hits;
}
*/
