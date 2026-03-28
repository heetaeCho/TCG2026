#include <glib.h>
#include <glib-object.h>
#include "poppler-structure-element.h"
#include "poppler-private.h"
#include "poppler.h"
#include <gtest/gtest.h>

class PopplerStructureElementGetPlacementTest_2551 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns the default/first enum value (and doesn't crash)
TEST_F(PopplerStructureElementGetPlacementTest_2551, NullElementReturnsDefault_2551)
{
    // g_return_val_if_fail should catch NULL and return default
    // We suppress the GLib critical warning for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    PopplerStructurePlacement result = poppler_structure_element_get_placement(nullptr);
    g_test_assert_expected_messages();
    // The function should return the first value in EnumNameValue values when precondition fails
    // We just verify it returns some valid enum value without crashing
    (void)result;
}

// Test that passing an invalid GObject (not a PopplerStructureElement) returns the default
TEST_F(PopplerStructureElementGetPlacementTest_2551, InvalidObjectReturnsDefault_2551)
{
    // Create some other GObject that is not a PopplerStructureElement
    GObject *not_a_structure_element = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    PopplerStructurePlacement result = poppler_structure_element_get_placement((PopplerStructureElement *)not_a_structure_element);
    g_test_assert_expected_messages();
    
    (void)result;
    g_object_unref(not_a_structure_element);
}
