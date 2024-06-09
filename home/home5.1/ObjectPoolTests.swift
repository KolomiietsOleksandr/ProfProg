import XCTest
@testable import MySwiftProject

final class ObjectPoolTests: XCTestCase {

    func testObjectPool() {
        let poolSize = 10
        let pool = ObjectPool<MegaData>(create: { MegaData() }, size: poolSize)

        XCTAssertEqual(pool.size(), poolSize)
        XCTAssertEqual(pool.usedSize(), 0)

        var objects: [MegaData] = []
        for _ in 0..<poolSize {
            if let obj = pool.acquire() {
                objects.append(obj)
            } else {
                XCTFail("Failed to acquire object from pool")
            }
        }

        XCTAssertEqual(pool.usedSize(), poolSize)

        for obj in objects {
            pool.release(obj)
        }

        XCTAssertEqual(pool.usedSize(), 0)

        for _ in 0..<poolSize {
            if let obj = pool.acquire() {
                objects.append(obj)
            }
        }

        XCTAssertNil(pool.acquire(), "Expected to fail acquiring beyond pool size")
    }
}
