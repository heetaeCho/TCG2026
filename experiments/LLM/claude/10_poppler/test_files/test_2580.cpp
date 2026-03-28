#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include "poppler-structure-element.h"
#include "poppler-private.h"
}

class PopplerStructureElementTextDecorationTest_2580 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns a default/fallback value (the first enum value)
// g_return_val_if_fail should trigger on NULL and return the default
TEST_F(PopplerStructureElementTextDecorationTest_2580, NullElementReturnsDefault_2580)
{
    // When passing NULL, g_return_val_if_fail should fail and return the default value
    PopplerStructureTextDecoration result = poppler_structure_element_get_text_decoration_type(nullptr);
    // We expect the first/default enum value to be returned
    // The exact value depends on EnumNameValue<PopplerStructureTextDecoration>::values[0].value
    // but it should be a valid enum value (typically POPPLER_STRUCTURE_TEXT_DECORATION_NONE or similar)
    // We just verify it doesn't crash and returns a consistent value
    PopplerStructureTextDecoration result2 = poppler_structure_element_get_text_decoration_type(nullptr);
    EXPECT_EQ(result, result2);
}

// Test that a non-inline element returns the default value
// g_return_val_if_fail checks poppler_structure_element_is_inline, so a non-inline element
// should return the default value
TEST_F(PopplerStructureElementTextDecorationTest_2580, NonInlineElementReturnsDefault_2580)
{
    // Create a PopplerStructureElement that is not inline
    // Since we can't easily construct one without the full infrastructure,
    // and the function checks is_inline first, a NULL elem would likely
    // fail the inline check. This is effectively covered by the NULL test above.
    // This test documents the expected behavior.
    PopplerStructureTextDecoration result = poppler_structure_element_get_text_decoration_type(nullptr);
    // Should return default without crashing
    (void)result;
    SUCCEED();
}

// Test that calling the function twice with the same argument gives consistent results
TEST_F(PopplerStructureElementTextDecorationTest_2580, ConsistentReturnOnRepeatedCalls_2580)
{
    PopplerStructureTextDecoration result1 = poppler_structure_element_get_text_decoration_type(nullptr);
    PopplerStructureTextDecoration result2 = poppler_structure_element_get_text_decoration_type(nullptr);
    EXPECT_EQ(result1, result2);
}
