#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Annot.h"



class DefaultAppearanceTest_757 : public ::testing::Test {

protected:

    std::unique_ptr<DefaultAppearance> defaultAppearance;



    void SetUp() override {

        defaultAppearance = std::make_unique<DefaultAppearance>("Helvetica", 12.0, std::make_unique<AnnotColor>());

    }

};



TEST_F(DefaultAppearanceTest_757, GetFontPtSize_ReturnsCorrectValue_757) {

    EXPECT_DOUBLE_EQ(defaultAppearance->getFontPtSize(), 12.0);

}



TEST_F(DefaultAppearanceTest_757, SetFontPtSize_UpdatesValue_757) {

    defaultAppearance->setFontPtSize(14.0);

    EXPECT_DOUBLE_EQ(defaultAppearance->getFontPtSize(), 14.0);

}



TEST_F(DefaultAppearanceTest_757, GetFontName_ReturnsCorrectValue_757) {

    EXPECT_EQ(defaultAppearance->getFontName(), "Helvetica");

}



TEST_F(DefaultAppearanceTest_757, SetFontName_UpdatesValue_757) {

    defaultAppearance->setFontName("Times-Roman");

    EXPECT_EQ(defaultAppearance->getFontName(), "Times-Roman");

}



TEST_F(DefaultAppearanceTest_757, GetFontColor_ReturnsCorrectPointer_757) {

    EXPECT_NE(defaultAppearance->getFontColor(), nullptr);

}
