import Foundation

class Pizza {
    private var ingredients: [String]
    private var totalCost: Double

    init() {
        self.ingredients = []
        self.totalCost = 0.0
    }

    func addIngredient(_ ingredient: String, cost: Double) {
        ingredients.append(ingredient)
        totalCost += cost
    }

    func getIngredients() -> [String] {
        return ingredients
    }

    func getTotalCost() -> Double {
        return totalCost
    }
}
