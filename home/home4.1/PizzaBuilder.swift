import Foundation

class PizzaBuilder {
    private var pizza: Pizza
    private var availableIngredients: [String: Double]
    private let defaultPizzas: [String: [String: Double]] = [
        "Margherita": ["Cheese": 1.50, "Tomato": 0.50],
        "Pepperoni": ["Cheese": 1.50, "Pepperoni": 2.00],
        "Vegetarian": ["Cheese": 1.50, "Tomato": 0.50, "Mushroom": 1.00, "Onion": 0.75, "Olives": 1.25]
    ]
    init() {
        self.pizza = Pizza()
        self.availableIngredients = [
            "Cheese": 1.50,
            "Tomato": 0.50,
            "Pepperoni": 2.00,
            "Mushroom": 1.00,
            "Onion": 0.75,
            "Olives": 1.25,
            "Bacon": 2.50
        ]
    }

    func addIngredient(_ ingredient: String) {
        if let cost = availableIngredients[ingredient] {
            pizza.addIngredient(ingredient, cost: cost)
        } else {
            print("Invalid ingredient: \(ingredient)")
        }
    }

    func build() -> Pizza {
        return pizza
    }

    func getAvailableIngredients() -> [String: Double] {
        return availableIngredients
    }

    func getDefaultPizzas() -> [String: [String: Double]] {
        return defaultPizzas
    }

    func chooseDefaultPizza(named name: String) -> Pizza? {
        if let ingredients = defaultPizzas[name] {
            let pizza = Pizza()
            for (ingredient, cost) in ingredients {
                pizza.addIngredient(ingredient, cost: cost)
            }
            return pizza
        }
        return nil
    }
}
