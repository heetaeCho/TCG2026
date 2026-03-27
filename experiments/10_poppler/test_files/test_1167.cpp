#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"



using namespace testing;



class Gfx8BitFontTest : public Test {

protected:

    XRef* mockXRef;

    Dict* mockDict;

    Ref idA = {1, 0};

    Ref embFontIDA = {2, 0};



    void SetUp() override {

        mockXRef = new XRef();

        mockDict = new Dict();

    }



    void TearDown() override {

        delete mockXRef;

        delete mockDict;

    }



    Gfx8BitFont createGfx8BitFont(const char* tagA, std::optional<std::string>&& nameA, GfxFontType typeA) {

        return Gfx8BitFont(mockXRef, tagA, idA, std::move(nameA), typeA, embFontIDA, mockDict);

    }



    Gfx8BitFont createGfx8BitFont(const char* tagA, int nameA, GfxFontType typeA) {

        return Gfx8BitFont(mockXRef, tagA, idA, std::move(nameA), typeA, embFontIDA, mockDict);

    }

};



TEST_F(Gfx8BitFontTest_1167, GetWidth_NormalOperation_1167) {

    auto name = "Arial";

    Gfx8BitFont font = createGfx8BitFont("Tag", std::move(name), gfxFontType1);

    unsigned char c = 'A';

    double width = font.getWidth(c);

    EXPECT_GE(width, 0.0); // Assuming width is non-negative

}



TEST_F(Gfx8BitFontTest_1167, GetWidth_BoundaryCondition_Min_1167) {

    auto name = "Arial";

    Gfx8BitFont font = createGfx8BitFont("Tag", std::move(name), gfxFontType1);

    unsigned char c = 0;

    double width = font.getWidth(c);

    EXPECT_GE(width, 0.0); // Assuming width is non-negative

}



TEST_F(Gfx8BitFontTest_1167, GetWidth_BoundaryCondition_Max_1167) {

    auto name = "Arial";

    Gfx8BitFont font = createGfx8BitFont("Tag", std::move(name), gfxFontType1);

    unsigned char c = 255;

    double width = font.getWidth(c);

    EXPECT_GE(width, 0.0); // Assuming width is non-negative

}



TEST_F(Gfx8BitFontTest_1167, GetWidth_ExceptionalCase_UnsupportedChar_1167) {

    auto name = "Arial";

    Gfx8BitFont font = createGfx8BitFont("Tag", std::move(name), gfxFontType1);

    unsigned char c = 256; // Invalid character

    EXPECT_THROW(font.getWidth(c), std::out_of_range); // Assuming it throws for invalid characters

}
