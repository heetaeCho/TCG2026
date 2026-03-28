#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstring>

// Include necessary poppler headers
extern "C" {
#include "poppler-document.h"
}

#include "FontInfo.h"

// Since we need to test poppler_fonts_iter_get_name which operates on
// PopplerFontsIter, and the struct has items and index fields, we need
// to understand the structure layout. Based on the code:
// iter->items[iter->index] gives a FontInfo*
// So items is FontInfo** and index is int.

// We work with the actual poppler API where possible.

class PopplerFontsIterGetNameTest_2221 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_fonts_iter_get_name returns NULL when iter is NULL-like edge case
// Note: passing NULL iter would likely crash, so we test with valid iterators

// Test with a non-subset font - name should be returned as-is (full name)
TEST_F(PopplerFontsIterGetNameTest_2221, NonSubsetFontReturnsFullName_2221)
{
    // For a non-subset font, poppler_fonts_iter_get_name should return
    // the same as poppler_fonts_iter_get_full_name
    // We need a real PopplerDocument to test this properly
    // This is a documentation/specification test

    // If we can load a test PDF:
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    poppler_font_info_scan(font_info, 100, &iter);

    if (iter) {
        do {
            const char *name = poppler_fonts_iter_get_name(iter);
            const char *full_name = poppler_fonts_iter_get_full_name(iter);
            gboolean is_subset = poppler_fonts_iter_is_subset(iter);

            if (!is_subset && full_name) {
                // For non-subset fonts, name should equal full_name
                EXPECT_STREQ(name, full_name);
            }

            if (is_subset && full_name) {
                // For subset fonts, name should skip past the '+' prefix
                const char *plus = strchr(full_name, '+');
                if (plus) {
                    EXPECT_STREQ(name, plus + 1);
                }
            }

            if (!full_name) {
                EXPECT_EQ(name, nullptr);
            }
        } while (poppler_fonts_iter_next(iter));

        poppler_fonts_iter_free(iter);
    }

    poppler_font_info_free(font_info);
    g_object_unref(doc);
}

// Test that subset font name strips prefix up to and including '+'
TEST_F(PopplerFontsIterGetNameTest_2221, SubsetFontStripsPrefix_2221)
{
    // The function should advance past "ABCDEF+" prefix for subset fonts
    // This behavior is verified: if getSubset() is true, skip to after '+'
    
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test_subset.pdf", nullptr, &error);
    if (!doc) {
        GTEST_SKIP() << "Test PDF with subset fonts not available";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    poppler_font_info_scan(font_info, 100, &iter);

    if (iter) {
        do {
            const char *name = poppler_fonts_iter_get_name(iter);
            const char *full_name = poppler_fonts_iter_get_full_name(iter);
            gboolean is_subset = poppler_fonts_iter_is_subset(iter);

            if (is_subset && full_name) {
                // Name should not contain the subset prefix
                // The full_name typically looks like "ABCDEF+FontName"
                // name should be "FontName"
                const char *plus_in_full = strchr(full_name, '+');
                if (plus_in_full) {
                    EXPECT_EQ(name, plus_in_full + 1);
                    EXPECT_TRUE(strstr(full_name, name) != nullptr);
                }
            }
        } while (poppler_fonts_iter_next(iter));

        poppler_fonts_iter_free(iter);
    }

    poppler_font_info_free(font_info);
    g_object_unref(doc);
}

// Test with NULL name - function should return NULL
TEST_F(PopplerFontsIterGetNameTest_2221, NullNameReturnsNull_2221)
{
    // When poppler_fonts_iter_get_full_name returns NULL,
    // poppler_fonts_iter_get_name should also return NULL
    // (the subset check has && name, so NULL is preserved)
    
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    poppler_font_info_scan(font_info, 100, &iter);

    if (iter) {
        do {
            const char *full_name = poppler_fonts_iter_get_full_name(iter);
            const char *name = poppler_fonts_iter_get_name(iter);

            if (full_name == nullptr) {
                EXPECT_EQ(name, nullptr);
            }
        } while (poppler_fonts_iter_next(iter));

        poppler_fonts_iter_free(iter);
    }

    poppler_font_info_free(font_info);
    g_object_unref(doc);
}

// Test that for non-subset font, returned pointer equals full_name pointer
TEST_F(PopplerFontsIterGetNameTest_2221, NonSubsetReturnsSamePointer_2221)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    poppler_font_info_scan(font_info, 100, &iter);

    if (iter) {
        do {
            gboolean is_subset = poppler_fonts_iter_is_subset(iter);
            const char *full_name = poppler_fonts_iter_get_full_name(iter);
            const char *name = poppler_fonts_iter_get_name(iter);

            if (!is_subset) {
                // For non-subset fonts, the pointer should be the same
                EXPECT_EQ(name, full_name);
            }
        } while (poppler_fonts_iter_next(iter));

        poppler_fonts_iter_free(iter);
    }

    poppler_font_info_free(font_info);
    g_object_unref(doc);
}

// Test consistency - calling get_name multiple times returns same result
TEST_F(PopplerFontsIterGetNameTest_2221, ConsistentResults_2221)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    poppler_font_info_scan(font_info, 100, &iter);

    if (iter) {
        do {
            const char *name1 = poppler_fonts_iter_get_name(iter);
            const char *name2 = poppler_fonts_iter_get_name(iter);

            // Calling twice should yield the same result
            EXPECT_EQ(name1, name2);
            if (name1 && name2) {
                EXPECT_STREQ(name1, name2);
            }
        } while (poppler_fonts_iter_next(iter));

        poppler_fonts_iter_free(iter);
    }

    poppler_font_info_free(font_info);
    g_object_unref(doc);
}

// Test that for subset font with no '+' in name, pointer advances to end (empty string)
TEST_F(PopplerFontsIterGetNameTest_2221, SubsetFontNoPlusReturnsEndOfString_2221)
{
    // If a subset font's full_name has no '+', the while loop will advance
    // to the null terminator, and since *name == '\0', the if (*name) fails,
    // so name stays at the null terminator -> returns empty string ""
    
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///tmp/test.pdf", nullptr, &error);
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PopplerFontInfo *font_info = poppler_font_info_new(doc);
    PopplerFontsIter *iter = nullptr;
    poppler_font_info_scan(font_info, 100, &iter);

    if (iter) {
        do {
            gboolean is_subset = poppler_fonts_iter_is_subset(iter);
            const char *full_name = poppler_fonts_iter_get_full_name(iter);
            const char *name = poppler_fonts_iter_get_name(iter);

            if (is_subset && full_name && !strchr(full_name, '+')) {
                // Should point to end of string (empty string)
                EXPECT_STREQ(name, "");
            }
        } while (poppler_fonts_iter_next(iter));

        poppler_fonts_iter_free(iter);
    }

    poppler_font_info_free(font_info);
    g_object_unref(doc);
}
