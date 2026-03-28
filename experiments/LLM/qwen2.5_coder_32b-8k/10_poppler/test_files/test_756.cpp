#include <gtest/gtest.h>

#include "Annot.h"



class DefaultAppearanceTest : public ::testing::Test {

protected:

    DefaultAppearance* defaultAppearance;



    void SetUp() override {

        defaultAppearance = new DefaultAppearance("Helvetica", 12.0, std::make_unique<AnnotColor>());

    }



    void TearDown() override {

        delete defaultAppearance;

    }

};



TEST_F(DefaultAppearanceTest_756, GetFontName_ReturnsCorrectFontName_756) {

    EXPECT_EQ(defaultAppearance->getFontName(), "Helvetica");

}



TEST_F(DefaultAppearanceTest_756, SetFontName_ChangesFontName_756) {

    defaultAppearance->setFontName("Arial");

    EXPECT_EQ(defaultAppearance->getFontName(), "Arial");

}



TEST_F(DefaultAppearanceTest_756, GetFontPtSize_ReturnsCorrectFontSize_756) {

    EXPECT_DOUBLE_EQ(defaultAppearance->getFontPtSize(), 12.0);

}



TEST_F(DefaultAppearanceTest_756, SetFontPtSize_ChangesFontSize_756) {

    defaultAppearance->setFontPtSize(14.0);

    EXPECT_DOUBLE_EQ(defaultAppearance->getFontPtSize(), 14.0);

}



TEST_F(DefaultAppearanceTest_756, GetFontColor_ReturnsCorrectFontColor_756) {

    auto fontColor = std::make_unique<AnnotColor>();

    defaultAppearance->setFontColor(std::move(fontColor));

    EXPECT_NE(defaultAppearance->getFontColor(), nullptr);

}
