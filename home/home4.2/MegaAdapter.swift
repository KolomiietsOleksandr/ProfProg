
// MegaAdapter.swift
class MegaAdapter: ModernCalculator {
    private let legacyCalculator: LegacyCalculator

    init() {
        self.legacyCalculator = LegacyCalculator()
    }

    func compute(_ a: Int, _ b: Int) -> Int {
        return legacyCalculator.calculate(a, b)
    }
}
