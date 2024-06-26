#ifndef PIZZA_H
#define PIZZA_H

#include <vector>
#include <string>
#include <iostream>

class Pizza {
public:
    void add_ingredient(const std::string& ingredient, double cost);
    std::vector<std::string> get_ingredients() const;
    double get_total_cost() const;

private:
    std::vector<std::string> ingredients;
    double total_cost = 0.0;
};

#endif // PIZZA_H
