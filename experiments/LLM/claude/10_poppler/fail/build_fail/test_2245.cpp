#include <gtest/gtest.h>
#include <glib.h>

// Include poppler glib headers
extern "C" {
#include <poppler.h>
}

#include <cstring>
#include <string>

class PopplerDocumentLayersTest_2245 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        // Try to create a document from a simple PDF for testing
        // We use a minimal in-memory PDF approach or file-based
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerDocument* loadTestDocument(const char* path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        PopplerDocument *d = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) g_error_free(error);
        return d;
    }
};

// Test that creating and destroying a document with no layers doesn't crash
// This exercises the layers_free path with nullptr layers
TEST_F(PopplerDocumentLayersTest_2245, DestroyDocumentWithNullLayers_2245) {
    // Create a minimal PDF in memory (no layers)
    const char *minimal_pdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (doc == nullptr) {
        // If we can't create the document, skip
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create minimal PDF document";
        return;
    }

    // Getting layers on a document without layers should work without crash
    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    // For a simple PDF with no layers, iter should be NULL
    EXPECT_EQ(iter, nullptr);

    // Unreffing the document triggers layers_free internally
    g_object_unref(doc);
    doc = nullptr;
    // If we reach here without crash, the test passes
    SUCCEED();
}

// Test that repeated calls to get layers iter are safe
TEST_F(PopplerDocumentLayersTest_2245, RepeatedLayersIterCreation_2245) {
    const char *minimal_pdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document";
        return;
    }

    // Multiple calls should be safe - exercises internal caching/freeing
    for (int i = 0; i < 5; i++) {
        PopplerLayersIter *iter = poppler_layers_iter_new(doc);
        if (iter) {
            poppler_layers_iter_free(iter);
        }
    }
    SUCCEED();
}

// Test document finalization with no prior layer access
TEST_F(PopplerDocumentLayersTest_2245, DocumentFinalizeWithoutLayerAccess_2245) {
    const char *minimal_pdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    PopplerDocument *local_doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (!local_doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document";
        return;
    }

    // Destroy without ever accessing layers - exercises the G_UNLIKELY(!document->layers) path
    g_object_unref(local_doc);
    SUCCEED();
}

// Test that document with no layers returns null layers iter
TEST_F(PopplerDocumentLayersTest_2245, NoLayersDocumentReturnsNullIter_2245) {
    const char *minimal_pdf = 
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(minimal_pdf, strlen(minimal_pdf));
    doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create PDF document";
        return;
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    EXPECT_EQ(iter, nullptr);
}
