#include "pizza_builder.h"

PizzaBuilder::PizzaBuilder() {
    load_ingredients("ingredients.txt");
}

void PizzaBuilder::load_ingredients(const std::string& file_path) {
    std::ifstream file(file_path);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string ingredient;
        double cost;
        if (iss >> ingredient >> cost) {
            available_ingredients[ingredient] = cost;
        }
    }
}

void PizzaBuilder::add_ingredient(const std::string& ingredient) {
    if (available_ingredients.find(ingredient) != available_ingredients.end()) {
        pizza.add_ingredient(ingredient, available_ingredients[ingredient]);
    }
}

Pizza PizzaBuilder::build() const {
    return pizza;
}

std::map<std::string, double> PizzaBuilder::get_available_ingredients() const {
    return available_ingredients;
}
