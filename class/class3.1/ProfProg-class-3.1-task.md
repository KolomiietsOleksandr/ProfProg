**TASK. Unit testing**

***1. Read include/UnitTests.hpp file with implementation of a simple unit test framework.***

***2. Compile dummy unit test example***

a. Use the following flags to use headers from include folder and compile Helpers.cpp together with test.cpp:

-Iinclude src/test.cpp src/Helpers.cpp -o test

b. Run the test binary with ./test

c. Try to change unit test ASSERT_EQ check to fail the test execution.

d. Add two different test cases to cover dummyFunc.

***3. Write and cover function with unit tests***

a. Write a function that takes a vector of integers and a string. The return value should be that string repeated as much times as the biggest int in the vector e.g. if vector is {0, 2, 1} and string is home then we should return the string "homehome"
Place declaration of the function to Helpers.hpp and its definition to Helpers.cpp

b. Write at least 5 different test cases in src/test.cpp to cover the function with unit tests.

c. Compile and run the tests.
