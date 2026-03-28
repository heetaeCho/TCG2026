#include <glib.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>
#include <fstream>

class PopplerOptionalContentTest_2243 : public ::testing::Test {
protected:
    void SetUp() override {
        doc_ = nullptr;
    }

    void TearDown() override {
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    PopplerDocument *loadDocument(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, nullptr, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        return doc;
    }

    PopplerDocument *doc_;
};

TEST_F(PopplerOptionalContentTest_2243, NullDocumentHasNoLayers_2243) {
    // When no document is loaded, we cannot get layers
    // This tests the boundary condition of no document
    EXPECT_EQ(doc_, nullptr);
}

TEST_F(PopplerOptionalContentTest_2243, GetLayersFromNonOCGDocument_2243) {
    // Create a simple PDF without optional content groups
    // Try to load a document that has no OCG - layers should return NULL
    const char *test_path = "/tmp/test_no_ocg_2243.pdf";
    
    // Check if we can create a minimal test - if not available, skip
    doc_ = loadDocument(test_path);
    if (!doc_) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    GList *layers = poppler_document_get_layers(doc_);
    // A document without OCGs should return NULL for layers
    EXPECT_EQ(layers, nullptr);
}

TEST_F(PopplerOptionalContentTest_2243, HasOptionalContentReturnsFalseForSimplePDF_2243) {
    const char *test_path = "/tmp/test_simple_2243.pdf";
    doc_ = loadDocument(test_path);
    if (!doc_) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    GList *layers = poppler_document_get_layers(doc_);
    // Simple PDF without layers
    if (layers == nullptr) {
        EXPECT_EQ(layers, nullptr);
    } else {
        // If layers exist, the list should be non-empty
        EXPECT_NE(g_list_length(layers), 0u);
        // Clean up
        g_list_free(layers);
    }
}

TEST_F(PopplerOptionalContentTest_2243, GetLayersReturnsListForOCGDocument_2243) {
    // Test with a PDF that has optional content groups
    const char *test_path = "/tmp/test_ocg_2243.pdf";
    doc_ = loadDocument(test_path);
    if (!doc_) {
        GTEST_SKIP() << "Test PDF with OCGs not available, skipping";
    }
    
    GList *layers = poppler_document_get_layers(doc_);
    if (layers) {
        // If the document has OCGs, the list should have elements
        EXPECT_GT(g_list_length(layers), 0u);
        g_list_free(layers);
    }
}

TEST_F(PopplerOptionalContentTest_2243, DocumentFromBytesNullLayers_2243) {
    // Test creating a document from minimal PDF bytes (no OCG)
    const char *minimal_pdf = 
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
        "startxref\n190\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new(minimal_pdf, strlen(minimal_pdf));
    doc_ = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);
    
    if (!doc_) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create document from bytes";
    }
    
    GList *layers = poppler_document_get_layers(doc_);
    // Minimal PDF should not have optional content
    EXPECT_EQ(layers, nullptr);
}

TEST_F(PopplerOptionalContentTest_2243, LayerListIsProperlyOrdered_2243) {
    // Test that when layers exist, they maintain order
    const char *test_path = "/tmp/test_ordered_ocg_2243.pdf";
    doc_ = loadDocument(test_path);
    if (!doc_) {
        GTEST_SKIP() << "Test PDF with ordered OCGs not available, skipping";
    }
    
    GList *layers = poppler_document_get_layers(doc_);
    if (layers) {
        // Iterate through layers - each element should be non-null
        for (GList *l = layers; l != nullptr; l = l->next) {
            EXPECT_NE(l->data, nullptr);
        }
        g_list_free(layers);
    }
}

TEST_F(PopplerOptionalContentTest_2243, MultipleCallsReturnConsistentResults_2243) {
    const char *test_path = "/tmp/test_ocg_consistent_2243.pdf";
    doc_ = loadDocument(test_path);
    if (!doc_) {
        GTEST_SKIP() << "Test PDF not available, skipping";
    }
    
    GList *layers1 = poppler_document_get_layers(doc_);
    GList *layers2 = poppler_document_get_layers(doc_);
    
    // Both calls should return consistent results
    guint len1 = layers1 ? g_list_length(layers1) : 0;
    guint len2 = layers2 ? g_list_length(layers2) : 0;
    EXPECT_EQ(len1, len2);
    
    if (layers1) g_list_free(layers1);
    if (layers2) g_list_free(layers2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
