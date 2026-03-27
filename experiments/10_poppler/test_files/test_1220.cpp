#include <gtest/gtest.h>

#include "TextOutputDev.h"

#include <memory>



using namespace std;



class TextOutputDevTest : public ::testing::Test {

protected:

    void SetUp() override {

        textOutputDev = make_unique<TextOutputDev>([](const char*, const Unicode*, int){}, nullptr, false, 0.0, false, false);

    }



    unique_ptr<TextOutputDev> textOutputDev;

};



TEST_F(TextOutputDevTest_1220, InterpretType3Chars_ReturnsFalse_1220) {

    EXPECT_FALSE(textOutputDev->interpretType3Chars());

}



TEST_F(TextOutputDevTest_1220, IsOk_DefaultConstructor_ReturnsTrue_1220) {

    EXPECT_TRUE(textOutputDev->isOk());

}



TEST_F(TextOutputDevTest_1220, UpsideDown_DefaultConstructor_ReturnsFalse_1220) {

    EXPECT_FALSE(textOutputDev->upsideDown());

}



TEST_F(TextOutputDevTest_1220, UseDrawChar_DefaultConstructor_ReturnsTrue_1220) {

    EXPECT_TRUE(textOutputDev->useDrawChar());

}



TEST_F(TextOutputDevTest_1220, NeedNonText_DefaultConstructor_ReturnsFalse_1220) {

    EXPECT_FALSE(textOutputDev->needNonText());

}



TEST_F(TextOutputDevTest_1220, NeedCharCount_DefaultConstructor_ReturnsFalse_1220) {

    EXPECT_FALSE(textOutputDev->needCharCount());

}



TEST_F(TextOutputDevTest_1220, GetMinColSpacing1_DefaultValue_ReturnsZero_1220) {

    EXPECT_EQ(0.0, textOutputDev->getMinColSpacing1());

}
