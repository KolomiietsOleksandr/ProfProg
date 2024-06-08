#pragma once
#include <string>

class BaseMegaCalculator {
    public :
       virtual ~BaseMegaCalculator() = default;

       virtual double getPrice() const = 0;
       virtual double getMinimalValue() const = 0;
       virtual std::string getReport() const = 0;
};

// Some constant behavior is always a good idea:-)
class ConstantCalculator : public BaseMegaCalculator {
public:
    double getPrice() const override {
        return 0.0;
    }

    double getMinimalValue() const override {
        return 0.0;
    }

    std::string getReport() const override {
        return "Sound of Silence";
    }
};

// The best ever calculator
class MyCoolCalculator : public BaseMegaCalculator {
public:
    MyCoolCalculator(double in_coef1, double in_coef2, double in_coef3) {
        coef1 = in_coef1;
        coef2 = in_coef2;
        coef3 = in_coef3;
    }

    double getPrice() const override {
        return coef1 * VAL1 + coef2 * VAL2 - coef3*VAL3;
    }

    double getMinimalValue() const override {
        return std::min(coef1 * VAL1, coef2 * VAL2);
    }

    std::string getReport() const override {
        return std::format("Some1 {}, another2 {:.3f}, and3 {:.2f}", coef1, coef2, coef3 * VAL2);
    }
private:
    double coef1;
    double coef2;
    double coef3;

    static constexpr auto VAL1 = 12.0;
    static constexpr auto VAL2 = 3.0;
    static constexpr auto VAL3 = 0.05;

};
