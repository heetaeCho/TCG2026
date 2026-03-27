#include <gtest/gtest.h>

#include "poppler/Annot.h"



class AnnotAppearanceCharacsTest : public ::testing::Test {

protected:

    std::unique_ptr<Dict> dict;

    std::unique_ptr<AnnotAppearanceCharacs> annotCharacs;



    void SetUp() override {

        dict = std::make_unique<Dict>();

        annotCharacs = std::make_unique<AnnotAppearanceCharacs>(dict.get());

    }

};



TEST_F(AnnotAppearanceCharacsTest_765, GetBorderColor_Default_ReturnsNullptr_765) {

    EXPECT_EQ(annotCharacs->getBorderColor(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_765, SetAndGetBorderColor_ValidColor_ReturnsSameColor_765) {

    auto color = std::make_unique<AnnotColor>();

    annotCharacs->setBorderColor(std::move(color));

    EXPECT_NE(annotCharacs->getBorderColor(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_765, SetAndGetBackColor_ValidColor_ReturnsSameColor_765) {

    auto color = std::make_unique<AnnotColor>();

    annotCharacs->setBackColor(std::move(color));

    EXPECT_NE(annotCharacs->getBackColor(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_765, GetNormalCaption_Default_ReturnsNullptr_765) {

    EXPECT_EQ(annotCharacs->getNormalCaption(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_765, GetRolloverCaption_Default_ReturnsNullptr_765) {

    EXPECT_EQ(annotCharacs->getRolloverCaption(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_765, GetAlternateCaption_Default_ReturnsNullptr_765) {

    EXPECT_EQ(annotCharacs->getAlternateCaption(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_765, GetIconFit_Default_ReturnsNullptr_765) {

    EXPECT_EQ(annotCharacs->getIconFit(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_765, GetPosition_Default_ReturnsDefaultTextPos_765) {

    EXPECT_EQ(annotCharacs->getPosition(), AnnotAppearanceCharacsTextPos::defaultPos);

}
