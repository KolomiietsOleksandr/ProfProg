#include "MegaDataPool.h"
#include <stdexcept>

MegaDataPool::MegaDataPool(size_t size) : poolSize(size), usedCount(0) {
    pool.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        pool.push_back(std::make_shared<MegaData>());
        available.push_back(pool[i]);
    }
}

std::shared_ptr<MegaData> MegaDataPool::acquire() {
    if (available.empty()) {
        throw std::runtime_error("No available objects in the pool");
    }
    auto obj = available.back();
    available.pop_back();
    ++usedCount;
    return obj;
}

void MegaDataPool::release(std::shared_ptr<MegaData> obj) {
    obj->reset();
    available.push_back(obj);
    --usedCount;
}

size_t MegaDataPool::size() const {
    return poolSize;
}

size_t MegaDataPool::usedSize() const {
    return usedCount;
}
