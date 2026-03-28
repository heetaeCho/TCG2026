#include <gtest/gtest.h>
#include <glib.h>

// Forward declarations and includes needed for the poppler glib API
extern "C" {
#include "poppler-structure-element.h"
#include "poppler-document.h"
}

class PopplerStructureElementIterTest_2539 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL iter returns NULL
TEST_F(PopplerStructureElementIterTest_2539, NullIterReturnsNull_2539)
{
    // g_return_val_if_fail should cause NULL return when iter is nullptr
    // Note: This may also produce a GLib warning/critical message
    PopplerStructureElement *result = poppler_structure_element_iter_get_element(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with a valid PDF document that has structure elements
class PopplerStructureElementDocTest_2539 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        // Try to load a tagged PDF for testing
        GError *error = nullptr;
        // Use a test PDF if available; this test may be skipped if no suitable PDF exists
        gchar *uri = g_filename_to_uri("./test_tagged.pdf", nullptr, &error);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, &error);
            g_free(uri);
        }
        if (error) {
            g_error_free(error);
        }
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test getting element from a valid structure element iterator (requires tagged PDF)
TEST_F(PopplerStructureElementDocTest_2539, GetElementFromValidIter_2539)
{
    if (!doc) {
        GTEST_SKIP() << "No test PDF available for structure element testing";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    EXPECT_NE(elem, nullptr);
    
    if (elem) {
        g_object_unref(elem);
    }
    poppler_structure_element_iter_free(iter);
}

// Test iterating through multiple elements
TEST_F(PopplerStructureElementDocTest_2539, IterateMultipleElements_2539)
{
    if (!doc) {
        GTEST_SKIP() << "No test PDF available for structure element testing";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    int count = 0;
    do {
        PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
        EXPECT_NE(elem, nullptr);
        if (elem) {
            count++;
            g_object_unref(elem);
        }
    } while (poppler_structure_element_iter_next(iter));
    
    EXPECT_GT(count, 0);
    poppler_structure_element_iter_free(iter);
}

// Test getting element returns a valid GObject
TEST_F(PopplerStructureElementDocTest_2539, ReturnedElementIsValidGObject_2539)
{
    if (!doc) {
        GTEST_SKIP() << "No test PDF available for structure element testing";
    }
    
    PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
    if (!iter) {
        GTEST_SKIP() << "Document has no structure elements";
    }
    
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
    ASSERT_NE(elem, nullptr);
    EXPECT_TRUE(G_IS_OBJECT(elem));
    
    g_object_unref(elem);
    poppler_structure_element_iter_free(iter);
}
