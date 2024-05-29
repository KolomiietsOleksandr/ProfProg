#include "Helpers.hpp"
#include <algorithm>

double dummyFunc(double x) {
    return x > 0 ? x : 0;
}

std::string repeatString(const std::vector<int>& vec, const std::string& str) {
    if (vec.empty()) {
        return "";
    }

    int max_val = *std::max_element(vec.begin(), vec.end());
    std::string result;
    result.reserve(str.size() * max_val);

    for (int i = 0; i < max_val; ++i) {
        result += str;
    }

    return result;
}
