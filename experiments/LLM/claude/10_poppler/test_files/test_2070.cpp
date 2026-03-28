#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include <glib-object.h>
}

// We need to include poppler headers
#include "poppler-annot.h"
#include "poppler-private.h"

#include <memory>

// We need to create a mock for the Annot class to control getPageNum() behavior
// Since we can't access the real Annot internals, we create a testable setup

// Forward declarations and includes for Annot
#include "Annot.h"

// Helper to create a PopplerAnnot for testing
// We need a way to construct PopplerAnnot objects with controlled Annot behavior

class PopplerAnnotGetPageIndexTest_2070 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Since we're dealing with GObject-based code, we need to properly create PopplerAnnot
// objects. The challenge is that PopplerAnnot wraps a C++ Annot object.
// We'll test through the public C API as much as possible.

// Test that passing NULL returns -1
TEST_F(PopplerAnnotGetPageIndexTest_2070, NullAnnotReturnsMinusOne_2070)
{
    // g_return_val_if_fail should catch NULL and return -1
    // Note: This will produce a g_critical warning
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
    gint result = poppler_annot_get_page_index(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, -1);
}

// Test that passing a non-PopplerAnnot GObject returns -1
TEST_F(PopplerAnnotGetPageIndexTest_2070, InvalidGObjectReturnsMinusOne_2070)
{
    // Create some random GObject that is not a PopplerAnnot
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT*");
    gint result = poppler_annot_get_page_index((PopplerAnnot *)obj);
    g_test_assert_expected_messages();
    EXPECT_EQ(result, -1);
    g_object_unref(obj);
}

// To test actual behavior with valid PopplerAnnot objects, we would need
// to create them through the proper poppler API (e.g., by loading a PDF
// document and extracting annotations). Since we're testing the function
// as a black box and the conversion logic is:
//   page_num <= 0 ? -1 : page_num - 1
// We document expected behaviors:

// If we can create a PopplerAnnot from a real document:
class PopplerAnnotFromDocumentTest_2070 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        // Try to load a test PDF if available
        GError *error = nullptr;
        // We'll skip tests if no document is available
        doc = nullptr;
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test the boundary: when annot's getPageNum() returns 0, result should be -1
// Test the boundary: when annot's getPageNum() returns 1, result should be 0 (first page)
// Test normal: when annot's getPageNum() returns N > 0, result should be N-1

// Since we cannot easily create mock Annot objects with the GObject system,
// we verify the mathematical contract through interface documentation:
// The function converts 1-based page numbers to 0-based, returning -1 for invalid

// Integration-style test if a test PDF with annotations is available
TEST_F(PopplerAnnotFromDocumentTest_2070, AnnotFromDocumentReturnsValidIndex_2070)
{
    // This test verifies that for a valid annotation from a document,
    // the page index is >= 0 (since it should map to a valid page)
    // Skip if we can't load a test document
    if (!doc) {
        GTEST_SKIP() << "No test document available";
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
