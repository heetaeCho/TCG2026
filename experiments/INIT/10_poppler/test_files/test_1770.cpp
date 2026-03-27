// TEST_ID: 1770
// Unit tests for isRGBColor (StructElement.cc)

#include <gtest/gtest.h>
#include "Object.h"

// Forward declaration of the function under test.
// It is defined as static in StructElement.cc, so we declare it here
// to treat it as a black-box function with the given signature.
static bool isRGBColor(Object *value);

class IsRGBColorTest_1770 : public ::testing::Test {
protected:
    Object createArrayObject() {
        Array *arr = new Array();
        return Object(arr);
    }

    Object createRGBArray(double r, double g, double b) {
        Array *arr = new Array();
        Object arrayObj(arr);
        arrayObj.arrayAdd(Object(r));
        arrayObj.arrayAdd(Object(g));
        arrayObj.arrayAdd(Object(b));
        return arrayObj;
    }
};

// ---------------------- Normal Operation ----------------------

TEST_F(IsRGBColorTest_1770, ValidRGBColorWithinRangeReturnsTrue_1770) {
    Object rgb = createRGBArray(0.0, 0.5, 1.0);

    EXPECT_TRUE(isRGBColor(&rgb));
}

TEST_F(IsRGBColorTest_1770, ValidRGBColorAtExactBoundsReturnsTrue_1770) {
    Object rgb = createRGBArray(0.0, 1.0, 0.0);

    EXPECT_TRUE(isRGBColor(&rgb));
}

// ---------------------- Boundary Conditions ----------------------

TEST_F(IsRGBColorTest_1770, RGBColorWithNegativeComponentReturnsFalse_1770) {
    Object rgb = createRGBArray(-0.1, 0.5, 0.5);

    EXPECT_FALSE(isRGBColor(&rgb));
}

TEST_F(IsRGBColorTest_1770, RGBColorWithComponentGreaterThanOneReturnsFalse_1770) {
    Object rgb = createRGBArray(0.5, 1.1, 0.5);

    EXPECT_FALSE(isRGBColor(&rgb));
}

TEST_F(IsRGBColorTest_1770, ArrayWithLessThanThreeElementsReturnsFalse_1770) {
    Array *arr = new Array();
    Object rgb(arr);
    rgb.arrayAdd(Object(0.1));
    rgb.arrayAdd(Object(0.2));

    EXPECT_FALSE(isRGBColor(&rgb));
}

TEST_F(IsRGBColorTest_1770, ArrayWithMoreThanThreeElementsReturnsFalse_1770) {
    Array *arr = new Array();
    Object rgb(arr);
    rgb.arrayAdd(Object(0.1));
    rgb.arrayAdd(Object(0.2));
    rgb.arrayAdd(Object(0.3));
    rgb.arrayAdd(Object(0.4));  // Extra element

    EXPECT_FALSE(isRGBColor(&rgb));
}

// ---------------------- Exceptional / Error Cases ----------------------

TEST_F(IsRGBColorTest_1770, NonArrayObjectReturnsFalse_1770) {
    Object notArray(0.5);

    EXPECT_FALSE(isRGBColor(&notArray));
}

TEST_F(IsRGBColorTest_1770, ArrayWithNonNumericElementReturnsFalse_1770) {
    Array *arr = new Array();
    Object rgb(arr);
    rgb.arrayAdd(Object(0.1));
    rgb.arrayAdd(Object(0.2));
    rgb.arrayAdd(Object(std::string("not-a-number")));

    EXPECT_FALSE(isRGBColor(&rgb));
}

TEST_F(IsRGBColorTest_1770, ArrayWithNullElementReturnsFalse_1770) {
    Array *arr = new Array();
    Object rgb(arr);
    rgb.arrayAdd(Object(0.1));
    rgb.arrayAdd(Object::null());
    rgb.arrayAdd(Object(0.3));

    EXPECT_FALSE(isRGBColor(&rgb));
}