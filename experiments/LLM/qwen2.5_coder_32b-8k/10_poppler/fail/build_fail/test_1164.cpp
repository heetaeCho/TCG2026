#include <gtest/gtest.h>

#include "GfxFont.h"



class Gfx8BitFontTest_1164 : public ::testing::Test {

protected:

    XRef xref;

    Ref id = {0, 0};

    Dict fontDict;



    std::optional<std::string> name = "ExampleName";

    GfxFontType type = gfxFontType1;

    Ref embFontID = {1, 0};



    Gfx8BitFont* font;



    void SetUp() override {

        font = new Gfx8BitFont(&xref, "tag", id, std::move(name), type, embFontID, &fontDict);

    }



    void TearDown() override {

        delete font;

    }

};



TEST_F(Gfx8BitFontTest_1164, GetCharName_ReturnsValidString_1164) {

    const char* name = font->getCharName(32); // Assuming code 32 has a valid name

    EXPECT_TRUE(name != nullptr);

}



TEST_F(Gfx8BitFontTest_1164, GetCharName_OutOfBounds_ReturnsNull_1164) {

    const char* name = font->getCharName(256); // Out of bounds code

    EXPECT_EQ(name, nullptr);

}



TEST_F(Gfx8BitFontTest_1164, GetHasEncoding_ReturnsFalse_ByDefault_1164) {

    bool hasEncoding = font->getHasEncoding();

    EXPECT_FALSE(hasEncoding);

}



TEST_F(Gfx8BitFontTest_1164, GetUsesMacRomanEnc_ReturnsFalse_ByDefault_1164) {

    bool usesMacRomanEnc = font->getUsesMacRomanEnc();

    EXPECT_FALSE(usesMacRomanEnc);

}



TEST_F(Gfx8BitFontTest_1164, GetWidth_ValidCode_ReturnsNonNegative_1164) {

    double width = font->getWidth(32); // Assuming code 32 has a valid width

    EXPECT_GE(width, 0.0);

}



TEST_F(Gfx8BitFontTest_1164, GetWidth_OutOfBounds_ReturnsZero_1164) {

    double width = font->getWidth(256); // Out of bounds code

    EXPECT_EQ(width, 0.0);

}
