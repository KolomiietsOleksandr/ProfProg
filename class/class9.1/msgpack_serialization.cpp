#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <cstdint>

class MyDataType {
public:
    enum Type {
        INTEGER,
        STRING,
        MAP
    };

    MyDataType(int16_t intValue) : type(INTEGER), intValue(intValue) {}
    MyDataType(const std::string& strValue) : type(STRING), strValue(strValue) {}
    MyDataType(const std::vector<std::pair<std::string, MyDataType>>& mapValue) : type(MAP), mapValue(mapValue) {}

    Type getType() const { return type; }
    int16_t getIntValue() const { return intValue; }
    const std::string& getStringValue() const { return strValue; }
    const std::vector<std::pair<std::string, MyDataType>>& getMapValue() const { return mapValue; }

private:
    Type type;
    int16_t intValue;
    std::string strValue;
    std::vector<std::pair<std::string, MyDataType>> mapValue;
};

std::vector<uint8_t> serialize(const MyDataType& data);

std::vector<uint8_t> serializeInt(int16_t value) {
    std::vector<uint8_t> result;
    if (value >= 0) {
        if (value <= 0x7f) {
            result.push_back(static_cast<uint8_t>(value));
        } else {
            result.push_back(0xd1);
            result.push_back(static_cast<uint8_t>(value >> 8));
            result.push_back(static_cast<uint8_t>(value));
        }
    } else {
        result.push_back(0xd1);
        result.push_back(static_cast<uint8_t>(value >> 8));
        result.push_back(static_cast<uint8_t>(value));
    }
    return result;
}

std::vector<uint8_t> serializeString(const std::string& value) {
    std::vector<uint8_t> result;
    result.push_back(static_cast<uint8_t>(0xa0 | value.size()));
    result.insert(result.end(), value.begin(), value.end());
    return result;
}

std::vector<uint8_t> serializeMap(const std::vector<std::pair<std::string, MyDataType>>& map) {
    std::vector<uint8_t> result;
    result.push_back(static_cast<uint8_t>(0x80 | map.size()));
    for (const auto& pair : map) {
        std::vector<uint8_t> key = serializeString(pair.first);
        result.insert(result.end(), key.begin(), key.end());
        std::vector<uint8_t> value = serialize(pair.second);
        result.insert(result.end(), value.begin(), value.end());
    }
    return result;
}

std::vector<uint8_t> serialize(const MyDataType& data) {
    switch (data.getType()) {
        case MyDataType::INTEGER:
            return serializeInt(data.getIntValue());
        case MyDataType::STRING:
            return serializeString(data.getStringValue());
        case MyDataType::MAP:
            return serializeMap(data.getMapValue());
    }
    return {};
}

void saveToFile(const std::string& filename, const std::vector<uint8_t>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(data.data()), data.size());
        file.close();
    } else {
        std::cerr << "Failed to open file for writing." << std::endl;
    }
}

int main() {
    MyDataType intData(3213);
    MyDataType strData("Test");
    MyDataType mapData({
        {"key1", MyDataType(42)},
        {"key2", MyDataType("Value")},
        {"key3", MyDataType({
            {"nestedKey", MyDataType("NestedValue")}
        })}
    });

    saveToFile("intData.msgpack", serialize(intData));
    saveToFile("strData.msgpack", serialize(strData));
    saveToFile("mapData.msgpack", serialize(mapData));

    return 0;
}
