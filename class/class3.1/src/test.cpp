#include <print>
#include <Helpers.hpp>
#include <UnitTests.hpp>

int main() {
    UnitTests testSuite;

    testSuite.addTest("Dummy_test1",
    [](){
        double value = 0.0;

        auto result = dummyFunc(value);

        ASSERT_EQ(result, 0.0);
    });

    testSuite.addTest("Dummy_test2",
    [](){
        double value = 5.0;

        auto result = dummyFunc(value);

        ASSERT_EQ(result, 5.0);
    });

    testSuite.addTest("Dummy_test3",
    [](){
        double value = -3.0;

        auto result = dummyFunc(value);

        ASSERT_EQ(result, 0.0);
    });

    testSuite.addTest("RepeatString_Test1",
    [](){
        std::vector<int> vec;
        std::string str = "home";

        auto result = repeatString(vec, str);

        ASSERT_EQ(result, "");
    });

    testSuite.addTest("RepeatString_Test2",
    [](){
        std::vector<int> vec = {0, 0, 0};
        std::string str = "home";

        auto result = repeatString(vec, str);

        ASSERT_EQ(result, "");
    });

    testSuite.addTest("RepeatString_Test3",
    [](){
        std::vector<int> vec = {0, 2, 1};
        std::string str = "home";

        auto result = repeatString(vec, str);

        ASSERT_EQ(result, "homehome");
    });

    testSuite.addTest("RepeatString_Test4",
    [](){
        std::vector<int> vec = {5};
        std::string str = "home";

        auto result = repeatString(vec, str);

        ASSERT_EQ(result, "homehomehomehomehome");
    });

    testSuite.addTest("RepeatString_Test5",
    [](){
        std::vector<int> vec = {-1, 3, 2};
        std::string str = "home";

        auto result = repeatString(vec, str);

        ASSERT_EQ(result, "homehomehome");
    });

    testSuite.run();

    return 0;
}
