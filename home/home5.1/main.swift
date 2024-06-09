import Foundation

func main() {
    let poolSize = 10
    let pool = ObjectPool<MegaData>(create: { MegaData() }, size: poolSize)

    print("Initial pool size: \(pool.size())")
    print("Initial used size: \(pool.usedSize())")

    var objects: [MegaData] = []
    for _ in 0..<poolSize {
        if let obj = pool.acquire() {
            objects.append(obj)
        } else {
            print("Failed to acquire object from pool")
        }
    }

    print("After acquiring all objects - used size: \(pool.usedSize())")

    for obj in objects {
        pool.release(obj)
    }

    print("After releasing all objects - used size: \(pool.usedSize())")

    for _ in 0..<poolSize {
        if let obj = pool.acquire() {
            objects.append(obj)
        }
    }

    if pool.acquire() == nil {
        print("Expected to fail acquiring beyond pool size")
    }
}

main()
