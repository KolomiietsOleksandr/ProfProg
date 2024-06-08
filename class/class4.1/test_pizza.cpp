#include "pizza.h"
#include "pizza_builder.h"
#include <iostream>
#include <cassert>
#include <print>

void run_tests() {
    // Test Pizza class
    {
        Pizza pizza;
        pizza.add_ingredient("Cheese", 1.50);
        assert(pizza.get_ingredients().size() == 1);
        assert(pizza.get_ingredients()[0] == "Cheese");
        assert(pizza.get_total_cost() == 1.50);
    }

    // Test PizzaBuilder class
    {
        PizzaBuilder builder;
        builder.load_ingredients("ingredients.txt");
        auto available_ingredients = builder.get_available_ingredients();
        assert(!available_ingredients.empty());
        builder.add_ingredient("Cheese");
        builder.add_ingredient("Tomato");
        Pizza pizza = builder.build();
        assert(pizza.get_ingredients().size() == 2);
        assert(pizza.get_total_cost() == 2.00);
    }

    // Test invalid ingredient handling
    {
        PizzaBuilder builder;
        builder.load_ingredients("ingredients.txt");
        builder.add_ingredient("InvalidIngredient");
        Pizza pizza = builder.build();
        assert(pizza.get_ingredients().empty());
        assert(pizza.get_total_cost() == 0.0);
    }

    std::println << "All tests passed!\n";
}

int main() {
    run_tests();
    return 0;
}
