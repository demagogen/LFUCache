#ifndef IDEAL_CACHE_H_
#define IDEAL_CACHE_H_

#include <vector>
#include <unordered_map>
#include "main.h"

class IdealCache
{
    private:
        size_t                             capacity;
        size_t                             data_amount;
        std::vector<int>                   data;
        std::unordered_map<size_t, size_t> DataFrequency;
        std::unordered_map<size_t, int>    Cache;

    public:
        IdealCache(size_t capacity, size_t data_amount) :
            capacity(capacity),
            data_amount(data_amount)
        {
            IdealCache::capacity    = capacity;
            IdealCache::data_amount = data_amount;
            data.reserve(data_amount);
        }

        ~IdealCache() {}

        const void vector_dump()
        {
            for (size_t index = 0; index < data.size(); index++)
            {
                std::cout << " " << data[index];
            }

            std::cout << std::endl;
        }

        const void cache_dump()
        {
            for (const auto& cache_iterator : Cache)
            {
                std::cout << cache_iterator.first << " " << cache_iterator.second << std::endl;
            }

            std::cout << std::endl;
        }

        const void data_frequency_dump()
        {
            for (const auto& data_frequency_iterator : DataFrequency)
            {
                std::cout << data_frequency_iterator.first << " " << data_frequency_iterator.second << std::endl;
            }

            std::cout << std::endl;
        }

        void read_data()
        {
            int element = 0;

            for (size_t index = 0; index < data_amount; index++)
            {
                std::cin >> element;
                check_input("Invalid element input");
                push_back(element);
                auto data_frequency_iterator = DataFrequency.find(element);

                if (data_frequency_iterator != DataFrequency.end())
                {
                    data_frequency_iterator->second++;
                }
                else
                {
                    DataFrequency.emplace(element, 1);
                }
            }
        }

        void push_back(int element)
        {
            data.push_back(element);
        }

        bool search(size_t key)
        {
            auto cache_iterator = Cache.find(key);
            if (cache_iterator != Cache.end()) return true;
            return false;
        }

        size_t predict(size_t from)
        {
            size_t farthest_element_index = 0;
            size_t farthest_element_key   = 0;
            bool   found_farthest         = false;

            for (auto& cache_iterator : Cache)
            {
                bool found             = false;
                size_t next_occurrence = data_amount;

                for (size_t index = from; index < data_amount; index++)
                {
                    if (cache_iterator.second == data[index])
                    {
                        next_occurrence = index;
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    return cache_iterator.first;
                }
                else if (next_occurrence > farthest_element_index || !found_farthest)
                {
                    farthest_element_index = next_occurrence;
                    farthest_element_key   = cache_iterator.first;
                    found_farthest         = true;
                }
            }

            return farthest_element_key;
        }

        size_t optimal_page()
        {
            size_t hits = 0;

            for (size_t index = 0; index < data_amount; index++)
            {
                int data_element = data[index];
                // cache_dump();
                if (search(data_element))
                {
                    hits++;
                    continue;
                }

                // That is not Belady cache algo way, but I found it cool
                auto data_frequency_iterator = DataFrequency.find(data_element);
                if (data_frequency_iterator->second == 1) continue;

                if (capacity > Cache.size())
                {
                    Cache.emplace(data_element, data_element);
                }
                else
                {
                    auto cache_key = predict(index + 1);
                    Cache.erase  (cache_key);
                    Cache.emplace(data_element, data_element);
                }
            }

            return hits;
        }
};

#endif
