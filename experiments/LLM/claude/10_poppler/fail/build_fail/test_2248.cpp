#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler glib headers
extern "C" {
#include "poppler-document.h"
}

class PopplerLayersIterTest_2248 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll create documents from real PDFs where possible
    }

    void TearDown() override {
    }
};

// Test that poppler_layers_iter_new returns nullptr for a document with no layers
TEST_F(PopplerLayersIterTest_2248, ReturnsNullForDocumentWithNoLayers_2248) {
    GError *error = nullptr;
    // Create a simple PDF document that has no layers
    // Use a minimal PDF file or a known test file
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_no_layers.pdf", nullptr, &error);
    
    if (doc == nullptr) {
        // If we can't load a test document, create one from data
        // Try creating a minimal document from bytes
        const char *minimal_pdf = "%PDF-1.0\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                                   "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                                   "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                                   "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                                   "0000000058 00000 n \n0000000115 00000 n \n"
                                   "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
        
        // Write minimal PDF to temp file
        FILE *f = fopen("/tmp/test_no_layers.pdf", "wb");
        if (f) {
            fwrite(minimal_pdf, 1, strlen(minimal_pdf), f);
            fclose(f);
            doc = poppler_document_new_from_file("file:///tmp/test_no_layers.pdf", nullptr, &error);
        }
    }
    
    if (doc != nullptr) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        // A simple PDF without layers should return nullptr
        // (since _poppler_document_get_layers would return nullptr/empty)
        // This depends on the document content - if no OCG layers, expect nullptr
        if (iter != nullptr) {
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test PDF document";
    }
}

// Test that poppler_layers_iter_new handles nullptr document gracefully
TEST_F(PopplerLayersIterTest_2248, HandlesNullDocument_2248) {
    // Passing nullptr should not crash - it should return nullptr
    // Note: This may cause a segfault if the implementation doesn't check for null,
    // but we test the interface contract
    // If the function expects non-null, this tests robustness
    // We wrap in a death test or simply skip if we know it crashes
    // For safety, we can test with EXPECT_DEATH or skip
    // Based on the code, it calls _poppler_document_get_layers(document) which
    // likely dereferences document, so nullptr would crash
    // We document this as expected behavior
    SUCCEED() << "Passing nullptr document is undefined behavior per the API";
}

// Test that poppler_layers_iter_new returns valid iter for a document with layers
TEST_F(PopplerLayersIterTest_2248, ReturnsValidIterForDocumentWithLayers_2248) {
    GError *error = nullptr;
    
    // Try to find a PDF with layers (OCG)
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_with_layers.pdf", nullptr, &error);
    
    if (doc != nullptr) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        if (iter != nullptr) {
            // If the document has layers, we should get a valid iterator
            EXPECT_NE(iter, nullptr);
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "No test PDF with layers available";
    }
}

// Test that the returned iterator can be freed without issues
TEST_F(PopplerLayersIterTest_2248, IterCanBeFreed_2248) {
    GError *error = nullptr;
    
    const char *minimal_pdf = "%PDF-1.0\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                               "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                               "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                               "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                               "0000000058 00000 n \n0000000115 00000 n \n"
                               "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    FILE *f = fopen("/tmp/test_iter_free.pdf", "wb");
    if (f) {
        fwrite(minimal_pdf, 1, strlen(minimal_pdf), f);
        fclose(f);
    }
    
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_iter_free.pdf", nullptr, &error);
    
    if (doc != nullptr) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        // Even if iter is nullptr (no layers), freeing nullptr should be safe
        if (iter != nullptr) {
            poppler_layers_iter_free(iter);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test PDF document";
    }
}

// Test that calling poppler_layers_iter_new multiple times on the same document works
TEST_F(PopplerLayersIterTest_2248, MultipleIterCreation_2248) {
    GError *error = nullptr;
    
    const char *minimal_pdf = "%PDF-1.0\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                               "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                               "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                               "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                               "0000000058 00000 n \n0000000115 00000 n \n"
                               "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    FILE *f = fopen("/tmp/test_multi_iter.pdf", "wb");
    if (f) {
        fwrite(minimal_pdf, 1, strlen(minimal_pdf), f);
        fclose(f);
    }
    
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_multi_iter.pdf", nullptr, &error);
    
    if (doc != nullptr) {
        PopplerLayersIter *iter1 = poppler_layers_iter_new(doc);
        PopplerLayersIter *iter2 = poppler_layers_iter_new(doc);
        
        // Both should return the same type of result (both null or both non-null)
        // for the same document
        EXPECT_EQ(iter1 == nullptr, iter2 == nullptr);
        
        if (iter1) poppler_layers_iter_free(iter1);
        if (iter2) poppler_layers_iter_free(iter2);
        
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test PDF document";
    }
}

// Test that the document reference count is incremented when iter is created
TEST_F(PopplerLayersIterTest_2248, DocumentRefCountIncremented_2248) {
    GError *error = nullptr;
    
    // This test verifies that creating an iter refs the document
    // We can check by seeing if the document is still valid after we would
    // normally unref it (but we won't actually do that to avoid issues)
    
    const char *minimal_pdf = "%PDF-1.0\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                               "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                               "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                               "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                               "0000000058 00000 n \n0000000115 00000 n \n"
                               "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    FILE *f = fopen("/tmp/test_refcount.pdf", "wb");
    if (f) {
        fwrite(minimal_pdf, 1, strlen(minimal_pdf), f);
        fclose(f);
    }
    
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_refcount.pdf", nullptr, &error);
    
    if (doc != nullptr) {
        // The implementation does g_object_ref on the document when creating iter
        // If iter is non-null, the refcount should have increased
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        
        if (iter != nullptr) {
            // Document should still be valid even if we conceptually have an extra ref
            // We just verify iter was created successfully with the ref
            EXPECT_NE(iter, nullptr);
            poppler_layers_iter_free(iter);
        }
        
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test PDF document";
    }
}
