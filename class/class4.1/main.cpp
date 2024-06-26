#include "pizza_builder.h"
#include <iostream>
#include <string>
#include <print>

int main() {
    PizzaBuilder builder;
    std::string input;
    std::println << "Available ingredients:\n";
    for (const auto& [ingredient, cost] : builder.get_available_ingredients()) {
        std::println << "- " << ingredient << ": $" << cost << "\n";
    }

    std::println << "Enter ingredients to add to your pizza. Type 'done' to finish.\n";
    while (true) {
        std::println << "> ";
        std::cin >> input;
        if (input == "done") {
            break;
        }
        builder.add_ingredient(input);
    }

    Pizza pizza = builder.build();
    std::println << "Your pizza contains:\n";
    for (const auto& ingredient : pizza.get_ingredients()) {
        std::println << "- " << ingredient << "\n";
    }
    std::println << "Total cost: $" << pizza.get_total_cost() << "\n";

    return 0;
}
