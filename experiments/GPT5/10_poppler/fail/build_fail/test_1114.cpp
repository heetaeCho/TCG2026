#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/SplashOutputDev.h"

class SplashOutputDevTest_1114 : public ::testing::Test {
protected:
    // Setup code goes here if necessary
    SplashOutputDev splashOutputDev; // Example instantiation of the class under test
};

TEST_F(SplashOutputDevTest_1114, GetFontAntialias_ReturnsCorrectValue_1114) {
    // Test normal operation: verify the default value of fontAntialias.
    ASSERT_EQ(splashOutputDev.getFontAntialias(), false);  // Adjust based on expected default value
}

TEST_F(SplashOutputDevTest_1114, SetFontAntialias_SetsCorrectValue_1114) {
    // Test setting fontAntialias to true.
    splashOutputDev.setFontAntialias(true);
    ASSERT_EQ(splashOutputDev.getFontAntialias(), true);

    // Test setting fontAntialias to false.
    splashOutputDev.setFontAntialias(false);
    ASSERT_EQ(splashOutputDev.getFontAntialias(), false);
}

TEST_F(SplashOutputDevTest_1114, SetEnableFreeType_SetsCorrectValue_1114) {
    // Test setting enableFreeType to true.
    splashOutputDev.setEnableFreeType(true);
    // Here, you can check if the behavior changes based on enableFreeType being true
    // Example: ASSERT_EQ(splashOutputDev.someMethod(), expectedBehavior);

    // Test setting enableFreeType to false.
    splashOutputDev.setEnableFreeType(false);
    // Similarly, assert expected behavior when false
}

TEST_F(SplashOutputDevTest_1114, GetFontAntialias_ExceptionalCase_1114) {
    // Exceptional case could test behavior on an invalid state or an uninitialized property
    // This example assumes that setting an invalid state throws an error, though based on the class,
    // it might not have such a mechanism. If it does, you can test it similarly.
    try {
        splashOutputDev.setFontAntialias(-1);  // Assuming this causes an error
        FAIL() << "Expected exception to be thrown.";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Invalid argument for setFontAntialias");
    }
}

TEST_F(SplashOutputDevTest_1114, MockExternalHandlerCall_1114) {
    // Example of external interaction testing using Google Mock
    // This will depend on what external collaborations the class might have, such as calling a callback or external service.
    // If there were an external handler passed into this class, it could be mocked here.

    // Example code:
    // Mocking a collaborator and testing the interaction
    // MockExternalClass mockExternal;
    // EXPECT_CALL(mockExternal, expectedMethod())
    //     .Times(1);
    // splashOutputDev.someMethodThatUsesMockedHandler();
}