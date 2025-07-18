#ifndef CONCURRENT_HASH_MAP_H
#define CONCURRENT_HASH_MAP_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <shared_mutex>

template<typename Key, typename Value, typename Hash = std::hash<Key>>
class ConcurrentHashMap
{
private:
    struct Shard
    {
        std::unordered_map hash_map;
        mutable std::shared_mutex mutex_;
    } 
    std::vector<Shard> shards;

    ConcurrentHashMap() {}
    ~ConcurrentHashMap() {}

    ConcurrentHashMap(const ConcurrentHashMap&) = delete;
    ConcurrentHashMap operator=(ConcurrentHashMap&) = delete;
public:
    void insert(const Key& key, const Value& val);
    const Value& get(const Key& key) const;
    const Value& erase(const Key& key) const;
}

#endif  // CONCURRENT_HASH_MAP_H


// update gemini to tell me which chapter/section of the book to read before doing a feature
// + maybe explain i need to learn rather than it doing it for me 