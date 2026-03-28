#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"



using namespace ::testing;



class GfxFontTest_1148 : public Test {

protected:

    Ref validEmbFontID;

    Ref invalidEmbFontID;



    void SetUp() override {

        validEmbFontID = Ref{42, 0};

        invalidEmbFontID = Ref::INVALID();

    }



    std::unique_ptr<GfxFont> createGfxFontWithEmbeddedFont(Ref embFontID) {

        return std::make_unique<GfxFont>("testTag", Ref{1, 0}, "TestName", gfxFontType1, embFontID);

    }

};



TEST_F(GfxFontTest_1148, InvalidateEmbeddedFont_ValidID_ReturnsTrue_1148) {

    auto font = createGfxFontWithEmbeddedFont(validEmbFontID);

    EXPECT_TRUE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1148, InvalidateEmbeddedFont_InvalidID_ReturnsFalse_1148) {

    auto font = createGfxFontWithEmbeddedFont(invalidEmbFontID);

    EXPECT_FALSE(font->invalidateEmbeddedFont());

}



TEST_F(GfxFontTest_1148, InvalidateEmbeddedFont_IdSetToInvalid_AfterInvalidate_1148) {

    auto font = createGfxFontWithEmbeddedFont(validEmbFontID);

    font->invalidateEmbeddedFont();

    Ref embFontID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embFontID));

}



TEST_F(GfxFontTest_1148, InvalidateEmbeddedFont_IdAlreadyInvalid_NoChange_1148) {

    auto font = createGfxFontWithEmbeddedFont(invalidEmbFontID);

    font->invalidateEmbeddedFont();

    Ref embFontID;

    EXPECT_FALSE(font->getEmbeddedFontID(&embFontID));

}
