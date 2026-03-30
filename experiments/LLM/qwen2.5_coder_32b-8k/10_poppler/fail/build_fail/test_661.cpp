#include <gtest/gtest.h>

#include "GfxState.h"

#include "GfxPath.h"



class GfxStateTest_661 : public ::testing::Test {

protected:

    std::unique_ptr<GfxPath> path;

    std::unique_ptr<GfxState> state;



    void SetUp() override {

        path = std::make_unique<GfxPath>();

        state = std::make_unique<GfxState>(72.0, 72.0, nullptr, 0, false);

        state->path = path.get();

    }

};



TEST_F(GfxStateTest_661, MoveToSetsCurrentCoordinates_661) {

    double x = 10.5;

    double y = 20.3;

    state->moveTo(x, y);

    EXPECT_DOUBLE_EQ(state->getCurX(), x);

    EXPECT_DOUBLE_EQ(state->getCurY(), y);

}



TEST_F(GfxStateTest_661, MoveToUpdatesPath_661) {

    double x = 5.0;

    double y = 7.5;

    state->moveTo(x, y);

    EXPECT_TRUE(path->isCurPt());

    EXPECT_DOUBLE_EQ(path->getLastX(), x);

    EXPECT_DOUBLE_EQ(path->getLastY(), y);

}



TEST_F(GfxStateTest_661, MoveToWithZeroCoordinates_661) {

    double x = 0.0;

    double y = 0.0;

    state->moveTo(x, y);

    EXPECT_DOUBLE_EQ(state->getCurX(), x);

    EXPECT_DOUBLE_EQ(state->getCurY(), y);

}



TEST_F(GfxStateTest_661, MoveToWithNegativeCoordinates_661) {

    double x = -15.2;

    double y = -30.4;

    state->moveTo(x, y);

    EXPECT_DOUBLE_EQ(state->getCurX(), x);

    EXPECT_DOUBLE_EQ(state->getCurY(), y);

}



TEST_F(GfxStateTest_661, MoveToWithLargeCoordinates_661) {

    double x = 1e9;

    double y = 1e9;

    state->moveTo(x, y);

    EXPECT_DOUBLE_EQ(state->getCurX(), x);

    EXPECT_DOUBLE_EQ(state->getCurY(), y);

}
