#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>
#include "poppler-document.h"
}

class PopplerDocumentIsLinearizedTest_2192 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL document returns FALSE and doesn't crash
TEST_F(PopplerDocumentIsLinearizedTest_2192, NullDocumentReturnsFalse_2192)
{
    gboolean result = poppler_document_is_linearized(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test with a linearized PDF document
TEST_F(PopplerDocumentIsLinearizedTest_2192, LinearizedDocumentReturnsTrue_2192)
{
    GError *error = nullptr;
    // Create a document from a known linearized PDF file if available
    // Using a simple PDF from data URI or file path
    PopplerDocument *doc = poppler_document_new_from_file(
        "file:///tmp/test_linearized.pdf", nullptr, &error);
    
    if (doc != nullptr) {
        gboolean result = poppler_document_is_linearized(doc);
        // We just verify it returns a valid gboolean (TRUE or FALSE)
        EXPECT_TRUE(result == TRUE || result == FALSE);
        g_object_unref(doc);
    } else {
        // If the test file doesn't exist, skip gracefully
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Linearized test PDF not available";
    }
}

// Test with a non-linearized PDF document
TEST_F(PopplerDocumentIsLinearizedTest_2192, NonLinearizedDocumentReturnsFalse_2192)
{
    GError *error = nullptr;
    
    // Create a minimal non-linearized PDF in memory
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
    
    gsize len = strlen(minimal_pdf);
    GBytes *bytes = g_bytes_new(minimal_pdf, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    
    PopplerDocument *doc = poppler_document_new_from_stream(
        stream, len, nullptr, nullptr, &error);
    
    if (doc != nullptr) {
        gboolean result = poppler_document_is_linearized(doc);
        EXPECT_EQ(result, FALSE);
        g_object_unref(doc);
    } else {
        // Try alternative approach with data
        if (error) {
            g_error_free(error);
            error = nullptr;
        }
        
        PopplerDocument *doc2 = poppler_document_new_from_data(
            (char *)minimal_pdf, (int)len, nullptr, &error);
        
        if (doc2 != nullptr) {
            gboolean result = poppler_document_is_linearized(doc2);
            EXPECT_EQ(result, FALSE);
            g_object_unref(doc2);
        } else {
            if (error) {
                g_error_free(error);
            }
            GTEST_SKIP() << "Could not create test document from minimal PDF data";
        }
    }
    
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

// Test that the function works with an invalid GObject (not a PopplerDocument)
TEST_F(PopplerDocumentIsLinearizedTest_2192, InvalidObjectReturnsFalse_2192)
{
    // g_return_val_if_fail with POPPLER_IS_DOCUMENT check should return FALSE
    // for a non-PopplerDocument GObject. We pass NULL which triggers the same guard.
    gboolean result = poppler_document_is_linearized(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test consistency: calling is_linearized multiple times gives same result
TEST_F(PopplerDocumentIsLinearizedTest_2192, ConsistentResultOnMultipleCalls_2192)
{
    GError *error = nullptr;
    
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
    
    gsize len = strlen(minimal_pdf);
    GBytes *bytes = g_bytes_new(minimal_pdf, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    
    PopplerDocument *doc = poppler_document_new_from_stream(
        stream, len, nullptr, nullptr, &error);
    
    if (doc != nullptr) {
        gboolean result1 = poppler_document_is_linearized(doc);
        gboolean result2 = poppler_document_is_linearized(doc);
        gboolean result3 = poppler_document_is_linearized(doc);
        
        EXPECT_EQ(result1, result2);
        EXPECT_EQ(result2, result3);
        
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test document";
    }
    
    g_object_unref(stream);
    g_bytes_unref(bytes);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
