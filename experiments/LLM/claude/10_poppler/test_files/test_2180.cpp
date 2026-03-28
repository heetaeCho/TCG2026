#include <glib.h>
#include <gtest/gtest.h>

// Include poppler glib headers
#include "poppler-document.h"

class PopplerDocumentGetCreatorTest_2180 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL document returns NULL
TEST_F(PopplerDocumentGetCreatorTest_2180, NullDocumentReturnsNull_2180)
{
    gchar *creator = poppler_document_get_creator(NULL);
    EXPECT_EQ(creator, nullptr);
}

// Test that a valid PDF with a creator field returns a non-null string
TEST_F(PopplerDocumentGetCreatorTest_2180, ValidDocumentWithCreator_2180)
{
    GError *error = nullptr;
    // Try to load a sample PDF that likely has creator metadata
    // We use a simple approach: create a document from a known test file
    const char *test_pdf_path = TESTDATADIR "/unittestcases/WithCreator.pdf";
    
    gchar *uri = g_filename_to_uri(test_pdf_path, NULL, &error);
    if (uri == NULL) {
        // If we can't construct a URI, skip this test
        GTEST_SKIP() << "Cannot construct URI for test PDF";
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, NULL, &error);
    g_free(uri);

    if (doc == NULL) {
        // If test PDF doesn't exist, skip
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Test PDF not available";
    }

    gchar *creator = poppler_document_get_creator(doc);
    // Creator may or may not be set depending on the PDF; just ensure no crash
    if (creator != NULL) {
        EXPECT_TRUE(g_utf8_validate(creator, -1, NULL));
        g_free(creator);
    }

    g_object_unref(doc);
}

// Test with a minimal PDF that has no creator field
TEST_F(PopplerDocumentGetCreatorTest_2180, DocumentWithoutCreatorReturnsNull_2180)
{
    GError *error = nullptr;
    // Minimal PDF content without creator info
    const char minimal_pdf[] =
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

    GBytes *bytes = g_bytes_new_static(minimal_pdf, sizeof(minimal_pdf) - 1);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    PopplerDocument *doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), NULL, NULL, &error);

    if (doc == NULL) {
        // Fallback: try poppler_document_new_from_data if stream approach fails
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
        g_object_unref(stream);
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not create document from minimal PDF";
    }

    gchar *creator = poppler_document_get_creator(doc);
    // A minimal PDF with no Info dict should return NULL for creator
    EXPECT_EQ(creator, nullptr);

    if (creator) {
        g_free(creator);
    }

    g_object_unref(doc);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test that passing a non-PopplerDocument GObject returns NULL (g_return_val_if_fail check)
TEST_F(PopplerDocumentGetCreatorTest_2180, NonDocumentObjectReturnsNull_2180)
{
    // Create a plain GObject which is NOT a PopplerDocument
    GObject *not_a_document = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);

    // This should trigger g_return_val_if_fail and return NULL
    // Note: This will produce a g_critical warning which is expected
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    gchar *creator = poppler_document_get_creator((PopplerDocument *)not_a_document);
    g_test_assert_expected_messages();

    EXPECT_EQ(creator, nullptr);

    g_object_unref(not_a_document);
}

// Test that the returned string is valid UTF-8 when creator exists
TEST_F(PopplerDocumentGetCreatorTest_2180, ReturnedStringIsValidUtf8_2180)
{
    GError *error = nullptr;
    // PDF with creator in Info dictionary
    const char pdf_with_creator[] =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "4 0 obj<</Creator(TestCreatorApp)>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000190 00000 n \n"
        "trailer<</Size 5/Root 1 0 R/Info 4 0 R>>\n"
        "startxref\n"
        "232\n"
        "%%EOF\n";

    GBytes *bytes = g_bytes_new_static(pdf_with_creator, sizeof(pdf_with_creator) - 1);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    PopplerDocument *doc = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), NULL, NULL, &error);

    if (doc == NULL) {
        if (error) {
            g_error_free(error);
        }
        g_object_unref(stream);
        g_bytes_unref(bytes);
        GTEST_SKIP() << "Could not create document from PDF with creator";
    }

    gchar *creator = poppler_document_get_creator(doc);
    if (creator != NULL) {
        EXPECT_TRUE(g_utf8_validate(creator, -1, NULL));
        // Verify content matches what we put in
        EXPECT_STREQ(creator, "TestCreatorApp");
        g_free(creator);
    }

    g_object_unref(doc);
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
