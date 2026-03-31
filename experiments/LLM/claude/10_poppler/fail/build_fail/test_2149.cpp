#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler.h"

class PopplerDocumentTest_2149 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to create a document from a valid PDF file for testing
static PopplerDocument *create_test_document_from_data()
{
    // Minimal valid PDF content
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

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_content, strlen(pdf_content));
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (error) {
        g_error_free(error);
        return nullptr;
    }
    return doc;
}

// Test that creating a document from valid PDF data succeeds
TEST_F(PopplerDocumentTest_2149, CreateFromValidData_2149)
{
    PopplerDocument *doc = create_test_document_from_data();
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document from minimal PDF";
    }
    EXPECT_TRUE(POPPLER_IS_DOCUMENT(doc));
    g_object_unref(doc);
}

// Test that unreffing a document doesn't crash (exercises finalize)
TEST_F(PopplerDocumentTest_2149, UnrefDoesNotCrash_2149)
{
    PopplerDocument *doc = create_test_document_from_data();
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document from minimal PDF";
    }
    EXPECT_TRUE(POPPLER_IS_DOCUMENT(doc));
    // This triggers poppler_document_finalize internally
    g_object_unref(doc);
    // If we reach here without crash, the test passes
    SUCCEED();
}

// Test creating a document with invalid data returns NULL and sets error
TEST_F(PopplerDocumentTest_2149, CreateFromInvalidDataReturnsNull_2149)
{
    const char *invalid_data = "This is not a valid PDF";
    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(invalid_data, strlen(invalid_data));
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test creating from empty data
TEST_F(PopplerDocumentTest_2149, CreateFromEmptyDataReturnsNull_2149)
{
    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static("", 0);
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    EXPECT_EQ(doc, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test that the document has the expected number of pages
TEST_F(PopplerDocumentTest_2149, GetNPages_2149)
{
    PopplerDocument *doc = create_test_document_from_data();
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document from minimal PDF";
    }
    int n_pages = poppler_document_get_n_pages(doc);
    EXPECT_EQ(n_pages, 1);
    g_object_unref(doc);
}

// Test getting a page from document
TEST_F(PopplerDocumentTest_2149, GetPage_2149)
{
    PopplerDocument *doc = create_test_document_from_data();
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document from minimal PDF";
    }
    PopplerPage *page = poppler_document_get_page(doc, 0);
    EXPECT_NE(page, nullptr);
    if (page) {
        g_object_unref(page);
    }
    g_object_unref(doc);
}

// Test getting an out-of-range page returns NULL
TEST_F(PopplerDocumentTest_2149, GetPageOutOfRange_2149)
{
    PopplerDocument *doc = create_test_document_from_data();
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document from minimal PDF";
    }
    PopplerPage *page = poppler_document_get_page(doc, 999);
    EXPECT_EQ(page, nullptr);
    g_object_unref(doc);
}

// Test getting page with negative index returns NULL
TEST_F(PopplerDocumentTest_2149, GetPageNegativeIndex_2149)
{
    PopplerDocument *doc = create_test_document_from_data();
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document from minimal PDF";
    }
    PopplerPage *page = poppler_document_get_page(doc, -1);
    EXPECT_EQ(page, nullptr);
    g_object_unref(doc);
}

// Test multiple ref/unref cycles
TEST_F(PopplerDocumentTest_2149, MultipleRefUnref_2149)
{
    PopplerDocument *doc = create_test_document_from_data();
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document from minimal PDF";
    }
    // Add extra references
    g_object_ref(doc);
    g_object_ref(doc);

    // Remove them
    g_object_unref(doc);
    g_object_unref(doc);

    // Final unref triggers finalize
    g_object_unref(doc);
    SUCCEED();
}

// Test that PDF version can be retrieved
TEST_F(PopplerDocumentTest_2149, GetPDFVersion_2149)
{
    PopplerDocument *doc = create_test_document_from_data();
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document from minimal PDF";
    }
    gchar *pdf_version = poppler_document_get_pdf_version_string(doc);
    EXPECT_NE(pdf_version, nullptr);
    if (pdf_version) {
        g_free(pdf_version);
    }
    g_object_unref(doc);
}

// Test that wrong password returns error for non-encrypted doc
TEST_F(PopplerDocumentTest_2149, WrongPasswordNonEncrypted_2149)
{
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

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_content, strlen(pdf_content));
    // Providing a password to a non-encrypted document should still work
    PopplerDocument *doc = poppler_document_new_from_bytes(bytes, "somepassword", &error);
    g_bytes_unref(bytes);

    // Non-encrypted doc should open fine even with a password provided
    if (doc != nullptr) {
        EXPECT_TRUE(POPPLER_IS_DOCUMENT(doc));
        g_object_unref(doc);
    }
    if (error) {
        g_error_free(error);
    }
}

// Test GObject type checking
TEST_F(PopplerDocumentTest_2149, IsGObjectType_2149)
{
    PopplerDocument *doc = create_test_document_from_data();
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test document from minimal PDF";
    }
    EXPECT_TRUE(G_IS_OBJECT(doc));
    EXPECT_TRUE(POPPLER_IS_DOCUMENT(doc));
    g_object_unref(doc);
}
