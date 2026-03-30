#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/splash/SplashPattern.h"

// Mock class for external dependencies
class MockSplashColor : public SplashColor {
public:
    MOCK_METHOD(bool, isStatic, (), (const, override));
    MOCK_METHOD(const bool, getColor, (int x, int y, SplashColorPtr c), (const, override));
    MOCK_METHOD(SplashPattern*, copy, (), (const, override));
    MOCK_METHOD(bool, testPosition, (int x, int y), (const, override));
    MOCK_METHOD(bool, isCMYK, (), (const, override));
};

// Test fixture for SplashSolidColor tests
class SplashSolidColorTest_1051 : public ::testing::Test {
protected:
    SplashColorConstPtr mockColor;
    SplashSolidColor* solidColor;

    void SetUp() override {
        mockColor = std::make_shared<MockSplashColor>();  // Using mock class for SplashColor
        solidColor = new SplashSolidColor(mockColor);
    }

    void TearDown() override {
        delete solidColor;
    }
};

// Test case for the isStatic function
TEST_F(SplashSolidColorTest_1051, isStaticReturnsTrue_1051) {
    // Setup: Call isStatic method
    bool result = solidColor->isStatic();

    // Assert: isStatic() should return true as per the implementation
    EXPECT_TRUE(result);
}

// Test case for getColor function (boundary test for x=0, y=0)
TEST_F(SplashSolidColorTest_1051, getColorAtOrigin_1051) {
    // Setup: Prepare a color object and mock the getColor call
    SplashColorPtr colorPtr;
    EXPECT_CALL(*mockColor, getColor(0, 0, ::testing::_))
        .WillOnce(::testing::Return(true));

    // Act: Call getColor with coordinates (0, 0)
    bool result = solidColor->getColor(0, 0, colorPtr);

    // Assert: Ensure the method returns true
    EXPECT_TRUE(result);
}

// Test case for getColor function (boundary test for large x, y)
TEST_F(SplashSolidColorTest_1051, getColorAtLargeCoordinates_1051) {
    // Setup: Prepare a color object and mock the getColor call
    SplashColorPtr colorPtr;
    EXPECT_CALL(*mockColor, getColor(1000, 1000, ::testing::_))
        .WillOnce(::testing::Return(true));

    // Act: Call getColor with coordinates (1000, 1000)
    bool result = solidColor->getColor(1000, 1000, colorPtr);

    // Assert: Ensure the method returns true
    EXPECT_TRUE(result);
}

// Test case for copy function
TEST_F(SplashSolidColorTest_1051, copyCreatesDuplicate_1051) {
    // Setup: Mock the copy method
    EXPECT_CALL(*mockColor, copy())
        .WillOnce(::testing::Return(mockColor.get()));

    // Act: Call the copy function
    SplashPattern* result = solidColor->copy();

    // Assert: Ensure the copy method returns a valid copy
    EXPECT_NE(result, nullptr);
}

// Test case for testPosition function (boundary case)
TEST_F(SplashSolidColorTest_1051, testPositionReturnsTrue_1051) {
    // Setup: Mock testPosition to always return true
    EXPECT_CALL(*mockColor, testPosition(100, 100))
        .WillOnce(::testing::Return(true));

    // Act: Call the testPosition method
    bool result = solidColor->testPosition(100, 100);

    // Assert: Ensure the method returns true
    EXPECT_TRUE(result);
}

// Test case for isCMYK function
TEST_F(SplashSolidColorTest_1051, isCMYKReturnsFalse_1051) {
    // Setup: Mock isCMYK to return false
    EXPECT_CALL(*mockColor, isCMYK())
        .WillOnce(::testing::Return(false));

    // Act: Call isCMYK method
    bool result = solidColor->isCMYK();

    // Assert: Ensure the method returns false
    EXPECT_FALSE(result);
}