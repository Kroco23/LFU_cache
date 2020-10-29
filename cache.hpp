#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>

namespace cache_lfu {
template <typename DataT, typename KeyT = int>
class LFUCache {
public:

    explicit LFUCache(size_t capacity): sz_(capacity)
    {
    }

    bool isFull() const
    {
    return (sz_==Key_Data.size());
    }

    bool lookup(const KeyT& key)
    {
        bool value;
        auto hit = Key_Data.find(key);
        if ( hit== Key_Data.end())
        {
            if (isFull()==true)
            {
                KeyT lf = Freq_Key.begin()->second; //found element to erase
                Freq_Key.erase(Key_Iter[lf]);
                Key_Data.erase(lf);
                Key_Iter.erase(lf);
            }
            Key_Data.emplace(key, long_get_elem(key));
            Key_Iter.emplace(key, Freq_Key.emplace(1, key));
            value = false;
        }
        else value = true;
        auto freq_key = Key_Iter[key] ;
        Freq_Key.erase(freq_key);
        Key_Iter[key] = Freq_Key.emplace(freq_key->first + 1, key);
        return value;
    }



private:
    DataT long_get_elem([[maybe_unused]] const KeyT& key) const
    {
            return static_cast<DataT>(1);
    }
    using CacheIt = typename std::multimap <size_t, KeyT>::iterator;
    std::unordered_map<KeyT, DataT>   Key_Data; //to store data
    std::multimap<size_t, KeyT>  Freq_Key; //to store frequency
    std::unordered_map<KeyT, CacheIt> Key_Iter; //to iterate by key
    size_t sz_;

};

}// namespace cache_lfu
