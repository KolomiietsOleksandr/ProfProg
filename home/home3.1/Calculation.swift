import Foundation

func calculateInverse(_ x: Double, _ y: Double, _ z: Double) -> Double {
    let product = x * y * z
    if product != 0 {
        return 1 / product
    }

    let sum = x + y + z
    if sum != 0 {
        return 1 / sum
    }

    return x + (y + 1) * (z - 1)
}

