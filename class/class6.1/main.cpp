#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
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
    using GreenMessageCb = std::function<void(const GreenMessage&)>;
    using BlueMessageCb = std::function<void(const BlueMessage&)>;
    using OrangeMessageCb = std::function<void(const OrangeMessage&)>;

    MessageDispatcher() {
        greenDispatchThread = std::thread(&MessageDispatcher::dispatchGreenMessages, this);
        blueDispatchThread = std::thread(&MessageDispatcher::dispatchBlueMessages, this);
        orangeDispatchThread = std::thread(&MessageDispatcher::dispatchOrangeMessages, this);
    }

    ~MessageDispatcher() {
        {
            std::unique_lock<std::mutex> lock(greenMtx);
            stop = true;
        }
        greenCv.notify_all();
        if (greenDispatchThread.joinable()) {
            greenDispatchThread.join();
        }

        {
            std::unique_lock<std::mutex> lock(blueMtx);
            stop = true;
        }
        blueCv.notify_all();
        if (blueDispatchThread.joinable()) {
            blueDispatchThread.join();
        }

        {
            std::unique_lock<std::mutex> lock(orangeMtx);
            stop = true;
        }
        orangeCv.notify_all();
        if (orangeDispatchThread.joinable()) {
            orangeDispatchThread.join();
        }
    }

    void publishGreenMessage(const GreenMessage& msg) {
        {
            std::unique_lock<std::mutex> lock(greenMtx);
            greenMessageQueue.push(msg);
        }
        greenCv.notify_one();
    }

    void publishBlueMessage(const BlueMessage& msg) {
        {
            std::unique_lock<std::mutex> lock(blueMtx);
            blueMessageQueue.push(msg);
        }
        blueCv.notify_one();
    }

    void publishOrangeMessage(const OrangeMessage& msg) {
        {
            std::unique_lock<std::mutex> lock(orangeMtx);
            orangeMessageQueue.push(msg);
        }
        orangeCv.notify_one();
    }

    void subscribeToGreenMessage(GreenMessageCb callback) {
        std::unique_lock<std::mutex> lock(greenMtx);
        greenSubscribers.push_back(callback);
    }

    void subscribeToBlueMessage(BlueMessageCb callback) {
        std::unique_lock<std::mutex> lock(blueMtx);
        blueSubscribers.push_back(callback);
    }

    void subscribeToOrangeMessage(OrangeMessageCb callback) {
        std::unique_lock<std::mutex> lock(orangeMtx);
        orangeSubscribers.push_back(callback);
    }

private:
    std::vector<GreenMessageCb> greenSubscribers;
    std::vector<BlueMessageCb> blueSubscribers;
    std::vector<OrangeMessageCb> orangeSubscribers;

    std::queue<GreenMessage> greenMessageQueue;
    std::queue<BlueMessage> blueMessageQueue;
    std::queue<OrangeMessage> orangeMessageQueue;

    std::mutex greenMtx, blueMtx, orangeMtx;
    std::condition_variable greenCv, blueCv, orangeCv;
    std::thread greenDispatchThread, blueDispatchThread, orangeDispatchThread;
    bool stop = false;

    void dispatchGreenMessages() {
        while (true) {
            std::unique_lock<std::mutex> lock(greenMtx);
            greenCv.wait(lock, [this] { return !greenMessageQueue.empty() || stop; });

            if (stop && greenMessageQueue.empty()) {
                break;
            }

            GreenMessage msg = greenMessageQueue.front();
            greenMessageQueue.pop();
            lock.unlock();

            for (auto& subscriber : greenSubscribers) {
                subscriber(msg);
            }
        }
    }

    void dispatchBlueMessages() {
        while (true) {
            std::unique_lock<std::mutex> lock(blueMtx);
            blueCv.wait(lock, [this] { return !blueMessageQueue.empty() || stop; });

            if (stop && blueMessageQueue.empty()) {
                break;
            }

            BlueMessage msg = blueMessageQueue.front();
            blueMessageQueue.pop();
            lock.unlock();

            for (auto& subscriber : blueSubscribers) {
                subscriber(msg);
            }
        }
    }

    void dispatchOrangeMessages() {
        while (true) {
            std::unique_lock<std::mutex> lock(orangeMtx);
            orangeCv.wait(lock, [this] { return !orangeMessageQueue.empty() || stop; });

            if (stop && orangeMessageQueue.empty()) {
                break;
            }

            OrangeMessage msg = orangeMessageQueue.front();
            orangeMessageQueue.pop();
            lock.unlock();

            for (auto& subscriber : orangeSubscribers) {
                subscriber(msg);
            }
        }
    }
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
