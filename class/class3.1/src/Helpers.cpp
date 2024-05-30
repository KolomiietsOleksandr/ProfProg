#include <algorithm>
#include <string>
#include <vector>
#include <ranges>
#include <iterator>

std::string repeatString(const std::vector<int>& vec, const std::string& str) {
    if (vec.empty()) {
        return "";
    }

    int repeatCount = *std::max_element(vec.begin(), vec.end());
    if (repeatCount <= 0) {
        return "";
    }

    auto repeatedView = std::views::repeat(str) | std::views::take(repeatCount) | std::views::join;

    std::string result;
    std::ranges::copy(repeatedView, std::back_inserter(result));

    return result;
}
