#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler-document.h"

class PopplerFontInfoTest_2232 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that PopplerFontInfo type is registered and can be queried
TEST_F(PopplerFontInfoTest_2232, TypeIsRegistered_2232)
{
    GType type = POPPLER_TYPE_FONT_INFO;
    EXPECT_NE(type, G_TYPE_INVALID);
}

// Test creating a PopplerFontInfo object with a valid PopplerDocument
TEST_F(PopplerFontInfoTest_2232, CreateWithValidDocument_2232)
{
    GError *error = nullptr;
    // We need a valid PDF document to create a PopplerFontInfo
    // Create a minimal PDF in memory
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new_static(pdf_data, len);

    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerFontInfo *font_info = poppler_font_info_new(doc);
        EXPECT_NE(font_info, nullptr);
        EXPECT_TRUE(POPPLER_IS_FONT_INFO(font_info));

        g_object_unref(font_info);
        g_object_unref(doc);
    }
    // Cleanup even if doc creation failed (some environments may not support this)
    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}

// Test that PopplerFontInfo can be properly unreferenced (finalize path)
TEST_F(PopplerFontInfoTest_2232, UnrefDoesNotCrash_2232)
{
    GError *error = nullptr;
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new_static(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerFontInfo *font_info = poppler_font_info_new(doc);
        ASSERT_NE(font_info, nullptr);

        // This exercises the finalize path (poppler_font_info_finalize)
        g_object_unref(font_info);
        // If we get here without crash, finalize worked
        SUCCEED();

        g_object_unref(doc);
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}

// Test that PopplerFontInfo is a GObject
TEST_F(PopplerFontInfoTest_2232, IsGObject_2232)
{
    GError *error = nullptr;
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new_static(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerFontInfo *font_info = poppler_font_info_new(doc);
        ASSERT_NE(font_info, nullptr);
        EXPECT_TRUE(G_IS_OBJECT(font_info));

        g_object_unref(font_info);
        g_object_unref(doc);
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}

// Test scanning fonts on a simple document
TEST_F(PopplerFontInfoTest_2232, ScanReturnsFontsIterator_2232)
{
    GError *error = nullptr;
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new_static(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerFontInfo *font_info = poppler_font_info_new(doc);
        ASSERT_NE(font_info, nullptr);

        PopplerFontsIter *iter = nullptr;
        int n_pages = poppler_document_get_n_pages(doc);
        // Scan all pages
        gboolean result = poppler_font_info_scan(font_info, n_pages, &iter);
        // Result can be TRUE or FALSE depending on whether there are more pages
        // For a 1-page doc with no fonts, iter may be NULL
        // We just verify the call doesn't crash
        (void)result;

        if (iter != nullptr) {
            poppler_fonts_iter_free(iter);
        }

        g_object_unref(font_info);
        g_object_unref(doc);
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}

// Test that ref/unref works correctly
TEST_F(PopplerFontInfoTest_2232, RefUnrefWorks_2232)
{
    GError *error = nullptr;
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new_static(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerFontInfo *font_info = poppler_font_info_new(doc);
        ASSERT_NE(font_info, nullptr);

        // Add a reference
        g_object_ref(font_info);
        // Unref once (should still be alive)
        g_object_unref(font_info);
        // Verify it's still valid
        EXPECT_TRUE(POPPLER_IS_FONT_INFO(font_info));
        // Final unref triggers finalize
        g_object_unref(font_info);

        g_object_unref(doc);
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}

// Test free function on font info
TEST_F(PopplerFontInfoTest_2232, FreeFontInfo_2232)
{
    GError *error = nullptr;
    const char *pdf_data =
        "%PDF-1.0\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n190\n%%EOF\n";

    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new_static(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        PopplerFontInfo *font_info = poppler_font_info_new(doc);
        ASSERT_NE(font_info, nullptr);

        poppler_font_info_free(font_info);
        // Should not crash - the free function should clean up properly
        SUCCEED();

        g_object_unref(doc);
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}
