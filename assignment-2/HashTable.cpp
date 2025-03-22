#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>

class HashTable {
private:
    struct Entry {
        int key;
        bool is_active; // To handle deleted entries

        Entry(int k) : key(k), is_active(true) {}
    };

    std::vector<Entry*> table; // Hash table as a vector of pointers to entries
    int size; // Current size of the table
    int count; // Number of active entries
    double loadFactorThreshold; // Load factor threshold

    // Hash function
    int hash(int key) const {
        return key % size;
    }

    // Probing function using quadratic probing
    int probe(int key) {
        int index = hash(key);
        int i = 0;
        while (table[index] != nullptr && (table[index]->key != key || !table[index]->is_active)) {
            index = (hash(key) + i * i) % size;
            ++i;
            if (i >= (size + 1) / 2) {
                std::cout << "Max probing limit reached!" << std::endl;
                return -1; // Indicating probing failed
            }
        }
        return index; // Return the index where the key can be inserted
    }

    // Resize function
    void resize() {
        int newSize = next_prime(size * 2);
        std::vector<Entry*> old_table = table; // Save the old table
        size = newSize; // Update to the new size
        table = std::vector<Entry*>(size, nullptr); // Create a new table
        count = 0; // Reset count for reinserting

        // Reinsert old entries
        for (size_t i = 0; i < old_table.size(); ++i) {
            if (old_table[i] != nullptr && old_table[i]->is_active) {
                insert(old_table[i]->key);
            }
            delete old_table[i]; // Clean up old entries
        }
    }

    // Find the next prime number greater than n
    int next_prime(int n) {
        while (true) {
            bool is_prime = true;
            for (int i = 2; i * i <= n; ++i) {
                if (n % i == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) return n;
            ++n;
        }
    }

public:
    HashTable(int initial_size = 11) : size(initial_size), count(0), loadFactorThreshold(0.8) {
        table.resize(size, nullptr); // Initialize the table
    }

    // Insert function
    void insert(int key) {
        // Check load factor and resize if necessary
        if (count / static_cast<double>(size) >= loadFactorThreshold) {
            resize();
        }

        int index = probe(key);
        if (index == -1) { // Max probing limit reached
            return; // Early return if probing failed
        }

        // Insert the key if it's not already in the table
        if (table[index] != nullptr && table[index]->is_active) {
            std::cout << "Duplicate key insertion is not allowed" << std::endl;
            return;
        }

        if (table[index] == nullptr) {
            table[index] = new Entry(key);
            ++count; // Increment the count of entries
        }
    }

    // Remove function
    void remove(int key) {
        int index = hash(key);
        int i = 0;

        while (table[index] != nullptr) {
            if (table[index]->key == key && table[index]->is_active) {
                table[index]->is_active = false; // Mark as deleted
                --count; // Decrement count
                return;
            }
            index = (hash(key) + i * i) % size;
            ++i;
        }

        std::cout << "Element not found" << std::endl; // Not found
    }

    // Search function
    int search(int key) {
        int index = hash(key);
        int i = 0;

        while (table[index] != nullptr) {
            if (table[index]->key == key && table[index]->is_active) {
                return index; // Return index if found
            }
            index = (hash(key) + i * i) % size;
            ++i;
        }

        return -1; // Not found
    }

    // Print the table
    void printTable() const {
        for (int i = 0; i < size; ++i) {
            if (table[i] != nullptr && table[i]->is_active) {
                std::cout << table[i]->key << " ";
            } else {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }

    // Destructor to clean up memory
    ~HashTable() {
        for (size_t i = 0; i < table.size(); ++i) {
            delete table[i]; // Clean up each entry
        }
    }
};

#endif // HASHTABLE_H
//test