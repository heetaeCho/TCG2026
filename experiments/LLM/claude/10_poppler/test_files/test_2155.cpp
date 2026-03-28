#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstdlib>
#include <cstring>

class PopplerDocumentHasAttachmentsTest_2155 : public ::testing::Test {
protected:
    PopplerDocument *doc_with_attachments = nullptr;
    PopplerDocument *doc_without_attachments = nullptr;

    void SetUp() override {
        // Try to load a PDF that has attachments
        GError *error = nullptr;

        // Create a simple PDF without attachments for testing
        // We'll use a minimal PDF file approach
        const char *src_dir = g_getenv("TEST_DATA_DIR");
        if (!src_dir) {
            src_dir = ".";
        }

        // Try to create a minimal PDF in memory for testing
        // We'll create a temporary file with minimal PDF content
        gchar *tmp_path = nullptr;
        int fd = g_file_open_tmp("test_no_attach_XXXXXX.pdf", &tmp_path, &error);
        if (fd != -1) {
            // Minimal valid PDF content
            const char *minimal_pdf =
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

            write(fd, minimal_pdf, strlen(minimal_pdf));
            close(fd);

            gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
            if (uri) {
                doc_without_attachments = poppler_document_new_from_file(uri, nullptr, &error);
                g_free(uri);
            }
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
            g_unlink(tmp_path);
            g_free(tmp_path);
        }
    }

    void TearDown() override {
        if (doc_with_attachments) {
            g_object_unref(doc_with_attachments);
        }
        if (doc_without_attachments) {
            g_object_unref(doc_without_attachments);
        }
    }
};

// Test that passing NULL returns FALSE (g_return_val_if_fail check)
TEST_F(PopplerDocumentHasAttachmentsTest_2155, NullDocumentReturnsFalse_2155)
{
    // Passing NULL should trigger g_return_val_if_fail and return FALSE
    // This will produce a g_warning, but should not crash
    gboolean result = poppler_document_has_attachments(nullptr);
    EXPECT_FALSE(result);
}

// Test that a simple PDF without attachments returns FALSE
TEST_F(PopplerDocumentHasAttachmentsTest_2155, DocumentWithoutAttachmentsReturnsFalse_2155)
{
    if (!doc_without_attachments) {
        GTEST_SKIP() << "Could not create test document without attachments";
    }
    gboolean result = poppler_document_has_attachments(doc_without_attachments);
    EXPECT_FALSE(result);
}

// Test consistency: has_attachments should match get_n_attachments != 0
TEST_F(PopplerDocumentHasAttachmentsTest_2155, ConsistentWithGetNAttachments_2155)
{
    if (!doc_without_attachments) {
        GTEST_SKIP() << "Could not create test document";
    }
    guint n = poppler_document_get_n_attachments(doc_without_attachments);
    gboolean has = poppler_document_has_attachments(doc_without_attachments);

    if (n == 0) {
        EXPECT_FALSE(has);
    } else {
        EXPECT_TRUE(has);
    }
}

// Test that calling has_attachments multiple times gives consistent results
TEST_F(PopplerDocumentHasAttachmentsTest_2155, RepeatedCallsConsistent_2155)
{
    if (!doc_without_attachments) {
        GTEST_SKIP() << "Could not create test document";
    }
    gboolean result1 = poppler_document_has_attachments(doc_without_attachments);
    gboolean result2 = poppler_document_has_attachments(doc_without_attachments);
    EXPECT_EQ(result1, result2);
}

// Test with an invalid GObject (not a PopplerDocument) - should return FALSE
TEST_F(PopplerDocumentHasAttachmentsTest_2155, InvalidObjectReturnsFalse_2155)
{
    // Create a non-PopplerDocument GObject
    // g_return_val_if_fail with POPPLER_IS_DOCUMENT should catch this
    GObject *not_a_document = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    gboolean result = poppler_document_has_attachments((PopplerDocument *)not_a_document);
    EXPECT_FALSE(result);
    g_object_unref(not_a_document);
}
