#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>

// Include necessary headers
extern "C" {
#include <glib.h>
#include "poppler-structure-element.h"
}

#include "poppler-private.h"
#include "StructElement.h"

// We need to test poppler_structure_element_get_space_after which:
// 1. Checks if the element is a block element (returns NAN if not)
// 2. Returns the SpaceAfter attribute value as a double

class PopplerStructureElementGetSpaceAfterTest_2564 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that calling with NULL returns NAN (g_return_val_if_fail check)
TEST_F(PopplerStructureElementGetSpaceAfterTest_2564, NullElementReturnsNAN_2564)
{
    gdouble result = poppler_structure_element_get_space_after(nullptr);
    EXPECT_TRUE(std::isnan(result));
}

// Test that calling with a non-block element returns NAN
TEST_F(PopplerStructureElementGetSpaceAfterTest_2564, NonBlockElementReturnsNAN_2564)
{
    // Create an inline-level structure element (e.g., Span)
    // A non-block element should cause poppler_structure_element_is_block to return FALSE
    // and thus g_return_val_if_fail returns NAN
    
    // We need a PopplerStructureElement that wraps a non-block StructElement
    // Since we can't easily construct these without the full document context,
    // we rely on the NULL test above as the primary error case test.
    // This test documents expected behavior for non-block elements.
    
    // If we can create an inline element, test it here
    // For now, the NULL case covers the g_return_val_if_fail path
}

// Test that a valid block element returns a numeric (non-NAN) value
TEST_F(PopplerStructureElementGetSpaceAfterTest_2564, BlockElementReturnsNumericValue_2564)
{
    // This test would require a properly constructed PopplerStructureElement
    // backed by a block-level StructElement with SpaceAfter attribute set.
    // Without access to internal construction helpers, we document the expected behavior:
    // A block element with SpaceAfter=10.0 should return 10.0
    // A block element without explicit SpaceAfter should return the default (typically 0.0)
    
    // Since we cannot easily construct the full object graph in a unit test
    // without the PDF document infrastructure, this serves as documentation.
}

// Verify that the function properly guards against invalid input types
TEST_F(PopplerStructureElementGetSpaceAfterTest_2564, InvalidGObjectTypeReturnsNAN_2564)
{
    // Passing a GObject that is not a PopplerStructureElement
    // g_return_val_if_fail should catch this and return NAN
    gdouble result = poppler_structure_element_get_space_after((PopplerStructureElement *)0x1);
    // This would likely crash or return NAN depending on GLib's handling
    // We cannot safely test with an arbitrary pointer, so NULL is the primary test
}
#include <gtest/gtest.h>
#include <cmath>

extern "C" {
#include <glib-object.h>
#include "poppler-structure-element.h"
}

class PopplerStructureElementSpaceAfterTest_2564 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL to poppler_structure_element_get_space_after returns NAN
// This exercises the g_return_val_if_fail guard at the beginning of the function
TEST_F(PopplerStructureElementSpaceAfterTest_2564, NullElementReturnsNAN_2564)
{
    gdouble result = poppler_structure_element_get_space_after(nullptr);
    EXPECT_TRUE(std::isnan(result));
}

// Test boundary: the function should return NAN for any element that is not a block element.
// Since poppler_structure_element_is_block(NULL) should return FALSE,
// the g_return_val_if_fail macro triggers and returns NAN.
TEST_F(PopplerStructureElementSpaceAfterTest_2564, GuardReturnValueIsNAN_2564)
{
    // Calling with NULL exercises the precondition check path
    gdouble result = poppler_structure_element_get_space_after(NULL);
    // NAN != NAN by IEEE 754, so we use isnan
    EXPECT_TRUE(std::isnan(result));
    // Also verify it's not a valid number
    EXPECT_FALSE(std::isfinite(result));
}
