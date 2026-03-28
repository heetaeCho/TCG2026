#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/MarkedContentOutputDev.h"



class MarkedContentOutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<MarkedContentOutputDev> dev;



    void SetUp() override {

        Object stmObj; // Assuming Object is default constructible for this test

        dev = std::make_unique<MarkedContentOutputDev>(0, stmObj);

    }

};



TEST_F(MarkedContentOutputDevTest_1677, interpretType3Chars_ReturnsFalse_1677) {

    EXPECT_FALSE(dev->interpretType3Chars());

}



TEST_F(MarkedContentOutputDevTest_1677, isOk_DefaultConstructor_ReturnsTrue_1677) {

    EXPECT_TRUE(dev->isOk());

}



TEST_F(MarkedContentOutputDevTest_1677, upsideDown_DefaultConstructor_ReturnsFalse_1677) {

    EXPECT_FALSE(dev->upsideDown());

}



TEST_F(MarkedContentOutputDevTest_1677, useDrawChar_DefaultConstructor_ReturnsFalse_1677) {

    EXPECT_FALSE(dev->useDrawChar());

}



TEST_F(MarkedContentOutputDevTest_1677, needNonText_DefaultConstructor_ReturnsFalse_1677) {

    EXPECT_FALSE(dev->needNonText());

}



TEST_F(MarkedContentOutputDevTest_1677, needCharCount_DefaultConstructor_ReturnsFalse_1677) {

    EXPECT_FALSE(dev->needCharCount());

}



TEST_F(MarkedContentOutputDevTest_1677, getTextSpans_DefaultConstructor_ReturnsZero_1677) {

    EXPECT_EQ(0, dev->getTextSpans());

}
