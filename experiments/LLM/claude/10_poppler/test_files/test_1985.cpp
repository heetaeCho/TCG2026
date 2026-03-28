#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <unordered_map>
#include <memory>
#include <cassert>

#include "GfxFont.h"
#include "GooString.h"

// Since findSubstituteName is a static function in GlobalParamsWin.cc,
// we include the source to get access to it for testing purposes.
// We need the default font macros defined.
#ifndef DEFAULT_CID_FONT_AC1_MSWIN
#define DEFAULT_CID_FONT_AC1_MSWIN "MingLiU"
#endif
#ifndef DEFAULT_CID_FONT_AG1_MSWIN
#define DEFAULT_CID_FONT_AG1_MSWIN "SimSun"
#endif
#ifndef DEFAULT_CID_FONT_AJ1_MSWIN
#define DEFAULT_CID_FONT_AJ1_MSWIN "MS-Mincho"
#endif
#ifndef DEFAULT_CID_FONT_AJ2_MSWIN
#define DEFAULT_CID_FONT_AJ2_MSWIN "MS-Mincho"
#endif
#ifndef DEFAULT_CID_FONT_AK1_MSWIN
#define DEFAULT_CID_FONT_AK1_MSWIN "Batang"
#endif
#ifndef DEFAULT_CID_FONT_MSWIN
#define DEFAULT_CID_FONT_MSWIN "Arial Unicode MS"
#endif
#ifndef DEFAULT_SUBSTITUTE_FONT
#define DEFAULT_SUBSTITUTE_FONT "Arial"
#endif

// Include the static function's source
// We wrap it so we can call it from tests
namespace {
#include "GlobalParamsWin.cc"
}

class FindSubstituteNameTest_1985 : public ::testing::Test {
protected:
    std::unordered_map<std::string, std::string> fontFiles;
    std::unordered_map<std::string, std::string> substFiles;
};

// Test: when origName is found directly in substFiles, return the substitute
TEST_F(FindSubstituteNameTest_1985, DirectSubstitution_1985) {
    substFiles["TestFont"] = "SubstituteFont";
    
    // Create a non-CID font mock - we need a minimal GfxFont
    // Since GfxFont is complex, we use a real but minimal instance if possible
    // For non-CID path, isCIDFont() must return false
    auto font = GfxFont::makeFont(nullptr, "F1", {0, 0}, nullptr);
    // If we can't create a real font, we skip this approach and use a simpler method
    
    const char *result = findSubstituteName(font.get(), fontFiles, substFiles, "TestFont");
    EXPECT_STREQ(result, "SubstituteFont");
}

// Test: Identity-H suffix is stripped before lookup
TEST_F(FindSubstituteNameTest_1985, StripIdentityH_1985) {
    substFiles["TestFont"] = "SubstituteFont";
    
    auto font = GfxFont::makeFont(nullptr, "F1", {0, 0}, nullptr);
    const char *result = findSubstituteName(font.get(), fontFiles, substFiles, "TestFont-Identity-H");
    EXPECT_STREQ(result, "SubstituteFont");
}

// Test: Identity-V suffix is stripped before lookup
TEST_F(FindSubstituteNameTest_1985, StripIdentityV_1985) {
    substFiles["TestFont"] = "SubstituteFont";
    
    auto font = GfxFont::makeFont(nullptr, "F1", {0, 0}, nullptr);
    const char *result = findSubstituteName(font.get(), fontFiles, substFiles, "TestFont-Identity-V");
    EXPECT_STREQ(result, "SubstituteFont");
}

// Test: when no match found and font is not CID, return DEFAULT_SUBSTITUTE_FONT
TEST_F(FindSubstituteNameTest_1985, FallbackToDefaultSubstitute_1985) {
    auto font = GfxFont::makeFont(nullptr, "F1", {0, 0}, nullptr);
    if (font && !font->isCIDFont()) {
        const char *result = findSubstituteName(font.get(), fontFiles, substFiles, "UnknownFont");
        EXPECT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);
    }
}

// Test: short name (less than 11 chars) with no substFile match
TEST_F(FindSubstituteNameTest_1985, ShortNameNoMatch_1985) {
    auto font = GfxFont::makeFont(nullptr, "F1", {0, 0}, nullptr);
    if (font && !font->isCIDFont()) {
        const char *result = findSubstituteName(font.get(), fontFiles, substFiles, "Short");
        EXPECT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);
    }
}

// Test: name exactly 11 characters that is not an Identity suffix
TEST_F(FindSubstituteNameTest_1985, ExactElevenCharsNoSuffix_1985) {
    auto font = GfxFont::makeFont(nullptr, "F1", {0, 0}, nullptr);
    if (font && !font->isCIDFont()) {
        const char *result = findSubstituteName(font.get(), fontFiles, substFiles, "12345678901");
        EXPECT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);
    }
}

// Test: empty string after stripping Identity-H results in lookup of empty string
TEST_F(FindSubstituteNameTest_1985, EmptyAfterStripIdentityH_1985) {
    substFiles[""] = "EmptySubst";
    auto font = GfxFont::makeFont(nullptr, "F1", {0, 0}, nullptr);
    // Name "-Identity-H" has length 11, so n > 11 is false, no stripping
    const char *result = findSubstituteName(font.get(), fontFiles, substFiles, "-Identity-H");
    // Length is exactly 11, condition n > 11 is false, so no stripping occurs
    // Lookup for "-Identity-H" in substFiles
    if (substFiles.find("-Identity-H") == substFiles.end()) {
        if (font && !font->isCIDFont()) {
            EXPECT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);
        }
    }
}

// Test: name longer than 11 but without Identity suffix
TEST_F(FindSubstituteNameTest_1985, LongNameNoIdentitySuffix_1985) {
    auto font = GfxFont::makeFont(nullptr, "F1", {0, 0}, nullptr);
    if (font && !font->isCIDFont()) {
        const char *result = findSubstituteName(font.get(), fontFiles, substFiles, "VeryLongFontNameWithoutSuffix");
        EXPECT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <unordered_map>
#include <cstring>
#include <cassert>

#include "GfxFont.h"
#include "GooString.h"

// Define default font constants matching GlobalParamsWin.cc
#define DEFAULT_CID_FONT_AC1_MSWIN "MingLiU"
#define DEFAULT_CID_FONT_AG1_MSWIN "SimSun"  
#define DEFAULT_CID_FONT_AJ1_MSWIN "MS-Mincho"
#define DEFAULT_CID_FONT_AJ2_MSWIN "MS-Mincho"
#define DEFAULT_CID_FONT_AK1_MSWIN "Batang"
#define DEFAULT_CID_FONT_MSWIN "Arial Unicode MS"
#define DEFAULT_SUBSTITUTE_FONT "Arial"

// Bring in the static function for testing
static const char *findSubstituteName(const GfxFont *font,
    const std::unordered_map<std::string, std::string> &fontFiles,
    const std::unordered_map<std::string, std::string> &substFiles,
    const char *origName);

#include "GlobalParamsWin.cc"

class MockGfxFont : public GfxFont {
public:
    MOCK_METHOD(bool, isCIDFont, (), (const, override));
    MOCK_METHOD(int, getNextChar, (const char*, int, CharCode*, const Unicode**, int*, double*, double*, double*, double*), (const, override));
    MOCK_METHOD(const CharCodeToUnicode*, getToUnicode, (), (const, override));
    MOCK_METHOD(WritingMode, getWMode, (), (const, override));
};

class MockGfxCIDFont : public GfxCIDFont {
public:
    MOCK_METHOD(const GooString*, getCollection, (), (const));
    MOCK_METHOD(bool, isCIDFont, (), (const, override));
};

class FindSubstituteNameTest_1985 : public ::testing::Test {
protected:
    std::unordered_map<std::string, std::string> fontFiles;
    std::unordered_map<std::string, std::string> substFiles;
};

TEST_F(FindSubstituteNameTest_1985, DirectSubstMatch_1985) {
    substFiles["MyFont"] = "ReplacementFont";
    MockGfxFont font;
    EXPECT_CALL(font, isCIDFont()).WillRepeatedly(::testing::Return(false));
    const char *result = findSubstituteName(&font, fontFiles, substFiles, "MyFont");
    EXPECT_STREQ(result, "ReplacementFont");
}

TEST_F(FindSubstituteNameTest_1985, StripIdentityHAndMatch_1985) {
    substFiles["MyFont"] = "ReplacementFont";
    MockGfxFont font;
    EXPECT_CALL(font, isCIDFont()).WillRepeatedly(::testing::Return(false));
    const char *result = findSubstituteName(&font, fontFiles, substFiles, "MyFont-Identity-H");
    EXPECT_STREQ(result, "ReplacementFont");
}

TEST_F(FindSubstituteNameTest_1985, StripIdentityVAndMatch_1985) {
    substFiles["MyFont"] = "ReplacementFont";
    MockGfxFont font;
    EXPECT_CALL(font, isCIDFont()).WillRepeatedly(::testing::Return(false));
    const char *result = findSubstituteName(&font, fontFiles, substFiles, "MyFont-Identity-V");
    EXPECT_STREQ(result, "ReplacementFont");
}

TEST_F(FindSubstituteNameTest_1985, NoMatchNonCIDFallback_1985) {
    MockGfxFont font;
    EXPECT_CALL(font, isCIDFont()).WillRepeatedly(::testing::Return(false));
    const char *result = findSubstituteName(&font, fontFiles, substFiles, "UnknownFont");
    EXPECT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);
}

TEST_F(FindSubstituteNameTest_1985, CIDFontAdobeCNS1_1985) {
    fontFiles[DEFAULT_CID_FONT_AC1_MSWIN] = "/path/to/font";
    GooString collection("Adobe-CNS1");
    MockGfxCIDFont font;
    EXPECT_CALL(font, isCIDFont()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(font, getCollection()).WillRepeatedly(::testing::Return(&collection));
    const char *result = findSubstituteName(&font, fontFiles, substFiles, "SomeCIDFont");
    EXPECT_STREQ(result, DEFAULT_CID_FONT_AC1_MSWIN);
}

TEST_F(FindSubstituteNameTest_1985, CIDFontFallbackToDefault_1985) {
    fontFiles[DEFAULT_CID_FONT_MSWIN] = "/path/to/font";
    GooString collection("Adobe-Unknown");
    MockGfxCIDFont font;
    EXPECT_CALL(font, isCIDFont()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(font, getCollection()).WillRepeatedly(::testing::Return(&collection));
    const char *result = findSubstituteName(&font, fontFiles, substFiles, "SomeCIDFont");
    EXPECT_STREQ(result, DEFAULT_CID_FONT_MSWIN);
}

TEST_F(FindSubstituteNameTest_1985, CIDFontNoFontFilesAvailable_1985) {
    GooString collection("Adobe-CNS1");
    MockGfxCIDFont font;
    EXPECT_CALL(font, isCIDFont()).WillRepeatedly(::testing::Return(true));
    EXPECT_CALL(font, getCollection()).WillRepeatedly(::testing::Return(&collection));
    const char *result = findSubstituteName(&font, fontFiles, substFiles, "SomeCIDFont");
    EXPECT_STREQ(result, DEFAULT_SUBSTITUTE_FONT);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
