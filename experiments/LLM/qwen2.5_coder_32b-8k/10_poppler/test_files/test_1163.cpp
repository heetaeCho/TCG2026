#include <gtest/gtest.h>

#include "GfxFont.h"



class Gfx8BitFontTest_1163 : public ::testing::Test {

protected:

    XRef xref;

    Ref id;

    Dict fontDict;



    std::unique_ptr<Gfx8BitFont> font;



    void SetUp() override {

        font = std::make_unique<Gfx8BitFont>(&xref, "tag", id, "name", gfxFontType1, Ref(), &fontDict);

    }

};



TEST_F(Gfx8BitFontTest_1163, GetEncoding_ReturnsValidPointer_1163) {

    char** encoding = font->getEncoding();

    EXPECT_NE(encoding, nullptr);

}



TEST_F(Gfx8BitFontTest_1163, GetHasEncoding_ReturnsFalseByDefault_1163) {

    bool hasEncoding = font->getHasEncoding();

    EXPECT_FALSE(hasEncoding);

}



TEST_F(Gfx8BitFontTest_1163, GetUsesMacRomanEnc_ReturnsFalseByDefault_1163) {

    bool usesMacRomanEnc = font->getUsesMacRomanEnc();

    EXPECT_FALSE(usesMacRomanEnc);

}



TEST_F(Gfx8BitFontTest_1163, GetWidth_ReturnsValidDouble_1163) {

    double width = font->getWidth(0x20); // space character

    EXPECT_GE(width, 0.0);

}



TEST_F(Gfx8BitFontTest_1163, GetCharName_ReturnsNonEmptyStringForValidCode_1163) {

    const char* name = font->getCharName(0x20); // space character

    EXPECT_NE(name, nullptr);

    EXPECT_FALSE(std::string(name).empty());

}



TEST_F(Gfx8BitFontTest_1163, GetCharProc_ReturnsNonEmptyObjectForValidCode_1163) {

    Object charProc = font->getCharProc(0x20); // space character

    EXPECT_FALSE(charProc.isNull());

}



TEST_F(Gfx8BitFontTest_1163, GetCharProcNF_ReturnsNonEmptyObjectForValidCode_1163) {

    Object charProcNF = font->getCharProcNF(0x20); // space character

    EXPECT_FALSE(charProcNF.isNull());

}



TEST_F(Gfx8BitFontTest_1163, GetResources_ReturnsNonNullPointer_1163) {

    Dict* resources = font->getResources();

    EXPECT_NE(resources, nullptr);

}
