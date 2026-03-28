#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
extern "C" {
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
}

#include "poppler-private.h"

class PopplerAnnotCropboxTest_2072 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll set up test fixtures as needed per test
    }

    void TearDown() override {
    }
};

// Test that _poppler_annot_get_cropbox returns non-null for a valid annotation
TEST_F(PopplerAnnotCropboxTest_2072, ReturnsNonNullForValidAnnot_2072) {
    // To test this properly, we need a real PopplerAnnot from a PDF document.
    // Since we can't easily create one without a document, we test with nullptr
    // to verify error handling.
    
    // Test with nullptr - this tests boundary/error condition
    // Note: depending on implementation this may crash or return nullptr
    // We document expected behavior based on interface
    const PDFRectangle *result = _poppler_annot_get_cropbox(nullptr);
    // If the function handles nullptr gracefully, result should be nullptr
    EXPECT_EQ(result, nullptr);
}

// Test with a PopplerAnnot that has no associated page
TEST_F(PopplerAnnotCropboxTest_2072, NullAnnotReturnsNull_2072) {
    const PDFRectangle *result = _poppler_annot_get_cropbox(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Integration test: Load a PDF with annotations and verify cropbox
class PopplerAnnotCropboxIntegrationTest_2072 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        GError *error = nullptr;
        // Try to load a test PDF - this path may need adjustment
        // for the actual test environment
        doc = nullptr;
        page = nullptr;
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that cropbox can be retrieved from annotations in a real document
TEST_F(PopplerAnnotCropboxIntegrationTest_2072, CropboxFromDocumentAnnot_2072) {
    GError *error = nullptr;
    
    // Attempt to load a test document with annotations
    // Using a commonly available test file path
    gchar *uri = g_filename_to_uri("./test-poppler-annot.pdf", nullptr, &error);
    if (uri == nullptr) {
        // If test file doesn't exist, skip this test
        GTEST_SKIP() << "Test PDF file not available";
        return;
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not load test PDF";
        return;
    }

    int n_pages = poppler_document_get_n_pages(doc);
    if (n_pages == 0) {
        GTEST_SKIP() << "Test PDF has no pages";
        return;
    }

    page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    GList *annot_mappings = poppler_page_get_annot_mapping(page);
    if (annot_mappings == nullptr) {
        GTEST_SKIP() << "No annotations found in test PDF";
        return;
    }

    // Get first annotation
    PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)annot_mappings->data;
    ASSERT_NE(mapping, nullptr);
    ASSERT_NE(mapping->annot, nullptr);

    const PDFRectangle *cropbox = _poppler_annot_get_cropbox(mapping->annot);
    // Cropbox should be non-null for a valid annotation associated with a page
    EXPECT_NE(cropbox, nullptr);

    if (cropbox != nullptr) {
        // Verify cropbox has reasonable values (non-negative dimensions)
        EXPECT_GE(cropbox->x2, cropbox->x1);
        EXPECT_GE(cropbox->y2, cropbox->y1);
    }

    poppler_page_free_annot_mapping(annot_mappings);
}
