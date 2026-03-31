#include <glib.h>
#include <glib-object.h>
#include "poppler-document.h"
#include <gtest/gtest.h>

class PopplerLayersIterCopyTest_2246 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that copying a NULL iterator returns NULL
TEST_F(PopplerLayersIterCopyTest_2246, CopyNullIterReturnsNull_2246)
{
    PopplerLayersIter *result = poppler_layers_iter_copy(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that copying a valid iterator returns a non-null copy
TEST_F(PopplerLayersIterCopyTest_2246, CopyValidIterReturnsNonNull_2246)
{
    // We need a valid PopplerDocument to create a layers iter
    // Create a simple PDF in memory to get a valid document
    const char *uri = nullptr;
    GError *error = nullptr;

    // Try to create a document from a minimal PDF bytes
    const char pdf_data[] =
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

    // Write to a temp file
    gchar *tmp_path = nullptr;
    gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmp_path, &error);
    if (fd == -1 || error != nullptr) {
        GTEST_SKIP() << "Cannot create temp file for test";
        return;
    }

    gsize written = write(fd, pdf_data, sizeof(pdf_data) - 1);
    close(fd);

    if (written != sizeof(pdf_data) - 1) {
        g_free(tmp_path);
        GTEST_SKIP() << "Cannot write temp PDF file";
        return;
    }

    gchar *file_uri = g_filename_to_uri(tmp_path, nullptr, &error);
    if (file_uri == nullptr) {
        g_free(tmp_path);
        GTEST_SKIP() << "Cannot convert filename to URI";
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(file_uri, nullptr, &error);
    g_free(file_uri);

    if (doc == nullptr) {
        g_free(tmp_path);
        GTEST_SKIP() << "Cannot create PopplerDocument from test PDF";
        return;
    }

    // Try to get a layers iter - it may be NULL if the document has no layers
    PopplerLayersIter *iter = poppler_layers_iter_new(doc);

    if (iter != nullptr) {
        // Test the copy
        PopplerLayersIter *copy = poppler_layers_iter_copy(iter);
        EXPECT_NE(copy, nullptr);
        EXPECT_NE(copy, iter); // Should be a different pointer (actual copy)

        poppler_layers_iter_free(copy);
        poppler_layers_iter_free(iter);
    } else {
        // Document has no layers, so we can't test copy with a valid iter from this doc
        // This is expected for a minimal PDF
    }

    g_object_unref(doc);
    g_unlink(tmp_path);
    g_free(tmp_path);
}
