#include <gtest/gtest.h>

#include "GfxState.h"



class GfxStateTest : public ::testing::Test {

protected:

    double hDPI = 72.0;

    double vDPI = 72.0;

    PDFRectangle pageBox{0, 0, 612, 792};

    int rotate = 0;

    bool upsideDown = false;



    std::unique_ptr<GfxState> state;



    void SetUp() override {

        state = std::make_unique<GfxState>(hDPI, vDPI, &pageBox, rotate, upsideDown);

    }

};



TEST_F(GfxStateTest_649, SetHorizScaling_NormalOperation_649) {

    double scale = 100.0;

    state->setHorizScaling(scale);

    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1.0); // 0.01 * 100 = 1.0

}



TEST_F(GfxStateTest_649, SetHorizScaling_BoundaryCondition_Zero_649) {

    double scale = 0.0;

    state->setHorizScaling(scale);

    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 0.0); // 0.01 * 0 = 0.0

}



TEST_F(GfxStateTest_649, SetHorizScaling_BoundaryCondition_MaxDouble_649) {

    double scale = std::numeric_limits<double>::max();

    state->setHorizScaling(scale);

    EXPECT_DOUBLE_EQ(state->getHorizScaling(), 1e308); // Approximation due to precision limits

}



TEST_F(GfxStateTest_649, SetHorizScaling_BoundaryCondition_MinDouble_649) {

    double scale = std::numeric_limits<double>::lowest();

    state->setHorizScaling(scale);

    EXPECT_DOUBLE_EQ(state->getHorizScaling(), -1e308); // Approximation due to precision limits

}
