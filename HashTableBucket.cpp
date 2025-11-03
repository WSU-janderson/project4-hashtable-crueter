#include "HashTableBucket.h"

HashTableBucket::HashTableBucket() : type(BucketType::ESS) {}

HashTableBucket::HashTableBucket(const std::string& key, const size_t& value)
    : key(key), value(value), type(BucketType::NORMAL) {}

void HashTableBucket::load(const std::string& key, const size_t& value) {
    this->key = key;
    this->value = value;
    type = BucketType::NORMAL;
}

// a bucket is empty if it's EAR or ESS
bool HashTableBucket::isEmpty() const {
    return type != BucketType::NORMAL;
}

std::ostream& operator<<(std::ostream& os, const HashTableBucket& bucket) {
    if (bucket.type == BucketType::NORMAL) {
        os << "<" << bucket.key << ", " << bucket.value << ">";
    }
    return os;
}
