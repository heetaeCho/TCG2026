#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "GfxColorSpace.h"



using namespace testing;



// Mock GfxColorSpace for verification of external interactions

class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD0(isGray, bool());

    MOCK_METHOD0(isRGB, bool());

    MOCK_METHOD0(isCMYK, bool());

};



TEST_F(GfxStateTest_657, SetDefaultCMYKColorSpace_NormalOperation_657) {

    auto colorSpace = std::make_unique<MockGfxColorSpace>();

    EXPECT_CALL(*colorSpace, isCMYK()).WillOnce(Return(true));



    GfxState state(300.0, 300.0, nullptr, 0, false);

    state.setDefaultCMYKColorSpace(std::move(colorSpace));

}



TEST_F(GfxStateTest_657, SetDefaultCMYKColorSpace_NullPointer_657) {

    GfxState state(300.0, 300.0, nullptr, 0, false);

    state.setDefaultCMYKColorSpace(nullptr);

}



TEST_F(GfxStateTest_657, SetDefaultCMYKColorSpace_MultipleCalls_657) {

    auto colorSpace1 = std::make_unique<MockGfxColorSpace>();

    EXPECT_CALL(*colorSpace1, isCMYK()).WillOnce(Return(true));



    auto colorSpace2 = std::make_unique<MockGfxColorSpace>();

    EXPECT_CALL(*colorSpace2, isCMYK()).WillOnce(Return(true));



    GfxState state(300.0, 300.0, nullptr, 0, false);

    state.setDefaultCMYKColorSpace(std::move(colorSpace1));

    state.setDefaultCMYKColorSpace(std::move(colorSpace2));

}
