#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include <memory>



using ::testing::Return;

using ::testing::_;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(void, getDeviceN, (const GfxColor* color, GfxColor* deviceN), (override));

};



class GfxStateTest_582 : public testing::Test {

protected:

    std::unique_ptr<MockGfxColorSpace> mockFillColorSpace;

    std::unique_ptr<GfxState> gfxState;



    void SetUp() override {

        mockFillColorSpace = std::make_unique<MockGfxColorSpace>();

        gfxState = std::make_unique<GfxState>(72.0, 72.0, nullptr, 0, false);

        gfxState->setFillColorSpace(std::move(mockFillColorSpace));

    }

};



TEST_F(GfxStateTest_582, GetFillDeviceN_NormalOperation_582) {

    GfxColor color;

    GfxColor deviceN;



    EXPECT_CALL(*mockFillColorSpace, getDeviceN(&color, &deviceN))

        .Times(1);



    gfxState->getFillDeviceN(&deviceN);

}



TEST_F(GfxStateTest_582, GetFillDeviceN_VerifyParameterPassing_582) {

    GfxColor color;

    GfxColor deviceN;



    EXPECT_CALL(*mockFillColorSpace, getDeviceN(&color, &deviceN))

        .WillOnce(Return());



    gfxState->getFillDeviceN(&deviceN);

}



TEST_F(GfxStateTest_582, GetFillDeviceN_NullPointerArgument_582) {

    GfxColor deviceN;



    EXPECT_CALL(*mockFillColorSpace, getDeviceN(_, _)).Times(0);



    EXPECT_NO_THROW(gfxState->getFillDeviceN(nullptr));

}
