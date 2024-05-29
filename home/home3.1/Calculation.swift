import Foundation

func calculateInverse(x: Double, y: Double, z: Double) -> Double {
    let product = x * y * z
    if product != 0 {
        return 1 / product
    } else {
        let sum = x + y + z
        if sum != 0 {
            return 1 / sum
        } else {
            return x + (y + 1) * (z - 1)
        }
    }
}