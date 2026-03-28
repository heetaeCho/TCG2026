#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/TextOutputDev.h"



class TextOutputDevTest : public ::testing::Test {

protected:

    TextOutputDev* textOutputDev;



    void SetUp() override {

        textOutputDev = new TextOutputDev(nullptr, nullptr, false, 0.0, false, false);

    }



    void TearDown() override {

        delete textOutputDev;

    }

};



TEST_F(TextOutputDevTest_1226, GetMinColSpacing1_DefaultValue_1226) {

    EXPECT_DOUBLE_EQ(0.0, textOutputDev->getMinColSpacing1());

}



TEST_F(TextOutputDevTest_1226, SetAndGetMinColSpacing1_PositiveValue_1226) {

    double testValue = 5.0;

    textOutputDev->setMinColSpacing1(testValue);

    EXPECT_DOUBLE_EQ(testValue, textOutputDev->getMinColSpacing1());

}



TEST_F(TextOutputDevTest_1226, SetAndGetMinColSpacing1_ZeroValue_1226) {

    double testValue = 0.0;

    textOutputDev->setMinColSpacing1(testValue);

    EXPECT_DOUBLE_EQ(testValue, textOutputDev->getMinColSpacing1());

}



TEST_F(TextOutputDevTest_1226, SetAndGetMinColSpacing1_NegativeValue_1226) {

    double testValue = -5.0;

    textOutputDev->setMinColSpacing1(testValue);

    EXPECT_DOUBLE_EQ(testValue, textOutputDev->getMinColSpacing1());

}
