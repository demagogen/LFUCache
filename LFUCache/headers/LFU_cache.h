#ifndef LFU_CACHE_H_
#define LFU_CACHE_H_

#include <list>
#include <unordered_map>
#include <iterator>
#include <cstddef>
#include "main.h"

template<typename key_t, typename data_t>
class LFUCache
{
    private:
        struct Element
        {
            data_t                               value;
            size_t                               frequency;
            typename std::list<data_t>::iterator iterator;
        };

        size_t                                        capacity;
        size_t                                        min_frequency;
        std::list<std::pair<key_t, data_t>>           Data;
        std::unordered_map<key_t, Element>            Cache;
        std::unordered_map<size_t, std::list<data_t>> FrequencyMap;

    public:
        LFUCache(size_t capacity) : capacity(capacity)
        {
            LFUCache::capacity = capacity;
            min_frequency      = 0;
        }

        size_t driver(size_t data_amount)
        {
            data_t element; // No way to initialize all types (std::string element = 0 -- construction from null is not valid)
            size_t hits    = 0;

            for (size_t index = 0; index < data_amount; index++)
            {
                // std::getline(std::cin, element);
                std::cin >> element;
                check_input("Invalid element input");
                Data.emplace_back(element, element);

                if (get(element))
                {
                    hits++;
                }
                else
                {
                    put(element, element);
                }
            }

            return hits;
        }

    private:
        data_t slow_get_page(key_t key)
        {
            auto iterator = Data.find(key);
            return iterator->second.value;
        }

        bool get(key_t key)
        {
            auto iterator = Cache.find(key);

            if (iterator == Cache.end())
            {
                return false;
            }

            update_frequency(key);

            return true;
        }

        void put(key_t key, data_t value)
        {
            auto iterator = Cache.find(key);

            if (iterator != Cache.end())
            {
                update_frequency(key);
                return;
            }

            if (Cache.size() >= capacity)
            {
                remove();
            }

            min_frequency = 1;
            FrequencyMap[min_frequency].push_front(key);
            Cache.emplace(key, Element{value, 1, FrequencyMap[min_frequency].begin()});
        }

        void update_frequency(key_t key)
        {
            auto iterator = Cache.find(key);
            if (iterator == Cache.end()) return;

            Element& element = iterator->second;
            size_t old_frequency = element.frequency;
            size_t new_frequency = element.frequency + 1;

            FrequencyMap[old_frequency].erase(element.iterator);

            if (FrequencyMap[old_frequency].empty())
            {
                FrequencyMap.erase(old_frequency);
                if (min_frequency == old_frequency)
                {
                    min_frequency = new_frequency;
                }
            }

            FrequencyMap[new_frequency].push_front(key);
            element.iterator = FrequencyMap[new_frequency].begin();
            element.frequency = new_frequency;
        }

        void remove()
        {
            while (FrequencyMap[min_frequency].empty())
            {
                min_frequency++;
            }

            data_t key_to_remove = FrequencyMap[min_frequency].back();
            FrequencyMap[min_frequency].pop_back();
            Cache.erase(key_to_remove);

            if (FrequencyMap[min_frequency].empty())
            {
                FrequencyMap.erase(min_frequency);
            }
        }
};

#endif
