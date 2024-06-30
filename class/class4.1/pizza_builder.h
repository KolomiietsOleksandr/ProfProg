#ifndef PIZZA_BUILDER_H
#define PIZZA_BUILDER_H

#include "pizza.h"
#include <map>
#include <string>
#include <fstream>
#include <sstream>

class PizzaBuilder {
public:
    PizzaBuilder();
    void load_ingredients(const std::string& file_path);
    void add_ingredient(const std::string& ingredient);
    Pizza build();
    std::map<std::string, double> get_available_ingredients() const;

private:
    Pizza pizza;
    std::map<std::string, double> available_ingredients;
};

#endif // PIZZA_BUILDER_H
