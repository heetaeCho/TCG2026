#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <poppler.h>
}

#include <cstdlib>
#include <cstring>
#include <string>

class PopplerIndexIterGetChildTest_2214 : public ::testing::Test {
protected:
    void SetUp() override {
        document = nullptr;
        iter = nullptr;
    }

    void TearDown() override {
        if (iter) {
            poppler_index_iter_free(iter);
            iter = nullptr;
        }
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }

    PopplerDocument *document;
    PopplerIndexIter *iter;
};

// Test that passing NULL parent returns NULL
TEST_F(PopplerIndexIterGetChildTest_2214, NullParentReturnsNull_2214) {
    PopplerIndexIter *child = poppler_index_iter_get_child(nullptr);
    EXPECT_EQ(child, nullptr);
}

// Test with a real PDF document that has no index/outline
TEST_F(PopplerIndexIterGetChildTest_2214, DocumentWithNoIndexReturnsNullIter_2214) {
    // Create a minimal PDF in memory that has no outline
    const char *pdf_content =
        "%PDF-1.4\n"
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
    gsize len = strlen(pdf_content);
    GBytes *bytes = g_bytes_new_static(pdf_content, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    document = poppler_document_new_from_stream(stream, len, nullptr, &error);
    g_object_unref(stream);
    g_bytes_unref(bytes);

    if (document == nullptr) {
        // If we can't create the document from this minimal PDF, skip
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    iter = poppler_index_iter_new(document);
    // A document without an outline should return NULL iter
    EXPECT_EQ(iter, nullptr);
}

// Test loading a PDF with an outline and getting children
TEST_F(PopplerIndexIterGetChildTest_2214, GetChildFromValidIterWithNoChildren_2214) {
    // Try to load a test PDF file if available
    const char *test_pdf_path = g_getenv("TEST_PDF_WITH_OUTLINE");
    if (test_pdf_path == nullptr) {
        GTEST_SKIP() << "TEST_PDF_WITH_OUTLINE env var not set; skipping real PDF test";
    }

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not convert path to URI";
    }

    document = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!document) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not open test PDF";
    }

    iter = poppler_index_iter_new(document);
    if (!iter) {
        GTEST_SKIP() << "Test PDF has no outline";
    }

    // Try getting child of first item - may or may not have children
    PopplerIndexIter *child = poppler_index_iter_get_child(iter);
    // We just verify it doesn't crash; child may be null if no sub-items
    if (child) {
        poppler_index_iter_free(child);
    }
}

// Test that poppler_index_iter_get_child with null is safe to call multiple times
TEST_F(PopplerIndexIterGetChildTest_2214, NullParentMultipleCalls_2214) {
    for (int i = 0; i < 10; i++) {
        PopplerIndexIter *child = poppler_index_iter_get_child(nullptr);
        EXPECT_EQ(child, nullptr);
    }
}
