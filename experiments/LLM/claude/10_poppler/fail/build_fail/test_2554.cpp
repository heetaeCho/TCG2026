#include <glib.h>
#include <glib-object.h>
#include "poppler-structure-element.h"
#include "poppler-enums.h"
#include <gtest/gtest.h>

// Note: Since PopplerStructureElement is a GObject-based type, we need to work
// with the GObject type system. We test the public API function
// poppler_structure_element_get_border_style based on its interface contract.

class PopplerStructureElementGetBorderStyleTest_2554 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL as poppler_structure_element is handled gracefully
// (g_return_if_fail should cause early return without crash)
TEST_F(PopplerStructureElementGetBorderStyleTest_2554, NullElementDoesNotCrash_2554)
{
    PopplerStructureBorderStyle border_styles[4];
    // g_return_if_fail should handle NULL gracefully - no crash expected
    // We suppress the GLib critical warning for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    poppler_structure_element_get_border_style(nullptr, border_styles);
    g_test_assert_expected_messages();
}

// Test that passing NULL as border_styles is handled gracefully
// This requires a valid PopplerStructureElement, but since we can't easily
// create one without a document, we test with NULL element + NULL styles
// to verify g_return_if_fail guards work in order.
TEST_F(PopplerStructureElementGetBorderStyleTest_2554, NullBorderStylesDoesNotCrash_2554)
{
    // First guard (POPPLER_IS_STRUCTURE_ELEMENT) should fire before the second
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    poppler_structure_element_get_border_style(nullptr, nullptr);
    g_test_assert_expected_messages();
}

// Test that passing an invalid GObject (not a PopplerStructureElement) is handled
TEST_F(PopplerStructureElementGetBorderStyleTest_2554, InvalidGObjectTypeDoesNotCrash_2554)
{
    PopplerStructureBorderStyle border_styles[4];
    // Create a plain GObject which is not a PopplerStructureElement
    GObject *not_a_structure_element = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);

    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    poppler_structure_element_get_border_style((PopplerStructureElement *)not_a_structure_element, border_styles);
    g_test_assert_expected_messages();

    g_object_unref(not_a_structure_element);
}
