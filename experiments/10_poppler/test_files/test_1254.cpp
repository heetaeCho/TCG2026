#include <gtest/gtest.h>

#include "QPainterOutputDev.h"

#include <array>



class QPainterOutputDevTest_1254 : public ::testing::Test {

protected:

    int painter;

    QPainterOutputDev* outputDev;



    void SetUp() override {

        painter = 0; // Initialize painter as needed

        outputDev = new QPainterOutputDev(&painter);

    }



    void TearDown() override {

        delete outputDev;

    }

};



TEST_F(QPainterOutputDevTest_1254, UseShadedFills_Type2_ReturnsTrue_1254) {

    EXPECT_TRUE(outputDev->useShadedFills(2));

}



TEST_F(QPainterOutputDevTest_1254, UseShadedFills_OtherTypes_ReturnsFalse_1254) {

    EXPECT_FALSE(outputDev->useShadedFills(0));

    EXPECT_FALSE(outputDev->useShadedFills(1));

    EXPECT_FALSE(outputDev->useShadedFills(3));

}



TEST_F(QPainterOutputDevTest_1254, UseDrawChar_ReturnsFalse_1254) {

    EXPECT_FALSE(outputDev->useDrawChar());

}



TEST_F(QPainterOutputDevTest_1254, UpsideDown_ReturnsFalse_1254) {

    EXPECT_FALSE(outputDev->upsideDown());

}



TEST_F(QPainterOutputDevTest_1254, InterpretType3Chars_ReturnsFalse_1254) {

    EXPECT_FALSE(outputDev->interpretType3Chars());

}
