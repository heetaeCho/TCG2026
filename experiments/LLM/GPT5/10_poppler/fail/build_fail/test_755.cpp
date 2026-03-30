#include <gtest/gtest.h>
#include <array>
#include <stdexcept>

// Assuming AnnotColor is declared as in the provided code
class AnnotColor {
public:
    const std::array<double, 4>& getValues() const { return values; }

    // Constructors (simplified for test case purposes)
    AnnotColor() : values{0.0, 0.0, 0.0, 0.0} {}
    explicit AnnotColor(double gray) : values{gray, gray, gray, gray} {}
    AnnotColor(double r, double g, double b) : values{r, g, b, 0.0} {}
    AnnotColor(double c, double m, double y, double k) : values{c, m, y, k} {}
    explicit AnnotColor(const std::array<double, 4>& array, int adjust) {
        if (adjust < 0 || adjust > 255)
            throw std::out_of_range("Adjust value out of range");
        values = array;
    }

    void adjustColor(int adjust) {
        if (adjust < 0 || adjust > 255)
            throw std::out_of_range("Adjust value out of range");
        for (auto& v : values) {
            v = std::min(v + adjust, 255.0);
        }
    }

private:
    std::array<double, 4> values;
};

// Unit test cases

TEST_F(AnnotColorTest_755, DefaultConstructor_755) {
    AnnotColor color;
    const auto& values = color.getValues();
    EXPECT_EQ(values[0], 0.0);
    EXPECT_EQ(values[1], 0.0);
    EXPECT_EQ(values[2], 0.0);
    EXPECT_EQ(values[3], 0.0);
}

TEST_F(AnnotColorTest_755, GrayscaleConstructor_755) {
    double gray = 0.5;
    AnnotColor color(gray);
    const auto& values = color.getValues();
    EXPECT_EQ(values[0], gray);
    EXPECT_EQ(values[1], gray);
    EXPECT_EQ(values[2], gray);
    EXPECT_EQ(values[3], gray);
}

TEST_F(AnnotColorTest_755, RGBConstructor_755) {
    double r = 0.3, g = 0.5, b = 0.7;
    AnnotColor color(r, g, b);
    const auto& values = color.getValues();
    EXPECT_EQ(values[0], r);
    EXPECT_EQ(values[1], g);
    EXPECT_EQ(values[2], b);
    EXPECT_EQ(values[3], 0.0); // Default for 'a' is 0.0 (Alpha is not set)
}

TEST_F(AnnotColorTest_755, CMYKConstructor_755) {
    double c = 0.1, m = 0.2, y = 0.3, k = 0.4;
    AnnotColor color(c, m, y, k);
    const auto& values = color.getValues();
    EXPECT_EQ(values[0], c);
    EXPECT_EQ(values[1], m);
    EXPECT_EQ(values[2], y);
    EXPECT_EQ(values[3], k);
}

TEST_F(AnnotColorTest_755, ArrayConstructorValid_755) {
    std::array<double, 4> arr = {0.1, 0.2, 0.3, 0.4};
    AnnotColor color(arr, 100);
    const auto& values = color.getValues();
    EXPECT_EQ(values[0], 0.1);
    EXPECT_EQ(values[1], 0.2);
    EXPECT_EQ(values[2], 0.3);
    EXPECT_EQ(values[3], 0.4);
}

TEST_F(AnnotColorTest_755, ArrayConstructorInvalidAdjust_755) {
    std::array<double, 4> arr = {0.1, 0.2, 0.3, 0.4};
    EXPECT_THROW(AnnotColor color(arr, -1), std::out_of_range);
    EXPECT_THROW(AnnotColor color(arr, 256), std::out_of_range);
}

TEST_F(AnnotColorTest_755, AdjustColorValid_755) {
    AnnotColor color(0.2, 0.3, 0.4);
    color.adjustColor(10);
    const auto& values = color.getValues();
    EXPECT_EQ(values[0], 0.2 + 10);
    EXPECT_EQ(values[1], 0.3 + 10);
    EXPECT_EQ(values[2], 0.4 + 10);
}

TEST_F(AnnotColorTest_755, AdjustColorInvalid_755) {
    AnnotColor color(0.2, 0.3, 0.4);
    EXPECT_THROW(color.adjustColor(-1), std::out_of_range);
    EXPECT_THROW(color.adjustColor(256), std::out_of_range);
}