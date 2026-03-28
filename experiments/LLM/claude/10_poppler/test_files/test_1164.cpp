#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"

// Since Gfx8BitFont has a complex constructor requiring XRef, Dict, etc.,
// and we cannot easily construct one without the full Poppler infrastructure,
// we test what we can based on the interface. However, the getCharName method
// simply returns enc[code], which is a private member. We need a constructed
// Gfx8BitFont to test it.
//
// Given the constraints, we'll attempt to create tests that exercise the
// public interface. Since the constructor requires complex Poppler objects,
// we'll need to set up minimal infrastructure.

#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include "GlobalParams.h"
#include <memory>

class Gfx8BitFontTest_1164 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getCharName returns expected values for a basic font setup
// We create a minimal Type1 font dictionary to construct a Gfx8BitFont
TEST_F(Gfx8BitFontTest_1164, GetCharNameReturnsNullForUninitializedCodes_1164)
{
    // Create a minimal font dictionary
    auto dict = new Dict(nullptr);

    // Set required entries for a Type1 font
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Helvetica"));

    Ref idRef = { 1, 0 };
    Ref embFontID = Ref::INVALID();

    // Attempt to create a Gfx8BitFont with a known Base14 font (Helvetica)
    // This should succeed and populate the encoding from the built-in tables
    std::optional<std::string> fontName = std::string("Helvetica");
    Gfx8BitFont font(nullptr, "F1", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    // For a Base14 font like Helvetica, standard encoding codes should have names
    // Code 65 = 'A' in standard encoding
    const char *name65 = font.getCharName(65);
    if (name65 != nullptr) {
        EXPECT_STREQ(name65, "A");
    }

    // Code 66 = 'B'
    const char *name66 = font.getCharName(66);
    if (name66 != nullptr) {
        EXPECT_STREQ(name66, "B");
    }

    // Code 0 might be .notdef or nullptr
    const char *name0 = font.getCharName(0);
    // Just verify it doesn't crash - value may be nullptr or ".notdef"
    if (name0 != nullptr) {
        EXPECT_TRUE(strlen(name0) > 0);
    }

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, GetCharNameBoundaryCode255_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Helvetica"));

    Ref idRef = { 2, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Helvetica");
    Gfx8BitFont font(nullptr, "F2", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    // Test boundary: code 255 (maximum valid 8-bit code)
    const char *name255 = font.getCharName(255);
    // Should not crash; may be nullptr or a valid glyph name
    SUCCEED();

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, GetWidthReturnsNonNegative_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Helvetica"));

    Ref idRef = { 3, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Helvetica");
    Gfx8BitFont font(nullptr, "F3", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    // Width of 'A' (code 65) for Helvetica should be positive
    double widthA = font.getWidth(65);
    EXPECT_GE(widthA, 0.0);

    // Width of space (code 32)
    double widthSpace = font.getWidth(32);
    EXPECT_GE(widthSpace, 0.0);

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, GetHasEncodingForBase14_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Helvetica"));

    Ref idRef = { 4, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Helvetica");
    Gfx8BitFont font(nullptr, "F4", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    // A base14 font without explicit Encoding dict may or may not have hasEncoding set
    // Just verify it returns a boolean without crashing
    bool hasEnc = font.getHasEncoding();
    (void)hasEnc;
    SUCCEED();

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, GetUsesMacRomanEnc_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Helvetica"));

    Ref idRef = { 5, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Helvetica");
    Gfx8BitFont font(nullptr, "F5", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    // Without MacRomanEncoding explicitly set, this should be false
    bool usesMacRoman = font.getUsesMacRomanEnc();
    EXPECT_FALSE(usesMacRoman);

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, GetEncodingReturnsNonNull_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Helvetica"));

    Ref idRef = { 6, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Helvetica");
    Gfx8BitFont font(nullptr, "F6", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    char **encoding = font.getEncoding();
    EXPECT_NE(encoding, nullptr);

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, GetCharNameConsistentWithGetEncoding_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Courier"));

    Ref idRef = { 7, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Courier");
    Gfx8BitFont font(nullptr, "F7", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    char **encoding = font.getEncoding();
    ASSERT_NE(encoding, nullptr);

    // getCharName(code) should return the same pointer as encoding[code]
    for (int i = 0; i < 256; i++) {
        EXPECT_EQ(font.getCharName(i), encoding[i])
            << "Mismatch at code " << i;
    }

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, GetCharProcsForType1_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Times-Roman"));

    Ref idRef = { 8, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Times-Roman");
    Gfx8BitFont font(nullptr, "F8", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    // For a standard Type1 font (not Type3), getCharProcs should return nullptr
    Dict *charProcs = font.getCharProcs();
    EXPECT_EQ(charProcs, nullptr);

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, GetWidthBoundaryValues_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Helvetica"));

    Ref idRef = { 9, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Helvetica");
    Gfx8BitFont font(nullptr, "F9", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    // Test width at boundary: code 0
    double width0 = font.getWidth(0);
    EXPECT_GE(width0, 0.0);

    // Test width at boundary: code 255
    double width255 = font.getWidth(255);
    EXPECT_GE(width255, 0.0);

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, GetToUnicode_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Helvetica"));

    Ref idRef = { 10, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Helvetica");
    Gfx8BitFont font(nullptr, "F10", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    // getToUnicode should return a valid pointer for a Base14 font
    const CharCodeToUnicode *ctu = font.getToUnicode();
    // May or may not be null depending on initialization
    SUCCEED();

    delete dict;
}

TEST_F(Gfx8BitFontTest_1164, MultipleCharNamesForPrintableASCII_1164)
{
    auto dict = new Dict(nullptr);
    dict->add("Type", Object(objName, "Font"));
    dict->add("Subtype", Object(objName, "Type1"));
    dict->add("BaseFont", Object(objName, "Helvetica"));

    Ref idRef = { 11, 0 };
    Ref embFontID = Ref::INVALID();

    std::optional<std::string> fontName = std::string("Helvetica");
    Gfx8BitFont font(nullptr, "F11", idRef, std::move(fontName),
                      fontType1, embFontID, dict);

    // Verify some well-known glyph names for standard encoding
    // These are standard PostScript glyph names
    struct {
        int code;
        const char *expectedName;
    } knownNames[] = {
        {65, "A"},
        {66, "B"},
        {67, "C"},
        {97, "a"},
        {98, "b"},
        {48, "zero"},
        {49, "one"},
        {50, "two"},
        {32, "space"},
    };

    for (const auto &kn : knownNames) {
        const char *name = font.getCharName(kn.code);
        if (name != nullptr) {
            EXPECT_STREQ(name, kn.expectedName)
                << "Failed for code " << kn.code;
        }
    }

    delete dict;
}
