#include "cache.hpp"
#include <iostream>
#include <cassert>

namespace cache_lfu {
void TestEmpty (size_t capacity)
{
    LFUCache<int> cache(capacity);
    for(size_t i = 0; i < capacity; i++) {
        assert (!cache.lookup(i));
	}
}

void TestNoHits (size_t capacity)
{
    LFUCache<int> cache(capacity);
    for(size_t j = 0; j < 4; j++) {
        for(size_t i = 0; i < capacity+1; i++) {
            assert (!cache.lookup(i));
        }
    }
}

void TestIsFull (size_t capacity)
{
    LFUCache<int> cache(capacity);
    for(size_t i = 0; i < capacity*2; i++) {
		cache.lookup(i);
		if (i >= capacity-1)
            assert (cache.isFull());
        else
            assert (!cache.isFull());
	}
}

void TestRealLFU ()
{
    LFUCache<int> cache(4);
    assert(!cache.isFull());
	assert(!cache.lookup(1));
    assert(!cache.lookup(2));
    assert(!cache.lookup(3));
    assert(!cache.lookup(4)); //(4321)
    assert(cache.isFull());
    assert(!cache.lookup(5));
    assert(!cache.lookup(6));
    assert(!cache.lookup(7)); //(7654)
    assert(cache.lookup(4));  //(4765)
    assert(!cache.lookup(8)); //(4876)
    assert(cache.lookup(4));
    assert(cache.lookup(8));
    assert(cache.lookup(7));
    assert(cache.lookup(6)); //(4876)
    assert(!cache.lookup(1));
    assert(!cache.lookup(2));
    assert(!cache.lookup(3));
}

void TestOldFreq (size_t capacity)
{
    LFUCache<int> cache(capacity);
    for(size_t i = 0; i < capacity-1; i++) {
		cache.lookup(i);
		cache.lookup(i);
	}
    for(size_t i = 0; i < 100; i++) {
		assert(!cache.lookup(capacity));
		assert(!cache.lookup(capacity+1));
	}
}
} // //namespace cache_lfu

int main (int argc, char *argv[])
{
    cache_lfu::TestEmpty(500);
    cache_lfu::TestNoHits(100);
    cache_lfu::TestIsFull(150);
    cache_lfu::TestOldFreq(100);
    cache_lfu::TestRealLFU();
    std::cout << "Tests passed!" << std::endl;
	return 0;
}
