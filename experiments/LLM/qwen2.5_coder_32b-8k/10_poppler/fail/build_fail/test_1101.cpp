#include <gtest/gtest.h>

#include "SplashOutputDev.h"

#include "GfxState.h"



using namespace testing;



class MockGfxGouraudTriangleShading : public GfxGouraudTriangleShading {

public:

    MOCK_METHOD(bool, isParameterized, (), (const, override));

    MOCK_METHOD(int, getNTriangles, (), (const, override));

};



class SplashGouraudPatternTest : public Test {

protected:

    MockGfxGouraudTriangleShading mockShading;

    SplashGouraudPattern pattern{true, &mockShading};

};



TEST_F(SplashGouraudPatternTest, IsParameterized_ReturnsTrue_1101) {

    EXPECT_CALL(mockShading, isParameterized()).WillOnce(Return(true));

    ASSERT_TRUE(pattern.isParameterized());

}



TEST_F(SplashGouraudPatternTest, IsParameterized_ReturnsFalse_1101) {

    EXPECT_CALL(mockShading, isParameterized()).WillOnce(Return(false));

    ASSERT_FALSE(pattern.isParameterized());

}



TEST_F(SplashGouraudPatternTest, GetNTriangles_ReturnsExpectedValue_1101) {

    const int expectedTriangles = 5;

    EXPECT_CALL(mockShading, getNTriangles()).WillOnce(Return(expectedTriangles));

    ASSERT_EQ(pattern.getNTriangles(), expectedTriangles);

}



TEST_F(SplashGouraudPatternTest, GetNTriangles_ReturnsZero_1101) {

    EXPECT_CALL(mockShading, getNTriangles()).WillOnce(Return(0));

    ASSERT_EQ(pattern.getNTriangles(), 0);

}
