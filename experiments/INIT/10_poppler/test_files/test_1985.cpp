#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <string>
#include <memory>
#include "GfxFont.h"  // Assuming the header is correctly included
#include "GlobalParamsWin.h"  // Assuming the original function is here

// Mock for GfxFont to interact with the findSubstituteName function
class MockGfxFont : public GfxFont {
public:
    MockGfxFont(const char* tagA, Ref idA, std::optional<std::string>&& nameA, GfxFontType typeA, Ref embFontIDA)
        : GfxFont(tagA, idA, std::move(nameA), typeA, embFontIDA) {}

    MOCK_METHOD(bool, isCIDFont, (), (const, override));
    MOCK_METHOD(const GooString*, getCollection, (), (const, override));
};

// Test Fixture
class FindSubstituteNameTest_1985 : public ::testing::Test {
protected:
    std::unordered_map<std::string, std::string> fontFiles;
    std::unordered_map<std::string, std::string> substFiles;

    void SetUp() override {
        // Add some mock data for fontFiles and substFiles
        fontFiles["Adobe-CNS1"] = "path/to/Adobe-CNS1";
        fontFiles["Adobe-GB1"] = "path/to/Adobe-GB1";
        substFiles["OriginalFontName"] = "SubstituteFontName";
    }
};

// Test cases

TEST_F(FindSubstituteNameTest_1985, ReturnsSubstituteName_IfMatchFoundInSubstFiles) {
    MockGfxFont font("tagA", Ref(), "OriginalFontName", GfxFontType(), Ref());
    
    const char* result = findSubstituteName(&font, fontFiles, substFiles, "OriginalFontName");

    ASSERT_STREQ(result, "SubstituteFontName");
}

TEST_F(FindSubstituteNameTest_1985, ReturnsDefaultIfNoSubstituteNameFoundInSubstFiles) {
    MockGfxFont font("tagA", Ref(), "UnknownFont", GfxFontType(), Ref());

    const char* result = findSubstituteName(&font, fontFiles, substFiles, "UnknownFont");

    ASSERT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);
}

TEST_F(FindSubstituteNameTest_1985, ReturnsDefaultIfFontIsCIDFontAndNoMatchingCollection) {
    MockGfxFont font("tagA", Ref(), "SomeCIDFont", GfxFontType(), Ref());
    EXPECT_CALL(font, isCIDFont()).WillOnce(::testing::Return(true));
    EXPECT_CALL(font, getCollection()).WillOnce(::testing::Return(new GooString("Unknown-Collection")));

    const char* result = findSubstituteName(&font, fontFiles, substFiles, "SomeCIDFont");

    ASSERT_STREQ(result, DEFAULT_CID_FONT_MSWIN);
}

TEST_F(FindSubstituteNameTest_1985, ReturnsCorrectCIDFontBasedOnCollection) {
    MockGfxFont font("tagA", Ref(), "Adobe-CNS1", GfxFontType(), Ref());
    EXPECT_CALL(font, isCIDFont()).WillOnce(::testing::Return(true));
    EXPECT_CALL(font, getCollection()).WillOnce(::testing::Return(new GooString("Adobe-CNS1")));

    const char* result = findSubstituteName(&font, fontFiles, substFiles, "Adobe-CNS1");

    ASSERT_STREQ(result, "path/to/Adobe-CNS1");
}

// Edge case where font name is null
TEST_F(FindSubstituteNameTest_1985, ReturnsNullIfOriginalNameIsNull) {
    MockGfxFont font("tagA", Ref(), "SomeCIDFont", GfxFontType(), Ref());
    const char* result = findSubstituteName(&font, fontFiles, substFiles, nullptr);

    ASSERT_EQ(result, nullptr);
}

// Edge case where font name is empty
TEST_F(FindSubstituteNameTest_1985, ReturnsDefaultIfOriginalNameIsEmpty) {
    MockGfxFont font("tagA", Ref(), "", GfxFontType(), Ref());

    const char* result = findSubstituteName(&font, fontFiles, substFiles, "");

    ASSERT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);
}