/**
 * HashTableDebug.cpp
 *
 * Write your tests in this file
 */
#include "HashTable.h"
#include <iostream>

int main()
{
    HashTable ht;

    // Insertion //
    ht.insert("Alice", 1001);
    ht.insert("Bob", 2022);
    ht.insert("Charlie", 3033);

    std::cout << "-- init:\n" << ht << "\n";

    // Contains //
    std::cout << "-- Alice? " << (ht.contains("Alice") ? "Yes" : "No") << "\n";
    std::cout << "-- Eve? " << (ht.contains("Eve") ? "Yes" : "No") << "\n";

    // Operator access //
    ht["Alice"] = 1111; // update
    ht["Eve"] = 4044; // insert--this took forever :<

    std::cout << "\n-- after updates:\n" << ht << "\n";

    // Get //
    auto val = ht.get("Bob");
    if (val) {
        std::cout << "-- Bob: " << *val << "\n";
    }

    // Removal //
    ht.remove("Charlie");
    std::cout << "\n-- After removal:\n" << ht << "\n";

    // Printing //
    std::cout << "-- Keys: ";
    for (const auto& k : ht.keys()) {
        std::cout << k << " ";
    }
    std::cout << "\n";

    // In theory charlie and eve might switch places but
    // this isn't an issue... because charlie gets removed
    // (poor charlie...)
    std::cout << "-- Expected: Bob Alice Eve" << std::endl;

    // alpha //
    std::cout << "-- Alpha: " << ht.alpha() << "\n";

    return 0;
}
