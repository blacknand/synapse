#ifndef CACHE_H
#define CACHE_H

template<typename T>
class SynapseCache
{
private:
    SynapseCache() : {}
    ~SynapseCache() : {}

    SynapseCache(const SynapseCache&) = delete;
    SynapseCache& operator=(SynapseCache&) = delete;
public:
    void put(const T&) const;
    T& get(const T&) const;
    T& erase(T&);
    int size_of(const T&) const;
}

#endif // CACHE_H