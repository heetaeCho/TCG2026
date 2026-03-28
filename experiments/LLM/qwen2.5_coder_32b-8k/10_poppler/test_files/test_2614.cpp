#include <gtest/gtest.h>



// Assuming SplashCoord and splashFloor/splashCeil are defined somewhere in the codebase.

// For the purpose of this test, we will mock these if necessary.



class MockMathFunctions {

public:

    MOCK_CONST_METHOD1(splashFloorMock, int(SplashCoord));

    MOCK_CONST_METHOD1(splashCeilMock, int(SplashCoord));



    int splashFloor(SplashCoord x) const {

        return splashFloorMock(x);

    }



    int splashCeil(SplashCoord x) const {

        return splashCeilMock(x);

    }

};



class SplashTest : public ::testing::Test {

protected:

    MockMathFunctions mockMath;



    int imgCoordMungeUpperC(SplashCoord x, bool glyphMode) const {

        return glyphMode ? (mockMath.splashCeilMock(x + 0.5) - 1) : (mockMath.splashFloorMock(x) + 1);

    }

};



TEST_F(SplashTest_2614, GlyphModeTrue_ReturnsCorrectValue_2614) {

    EXPECT_CALL(mockMath, splashCeilMock(1.0)).WillOnce(::testing::Return(2));

    int result = imgCoordMungeUpperC(0.5, true);

    EXPECT_EQ(result, 1);

}



TEST_F(SplashTest_2614, GlyphModeFalse_ReturnsCorrectValue_2614) {

    EXPECT_CALL(mockMath, splashFloorMock(1.0)).WillOnce(::testing::Return(1));

    int result = imgCoordMungeUpperC(1.0, false);

    EXPECT_EQ(result, 2);

}



TEST_F(SplashTest_2614, BoundaryCondition_GlyphModeTrue_2614) {

    EXPECT_CALL(mockMath, splashCeilMock(0.5)).WillOnce(::testing::Return(1));

    int result = imgCoordMungeUpperC(0.0, true);

    EXPECT_EQ(result, 0);

}



TEST_F(SplashTest_2614, BoundaryCondition_GlyphModeFalse_2614) {

    EXPECT_CALL(mockMath, splashFloorMock(-0.5)).WillOnce(::testing::Return(-1));

    int result = imgCoordMungeUpperC(-1.0, false);

    EXPECT_EQ(result, 0);

}



TEST_F(SplashTest_2614, NegativeValue_GlyphModeTrue_2614) {

    EXPECT_CALL(mockMath, splashCeilMock(-0.5)).WillOnce(::testing::Return(0));

    int result = imgCoordMungeUpperC(-1.0, true);

    EXPECT_EQ(result, -1);

}



TEST_F(SplashTest_2614, NegativeValue_GlyphModeFalse_2614) {

    EXPECT_CALL(mockMath, splashFloorMock(-1.5)).WillOnce(::testing::Return(-2));

    int result = imgCoordMungeUpperC(-1.0, false);

    EXPECT_EQ(result, -1);

}
