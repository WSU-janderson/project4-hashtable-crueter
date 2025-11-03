#pragma once

#include <string>
#include <iostream>

// normal = valid KV pair
// ESS = empty since start
// EAR = empty after removal
enum class BucketType { NORMAL, ESS, EAR };

/**
 * @brief Represents one "bucket" within a hash table
 */
class HashTableBucket
{
public:
    /**
     * @brief Initialize the bucket as ESS
     */
    HashTableBucket();

    /**
     * @brief initialize the K/V pairing with this bucket
     */
    HashTableBucket(const std::string& key, const size_t& value);

    /**
     * @brief loads a key-value pair into the bucket, setting it to NORMAL
     *
     * @param key The key to insert
     * @param value The value to insert
     */
    void load(const std::string& key, const size_t& value);

    /**
     * @brief check if the bucket is EAR or ESS
     *
     */
    bool isEmpty() const;

    /**
     * @brief Marks the bucket as deleted (EAR).
     */
    inline void markDeleted() { type = BucketType::EAR; }

    /**
     * @brief Check if the bucket is occupied
     */
    inline bool isOccupied() const { return type == BucketType::NORMAL; }

    /**
     * @brief Check if the bucket was deleted
     */
    inline bool isDeleted() const { return type == BucketType::EAR; }

    /**
     * @brief Check if the bucket is blank (aka empty since start)
     */
    inline bool isBlank() const { return type == BucketType::ESS; }

    /**
     * @brief helper thingy to let std::cout et al. work with this lass
     */
    friend std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket);

    // member variables are public which KIND OF HURTS ME
    // but whatever, makes my life a tad easier
    std::string key;
    size_t value;
    BucketType type;
};
