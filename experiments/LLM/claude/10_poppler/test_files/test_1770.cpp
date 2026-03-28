#include <gtest/gtest.h>
#include "poppler/Object.h"
#include "poppler/Array.h"

// Include the .cc file to get access to the static function
// This is necessary because isRGBColor has internal linkage
#include "poppler/StructElement.cc"

class IsRGBColorTest_1770 : public ::testing::Test {
protected:
    // Helper to create an Object that is an array with given double values
    Object makeArrayOfDoubles(std::vector<double> values) {
        Array *arr = new Array(nullptr);
        for (double v : values) {
            arr->add(Object(v));
        }
        return Object(arr);
    }

    Object makeArrayOfMixed(std::vector<Object> &objects) {
        Array *arr = new Array(nullptr);
        for (auto &o : objects) {
            arr->add(std::move(o));
        }
        return Object(arr);
    }
};

// Test valid RGB color with all zeros
TEST_F(IsRGBColorTest_1770, ValidRGBAllZeros_1770) {
    Object obj = makeArrayOfDoubles({0.0, 0.0, 0.0});
    EXPECT_TRUE(isRGBColor(&obj));
}

// Test valid RGB color with all ones
TEST_F(IsRGBColorTest_1770, ValidRGBAllOnes_1770) {
    Object obj = makeArrayOfDoubles({1.0, 1.0, 1.0});
    EXPECT_TRUE(isRGBColor(&obj));
}

// Test valid RGB color with mixed values
TEST_F(IsRGBColorTest_1770, ValidRGBMixedValues_1770) {
    Object obj = makeArrayOfDoubles({0.5, 0.3, 0.8});
    EXPECT_TRUE(isRGBColor(&obj));
}

// Test valid RGB color at boundaries
TEST_F(IsRGBColorTest_1770, ValidRGBBoundaryValues_1770) {
    Object obj = makeArrayOfDoubles({0.0, 1.0, 0.5});
    EXPECT_TRUE(isRGBColor(&obj));
}

// Test non-array object (integer)
TEST_F(IsRGBColorTest_1770, NonArrayObjectInt_1770) {
    Object obj(42);
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test non-array object (bool)
TEST_F(IsRGBColorTest_1770, NonArrayObjectBool_1770) {
    Object obj(true);
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test non-array object (null)
TEST_F(IsRGBColorTest_1770, NullObject_1770) {
    Object obj = Object::null();
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test array with wrong length (2 elements)
TEST_F(IsRGBColorTest_1770, ArrayTooShort_1770) {
    Object obj = makeArrayOfDoubles({0.5, 0.5});
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test array with wrong length (4 elements)
TEST_F(IsRGBColorTest_1770, ArrayTooLong_1770) {
    Object obj = makeArrayOfDoubles({0.5, 0.5, 0.5, 0.5});
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test empty array
TEST_F(IsRGBColorTest_1770, EmptyArray_1770) {
    Object obj = makeArrayOfDoubles({});
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test array with one element
TEST_F(IsRGBColorTest_1770, ArrayOneElement_1770) {
    Object obj = makeArrayOfDoubles({0.5});
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test array with negative value
TEST_F(IsRGBColorTest_1770, NegativeValue_1770) {
    Object obj = makeArrayOfDoubles({-0.1, 0.5, 0.5});
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test array with value greater than 1.0
TEST_F(IsRGBColorTest_1770, ValueGreaterThanOne_1770) {
    Object obj = makeArrayOfDoubles({0.5, 1.1, 0.5});
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test array with value greater than 1.0 in third position
TEST_F(IsRGBColorTest_1770, ThirdValueGreaterThanOne_1770) {
    Object obj = makeArrayOfDoubles({0.5, 0.5, 1.5});
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test array with non-numeric element (contains a bool)
TEST_F(IsRGBColorTest_1770, NonNumericElement_1770) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0.5));
    arr->add(Object(true));
    arr->add(Object(0.5));
    Object obj(arr);
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test array with integer values (integers are also Num)
TEST_F(IsRGBColorTest_1770, IntegerValuesZeroAndOne_1770) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(1));
    arr->add(Object(0));
    Object obj(arr);
    EXPECT_TRUE(isRGBColor(&obj));
}

// Test array with integer value out of range
TEST_F(IsRGBColorTest_1770, IntegerValueOutOfRange_1770) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0));
    arr->add(Object(2));
    arr->add(Object(0));
    Object obj(arr);
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test array with negative integer
TEST_F(IsRGBColorTest_1770, NegativeIntegerValue_1770) {
    Array *arr = new Array(nullptr);
    arr->add(Object(-1));
    arr->add(Object(0));
    arr->add(Object(0));
    Object obj(arr);
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test with string element in array
TEST_F(IsRGBColorTest_1770, StringElementInArray_1770) {
    Array *arr = new Array(nullptr);
    arr->add(Object(0.5));
    arr->add(Object(0.5));
    arr->add(Object(std::string("not a number")));
    Object obj(arr);
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test exact boundary: slightly below 0
TEST_F(IsRGBColorTest_1770, SlightlyBelowZero_1770) {
    Object obj = makeArrayOfDoubles({-0.0001, 0.5, 0.5});
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test exact boundary: slightly above 1
TEST_F(IsRGBColorTest_1770, SlightlyAboveOne_1770) {
    Object obj = makeArrayOfDoubles({0.5, 0.5, 1.0001});
    EXPECT_FALSE(isRGBColor(&obj));
}

// Test with none object
TEST_F(IsRGBColorTest_1770, NoneObject_1770) {
    Object obj;
    EXPECT_FALSE(isRGBColor(&obj));
}
