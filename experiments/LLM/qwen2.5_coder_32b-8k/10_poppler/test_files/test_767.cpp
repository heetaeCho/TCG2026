#include <gtest/gtest.h>

#include "Annot.h"



class AnnotAppearanceCharacsTest_767 : public ::testing::Test {

protected:

    std::unique_ptr<Dict> dict;

    std::unique_ptr<AnnotAppearanceCharacs> annotAppearanceCharacs;



    void SetUp() override {

        dict = std::make_unique<Dict>();

        annotAppearanceCharacs = std::make_unique<AnnotAppearanceCharacs>(dict.get());

    }

};



TEST_F(AnnotAppearanceCharacsTest_767, GetBackColor_ReturnsNullPointer_767) {

    EXPECT_EQ(nullptr, annotAppearanceCharacs->getBackColor());

}



TEST_F(AnnotAppearanceCharacsTest_767, SetAndGetBackColor_NormalOperation_767) {

    auto color = std::make_unique<AnnotColor>();

    const AnnotColor* originalColorPtr = color.get();

    annotAppearanceCharacs->setBackColor(std::move(color));

    EXPECT_EQ(originalColorPtr, annotAppearanceCharacs->getBackColor());

}



TEST_F(AnnotAppearanceCharacsTest_767, SetAndGetBackColor_MultipleTimes_767) {

    auto color1 = std::make_unique<AnnotColor>();

    const AnnotColor* originalColor1Ptr = color1.get();

    annotAppearanceCharacs->setBackColor(std::move(color1));

    EXPECT_EQ(originalColor1Ptr, annotAppearanceCharacs->getBackColor());



    auto color2 = std::make_unique<AnnotColor>();

    const AnnotColor* originalColor2Ptr = color2.get();

    annotAppearanceCharacs->setBackColor(std::move(color2));

    EXPECT_EQ(originalColor2Ptr, annotAppearanceCharacs->getBackColor());

}



TEST_F(AnnotAppearanceCharacsTest_767, SetBackColor_AfterMove_767) {

    auto color1 = std::make_unique<AnnotColor>();

    const AnnotColor* originalColorPtr = color1.get();

    annotAppearanceCharacs->setBackColor(std::move(color1));

    EXPECT_EQ(originalColorPtr, annotAppearanceCharacs->getBackColor());



    auto color2 = std::make_unique<AnnotColor>();

    annotAppearanceCharacs->setBackColor(std::move(color2));

    EXPECT_NE(originalColorPtr, annotAppearanceCharacs->getBackColor());

}



TEST_F(AnnotAppearanceCharacsTest_767, SetBackColor_NullPointer_767) {

    annotAppearanceCharacs->setBackColor(nullptr);

    EXPECT_EQ(nullptr, annotAppearanceCharacs->getBackColor());

}
