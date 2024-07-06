import Foundation

protocol PriceCalculable {
    func getCoefficient() -> Double
    func getBasePrice() -> Double
}

struct PricePresenter<Priority: FixedWidthInteger> {
    let priority: Priority
    func printTotalPrice<T1: PriceCalculable, T2: PriceCalculable>(_ obj1: T1, _ obj2: T2) {
        let totalPrice = Double(priority) * obj1.getCoefficient() * obj1.getBasePrice() +
                         obj2.getCoefficient() * obj2.getBasePrice()
        print("Total Price: \(totalPrice)")
    }
}

class Milk: PriceCalculable {
    func getCoefficient() -> Double { return 1.5 }
    func getBasePrice() -> Double { return 2.0 }
}

class Cookies: PriceCalculable {
    func getCoefficient() -> Double { return 2.0 }
    func getBasePrice() -> Double { return 3.5 }
}

class Pineapple: PriceCalculable {
    func getCoefficient() -> Double { return 1.8 }
    func getBasePrice() -> Double { return 5.0 }
}

func main() {
    let presenter = PricePresenter(priority: 2)

    let milk = Milk()
    let cookies = Cookies()
    let pineapple = Pineapple()

    presenter.printTotalPrice(milk, cookies)
    presenter.printTotalPrice(cookies, pineapple)
    presenter.printTotalPrice(milk, pineapple)
}

main()
