// Thx Matvey787
// https://www.geeksforgeeks.org/dsa/least-frequently-used-lfu-cache-implementation/
// https://www.geeksforgeeks.org/dsa/optimal-page-replacement-algorithm/

#include <iostream>
#include <unordered_map>
#include <fstream>
#include "LFU_cache.h"

int main(int argc, char* argv[]) {
    std::ifstream input_file;
    std::ofstream output_file;
    std::streambuf* cin_buf = std::cin.rdbuf();
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
    std::cin >> data_amount;

    LFUCache cache(cache_capacity);
    size_t hits = 0;
    int key     = 0;

    for (size_t index = 0; index < data_amount; index++)
    {
        std::cin >> key;

        if (cache.get(key) != -1)
        {
            hits++;
        }
        else
        {
            cache.put(key, key);
        }
    }

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
