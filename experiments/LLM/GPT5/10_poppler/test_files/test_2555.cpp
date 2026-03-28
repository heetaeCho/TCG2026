// convert_doubles_array_test_2555.cc
//
// Unit tests for convert_doubles_array() in poppler-structure-element.cc
//
// NOTE: This function is defined as static inline in the .cc file, so we
// include that .cc directly to make it visible in this test translation unit.

#include <gtest/gtest.h>

#include <glib.h>

#include <type_traits>
#include <utility>

#include "poppler/Object.h"

// Pull the static inline under test into this TU.
#include "TestProjects/poppler/glib/poppler-structure-element.cc"

namespace {

// Forward-declare types that may be referenced by Array constructors.
class XRef;

// Helper: Construct an Object that is an Array, without assuming a single
// specific Array ctor signature. This avoids hard-coding internal ctor details.
static Object MakeArrayObject_2555()
{
    // Array is part of Poppler internals; it should be visible via Object.h.
    // Try a few common constructor shapes via compile-time checks.
    if constexpr (std::is_constructible_v<Array>) {
        auto *arr = new Array();
        return Object(arr);
    } else if constexpr (std::is_constructible_v<Array, XRef *>) {
        auto *arr = new Array(static_cast<XRef *>(nullptr));
        return Object(arr);
    } else if constexpr (std::is_constructible_v<Array, int>) {
        auto *arr = new Array(0);
        return Object(arr);
    } else if constexpr (std::is_constructible_v<Array, long long>) {
        auto *arr = new Array(0LL);
        return Object(arr);
    } else {
        // If none match, fail loudly at compile time.
        static_assert(std::is_constructible_v<Array>,
                      "No supported Array constructor found for tests.");
    }
}

// Helper: Add numeric elements to an array Object.
static void AddNumsToArray_2555(Object &arrObj, std::initializer_list<double> nums)
{
    for (double v : nums) {
        arrObj.arrayAdd(Object(v));
    }
}

class ConvertDoublesArrayTest_2555 : public ::testing::Test {
};

} // namespace

TEST_F(ConvertDoublesArrayTest_2555, ArraySetsNValues_ButDoesNotModifyOutPointer_2555)
{
    Object arrObj = MakeArrayObject_2555();
    ASSERT_TRUE(arrObj.isArray());

    AddNumsToArray_2555(arrObj, {1.25, -2.0, 3.5});

    guint n_values = 999; // sentinel
    // Use a sentinel pointer value and verify it is not modified.
    gdouble *out_values = reinterpret_cast<gdouble *>(static_cast<uintptr_t>(0x1));

    ASSERT_NO_FATAL_FAILURE(convert_doubles_array(&arrObj, &out_values, &n_values));

    EXPECT_EQ(n_values, 3u);
    // Observed behavior through the interface: the out pointer is not modified.
    EXPECT_EQ(out_values, reinterpret_cast<gdouble *>(static_cast<uintptr_t>(0x1)));
}

TEST_F(ConvertDoublesArrayTest_2555, EmptyArrayProducesZeroCount_2555)
{
    Object arrObj = MakeArrayObject_2555();
    ASSERT_TRUE(arrObj.isArray());

    guint n_values = 123; // sentinel
    gdouble *out_values = nullptr;

    ASSERT_NO_FATAL_FAILURE(convert_doubles_array(&arrObj, &out_values, &n_values));

    EXPECT_EQ(n_values, 0u);
    // Out pointer remains unchanged (nullptr).
    EXPECT_EQ(out_values, nullptr);
}

TEST_F(ConvertDoublesArrayTest_2555, DeathWhenObjectIsNotArray_2555)
{
    Object notArrayObj(3.14);
    ASSERT_FALSE(notArrayObj.isArray());

    guint n_values = 0;
    gdouble *out_values = nullptr;

    EXPECT_DEATH(
        {
            convert_doubles_array(&notArrayObj, &out_values, &n_values);
        },
        ".*");
}

TEST_F(ConvertDoublesArrayTest_2555, DeathWhenOutParamsAreNull_2555)
{
    Object arrObj = MakeArrayObject_2555();
    ASSERT_TRUE(arrObj.isArray());

    guint n_values = 0;
    gdouble *out_values = nullptr;

    // Null n_values pointer should assert.
    EXPECT_DEATH(
        {
            convert_doubles_array(&arrObj, &out_values, nullptr);
        },
        ".*");

    // Null values pointer should assert.
    EXPECT_DEATH(
        {
            convert_doubles_array(&arrObj, nullptr, &n_values);
        },
        ".*");
}