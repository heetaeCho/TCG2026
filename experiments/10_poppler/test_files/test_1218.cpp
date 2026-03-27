#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



using namespace testing;



class TextOutputDevTest_1218 : public ::testing::Test {

protected:

    TextOutputDev* textOutputDev;



    void SetUp() override {

        textOutputDev = new TextOutputDev(nullptr, nullptr, false, 0.0, false, false);

    }



    void TearDown() override {

        delete textOutputDev;

    }

};



TEST_F(TextOutputDevTest_1218, UpsideDown_ReturnsTrue_1218) {

    EXPECT_TRUE(textOutputDev->upsideDown());

}



TEST_F(TextOutputDevTest_1218, UseDrawChar_DefaultValue_1218) {

    EXPECT_FALSE(textOutputDev->useDrawChar());

}



TEST_F(TextOutputDevTest_1218, InterpretType3Chars_DefaultValue_1218) {

    EXPECT_TRUE(textOutputDev->interpretType3Chars());

}



TEST_F(TextOutputDevTest_1218, NeedNonText_DefaultValue_1218) {

    EXPECT_FALSE(textOutputDev->needNonText());

}



TEST_F(TextOutputDevTest_1218, NeedCharCount_DefaultValue_1218) {

    EXPECT_FALSE(textOutputDev->needCharCount());

}



TEST_F(TextOutputDevTest_1218, IsOk_ReturnsTrue_1218) {

    EXPECT_TRUE(textOutputDev->isOk());

}



TEST_F(TextOutputDevTest_1218, GetMinColSpacing1_DefaultValue_1218) {

    EXPECT_DOUBLE_EQ(0.0, textOutputDev->getMinColSpacing1());

}



TEST_F(TextOutputDevTest_1218, SetMinColSpacing1_NewValue_1218) {

    double newValue = 1.5;

    textOutputDev->setMinColSpacing1(newValue);

    EXPECT_DOUBLE_EQ(newValue, textOutputDev->getMinColSpacing1());

}
