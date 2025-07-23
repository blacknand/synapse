#ifndef CONCURRENT_HASH_MAP_H
#define CONCURRENT_HASH_MAP_H

#include <vector>
#include <unordered_map>
#include <functional>
#include <shared_mutex>
#include <mutex>
#include <optional>

template<typename Key, typename Value, typename Hash = std::hash<Key>>
class ConcurrentHashMap
{
private:
    struct Shard
    {
        std::unordered_map<Key, Value, Hash> hash_map;
        mutable std::shared_mutex mutex_;
    } 

    Shard& get_shard(const Key& key) 
    {
        return shards.at(hasher(key) % shards.size());
    }

    const Shard& get_shard(const Key& key) const 
    {
        return shards.at(hasher(key) % shards.size());
    }

    Hash hasher;
    std::vector<Shard> shards;
public:
    ConcurrentHashMap(size_t shard_count = 32) : shards(shard_count) {}
    ~ConcurrentHashMap() {}

    ConcurrentHashMap(const ConcurrentHashMap&) = delete;
    ConcurrentHashMap operator=(ConcurrentHashMap&) = delete;

    void insert(const Key& key, const Value& val)
    {
        auto& shard = get_shard(key);
        std::unique_lock lock(shard.mutex_);
        shard.hash_map[key] = value;
    }

    std::optional<Value> get(const Key& key) const
    {
        const auto& shard = get_shard(key);
        std::shared_lock lock(shard.mutex_);
        if (auto it = shard.hash_map.find(key); it != shard.hash_map.end())
            return it->second;
        return std::nullptr;
    }

    const Value& erase(const Key& key) 
    {
        auto& shard = get_shard(key);
        std::unique_lock lock(shard.mutex_);
        shard.hash_map.erase(key);
    }
}

#endif  // CONCURRENT_HASH_MAP_H