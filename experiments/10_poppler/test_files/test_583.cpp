#include <gtest/gtest.h>

#include <gmock/gmock.h>



#include "GfxState.h"



using ::testing::_;

using ::testing::Return;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_METHOD(void, getCMYK, (const GfxColor*, GfxCMYK*), (override));

};



class GfxStateTest_583 : public ::testing::Test {

protected:

    void SetUp() override {

        mockStrokeColorSpace = std::make_unique<MockGfxColorSpace>();

        gfxState.setStrokeColorSpace(std::move(mockStrokeColorSpace));

    }



    GfxState gfxState{72.0, 72.0, nullptr, 0, false};

    std::unique_ptr<MockGfxColorSpace> mockStrokeColorSpace;

};



TEST_F(GfxStateTest_583, GetStrokeCMYK_NormalOperation_583) {

    GfxCMYK expectedCMYK = {0.1f, 0.2f, 0.3f, 0.4f};

    EXPECT_CALL(*mockStrokeColorSpace, getCMYK(_, _))

        .WillOnce(testing::Invoke([](const GfxColor*, GfxCMYK* cmyk) {

            *cmyk = {0.1f, 0.2f, 0.3f, 0.4f};

        }));



    GfxCMYK actualCMYK;

    gfxState.getStrokeCMYK(&actualCMYK);



    EXPECT_FLOAT_EQ(expectedCMYK.c, actualCMYK.c);

    EXPECT_FLOAT_EQ(expectedCMYK.m, actualCMYK.m);

    EXPECT_FLOAT_EQ(expectedCMYK.y, actualCMYK.y);

    EXPECT_FLOAT_EQ(expectedCMYK.k, actualCMYK.k);

}



TEST_F(GfxStateTest_583, GetStrokeCMYK_NullPointer_583) {

    GfxCMYK cmyk;

    EXPECT_DEATH(gfxState.getStrokeCMYK(nullptr), "");

}



TEST_F(GfxStateTest_583, GetStrokeCMYK_UninitializedColorSpace_583) {

    gfxState.setStrokeColorSpace(nullptr);



    GfxCMYK cmyk;

    EXPECT_DEATH(gfxState.getStrokeCMYK(&cmyk), "");

}
