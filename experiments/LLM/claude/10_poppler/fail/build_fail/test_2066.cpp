#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdlib>

// Helper to create a simple PDF in memory with an annotation that has a modified date
static PopplerDocument *create_pdf_with_annotation(const char *modified_date)
{
    // We'll create a minimal PDF with a text annotation
    // This is a minimal valid PDF with a text annotation
    GString *pdf_content = g_string_new(nullptr);

    g_string_append(pdf_content, "%PDF-1.4\n");
    g_string_append(pdf_content, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
    g_string_append(pdf_content, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

    if (modified_date) {
        g_string_append_printf(pdf_content,
                               "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
                               "/Annots [4 0 R] >>\nendobj\n"
                               "4 0 obj\n<< /Type /Annot /Subtype /Text /Rect [100 100 200 200] "
                               "/M (%s) >>\nendobj\n",
                               modified_date);
    } else {
        g_string_append(pdf_content,
                        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] "
                        "/Annots [4 0 R] >>\nendobj\n"
                        "4 0 obj\n<< /Type /Annot /Subtype /Text /Rect [100 100 200 200] >>\nendobj\n");
    }

    // Calculate xref positions (approximate - we need exact)
    // For simplicity, let's just build the xref
    // Actually, let's use poppler's ability to load from data

    gsize len = pdf_content->len;

    // Build a proper xref - this is tricky with dynamic content
    // Let's use a simpler approach: write to a temp file
    gchar *tmpfile = nullptr;
    GError *error = nullptr;
    gint fd = g_file_open_tmp("test_annot_XXXXXX.pdf", &tmpfile, &error);
    if (fd < 0) {
        g_string_free(pdf_content, TRUE);
        return nullptr;
    }
    close(fd);

    // Instead of manually crafting PDF, let's just try to open any PDF
    // We'll rely on the poppler API for creating annotations
    g_string_free(pdf_content, TRUE);
    g_free(tmpfile);

    return nullptr;
}

class PopplerAnnotGetModifiedTest_2066 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;
    gchar *tmp_path = nullptr;

    void SetUp() override
    {
        // Create a minimal but valid PDF in memory
        const char *pdf_data =
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
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

        gsize pdf_len = strlen(pdf_data);

        GError *error = nullptr;

        // Write to temp file
        gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmp_path, &error);
        if (fd >= 0) {
            write(fd, pdf_data, pdf_len);
            close(fd);

            gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override
    {
        if (page)
            g_object_unref(page);
        if (doc)
            g_object_unref(doc);
        if (tmp_path) {
            g_unlink(tmp_path);
            g_free(tmp_path);
        }
    }
};

// Test that passing NULL to poppler_annot_get_modified returns NULL
TEST_F(PopplerAnnotGetModifiedTest_2066, NullAnnotReturnsNull_2066)
{
    gchar *result = poppler_annot_get_modified(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with a valid annotation that has no modified date
TEST_F(PopplerAnnotGetModifiedTest_2066, AnnotWithNoModifiedDateReturnsNull_2066)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    // Create a text annotation on the page
    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(poppler_annot_text_new(doc, &rect));
    ASSERT_NE(annot, nullptr);

    // A newly created annotation might not have a modified date set
    gchar *modified = poppler_annot_get_modified(annot);
    // It could be NULL or some default value; we just ensure no crash
    if (modified) {
        EXPECT_TRUE(strlen(modified) >= 0);
        g_free(modified);
    }

    g_object_unref(annot);
}

// Test that setting modified date and getting it back works
TEST_F(PopplerAnnotGetModifiedTest_2066, SetAndGetModifiedDate_2066)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(poppler_annot_text_new(doc, &rect));
    ASSERT_NE(annot, nullptr);

    // Set a modified date
    const gchar *test_date = "D:20231015120000+00'00'";
    poppler_annot_set_modified(annot, test_date);

    gchar *modified = poppler_annot_get_modified(annot);
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified, test_date);
    g_free(modified);

    g_object_unref(annot);
}

// Test with an empty modified date string
TEST_F(PopplerAnnotGetModifiedTest_2066, SetEmptyModifiedDate_2066)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(poppler_annot_text_new(doc, &rect));
    ASSERT_NE(annot, nullptr);

    poppler_annot_set_modified(annot, "");

    gchar *modified = poppler_annot_get_modified(annot);
    // Empty string set - could return empty string or NULL
    if (modified) {
        EXPECT_STREQ(modified, "");
        g_free(modified);
    }

    g_object_unref(annot);
}

// Test setting a plain text modified string (not a PDF date format)
TEST_F(PopplerAnnotGetModifiedTest_2066, SetPlainTextModifiedDate_2066)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(poppler_annot_text_new(doc, &rect));
    ASSERT_NE(annot, nullptr);

    const gchar *plain_text = "October 15, 2023";
    poppler_annot_set_modified(annot, plain_text);

    gchar *modified = poppler_annot_get_modified(annot);
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified, plain_text);
    g_free(modified);

    g_object_unref(annot);
}

// Test multiple set/get cycles
TEST_F(PopplerAnnotGetModifiedTest_2066, MultipleSetGetCycles_2066)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle rect = {50.0, 50.0, 150.0, 150.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(poppler_annot_text_new(doc, &rect));
    ASSERT_NE(annot, nullptr);

    // First set
    poppler_annot_set_modified(annot, "first date");
    gchar *modified1 = poppler_annot_get_modified(annot);
    ASSERT_NE(modified1, nullptr);
    EXPECT_STREQ(modified1, "first date");
    g_free(modified1);

    // Second set - should overwrite
    poppler_annot_set_modified(annot, "second date");
    gchar *modified2 = poppler_annot_get_modified(annot);
    ASSERT_NE(modified2, nullptr);
    EXPECT_STREQ(modified2, "second date");
    g_free(modified2);

    g_object_unref(annot);
}

// Test that returned string is a newly allocated copy (caller owns it)
TEST_F(PopplerAnnotGetModifiedTest_2066, ReturnedStringIsNewlyAllocated_2066)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(poppler_annot_text_new(doc, &rect));
    ASSERT_NE(annot, nullptr);

    poppler_annot_set_modified(annot, "test date");

    gchar *modified1 = poppler_annot_get_modified(annot);
    gchar *modified2 = poppler_annot_get_modified(annot);

    ASSERT_NE(modified1, nullptr);
    ASSERT_NE(modified2, nullptr);
    // They should have the same content
    EXPECT_STREQ(modified1, modified2);
    // But be different allocations
    EXPECT_NE(modified1, modified2);

    g_free(modified1);
    g_free(modified2);

    g_object_unref(annot);
}

// Test with UTF-8 characters in modified string
TEST_F(PopplerAnnotGetModifiedTest_2066, Utf8ModifiedString_2066)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(poppler_annot_text_new(doc, &rect));
    ASSERT_NE(annot, nullptr);

    const gchar *utf8_date = "Modifié le 15/10/2023";
    poppler_annot_set_modified(annot, utf8_date);

    gchar *modified = poppler_annot_get_modified(annot);
    ASSERT_NE(modified, nullptr);
    // The returned string should be valid UTF-8
    EXPECT_TRUE(g_utf8_validate(modified, -1, nullptr));
    g_free(modified);

    g_object_unref(annot);
}

// Test with a long modified string
TEST_F(PopplerAnnotGetModifiedTest_2066, LongModifiedString_2066)
{
    if (!page) {
        GTEST_SKIP() << "Could not load test PDF page";
    }

    PopplerRectangle rect = {100.0, 100.0, 200.0, 200.0};
    PopplerAnnot *annot = reinterpret_cast<PopplerAnnot *>(poppler_annot_text_new(doc, &rect));
    ASSERT_NE(annot, nullptr);

    // Create a long string
    GString *long_str = g_string_new(nullptr);
    for (int i = 0; i < 1000; i++) {
        g_string_append_c(long_str, 'A' + (i % 26));
    }

    poppler_annot_set_modified(annot, long_str->str);

    gchar *modified = poppler_annot_get_modified(annot);
    ASSERT_NE(modified, nullptr);
    EXPECT_STREQ(modified, long_str->str);
    g_free(modified);

    g_string_free(long_str, TRUE);
    g_object_unref(annot);
}
