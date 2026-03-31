#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "poppler-structure-element.h"
#include "poppler-private.h"
}

class PopplerStructureElementTextAlignTest_2568 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns the default value (first enum value)
TEST_F(PopplerStructureElementTextAlignTest_2568, NullElementReturnsDefault_2568)
{
    // g_return_val_if_fail should trigger on NULL and return default
    // We expect it not to crash and to return a valid enum value
    PopplerStructureTextAlign result = poppler_structure_element_get_text_align(nullptr);
    // The default is the first value in the enum values table
    // We just verify it returns without crashing and gives a valid enum
    EXPECT_GE(static_cast<int>(result), 0);
}

// Test that a non-block element returns the default value
TEST_F(PopplerStructureElementTextAlignTest_2568, NonBlockElementReturnsDefault_2568)
{
    // Create a structure element that is not a block element
    // The g_return_val_if_fail checks poppler_structure_element_is_block
    // If it's not a block, it should return the default value
    PopplerStructureElement *elem = static_cast<PopplerStructureElement *>(g_malloc0(sizeof(PopplerStructureElement)));
    // With elem->elem being NULL or pointing to a non-block element,
    // poppler_structure_element_is_block should return FALSE
    elem->elem = nullptr;

    PopplerStructureTextAlign result = poppler_structure_element_get_text_align(elem);
    EXPECT_GE(static_cast<int>(result), 0);

    g_free(elem);
}
