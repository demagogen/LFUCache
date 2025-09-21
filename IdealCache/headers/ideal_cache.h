#ifndef IDEAL_CACHE_H_
#define IDEAL_CACHE_H_

#include <vector>
#include <unordered_map>

class IdealCache
{
    private:
        size_t                          capacity;
        size_t                          data_amount;
        std::vector<int>                data;
        std::unordered_map<size_t, int> Cache;

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

        void vector_dump(size_t capacity)
        {
            for (size_t index = 0; index < capacity; index++)
            {
                std::cout << " " << data[index];
            }

            std::cout << std::endl;
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

            size_t index = 0;
            for (auto& cache_iterator : Cache)
            {
                for (index = from; index < data_amount; index++)
                {
                    if (cache_iterator.second == data[index])
                    {
                        if (index > farthest_element_index)
                        {
                            farthest_element_index = index;
                            farthest_element_key   = cache_iterator.first;
                        }

                        break;
                    }
                }
            }

            if (index == data_amount) return 0;

            return farthest_element_key;
        }

        size_t optimal_page()
        {
            size_t hits = 0;

            for (size_t index = 0; index < data_amount; index++)
            {
                if (search(data[index]))
                {
                    hits++;
                    continue;
                }

                if (capacity > Cache.size())
                {
                    Cache.emplace(data[index], data[index]);
                }
                else
                {
                    auto cache_key = predict(index + 1);
                    Cache.erase  (cache_key);
                    Cache.emplace(data[index], data[index]);
                }
            }

            return hits;
        }
};

#endif
