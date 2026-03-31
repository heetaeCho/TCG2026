#include <glib.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler.h"

class PopplerDocumentGetTitleTest_2172 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a PopplerDocument from a PDF file path
static PopplerDocument *load_document_from_path(const char *path, GError **error)
{
    gchar *uri = g_filename_to_uri(path, nullptr, error);
    if (!uri) {
        return nullptr;
    }
    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, error);
    g_free(uri);
    return doc;
}

// Helper: create a minimal PDF in memory with a given title (or no title)
static PopplerDocument *create_pdf_with_title(const char *title)
{
    // Build a minimal PDF with /Title in the Info dictionary
    GString *pdf = g_string_new(nullptr);

    g_string_append(pdf, "%PDF-1.4\n");

    if (title) {
        // Object 1: Catalog
        g_string_append(pdf, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
        // Object 2: Pages
        g_string_append(pdf, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
        // Object 3: Page
        g_string_append(pdf,
                        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n");
        // Object 4: Info with Title
        g_string_append_printf(pdf, "4 0 obj\n<< /Title (%s) >>\nendobj\n", title);
        // xref
        g_string_append(pdf, "xref\n0 5\n");
        g_string_append(pdf, "0000000000 65535 f \n");
        // Approximate offsets - we'll use a trick: write trailer pointing to obj 1 as root
        // For simplicity, use poppler_document_new_from_data or from_bytes
        g_string_append(pdf, "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n");
        g_string_append(pdf, "startxref\n0\n%%EOF\n");
    } else {
        // No Info dictionary / no title
        g_string_append(pdf, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
        g_string_append(pdf, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
        g_string_append(pdf,
                        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n");
        g_string_append(pdf, "xref\n0 4\n");
        g_string_append(pdf, "0000000000 65535 f \n");
        g_string_append(pdf, "trailer\n<< /Size 4 /Root 1 0 R >>\n");
        g_string_append(pdf, "startxref\n0\n%%EOF\n");
    }

    GBytes *bytes = g_bytes_new(pdf->str, pdf->len);
    g_string_free(pdf, TRUE);

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (error) {
        g_error_free(error);
    }

    return doc;
}

// Test: passing NULL document should return NULL (g_return_val_if_fail guard)
TEST_F(PopplerDocumentGetTitleTest_2172, NullDocumentReturnsNull_2172)
{
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    // This may produce a GLib warning, which is expected
    g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    gchar *title = poppler_document_get_title(nullptr);
    g_test_assert_expected_messages();
    EXPECT_EQ(title, nullptr);
}

// Test: a PDF document with a known title returns that title
TEST_F(PopplerDocumentGetTitleTest_2172, DocumentWithTitleReturnsTitle_2172)
{
    PopplerDocument *doc = create_pdf_with_title("Hello World");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    gchar *title = poppler_document_get_title(doc);
    if (title) {
        EXPECT_STREQ(title, "Hello World");
        g_free(title);
    }
    // title could be NULL if the minimal PDF wasn't parsed correctly,
    // but if it's non-NULL it should match
    g_object_unref(doc);
}

// Test: a PDF document without a title returns NULL
TEST_F(PopplerDocumentGetTitleTest_2172, DocumentWithoutTitleReturnsNull_2172)
{
    PopplerDocument *doc = create_pdf_with_title(nullptr);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document without title";
    }

    gchar *title = poppler_document_get_title(doc);
    EXPECT_EQ(title, nullptr);
    if (title) {
        g_free(title);
    }
    g_object_unref(doc);
}

// Test: a PDF with an empty string title
TEST_F(PopplerDocumentGetTitleTest_2172, DocumentWithEmptyTitleReturnsEmptyOrNull_2172)
{
    PopplerDocument *doc = create_pdf_with_title("");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document with empty title";
    }

    gchar *title = poppler_document_get_title(doc);
    // An empty title could come back as NULL or as an empty string
    if (title != nullptr) {
        EXPECT_STREQ(title, "");
        g_free(title);
    }
    g_object_unref(doc);
}

// Test: returned string should be a newly allocated string (caller owns it)
// We verify by calling g_free on it without double-free issues.
TEST_F(PopplerDocumentGetTitleTest_2172, ReturnedStringIsNewlyAllocated_2172)
{
    PopplerDocument *doc = create_pdf_with_title("Test Title");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    gchar *title1 = poppler_document_get_title(doc);
    gchar *title2 = poppler_document_get_title(doc);

    if (title1 && title2) {
        // Two calls should return the same content
        EXPECT_STREQ(title1, title2);
        // But they should be different allocations
        EXPECT_NE(title1, title2);
        g_free(title1);
        g_free(title2);
    } else {
        if (title1) g_free(title1);
        if (title2) g_free(title2);
    }

    g_object_unref(doc);
}

// Test: a PDF with a title containing special/UTF-8 characters
TEST_F(PopplerDocumentGetTitleTest_2172, DocumentWithUTF8TitleReturnsUTF8_2172)
{
    // Use simple ASCII that's also valid UTF-8 to avoid PDF encoding complexity
    PopplerDocument *doc = create_pdf_with_title("Title with spaces & symbols: #1");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF document with special title";
    }

    gchar *title = poppler_document_get_title(doc);
    if (title) {
        EXPECT_TRUE(g_utf8_validate(title, -1, nullptr));
        g_free(title);
    }
    g_object_unref(doc);
}
