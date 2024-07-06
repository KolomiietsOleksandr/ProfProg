#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>

struct GreenMessage {
    std::string text;
    int counter;
};

struct BlueMessage {
    double value1;
    double value2;
};

struct OrangeMessage {
    std::string text1;
    std::string text2;
    int integer;
    double value;
};

class MessageDispatcher {
public:
    void publishGreenMessage(const GreenMessage& msg) {
        std::unique_lock<std::mutex> lock(mtx);
        for (auto& subscriber : greenSubscribers) {
            subscriber(msg);
        }
    }

    void publishBlueMessage(const BlueMessage& msg) {
        std::unique_lock<std::mutex> lock(mtx);
        for (auto& subscriber : blueSubscribers) {
            subscriber(msg);
        }
    }

    void publishOrangeMessage(const OrangeMessage& msg) {
        std::unique_lock<std::mutex> lock(mtx);
        for (auto& subscriber : orangeSubscribers) {
            subscriber(msg);
        }
    }

    void subscribeToGreenMessage(std::function<void(const GreenMessage&)> callback) {
        std::unique_lock<std::mutex> lock(mtx);
        greenSubscribers.push_back(callback);
    }

    void subscribeToBlueMessage(std::function<void(const BlueMessage&)> callback) {
        std::unique_lock<std::mutex> lock(mtx);
        blueSubscribers.push_back(callback);
    }

    void subscribeToOrangeMessage(std::function<void(const OrangeMessage&)> callback) {
        std::unique_lock<std::mutex> lock(mtx);
        orangeSubscribers.push_back(callback);
    }

private:
    std::vector<std::function<void(const GreenMessage&)>> greenSubscribers;
    std::vector<std::function<void(const BlueMessage&)>> blueSubscribers;
    std::vector<std::function<void(const OrangeMessage&)>> orangeSubscribers;

    std::mutex mtx;
};

void generateGreenMessages(MessageDispatcher& dispatcher) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 0; i < 10; ++i) {
        GreenMessage msg = {"GreenMessage_" + std::to_string(i), dist(gen)};
        dispatcher.publishGreenMessage(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void generateBlueMessages(MessageDispatcher& dispatcher) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 100.0);

    for (int i = 0; i < 10; ++i) {
        BlueMessage msg = {dist(gen), dist(gen)};
        dispatcher.publishBlueMessage(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}

void generateOrangeMessages(MessageDispatcher& dispatcher) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> intDist(1, 100);
    std::uniform_real_distribution<> doubleDist(0.0, 100.0);

    for (int i = 0; i < 10; ++i) {
        OrangeMessage msg = {
            "OrangeMessage1_" + std::to_string(i),
            "OrangeMessage2_" + std::to_string(i),
            intDist(gen),
            doubleDist(gen)
        };
        dispatcher.publishOrangeMessage(msg);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

int main() {
    MessageDispatcher dispatcher;

    dispatcher.subscribeToGreenMessage([](const GreenMessage& msg) {
        std::cout << "Received GreenMessage: " << msg.text << ", " << msg.counter << std::endl;
    });
    dispatcher.subscribeToBlueMessage([](const BlueMessage& msg) {
        std::cout << "Received BlueMessage: " << msg.value1 << ", " << msg.value2 << std::endl;
    });
    dispatcher.subscribeToOrangeMessage([](const OrangeMessage& msg) {
        std::cout << "Received OrangeMessage: " << msg.text1 << ", " << msg.text2 << ", " << msg.integer << ", " << msg.value << std::endl;
    });

    std::thread greenThread(generateGreenMessages, std::ref(dispatcher));
    std::thread blueThread(generateBlueMessages, std::ref(dispatcher));
    std::thread orangeThread(generateOrangeMessages, std::ref(dispatcher));

    greenThread.join();
    blueThread.join();
    orangeThread.join();

    return 0;
}
