#include <gtest/gtest.h>

#include "Annot.h"



class AnnotAppearanceCharacsTest_772 : public ::testing::Test {

protected:

    std::unique_ptr<Dict> dict;

    std::unique_ptr<AnnotAppearanceCharacs> annotAppearance;



    void SetUp() override {

        dict = std::make_unique<Dict>();

        annotAppearance = std::make_unique<AnnotAppearanceCharacs>(dict.get());

    }

};



TEST_F(AnnotAppearanceCharacsTest_772, GetIconFit_ReturnsNonNullPointer_772) {

    const AnnotIconFit* iconFit = annotAppearance->getIconFit();

    EXPECT_NE(iconFit, nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_772, GetRotation_DefaultValueIsZero_772) {

    int rotation = annotAppearance->getRotation();

    EXPECT_EQ(rotation, 0);

}



TEST_F(AnnotAppearanceCharacsTest_772, GetBorderColor_ReturnsNonNullPointer_772) {

    const AnnotColor* borderColor = annotAppearance->getBorderColor();

    EXPECT_NE(borderColor, nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_772, GetBackColor_ReturnsNonNullPointer_772) {

    const AnnotColor* backColor = annotAppearance->getBackColor();

    EXPECT_NE(backColor, nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_772, GetNormalCaption_ReturnsNonNullPointer_772) {

    const GooString* normalCaption = annotAppearance->getNormalCaption();

    EXPECT_NE(normalCaption, nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_772, GetRolloverCaption_ReturnsNonNullPointer_772) {

    const GooString* rolloverCaption = annotAppearance->getRolloverCaption();

    EXPECT_NE(rolloverCaption, nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_772, GetAlternateCaption_ReturnsNonNullPointer_772) {

    const GooString* alternateCaption = annotAppearance->getAlternateCaption();

    EXPECT_NE(alternateCaption, nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_772, SetBorderColor_DoesNotCrash_772) {

    auto color = std::make_unique<AnnotColor>();

    EXPECT_NO_THROW(annotAppearance->setBorderColor(std::move(color)));

}



TEST_F(AnnotAppearanceCharacsTest_772, SetBackColor_DoesNotCrash_772) {

    auto color = std::make_unique<AnnotColor>();

    EXPECT_NO_THROW(annotAppearance->setBackColor(std::move(color)));

}
