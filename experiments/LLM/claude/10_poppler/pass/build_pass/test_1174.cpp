#include <gtest/gtest.h>
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"
#include <memory>

class TextFontInfoTest_1174 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test construction with nullptr GfxState - boundary condition
TEST_F(TextFontInfoTest_1174, ConstructWithNullState_1174) {
    // Constructing with null state - testing that it doesn't crash
    // or that it handles null gracefully
    TextFontInfo* info = nullptr;
    EXPECT_NO_FATAL_FAILURE({
        info = new TextFontInfo(nullptr);
    });
    if (info) {
        delete info;
    }
}

// Test isFixedWidth with null-constructed TextFontInfo
TEST_F(TextFontInfoTest_1174, IsFixedWidthWithNullState_1174) {
    TextFontInfo info(nullptr);
    // With no font, flags should be 0, so isFixedWidth should return false
    bool result = info.isFixedWidth();
    EXPECT_FALSE(result);
}

// Test isSerif with null-constructed TextFontInfo
TEST_F(TextFontInfoTest_1174, IsSerifWithNullState_1174) {
    TextFontInfo info(nullptr);
    bool result = info.isSerif();
    EXPECT_FALSE(result);
}

// Test isSymbolic with null-constructed TextFontInfo
TEST_F(TextFontInfoTest_1174, IsSymbolicWithNullState_1174) {
    TextFontInfo info(nullptr);
    bool result = info.isSymbolic();
    EXPECT_FALSE(result);
}

// Test isItalic with null-constructed TextFontInfo
TEST_F(TextFontInfoTest_1174, IsItalicWithNullState_1174) {
    TextFontInfo info(nullptr);
    bool result = info.isItalic();
    EXPECT_FALSE(result);
}

// Test isBold with null-constructed TextFontInfo
TEST_F(TextFontInfoTest_1174, IsBoldWithNullState_1174) {
    TextFontInfo info(nullptr);
    bool result = info.isBold();
    EXPECT_FALSE(result);
}

// Test getFontName with null-constructed TextFontInfo
TEST_F(TextFontInfoTest_1174, GetFontNameWithNullState_1174) {
    TextFontInfo info(nullptr);
    const GooString* name = info.getFontName();
    // With null state, font name should be null
    EXPECT_EQ(name, nullptr);
}

// Test getAscent with null-constructed TextFontInfo
TEST_F(TextFontInfoTest_1174, GetAscentWithNullState_1174) {
    TextFontInfo info(nullptr);
    double ascent = info.getAscent();
    // Default ascent value when no font is set
    EXPECT_GE(ascent, 0.0);
}

// Test getDescent with null-constructed TextFontInfo
TEST_F(TextFontInfoTest_1174, GetDescentWithNullState_1174) {
    TextFontInfo info(nullptr);
    double descent = info.getDescent();
    // Descent is typically negative or zero
    EXPECT_LE(descent, 0.0);
}

// Test matches with same null-state object
TEST_F(TextFontInfoTest_1174, MatchesFontInfoSelf_1174) {
    TextFontInfo info(nullptr);
    // A TextFontInfo should match itself
    bool result = info.matches(&info);
    EXPECT_TRUE(result);
}

// Test matches with two different null-state objects
TEST_F(TextFontInfoTest_1174, MatchesTwoNullStateObjects_1174) {
    TextFontInfo info1(nullptr);
    TextFontInfo info2(nullptr);
    // Two null-state font infos should match each other
    bool result = info1.matches(&info2);
    EXPECT_TRUE(result);
}

// Test matches with GfxState parameter (null)
TEST_F(TextFontInfoTest_1174, MatchesNullGfxState_1174) {
    TextFontInfo info(nullptr);
    bool result = info.matches(static_cast<const GfxState*>(nullptr));
    EXPECT_TRUE(result);
}

// Test that copy constructor is deleted
TEST_F(TextFontInfoTest_1174, CopyConstructorDeleted_1174) {
    EXPECT_FALSE(std::is_copy_constructible<TextFontInfo>::value);
}

// Test that copy assignment is deleted
TEST_F(TextFontInfoTest_1174, CopyAssignmentDeleted_1174) {
    EXPECT_FALSE(std::is_copy_assignable<TextFontInfo>::value);
}
