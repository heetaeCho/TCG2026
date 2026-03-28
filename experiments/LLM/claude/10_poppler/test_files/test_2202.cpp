#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib-object.h>

// Include necessary headers
#include "poppler-document.h"
#include "poppler-private.h"
#include "PDFDoc.h"

// We need to mock PDFDoc since it's a dependency
class MockPDFDoc {
public:
    MOCK_METHOD(PDFSubtype, getPDFSubtype, (), (const));
    MOCK_METHOD(std::unique_ptr<GooString>, getDocInfoStringEntry, (const char*));
};

// Since we can't easily create real PopplerDocument objects without a real PDF,
// we'll use poppler's own API to load test documents or handle NULL cases.

class PopplerDocumentGetPdfSubtypeStringTest_2202 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NULL (g_return_val_if_fail check)
TEST_F(PopplerDocumentGetPdfSubtypeStringTest_2202, NullDocumentReturnsNull_2202)
{
    gchar *result = poppler_document_get_pdf_subtype_string(NULL);
    EXPECT_EQ(result, nullptr);
}

// Test that passing an invalid GObject type returns NULL
TEST_F(PopplerDocumentGetPdfSubtypeStringTest_2202, InvalidObjectReturnsNull_2202)
{
    // Create a non-PopplerDocument GObject and cast it
    // This should fail the POPPLER_IS_DOCUMENT check
    GObject *obj = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    gchar *result = poppler_document_get_pdf_subtype_string((PopplerDocument *)obj);
    EXPECT_EQ(result, nullptr);
    g_object_unref(obj);
}

// Test with a real PDF that has no subtype (subtypeNone/subtypeNull)
// We load a basic PDF from memory that doesn't have subtype info
class PopplerDocumentFromFileTest_2202 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override
    {
        // Create a minimal PDF in memory
        // This is a very minimal valid PDF
        const char *minimal_pdf = "%PDF-1.0\n"
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

        // Write to a temp file
        gchar *tmpfile = NULL;
        GError *error = NULL;
        gint fd = g_file_open_tmp("test_pdf_XXXXXX.pdf", &tmpfile, &error);
        if (fd >= 0) {
            write(fd, minimal_pdf, strlen(minimal_pdf));
            close(fd);

            gchar *uri = g_filename_to_uri(tmpfile, NULL, &error);
            if (uri) {
                doc = poppler_document_new_from_file(uri, NULL, &error);
                g_free(uri);
            }
            g_unlink(tmpfile);
            g_free(tmpfile);
        }
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override
    {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }
};

// Test that a basic PDF without subtype returns NULL
TEST_F(PopplerDocumentFromFileTest_2202, BasicPdfReturnsNullSubtypeString_2202)
{
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    gchar *result = poppler_document_get_pdf_subtype_string(doc);
    // A basic PDF without PDF/A, PDF/E, etc. should return NULL
    EXPECT_EQ(result, nullptr);
    if (result) {
        g_free(result);
    }
}

// Test the poppler_document_get_pdf_subtype function as well for completeness
TEST_F(PopplerDocumentFromFileTest_2202, BasicPdfSubtypeIsNoneOrNull_2202)
{
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    PopplerPDFSubtype subtype = poppler_document_get_pdf_subtype(doc);
    // A minimal PDF should not have a recognized subtype
    EXPECT_TRUE(subtype == POPPLER_PDF_SUBTYPE_NONE || subtype == POPPLER_PDF_SUBTYPE_UNSET);
}

// Test that get_pdf_subtype_string frees properly when called multiple times
TEST_F(PopplerDocumentFromFileTest_2202, MultipleCallsReturnConsistentResults_2202)
{
    if (doc == nullptr) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    gchar *result1 = poppler_document_get_pdf_subtype_string(doc);
    gchar *result2 = poppler_document_get_pdf_subtype_string(doc);

    // Both should be the same (both NULL for basic PDF)
    if (result1 == nullptr) {
        EXPECT_EQ(result2, nullptr);
    } else {
        ASSERT_NE(result2, nullptr);
        EXPECT_STREQ(result1, result2);
        g_free(result2);
    }
    g_free(result1);
}
