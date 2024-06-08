import Foundation

func main() {
    let builder = PizzaBuilder()
    print("Do you want to choose a classical pizza or compose a custom one?")
    print("Type 'classical' for classical pizza, 'custom' for custom pizza:")
    if let choice = readLine()?.lowercased() {
        if choice == "classical" {
            print("Available classical pizzas:")
            for (name, ingredients) in builder.getDefaultPizzas() {
                print("- \(name): \(ingredients.keys.joined(separator: ", "))")
            }
            print("Enter the name of the classical pizza you want to choose:")
            if let pizzaName = readLine() {
                if let pizza = builder.chooseDefaultPizza(named: pizzaName) {
                    print("You have chosen a \(pizzaName) pizza with the following ingredients:")
                    for ingredient in pizza.getIngredients() {
                        print("- \(ingredient)")
                    }
                    print("Total cost: $\(pizza.getTotalCost())")
                } else {
                    print("Invalid classical pizza name")
                }
            }
        } else if choice == "custom" {
            print("Available ingredients:")
            for (ingredient, cost) in builder.getAvailableIngredients() {
                print("- \(ingredient): $\(cost)")
            }
            print("Enter ingredients to add to your pizza. Type 'done' to finish.")
            while true {
                print("> ", terminator: "")
                if let input = readLine()?.lowercased(), input != "done" {
                    builder.addIngredient(input)
                } else {
                    break
                }
            }
            let pizza = builder.build()
            print("Your pizza contains:")
            for ingredient in pizza.getIngredients() {
                print("- \(ingredient)")
            }
            print("Total cost: $\(pizza.getTotalCost())")
        } else {
            print("Invalid choice")
        }
    }
}

main()
