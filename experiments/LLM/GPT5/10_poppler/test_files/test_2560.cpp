//===----------------------------------------------------------------------===//
// Unit tests for convert_double_or_4_doubles (TEST_ID: 2560)
// File: poppler-structure-element-convert-double-or-4-doubles-test-2560.cc
//===----------------------------------------------------------------------===//

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler/Array.h"
#include "poppler/Object.h"

// The function under test is a static inline in a .cc file.
// Include the implementation unit so the test TU can see it.
#include "glib/poppler-structure-element.cc"

namespace {

class ConvertDoubleOr4DoublesTest_2560 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        // Make death tests more reliable across platforms.
        ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    }

    static void FillSentinel(gdouble v[4])
    {
        v[0] = -1111.0;
        v[1] = -2222.0;
        v[2] = -3333.0;
        v[3] = -4444.0;
    }
};

TEST_F(ConvertDoubleOr4DoublesTest_2560, NumObjectSetsAllFourValues_2560)
{
    Object obj(3.25);
    gdouble values[4];
    FillSentinel(values);

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 3.25);
    EXPECT_DOUBLE_EQ(values[1], 3.25);
    EXPECT_DOUBLE_EQ(values[2], 3.25);
    EXPECT_DOUBLE_EQ(values[3], 3.25);
}

TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayOfFourNumbersCopiesEachElement_2560)
{
    auto *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1.0));
    obj.arrayAdd(Object(2.5));
    obj.arrayAdd(Object(-3));     // int should still be treated as numeric
    obj.arrayAdd(Object(42.125)); // real

    gdouble values[4];
    FillSentinel(values);

    convert_double_or_4_doubles(&obj, values);

    EXPECT_DOUBLE_EQ(values[0], 1.0);
    EXPECT_DOUBLE_EQ(values[1], 2.5);
    EXPECT_DOUBLE_EQ(values[2], -3.0);
    EXPECT_DOUBLE_EQ(values[3], 42.125);
}

TEST_F(ConvertDoubleOr4DoublesTest_2560, ArrayBoundaryExactlyFourElements_2560)
{
    auto *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(0));
    obj.arrayAdd(Object(0));
    obj.arrayAdd(Object(0));
    obj.arrayAdd(Object(0));

    gdouble values[4];
    FillSentinel(values);

    // Should not assert/crash for exactly 4 elements.
    ASSERT_NO_FATAL_FAILURE(convert_double_or_4_doubles(&obj, values));

    EXPECT_DOUBLE_EQ(values[0], 0.0);
    EXPECT_DOUBLE_EQ(values[1], 0.0);
    EXPECT_DOUBLE_EQ(values[2], 0.0);
    EXPECT_DOUBLE_EQ(values[3], 0.0);
}

TEST_F(ConvertDoubleOr4DoublesTest_2560, DeathOnNullObjectPointer_2560)
{
    gdouble values[4];
    FillSentinel(values);

    ASSERT_DEATH(
        {
            convert_double_or_4_doubles(nullptr, values);
        },
        ".*");
}

TEST_F(ConvertDoubleOr4DoublesTest_2560, DeathOnArrayWithWrongLength_2560)
{
    // Length 3 should trigger g_assert(arrayGetLength() == 4).
    auto *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));

    gdouble values[4];
    FillSentinel(values);

    ASSERT_DEATH(
        {
            convert_double_or_4_doubles(&obj, values);
        },
        ".*");
}

TEST_F(ConvertDoubleOr4DoublesTest_2560, DeathOnNonArrayNonNumericObject_2560)
{
    Object obj(true); // bool is neither array nor num per the interface expectations
    gdouble values[4];
    FillSentinel(values);

    ASSERT_DEATH(
        {
            convert_double_or_4_doubles(&obj, values);
        },
        ".*");
}

} // namespace