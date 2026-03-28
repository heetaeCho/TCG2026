#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxState.h"



using ::testing::NiceMock;

using ::testing::Return;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(void, getCMYK, (const GfxColor *color, GfxCMYK *cmyk), (override));

};



class GfxStateTest_581 : public ::testing::Test {

protected:

    void SetUp() override {

        mockFillColorSpace = std::make_unique<NiceMock<MockGfxColorSpace>>();

        gfxState.setFillColorSpace(std::move(mockFillColorSpace));

    }



    GfxState gfxState{72.0, 72.0, nullptr, 0, false};

    std::unique_ptr<GfxColorSpace> mockFillColorSpace;

};



TEST_F(GfxStateTest_581, GetFillCMYK_NormalOperation_581) {

    GfxCMYK expectedCMYK{0.1f, 0.2f, 0.3f, 0.4f};

    EXPECT_CALL(*mockFillColorSpace, getCMYK(::testing::_, ::testing::_))

        .WillOnce(testing::DoAll(

            testing::SetArgReferee<1>(expectedCMYK),

            Return()));



    GfxCMYK result;

    gfxState.getFillCMYK(&result);



    EXPECT_FLOAT_EQ(result.c, expectedCMYK.c);

    EXPECT_FLOAT_EQ(result.m, expectedCMYK.m);

    EXPECT_FLOAT_EQ(result.y, expectedCMYK.y);

    EXPECT_FLOAT_EQ(result.k, expectedCMYK.k);

}



TEST_F(GfxStateTest_581, GetFillCMYK_NullPointer_581) {

    GfxCMYK result;

    EXPECT_NO_THROW(gfxState.getFillCMYK(nullptr));

    // Since the pointer is null, we cannot verify the values, but we ensure no crash occurs.

}



TEST_F(GfxStateTest_581, GetFillCMYK_UnsetFillColorSpace_581) {

    gfxState.setFillColorSpace(std::unique_ptr<GfxColorSpace>(nullptr));



    GfxCMYK result;

    EXPECT_NO_THROW(gfxState.getFillCMYK(&result));

    // Assuming that if the color space is unset, it doesn't crash and possibly sets default values.

}
