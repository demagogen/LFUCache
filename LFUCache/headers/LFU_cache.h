#ifndef LFU_CACHE_H_
#define LFU_CACHE_H_

#include <list>
#include <unordered_map>
#include <iterator>
#include <cstddef>

class LFUCache
{
    private:
        struct Element
        {
            int    value;
            size_t frequency;
            std::list<int>::iterator iterator;
        };

        size_t capacity;
        size_t min_frequency;
        std::unordered_map<size_t, Element> Cache;
        std::unordered_map<size_t, std::list<int>> FrequencyMap;

    public:
        LFUCache(size_t capacity) : capacity(capacity)
        {
            if (capacity == 0)
            {
                throw std::invalid_argument("Zero capacity error\n");
            }

            LFUCache::capacity = capacity;
            min_frequency      = 0;
        }

        int get(size_t key)
        {
            if (Cache.find(key) == Cache.end())
            {
                return -1;
            }

            update_frequency(key);
            return Cache[key].value;
        }

        void put(size_t key, int value)
        {
            if (Cache.find(key) != Cache.end())
            {
                Cache[key].value = value;
                update_frequency(key);
                return;
            }

            if (Cache.size() >= capacity)
            {2
                remove();
            }

            min_frequency = 1;
            FrequencyMap[1].push_front(key);
            Cache[key] = {value, 1, FrequencyMap[1].begin()};
            Cache.emplace(key, Element{value, 1, FrequencyMap[1].begin()});
        }

    private:
        void update_frequency(size_t key)
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

            size_t key_to_remove = FrequencyMap[min_frequency].back();
            FrequencyMap[min_frequency].pop_back();
            Cache.erase(key_to_remove);

            if (FrequencyMap[min_frequency].empty())
            {
                FrequencyMap.erase(min_frequency);
            }
        }
};

#endif
