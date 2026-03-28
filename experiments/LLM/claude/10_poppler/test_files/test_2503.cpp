#include <glib.h>
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

class PopplerPageTextAttributesTest_2503 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to get a valid PopplerPage
        // We'll try to load a simple PDF from a GBytes buffer
        const char *pdf_content =
            "%PDF-1.4\n"
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
            "BT /F1 12 Tf 100 700 Td (Hello World) Tj ET\n"
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
            "0000000282 00000 n \n"
            "0000000380 00000 n \n"
            "trailer\n"
            "<< /Size 6 /Root 1 0 R >>\n"
            "startxref\n"
            "460\n"
            "%%EOF\n";

        gsize len = strlen(pdf_content);
        GError *error = nullptr;

        // Write to a temp file and load
        char tmpfile[] = "/tmp/poppler_test_XXXXXX.pdf";
        int fd = g_mkstemp(tmpfile);
        if (fd >= 0) {
            write(fd, pdf_content, len);
            close(fd);

            gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            unlink(tmpfile);
        }

        if (doc) {
            page = poppler_document_get_page(doc, 0);
        }
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

// Test that passing NULL page returns NULL
TEST_F(PopplerPageTextAttributesTest_2503, NullPageReturnsNull_2503)
{
    // g_return_val_if_fail should cause NULL return for non-page input
    GList *attrs = poppler_page_get_text_attributes(nullptr);
    EXPECT_EQ(attrs, nullptr);
}

// Test that a valid page returns without crashing (may return NULL or a valid list)
TEST_F(PopplerPageTextAttributesTest_2503, ValidPageDoesNotCrash_2503)
{
    if (!page) {
        GTEST_SKIP() << "Could not create a test PDF page";
    }

    GList *attrs = poppler_page_get_text_attributes(page);
    // The result can be NULL (no text attributes) or a valid list
    // Either way, it should not crash
    if (attrs) {
        poppler_page_free_text_attributes(attrs);
    }
}

// Test that the returned list (if any) contains valid PopplerTextAttributes
TEST_F(PopplerPageTextAttributesTest_2503, ReturnedAttributesAreValid_2503)
{
    if (!page) {
        GTEST_SKIP() << "Could not create a test PDF page";
    }

    GList *attrs = poppler_page_get_text_attributes(page);
    if (attrs) {
        for (GList *l = attrs; l != nullptr; l = l->next) {
            PopplerTextAttributes *attr = static_cast<PopplerTextAttributes *>(l->data);
            ASSERT_NE(attr, nullptr);
            // Font size should be non-negative for valid attributes
            EXPECT_GE(attr->font_size, 0.0);
        }
        poppler_page_free_text_attributes(attrs);
    }
}

// Test calling get_text_attributes multiple times returns consistent results
TEST_F(PopplerPageTextAttributesTest_2503, MultipleCallsConsistent_2503)
{
    if (!page) {
        GTEST_SKIP() << "Could not create a test PDF page";
    }

    GList *attrs1 = poppler_page_get_text_attributes(page);
    GList *attrs2 = poppler_page_get_text_attributes(page);

    guint len1 = attrs1 ? g_list_length(attrs1) : 0;
    guint len2 = attrs2 ? g_list_length(attrs2) : 0;
    EXPECT_EQ(len1, len2);

    if (attrs1) {
        poppler_page_free_text_attributes(attrs1);
    }
    if (attrs2) {
        poppler_page_free_text_attributes(attrs2);
    }
}

// Test with a page that has text - font name should be set
TEST_F(PopplerPageTextAttributesTest_2503, FontNameIsSet_2503)
{
    if (!page) {
        GTEST_SKIP() << "Could not create a test PDF page";
    }

    // Check if there's any text on the page first
    char *text = poppler_page_get_text(page);
    if (!text || strlen(text) == 0) {
        g_free(text);
        GTEST_SKIP() << "No text found on the test page";
    }
    g_free(text);

    GList *attrs = poppler_page_get_text_attributes(page);
    if (attrs) {
        PopplerTextAttributes *attr = static_cast<PopplerTextAttributes *>(attrs->data);
        ASSERT_NE(attr, nullptr);
        // Font name should exist for text content
        EXPECT_NE(attr->font_name, nullptr);
        poppler_page_free_text_attributes(attrs);
    }
}

// Test that get_text_attributes_for_area with full page area matches get_text_attributes
TEST_F(PopplerPageTextAttributesTest_2503, ForAreaMatchesFullPage_2503)
{
    if (!page) {
        GTEST_SKIP() << "Could not create a test PDF page";
    }

    GList *attrs_full = poppler_page_get_text_attributes(page);

    PopplerRectangle rect;
    rect.x1 = 0;
    rect.y1 = 0;
    poppler_page_get_size(page, &rect.x2, &rect.y2);
    GList *attrs_area = poppler_page_get_text_attributes_for_area(page, &rect);

    guint len_full = attrs_full ? g_list_length(attrs_full) : 0;
    guint len_area = attrs_area ? g_list_length(attrs_area) : 0;
    EXPECT_EQ(len_full, len_area);

    if (attrs_full) {
        poppler_page_free_text_attributes(attrs_full);
    }
    if (attrs_area) {
        poppler_page_free_text_attributes(attrs_area);
    }
}

// Test with zero-area rectangle returns empty or NULL
TEST_F(PopplerPageTextAttributesTest_2503, ZeroAreaRectangle_2503)
{
    if (!page) {
        GTEST_SKIP() << "Could not create a test PDF page";
    }

    PopplerRectangle rect = {0, 0, 0, 0};
    GList *attrs = poppler_page_get_text_attributes_for_area(page, &rect);
    // With zero area, we expect either NULL or an empty-ish list
    // Just verify no crash
    if (attrs) {
        poppler_page_free_text_attributes(attrs);
    }
}

// Test that color values in attributes are in valid range [0, 65535]
TEST_F(PopplerPageTextAttributesTest_2503, ColorValuesInRange_2503)
{
    if (!page) {
        GTEST_SKIP() << "Could not create a test PDF page";
    }

    GList *attrs = poppler_page_get_text_attributes(page);
    if (attrs) {
        for (GList *l = attrs; l != nullptr; l = l->next) {
            PopplerTextAttributes *attr = static_cast<PopplerTextAttributes *>(l->data);
            ASSERT_NE(attr, nullptr);
            // PopplerColor uses guint16 values (0-65535)
            EXPECT_GE(attr->color.red, 0);
            EXPECT_LE(attr->color.red, 65535);
            EXPECT_GE(attr->color.green, 0);
            EXPECT_LE(attr->color.green, 65535);
            EXPECT_GE(attr->color.blue, 0);
            EXPECT_LE(attr->color.blue, 65535);
        }
        poppler_page_free_text_attributes(attrs);
    }
}
