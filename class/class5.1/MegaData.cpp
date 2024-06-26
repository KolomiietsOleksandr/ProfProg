#include "MegaData.h"
#include <algorithm>

MegaData::MegaData() {
    reset();
}

void MegaData::reset() {
    std::fill(std::begin(smallArray), std::end(smallArray), 42.0f);
    std::fill(std::begin(bigArray), std::end(bigArray), 42.0);
}
