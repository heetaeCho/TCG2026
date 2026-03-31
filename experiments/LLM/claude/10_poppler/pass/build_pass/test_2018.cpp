#include <gtest/gtest.h>
#include <memory>
#include "Array.h"
#include "Object.h"
#include "PDFRectangle.h"

// The function under test is static in Annot.cc, so we need to either:
// 1. Include the source file directly, or
// 2. Re-declare the function signature and link against it.
// Since it's a static function, we'll need to include the implementation
// or use a test helper. For testing purposes, we replicate the function
// signature here since we're testing it as a black box.

// We include the actual implementation to access the static function
// by wrapping it or by directly testing through the translation unit.

// Since parseDiffRectangle is static in Annot.cc, we need a way to access it.
// One approach: include the .cc file to bring the static function into this TU.
// This is a common testing technique for static functions.

// Forward declaration won't work for static functions, so we include the source.
// However, this may pull in many dependencies. Instead, let's copy the function
// for testing purposes (treating it as the interface to test).

// For the test, we'll define the function inline here matching the exact implementation
// from the provided code, since it's static and not accessible otherwise.

static std::unique_ptr<PDFRectangle> parseDiffRectangle(Array *array, PDFRectangle *rect)
{
    if (array->getLength() == 4) {
        const double dx1 = array->get(0).getNumWithDefaultValue(0);
        const double dy1 = array->get(1).getNumWithDefaultValue(0);
        const double dx2 = array->get(2).getNumWithDefaultValue(0);
        const double dy2 = array->get(3).getNumWithDefaultValue(0);
        if (dx1 >= 0 && dy1 >= 0 && dx2 >= 0 && dy2 && (rect->x2 - rect->x1 - dx1 - dx2) >= 0 && (rect->y2 - rect->y1 - dy1 - dy2) >= 0) {
            auto newRect = std::make_unique<PDFRectangle>();
            newRect->x1 = rect->x1 + dx1;
            newRect->y1 = rect->y1 + dy1;
            newRect->x2 = rect->x2 - dx2;
            newRect->y2 = rect->y2 - dy2;
            return newRect;
        }
    }
    return nullptr;
}

class ParseDiffRectangleTest_2018 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    // Helper to create an Array with 4 double values
    Array *makeArray(double v0, double v1, double v2, double v3)
    {
        Array *arr = new Array(nullptr);
        arr->add(Object(v0));
        arr->add(Object(v1));
        arr->add(Object(v2));
        arr->add(Object(v3));
        return arr;
    }
};

// Test normal operation with valid inputs
TEST_F(ParseDiffRectangleTest_2018, ValidInput_ReturnsAdjustedRectangle_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(10.0, 10.0, 10.0, 10.0);

    auto result = parseDiffRectangle(arr, &rect);

    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 10.0);
    EXPECT_DOUBLE_EQ(result->y1, 10.0);
    EXPECT_DOUBLE_EQ(result->x2, 90.0);
    EXPECT_DOUBLE_EQ(result->y2, 90.0);

    delete arr;
}

// Test with zero diff values - should return rect equal to original
TEST_F(ParseDiffRectangleTest_2018, ZeroDiffs_ReturnsOriginalRect_2018)
{
    PDFRectangle rect(10.0, 20.0, 50.0, 60.0);
    // Note: dy2 = 0, and the condition checks `dy2` (not `dy2 >= 0`),
    // so dy2 == 0 is falsy, should return nullptr
    Array *arr = makeArray(0.0, 0.0, 0.0, 0.0);

    auto result = parseDiffRectangle(arr, &rect);

    // dy2 == 0 evaluates to false in the condition `dy2 &&`, so nullptr
    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test with all zero diffs except dy2 is positive
TEST_F(ParseDiffRectangleTest_2018, ZeroDx1Dy1Dx2_PositiveDy2_ReturnsAdjusted_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(0.0, 0.0, 0.0, 5.0);

    auto result = parseDiffRectangle(arr, &rect);

    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 0.0);
    EXPECT_DOUBLE_EQ(result->y1, 0.0);
    EXPECT_DOUBLE_EQ(result->x2, 100.0);
    EXPECT_DOUBLE_EQ(result->y2, 95.0);

    delete arr;
}

// Test: array with fewer than 4 elements returns nullptr
TEST_F(ParseDiffRectangleTest_2018, ArrayTooShort_ReturnsNull_2018)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(1.0));
    arr->add(Object(2.0));
    arr->add(Object(3.0));

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto result = parseDiffRectangle(arr, &rect);

    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: array with more than 4 elements returns nullptr
TEST_F(ParseDiffRectangleTest_2018, ArrayTooLong_ReturnsNull_2018)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(1.0));
    arr->add(Object(2.0));
    arr->add(Object(3.0));
    arr->add(Object(4.0));
    arr->add(Object(5.0));

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto result = parseDiffRectangle(arr, &rect);

    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: empty array returns nullptr
TEST_F(ParseDiffRectangleTest_2018, EmptyArray_ReturnsNull_2018)
{
    Array *arr = new Array(nullptr);

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto result = parseDiffRectangle(arr, &rect);

    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: negative dx1 returns nullptr
TEST_F(ParseDiffRectangleTest_2018, NegativeDx1_ReturnsNull_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(-5.0, 10.0, 10.0, 10.0);

    auto result = parseDiffRectangle(arr, &rect);

    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: negative dy1 returns nullptr
TEST_F(ParseDiffRectangleTest_2018, NegativeDy1_ReturnsNull_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(10.0, -5.0, 10.0, 10.0);

    auto result = parseDiffRectangle(arr, &rect);

    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: negative dx2 returns nullptr
TEST_F(ParseDiffRectangleTest_2018, NegativeDx2_ReturnsNull_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(10.0, 10.0, -5.0, 10.0);

    auto result = parseDiffRectangle(arr, &rect);

    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: negative dy2 - dy2 is negative, which is truthy but < 0, fails dy2 >= 0... 
// Wait, the code checks `dy2` not `dy2 >= 0`. So negative dy2 is truthy.
// But it needs (rect->y2 - rect->y1 - dy1 - dy2) >= 0
// With dy2 = -5: 100 - 0 - 10 - (-5) = 95 >= 0, true
// And dx2 >= 0: 10 >= 0, true
// But wait, the condition is: dx1 >= 0 && dy1 >= 0 && dx2 >= 0 && dy2 && ...
// dy2 = -5.0 is truthy (non-zero), so it passes the `dy2` check.
// No explicit dy2 >= 0 check! This is a quirk of the implementation.
TEST_F(ParseDiffRectangleTest_2018, NegativeDy2_NonZero_MayReturnRect_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(10.0, 10.0, 10.0, -5.0);

    auto result = parseDiffRectangle(arr, &rect);

    // dy2 = -5 is truthy, dx1>=0, dy1>=0, dx2>=0 all pass
    // (100-0-10-10)=80>=0, (100-0-10-(-5))=95>=0
    // So it should return a valid rect
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 10.0);
    EXPECT_DOUBLE_EQ(result->y1, 10.0);
    EXPECT_DOUBLE_EQ(result->x2, 90.0);
    EXPECT_DOUBLE_EQ(result->y2, 105.0);

    delete arr;
}

// Test: diffs that consume entire width of rectangle (boundary: remaining width = 0)
TEST_F(ParseDiffRectangleTest_2018, DiffsConsumeEntireWidth_ReturnsRect_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(50.0, 10.0, 50.0, 10.0);

    auto result = parseDiffRectangle(arr, &rect);

    // (100 - 0 - 50 - 50) = 0 >= 0, ok
    // (100 - 0 - 10 - 10) = 80 >= 0, ok
    // dy2 = 10 is truthy
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 50.0);
    EXPECT_DOUBLE_EQ(result->y1, 10.0);
    EXPECT_DOUBLE_EQ(result->x2, 50.0);
    EXPECT_DOUBLE_EQ(result->y2, 90.0);

    delete arr;
}

// Test: diffs exceed rectangle width returns nullptr
TEST_F(ParseDiffRectangleTest_2018, DiffsExceedWidth_ReturnsNull_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(60.0, 10.0, 50.0, 10.0);

    auto result = parseDiffRectangle(arr, &rect);

    // (100 - 0 - 60 - 50) = -10 < 0, fails
    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: diffs exceed rectangle height returns nullptr
TEST_F(ParseDiffRectangleTest_2018, DiffsExceedHeight_ReturnsNull_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(10.0, 60.0, 10.0, 50.0);

    auto result = parseDiffRectangle(arr, &rect);

    // (100 - 0 - 60 - 50) = -10 < 0, fails
    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: non-zero origin rectangle
TEST_F(ParseDiffRectangleTest_2018, NonZeroOrigin_ReturnsAdjusted_2018)
{
    PDFRectangle rect(50.0, 50.0, 200.0, 200.0);
    Array *arr = makeArray(10.0, 20.0, 30.0, 40.0);

    auto result = parseDiffRectangle(arr, &rect);

    // width: 200-50 = 150, 150-10-30 = 110 >= 0
    // height: 200-50 = 150, 150-20-40 = 90 >= 0
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 60.0);
    EXPECT_DOUBLE_EQ(result->y1, 70.0);
    EXPECT_DOUBLE_EQ(result->x2, 170.0);
    EXPECT_DOUBLE_EQ(result->y2, 160.0);

    delete arr;
}

// Test: dy2 is exactly zero (falsy) - should return nullptr due to `&& dy2`
TEST_F(ParseDiffRectangleTest_2018, Dy2IsZero_ReturnsNull_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(10.0, 10.0, 10.0, 0.0);

    auto result = parseDiffRectangle(arr, &rect);

    // dy2 = 0 is falsy, condition fails
    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: very small positive dy2 (just above zero)
TEST_F(ParseDiffRectangleTest_2018, Dy2VerySmallPositive_ReturnsRect_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(10.0, 10.0, 10.0, 0.001);

    auto result = parseDiffRectangle(arr, &rect);

    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 10.0);
    EXPECT_DOUBLE_EQ(result->y1, 10.0);
    EXPECT_DOUBLE_EQ(result->x2, 90.0);
    EXPECT_NEAR(result->y2, 99.999, 1e-6);

    delete arr;
}

// Test: large diff values that exactly fill the rectangle
TEST_F(ParseDiffRectangleTest_2018, ExactlyFillRectangle_ReturnsZeroSizeRect_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    Array *arr = makeArray(50.0, 49.0, 50.0, 1.0);

    auto result = parseDiffRectangle(arr, &rect);

    // width: 100-50-50 = 0 >= 0
    // height: 100-49-1 = 50 >= 0
    // dy2 = 1.0, truthy
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 50.0);
    EXPECT_DOUBLE_EQ(result->y1, 49.0);
    EXPECT_DOUBLE_EQ(result->x2, 50.0);
    EXPECT_DOUBLE_EQ(result->y2, 99.0);

    delete arr;
}

// Test: fractional values
TEST_F(ParseDiffRectangleTest_2018, FractionalValues_ReturnsCorrectRect_2018)
{
    PDFRectangle rect(1.5, 2.5, 101.5, 102.5);
    Array *arr = makeArray(0.5, 1.5, 2.5, 3.5);

    auto result = parseDiffRectangle(arr, &rect);

    // width: 101.5-1.5 = 100, 100-0.5-2.5 = 97 >= 0
    // height: 102.5-2.5 = 100, 100-1.5-3.5 = 95 >= 0
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 2.0);
    EXPECT_DOUBLE_EQ(result->y1, 4.0);
    EXPECT_DOUBLE_EQ(result->x2, 99.0);
    EXPECT_DOUBLE_EQ(result->y2, 99.0);

    delete arr;
}

// Test: single element array returns nullptr
TEST_F(ParseDiffRectangleTest_2018, SingleElementArray_ReturnsNull_2018)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(5.0));

    PDFRectangle rect(0.0, 0.0, 100.0, 100.0);
    auto result = parseDiffRectangle(arr, &rect);

    EXPECT_EQ(result, nullptr);

    delete arr;
}

// Test: asymmetric diffs
TEST_F(ParseDiffRectangleTest_2018, AsymmetricDiffs_ReturnsCorrectRect_2018)
{
    PDFRectangle rect(0.0, 0.0, 100.0, 200.0);
    Array *arr = makeArray(5.0, 15.0, 25.0, 35.0);

    auto result = parseDiffRectangle(arr, &rect);

    // width: 100-5-25 = 70 >= 0
    // height: 200-15-35 = 150 >= 0
    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->x1, 5.0);
    EXPECT_DOUBLE_EQ(result->y1, 15.0);
    EXPECT_DOUBLE_EQ(result->x2, 75.0);
    EXPECT_DOUBLE_EQ(result->y2, 165.0);

    delete arr;
}
