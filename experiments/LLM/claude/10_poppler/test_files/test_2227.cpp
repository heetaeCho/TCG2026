#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>
#include <vector>

// Include necessary poppler headers
extern "C" {
#include "poppler-document.h"
}

#include "FontInfo.h"

// Since we need to access the internal structure to set up test fixtures,
// and the struct is defined in the source, we replicate the test-relevant parts
struct _PopplerFontsIter {
    std::vector<FontInfo*> items;
    int index;
};

// We need a way to create FontInfo objects for testing.
// Since FontInfo requires GfxFont* and XRef*, we'll use a helper approach.
// We'll create a mock-friendly subclass or use real objects if possible.

// For black-box testing of poppler_fonts_iter_is_subset, we test through
// the C API. Since constructing PopplerFontsIter properly requires a 
// PopplerDocument, we test with document loading.

class PopplerFontsIterSubsetTest_2227 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll test with actual PDF documents if available
    }

    void TearDown() override {
    }
};

// Test that poppler_fonts_iter_is_subset returns a gboolean value
// when called with a valid iterator from a real document
TEST_F(PopplerFontsIterSubsetTest_2227, ReturnsValidBooleanValue_2227) {
    GError *error = nullptr;
    // Try to load a test PDF document
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    
    if (doc == nullptr) {
        // Skip test if no test document available
        GTEST_SKIP() << "No test PDF document available";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    
    // Scan some pages for fonts
    gboolean has_more = poppler_font_info_scan(font_info, 10, &iter);
    
    if (iter != nullptr) {
        do {
            gboolean is_subset = poppler_fonts_iter_is_subset(iter);
            // Result should be either TRUE or FALSE
            EXPECT_TRUE(is_subset == TRUE || is_subset == FALSE);
        } while (poppler_fonts_iter_next(iter));
        
        poppler_fonts_iter_free(iter);
    }
    
    g_object_unref(font_info);
    g_object_unref(doc);
}

// Test that poppler_fonts_iter_is_subset is consistent across multiple calls
TEST_F(PopplerFontsIterSubsetTest_2227, ConsistentAcrossMultipleCalls_2227) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    
    if (doc == nullptr) {
        GTEST_SKIP() << "No test PDF document available";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    
    poppler_font_info_scan(font_info, 10, &iter);
    
    if (iter != nullptr) {
        // Calling is_subset twice on same position should return same value
        gboolean first_call = poppler_fonts_iter_is_subset(iter);
        gboolean second_call = poppler_fonts_iter_is_subset(iter);
        EXPECT_EQ(first_call, second_call);
        
        poppler_fonts_iter_free(iter);
    }
    
    g_object_unref(font_info);
    g_object_unref(doc);
}

// Test with a copy of the iterator
TEST_F(PopplerFontsIterSubsetTest_2227, CopiedIteratorReturnsSameResult_2227) {
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    
    if (doc == nullptr) {
        GTEST_SKIP() << "No test PDF document available";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    
    poppler_font_info_scan(font_info, 10, &iter);
    
    if (iter != nullptr) {
        PopplerFontsIter *copy = poppler_fonts_iter_copy(iter);
        ASSERT_NE(copy, nullptr);
        
        gboolean original_result = poppler_fonts_iter_is_subset(iter);
        gboolean copy_result = poppler_fonts_iter_is_subset(copy);
        EXPECT_EQ(original_result, copy_result);
        
        poppler_fonts_iter_free(copy);
        poppler_fonts_iter_free(iter);
    }
    
    g_object_unref(font_info);
    g_object_unref(doc);
}
