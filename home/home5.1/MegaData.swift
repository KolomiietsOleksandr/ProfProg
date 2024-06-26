import Foundation

class MegaData {
    var smallArray: [Float]
    var bigArray: [Double]

    init() {
        smallArray = Array(repeating: 42.0, count: 1024)
        bigArray = Array(repeating: 42.0, count: 1024 * 1024)
    }

    func reset() {
        smallArray = Array(repeating: 42.0, count: 1024)
        bigArray = Array(repeating: 42.0, count: 1024 * 1024)
    }
}
