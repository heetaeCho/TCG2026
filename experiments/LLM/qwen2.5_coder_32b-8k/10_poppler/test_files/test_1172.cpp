#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"



using namespace testing;



class GfxFontDictTest_1172 : public Test {

protected:

    XRef* xref = nullptr;

    Ref fontDictRef;

    Dict* fontDict = nullptr;

    std::shared_ptr<GfxFont> mockFont1 = std::make_shared<GfxFont>();

    std::shared_ptr<GfxFont> mockFont2 = std::make_shared<GfxFont>();



    GfxFontDictTest_1172() {

        // Mocking the necessary objects for construction

        xref = new XRef();

        fontDict = new Dict();

        fontDict->add("Font1", Object(mockFont1));

        fontDict->add("Font2", Object(mockFont2));

    }



    ~GfxFontDictTest_1172() {

        delete xref;

        delete fontDict;

    }



    GfxFontDict getInitializedFontDict() {

        return GfxFontDict(xref, fontDictRef, fontDict);

    }

};



TEST_F(GfxFontDictTest_1172, GetNumFonts_ReturnsCorrectCount_1172) {

    GfxFontDict fontDict = getInitializedFontDict();

    EXPECT_EQ(fontDict.getNumFonts(), 2);

}



TEST_F(GfxFontDictTest_1172, GetFont_ReturnsCorrectFont_1172) {

    GfxFontDict fontDict = getInitializedFontDict();

    EXPECT_EQ(fontDict.getFont(0), mockFont1);

    EXPECT_EQ(fontDict.getFont(1), mockFont2);

}



TEST_F(GfxFontDictTest_1172, GetFont_OutOfBounds_ReturnsNull_1172) {

    GfxFontDict fontDict = getInitializedFontDict();

    EXPECT_THROW(fontDict.getFont(2), std::out_of_range); // Assuming out of range throws an exception

}



TEST_F(GfxFontDictTest_1172, Lookup_ExistingTag_ReturnsCorrectFont_1172) {

    GfxFontDict fontDict = getInitializedFontDict();

    EXPECT_EQ(fontDict.lookup("Font1"), mockFont1);

    EXPECT_EQ(fontDict.lookup("Font2"), mockFont2);

}



TEST_F(GfxFontDictTest_1172, Lookup_NonExistingTag_ReturnsNull_1172) {

    GfxFontDict fontDict = getInitializedFontDict();

    EXPECT_EQ(fontDict.lookup("NonExistentTag"), nullptr);

}
