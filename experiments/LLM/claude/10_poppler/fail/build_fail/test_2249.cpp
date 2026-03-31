#include <glib.h>
#include <glib-object.h>
#include "poppler-document.h"
#include <gtest/gtest.h>

class PopplerLayersIterTest_2249 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL parent returns NULL
TEST_F(PopplerLayersIterTest_2249, NullParentReturnsNull_2249)
{
    PopplerLayersIter *result = poppler_layers_iter_get_child(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with a real document that has layers
// We need a PDF with layers to fully test, but we can at least verify the null parent case
// and test with documents that have no layers

class PopplerDocumentLayersTest_2249 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override
    {
        // Try to create a simple document - if no test file available, skip
        GError *error = nullptr;
        // Create a minimal PDF in memory to test with
        // Most simple PDFs won't have layers, so we test the no-layers path
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that get_child with null returns null (repeated for clarity with different fixture)
TEST_F(PopplerDocumentLayersTest_2249, GetChildNullParent_2249)
{
    PopplerLayersIter *child = poppler_layers_iter_get_child(nullptr);
    EXPECT_EQ(child, nullptr);
}

// Test poppler_layers_iter_new with null document
TEST_F(PopplerDocumentLayersTest_2249, NewIterNullDocument_2249)
{
    PopplerLayersIter *iter = poppler_layers_iter_new(nullptr);
    EXPECT_EQ(iter, nullptr);
}

// Test that a document without layers returns null iter
TEST_F(PopplerDocumentLayersTest_2249, NoLayersDocumentReturnsNullIter_2249)
{
    // Create a simple PDF without layers
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
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_content);
    GBytes *bytes = g_bytes_new(pdf_content, len);

    // Try creating a temp file
    gchar *tmpfile = nullptr;
    GError *error = nullptr;
    gint fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmpfile, &error);
    if (fd == -1) {
        if (error) {
            g_error_free(error);
        }
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Cannot create temp file";
        return;
    }

    write(fd, pdf_content, len);
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        if (error) {
            g_error_free(error);
        }
        g_free(tmpfile);
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Cannot convert to URI";
        return;
    }

    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);
    g_bytes_unref(bytes);

    if (!doc) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Cannot create document from minimal PDF";
        return;
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    // A simple PDF without OCG (layers) should return NULL
    EXPECT_EQ(iter, nullptr);

    if (iter) {
        poppler_layers_iter_free(iter);
    }
}

// Test that poppler_layers_iter_copy with null returns null
TEST_F(PopplerDocumentLayersTest_2249, CopyNullIter_2249)
{
    PopplerLayersIter *copy = poppler_layers_iter_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

// Test that poppler_layers_iter_free with null doesn't crash
TEST_F(PopplerDocumentLayersTest_2249, FreeNullIter_2249)
{
    // Should not crash
    poppler_layers_iter_free(nullptr);
}
