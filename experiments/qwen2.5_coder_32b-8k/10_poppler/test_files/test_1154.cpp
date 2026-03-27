#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"



using namespace testing;



class MockXRef : public XRef {

public:

    MOCK_METHOD(void, dummyMethod, (), (const));

};



class MockDict : public Dict {

public:

    MOCK_METHOD(void, dummyMethod, (), (const));

};



class MockPSOutputDev : public PSOutputDev {

public:

    MOCK_METHOD(void, dummyMethod, (), (const));

};



class GfxFontTest_1154 : public Test {

protected:

    MockXRef xref;

    MockDict fontDict;

    Ref id{1, 0};

    std::string tag = "SampleTag";

    GfxFontType type = gfxFontType1;

    Ref embFontID{2, 0};



    std::unique_ptr<GfxFont> createGfxFont(bool isItalicFlag) {

        class ConcreteGfxFont : public GfxFont {

        public:

            ConcreteGfxFont(const char *tagA, Ref idA, Dict *fontDictA, GfxFontType typeA, Ref embFontIDA)

                : GfxFont(tagA, idA, std::string{}, typeA, embFontIDA) {

                flags = isItalicFlag ? fontItalic : 0;

            }

        };

        return std::make_unique<ConcreteGfxFont>(tag.c_str(), id, &fontDict, type, embFontID);

    }

};



TEST_F(GfxFontTest_1154, IsItalic_ReturnsTrueWhenFlagSet_1154) {

    auto font = createGfxFont(true);

    EXPECT_TRUE(font->isItalic());

}



TEST_F(GfxFontTest_1154, IsItalic_ReturnsFalseWhenFlagNotSet_1154) {

    auto font = createGfxFont(false);

    EXPECT_FALSE(font->isItalic());

}



TEST_F(GfxFontTest_1154, GetTag_ReturnsExpectedValue_1154) {

    auto font = createGfxFont(true);

    EXPECT_EQ(font->getTag(), tag);

}



TEST_F(GfxFontTest_1154, GetID_ReturnsExpectedValue_1154) {

    auto font = createGfxFont(true);

    EXPECT_EQ(*font->getID(), id);

}



TEST_F(GfxFontTest_1154, IsOk_DefaultImplementation_ReturnsTrue_1154) {

    auto font = createGfxFont(true);

    EXPECT_TRUE(font->isOk());

}



TEST_F(GfxFontTest_1154, GetFontMatrix_DefaultImplementation_ReturnsEmptyArray_1154) {

    auto font = createGfxFont(true);

    EXPECT_EQ(font->getFontMatrix(), std::array<double, 6>{0.0, 0.0, 0.0, 0.0, 0.0, 0.0});

}



TEST_F(GfxFontTest_1154, GetFontBBox_DefaultImplementation_ReturnsEmptyArray_1154) {

    auto font = createGfxFont(true);

    EXPECT_EQ(font->getFontBBox(), std::array<double, 4>{0.0, 0.0, 0.0, 0.0});

}



TEST_F(GfxFontTest_1154, GetAscent_DefaultImplementation_ReturnsZero_1154) {

    auto font = createGfxFont(true);

    EXPECT_EQ(font->getAscent(), 0.0);

}



TEST_F(GfxFontTest_1154, GetDescent_DefaultImplementation_ReturnsZero_1154) {

    auto font = createGfxFont(true);

    EXPECT_EQ(font->getDescent(), 0.0);

}



TEST_F(GfxFontTest_1154, IsCIDFont_DefaultImplementation_ReturnsFalse_1154) {

    auto font = createGfxFont(true);

    EXPECT_FALSE(font->isCIDFont());

}
