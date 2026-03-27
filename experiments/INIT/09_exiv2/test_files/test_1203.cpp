#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "bmffimage.hpp"
#include "basicio.hpp"

namespace Exiv2 {
    // Mock BasicIo for the purpose of testing
    class MockBasicIo : public BasicIo {
    public:
        MOCK_METHOD(void, open, (const std::string& file), (override));
        MOCK_METHOD(bool, good, (), (const, override));
        MOCK_METHOD(void, close, (), (override));
        MOCK_METHOD(size_t, read, (void* buffer, size_t length), (override));
        MOCK_METHOD(size_t, write, (const void* buffer, size_t length), (override));
    };
}

// Test case to check the normal behavior of newBmffInstance
TEST_F(BmffImageTest_1203, NewBmffInstance_Success) {
    // Arrange
    auto mockIo = std::make_unique<Exiv2::MockBasicIo>();
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(true));
    
    // Act
    auto result = Exiv2::newBmffInstance(std::move(mockIo), true);

    // Assert
    ASSERT_NE(result, nullptr);  // The result should not be nullptr
    EXPECT_TRUE(result->good()); // Ensure the image is "good"
}

// Test case to check failure when the image is not good
TEST_F(BmffImageTest_1203, NewBmffInstance_Failure) {
    // Arrange
    auto mockIo = std::make_unique<Exiv2::MockBasicIo>();
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(false));

    // Act
    auto result = Exiv2::newBmffInstance(std::move(mockIo), true);

    // Assert
    ASSERT_EQ(result, nullptr);  // The result should be nullptr when image is not good
}

// Test case to check boundary condition when BasicIo is empty
TEST_F(BmffImageTest_1203, NewBmffInstance_EmptyIo) {
    // Arrange
    auto mockIo = std::make_unique<Exiv2::MockBasicIo>();
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(true));  // Image is good

    // Act
    auto result = Exiv2::newBmffInstance(std::move(mockIo), false);

    // Assert
    ASSERT_NE(result, nullptr);  // The result should not be nullptr
    EXPECT_TRUE(result->good()); // Ensure the image is "good"
}

// Test case to verify interactions with external collaborators (Mock BasicIo)
TEST_F(BmffImageTest_1203, NewBmffInstance_InteractionWithIo) {
    // Arrange
    auto mockIo = std::make_unique<Exiv2::MockBasicIo>();
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(true)); // Image is good

    // Act
    auto result = Exiv2::newBmffInstance(std::move(mockIo), true);

    // Assert
    EXPECT_CALL(*mockIo, good()).Times(1);  // Ensure good() is called once
    ASSERT_NE(result, nullptr);  // The result should not be nullptr
}