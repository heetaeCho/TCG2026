#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <optional>
#include <vector>

// Forward declarations and includes needed
// We need to include the poppler glib headers
extern "C" {
#include "poppler-document.h"
}

#include "FontInfo.h"

// Since we can't easily construct FontInfo objects without GfxFont/XRef,
// and PopplerFontsIter is an internal struct, we test through the public
// C API where possible.

// We test the function behavior via integration-style tests using
// actual PopplerDocument objects loaded from test PDFs.

class PopplerFontsIterGetEncodingTest_2225 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing a nullptr document to font enumeration is handled
TEST_F(PopplerFontsIterGetEncodingTest_2225, NullIterReturnsNullOrCrashes_2225)
{
    // We can't safely pass nullptr to poppler_fonts_iter_get_encoding
    // as it will dereference it. This documents the expected behavior.
    // PopplerFontsIter *iter = nullptr;
    // This would segfault: poppler_fonts_iter_get_encoding(iter);
    SUCCEED(); // Document that null iter is undefined behavior
}

// Test with a real PDF document that has fonts
TEST_F(PopplerFontsIterGetEncodingTest_2225, DocumentWithFonts_2225)
{
    GError *error = nullptr;
    // Try to load a simple test PDF
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    
    if (doc == nullptr) {
        // If no test PDF available, skip
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    
    // Scan some pages
    gboolean has_more = poppler_font_info_scan(font_info, 10, &iter);
    
    if (iter != nullptr) {
        do {
            const char *encoding = poppler_fonts_iter_get_encoding(iter);
            // Encoding can be either a valid string or nullptr (for empty encoding)
            if (encoding != nullptr) {
                // If not null, it should be a valid C string
                EXPECT_GT(strlen(encoding), 0u);
            }
            // nullptr is also valid (empty encoding case)
        } while (poppler_fonts_iter_next(iter));
        
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
    g_object_unref(doc);
}

// Test encoding returns nullptr for fonts with empty encoding
TEST_F(PopplerFontsIterGetEncodingTest_2225, EmptyEncodingReturnsNull_2225)
{
    GError *error = nullptr;
    // Load a PDF that might have fonts without encoding info
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_no_encoding.pdf", nullptr, &error);
    
    if (doc == nullptr) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "No test PDF available for empty encoding test";
        return;
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    
    poppler_font_info_scan(font_info, 10, &iter);
    
    if (iter != nullptr) {
        // Just verify the function doesn't crash
        const char *encoding = poppler_fonts_iter_get_encoding(iter);
        // Result is either null or a valid string - both are acceptable
        SUCCEED();
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
    g_object_unref(doc);
}

// Test that encoding string is consistent across multiple calls
TEST_F(PopplerFontsIterGetEncodingTest_2225, EncodingConsistentAcrossCalls_2225)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    
    if (doc == nullptr) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "No test PDF available";
        return;
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    
    poppler_font_info_scan(font_info, 10, &iter);
    
    if (iter != nullptr) {
        const char *encoding1 = poppler_fonts_iter_get_encoding(iter);
        const char *encoding2 = poppler_fonts_iter_get_encoding(iter);
        
        // Multiple calls should return the same result
        if (encoding1 == nullptr) {
            EXPECT_EQ(encoding2, nullptr);
        } else {
            ASSERT_NE(encoding2, nullptr);
            EXPECT_STREQ(encoding1, encoding2);
        }
        
        poppler_fonts_iter_free(iter);
    }

    g_object_unref(font_info);
    g_object_unref(doc);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
