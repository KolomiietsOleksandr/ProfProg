#ifndef MEGADATAPOOL_H
#define MEGADATAPOOL_H

#include "MegaData.h"
#include <vector>
#include <memory>

class MegaDataPool {
public:
    explicit MegaDataPool(size_t size);

    std::shared_ptr<MegaData> acquire();
    void release(std::shared_ptr<MegaData> obj);

    size_t size() const;
    size_t usedSize() const;

private:
    size_t poolSize;
    size_t usedCount;
    std::vector<std::shared_ptr<MegaData>> pool;
    std::vector<std::shared_ptr<MegaData>> available;
};

#endif
