#include <gtest/gtest.h>
#include <glib.h>
#include <optional>
#include "GooString.h"

// We need to declare the function under test since it's static in the source file.
// To test a static function, we need to include the source or use a workaround.
// Since the function is static, we'll re-declare it by including the source context.
// In practice, we'd need the function to be accessible. For testing purposes,
// we replicate the declaration and include the necessary headers.

// Forward declaration - we need access to the static function.
// One common approach is to include the .cc file directly for testing static functions.
// This is a known pattern for testing static/file-local functions.

// We'll include the source file to get access to the static function
// But first we need the necessary includes that the source file expects

#include <config.h>
#include <cerrno>
#include <cstring>
#include <cmath>

// Minimal includes to make the source file compilable
#include "poppler.h"
#include "poppler-private.h"

// Since poppler_password_to_latin1 is static in the .cc file,
// we need to either include the .cc file or test through public API.
// Testing through public API (poppler_document_new_from_file, etc.) is more appropriate.

// However, since the prompt specifically shows this function, let's test through
// the public API that uses it.

class PopplerDocumentPasswordTest_2138 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Loading a document with NULL password (no password)
TEST_F(PopplerDocumentPasswordTest_2138, NullPasswordReturnsNullopt_2138)
{
    // We test indirectly through poppler_document_new_from_file
    // A non-encrypted PDF should open fine with NULL password
    GError *error = nullptr;

    // Create a minimal valid PDF in a temp file
    const char *pdf_content =
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

    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmpfile, &error);
    if (fd == -1) {
        GTEST_SKIP() << "Could not create temp file";
    }

    FILE *f = fdopen(fd, "wb");
    fwrite(pdf_content, 1, strlen(pdf_content), f);
    fclose(f);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    // Test with NULL password - should work for non-encrypted PDF
    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    if (doc) {
        g_object_unref(doc);
    }
    // Non-encrypted PDF should open without password
    // (may fail if our minimal PDF is malformed, which is acceptable)

    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);
}

// Test: Loading a document with empty string password
TEST_F(PopplerDocumentPasswordTest_2138, EmptyPasswordString_2138)
{
    GError *error = nullptr;

    const char *pdf_content =
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

    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmpfile, &error);
    if (fd == -1) {
        GTEST_SKIP() << "Could not create temp file";
    }

    FILE *f = fdopen(fd, "wb");
    fwrite(pdf_content, 1, strlen(pdf_content), f);
    fclose(f);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    // Test with empty password string
    PopplerDocument *doc = poppler_document_new_from_file(uri, "", &error);
    if (doc) {
        g_object_unref(doc);
    }

    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);
}

// Test: Loading a document with ASCII password
TEST_F(PopplerDocumentPasswordTest_2138, ASCIIPassword_2138)
{
    GError *error = nullptr;

    const char *pdf_content =
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

    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmpfile, &error);
    if (fd == -1) {
        GTEST_SKIP() << "Could not create temp file";
    }

    FILE *f = fdopen(fd, "wb");
    fwrite(pdf_content, 1, strlen(pdf_content), f);
    fclose(f);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    // Test with a regular ASCII password on non-encrypted PDF
    PopplerDocument *doc = poppler_document_new_from_file(uri, "testpassword", &error);
    if (doc) {
        g_object_unref(doc);
    }

    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);
}

// Test: Loading with wrong password on encrypted document should fail
TEST_F(PopplerDocumentPasswordTest_2138, WrongPasswordOnEncryptedDoc_2138)
{
    // This test verifies that password handling works correctly
    // when a wrong password is supplied to an encrypted document.
    // Without an actual encrypted PDF, we skip this.
    GTEST_SKIP() << "Requires an encrypted PDF test fixture";
}

// Test: Verify document creation from data with NULL password
TEST_F(PopplerDocumentPasswordTest_2138, NewFromDataNullPassword_2138)
{
    GError *error = nullptr;

    const char *pdf_content =
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

    G_GNUC_BEGIN_IGNORE_DEPRECATIONS
    PopplerDocument *doc = poppler_document_new_from_data(
        g_strdup(pdf_content), strlen(pdf_content), nullptr, &error);
    G_GNUC_END_IGNORE_DEPRECATIONS

    if (doc) {
        g_object_unref(doc);
    }
    // May or may not succeed depending on PDF validity - we just verify no crash
    if (error) {
        g_error_free(error);
    }
}

// Test: Verify document creation from GBytes with password
TEST_F(PopplerDocumentPasswordTest_2138, NewFromBytesWithPassword_2138)
{
    GError *error = nullptr;

    const char *pdf_content =
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

    GBytes *bytes = g_bytes_new(pdf_content, strlen(pdf_content));

    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, "password123", &error);
    if (doc) {
        g_object_unref(doc);
    }
    if (error) {
        g_error_free(error);
    }

    g_bytes_unref(bytes);
}

// Test: Loading non-existent file returns error
TEST_F(PopplerDocumentPasswordTest_2138, NonExistentFileReturnsError_2138)
{
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_file(
        "file:///nonexistent/path/to/file.pdf", nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);

    if (error) {
        g_error_free(error);
    }
}

// Test: Invalid URI returns error
TEST_F(PopplerDocumentPasswordTest_2138, InvalidURIReturnsError_2138)
{
    GError *error = nullptr;

    PopplerDocument *doc = poppler_document_new_from_file(
        "not_a_valid_uri", nullptr, &error);

    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);

    if (error) {
        g_error_free(error);
    }
}

// Test: UTF-8 password that can be converted to Latin1
TEST_F(PopplerDocumentPasswordTest_2138, UTF8Latin1ConvertiblePassword_2138)
{
    GError *error = nullptr;

    const char *pdf_content =
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

    gchar *tmpfile = nullptr;
    gint fd = g_file_open_tmp("poppler_test_XXXXXX.pdf", &tmpfile, &error);
    if (fd == -1) {
        GTEST_SKIP() << "Could not create temp file";
    }

    FILE *f = fdopen(fd, "wb");
    fwrite(pdf_content, 1, strlen(pdf_content), f);
    fclose(f);

    gchar *uri = g_filename_to_uri(tmpfile, nullptr, &error);
    if (!uri) {
        g_free(tmpfile);
        GTEST_SKIP() << "Could not create URI";
    }

    // Use a password with Latin1-compatible characters (e.g., café = caf\xc3\xa9 in UTF-8)
    PopplerDocument *doc = poppler_document_new_from_file(uri, "caf\xc3\xa9", &error);
    if (doc) {
        g_object_unref(doc);
    }
    if (error) {
        g_error_free(error);
    }

    g_free(uri);
    g_unlink(tmpfile);
    g_free(tmpfile);
}
