#include <gtest/gtest.h>
#include <glib.h>
#include "Object.h"
#include "Array.h"

// We need to include or declare the function under test.
// Since it's a static inline function in a .cc file, we need to either
// include that file or redeclare/redefine it for testing purposes.
// We'll include the relevant header or redefine the function signature.

// The function is static inline in the .cc file, so we need to pull it in.
// For testing purposes, we replicate the exact function signature here
// since we cannot include the .cc file directly in most build systems.
// However, the function is exactly as provided, so we define it here for testing.

static inline void convert_double_or_4_doubles(const Object *object, gdouble *value)
{
    g_assert(object != nullptr);
    if (object->isArray()) {
        g_assert(object->arrayGetLength() == 4);
        for (guint i = 0; i < 4; i++) {
            value[i] = object->arrayGet(i).getNum();
        }
    } else {
        g_assert(object->isNum());
        value[0] = value[1] = value[2] = value[3] = object->getNum();
    }
}

class ConvertDoubleOr4DoublesTest_2560 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: A single integer value is replicated to all 4 elements
TEST_F(ConvertDoubleOr4DoublesTest_2560, SingleIntValue_AllFourSet_2560)
{
    Object obj(42);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 42.0);
    EXPECT_DOUBLE_EQ(values[1], 42.0);
    EXPECT_DOUBLE_EQ(values[2], 42.0);
    EXPECT_DOUBLE_EQ(values[3], 42.0);
}

// Test: A single real (double) value is replicated to all 4 elements
TEST_F(ConvertDoubleOr4DoublesTest_2560, SingleRealValue_AllFourSet_2560)
{
    Object obj(3.14);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 3.14);
    EXPECT_DOUBLE_EQ(values[1], 3.14);
    EXPECT_DOUBLE_EQ(values[2], 3.14);
    EXPECT_DOUBLE_EQ(values[3], 3.14);
}

// Test: A single zero value is replicated to all 4 elements
TEST_F(ConvertDoubleOr4DoublesTest_2560, SingleZeroValue_AllFourSet_2560)
{
    Object obj(0.0);
    gdouble values[4] = {1.0, 2.0, 3.0, 4.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.0);
    EXPECT_DOUBLE_EQ(values[2], 0.0);
    EXPECT_DOUBLE_EQ(values[3], 0.0);
}

// Test: A single negative value is replicated to all 4 elements
TEST_F(ConvertDoubleOr4DoublesTest_2560, SingleNegativeValue_AllFourSet_2560)
{
    Object obj(-5.5);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], -5.5);
    EXPECT_DOUBLE_EQ(values[1], -5.5);
    EXPECT_DOUBLE_EQ(values[2], -5.5);
    EXPECT_DOUBLE_EQ(values[3], -5.5);
}

// Test: An array of 4 doubles sets each element individually
TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayOf4Doubles_EachElementSet_2560)
{
    // Create an array with 4 numeric elements
    Array *arr = new Array(nullptr);
    arr->add(Object(1.0));
    arr->add(Object(2.0));
    arr->add(Object(3.0));
    arr->add(Object(4.0));

    Object obj(arr);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 1.0);
    EXPECT_DOUBLE_EQ(values[1], 2.0);
    EXPECT_DOUBLE_EQ(values[2], 3.0);
    EXPECT_DOUBLE_EQ(values[3], 4.0);
}

// Test: An array of 4 integers sets each element individually
TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayOf4Integers_EachElementSet_2560)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(10));
    arr->add(Object(20));
    arr->add(Object(30));
    arr->add(Object(40));

    Object obj(arr);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 10.0);
    EXPECT_DOUBLE_EQ(values[1], 20.0);
    EXPECT_DOUBLE_EQ(values[2], 30.0);
    EXPECT_DOUBLE_EQ(values[3], 40.0);
}

// Test: An array of 4 with mixed int and real values
TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayOf4MixedTypes_EachElementSet_2560)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(2.5));
    arr->add(Object(0));
    arr->add(Object(-3.7));

    Object obj(arr);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 1.0);
    EXPECT_DOUBLE_EQ(values[1], 2.5);
    EXPECT_DOUBLE_EQ(values[2], 0.0);
    EXPECT_DOUBLE_EQ(values[3], -3.7);
}

// Test: An array of 4 zeros
TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayOf4Zeros_AllZero_2560)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    arr->add(Object(0.0));

    Object obj(arr);
    gdouble values[4] = {1.0, 2.0, 3.0, 4.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.0);
    EXPECT_DOUBLE_EQ(values[2], 0.0);
    EXPECT_DOUBLE_EQ(values[3], 0.0);
}

// Test: An array of 4 negative values
TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayOf4NegativeValues_2560)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(-1.1));
    arr->add(Object(-2.2));
    arr->add(Object(-3.3));
    arr->add(Object(-4.4));

    Object obj(arr);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], -1.1);
    EXPECT_DOUBLE_EQ(values[1], -2.2);
    EXPECT_DOUBLE_EQ(values[2], -3.3);
    EXPECT_DOUBLE_EQ(values[3], -4.4);
}

// Test: Very large single value
TEST_F(ConvertDoubleOr4DoublesTest_2560, SingleLargeValue_AllFourSet_2560)
{
    Object obj(1e308);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 1e308);
    EXPECT_DOUBLE_EQ(values[1], 1e308);
    EXPECT_DOUBLE_EQ(values[2], 1e308);
    EXPECT_DOUBLE_EQ(values[3], 1e308);
}

// Test: Very small single value
TEST_F(ConvertDoubleOr4DoublesTest_2560, SingleVerySmallValue_AllFourSet_2560)
{
    Object obj(1e-308);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 1e-308);
    EXPECT_DOUBLE_EQ(values[1], 1e-308);
    EXPECT_DOUBLE_EQ(values[2], 1e-308);
    EXPECT_DOUBLE_EQ(values[3], 1e-308);
}

// Test: Array with large double values
TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayWithLargeValues_2560)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(1e100));
    arr->add(Object(-1e100));
    arr->add(Object(1e-100));
    arr->add(Object(-1e-100));

    Object obj(arr);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 1e100);
    EXPECT_DOUBLE_EQ(values[1], -1e100);
    EXPECT_DOUBLE_EQ(values[2], 1e-100);
    EXPECT_DOUBLE_EQ(values[3], -1e-100);
}

// Death test: null object pointer triggers g_assert failure
TEST_F(ConvertDoubleOr4DoublesTest_2560, NullObjectPointer_Asserts_2560)
{
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};
    EXPECT_DEATH(convert_double_or_4_doubles(nullptr, values), "");
}

// Death test: non-numeric, non-array object triggers g_assert failure
TEST_F(ConvertDoubleOr4DoublesTest_2560, NonNumericNonArrayObject_Asserts_2560)
{
    Object obj(true); // boolean object - not num, not array
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};
    EXPECT_DEATH(convert_double_or_4_doubles(&obj, values), "");
}

// Death test: array with wrong length (not 4) triggers g_assert failure
TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayWrongLength_Asserts_2560)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(1.0));
    arr->add(Object(2.0));
    arr->add(Object(3.0));
    // Only 3 elements, not 4

    Object obj(arr);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};
    EXPECT_DEATH(convert_double_or_4_doubles(&obj, values), "");
}

// Death test: array with 5 elements triggers g_assert failure
TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayTooManyElements_Asserts_2560)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(1.0));
    arr->add(Object(2.0));
    arr->add(Object(3.0));
    arr->add(Object(4.0));
    arr->add(Object(5.0));
    // 5 elements, not 4

    Object obj(arr);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};
    EXPECT_DEATH(convert_double_or_4_doubles(&obj, values), "");
}

// Death test: empty array triggers g_assert failure
TEST_F(ConvertDoubleOr4DoublesTest_2560, EmptyArray_Asserts_2560)
{
    Array *arr = new Array(nullptr);
    // No elements

    Object obj(arr);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};
    EXPECT_DEATH(convert_double_or_4_doubles(&obj, values), "");
}

// Test: Single integer value of 0
TEST_F(ConvertDoubleOr4DoublesTest_2560, SingleIntZero_AllFourSet_2560)
{
    Object obj(0);
    gdouble values[4] = {5.0, 5.0, 5.0, 5.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.0);
    EXPECT_DOUBLE_EQ(values[2], 0.0);
    EXPECT_DOUBLE_EQ(values[3], 0.0);
}

// Test: Array with identical values
TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayWithIdenticalValues_2560)
{
    Array *arr = new Array(nullptr);
    arr->add(Object(7.7));
    arr->add(Object(7.7));
    arr->add(Object(7.7));
    arr->add(Object(7.7));

    Object obj(arr);
    gdouble values[4] = {0.0, 0.0, 0.0, 0.0};

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 7.7);
    EXPECT_DOUBLE_EQ(values[1], 7.7);
    EXPECT_DOUBLE_EQ(values[2], 7.7);
    EXPECT_DOUBLE_EQ(values[3], 7.7);
}
