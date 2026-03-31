#include <gtest/gtest.h>
#include "HtmlFonts.h"

// Test fixture for HtmlFontAccu
class HtmlFontAccuTest_2629 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a newly constructed HtmlFontAccu has size 0
TEST_F(HtmlFontAccuTest_2629, DefaultConstructorCreatesEmptyAccu_2629) {
    HtmlFontAccu accu;
    EXPECT_EQ(accu.size(), 0);
}

// Test that adding a font increases the size
TEST_F(HtmlFontAccuTest_2629, AddFontIncreasesSize_2629) {
    HtmlFontAccu accu;
    EXPECT_EQ(accu.size(), 0);

    HtmlFont font;
    accu.AddFont(font);
    EXPECT_EQ(accu.size(), 1);
}

// Test that adding multiple fonts increases the size accordingly
TEST_F(HtmlFontAccuTest_2629, AddMultipleFontsIncreasesSize_2629) {
    HtmlFontAccu accu;

    HtmlFont font1;
    HtmlFont font2;
    HtmlFont font3;

    accu.AddFont(font1);
    EXPECT_EQ(accu.size(), 1);

    accu.AddFont(font2);
    EXPECT_EQ(accu.size(), 2);

    accu.AddFont(font3);
    EXPECT_EQ(accu.size(), 3);
}

// Test that AddFont returns a valid index
TEST_F(HtmlFontAccuTest_2629, AddFontReturnsIndex_2629) {
    HtmlFontAccu accu;

    HtmlFont font;
    int index = accu.AddFont(font);
    EXPECT_GE(index, 0);
}

// Test that Get returns non-null for a valid index after adding a font
TEST_F(HtmlFontAccuTest_2629, GetReturnsValidPointerForValidIndex_2629) {
    HtmlFontAccu accu;

    HtmlFont font;
    int index = accu.AddFont(font);

    const HtmlFont *retrieved = accu.Get(index);
    EXPECT_NE(retrieved, nullptr);
}

// Test that Get with an out-of-range index returns null or handles gracefully
TEST_F(HtmlFontAccuTest_2629, GetWithOutOfRangeIndexReturnsNull_2629) {
    HtmlFontAccu accu;

    // No fonts added, any index should be invalid
    const HtmlFont *retrieved = accu.Get(0);
    // The behavior here depends on implementation, but we test it doesn't crash
    // and ideally returns nullptr for invalid index
    EXPECT_EQ(retrieved, nullptr);
}

// Test that Get with negative index handles gracefully
TEST_F(HtmlFontAccuTest_2629, GetWithNegativeIndexReturnsNull_2629) {
    HtmlFontAccu accu;

    HtmlFont font;
    accu.AddFont(font);

    const HtmlFont *retrieved = accu.Get(-1);
    EXPECT_EQ(retrieved, nullptr);
}

// Test that adding duplicate fonts may or may not increase size (deduplication behavior)
TEST_F(HtmlFontAccuTest_2629, AddDuplicateFontBehavior_2629) {
    HtmlFontAccu accu;

    HtmlFont font;
    int index1 = accu.AddFont(font);
    int index2 = accu.AddFont(font);

    // Whether duplicates are stored or deduplicated, both indices should be valid
    EXPECT_GE(index1, 0);
    EXPECT_GE(index2, 0);

    // If deduplicated, index1 == index2 and size == 1
    // If not deduplicated, size == 2
    // Either way, size should be at least 1
    EXPECT_GE(accu.size(), 1);
}

// Test CSStyle returns a result for valid indices
TEST_F(HtmlFontAccuTest_2629, CSStyleReturnsResultForValidIndex_2629) {
    HtmlFontAccu accu;

    HtmlFont font;
    int index = accu.AddFont(font);

    auto style = accu.CSStyle(index, 0);
    // CSStyle should return something (possibly non-null) for a valid font index
    EXPECT_NE(style, nullptr);
}

// Test that the class is not copy-constructible (compile-time check, just verify it exists)
TEST_F(HtmlFontAccuTest_2629, IsNotCopyConstructible_2629) {
    EXPECT_FALSE(std::is_copy_constructible<HtmlFontAccu>::value);
}

// Test that the class is not copy-assignable
TEST_F(HtmlFontAccuTest_2629, IsNotCopyAssignable_2629) {
    EXPECT_FALSE(std::is_copy_assignable<HtmlFontAccu>::value);
}

// Test size after many additions
TEST_F(HtmlFontAccuTest_2629, SizeAfterManyAdditions_2629) {
    HtmlFontAccu accu;

    const int numFonts = 100;
    for (int i = 0; i < numFonts; ++i) {
        HtmlFont font;
        accu.AddFont(font);
    }

    // Size should be at least 1 (if all deduplicated) and at most numFonts
    EXPECT_GE(accu.size(), 1);
    EXPECT_LE(accu.size(), numFonts);
}
