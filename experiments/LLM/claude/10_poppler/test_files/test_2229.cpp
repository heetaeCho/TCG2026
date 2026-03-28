#include <gtest/gtest.h>
#include <glib.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler-document.h"
}

class PopplerFontsIterTest_2229 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that copying a NULL iterator returns NULL
TEST_F(PopplerFontsIterTest_2229, CopyNullIterReturnsNull_2229)
{
    PopplerFontsIter *result = poppler_fonts_iter_copy(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that copying a valid iterator from a real document works
TEST_F(PopplerFontsIterTest_2229, CopyValidIterFromDocument_2229)
{
    // Create a minimal PDF in memory to get a valid PopplerDocument
    // We need a document that has fonts to iterate over
    const char *uri = nullptr;
    GError *error = nullptr;

    // Try to create a simple document from a data buffer
    // Minimal PDF content
    const char *pdf_content =
        "%PDF-1.0\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Contents 4 0 R /Resources << /Font << /F1 5 0 R >> >> >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 44 >>\n"
        "stream\n"
        "BT /F1 12 Tf 100 700 Td (Hello) Tj ET\n"
        "endstream\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000298 00000 n \n"
        "0000000392 00000 n \n"
        "trailer\n"
        "<< /Size 6 /Root 1 0 R >>\n"
        "startxref\n"
        "475\n"
        "%%EOF\n";

    // Write to a temp file
    gchar *tmp_filename = nullptr;
    gint fd = g_file_open_tmp("test_poppler_XXXXXX.pdf", &tmp_filename, &error);
    if (fd == -1 || error != nullptr) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create temp file";
        return;
    }

    gsize len = strlen(pdf_content);
    write(fd, pdf_content, len);
    close(fd);

    gchar *file_uri = g_filename_to_uri(tmp_filename, nullptr, &error);
    if (error != nullptr) {
        g_error_free(error);
        g_free(tmp_filename);
        GTEST_SKIP() << "Could not create URI";
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(file_uri, nullptr, &error);
    g_free(file_uri);

    if (doc == nullptr) {
        if (error) {
            g_error_free(error);
        }
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP() << "Could not open test PDF document";
        return;
    }

    // Scan for fonts
    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    int n_pages = poppler_document_get_n_pages(doc);

    gboolean has_more = poppler_font_info_scan(font_info, n_pages, &iter);

    if (iter != nullptr) {
        // Test copying the iterator
        PopplerFontsIter *copied_iter = poppler_fonts_iter_copy(iter);
        ASSERT_NE(copied_iter, nullptr);

        // The copied iterator should be a different pointer
        EXPECT_NE(copied_iter, iter);

        // Verify that the font name from original and copy match
        const char *orig_name = poppler_fonts_iter_get_name(iter);
        const char *copy_name = poppler_fonts_iter_get_name(copied_iter);

        if (orig_name != nullptr && copy_name != nullptr) {
            EXPECT_STREQ(orig_name, copy_name);
        } else {
            // Both should be null or both non-null
            EXPECT_EQ(orig_name == nullptr, copy_name == nullptr);
        }

        // Verify font type matches
        PopplerFontType orig_type = poppler_fonts_iter_get_font_type(iter);
        PopplerFontType copy_type = poppler_fonts_iter_get_font_type(copied_iter);
        EXPECT_EQ(orig_type, copy_type);

        // Verify embedded status matches
        gboolean orig_embedded = poppler_fonts_iter_is_embedded(iter);
        gboolean copy_embedded = poppler_fonts_iter_is_embedded(copied_iter);
        EXPECT_EQ(orig_embedded, copy_embedded);

        // Verify subset status matches
        gboolean orig_subset = poppler_fonts_iter_is_subset(iter);
        gboolean copy_subset = poppler_fonts_iter_is_subset(copied_iter);
        EXPECT_EQ(orig_subset, copy_subset);

        poppler_fonts_iter_free(copied_iter);
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
    g_object_unref(doc);
    g_unlink(tmp_filename);
    g_free(tmp_filename);
}

// Test that copying an iterator preserves iteration state
TEST_F(PopplerFontsIterTest_2229, CopiedIterPreservesState_2229)
{
    const char *pdf_content =
        "%PDF-1.0\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Contents 4 0 R /Resources << /Font << /F1 5 0 R /F2 6 0 R >> >> >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 74 >>\n"
        "stream\n"
        "BT /F1 12 Tf 100 700 Td (Hello) Tj /F2 12 Tf 100 680 Td (World) Tj ET\n"
        "endstream\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n"
        "6 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Courier >>\n"
        "endobj\n"
        "xref\n"
        "0 7\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000316 00000 n \n"
        "0000000440 00000 n \n"
        "0000000523 00000 n \n"
        "trailer\n"
        "<< /Size 7 /Root 1 0 R >>\n"
        "startxref\n"
        "603\n"
        "%%EOF\n";

    GError *error = nullptr;
    gchar *tmp_filename = nullptr;
    gint fd = g_file_open_tmp("test_poppler2_XXXXXX.pdf", &tmp_filename, &error);
    if (fd == -1) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create temp file";
        return;
    }

    write(fd, pdf_content, strlen(pdf_content));
    close(fd);

    gchar *file_uri = g_filename_to_uri(tmp_filename, nullptr, &error);
    if (!file_uri) {
        if (error) {
            g_error_free(error);
        }
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP() << "Could not create URI";
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(file_uri, nullptr, &error);
    g_free(file_uri);

    if (!doc) {
        if (error) {
            g_error_free(error);
        }
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP() << "Could not open test PDF";
        return;
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    int n_pages = poppler_document_get_n_pages(doc);

    poppler_font_info_scan(font_info, n_pages, &iter);

    if (iter != nullptr) {
        // Advance the iterator if possible
        if (poppler_fonts_iter_next(iter)) {
            // Now copy - the copy should be at the same position
            PopplerFontsIter *copied = poppler_fonts_iter_copy(iter);
            ASSERT_NE(copied, nullptr);

            const char *orig_name = poppler_fonts_iter_get_name(iter);
            const char *copy_name = poppler_fonts_iter_get_name(copied);

            if (orig_name && copy_name) {
                EXPECT_STREQ(orig_name, copy_name);
            }

            poppler_fonts_iter_free(copied);
        }

        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
    g_object_unref(doc);
    g_unlink(tmp_filename);
    g_free(tmp_filename);
}

// Test that modifying the original after copy doesn't affect the copy
TEST_F(PopplerFontsIterTest_2229, CopyIsIndependent_2229)
{
    const char *pdf_content =
        "%PDF-1.0\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
        "/Contents 4 0 R /Resources << /Font << /F1 5 0 R /F2 6 0 R >> >> >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Length 74 >>\n"
        "stream\n"
        "BT /F1 12 Tf 100 700 Td (Hello) Tj /F2 12 Tf 100 680 Td (World) Tj ET\n"
        "endstream\n"
        "endobj\n"
        "5 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>\n"
        "endobj\n"
        "6 0 obj\n"
        "<< /Type /Font /Subtype /Type1 /BaseFont /Courier >>\n"
        "endobj\n"
        "xref\n"
        "0 7\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000316 00000 n \n"
        "0000000440 00000 n \n"
        "0000000523 00000 n \n"
        "trailer\n"
        "<< /Size 7 /Root 1 0 R >>\n"
        "startxref\n"
        "603\n"
        "%%EOF\n";

    GError *error = nullptr;
    gchar *tmp_filename = nullptr;
    gint fd = g_file_open_tmp("test_poppler3_XXXXXX.pdf", &tmp_filename, &error);
    if (fd == -1) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create temp file";
        return;
    }

    write(fd, pdf_content, strlen(pdf_content));
    close(fd);

    gchar *file_uri = g_filename_to_uri(tmp_filename, nullptr, &error);
    if (!file_uri) {
        if (error) {
            g_error_free(error);
        }
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP();
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(file_uri, nullptr, &error);
    g_free(file_uri);

    if (!doc) {
        if (error) {
            g_error_free(error);
        }
        g_unlink(tmp_filename);
        g_free(tmp_filename);
        GTEST_SKIP();
        return;
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    int n_pages = poppler_document_get_n_pages(doc);

    poppler_font_info_scan(font_info, n_pages, &iter);

    if (iter != nullptr) {
        // Save the name at current position
        const char *first_name = poppler_fonts_iter_get_name(iter);
        gchar *saved_name = first_name ? g_strdup(first_name) : nullptr;

        // Copy the iterator
        PopplerFontsIter *copied = poppler_fonts_iter_copy(iter);
        ASSERT_NE(copied, nullptr);

        // Advance the original
        poppler_fonts_iter_next(iter);

        // The copy should still point to the original position
        const char *copy_name = poppler_fonts_iter_get_name(copied);
        if (saved_name && copy_name) {
            EXPECT_STREQ(saved_name, copy_name);
        }

        g_free(saved_name);
        poppler_fonts_iter_free(copied);
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
    g_object_unref(doc);
    g_unlink(tmp_filename);
    g_free(tmp_filename);
}
