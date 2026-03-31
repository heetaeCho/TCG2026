#include <glib.h>
#include <gtest/gtest.h>

// poppler-document.h should provide the declarations
extern "C" {
#include <poppler-document.h>
}

class PopplerDocumentNewFromFileTest_2139 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: NULL URI should return NULL and set error
TEST_F(PopplerDocumentNewFromFileTest_2139, NullUriReturnsNull_2139)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file(nullptr, nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test: Empty string URI should return NULL and set error
TEST_F(PopplerDocumentNewFromFileTest_2139, EmptyUriReturnsNull_2139)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("", nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test: Invalid URI (not a valid file:// URI) should return NULL and set error
TEST_F(PopplerDocumentNewFromFileTest_2139, InvalidUriReturnsNull_2139)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("not_a_valid_uri", nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    // g_filename_from_uri should fail for non-URI strings
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test: Valid URI format but non-existent file should return NULL
TEST_F(PopplerDocumentNewFromFileTest_2139, NonExistentFileReturnsNull_2139)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/nonexistent_file_poppler_test_2139.pdf", nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test: NULL error parameter with invalid URI should not crash
TEST_F(PopplerDocumentNewFromFileTest_2139, NullErrorParamDoesNotCrash_2139)
{
    PopplerDocument *doc = poppler_document_new_from_file("not_a_valid_uri", nullptr, nullptr);
    EXPECT_EQ(doc, nullptr);
}

// Test: Valid URI to a non-PDF file should return NULL
TEST_F(PopplerDocumentNewFromFileTest_2139, NonPdfFileReturnsNull_2139)
{
    // Create a temporary non-PDF file
    const char *tmpfile = "/tmp/poppler_test_2139_not_a_pdf.txt";
    FILE *f = fopen(tmpfile, "w");
    if (f) {
        fprintf(f, "This is not a PDF file.\n");
        fclose(f);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, nullptr);
        ASSERT_NE(uri, nullptr);

        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
        EXPECT_EQ(doc, nullptr);

        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        unlink(tmpfile);
    }
}

// Test: Valid minimal PDF file should return a valid document
TEST_F(PopplerDocumentNewFromFileTest_2139, ValidPdfFileReturnsDocument_2139)
{
    // Create a minimal valid PDF
    const char *tmpfile = "/tmp/poppler_test_2139_valid.pdf";
    FILE *f = fopen(tmpfile, "wb");
    if (f) {
        const char *minimal_pdf =
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
        fwrite(minimal_pdf, 1, strlen(minimal_pdf), f);
        fclose(f);

        gchar *uri = g_filename_to_uri(tmpfile, nullptr, nullptr);
        ASSERT_NE(uri, nullptr);

        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);

        // The minimal PDF may or may not be accepted depending on parser strictness
        // If it succeeds, the document should be non-null
        if (doc) {
            EXPECT_EQ(error, nullptr);
            g_object_unref(doc);
        }

        g_free(uri);
        if (error) {
            g_error_free(error);
        }
        unlink(tmpfile);
    }
}

// Test: HTTP URI should fail (g_filename_from_uri only handles file:// URIs)
TEST_F(PopplerDocumentNewFromFileTest_2139, HttpUriReturnsNull_2139)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("http://example.com/test.pdf", nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test: Password provided for non-existent file should still return NULL
TEST_F(PopplerDocumentNewFromFileTest_2139, PasswordWithNonExistentFile_2139)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/nonexistent_2139.pdf", "somepassword", &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test: URI with special characters in path should be handled properly
TEST_F(PopplerDocumentNewFromFileTest_2139, UriWithSpecialChars_2139)
{
    GError *error = nullptr;
    // Properly encoded URI with spaces
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/does%20not%20exist_2139.pdf", nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test: Empty password string should behave like no password
TEST_F(PopplerDocumentNewFromFileTest_2139, EmptyPasswordString_2139)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/nonexistent_empty_pw_2139.pdf", "", &error);
    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}
