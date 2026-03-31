#include <gtest/gtest.h>
#include "HtmlFonts.h"

class HtmlFontAccuTest_2628 : public ::testing::Test {
protected:
    HtmlFontAccu accu;
};

// Test that a newly created HtmlFontAccu has size 0
TEST_F(HtmlFontAccuTest_2628, InitialSizeIsZero_2628) {
    EXPECT_EQ(accu.size(), 0);
}

// Test that adding a font increases the size
TEST_F(HtmlFontAccuTest_2628, AddFontIncreasesSize_2628) {
    HtmlFont font;
    int idx = accu.AddFont(font);
    EXPECT_EQ(accu.size(), 1);
    EXPECT_GE(idx, 0);
}

// Test that Get returns a valid pointer for an added font
TEST_F(HtmlFontAccuTest_2628, GetReturnsAddedFont_2628) {
    HtmlFont font;
    int idx = accu.AddFont(font);
    const HtmlFont *retrieved = accu.Get(idx);
    EXPECT_NE(retrieved, nullptr);
}

// Test adding multiple fonts and retrieving them
TEST_F(HtmlFontAccuTest_2628, AddMultipleFontsAndRetrieve_2628) {
    HtmlFont font1;
    HtmlFont font2;
    HtmlFont font3;

    int idx1 = accu.AddFont(font1);
    int idx2 = accu.AddFont(font2);
    int idx3 = accu.AddFont(font3);

    EXPECT_EQ(accu.size(), 3);

    const HtmlFont *r1 = accu.Get(idx1);
    const HtmlFont *r2 = accu.Get(idx2);
    const HtmlFont *r3 = accu.Get(idx3);

    EXPECT_NE(r1, nullptr);
    EXPECT_NE(r2, nullptr);
    EXPECT_NE(r3, nullptr);
}

// Test that Get with index 0 works after adding one font
TEST_F(HtmlFontAccuTest_2628, GetAtIndexZero_2628) {
    HtmlFont font;
    accu.AddFont(font);
    const HtmlFont *retrieved = accu.Get(0);
    EXPECT_NE(retrieved, nullptr);
}

// Test that adding duplicate fonts may return existing index (deduplication behavior)
TEST_F(HtmlFontAccuTest_2628, AddDuplicateFonts_2628) {
    HtmlFont font;
    int idx1 = accu.AddFont(font);
    int idx2 = accu.AddFont(font);
    
    // Whether duplicates are deduplicated or not, both indices should be valid
    EXPECT_GE(idx1, 0);
    EXPECT_GE(idx2, 0);
    
    const HtmlFont *r1 = accu.Get(idx1);
    const HtmlFont *r2 = accu.Get(idx2);
    EXPECT_NE(r1, nullptr);
    EXPECT_NE(r2, nullptr);
}

// Test size after adding several fonts
TEST_F(HtmlFontAccuTest_2628, SizeAfterMultipleAdds_2628) {
    int initialSize = accu.size();
    EXPECT_EQ(initialSize, 0);

    HtmlFont font;
    accu.AddFont(font);
    EXPECT_GE(accu.size(), 1);
}

// Test CSStyle returns a non-null result for valid indices
TEST_F(HtmlFontAccuTest_2628, CSStyleReturnsNonNull_2628) {
    HtmlFont font;
    int idx = accu.AddFont(font);
    auto style = accu.CSStyle(idx, 0);
    // CSStyle should return some kind of style string
    EXPECT_NE(style, nullptr);
}

// Test CSStyle with different j parameter
TEST_F(HtmlFontAccuTest_2628, CSStyleDifferentJ_2628) {
    HtmlFont font;
    int idx = accu.AddFont(font);
    auto style0 = accu.CSStyle(idx, 0);
    auto style1 = accu.CSStyle(idx, 1);
    EXPECT_NE(style0, nullptr);
    EXPECT_NE(style1, nullptr);
}

// Test that the class is not copyable (compile-time check - we just verify it compiles correctly)
TEST_F(HtmlFontAccuTest_2628, NotCopyConstructible_2628) {
    EXPECT_FALSE(std::is_copy_constructible<HtmlFontAccu>::value);
}

TEST_F(HtmlFontAccuTest_2628, NotCopyAssignable_2628) {
    EXPECT_FALSE(std::is_copy_assignable<HtmlFontAccu>::value);
}

// Test adding a large number of fonts
TEST_F(HtmlFontAccuTest_2628, AddManyFonts_2628) {
    HtmlFont font;
    for (int i = 0; i < 100; i++) {
        int idx = accu.AddFont(font);
        EXPECT_GE(idx, 0);
    }
    EXPECT_GE(accu.size(), 1);
}
