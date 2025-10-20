#ifndef DRIVER_H_
#define DRIVER_H_

#include "LFU_cache.h"
#include "utils.h"

template<typename key_t, typename data_t>
class Driver
{
    private:
        size_t hits           = 0;
        size_t slow_gets      = 0;
        LFUCache<key_t, data_t> Cache;

    public:
        Driver(size_t cache_capacity) : Cache(cache_capacity) {}

        const size_t return_hits()
        {
            return hits;
        }

        const size_t return_slow_gets()
        {
            return slow_gets;
        }

        void clean_cache_work_info()
        {
            hits      = 0;
            slow_gets = 0;
        }

        template<typename function_t>
        void cache_driver(size_t data_amount, function_t slow_get_page)
        {
            data_t element; // No way to initialize all types (std::string element = 0 -- construction from null is not valid)

            for (size_t index = 0; index < data_amount; index++)
            {
                // std::getline(std::cin, element);
                std::cin >> element;
                if (!check_input("Invalid element input")) return;

                if (Cache.get(element))
                {
                    hits++;
                }
                else
                {
                    Cache.put(element, slow_get_page);
                    // data_t return_page = Cache.slow_get_page(element);
                }
            }
        }
};

#endif
