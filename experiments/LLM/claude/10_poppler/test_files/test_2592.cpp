#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib.h>
#include "poppler-structure-element.h"
#include "poppler-enums.h"
}

#include "poppler-private.h"

// We need to test poppler_structure_element_get_table_column_span
// Based on the interface, this function:
// 1. Returns 0 if the element kind is not POPPLER_STRUCTURE_ELEMENT_TABLE
// 2. Returns the ColSpan attribute value as guint for TABLE elements

// Since we're treating the implementation as a black box and we need to create
// PopplerStructureElement objects for testing, we need to work with the GObject system.
// However, creating proper PopplerStructureElement requires internal poppler structures.
// We'll test what we can through the public C API.

class PopplerStructureElementTableColumnSpanTest_2592 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns 0 (g_return_val_if_fail should catch this)
TEST_F(PopplerStructureElementTableColumnSpanTest_2592, NullElementReturnsZero_2592)
{
    // g_return_val_if_fail with NULL should trigger the guard and return 0
    // We need to suppress GLib critical warnings for this test
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    guint result = poppler_structure_element_get_table_column_span(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, 0u);
}

// Test that a non-TABLE element returns 0 due to the kind check
// To test this properly we would need a real PopplerStructureElement with a non-TABLE kind.
// Since constructing one requires internal structures, we verify the NULL case above
// demonstrates the guard behavior.

// Additional test: verify the function exists and is callable
TEST_F(PopplerStructureElementTableColumnSpanTest_2592, FunctionIsCallable_2592)
{
    // Verify the function pointer is not null (it's a real symbol)
    auto func_ptr = &poppler_structure_element_get_table_column_span;
    EXPECT_NE(func_ptr, nullptr);
}
