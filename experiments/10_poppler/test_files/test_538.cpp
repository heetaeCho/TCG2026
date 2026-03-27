#include <gtest/gtest.h>

#include "GfxState.h"

#include "GfxColorSpace.h"



using ::testing::Return;

using ::testing::_;



class MockGfxColorSpace : public GfxColorSpace {

public:

    MOCK_CONST_METHOD0(useGetDeviceNLine, bool());

};



class GfxImageColorMapTest_538 : public ::testing::Test {

protected:

    std::unique_ptr<MockGfxColorSpace> mockColorSpace;

    std::unique_ptr<GfxColorSpace> mockColorSpace2;



    void SetUp() override {

        mockColorSpace = std::make_unique<MockGfxColorSpace>();

        mockColorSpace2 = std::make_unique<GfxColorSpace>();

    }



    GfxImageColorMap createTestSubject(bool hasSecondColorSpace) {

        if (hasSecondColorSpace) {

            return GfxImageColorMap(8, nullptr, std::move(mockColorSpace), std::move(mockColorSpace2));

        } else {

            return GfxImageColorMap(8, nullptr, std::move(mockColorSpace));

        }

    }

};



TEST_F(GfxImageColorMapTest_538, UseDeviceNLineWithSecondColorSpaceReturnsTrueWhenFirstUsesDeviceNLine_538) {

    EXPECT_CALL(*mockColorSpace, useGetDeviceNLine()).WillOnce(Return(true));



    GfxImageColorMap testSubject = createTestSubject(true);

    

    ASSERT_TRUE(testSubject.useDeviceNLine());

}



TEST_F(GfxImageColorMapTest_538, UseDeviceNLineWithSecondColorSpaceReturnsTrueWhenSecondUsesDeviceNLine_538) {

    EXPECT_CALL(*mockColorSpace, useGetDeviceNLine()).WillOnce(Return(false));

    EXPECT_CALL(*mockColorSpace2, useGetDeviceNLine()).WillOnce(Return(true));



    GfxImageColorMap testSubject = createTestSubject(true);

    

    ASSERT_TRUE(testSubject.useDeviceNLine());

}



TEST_F(GfxImageColorMapTest_538, UseDeviceNLineWithSecondColorSpaceReturnsFalseWhenNeitherUsesDeviceNLine_538) {

    EXPECT_CALL(*mockColorSpace, useGetDeviceNLine()).WillOnce(Return(false));

    EXPECT_CALL(*mockColorSpace2, useGetDeviceNLine()).WillOnce(Return(false));



    GfxImageColorMap testSubject = createTestSubject(true);

    

    ASSERT_FALSE(testSubject.useDeviceNLine());

}



TEST_F(GfxImageColorMapTest_538, UseDeviceNLineWithoutSecondColorSpaceReturnsTrueWhenUsesDeviceNLine_538) {

    EXPECT_CALL(*mockColorSpace, useGetDeviceNLine()).WillOnce(Return(true));



    GfxImageColorMap testSubject = createTestSubject(false);

    

    ASSERT_TRUE(testSubject.useDeviceNLine());

}



TEST_F(GfxImageColorMapTest_538, UseDeviceNLineWithoutSecondColorSpaceReturnsFalseWhenDoesNotUseDeviceNLine_538) {

    EXPECT_CALL(*mockColorSpace, useGetDeviceNLine()).WillOnce(Return(false));



    GfxImageColorMap testSubject = createTestSubject(false);

    

    ASSERT_FALSE(testSubject.useDeviceNLine());

}
