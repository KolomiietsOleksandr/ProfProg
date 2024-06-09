import Foundation

class ObjectPool<T> {
    private var pool: [T] = []
    private let maxSize: Int
    private var usedCount = 0

    init(create: () -> T, size: Int) {
        self.maxSize = size
        for _ in 0..<size {
            pool.append(create())
        }
    }

    func acquire() -> T? {
        if usedCount >= maxSize {
            return nil
        }
        usedCount += 1
        return pool.removeLast()
    }

    func release(_ object: T) {
        if usedCount > 0 {
            pool.append(object)
            usedCount -= 1
        }
    }

    func size() -> Int {
        return maxSize
    }

    func usedSize() -> Int {
        return usedCount
    }
}
