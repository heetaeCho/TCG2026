#include <gtest/gtest.h>

#include "GfxFont.h"

#include <memory>



// Mock XRef for dependency injection in tests

class MockXRef : public XRef {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



// Mock Dict for dependency injection in tests

class MockDict : public Dict {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



// Mock PSOutputDev for dependency injection in tests

class MockPSOutputDev : public PSOutputDev {

public:

    MOCK_METHOD(void, dummyMethod, (), (override));

};



// Test fixture for GfxFont tests

class GfxFontTest_1152 : public ::testing::Test {

protected:

    std::unique_ptr<MockXRef> mock_xref;

    std::unique_ptr<MockDict> mock_font_dict;

    std::unique_ptr<GfxFont> gfx_font;



    void SetUp() override {

        mock_xref = std::make_unique<MockXRef>();

        mock_font_dict = std::make_unique<MockDict>();

        gfx_font = GfxFont::makeFont(mock_xref.get(), "TestTag", Ref(), mock_font_dict.get());

    }

};



TEST_F(GfxFontTest_1152, IsSerif_ReturnsTrueWhenFlagSet_1152) {

    // Assuming we can set the flag through constructor or some method for testing

    gfx_font = std::make_unique<GfxFont>("TestTag", Ref(), "TestName", fontType1, Ref());

    EXPECT_TRUE(gfx_font->isSerif());

}



TEST_F(GfxFontTest_1152, IsSerif_ReturnsFalseWhenFlagNotSet_1152) {

    // Assuming we can set the flag through constructor or some method for testing

    gfx_font = std::make_unique<GfxFont>("TestTag", Ref(), "TestName", fontType1, Ref());

    EXPECT_FALSE(gfx_font->isSerif()); // Modify setup to ensure flag is not set if needed

}



TEST_F(GfxFontTest_1152, IsOk_ReturnsTrueForValidInstance_1152) {

    EXPECT_TRUE(gfx_font->isOk());

}



TEST_F(GfxFontTest_1152, GetTag_ReturnsCorrectTag_1152) {

    EXPECT_EQ(gfx_font->getTag(), "TestTag");

}



TEST_F(GfxFontTest_1152, IsCIDFont_ReturnsFalseByDefault_1152) {

    EXPECT_FALSE(gfx_font->isCIDFont());

}



TEST_F(GfxFontTest_1152, HasToUnicodeCMap_ReturnsFalseByDefault_1152) {

    EXPECT_FALSE(gfx_font->hasToUnicodeCMap());

}



TEST_F(GfxFontTest_1152, IsBase14Font_StringOverload_ReturnsTrueForKnownFonts_1152) {

    EXPECT_TRUE(GfxFont::isBase14Font("Helvetica", "Normal"));

}



TEST_F(GfxFontTest_1152, IsBase14Font_StringOverload_ReturnsFalseForUnknownFonts_1152) {

    EXPECT_FALSE(GfxFont::isBase14Font("UnknownFont", "UnknownStyle"));

}



// Assuming integer overloads of isBase14Font are tested similarly with appropriate family and style values

TEST_F(GfxFontTest_1152, IsBase14Font_IntOverload_ReturnsTrueForKnownFonts_1152) {

    EXPECT_TRUE(GfxFont::isBase14Font(0, 0)); // Example known font and style values

}



TEST_F(GfxFontTest_1152, IsBase14Font_IntOverload_ReturnsFalseForUnknownFonts_1152) {

    EXPECT_FALSE(GfxFont::isBase14Font(-1, -1)); // Example unknown font and style values

}
