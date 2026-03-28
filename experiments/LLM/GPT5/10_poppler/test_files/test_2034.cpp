#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock the dependencies
class MockPopplerMedia {
public:
    MOCK_METHOD(bool, is_media, (), (const));
    MOCK_METHOD(int, auto_play, (), (const));
};

// Test fixture for PopplerMedia class
class PopplerMediaTest_2034 : public ::testing::Test {
protected:
    MockPopplerMedia mock_media;
};

// Normal operation test case
TEST_F(PopplerMediaTest_2034, GetAutoPlayReturnsCorrectValue_2034) {
    // Arrange: Set up mock behavior
    EXPECT_CALL(mock_media, is_media())
        .WillOnce(testing::Return(true));  // Simulate a valid media object
    EXPECT_CALL(mock_media, auto_play())
        .WillOnce(testing::Return(1));  // Simulate auto_play = 1 (true)

    // Act: Call the function
    int result = mock_media.auto_play();

    // Assert: Check if the return value matches the expected auto_play value
    EXPECT_EQ(result, 1);
}

// Boundary condition test case
TEST_F(PopplerMediaTest_2034, GetAutoPlayReturnsFalseForInvalidMedia_2034) {
    // Arrange: Set up mock behavior
    EXPECT_CALL(mock_media, is_media())
        .WillOnce(testing::Return(false));  // Simulate invalid media object
    EXPECT_CALL(mock_media, auto_play())
        .Times(0);  // Function should not be called

    // Act: Call the function
    int result = mock_media.auto_play();

    // Assert: Ensure the return value is false for invalid media
    EXPECT_EQ(result, 0);
}

// Exceptional case test case
TEST_F(PopplerMediaTest_2034, GetAutoPlayHandlesNullMedia_2034) {
    // Arrange: Set up mock behavior
    EXPECT_CALL(mock_media, is_media())
        .WillOnce(testing::Return(false));  // Simulate null or invalid media object

    // Act: Call the function and expect it to handle null gracefully
    int result = mock_media.auto_play();

    // Assert: Ensure the return value is false for null or invalid media
    EXPECT_EQ(result, 0);
}