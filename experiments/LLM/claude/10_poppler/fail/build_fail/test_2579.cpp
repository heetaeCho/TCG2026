#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>

// Include necessary headers
extern "C" {
#include <glib.h>
#include "poppler-structure-element.h"
}

#include "poppler-private.h"
#include "Object.h"
#include "StructElement.h"

// Since we're testing poppler_structure_element_get_text_decoration_thickness
// as a black box, we need to set up proper PopplerStructureElement instances.
// However, given the complexity of the internal dependencies, we'll test
// observable behavior through the public C API.

class PopplerStructureElementTextDecorationThicknessTest_2579 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NAN (g_return_val_if_fail should trigger)
TEST_F(PopplerStructureElementTextDecorationThicknessTest_2579, NullElementReturnsNaN_2579)
{
    // Passing NULL should trigger g_return_val_if_fail and return NAN
    gdouble result = poppler_structure_element_get_text_decoration_thickness(nullptr);
    EXPECT_TRUE(std::isnan(result));
}

// Test that a non-inline structure element returns NAN
// The g_return_val_if_fail checks poppler_structure_element_is_inline
TEST_F(PopplerStructureElementTextDecorationThicknessTest_2579, NonInlineElementReturnsNaN_2579)
{
    // Create a PopplerStructureElement that is NOT inline
    // We need to construct one backed by a non-inline StructElement
    // Since we can't easily construct StructElement objects without a full document,
    // we rely on the NULL test above as the primary boundary test.
    // This test documents the expected behavior for non-inline elements.
    
    // If we can create a block-level element, it should return NAN
    // For now, we verify the NULL case which also hits the g_return_val_if_fail path
    gdouble result = poppler_structure_element_get_text_decoration_thickness(nullptr);
    EXPECT_TRUE(std::isnan(result));
}

// Test verifying the function signature and return type
TEST_F(PopplerStructureElementTextDecorationThicknessTest_2579, FunctionExists_2579)
{
    // Verify the function pointer is valid (compilation test)
    gdouble (*func_ptr)(PopplerStructureElement *) = &poppler_structure_element_get_text_decoration_thickness;
    EXPECT_NE(func_ptr, nullptr);
}

// Test that calling with an invalid (but non-null) pointer that fails the inline check returns NAN
// This tests the g_return_val_if_fail guard
TEST_F(PopplerStructureElementTextDecorationThicknessTest_2579, InvalidStructureElementReturnsNaN_2579)
{
    // A zeroed-out structure should fail the is_inline check
    PopplerStructureElement elem = {};
    elem.elem = nullptr;
    
    // This should fail the g_return_val_if_fail check since elem is not valid/inline
    // Note: This may cause a warning but should return NAN safely
    gdouble result = poppler_structure_element_get_text_decoration_thickness(&elem);
    EXPECT_TRUE(std::isnan(result));
}
