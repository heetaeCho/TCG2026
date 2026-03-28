#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using ::testing::_;

using ::testing::NiceMock;

using ::testing::Return;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD2(getDeviceN, void(const GfxColor* color, GfxColor* deviceN));

};



class GfxStateTest_584 : public ::testing::Test {

protected:

    NiceMock<MockGfxColorSpace> mockStrokeColorSpace;

    GfxState state{72.0, 72.0, nullptr, 0, false};

    GfxColor strokeColor;



    void SetUp() override {

        state.setStrokeColorSpace(std::make_unique<MockGfxColorSpace>(mockStrokeColorSpace));

        state.setStrokeColor(&strokeColor);

    }

};



TEST_F(GfxStateTest_584, GetStrokeDeviceN_CallsGetDeviceNOnStrokeColorSpace_584) {

    GfxColor deviceN;

    EXPECT_CALL(mockStrokeColorSpace, getDeviceN(_, &deviceN)).Times(1);



    state.getStrokeDeviceN(&deviceN);

}



TEST_F(GfxStateTest_584, GetStrokeDeviceN_PassesCorrectStrokeColor_584) {

    GfxColor deviceN;

    EXPECT_CALL(mockStrokeColorSpace, getDeviceN(&strokeColor, _)).Times(1);



    state.getStrokeDeviceN(&deviceN);

}



TEST_F(GfxStateTest_584, GetStrokeDeviceN_HandlesNullPointerGracefully_584) {

    // Assuming the method should handle null pointers gracefully

    EXPECT_NO_THROW(state.getStrokeDeviceN(nullptr));

}
