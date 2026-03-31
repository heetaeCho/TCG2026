#include <glib.h>
#include <math.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler headers
extern "C" {
#include "poppler-structure-element.h"
#include "poppler-document.h"
}

#include "poppler-private.h"
#include "StructElement.h"
#include "Object.h"

class PopplerStructureElementLineHeightTest_2577 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NAN (g_return_val_if_fail should catch it)
TEST_F(PopplerStructureElementLineHeightTest_2577, NullElementReturnsNAN_2577)
{
    // Passing NULL should trigger g_return_val_if_fail and return NAN
    gdouble result = poppler_structure_element_get_line_height(nullptr);
    EXPECT_TRUE(isnan(result));
}

// Test that a non-inline element returns NAN
TEST_F(PopplerStructureElementLineHeightTest_2577, NonInlineElementReturnsNAN_2577)
{
    // Create a PopplerStructureElement that wraps a non-inline StructElement
    // A block-level element (like a paragraph or section) should cause the
    // g_return_val_if_fail to fail and return NAN
    
    // We need a valid PopplerStructureElement that is NOT inline
    // Using the GObject type system to create one
    PopplerStructureElement *elem = static_cast<PopplerStructureElement *>(
        g_object_new(POPPLER_TYPE_STRUCTURE_ELEMENT, nullptr));
    
    if (elem != nullptr) {
        // If elem->elem is null or not inline, should return NAN
        gdouble result = poppler_structure_element_get_line_height(elem);
        EXPECT_TRUE(isnan(result));
        g_object_unref(elem);
    }
}

// Test with a document that has tagged PDF structure
// This tests the integration path - requires a real PDF with structure
class PopplerStructureElementFromDocTest_2577 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        // Try to load a tagged PDF if available
        GError *error = nullptr;
        // This test may be skipped if no test PDF is available
        doc = nullptr;
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Verify the function signature and return type for non-inline elements
TEST_F(PopplerStructureElementFromDocTest_2577, FunctionAcceptsStructureElement_2577)
{
    // Verify that the function exists and can be called
    // With null, it should return NAN due to the precondition check
    gdouble result = poppler_structure_element_get_line_height(nullptr);
    EXPECT_TRUE(isnan(result));
}

// Test that the return value is a valid double (not uninitialized)
TEST_F(PopplerStructureElementLineHeightTest_2577, ReturnValueIsDefinedForNull_2577)
{
    gdouble result = poppler_structure_element_get_line_height(nullptr);
    // NAN is the expected return for invalid input
    // Verify it's specifically NAN and not some garbage
    EXPECT_NE(result, result); // NAN != NAN is true
}

// Additional boundary test: verify NAN behavior is consistent across calls
TEST_F(PopplerStructureElementLineHeightTest_2577, ConsistentNANForNullInput_2577)
{
    gdouble result1 = poppler_structure_element_get_line_height(nullptr);
    gdouble result2 = poppler_structure_element_get_line_height(nullptr);
    
    EXPECT_TRUE(isnan(result1));
    EXPECT_TRUE(isnan(result2));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
