#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <print>

int main() {
    std::vector<std::string> books = {
        "The Topographer’s Clown",
        "The Chamber of Beaver",
        "The Ironer of Kanban",
        "The Piglet of Tire",
        "The Border of the Unix",
        "The Half-Time Convince",
        "The Earthly Pillows",
        "The Censorship of the Ping",
        "The True Powers",
        "The Overturn of the Ling"
    };

    std::random_device rd;
    std::mt19937 g(rd());

    std::shuffle(books.begin(), books.end(), g);

    for (const auto& book : books) {
        std::println << "We recommend: " << book << std::endl;
        std::println << "Do you like this book? (yes/no): ";
        std::string response;
        std::cin >> response;
        if (response == "yes") {
            std::println << "Enjoy your book!" << std::endl;
            return 0;
        }
    }

    std::println << "Adios amigo!" << std::endl;
    return 0;
}
