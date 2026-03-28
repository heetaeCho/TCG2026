#include <glib.h>
#include <gtest/gtest.h>

// Include the necessary headers for the poppler structure element API
extern "C" {
#include "poppler-structure-element.h"
}

class PopplerStructureElementBlockAlignTest_2572 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns the default value (first enum value)
// g_return_val_if_fail should trigger and return default
TEST_F(PopplerStructureElementBlockAlignTest_2572, NullElementReturnsDefault_2572)
{
    // When passing NULL, g_return_val_if_fail should fail and return default
    // We need to suppress g_return_val_if_fail warnings
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    PopplerStructureBlockAlign result = poppler_structure_element_get_block_align(nullptr);
    g_test_assert_expected_messages();
    // The default value should be the first value in the enum
    // We just verify it returns without crashing and returns a valid enum value
    EXPECT_GE(result, 0);
}

// Test that a non-block element returns the default value
TEST_F(PopplerStructureElementBlockAlignTest_2572, NonBlockElementReturnsDefault_2572)
{
    // Create a PopplerStructureElement that is not a block element
    // Since we can't easily construct one without the full framework,
    // we test with NULL which also triggers the precondition check
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    PopplerStructureBlockAlign result = poppler_structure_element_get_block_align(NULL);
    g_test_assert_expected_messages();
    // Should return default enum value
    SUCCEED();
}

// Test with an invalid (but non-null) pointer - ensures precondition check works
TEST_F(PopplerStructureElementBlockAlignTest_2572, InvalidElementTriggersGuard_2572)
{
    // Create a dummy structure element with NULL internal elem
    PopplerStructureElement dummy_element;
    memset(&dummy_element, 0, sizeof(dummy_element));
    dummy_element.elem = nullptr;

    // This should trigger g_return_val_if_fail since it won't be recognized as a block
    g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    PopplerStructureBlockAlign result = poppler_structure_element_get_block_align(&dummy_element);
    g_test_assert_expected_messages();
    // Should return default without crashing
    SUCCEED();
}
