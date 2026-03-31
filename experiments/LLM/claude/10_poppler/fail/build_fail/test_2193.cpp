#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>
#include "poppler-document.h"
}

class PopplerDocumentSignaturesTest_2193 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL document returns 0
TEST_F(PopplerDocumentSignaturesTest_2193, NullDocumentReturnsZero_2193)
{
    gint result = poppler_document_get_n_signatures(nullptr);
    EXPECT_EQ(result, 0);
}

// Test with a valid PDF that has no signatures
TEST_F(PopplerDocumentSignaturesTest_2193, NoSignaturesDocument_2193)
{
    GError *error = nullptr;
    // Create a simple PDF document with no signature fields
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_no_sig.pdf", nullptr, &error);
    if (doc == nullptr) {
        // If we can't load a test file, skip
        GTEST_SKIP() << "Could not load test PDF without signatures";
    }
    gint n_sigs = poppler_document_get_n_signatures(doc);
    EXPECT_GE(n_sigs, 0);
    g_object_unref(doc);
}

// Test that the function returns non-negative for any valid document
TEST_F(PopplerDocumentSignaturesTest_2193, ValidDocumentReturnsNonNegative_2193)
{
    GError *error = nullptr;
    // Attempt to create a minimal PDF in memory
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

    gsize len = strlen(minimal_pdf);
    GBytes *bytes = g_bytes_new_static(minimal_pdf, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    PopplerDocument *doc = poppler_document_new_from_stream(
        stream, (goffset)len, nullptr, nullptr, &error);

    if (doc == nullptr) {
        g_clear_error(&error);
        g_object_unref(stream);
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not create document from minimal PDF stream";
    }

    gint n_sigs = poppler_document_get_n_signatures(doc);
    EXPECT_GE(n_sigs, 0);
    EXPECT_EQ(n_sigs, 0); // Minimal PDF has no signature fields

    g_object_unref(doc);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test that passing an invalid GObject (not a PopplerDocument) returns 0 due to g_return_val_if_fail
TEST_F(PopplerDocumentSignaturesTest_2193, InvalidGObjectReturnsZero_2193)
{
    // Suppress g_return_val_if_fail warnings for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");

    // Pass a non-PopplerDocument GObject - this should trigger the g_return_val_if_fail guard
    GObject *not_a_document = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    gint result = poppler_document_get_n_signatures((const PopplerDocument *)not_a_document);
    EXPECT_EQ(result, 0);

    g_test_assert_expected_messages();
    g_object_unref(not_a_document);
}
