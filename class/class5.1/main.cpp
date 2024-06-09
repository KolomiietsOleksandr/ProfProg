#include "MegaDataPool.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <print>

void testMegaDataPool(size_t poolSize) {
    MegaDataPool pool(poolSize);

    std::println("Initial pool size: {}", pool.size());
    std::println("Initial used size: {}", pool.usedSize());

    std::vector<std::shared_ptr<MegaData>> objects;
    for (size_t i = 0; i < poolSize; ++i) {
        objects.push_back(pool.acquire());
    }

    std::println("After acquiring all objects - used size: {}", pool.usedSize());

    for (auto& obj : objects) {
        pool.release(obj);
    }

    std::println("After releasing all objects - used size: {}", pool.usedSize());

    try {
        for (size_t i = 0; i < poolSize + 1; ++i) {
            objects.push_back(pool.acquire());
        }
    } catch (const std::runtime_error& e) {
        std::println("Expected error: {}", e.what());
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::println("Usage: {} <pool size>", argv[0]);
        return 1;
    }

    size_t poolSize = std::atoi(argv[1]);
    if (poolSize <= 0) {
        std::println("Invalid pool size. Must be a positive integer.");
        return 1;
    }

    testMegaDataPool(poolSize);
    return 0;
}
