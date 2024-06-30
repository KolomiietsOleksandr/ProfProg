import Foundation

let CLASSICAL_COMMAND = "classical"
let CUSTOM_COMMAND = "custom"
let DONE_COMMAND = "done"

func handleClassicalPizzaSelection(builder: PizzaBuilder) {
    print("Available classical pizzas:")
    for (name, ingredients) in builder.getDefaultPizzas() {
        print("- \(name): \(ingredients.keys.joined(separator: ", "))")
    }
    print("Enter the name of the classical pizza you want to choose:")
    if let pizzaName = readLine() {
        if let pizza = builder.chooseDefaultPizza(named: pizzaName) {
            print("You have chosen a \(pizzaName) pizza with the following ingredients:")
            for (ingredient, cost) in pizza.getIngredients() {
                print("- \(ingredient): $\(cost)")
            }
            print("Total cost: $\(pizza.getIngredients().values.reduce(0, +))")
        } else {
            print("Invalid classical pizza name")
        }
    }
}

func handleCustomPizzaCreation(builder: PizzaBuilder) {
    print("Available ingredients:")
    for (ingredient, cost) in builder.getAvailableIngredients() {
        print("- \(ingredient): $\(cost)")
    }
    print("Enter ingredients to add to your pizza. Type '\(DONE_COMMAND)' to finish.")
    while true {
        print("> ", terminator: "")
        if let input = readLine()?.lowercased(), input != DONE_COMMAND {
            builder.addIngredient(input)
        } else {
            break
        }
    }
    let pizza = builder.build()
    print("Your pizza contains:")
    for (ingredient, cost) in pizza.getIngredients() {
        print("- \(ingredient): $\(cost)")
    }
    print("Total cost: $\(pizza.getIngredients().values.reduce(0, +))")
}

func main() {
    let builder = PizzaBuilder()
    print("Do you want to choose a classical pizza or compose a custom one?")
    print("Type '\(CLASSICAL_COMMAND)' for classical pizza, '\(CUSTOM_COMMAND)' for custom pizza:")
    if let choice = readLine()?.lowercased() {
        switch choice {
        case CLASSICAL_COMMAND:
            handleClassicalPizzaSelection(builder: builder)
        case CUSTOM_COMMAND:
            handleCustomPizzaCreation(builder: builder)
        default:
            print("Invalid choice")
        }
    }
}

main()
