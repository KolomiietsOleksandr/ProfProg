
import Foundation

enum MyDataType {
    case integer(Int16)
    case string(String)
    case map([String: MyDataType])

    func serialize() -> Data {
        var data = Data()
        switch self {
        case .integer(let value):
            if value >= 0 {
                if value <= 0x7f {
                    data.append(UInt8(value))
                } else {
                    data.append(0xd1)
                    data.append(contentsOf: withUnsafeBytes(of: value.bigEndian, Array.init))
                }
            } else {
                data.append(0xd1)
                data.append(contentsOf: withUnsafeBytes(of: value.bigEndian, Array.init))
            }
        case .string(let value):
            data.append(0xa0 | UInt8(value.count))
            data.append(contentsOf: value.utf8)
        case .map(let map):
            data.append(0x80 | UInt8(map.count))
            for (key, value) in map {
                data.append(key.serialize())
                data.append(value.serialize())
            }
        }
        return data
    }

    static func deserialize(from data: Data) -> (MyDataType, Int)? {
        var index = 0
        let type = data[index]
        index += 1

        if type <= 0x7f {
            return (.integer(Int16(type)), index)
        } else if type >= 0xa0 && type <= 0xbf {
            let length = Int(type & 0x1f)
            let stringData = data.subdata(in: index..<index+length)
            let string = String(data: stringData, encoding: .utf8)!
            index += length
            return (.string(string), index)
        } else if type >= 0x80 && type <= 0x8f {
            let count = Int(type & 0x0f)
            var map = [String: MyDataType]()
            for _ in 0..<count {
                let (key, keyLength) = deserializeString(from: data, startingAt: index)!
                index += keyLength
                let (value, valueLength) = MyDataType.deserialize(from: data.subdata(in: index..<data.count))!
                index += valueLength
                map[key] = value
            }
            return (.map(map), index)
        } else if type == 0xd1 {
            let value = Int16(bigEndian: data.subdata(in: index..<index+2).withUnsafeBytes { $0.pointee })
            index += 2
            return (.integer(value), index)
        } else {
            return nil
        }
    }

    static func deserializeString(from data: Data, startingAt index: Int) -> (String, Int)? {
        let type = data[index]
        let length = Int(type & 0x1f)
        let stringData = data.subdata(in: index+1..<index+1+length)
        let string = String(data: stringData, encoding: .utf8)!
        return (string, length + 1)
    }
}

extension String {
    func serialize() -> Data {
        var data = Data()
        data.append(0xa0 | UInt8(self.count))
        data.append(contentsOf: self.utf8)
        return data
    }
}

func main() {
    let intData = MyDataType.integer(12345)
    let strData = MyDataType.string("Hello, MsgPack!")
    let mapData = MyDataType.map([
        "key1": .integer(42),
        "key2": .string("Value"),
        "key3": .map([
            "nestedKey": .string("NestedValue")
        ])
    ])

    let intSerialized = intData.serialize()
    let strSerialized = strData.serialize()
    let mapSerialized = mapData.serialize()

    print(intSerialized)
    print(strSerialized)
    print(mapSerialized)

    let (intDeserialized, _) = MyDataType.deserialize(from: intSerialized)!
    let (strDeserialized, _) = MyDataType.deserialize(from: strSerialized)!
    let (mapDeserialized, _) = MyDataType.deserialize(from: mapSerialized)!

    print(intDeserialized)
    print(strDeserialized)
    print(mapDeserialized)
}

main()
