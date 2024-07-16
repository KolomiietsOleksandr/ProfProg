#include <iostream>
#include <vector>
#include <limits>

class Rectangle {
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    double getArea() const {
        return width * height;
    }

    double getBiggerSide() const {
        return (width > height) ? width : height;
    }

    bool canBePlacedInside(const Rectangle& other) const {
        return width <= other.width && height <= other.height;
    }

private:
    double width;
    double height;
};

class RectangleProcessor {
public:
    void addRectangle(const Rectangle& rect) {
        rectangles.push_back(rect);
        double area = rect.getArea();
        if (area > biggestArea) {
            biggestArea = area;
        }
        if (area < smallestArea) {
            smallestArea = area;
        }
        totalArea += area;
    }

    void processRectangles() {
        for (size_t i = 0; i < rectangles.size(); ++i) {
            for (size_t j = 0; j < rectangles.size(); ++j) {
                if (i != j && rectangles[i].canBePlacedInside(rectangles[j])) {
                    std::println << "Rectangle " << i + 1 << " can be placed inside Rectangle " << j + 1 << std::endl;
                }
            }
            std::println << "The biggest side of rectangle " << i + 1 << ": " << rectangles[i].getBiggerSide() << std::endl;
        }

        std::println << "The biggest area: " << biggestArea << std::endl;
        std::println << "The smallest area: " << smallestArea << std::endl;
        std::println << "Total area of rectangles: " << totalArea << std::endl;
    }

private:
    std::vector<Rectangle> rectangles;
    double biggestArea = 0;
    double smallestArea = std::numeric_limits<double>::max();
    double totalArea = 0;
};

int main() {
    RectangleProcessor processor;

    double width, height;
    for (int i = 1; i <= 5; ++i) {
        std::println << "Enter rectangle " << i << ":" << std::endl;
        if (std::cin >> width >> height) {
            processor.addRectangle(Rectangle(width, height));
        }
    }

    processor.processRectangles();

    return 0;
}
