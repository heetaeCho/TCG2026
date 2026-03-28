#include <gtest/gtest.h>
#include <glib-object.h>

// Forward declarations and includes needed for the poppler glib API
extern "C" {
#include "poppler-document.h"
}

class PopplerIndexIterFreeTest_2219 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that passing nullptr does not crash
TEST_F(PopplerIndexIterFreeTest_2219, FreeNullIterDoesNotCrash_2219)
{
    // Should handle nullptr gracefully without crashing
    poppler_index_iter_free(nullptr);
    // If we reach here, the test passed (no crash/segfault)
    SUCCEED();
}

// Test that freeing a valid index iter obtained from a real document works
TEST_F(PopplerIndexIterFreeTest_2219, FreeValidIterFromDocument_2219)
{
    GError *error = nullptr;
    
    // Try to load a simple PDF to get a valid PopplerDocument
    // We'll use a data URI or a known test file path
    // Since we may not have a file available, we test what we can
    
    // Create a minimal PDF in memory
    const char *minimal_pdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";
    
    gsize pdf_len = strlen(minimal_pdf);
    
    // Try to create a document from data
    PopplerDocument *doc = poppler_document_new_from_data(
        (char *)minimal_pdf, (int)pdf_len, nullptr, &error);
    
    if (doc != nullptr) {
        // Try to get index iter - may be NULL if no TOC
        PopplerIndexIter *iter = poppler_index_iter_new(doc);
        
        // Free iter (could be NULL, which should be handled)
        poppler_index_iter_free(iter);
        
        g_object_unref(doc);
        SUCCEED();
    } else {
        // If we can't create a document, just test null case
        if (error) {
            g_error_free(error);
        }
        poppler_index_iter_free(nullptr);
        SUCCEED();
    }
}

// Test calling free with nullptr multiple times doesn't cause issues
TEST_F(PopplerIndexIterFreeTest_2219, FreeNullMultipleTimes_2219)
{
    poppler_index_iter_free(nullptr);
    poppler_index_iter_free(nullptr);
    poppler_index_iter_free(nullptr);
    SUCCEED();
}
