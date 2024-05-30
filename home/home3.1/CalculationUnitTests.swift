import XCTest

class CalculationUnitTests: XCTestCase {
    let accuracy: Double = 1e-9

    func testProductNonZero() {
        // Test where product is non-zero
        let x = 2.0
        let y = 3.0
        let z = 4.0
        let result = calculateInverse(x, y, z)
        let expectedResult = 0.041666666666666664
        XCTAssertEqual(result, expectedResult, accuracy: accuracy)
    }

    func testProductZeroSumNonZero() {
        // Test where product is zero but sum is non-zero
        let x = 0.0
        let y = 3.0
        let z = 4.0
        let result = calculateInverse(x, y, z)
        let expectedResult = 1 / (x + y + z)
        XCTAssertEqual(result, expectedResult, accuracy: accuracy)
    }

    func testProductAndSumZero() {
        // Test where both product and sum are zero
        let x = 0.0
        let y = -1.0
        let z = 1.0
        let result = calculateInverse(x, y, z)
        let expectedResult = x + (y + 1) * (z - 1)
        XCTAssertEqual(result, expectedResult, accuracy: accuracy)
    }

    func testRandomValues() {
        // Test with random values
        let x = 1.5
        let y = 2.0
        let z = -1.0
        let result = calculateInverse(x, y, z)
        let expectedResult = -0.3333333333333333
        XCTAssertEqual(result, expectedResult, accuracy: accuracy)
    }
}

#if !os(macOS)
XCTMain([
    testCase(CalculationUnitTests.allTests),
])
#endif
