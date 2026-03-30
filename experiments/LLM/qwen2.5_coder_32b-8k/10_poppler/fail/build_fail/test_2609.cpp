#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "SplashPath.h"

#include "SplashFTFont.cc"



using namespace testing;



class SplashFTFontPathTest : public ::testing::Test {

protected:

    SplashFTFontPath fontPath;

    MockFunction<void(const FT_Vector*, const FT_Vector*, void*)> mockCallback;



    virtual void SetUp() {

        fontPath.path = new SplashPath();

        fontPath.textScale = 1.0;

    }



    virtual void TearDown() {

        delete fontPath.path;

    }

};



TEST_F(SplashFTFontPathTest_2609, NormalOperation_CurveAdded_2609) {

    FT_Vector ctrl = {100, 150};

    FT_Vector pt = {200, 200};

    EXPECT_CALL(mockCallback, Call(_, _, _)).Times(1);



    int result = glyphPathConicTo(&ctrl, &pt, &fontPath);

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(fontPath.path->getCurPt(nullptr, nullptr));

}



TEST_F(SplashFTFontPathTest_2609, NoCurrentPoint_ReturnsZero_2609) {

    FT_Vector ctrl = {100, 150};

    FT_Vector pt = {200, 200};

    fontPath.path->close(true); // Close the path to remove current point



    int result = glyphPathConicTo(&ctrl, &pt, &fontPath);

    EXPECT_EQ(result, 0);

    EXPECT_FALSE(fontPath.path->getCurPt(nullptr, nullptr));

}



TEST_F(SplashFTFontPathTest_2609, BoundaryConditions_ZeroCoordinates_2609) {

    FT_Vector ctrl = {0, 0};

    FT_Vector pt = {0, 0};

    EXPECT_CALL(mockCallback, Call(_, _, _)).Times(1);



    int result = glyphPathConicTo(&ctrl, &pt, &fontPath);

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(fontPath.path->getCurPt(nullptr, nullptr));

}



TEST_F(SplashFTFontPathTest_2609, BoundaryConditions_MaxCoordinates_2609) {

    FT_Vector ctrl = {INT_MAX, INT_MAX};

    FT_Vector pt = {INT_MAX, INT_MAX};

    EXPECT_CALL(mockCallback, Call(_, _, _)).Times(1);



    int result = glyphPathConicTo(&ctrl, &pt, &fontPath);

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(fontPath.path->getCurPt(nullptr, nullptr));

}



TEST_F(SplashFTFontPathTest_2609, BoundaryConditions_NegativeCoordinates_2609) {

    FT_Vector ctrl = {-100, -150};

    FT_Vector pt = {-200, -200};

    EXPECT_CALL(mockCallback, Call(_, _, _)).Times(1);



    int result = glyphPathConicTo(&ctrl, &pt, &fontPath);

    EXPECT_EQ(result, 0);

    EXPECT_TRUE(fontPath.path->getCurPt(nullptr, nullptr));

}
