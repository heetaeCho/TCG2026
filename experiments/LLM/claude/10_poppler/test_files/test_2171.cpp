#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <poppler-document.h>
#include <glib.h>
#include <cstdio>
#include <cstdlib>
#include <string>

// Helper function to create a simple PDF file and return a PopplerDocument
static PopplerDocument *create_test_document(const char *pdf_content = nullptr)
{
    // Create a minimal valid PDF in a temporary file
    const char *minimal_pdf =
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
        "190\n"
        "%%EOF\n";

    if (pdf_content == nullptr) {
        pdf_content = minimal_pdf;
    }

    char tmpfile[] = "/tmp/poppler_test_XXXXXX.pdf";
    int fd = mkstemps(tmpfile, 4);
    if (fd == -1) {
        return nullptr;
    }

    write(fd, pdf_content, strlen(pdf_content));
    close(fd);

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        unlink(tmpfile);
        if (error) g_error_free(error);
        return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    unlink(tmpfile);

    if (error) {
        g_error_free(error);
    }

    return doc;
}

class PopplerDocumentGetPdfVersionTest_2171 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override
    {
        doc = create_test_document();
        // If we can't create a document, skip tests gracefully
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

// Test that both major and minor versions are retrieved correctly
TEST_F(PopplerDocumentGetPdfVersionTest_2171, GetBothVersions_2171)
{
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    guint major_version = 0;
    guint minor_version = 0;

    poppler_document_get_pdf_version(doc, &major_version, &minor_version);

    // Our minimal PDF is version 1.4
    EXPECT_EQ(major_version, 1u);
    EXPECT_EQ(minor_version, 4u);
}

// Test that passing NULL for major_version does not crash
TEST_F(PopplerDocumentGetPdfVersionTest_2171, NullMajorVersion_2171)
{
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    guint minor_version = 0;

    poppler_document_get_pdf_version(doc, nullptr, &minor_version);

    EXPECT_EQ(minor_version, 4u);
}

// Test that passing NULL for minor_version does not crash
TEST_F(PopplerDocumentGetPdfVersionTest_2171, NullMinorVersion_2171)
{
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    guint major_version = 0;

    poppler_document_get_pdf_version(doc, &major_version, nullptr);

    EXPECT_EQ(major_version, 1u);
}

// Test that passing NULL for both version pointers does not crash
TEST_F(PopplerDocumentGetPdfVersionTest_2171, BothVersionPointersNull_2171)
{
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Should not crash
    poppler_document_get_pdf_version(doc, nullptr, nullptr);
}

// Test with a PDF version 1.7
TEST_F(PopplerDocumentGetPdfVersionTest_2171, Pdf17Version_2171)
{
    const char *pdf_17 =
        "%PDF-1.7\n"
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
        "190\n"
        "%%EOF\n";

    PopplerDocument *doc17 = create_test_document(pdf_17);
    if (!doc17) {
        GTEST_SKIP() << "Could not create PDF 1.7 test document";
    }

    guint major_version = 0;
    guint minor_version = 0;

    poppler_document_get_pdf_version(doc17, &major_version, &minor_version);

    EXPECT_EQ(major_version, 1u);
    EXPECT_EQ(minor_version, 7u);

    g_object_unref(doc17);
}

// Test with a PDF version 1.0
TEST_F(PopplerDocumentGetPdfVersionTest_2171, Pdf10Version_2171)
{
    const char *pdf_10 =
        "%PDF-1.0\n"
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
        "190\n"
        "%%EOF\n";

    PopplerDocument *doc10 = create_test_document(pdf_10);
    if (!doc10) {
        GTEST_SKIP() << "Could not create PDF 1.0 test document";
    }

    guint major_version = 0;
    guint minor_version = 0;

    poppler_document_get_pdf_version(doc10, &major_version, &minor_version);

    EXPECT_EQ(major_version, 1u);
    EXPECT_EQ(minor_version, 0u);

    g_object_unref(doc10);
}

// Test with PDF version 2.0
TEST_F(PopplerDocumentGetPdfVersionTest_2171, Pdf20Version_2171)
{
    const char *pdf_20 =
        "%PDF-2.0\n"
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
        "190\n"
        "%%EOF\n";

    PopplerDocument *doc20 = create_test_document(pdf_20);
    if (!doc20) {
        GTEST_SKIP() << "Could not create PDF 2.0 test document";
    }

    guint major_version = 0;
    guint minor_version = 0;

    poppler_document_get_pdf_version(doc20, &major_version, &minor_version);

    EXPECT_EQ(major_version, 2u);
    EXPECT_EQ(minor_version, 0u);

    g_object_unref(doc20);
}

// Test that passing NULL document triggers g_return_if_fail (no crash, just returns)
TEST_F(PopplerDocumentGetPdfVersionTest_2171, NullDocument_2171)
{
    guint major_version = 99;
    guint minor_version = 99;

    // g_return_if_fail should cause early return without modifying output params
    // We need to suppress GLib critical warnings for this test
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");

    poppler_document_get_pdf_version(nullptr, &major_version, &minor_version);

    g_test_assert_expected_messages();

    // Values should remain unchanged since the function returned early
    EXPECT_EQ(major_version, 99u);
    EXPECT_EQ(minor_version, 99u);
}

// Test that version values are not modified when passing an invalid (non-document) GObject
TEST_F(PopplerDocumentGetPdfVersionTest_2171, InvalidDocumentType_2171)
{
    guint major_version = 42;
    guint minor_version = 42;

    // Cast a non-PopplerDocument GObject - this should trigger g_return_if_fail
    GObject *not_a_doc = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);

    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");

    poppler_document_get_pdf_version((PopplerDocument *)not_a_doc, &major_version, &minor_version);

    g_test_assert_expected_messages();

    EXPECT_EQ(major_version, 42u);
    EXPECT_EQ(minor_version, 42u);

    g_object_unref(not_a_doc);
}

// Test with PDF 1.5 version
TEST_F(PopplerDocumentGetPdfVersionTest_2171, Pdf15Version_2171)
{
    const char *pdf_15 =
        "%PDF-1.5\n"
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
        "190\n"
        "%%EOF\n";

    PopplerDocument *doc15 = create_test_document(pdf_15);
    if (!doc15) {
        GTEST_SKIP() << "Could not create PDF 1.5 test document";
    }

    guint major_version = 0;
    guint minor_version = 0;

    poppler_document_get_pdf_version(doc15, &major_version, &minor_version);

    EXPECT_EQ(major_version, 1u);
    EXPECT_EQ(minor_version, 5u);

    g_object_unref(doc15);
}
