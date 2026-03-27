#include <gtest/gtest.h>

#include "Annot.h"



class AnnotAppearanceCharacsTest_771 : public ::testing::Test {

protected:

    std::unique_ptr<Dict> dict;

    std::unique_ptr<AnnotAppearanceCharacs> annotAppearanceCharacs;



    void SetUp() override {

        dict = std::make_unique<Dict>();

        annotAppearanceCharacs = std::make_unique<AnnotAppearanceCharacs>(dict.get());

    }

};



TEST_F(AnnotAppearanceCharacsTest_771, GetAlternateCaption_ReturnsNullPtrWhenNotSet_771) {

    EXPECT_EQ(annotAppearanceCharacs->getAlternateCaption(), nullptr);

}



TEST_F(AnnotAppearanceCharacsTest_771, GetAlternateCaption_ReturnsSetValue_771) {

    auto alternateCaption = std::make_unique<GooString>("test caption");

    annotAppearanceCharacs.reset(new AnnotAppearanceCharacs(dict.get()));

    annotAppearanceCharacs->alternateCaption = std::move(alternateCaption);

    EXPECT_STREQ(annotAppearanceCharacs->getAlternateCaption()->getCString(), "test caption");

}
