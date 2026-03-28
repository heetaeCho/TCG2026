#include <gtest/gtest.h>

#include "./TestProjects/poppler/splash/Splash.cc"



// Since the provided code snippet does not define any class or functions to test directly,

// we will assume a hypothetical class that uses the imgCoordMungeLowerC function.

// This is necessary to create meaningful unit tests using Google Test.



class MockExternalHandler {

public:

    MOCK_METHOD(int, processCoordinate, (int), ());

};



class SplashTest : public ::testing::Test {

protected:

    MockExternalHandler mockHandler;

};



TEST_F(SplashTest_NormalOperation_2613, imgCoordMungeLowerC_GlyphModeTrue_2613) {

    // Arrange

    SplashCoord x = 3.7;

    bool glyphMode = true;

    

    // Act

    int result = imgCoordMungeLowerC(x, glyphMode);

    

    // Assert

    EXPECT_EQ(result, 4); // splashCeil(3.7 + 0.5) - 1 = splashCeil(4.2) - 1 = 5 - 1 = 4

}



TEST_F(SplashTest_NormalOperation_2613, imgCoordMungeLowerC_GlyphModeFalse_2613) {

    // Arrange

    SplashCoord x = 3.7;

    bool glyphMode = false;

    

    // Act

    int result = imgCoordMungeLowerC(x, glyphMode);

    

    // Assert

    EXPECT_EQ(result, 3); // splashFloor(3.7) = 3

}



TEST_F(SplashTest_BoundaryConditions_2613, imgCoordMungeLowerC_Zero_2613) {

    // Arrange

    SplashCoord x = 0.0;

    bool glyphMode = true;

    

    // Act

    int resultTrue = imgCoordMungeLowerC(x, glyphMode);

    glyphMode = false;

    int resultFalse = imgCoordMungeLowerC(x, glyphMode);

    

    // Assert

    EXPECT_EQ(resultTrue, 0); // splashCeil(0.5) - 1 = 1 - 1 = 0

    EXPECT_EQ(resultFalse, 0); // splashFloor(0.0) = 0

}



TEST_F(SplashTest_BoundaryConditions_2613, imgCoordMungeLowerC_Negative_2613) {

    // Arrange

    SplashCoord x = -2.5;

    bool glyphMode = true;

    

    // Act

    int resultTrue = imgCoordMungeLowerC(x, glyphMode);

    glyphMode = false;

    int resultFalse = imgCoordMungeLowerC(x, glyphMode);

    

    // Assert

    EXPECT_EQ(resultTrue, -3); // splashCeil(-2.5 + 0.5) - 1 = splashCeil(-2.0) - 1 = -2 - 1 = -3

    EXPECT_EQ(resultFalse, -3); // splashFloor(-2.5) = -3

}



// Assuming no exceptional cases are observable through the interface for this function.

```


