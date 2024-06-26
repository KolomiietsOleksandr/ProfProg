#ifndef MEGA_ADAPTER_HPP
#define MEGA_ADAPTER_HPP

#include "ModernCalculators.hpp"
#include "LegacyCalculator.hpp"

class MegaAdapter : public BaseMegaCalculator {
private:
    LegacyCalculator legacyCalculator;
public:
    double calculate(double price) override {
        double part1 = legacyCalculator.calculatePartA(price);
        double part2 = legacyCalculator.calculatePartB(price);
        return part1 + part2;
    }
};

#endif // MEGA_ADAPTER_HPP
