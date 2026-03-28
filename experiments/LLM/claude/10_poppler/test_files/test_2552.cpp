#include <glib.h>
#include <glib-object.h>
#include "poppler-structure-element.h"
#include "poppler-private.h"
#include "poppler-enums.h"
#include <gtest/gtest.h>

// Forward declarations for helper functions if needed
extern "C" {
// We need access to the poppler structure element API
PopplerStructureWritingMode poppler_structure_element_get_writing_mode(PopplerStructureElement *poppler_structure_element);
}

class PopplerStructureElementWritingModeTest_2552 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns the default value (first enum value)
TEST_F(PopplerStructureElementWritingModeTest_2552, NullElementReturnsDefault_2552) {
    // g_return_val_if_fail should trigger and return the default value
    // We suppress the GLib warning for this test
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    
    PopplerStructureWritingMode result = poppler_structure_element_get_writing_mode(nullptr);
    
    g_test_assert_expected_messages();
    
    // The default should be the first value in the enum, which is typically
    // POPPLER_STRUCTURE_WRITING_MODE_LR_TB
    EXPECT_EQ(result, POPPLER_STRUCTURE_WRITING_MODE_LR_TB);
}

// Test that passing an invalid GObject (not a PopplerStructureElement) returns default
TEST_F(PopplerStructureElementWritingModeTest_2552, InvalidObjectReturnsDefault_2552) {
    // Create some arbitrary GObject that is NOT a PopplerStructureElement
    GObject *not_a_structure_element = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_STRUCTURE_ELEMENT*");
    
    PopplerStructureWritingMode result = poppler_structure_element_get_writing_mode((PopplerStructureElement *)not_a_structure_element);
    
    g_test_assert_expected_messages();
    
    EXPECT_EQ(result, POPPLER_STRUCTURE_WRITING_MODE_LR_TB);
    
    g_object_unref(not_a_structure_element);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
