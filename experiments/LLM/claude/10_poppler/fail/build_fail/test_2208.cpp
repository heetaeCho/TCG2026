#include <gtest/gtest.h>
#include <gmock/gmock.h>

extern "C" {
#include <glib-object.h>
#include "poppler-document.h"
}

class PopplerDocumentHasJavascriptTest_2208 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL document returns FALSE (due to g_return_val_if_fail)
TEST_F(PopplerDocumentHasJavascriptTest_2208, NullDocumentReturnsFalse_2208)
{
    // g_return_val_if_fail should catch NULL and return FALSE
    gboolean result = poppler_document_has_javascript(nullptr);
    EXPECT_EQ(result, FALSE);
}

// Test with a valid PDF that has no JavaScript
TEST_F(PopplerDocumentHasJavascriptTest_2208, DocumentWithoutJavascriptReturnsFalse_2208)
{
    GError *error = nullptr;
    // Create a simple PDF document without JavaScript
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_no_js.pdf", nullptr, &error);
    
    if (doc != nullptr) {
        gboolean result = poppler_document_has_javascript(doc);
        EXPECT_EQ(result, FALSE);
        g_object_unref(doc);
    } else {
        // If file doesn't exist, skip gracefully
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Test PDF without JavaScript not available";
    }
}

// Test with a valid PDF that has JavaScript
TEST_F(PopplerDocumentHasJavascriptTest_2208, DocumentWithJavascriptReturnsTrue_2208)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_with_js.pdf", nullptr, &error);
    
    if (doc != nullptr) {
        gboolean result = poppler_document_has_javascript(doc);
        EXPECT_EQ(result, TRUE);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Test PDF with JavaScript not available";
    }
}

// Test that the return type is gboolean (TRUE or FALSE)
TEST_F(PopplerDocumentHasJavascriptTest_2208, ReturnValueIsBooleanType_2208)
{
    GError *error = nullptr;
    
    // Try to create a minimal PDF from data
    const char *minimal_pdf = "%PDF-1.0\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                               "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                               "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                               "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                               "0000000058 00000 n \n0000000115 00000 n \n"
                               "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    PopplerDocument *doc = poppler_document_new_from_data(
        (char *)minimal_pdf, strlen(minimal_pdf), nullptr, &error);
    
    if (doc != nullptr) {
        gboolean result = poppler_document_has_javascript(doc);
        EXPECT_TRUE(result == TRUE || result == FALSE);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
}

// Test that calling the function multiple times on the same document yields consistent results
TEST_F(PopplerDocumentHasJavascriptTest_2208, ConsistentResultsOnMultipleCalls_2208)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_no_js.pdf", nullptr, &error);
    
    if (doc != nullptr) {
        gboolean result1 = poppler_document_has_javascript(doc);
        gboolean result2 = poppler_document_has_javascript(doc);
        gboolean result3 = poppler_document_has_javascript(doc);
        EXPECT_EQ(result1, result2);
        EXPECT_EQ(result2, result3);
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Test PDF not available";
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
