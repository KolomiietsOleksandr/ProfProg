#include "UnitTests.hpp"
#include "MaybeTheBestCodeEver.cpp"

void testRectangleArea() {
    Rectangle rect1(3.0, 4.0);
    ASSERT_EQ(rect1.getArea(), 12.0);

    Rectangle rect2(5.0, 5.0);
    ASSERT_EQ(rect2.getArea(), 25.0);
}

void testRectangleBiggerSide() {
    Rectangle rect1(3.0, 4.0);
    ASSERT_EQ(rect1.getBiggerSide(), 4.0);

    Rectangle rect2(5.0, 3.0);
    ASSERT_EQ(rect2.getBiggerSide(), 5.0);
}

void testRectanglePlacement() {
    Rectangle rect1(3.0, 4.0);
    Rectangle rect2(5.0, 5.0);
    Rectangle rect3(2.0, 3.0);

    ASSERT_EQ(rect1.canBePlacedInside(rect2), true);
    ASSERT_EQ(rect3.canBePlacedInside(rect1), true);
    ASSERT_EQ(rect2.canBePlacedInside(rect3), false);
}

void testRectangleProcessorPlacement() {
    RectangleProcessor processor;

    processor.addRectangle(Rectangle(3.0, 4.0));
    processor.addRectangle(Rectangle(5.0, 5.0));
    processor.addRectangle(Rectangle(2.0, 3.0));

    processor.processRectangles();
}

int main() {
    UnitTests tests;

    tests.addTest("Test Rectangle Area", testRectangleArea);
    tests.addTest("Test Rectangle Bigger Side", testRectangleBiggerSide);
    tests.addTest("Test Rectangle Placement", testRectanglePlacement);
    tests.addTest("Test Rectangle Processor Placement", testRectangleProcessorPlacement);

    tests.run();

    return 0;
}
