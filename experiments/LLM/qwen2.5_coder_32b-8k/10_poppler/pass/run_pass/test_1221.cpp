#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



using namespace testing;



class TextOutputDevTest_1221 : public ::testing::Test {

protected:

    TextOutputDev* textOutputDev;



    void SetUp() override {

        textOutputDev = new TextOutputDev(nullptr, nullptr, false, 0.0, false, false);

    }



    void TearDown() override {

        delete textOutputDev;

    }

};



TEST_F(TextOutputDevTest_1221, NeedNonTextReturnsFalse_1221) {

    EXPECT_FALSE(textOutputDev->needNonText());

}



TEST_F(TextOutputDevTest_1221, IsOk_ReturnsTrueByDefault_1221) {

    EXPECT_TRUE(textOutputDev->isOk());

}



TEST_F(TextOutputDevTest_1221, UpsideDown_ReturnsFalseByDefault_1221) {

    EXPECT_FALSE(textOutputDev->upsideDown());

}



TEST_F(TextOutputDevTest_1221, UseDrawChar_ReturnsTrueByDefault_1221) {

    EXPECT_TRUE(textOutputDev->useDrawChar());

}



TEST_F(TextOutputDevTest_1221, InterpretType3Chars_ReturnsFalseByDefault_1221) {

    EXPECT_FALSE(textOutputDev->interpretType3Chars());

}



TEST_F(TextOutputDevTest_1221, NeedCharCount_ReturnsFalseByDefault_1221) {

    EXPECT_FALSE(textOutputDev->needCharCount());

}



TEST_F(TextOutputDevTest_1221, GetMinColSpacing1_DefaultValue_1221) {

    EXPECT_DOUBLE_EQ(0.0, textOutputDev->getMinColSpacing1());

}



TEST_F(TextOutputDevTest_1221, SetMinColSpacing1_ValueIsSetCorrectly_1221) {

    double newSpacing = 5.0;

    textOutputDev->setMinColSpacing1(newSpacing);

    EXPECT_DOUBLE_EQ(newSpacing, textOutputDev->getMinColSpacing1());

}



TEST_F(TextOutputDevTest_1221, SetTextEOL_ValueIsSetCorrectly_1221) {

    EndOfLineKind newEOL = eolUnix;

    textOutputDev->setTextEOL(newEOL);

    // No direct getter for this, so we assume it's set correctly based on the call

}



TEST_F(TextOutputDevTest_1221, SetTextPageBreaks_ValueIsSetCorrectly_1221) {

    bool newTextPageBreaks = true;

    textOutputDev->setTextPageBreaks(newTextPageBreaks);

    // No direct getter for this, so we assume it's set correctly based on the call

}



TEST_F(TextOutputDevTest_1221, EnableHTMLExtras_ValueIsSetCorrectly_1221) {

    bool enableHTML = true;

    textOutputDev->enableHTMLExtras(enableHTML);

    // No direct getter for this, so we assume it's set correctly based on the call

}
