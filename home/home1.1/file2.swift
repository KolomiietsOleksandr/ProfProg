import Foundation

func solveQuadraticEquation(a: Double, b: Double, c: Double) -> (Double?, Double?) {
    let determinant = b * b - 4 * a * c

    if determinant > 0 {
        let root1 = (-b + sqrt(determinant)) / (2 * a)
        let root2 = (-b - sqrt(determinant)) / (2 * a)
        return (root1, root2)
    } else if determinant == 0 {
        let root = -b / (2 * a)
        return (root, root)
    } else {
        return (nil, nil)
    }
}

func readDouble(prompt: String) -> Double {
    print(prompt, terminator: ": ")
    if let input = readLine(), let value = Double(input) {
        return value
    } else {
        print("Invalid value. Please try again.")
        return readDouble(prompt: prompt)
    }
}

let a = readDouble(prompt: "Enter the coefficient a")
let b = readDouble(prompt: "Enter the coefficient b")
let c = readDouble(prompt: "Enter the coefficient c")

let roots = solveQuadraticEquation(a: a, b: b, c: c)
if let root1 = roots.0, let root2 = roots.1 {
    if root1 == root2 {
        print("The equation has one real root: \(root1)")
    } else {
        print("The equation has two real root: \(root1) і \(root2)")
    }
} else {
    print("The equation hasn`t real root.")
}
