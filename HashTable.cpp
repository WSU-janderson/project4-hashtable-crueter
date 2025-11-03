/**
 * HashTable.cpp
 */

#include "HashTable.h"
#include <algorithm>
#include <functional>
#include <sstream>

HashTable::HashTable(size_t initCapacity)
    : currentSize(0)
    , currentCapacity(initCapacity > 0 ? initCapacity : 8)
{
    tableData.resize(currentCapacity);

    // initial gen of offsets
    if (currentCapacity > 1) {
        generateOffsets(currentCapacity);
    }
}

void HashTable::generateOffsets(size_t end)
{
    offsets.clear();
    offsets.reserve(end - 1);

    for (size_t i = 1; i < end; ++i) {
        offsets.push_back(i);
    }

    // shuffle :)
    std::shuffle(offsets.begin(), offsets.end(), rng);
}

size_t HashTable::hash(const std::string& key) const
{
    std::hash<std::string> hasher;
    return hasher(key) % currentCapacity;
}

// Neat part about using found as an output is
// we can repurpose this for like 5 different functions
size_t HashTable::probe(const std::string& key, bool& found) const
{
    // rewrote it 5 times award :P

    found = false;
    size_t home = hash(key);
    size_t firstDeleted = currentCapacity; // track first EAR for possible insertion

    // home
    const HashTableBucket& homeBucket = tableData[home];
    if (homeBucket.isOccupied()) {
        // dbg
        // std::cout << " probing home idx=" << home
        //           << " key=" << homeBucket.key
        //           << " type=" << static_cast<int>(homeBucket.type)
        //           << std::endl;

        if (homeBucket.key == key) {
            found = true;
            return home;
        }
    } else if (homeBucket.isDeleted()) {
        firstDeleted = home;
    } else {
        // truly empty, can insert here
        return home;
    }

    // Follow offsets
    for (size_t offset : offsets) {
        size_t idx = (home + offset) % currentCapacity;
        const HashTableBucket& bucket = tableData[idx];

        // dbg
        // std::cout << " probing idx=" << idx
        //           << " key=" << bucket.key
        //           << " type=" << static_cast<int>(bucket.type)
        //           << std::endl;

        if (bucket.isOccupied()) {
            if (bucket.key == key) {
                found = true;
                return idx;
            }
        } else if (bucket.isDeleted()) {
            if (firstDeleted == currentCapacity) firstDeleted = idx;
        } else {
            // empty bucket, insert here (or use first deleted)
            return (firstDeleted != currentCapacity) ? firstDeleted : idx;
        }
    }

    // fallback: insert into first deleted if available
    return (firstDeleted != currentCapacity) ? firstDeleted : home;
}

void HashTable::resize(size_t newCapacity)
{
    std::vector<HashTableBucket> oldData = tableData;

    currentCapacity = newCapacity;
    tableData.clear();
    tableData.resize(currentCapacity);
    currentSize = 0;

    generateOffsets(currentCapacity);

    // re-insert old stuf
    for (const auto& bucket : oldData) {
        if (bucket.isOccupied()) {
            insert(bucket.key, bucket.value);
        }
    }
}

bool HashTable::insert(const std::string& key, const size_t& value)
{
    if (currentSize + 1 > currentCapacity / 2) {
        resize(currentCapacity * 2);
    }

    bool found;
    size_t idx = probe(key, found);
    if (found) return false; // duplicate key

    tableData[idx].load(key, value);
    ++currentSize;
    return true;
}

bool HashTable::remove(const std::string& key)
{
    bool found;
    size_t idx = probe(key, found);
    if (!found) return false;

    tableData[idx].markDeleted(); // empty After rremoval
    --currentSize;
    return true;
}

bool HashTable::contains(const std::string& key) const
{
    bool found;
    probe(key, found);
    return found;
}

std::optional<size_t> HashTable::get(const std::string& key) const
{
    bool found;
    size_t idx = probe(key, found);

    if (!found) {
        return std::nullopt;
    }

    return tableData[idx].value;
}

size_t& HashTable::operator[](const std::string& key)
{
    bool found;
    size_t idx = probe(key, found);

    if (!found) {
        // default to 0
        // maybe a silly impl? idk
        tableData[idx].load(key, 0);
        ++currentSize;
    }

    return tableData[idx].value;
}

std::vector<std::string> HashTable::keys() const {
    std::vector<std::string> result;
    result.reserve(currentSize);
    for (const auto& bucket : tableData) {
        if (bucket.isOccupied()) {
            result.push_back(bucket.key);
        }
    }
    return result;
}

double HashTable::alpha() const {
    return static_cast<double>(currentSize) / currentCapacity;
}

size_t HashTable::capacity() const {
    return currentCapacity;
}

size_t HashTable::size() const {
    return currentSize;
}

// print me!
std::string HashTable::printMe() const {
    std::ostringstream oss;
    for (size_t i = 0; i < currentCapacity; ++i) {
        const HashTableBucket& bucket = tableData[i];
        if (bucket.isOccupied()) {
            oss << "Bucket " << i << ": " << bucket << "\n";
        }
    }
    return oss.str();
}

std::ostream& operator<<(std::ostream& os, const HashTable& hashTable) {
    os << hashTable.printMe();
    return os;
}
