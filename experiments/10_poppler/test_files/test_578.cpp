#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"

#include "GfxColorSpace.h"



using ::testing::StrictMock;

using ::testing::_;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(void, getGray, (const GfxColor *color, GfxGray *gray), (override));

};



class GfxStateTest_578 : public ::testing::Test {

protected:

    std::unique_ptr<MockGfxColorSpace> mockStrokeColorSpace;

    GfxState gfxState{100.0, 100.0, nullptr, 0, false};



    void SetUp() override {

        mockStrokeColorSpace = std::make_unique<StrictMock<MockGfxColorSpace>>();

        gfxState.setStrokeColorSpace(std::move(mockStrokeColorSpace));

    }

};



TEST_F(GfxStateTest_578, GetStrokeGray_NormalOperation_578) {

    GfxColor color{};

    GfxGray gray{};

    

    EXPECT_CALL(*mockStrokeColorSpace, getGray(&color, &gray))

        .Times(1)

        .WillOnce(::testing::Return());



    gfxState.getStrokeGray(&gray);

}



TEST_F(GfxStateTest_578, GetStrokeGray_NullPointerHandling_578) {

    GfxColor color{};

    

    EXPECT_DEATH(gfxState.getStrokeGray(nullptr), "");

}
