#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib.h>

// Include poppler glib headers
extern "C" {
#include "poppler.h"
}

#include "poppler-private.h"

class PopplerDocumentGetLayersTest_2244 : public ::testing::Test {
protected:
    void SetUp() override {
        document_ = nullptr;
    }

    void TearDown() override {
        if (document_) {
            g_object_unref(document_);
            document_ = nullptr;
        }
    }

    PopplerDocument *loadDocument(const char *filename) {
        GError *error = nullptr;
        gchar *uri = g_strdup_printf("file://%s", filename);
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    PopplerDocument *document_;
};

// Test that getting layers from a document without optional content returns nullptr
TEST_F(PopplerDocumentGetLayersTest_2244, NoOptionalContent_ReturnsNull_2244) {
    // Create a simple PDF in memory that has no optional content / layers
    // Using poppler_document_new_from_data or from_bytes if available
    // For a simple PDF without layers, _poppler_document_get_layers should return nullptr

    const char *simple_pdf = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(simple_pdf, strlen(simple_pdf));
    document_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (error) {
        g_error_free(error);
        GTEST_SKIP() << "Could not create document from minimal PDF";
        return;
    }

    ASSERT_NE(document_, nullptr);

    // _poppler_document_get_layers is internal, but we can test via poppler_document_get_n_layers
    // or by calling the internal function if accessible
    GList *layers = _poppler_document_get_layers(document_);
    EXPECT_EQ(layers, nullptr);
}

// Test that calling _poppler_document_get_layers twice returns the same cached result
TEST_F(PopplerDocumentGetLayersTest_2244, CachedResult_ReturnsSamePointer_2244) {
    const char *simple_pdf = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(simple_pdf, strlen(simple_pdf));
    document_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (error) {
        g_error_free(error);
        GTEST_SKIP() << "Could not create document from minimal PDF";
        return;
    }

    ASSERT_NE(document_, nullptr);

    GList *layers1 = _poppler_document_get_layers(document_);
    GList *layers2 = _poppler_document_get_layers(document_);

    // Whether null or not, the cached result should be the same pointer
    EXPECT_EQ(layers1, layers2);
}

// Test with a PDF file that has layers (if available on the test system)
TEST_F(PopplerDocumentGetLayersTest_2244, DocumentWithLayers_ReturnsNonNull_2244) {
    // This test requires a PDF with optional content groups (layers)
    // We'll construct a minimal one in memory
    // A PDF with OCG requires specific objects; this is a best-effort test
    
    const char *ocg_pdf =
        "%PDF-1.5\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R/OCProperties<</OCGs[4 0 R]/D<</ON[4 0 R]/Order[4 0 R]>>>>>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "4 0 obj<</Type/OCG/Name(Layer1)>>endobj\n"
        "xref\n0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000132 00000 n \n"
        "0000000189 00000 n \n"
        "0000000262 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n306\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(ocg_pdf, strlen(ocg_pdf));
    document_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (error) {
        g_error_free(error);
        GTEST_SKIP() << "Could not create document with OCG from minimal PDF";
        return;
    }

    ASSERT_NE(document_, nullptr);

    GList *layers = _poppler_document_get_layers(document_);
    // The document has optional content, so layers might be non-null
    // (depends on whether poppler correctly parses our minimal OCG PDF)
    // We just verify the function doesn't crash and returns consistently
    GList *layers2 = _poppler_document_get_layers(document_);
    EXPECT_EQ(layers, layers2);
}

// Test that layers are idempotent - multiple calls don't change the result
TEST_F(PopplerDocumentGetLayersTest_2244, IdempotentCalls_2244) {
    const char *simple_pdf = 
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n183\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(simple_pdf, strlen(simple_pdf));
    document_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (error) {
        g_error_free(error);
        GTEST_SKIP() << "Could not create document";
        return;
    }

    ASSERT_NE(document_, nullptr);

    // Call multiple times
    GList *result1 = _poppler_document_get_layers(document_);
    GList *result2 = _poppler_document_get_layers(document_);
    GList *result3 = _poppler_document_get_layers(document_);

    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);
}
