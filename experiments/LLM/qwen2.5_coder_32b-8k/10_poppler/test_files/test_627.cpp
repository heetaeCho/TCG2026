#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest_627 : public ::testing::Test {

protected:

    GfxState* state;



    void SetUp() override {

        // Assuming default constructor parameters for testing purposes

        double hDPIA = 100.0;

        double vDPIA = 100.0;

        PDFRectangle pageBox = {0, 0, 612, 792};

        int rotateA = 0;

        bool upsideDown = false;

        state = new GfxState(hDPIA, vDPIA, &pageBox, rotateA, upsideDown);

    }



    void TearDown() override {

        delete state;

    }

};



TEST_F(GfxStateTest_627, TextTransform_NormalOperation_627) {

    double x1 = 1.0, y1 = 1.0;

    double x2 = 0.0, y2 = 0.0;



    // Assuming textMat is identity matrix for simplicity

    state->textTransform(x1, y1, &x2, &y2);



    EXPECT_DOUBLE_EQ(x2, 1.0);

    EXPECT_DOUBLE_EQ(y2, 1.0);

}



TEST_F(GfxStateTest_627, TextTransform_BoundaryConditions_627) {

    double x1 = 0.0, y1 = 0.0;

    double x2 = 0.0, y2 = 0.0;



    state->textTransform(x1, y1, &x2, &y2);



    EXPECT_DOUBLE_EQ(x2, 0.0);

    EXPECT_DOUBLE_EQ(y2, 0.0);



    x1 = std::numeric_limits<double>::max();

    y1 = std::numeric_limits<double>::max();



    state->textTransform(x1, y1, &x2, &y2);



    // Check for potential overflow or unexpected behavior

    EXPECT_TRUE(std::isfinite(x2));

    EXPECT_TRUE(std::isfinite(y2));

}



TEST_F(GfxStateTest_627, TextTransform_ExceptionalCases_627) {

    double x1 = std::numeric_limits<double>::quiet_NaN(), y1 = 0.0;

    double x2 = 0.0, y2 = 0.0;



    state->textTransform(x1, y1, &x2, &y2);



    EXPECT_TRUE(std::isnan(x2));

    EXPECT_TRUE(std::isnan(y2));



    x1 = 0.0;

    y1 = std::numeric_limits<double>::infinity();



    state->textTransform(x1, y1, &x2, &y2);



    // Check for infinity propagation

    EXPECT_EQ(x2, std::numeric_limits<double>::infinity());

    EXPECT_TRUE(std::isfinite(y2));

}
