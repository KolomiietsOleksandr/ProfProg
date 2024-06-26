#include <string>

#include <memory>
#include <print>

#include "ModernCalculators.hpp"
#include "LegacyCalculator.hpp"
#include "MegaAdapter.hpp"


void printResults(const std::unique_ptr<BaseMegaCalculator>& calculator) {
    std::println("Current price: {}", calculator->getPrice());
    std::println("Current minimal value: {}", calculator->getMinimalValue());
    std::println("Current report: {}", calculator->getReport());
}

int main() {
    std::unique_ptr<BaseMegaCalculator> calculator = std::make_unique<MyCoolCalculator>(6.0, 12.1, 3.2);
    printResults(calculator);

    calculator = std::make_unique<ConstantCalculator>();
    printResults(calculator);

    calculator = std::make_unique<MegaAdapter>(std::make_unique<LegacyCalculator>(1.34, 5.4));
    printResults(calculator);
    return 0;
}
