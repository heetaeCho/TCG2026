#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    GfxState state{300, 300, nullptr, 0, false};

};



TEST_F(GfxStateTest_646, SetTextMat_NormalOperation_646) {

    double a = 1.0, b = 2.0, c = 3.0, d = 4.0, e = 5.0, f = 6.0;

    state.setTextMat(a, b, c, d, e, f);

    

    std::array<double, 6> textMat = state.getTextMat();

    EXPECT_EQ(textMat[0], a);

    EXPECT_EQ(textMat[1], b);

    EXPECT_EQ(textMat[2], c);

    EXPECT_EQ(textMat[3], d);

    EXPECT_EQ(textMat[4], e);

    EXPECT_EQ(textMat[5], f);

}



TEST_F(GfxStateTest_646, SetTextMat_BoundaryConditions_646) {

    double zero = 0.0;

    state.setTextMat(zero, zero, zero, zero, zero, zero);

    

    std::array<double, 6> textMat = state.getTextMat();

    EXPECT_EQ(textMat[0], zero);

    EXPECT_EQ(textMat[1], zero);

    EXPECT_EQ(textMat[2], zero);

    EXPECT_EQ(textMat[3], zero);

    EXPECT_EQ(textMat[4], zero);

    EXPECT_EQ(textMat[5], zero);



    double max = std::numeric_limits<double>::max();

    state.setTextMat(max, max, max, max, max, max);

    

    textMat = state.getTextMat();

    EXPECT_EQ(textMat[0], max);

    EXPECT_EQ(textMat[1], max);

    EXPECT_EQ(textMat[2], max);

    EXPECT_EQ(textMat[3], max);

    EXPECT_EQ(textMat[4], max);

    EXPECT_EQ(textMat[5], max);



    double min = std::numeric_limits<double>::lowest();

    state.setTextMat(min, min, min, min, min, min);

    

    textMat = state.getTextMat();

    EXPECT_EQ(textMat[0], min);

    EXPECT_EQ(textMat[1], min);

    EXPECT_EQ(textMat[2], min);

    EXPECT_EQ(textMat[3], min);

    EXPECT_EQ(textMat[4], min);

    EXPECT_EQ(textMat[5], min);

}



TEST_F(GfxStateTest_646, SetTextMat_ExceptionalCases_646) {

    // No exceptional cases expected based on the interface provided.

}
