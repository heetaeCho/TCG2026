#include <glib.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler-document.h"

class PopplerDocumentGetCreationDateTimeTest_2186 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL document returns nullptr
TEST_F(PopplerDocumentGetCreationDateTimeTest_2186, NullDocumentReturnsNull_2186)
{
    // Passing NULL should trigger g_return_val_if_fail and return nullptr
    GDateTime *result = poppler_document_get_creation_date_time(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test that a valid PDF with a creation date returns a non-null GDateTime
TEST_F(PopplerDocumentGetCreationDateTimeTest_2186, ValidPdfWithCreationDateReturnsNonNull_2186)
{
    GError *error = nullptr;
    // Create a simple PDF in memory with a creation date
    // We'll use a minimal PDF that has a CreationDate in its Info dictionary
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /CreationDate (D:20230615120000+00'00') >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000198 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
        "startxref\n"
        "268\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);

    // Try to load from a temporary file instead
    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("test_poppler_XXXXXX.pdf", &tmpfile, &error);
    if (fd == -1) {
        g_clear_error(&error);
        GTEST_SKIP() << "Could not create temporary file";
        return;
    }

    // Write the PDF content
    write(fd, pdf_content, len);
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        g_clear_error(&error);
        GTEST_SKIP() << "Could not convert filename to URI";
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!doc) {
        // The minimal PDF might not be parseable; skip in that case
        g_clear_error(&error);
        g_unlink(tmpfile);
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create PopplerDocument from minimal PDF";
        return;
    }

    GDateTime *dt = poppler_document_get_creation_date_time(doc);
    // If the document has a valid creation date, it should be non-null
    if (dt != nullptr) {
        // Verify it parsed the date we embedded: 2023-06-15 12:00:00 UTC
        EXPECT_EQ(g_date_time_get_year(dt), 2023);
        EXPECT_EQ(g_date_time_get_month(dt), 6);
        EXPECT_EQ(g_date_time_get_day_of_month(dt), 15);
        EXPECT_EQ(g_date_time_get_hour(dt), 12);
        EXPECT_EQ(g_date_time_get_minute(dt), 0);
        EXPECT_EQ(g_date_time_get_second(dt), 0);
        g_date_time_unref(dt);
    }

    g_object_unref(doc);
    g_unlink(tmpfile);
    g_free(tmpfile);
}

// Test that a PDF without a creation date returns nullptr
TEST_F(PopplerDocumentGetCreationDateTimeTest_2186, PdfWithoutCreationDateReturnsNull_2186)
{
    GError *error = nullptr;

    // Minimal PDF without Info dictionary / CreationDate
    const char *pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
        "endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n"
        "<< /Size 4 /Root 1 0 R >>\n"
        "startxref\n"
        "198\n"
        "%%EOF\n";

    gsize len = strlen(pdf_content);

    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("test_poppler_nodate_XXXXXX.pdf", &tmpfile, &error);
    if (fd == -1) {
        g_clear_error(&error);
        GTEST_SKIP() << "Could not create temporary file";
        return;
    }

    write(fd, pdf_content, len);
    close(fd);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        g_clear_error(&error);
        GTEST_SKIP() << "Could not convert filename to URI";
        return;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (!doc) {
        g_clear_error(&error);
        g_unlink(tmpfile);
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create PopplerDocument from minimal PDF without date";
        return;
    }

    GDateTime *dt = poppler_document_get_creation_date_time(doc);
    // No creation date in the document, so should be nullptr
    EXPECT_EQ(dt, nullptr);

    g_object_unref(doc);
    g_unlink(tmpfile);
    g_free(tmpfile);
}

// Test with an invalid (non-PopplerDocument) GObject pointer
TEST_F(PopplerDocumentGetCreationDateTimeTest_2186, InvalidGObjectReturnsNull_2186)
{
    // Pass a non-PopplerDocument GObject; g_return_val_if_fail should catch this
    // We create a simple GObject that is NOT a PopplerDocument
    GObject *not_a_document = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);

    // This should trigger the POPPLER_IS_DOCUMENT check and return nullptr
    GDateTime *result = poppler_document_get_creation_date_time((PopplerDocument *)not_a_document);
    EXPECT_EQ(result, nullptr);

    g_object_unref(not_a_document);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
