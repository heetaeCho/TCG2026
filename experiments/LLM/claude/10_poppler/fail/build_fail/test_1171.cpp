#include <gtest/gtest.h>
#include <memory>

#include "GfxFont.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"

class GfxFontDictTest_1171 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

TEST_F(GfxFontDictTest_1171, EmptyDictHasZeroFonts_1171) {
    // Create an empty Dict object to pass as fontDict
    // Using a null XRef and empty dict should result in zero fonts
    Object dictObj = Object(new Dict(nullptr));
    Dict *emptyDict = dictObj.getDict();
    
    Ref fontDictRef = {0, 0};
    GfxFontDict fontDict(nullptr, fontDictRef, emptyDict);
    
    EXPECT_EQ(fontDict.getNumFonts(), 0);
}

TEST_F(GfxFontDictTest_1171, GetFontOnEmptyDict_1171) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *emptyDict = dictObj.getDict();
    
    Ref fontDictRef = {0, 0};
    GfxFontDict fontDict(nullptr, fontDictRef, emptyDict);
    
    // Accessing font at index 0 on empty dict - should return a null/empty shared_ptr
    // Based on typical implementations, getFont with out-of-range index returns empty ptr
    const std::shared_ptr<GfxFont> &font = fontDict.getFont(0);
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxFontDictTest_1171, LookupNonExistentTag_1171) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *emptyDict = dictObj.getDict();
    
    Ref fontDictRef = {0, 0};
    GfxFontDict fontDict(nullptr, fontDictRef, emptyDict);
    
    // Looking up a tag that doesn't exist should return null
    auto result = fontDict.lookup("NonExistentFont");
    EXPECT_EQ(result, nullptr);
}

TEST_F(GfxFontDictTest_1171, LookupNullTag_1171) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *emptyDict = dictObj.getDict();
    
    Ref fontDictRef = {0, 0};
    GfxFontDict fontDict(nullptr, fontDictRef, emptyDict);
    
    // Looking up a null tag
    auto result = fontDict.lookup(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(GfxFontDictTest_1171, GetNumFontsReturnsCorrectSize_1171) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *emptyDict = dictObj.getDict();
    
    Ref fontDictRef = {0, 0};
    GfxFontDict fontDict(nullptr, fontDictRef, emptyDict);
    
    int numFonts = fontDict.getNumFonts();
    EXPECT_GE(numFonts, 0);
}

TEST_F(GfxFontDictTest_1171, CopyConstructorDeleted_1171) {
    // Verify that GfxFontDict is not copy constructible
    EXPECT_FALSE(std::is_copy_constructible<GfxFontDict>::value);
}

TEST_F(GfxFontDictTest_1171, CopyAssignmentDeleted_1171) {
    // Verify that GfxFontDict is not copy assignable
    EXPECT_FALSE(std::is_copy_assignable<GfxFontDict>::value);
}

TEST_F(GfxFontDictTest_1171, GetFontNegativeIndex_1171) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *emptyDict = dictObj.getDict();
    
    Ref fontDictRef = {0, 0};
    GfxFontDict fontDict(nullptr, fontDictRef, emptyDict);
    
    // Negative index should return null/empty shared_ptr
    const std::shared_ptr<GfxFont> &font = fontDict.getFont(-1);
    EXPECT_EQ(font, nullptr);
}

TEST_F(GfxFontDictTest_1171, LookupEmptyStringTag_1171) {
    Object dictObj = Object(new Dict(nullptr));
    Dict *emptyDict = dictObj.getDict();
    
    Ref fontDictRef = {0, 0};
    GfxFontDict fontDict(nullptr, fontDictRef, emptyDict);
    
    auto result = fontDict.lookup("");
    EXPECT_EQ(result, nullptr);
}

TEST_F(GfxFontDictTest_1171, DictWithFontEntry_1171) {
    // Create a dict with a font reference entry
    Dict *fontDictRaw = new Dict(nullptr);
    
    // Add a font entry that is a reference (typical usage)
    // Since we have no valid XRef, the font creation will likely fail gracefully
    Object refObj = Object(static_cast<int>(1), static_cast<int>(0));
    fontDictRaw->add("F1", std::move(refObj));
    
    Object dictObj = Object(fontDictRaw);
    
    Ref fontDictRef = {0, 0};
    GfxFontDict fontDict(nullptr, fontDictRef, fontDictRaw);
    
    // There should be 1 entry in the dict, though the font may be null due to invalid XRef
    EXPECT_EQ(fontDict.getNumFonts(), 1);
}
