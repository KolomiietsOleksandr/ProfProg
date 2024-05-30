#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <format>
#include <print>

namespace {
    constexpr const char* DATABASE_FILE = "user_data.txt";
    constexpr const char* DELETE_COMMAND = "delete";
    constexpr const char* BREAD_COMMAND = "bread";
}

class UserHistory {
public:
    explicit UserHistory(const std::string& filename)
        : filename_(filename) {
        loadStatistics();
    }

    ~UserHistory() {
        saveStatistics();
    }

    void loadStatistics() {
        std::ifstream file(filename_);
        std::string name;
        int count;
        while (file >> name >> count) {
            stats_[name] = count;
        }
    }

    void saveStatistics() const {
        std::ofstream file(filename_, std::ofstream::trunc);
        for (const auto& pair : stats_) {
            std::println(file, "{} {}", pair.first, pair.second);
        }
    }

    void clearStatistics() {
        stats_.clear();
    }

    bool hasUser(const std::string& name) const {
        return stats_.find(name) != stats_.end();
    }

    void addUser(const std::string& name) {
        stats_[name] = 1;
    }

    void incrementUserCount(const std::string& name) {
        if (hasUser(name)) {
            stats_[name]++;
        }
    }

    void deleteUser(const std::string& name) {
        stats_.erase(name);
    }

    int getUserCount(const std::string& name) const {
        auto it = stats_.find(name);
        if (it != stats_.end()) {
            return it->second;
        }
        return 0;
    }

private:
    std::string filename_;
    std::unordered_map<std::string, int> stats_;
};

int main(int argc, char* argv[]) {
    if (argc < 2 || argc > 3) {
        std::cerr << "Usage: " << argv[0] << " <name> [delete]" << std::endl;
        return 1;
    }

    std::string name = argv[1];
    std::string action = (argc == 3) ? argv[2] : "";

    UserHistory userHistory(DATABASE_FILE);

    if (name == BREAD_COMMAND) {
        userHistory.clearStatistics();
        std::println("Welcome, bread!");
        return 0;
    }

    if (action == DELETE_COMMAND) {
        userHistory.deleteUser(name);
        std::println("Statistics for {} have been reset.", name);
        return 0;
    }

    if (!userHistory.hasUser(name)) {
        std::println("Welcome, {}!", name);
        userHistory.addUser(name);
    } else {
        userHistory.incrementUserCount(name);
        std::println("Hello again(x={}), {}!", userHistory.getUserCount(name), name);
    }

    return 0;
}
