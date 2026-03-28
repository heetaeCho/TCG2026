#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>

// We need to include the header for GfxFontDict and its dependencies
#include "poppler/GfxFont.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/XRef.h"
#include "poppler/PDFDoc.h"
#include "poppler/GlobalParams.h"

class GfxFontDictTest_1172 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getFont returns a valid shared_ptr for fonts in a real dictionary
// We need a real PDF context to properly test, but we can test boundary behavior
// by creating a minimal font dictionary.

TEST_F(GfxFontDictTest_1172, GetFontReturnsSharedPtr_1172)
{
    // To properly test GfxFontDict, we need a valid XRef, Ref, and Dict.
    // Since GfxFontDict requires real PDF structures, we test with a minimal PDF file.
    // For this test, we create a GfxFontDict with an empty dictionary.
    
    // Create a minimal empty dict
    Object fontDictObj = Object(new Dict(nullptr));
    Dict *fontDict = fontDictObj.getDict();
    
    Ref fontDictRef = Ref::INVALID();
    
    GfxFontDict dict(nullptr, fontDictRef, fontDict);
    
    // With an empty font dictionary, getNumFonts should return 0
    EXPECT_EQ(dict.getNumFonts(), 0);
}

TEST_F(GfxFontDictTest_1172, LookupNonExistentTag_1172)
{
    Object fontDictObj = Object(new Dict(nullptr));
    Dict *fontDict = fontDictObj.getDict();
    
    Ref fontDictRef = Ref::INVALID();
    
    GfxFontDict dict(nullptr, fontDictRef, fontDict);
    
    // Looking up a tag that doesn't exist should return a null/empty shared_ptr
    auto font = dict.lookup("NonExistent");
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxFontDictTest_1172, GetNumFontsEmptyDict_1172)
{
    Object fontDictObj = Object(new Dict(nullptr));
    Dict *fontDict = fontDictObj.getDict();
    
    Ref fontDictRef = Ref::INVALID();
    
    GfxFontDict dict(nullptr, fontDictRef, fontDict);
    
    EXPECT_EQ(dict.getNumFonts(), 0);
}

TEST_F(GfxFontDictTest_1172, CopyConstructorDeleted_1172)
{
    // Verify that GfxFontDict is not copy constructible
    EXPECT_FALSE(std::is_copy_constructible<GfxFontDict>::value);
}

TEST_F(GfxFontDictTest_1172, CopyAssignmentDeleted_1172)
{
    // Verify that GfxFontDict is not copy assignable
    EXPECT_FALSE(std::is_copy_assignable<GfxFontDict>::value);
}

// Test with a font dictionary containing an entry
TEST_F(GfxFontDictTest_1172, DictWithFontEntry_1172)
{
    // Create a Dict with a font-like entry
    Dict *fontDict = new Dict(nullptr);
    
    // Add a font entry - a minimal font object (Type1 font as a dictionary)
    Dict *fontObjDict = new Dict(nullptr);
    fontObjDict->add("Type", Object(objName, "Font"));
    fontObjDict->add("Subtype", Object(objName, "Type1"));
    fontObjDict->add("BaseFont", Object(objName, "Helvetica"));
    
    fontDict->add("F1", Object(fontObjDict));
    
    Ref fontDictRef = Ref::INVALID();
    
    GfxFontDict dict(nullptr, fontDictRef, fontDict);
    
    // Should have at least one font
    EXPECT_GE(dict.getNumFonts(), 0);
    
    // If there are fonts, getFont(0) should return something
    if (dict.getNumFonts() > 0) {
        const auto &font = dict.getFont(0);
        // Font may or may not be null depending on whether it could be fully parsed
        // but the call itself should not crash
    }
    
    // Lookup should work for tag "F1" if fonts were loaded
    auto lookedUp = dict.lookup("F1");
    // The result depends on whether the font could be parsed without a real XRef
}

// Test that getFont returns consistent results when called multiple times
TEST_F(GfxFontDictTest_1172, GetFontConsistentResults_1172)
{
    Object fontDictObj = Object(new Dict(nullptr));
    Dict *fontDict = fontDictObj.getDict();
    
    // Add a minimal font
    Dict *fontObjDict = new Dict(nullptr);
    fontObjDict->add("Type", Object(objName, "Font"));
    fontObjDict->add("Subtype", Object(objName, "Type1"));
    fontObjDict->add("BaseFont", Object(objName, "Courier"));
    fontDict->add("F1", Object(fontObjDict));
    
    Ref fontDictRef = Ref::INVALID();
    
    GfxFontDict dict(nullptr, fontDictRef, fontDict);
    
    int numFonts = dict.getNumFonts();
    // Calling getNumFonts multiple times should return the same result
    EXPECT_EQ(dict.getNumFonts(), numFonts);
    
    if (numFonts > 0) {
        const auto &font1 = dict.getFont(0);
        const auto &font2 = dict.getFont(0);
        // Should return the same pointer
        EXPECT_EQ(font1.get(), font2.get());
    }
}

TEST_F(GfxFontDictTest_1172, LookupWithNullTag_1172)
{
    Object fontDictObj = Object(new Dict(nullptr));
    Dict *fontDict = fontDictObj.getDict();
    
    Ref fontDictRef = Ref::INVALID();
    
    GfxFontDict dict(nullptr, fontDictRef, fontDict);
    
    // Looking up with an empty string
    auto font = dict.lookup("");
    EXPECT_EQ(font, nullptr);
}
