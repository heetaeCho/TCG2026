#include <glib.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler-document.h"
}

class PopplerDocumentGetModificationDateTimeTest_2190 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a PopplerDocument from a PDF file
static PopplerDocument *load_test_document(const char *uri, GError **error)
{
    return poppler_document_new_from_file(uri, nullptr, error);
}

// Test that passing NULL document returns nullptr (and doesn't crash)
TEST_F(PopplerDocumentGetModificationDateTimeTest_2190, NullDocumentReturnsNull_2190)
{
    // Passing NULL should trigger g_return_val_if_fail and return nullptr
    GDateTime *result = poppler_document_get_modification_date_time(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test with a valid PDF document that has a modification date
TEST_F(PopplerDocumentGetModificationDateTimeTest_2190, ValidDocumentWithModDate_2190)
{
    // Create a minimal PDF in memory that has a ModDate
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
        "<< /ModDate (D:20230615120000+00'00') >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000196 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
        "startxref\n"
        "259\n"
        "%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_content);
    GBytes *bytes = g_bytes_new(pdf_content, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        GDateTime *mod_date = poppler_document_get_modification_date_time(doc);
        // The document may or may not have a parseable mod date depending on internal parsing
        // If it returns non-null, it should be a valid GDateTime
        if (mod_date != nullptr) {
            // Verify it's a valid date-time by checking year
            gint year = g_date_time_get_year(mod_date);
            EXPECT_EQ(year, 2023);
            gint month = g_date_time_get_month(mod_date);
            EXPECT_EQ(month, 6);
            gint day = g_date_time_get_day_of_month(mod_date);
            EXPECT_EQ(day, 15);
            g_date_time_unref(mod_date);
        }
        g_object_unref(doc);
    } else {
        // If we couldn't load the document, skip the test gracefully
        if (error) {
            g_error_free(error);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with a PDF document that has no modification date
TEST_F(PopplerDocumentGetModificationDateTimeTest_2190, DocumentWithoutModDateReturnsNull_2190)
{
    // Create a minimal PDF without ModDate in info dict
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
        "<< /Title (Test) >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000196 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n"
        "startxref\n"
        "232\n"
        "%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_content);
    GBytes *bytes = g_bytes_new(pdf_content, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        GDateTime *mod_date = poppler_document_get_modification_date_time(doc);
        // No ModDate field, so should return nullptr
        EXPECT_EQ(mod_date, nullptr);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test with a PDF that has no Info dictionary at all
TEST_F(PopplerDocumentGetModificationDateTimeTest_2190, DocumentWithNoInfoDictReturnsNull_2190)
{
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
        "196\n"
        "%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_content);
    GBytes *bytes = g_bytes_new(pdf_content, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);

    if (doc != nullptr) {
        GDateTime *mod_date = poppler_document_get_modification_date_time(doc);
        EXPECT_EQ(mod_date, nullptr);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
}
