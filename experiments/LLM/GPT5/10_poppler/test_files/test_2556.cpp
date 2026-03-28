// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for convert_color() in poppler-structure-element.cc
// TEST_ID: 2556
//
// Notes:
// - convert_color() is a static inline function in a .cc file (internal linkage).
//   To test it as a black box without changing production code, we include the
//   implementation file directly here.
// - Error paths use g_assert(), which aborts the process when enabled.
//   We use gtest death tests for those cases and skip them if G_DISABLE_ASSERT
//   disables g_assert().

#include <gtest/gtest.h>

#include <glib.h>

#include "poppler/Object.h"
#include "poppler/Array.h"
#include "glib/poppler-page.h"

// Include the implementation to access the internal static inline function.
#include "glib/poppler-structure-element.cc"

namespace {

static Object MakeArrayObjectWithNumbers(std::initializer_list<double> nums)
{
    auto *arr = new Array(nullptr); // Poppler's Array typically accepts XRef*; nullptr is common in unit tests.
    Object obj(arr);
    for (double v : nums) {
        obj.arrayAdd(Object(v));
    }
    return obj;
}

static int ScaledInt(double v)
{
    return static_cast<int>(v * 65535.0);
}

} // namespace

class ConvertColorTest_2556 : public ::testing::Test {
};

TEST_F(ConvertColorTest_2556, ConvertsFirstThreeArrayNumbersWhenLengthNotThree_2556)
{
    // The implementation asserts: object->isArray() && object->arrayGetLength() != 3
    // So we use a length of 4 to satisfy the assert while still providing indices 0..2.
    Object obj = MakeArrayObjectWithNumbers({0.0, 0.5, 1.0, 0.25});

    PopplerColor c{};
    convert_color(&obj, &c);

    EXPECT_EQ(c.red, ScaledInt(0.0));
    EXPECT_EQ(c.green, ScaledInt(0.5));
    EXPECT_EQ(c.blue, ScaledInt(1.0));
}

TEST_F(ConvertColorTest_2556, ConvertsEvenIfValuesOutsideZeroToOne_2556)
{
    Object obj = MakeArrayObjectWithNumbers({1.25, -0.25, 2.0, 0.0});

    PopplerColor c{};
    convert_color(&obj, &c);

    EXPECT_EQ(c.red, ScaledInt(1.25));
    EXPECT_EQ(c.green, ScaledInt(-0.25));
    EXPECT_EQ(c.blue, ScaledInt(2.0));
}

TEST_F(ConvertColorTest_2556, OverwritesExistingColorValues_2556)
{
    Object obj = MakeArrayObjectWithNumbers({0.1, 0.2, 0.3, 0.4});

    PopplerColor c{};
    c.red = 123;
    c.green = 456;
    c.blue = 789;

    convert_color(&obj, &c);

    EXPECT_EQ(c.red, ScaledInt(0.1));
    EXPECT_EQ(c.green, ScaledInt(0.2));
    EXPECT_EQ(c.blue, ScaledInt(0.3));
}

TEST_F(ConvertColorTest_2556, BoundaryUsesSmallFractions_2556)
{
    Object obj = MakeArrayObjectWithNumbers({1.0 / 65535.0, 2.0 / 65535.0, 3.0 / 65535.0, 0.0});

    PopplerColor c{};
    convert_color(&obj, &c);

    EXPECT_EQ(c.red, 1);
    EXPECT_EQ(c.green, 2);
    EXPECT_EQ(c.blue, 3);
}

TEST_F(ConvertColorTest_2556, DeathWhenColorIsNull_2556)
{
#ifdef G_DISABLE_ASSERT
    GTEST_SKIP() << "g_assert disabled (G_DISABLE_ASSERT): cannot death-test null color.";
#else
    Object obj = MakeArrayObjectWithNumbers({0.0, 0.0, 0.0, 0.0});
    ASSERT_DEATH({ convert_color(&obj, nullptr); }, "");
#endif
}

TEST_F(ConvertColorTest_2556, DeathWhenObjectIsNotArray_2556)
{
#ifdef G_DISABLE_ASSERT
    GTEST_SKIP() << "g_assert disabled (G_DISABLE_ASSERT): cannot death-test non-array object.";
#else
    Object notArray(1.0);

    PopplerColor c{};
    ASSERT_DEATH({ convert_color(&notArray, &c); }, "");
#endif
}

TEST_F(ConvertColorTest_2556, DeathWhenArrayLengthIsExactlyThree_2556)
{
#ifdef G_DISABLE_ASSERT
    GTEST_SKIP() << "g_assert disabled (G_DISABLE_ASSERT): cannot death-test length==3.";
#else
    // The implementation asserts arrayGetLength() != 3, so length==3 should abort.
    Object obj = MakeArrayObjectWithNumbers({0.0, 0.5, 1.0});

    PopplerColor c{};
    ASSERT_DEATH({ convert_color(&obj, &c); }, "");
#endif
}

TEST_F(ConvertColorTest_2556, DeathWhenArrayTooShortToReadThreeEntries_2556)
{
#ifdef G_DISABLE_ASSERT
    GTEST_SKIP() << "g_assert disabled (G_DISABLE_ASSERT): cannot death-test short array behavior.";
#else
    // Length 2 satisfies "!= 3", so it passes the explicit assert, but the subsequent
    // arrayGet(2) is expected to fail in some observable way (commonly an assert/abort).
    // We verify it terminates rather than producing a valid color.
    Object obj = MakeArrayObjectWithNumbers({0.0, 0.5});

    PopplerColor c{};
    ASSERT_DEATH({ convert_color(&obj, &c); }, "");
#endif
}