#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "Array.h"
#include "PDFRectangle.h"

// Test fixture for testing the parseDiffRectangle function
class ParseDiffRectangleTest_2018 : public ::testing::Test {
protected:
    Array *array;
    PDFRectangle *rect;

    void SetUp() override {
        // Initialize with default values
        array = new Array(nullptr);  // Assuming nullptr for simplicity, adjust as needed
        rect = new PDFRectangle(0, 0, 10, 10);  // A default rectangle
    }

    void TearDown() override {
        delete array;
        delete rect;
    }
};

// Normal operation test
TEST_F(ParseDiffRectangleTest_2018, ValidRectangle_2018) {
    // Valid inputs
    array->add(Object(1.0));  // dx1
    array->add(Object(1.0));  // dy1
    array->add(Object(1.0));  // dx2
    array->add(Object(1.0));  // dy2

    auto newRect = parseDiffRectangle(array, rect);
    ASSERT_NE(newRect, nullptr);
    EXPECT_EQ(newRect->x1, 1.0);
    EXPECT_EQ(newRect->y1, 1.0);
    EXPECT_EQ(newRect->x2, 8.0);
    EXPECT_EQ(newRect->y2, 8.0);
}

// Boundary condition tests
TEST_F(ParseDiffRectangleTest_2018, RectangleWithZeroDimensions_2018) {
    // Test when rectangle dimensions are zero (invalid case)
    array->add(Object(0.0));  // dx1
    array->add(Object(0.0));  // dy1
    array->add(Object(0.0));  // dx2
    array->add(Object(0.0));  // dy2

    auto newRect = parseDiffRectangle(array, rect);
    ASSERT_EQ(newRect, nullptr);
}

TEST_F(ParseDiffRectangleTest_2018, InvalidDx1_2018) {
    // Test when dx1 is invalid (negative value, for example)
    array->add(Object(-1.0));  // dx1
    array->add(Object(1.0));   // dy1
    array->add(Object(1.0));   // dx2
    array->add(Object(1.0));   // dy2

    auto newRect = parseDiffRectangle(array, rect);
    ASSERT_EQ(newRect, nullptr);
}

// Exceptional case test
TEST_F(ParseDiffRectangleTest_2018, InsufficientArrayLength_2018) {
    // Test when the array does not contain exactly 4 elements
    array->add(Object(1.0));  // dx1
    array->add(Object(1.0));  // dy1
    array->add(Object(1.0));  // dx2

    auto newRect = parseDiffRectangle(array, rect);
    ASSERT_EQ(newRect, nullptr);
}

// Mock interaction test
class MockArray : public Array {
public:
    MOCK_METHOD(void, add, (Object&& elem), (override));
    MOCK_METHOD(int, getLength, (), (const, override));
    MOCK_METHOD(Object, get, (int i, int recursion), (const, override));
};

TEST_F(ParseDiffRectangleTest_2018, MockArrayInteraction_2018) {
    MockArray mockArray;
    
    // Expecting calls to add method
    EXPECT_CALL(mockArray, add(::testing::_)).Times(4);
    
    // Simulate adding elements to the array
    mockArray.add(Object(1.0));  // dx1
    mockArray.add(Object(1.0));  // dy1
    mockArray.add(Object(1.0));  // dx2
    mockArray.add(Object(1.0));  // dy2

    auto newRect = parseDiffRectangle(&mockArray, rect);
    ASSERT_NE(newRect, nullptr);
}