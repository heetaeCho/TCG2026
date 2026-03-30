#include <gtest/gtest.h>

#include "BBoxOutputDev.h"



class BBoxOutputDevTest_1518 : public ::testing::Test {

protected:

    BBoxOutputDev* bbo;



    void SetUp() override {

        bbo = new BBoxOutputDev();

    }



    void TearDown() override {

        delete bbo;

    }

};



TEST_F(BBoxOutputDevTest_1518, UpsideDown_ReturnsFalse_1518) {

    EXPECT_FALSE(bbo->upsideDown());

}



TEST_F(BBoxOutputDevTest_1518, UseDrawChar_ReturnsTrue_1518) {

    EXPECT_TRUE(bbo->useDrawChar());

}



TEST_F(BBoxOutputDevTest_1518, InterpretType3Chars_ReturnsFalse_1518) {

    EXPECT_FALSE(bbo->interpretType3Chars());

}



TEST_F(BBoxOutputDevTest_1518, Constructor_Default_1518) {

    EXPECT_EQ(0.0, bbo->getX1());

    EXPECT_EQ(0.0, bbo->getY1());

    EXPECT_EQ(0.0, bbo->getX2());

    EXPECT_EQ(0.0, bbo->getY2());

}



TEST_F(BBoxOutputDevTest_1518, Constructor_BoolParameters_1518) {

    BBoxOutputDev customBBO(true, true, true);

    EXPECT_TRUE(customBBO.useDrawChar());

}



TEST_F(BBoxOutputDevTest_1518, Constructor_AllBoolParameters_1518) {

    BBoxOutputDev customBBO(false, false, false, false);

    EXPECT_FALSE(customBBO.useDrawChar());

}
