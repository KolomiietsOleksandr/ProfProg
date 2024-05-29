import XCTest

class CalculationUnitTests: XCTestCase {

    func testProductNonZero() {
        // Test where product is non-zero
        let result = calculateInverse(x: 2.0, y: 3.0, z: 4.0)
        XCTAssertEqual(result, 1 / (2.0 * 3.0 * 4.0), accuracy: 1e-9)
    }

    func testProductZeroSumNonZero() {
        // Test where product is zero but sum is non-zero
        let result = calculateInverse(x: 0.0, y: 3.0, z: 4.0)
        XCTAssertEqual(result, 1 / (0.0 + 3.0 + 4.0), accuracy: 1e-9)
    }

    func testProductAndSumZero() {
        // Test where both product and sum are zero
        let result = calculateInverse(x: 0.0, y: -1.0, z: 1.0)
        XCTAssertEqual(result, 0.0 + (-1.0 + 1) * (1.0 - 1), accuracy: 1e-9)
    }

    func testRandomValues() {
        // Test with random values
        let result = calculateInverse(x: 1.5, y: 2.0, z: -1.0)
        XCTAssertEqual(result, 1 / (1.5 * 2.0 * -1.0), accuracy: 1e-9)
    }
}

#if !os(macOS)
XCTMain([
    testCase(CalculationUnitTests.allTests),
])
#endif