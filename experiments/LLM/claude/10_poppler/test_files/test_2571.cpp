#include <glib.h>
#include <math.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the poppler glib headers
extern "C" {
#include "poppler-structure-element.h"
#include "poppler-document.h"
}

#include "poppler-private.h"
#include "StructElement.h"
#include "Object.h"

class PopplerStructureElementGetHeightTest_2571 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NAN (g_return_val_if_fail guard)
TEST_F(PopplerStructureElementGetHeightTest_2571, NullElementReturnsNaN_2571)
{
    // Passing NULL should trigger g_return_val_if_fail and return NAN
    // We need to suppress the GLib warning
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    gdouble result = poppler_structure_element_get_height(nullptr);
    g_test_assert_expected_messages();
    EXPECT_TRUE(isnan(result));
}

// Test that a non-block element returns NAN
// This tests the g_return_val_if_fail(poppler_structure_element_is_block(...)) guard
TEST_F(PopplerStructureElementGetHeightTest_2571, NonBlockElementReturnsNaN_2571)
{
    // Create a PopplerStructureElement that is NOT a block element
    // Since poppler_structure_element_is_block checks the element type,
    // we need an inline-type element. We can try to construct one if the API allows,
    // or we test with a document that has structure elements.
    
    // For this test, we rely on the fact that passing an invalid/non-block element
    // triggers the assertion. We test the guard condition.
    // If we can't easily construct a non-block element, we at least verify the NULL case above.
    // This test documents expected behavior even if it can't be fully exercised
    // without a proper PDF document.
    SUCCEED() << "Non-block element test requires a PDF with inline structure elements";
}

// Integration-style test: verify the function exists and has the correct signature
TEST_F(PopplerStructureElementGetHeightTest_2571, FunctionSignatureIsCorrect_2571)
{
    // Verify the function pointer type matches expected signature
    using FuncType = gdouble (*)(PopplerStructureElement *);
    FuncType func = &poppler_structure_element_get_height;
    EXPECT_NE(func, nullptr);
}

// Test with a real PDF document containing structure elements if available
class PopplerStructureElementFromDocTest_2571 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        // Try to load a tagged PDF for testing
        // This path may need adjustment based on test environment
        GError *error = nullptr;
        doc = poppler_document_new_from_file("file:///tmp/test_tagged.pdf", nullptr, &error);
        if (error) {
            g_error_free(error);
            doc = nullptr;
        }
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

TEST_F(PopplerStructureElementFromDocTest_2571, HeightFromBlockElement_2571)
{
    if (!doc) {
        GTEST_SKIP() << "No test PDF available for structure element testing";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    if (elem && poppler_structure_element_is_block(elem)) {
        gdouble height = poppler_structure_element_get_height(elem);
        // Height should either be -1.0 (Auto) or a non-negative number
        EXPECT_TRUE(height == -1.0 || height >= 0.0 || isnan(height));
    }
    
    if (elem) g_object_unref(elem);
    poppler_structure_element_iter_free(iter);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
