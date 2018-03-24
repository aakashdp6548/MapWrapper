#ifndef MAP_H
#define MAP_H

#include <unordered_map>
#include <map>
#include <utility>
#include <algorithm>
#include <functional>

enum class Type { Unordered, Ordered };

template <typename KeyType, typename ValueType>
class Map {
public:
    // Custom iterator wrapper for unordered and ordered map iterators
    class Iterator {
        public:
            // unordered_map constructor
            Iterator(typename std::unordered_map<KeyType, ValueType>::iterator iter)
                : type(Type::Unordered), hash_iter(iter) {}

            // map constructor
            Iterator(typename std::map<KeyType, ValueType>::iterator iter)
                : type(Type::Ordered), bst_iter(iter) {}

            // increment
            Iterator& operator++() {
                if (type == Type::Unordered) {
                    ++hash_iter;
                }
                else {
                    ++bst_iter;
                }
                return *this;
            }

            // equality
            bool operator==(const Iterator& other) {
                if (type == Type::Unordered) {
                    return hash_iter == other.hash_iter;
                }
                return bst_iter == other.bst_iter;
            }

            // inequality
            bool operator!=(const Iterator& other) {
                return !(*this == other);
            }

            // dereference
            std::pair<const KeyType, ValueType>& operator*() {
                if (type == Type::Unordered) {
                    return *hash_iter;
                }
                return *bst_iter;
            }

            // dereference and get value
            std::pair<const KeyType, ValueType>* operator->() {
                if (type == Type::Unordered) {
                    return &(*hash_iter);
                }
                return &(*bst_iter);
            }

            // returns the type of iterator
            const Type getType() const {
                return type;
            }

        private:
            friend class Map;
            Type type;
            typename std::unordered_map<KeyType, ValueType>::iterator hash_iter;
            typename std::map<KeyType, ValueType>::iterator bst_iter;
    };

    Map(Type t) : type(t) {}

    Iterator begin() {
        if (type == Type::Unordered) {
            return Iterator(hash_map.begin());
        }
        return Iterator(bst_map.begin());
    }

    Iterator end() {
        if (type == Type::Ordered) {
            return Iterator(hash_map.end());
        }
        return Iterator(bst_map.end());
    }

    size_t size() {
        if (type == Type::Unordered) {
            return hash_map.size();
        }
        return bst_map.size();
    }

    bool empty() {
        if (type == Type::Unordered) {
            return hash_map.empty();
        }
        return bst_map.empty();
    }

    size_t erase(const KeyType& key) {
        if (type == Type::Unordered) {
            return hash_map.erase(key);
        }
        return bst_map.erase(key);
    }

    void erase(Iterator& it) {
        if (type == Type::Unordered) {
            hash_map.erase(it.hash_iter);
        }
        bst_map.erase(it.bst_iter);
    }

    void insert(const KeyType& key, const ValueType& val) {
        if (type == Type::Unordered) {
            hash_map.insert(std::make_pair(key, val));
        }
        bst_map.insert(std::make_pair(key, val));
    }

    ValueType& operator[](const KeyType& key) {
        if (type == Type::Unordered) {
            return hash_map[key];
        }
        return bst_map[key];
    }

private:
    Type type;
    std::unordered_map<KeyType, ValueType> hash_map;
    std::map<KeyType, ValueType> bst_map;

};

#endif
