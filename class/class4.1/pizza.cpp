#include "pizza.h"

void Pizza::add_ingredient(const std::string& ingredient, double cost) {
    ingredients.push_back(ingredient);
    total_cost += cost;
}

std::vector<std::string> Pizza::get_ingredients() const {
    return ingredients;
}

double Pizza::get_total_cost() const {
    return total_cost;
}
