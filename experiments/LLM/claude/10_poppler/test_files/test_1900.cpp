#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <memory>

// Forward declarations and includes needed
#include "GooString.h"
#include "GfxFont.h"
#include "Error.h"

// To access the static function, we need to include the .cc file
// This is a common technique for testing file-static functions
#include "GlobalParams.cc"

// We need a way to create GfxFont/GfxCIDFont objects for testing.
// Since GfxCIDFont requires complex PDF structures, we create a minimal
// mock/fake subclass for testing purposes.

// Mock CID font that allows us to control the collection string
class FakeGfxCIDFont : public GfxFont {
public:
    std::unique_ptr<GooString> fakeCollection;

    // Minimal constructor - we use a simple setup
    FakeGfxCIDFont(const char* collectionStr)
        : GfxFont("tag", Ref::INVALID(), std::optional<std::string>("TestFont"), fontCIDType0, Ref::INVALID())
    {
        if (collectionStr) {
            fakeCollection = std::make_unique<GooString>(collectionStr);
        }
    }

    bool isCIDFont() const override { return true; }

    const GooString* getCollection() const {
        return fakeCollection.get();
    }

    int getNextChar(const char* s, int len, CharCode* code,
                    const Unicode** u, int* uLen, double* dx,
                    double* dy, double* ox, double* oy) const override {
        return 0;
    }

    WritingMode getWMode() const override { return writingModeHorizLR; }
    const CharCodeToUnicode* getToUnicode() const override { return nullptr; }

    ~FakeGfxCIDFont() override = default;
};

// Non-CID font mock for testing non-CID path
class FakeGfxFont : public GfxFont {
public:
    FakeGfxFont()
        : GfxFont("tag", Ref::INVALID(), std::optional<std::string>("TestFont"), fontType1, Ref::INVALID())
    {
    }

    bool isCIDFont() const override { return false; }

    int getNextChar(const char* s, int len, CharCode* code,
                    const Unicode** u, int* uLen, double* dx,
                    double* dy, double* ox, double* oy) const override {
        return 0;
    }

    const CharCodeToUnicode* getToUnicode() const override { return nullptr; }

    ~FakeGfxFont() override = default;
};

class GetFontLangTest_1900 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Adobe-GB1 collection returns Simplified Chinese
TEST_F(GetFontLangTest_1900, AdobeGB1ReturnsSimplifiedChinese_1900) {
    FakeGfxCIDFont font("Adobe-GB1");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "zh-cn");
}

// Test: Adobe-CNS1 collection returns Traditional Chinese
TEST_F(GetFontLangTest_1900, AdobeCNS1ReturnsTraditionalChinese_1900) {
    FakeGfxCIDFont font("Adobe-CNS1");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "zh-tw");
}

// Test: Adobe-Japan1 collection returns Japanese
TEST_F(GetFontLangTest_1900, AdobeJapan1ReturnsJapanese_1900) {
    FakeGfxCIDFont font("Adobe-Japan1");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "ja");
}

// Test: Adobe-Japan2 collection returns Japanese
TEST_F(GetFontLangTest_1900, AdobeJapan2ReturnsJapanese_1900) {
    FakeGfxCIDFont font("Adobe-Japan2");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "ja");
}

// Test: Adobe-Korea1 collection returns Korean
TEST_F(GetFontLangTest_1900, AdobeKorea1ReturnsKorean_1900) {
    FakeGfxCIDFont font("Adobe-Korea1");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "ko");
}

// Test: Adobe-UCS collection returns "xx"
TEST_F(GetFontLangTest_1900, AdobeUCSReturnsXX_1900) {
    FakeGfxCIDFont font("Adobe-UCS");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "xx");
}

// Test: Adobe-Identity collection returns "xx"
TEST_F(GetFontLangTest_1900, AdobeIdentityReturnsXX_1900) {
    FakeGfxCIDFont font("Adobe-Identity");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "xx");
}

// Test: Unknown collection returns "xx" (and triggers error)
TEST_F(GetFontLangTest_1900, UnknownCollectionReturnsXX_1900) {
    FakeGfxCIDFont font("Adobe-Unknown");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "xx");
}

// Test: Null collection on CID font returns "xx"
TEST_F(GetFontLangTest_1900, NullCollectionReturnsXX_1900) {
    FakeGfxCIDFont font(nullptr);
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "xx");
}

// Test: Non-CID font returns "xx"
TEST_F(GetFontLangTest_1900, NonCIDFontReturnsXX_1900) {
    FakeGfxFont font;
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "xx");
}

// Test: Empty collection string returns "xx"
TEST_F(GetFontLangTest_1900, EmptyCollectionReturnsXX_1900) {
    FakeGfxCIDFont font("");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "xx");
}

// Test: Collection with extra characters doesn't match known collections
TEST_F(GetFontLangTest_1900, CollectionWithExtraCharsReturnsXX_1900) {
    FakeGfxCIDFont font("Adobe-GB1-Extra");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "xx");
}

// Test: Case sensitivity - lowercase doesn't match
TEST_F(GetFontLangTest_1900, CaseSensitiveCollectionReturnsXX_1900) {
    FakeGfxCIDFont font("adobe-gb1");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "xx");
}

// Test: Partial match doesn't return language
TEST_F(GetFontLangTest_1900, PartialMatchReturnsXX_1900) {
    FakeGfxCIDFont font("Adobe-GB");
    const char* result = getFontLang(font);
    EXPECT_STREQ(result, "xx");
}

// Test: Return value is a valid non-null pointer for all paths
TEST_F(GetFontLangTest_1900, ReturnValueIsNeverNull_1900) {
    FakeGfxFont nonCidFont;
    EXPECT_NE(getFontLang(nonCidFont), nullptr);

    FakeGfxCIDFont cidFontNull(nullptr);
    EXPECT_NE(getFontLang(cidFontNull), nullptr);

    FakeGfxCIDFont cidFontKnown("Adobe-Japan1");
    EXPECT_NE(getFontLang(cidFontKnown), nullptr);

    FakeGfxCIDFont cidFontUnknown("SomeRandom");
    EXPECT_NE(getFontLang(cidFontUnknown), nullptr);
}
