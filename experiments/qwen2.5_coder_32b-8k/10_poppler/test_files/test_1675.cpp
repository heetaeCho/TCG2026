#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/MarkedContentOutputDev.h"

#include <memory>



class MarkedContentOutputDevTest : public ::testing::Test {

protected:

    std::unique_ptr<MarkedContentOutputDev> markedContentOutputDev;



    void SetUp() override {

        Object stmObj; // Assuming Object is default constructible for this test

        markedContentOutputDev = std::make_unique<MarkedContentOutputDev>(0, stmObj);

    }

};



TEST_F(MarkedContentOutputDevTest_1675, UpsideDown_ReturnsTrue_1675) {

    EXPECT_TRUE(markedContentOutputDev->upsideDown());

}



TEST_F(MarkedContentOutputDevTest_1675, IsOk_DefaultState_ReturnsTrue_1675) {

    EXPECT_TRUE(markedContentOutputDev->isOk());

}



TEST_F(MarkedContentOutputDevTest_1675, UseDrawChar_DefaultState_ReturnsFalse_1675) {

    EXPECT_FALSE(markedContentOutputDev->useDrawChar());

}



TEST_F(MarkedContentOutputDevTest_1675, InterpretType3Chars_DefaultState_ReturnsFalse_1675) {

    EXPECT_FALSE(markedContentOutputDev->interpretType3Chars());

}



TEST_F(MarkedContentOutputDevTest_1675, NeedNonText_DefaultState_ReturnsFalse_1675) {

    EXPECT_FALSE(markedContentOutputDev->needNonText());

}



TEST_F(MarkedContentOutputDevTest_1675, NeedCharCount_DefaultState_ReturnsFalse_1675) {

    EXPECT_FALSE(markedContentOutputDev->needCharCount());

}
