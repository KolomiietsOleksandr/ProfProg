#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

const std::string DATABASE_FILE = "user_data.txt";

void loadStatistics(std::unordered_map<std::string, int> &stats) {
    std::ifstream file(DATABASE_FILE);
    std::string name;
    int count;
    while (file >> name >> count) {
        stats[name] = count;
    }
    file.close();
}

void saveStatistics(const std::unordered_map<std::string, int> &stats) {
    std::ofstream file(DATABASE_FILE, std::ofstream::trunc);
    for (const auto &pair : stats) {
        file << pair.first << " " << pair.second << std::endl;
    }
    file.close();
}

void clearStatistics() {
    std::ofstream file(DATABASE_FILE, std::ofstream::trunc);
    file.close();
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <name> [delete]" << std::endl;
        return 1;
    }

    std::string name = argv[1];
    std::string action = (argc == 3) ? argv[2] : "";

    std::unordered_map<std::string, int> stats;
    loadStatistics(stats);

    if (name == "bread") {
        clearStatistics();
        std::cout << "Welcome, bread!" << std::endl;
        return 0;
    }

    if (action == "delete") {
        stats.erase(name);
        saveStatistics(stats);
        std::cout << "Statistics for " << name << " have been reset." << std::endl;
        return 0;
    }

    if (stats.find(name) == stats.end()) {
        std::cout << "Welcome, " << name << "!" << std::endl;
        stats[name] = 1;
    } else {
        stats[name]++;
        std::cout << "Hello again(x=" << stats[name] << "), " << name << "!" << std::endl;
    }

    saveStatistics(stats);
    return 0;
}
