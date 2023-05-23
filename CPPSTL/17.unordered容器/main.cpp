#include <string>
#include <unordered_map>
#include <iostream>

struct StringHash {
    std::size_t operator()(const std::string& str) const {
        std::size_t hash = 0;
        for (char c : str) {
            hash = hash * 31 + c;
        }
        return hash;
    }
};

int main() {
    std::unordered_map<std::string, int, StringHash> myMap;
    myMap["apple"] = 10;
    myMap["banana"] = 20;

    std::cout << myMap["apple"] << std::endl;   // 输出：10
    std::cout << myMap["banana"] << std::endl;  // 输出：20

    return 0;
}
