// File: poppler_structure_element_get_column_widths_test_2586.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib.h>
#include "poppler.h"
}

// We treat the implementation as a black box and only test
// observable behavior through the public interface.

class PopplerStructureElementGetColumnWidthsTest_2586 : public ::testing::Test {
protected:
    void SetUp() override {
        element = nullptr;
    }

    void TearDown() override {
        // Nothing to clean up since we never create a valid element here.
        element = nullptr;
    }

    PopplerStructureElement *element;
};

/**
 * Test normal operation when poppler_structure_element is NULL.
 * According to g_return_val_if_fail, passing NULL should return NULL.
 */
TEST_F(PopplerStructureElementGetColumnWidthsTest_2586,
       ReturnsNullWhenElementIsNull_2586)
{
    guint n_values = 123; // sentinel value
    gdouble *result = poppler_structure_element_get_column_widths(nullptr, &n_values);

    EXPECT_EQ(result, nullptr);
    // n_values should remain unchanged because function exits early.
    EXPECT_EQ(n_values, 123u);
}

/**
 * Test boundary condition when n_values is NULL.
 * According to g_return_val_if_fail, passing NULL n_values should return NULL.
 */
TEST_F(PopplerStructureElementGetColumnWidthsTest_2586,
       ReturnsNullWhenNValuesIsNull_2586)
{
    // element is NULL as well, but first guard checks grouping;
    // still, since element is NULL, function must return NULL.
    gdouble *result = poppler_structure_element_get_column_widths(nullptr, nullptr);

    EXPECT_EQ(result, nullptr);
}

/**
 * Test boundary condition: non-null element but NULL n_values.
 * Since we cannot construct a valid grouping element without
 * re-implementing logic, we verify only observable guard behavior.
 */
TEST_F(PopplerStructureElementGetColumnWidthsTest_2586,
       ReturnsNullWhenValidElementButNValuesNull_2586)
{
    // We simulate a non-null pointer without assuming internal layout.
    // This is safe because function should fail early due to n_values == nullptr.
    PopplerStructureElement dummy{};
    guint *null_n_values = nullptr;

    gdouble *result =
        poppler_structure_element_get_column_widths(&dummy, null_n_values);

    EXPECT_EQ(result, nullptr);
}

/**
 * Test boundary case where both parameters are invalid.
 * Should consistently return NULL.
 */
TEST_F(PopplerStructureElementGetColumnWidthsTest_2586,
       ReturnsNullWhenBothParametersInvalid_2586)
{
    gdouble *result =
        poppler_structure_element_get_column_widths(nullptr, nullptr);

    EXPECT_EQ(result, nullptr);
}

/**
 * Exceptional-like observable case:
 * If element is non-grouping (unknown here), function must return NULL.
 * Since we cannot control grouping status without re-implementation,
 * we validate that passing an arbitrary element does not crash and
 * returns either NULL or a valid pointer. If NULL, it's acceptable.
 */
TEST_F(PopplerStructureElementGetColumnWidthsTest_2586,
       DoesNotCrashWithArbitraryElementPointer_2586)
{
    PopplerStructureElement dummy{};
    guint n_values = 0;

    gdouble *result =
        poppler_structure_element_get_column_widths(&dummy, &n_values);

    // Black-box expectation: either NULL (most likely)
    // or non-null pointer with n_values set.
    // We do not assume internal behavior.
    if (result == nullptr) {
        SUCCEED();
    } else {
        EXPECT_GT(n_values, 0u);
        g_free(result);
    }
}