#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/GfxState.h"



using ::testing::_;

using ::testing::Return;

using ::testing::Eq;



class GfxPathMock : public GfxPath {

public:

    MOCK_METHOD5(curveTo, void(double, double, double, double, double));

    MOCK_CONST_METHOD0(getLastX, double());

    MOCK_CONST_METHOD0(getLastY, double());

};



class GfxStateTest_663 : public ::testing::Test {

protected:

    GfxPathMock* pathMock;

    std::unique_ptr<GfxState> gfxState;



    void SetUp() override {

        pathMock = new GfxPathMock();

        gfxState = std::make_unique<GfxState>(100.0, 100.0, nullptr, 0, false);

        gfxState->path.reset(pathMock);

    }



    void TearDown() override {

        pathMock = nullptr;

    }

};



TEST_F(GfxStateTest_663, CurveToUpdatesCurrentPosition_663) {

    EXPECT_CALL(*pathMock, curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0));

    EXPECT_CALL(*pathMock, getLastX()).WillOnce(Return(5.0));

    EXPECT_CALL(*pathMock, getLastY()).WillOnce(Return(6.0));



    gfxState->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0);



    EXPECT_EQ(gfxState->getCurX(), 5.0);

    EXPECT_EQ(gfxState->getCurY(), 6.0);

}



TEST_F(GfxStateTest_663, CurveToBoundaryConditions_663) {

    // Test with zero values

    EXPECT_CALL(*pathMock, curveTo(0.0, 0.0, 0.0, 0.0, 0.0, 0.0));

    gfxState->curveTo(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);



    // Test with negative values

    EXPECT_CALL(*pathMock, curveTo(-1.0, -2.0, -3.0, -4.0, -5.0, -6.0));

    gfxState->curveTo(-1.0, -2.0, -3.0, -4.0, -5.0, -6.0);



    // Test with large values

    EXPECT_CALL(*pathMock, curveTo(1e10, 2e10, 3e10, 4e10, 5e10, 6e10));

    gfxState->curveTo(1e10, 2e10, 3e10, 4e10, 5e10, 6e10);

}



TEST_F(GfxStateTest_663, CurveToNoPath_663) {

    gfxState->path.reset(nullptr);

    

    EXPECT_NO_THROW(gfxState->curveTo(1.0, 2.0, 3.0, 4.0, 5.0, 6.0));

}
