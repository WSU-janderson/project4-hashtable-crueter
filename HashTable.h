/**
 * HashTable.h
 */

#pragma once

#include "HashTableBucket.h"
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <vector>

/**
 * @brief hash table implementation; we use pseudo-random probing w/ open addressing
 */
class HashTable {
public:
    /**
     * @brief initialize the hash table with empty buckets
     *
     * @param initCapacity Initial number of buckets (must be > 0).
     *        Defaults to 8
     */
    explicit HashTable(size_t initCapacity = 8);

    /**
     * @brief Insert a key-value pair into the table
     *
     * @param key The key to insert
     * @param value The value to insert
     * @return true if inserted, false if the key already exists.
     */
    bool insert(const std::string& key, const size_t& value);

    /**
     * @brief remove a KV pair from the table
     *
     * @param key The key to remove
     * @return true if removed, false if key doesn't exist.
     */
    bool remove(const std::string& key);

    /**
     * @brief Check if a key is in the table
     *
     * @param key The key to check
     * @return Whether or not the key is present
     */
    bool contains(const std::string& key) const;

    /**
     * @brief Retrieve the value for a key
     *
     * @param key The key to look up
     * @return The value (I/A) -- std::nullopt otherwise --
     * If you're reading this, I hope you know what that this ;)
     */
    std::optional<size_t> get(const std::string& key) const;

    /**
     * @brief helper to access stuff in the map with array-like syntax
     *
     * @param key The key to access
     * @return A reference to the stored value--be careful
     */
    size_t& operator[](const std::string& key);

    /**
     * @brief get all the keys in the table as a vector
     *
     * @return Vector with all keys (as strings)
     */
    std::vector<std::string> keys() const;

    /**
     * @brief current load factor
     *
     * @return size / capacity
     */
    double alpha() const;

    /**
     * @brief Get the number of buckets, or the "capacity"
     *
     * @return Capacity
     */
    size_t capacity() const;

    /**
     * @brief Get the number of KV pairs
     *
     * @return size
     */
    size_t size() const;

    /**
     * @brief Helper for std::cout et al. to print out the hashtable, e.g.:
     *
     * Bucket n: <Key, value>
     *
     * Bucket n2: <Key2, value2>
     */
    friend std::ostream& operator<<(std::ostream& os, const HashTable& hashTable);

    /**
     * @brief print me :)
     *
     * String represenetation of the entire table
     */
    std::string printMe() const;

private:
    std::vector<HashTableBucket> tableData;
    std::vector<size_t> offsets;
    size_t currentSize;
    size_t currentCapacity;

    std::mt19937 rng{std::random_device{}()};

    /**
     * @brief Hash a string and get its target bucket index
     *
     * This just uses std::hash because it's ez
     */
    size_t hash(const std::string& key) const;

    /**
     * @brief Find the target index for a key; either its existing slot,
     * OR where to insert it
     *
     * If it's found, the variable passed into found is set to true
     *
     * @return The index to insert/find
     */
    size_t probe(const std::string& key, bool& found) const;

    /**
     * @brief Resize the table (usually current cap * 2)
     *
     * Also generates new offsets in the empty slots
     *
     * @param newCapacity New capacity.
     */
    void resize(size_t newCapacity);

    /**
     * @brief Generate pseudo-random offsets for open addressing use
     *
     * uses std::random
     *
     * Generates stuff in all indices :P
     */
    void generateOffsets(size_t end);
};
