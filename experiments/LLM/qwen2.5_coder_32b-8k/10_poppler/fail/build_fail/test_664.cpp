#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "GfxPath.h"



using ::testing::Return;



class GfxStateTest : public ::testing::Test {

protected:

    std::unique_ptr<GfxPath> mockPath;

    std::shared_ptr<GfxState> state;



    void SetUp() override {

        mockPath = std::make_unique<GfxPath>();

        state = std::make_shared<GfxState>(72.0, 72.0, nullptr, 0, false);

        state->path = mockPath.get();

    }

};



TEST_F(GfxStateTest_664, ClosePathUpdatesCurXAndCurY_664) {

    EXPECT_CALL(*mockPath, getLastX()).WillOnce(Return(10.0));

    EXPECT_CALL(*mockPath, getLastY()).WillOnce(Return(20.0));



    state->closePath();



    EXPECT_EQ(state->getCurX(), 10.0);

    EXPECT_EQ(state->getCurY(), 20.0);

}



TEST_F(GfxStateTest_664, ClosePathCallsCloseOnPath_664) {

    EXPECT_CALL(*mockPath, close());



    state->closePath();

}
