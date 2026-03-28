#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



class MockGfxPath : public GfxPath {

public:

    MOCK_METHOD(void, lineTo, (double x, double y), (override));

};



class GfxStateTest_662 : public ::testing::Test {

protected:

    std::unique_ptr<MockGfxPath> mockPath;

    GfxState gfxState;



    GfxStateTest_662() 

        : mockPath(std::make_unique<MockGfxPath>()),

          gfxState(100, 100, nullptr, 0, false) {

        gfxState.path = mockPath.get();

    }

};



TEST_F(GfxStateTest_662, LineToUpdatesCurrentCoordinates_NormalOperation_662) {

    EXPECT_CALL(*mockPath, lineTo(5.0, 7.0)).Times(1);

    gfxState.lineTo(5.0, 7.0);



    EXPECT_DOUBLE_EQ(gfxState.getCurX(), 5.0);

    EXPECT_DOUBLE_EQ(gfxState.getCurY(), 7.0);

}



TEST_F(GfxStateTest_662, LineToUpdatesCurrentCoordinates_BoundaryCondition_662) {

    EXPECT_CALL(*mockPath, lineTo(0.0, 0.0)).Times(1);

    gfxState.lineTo(0.0, 0.0);



    EXPECT_DOUBLE_EQ(gfxState.getCurX(), 0.0);

    EXPECT_DOUBLE_EQ(gfxState.getCurY(), 0.0);

}



TEST_F(GfxStateTest_662, LineToUpdatesCurrentCoordinates_NegativeCoordinates_662) {

    EXPECT_CALL(*mockPath, lineTo(-1.5, -3.4)).Times(1);

    gfxState.lineTo(-1.5, -3.4);



    EXPECT_DOUBLE_EQ(gfxState.getCurX(), -1.5);

    EXPECT_DOUBLE_EQ(gfxState.getCurY(), -3.4);

}



TEST_F(GfxStateTest_662, LineToUpdatesCurrentCoordinates_LargeCoordinates_662) {

    EXPECT_CALL(*mockPath, lineTo(1e9, 1e9)).Times(1);

    gfxState.lineTo(1e9, 1e9);



    EXPECT_DOUBLE_EQ(gfxState.getCurX(), 1e9);

    EXPECT_DOUBLE_EQ(gfxState.getCurY(), 1e9);

}
