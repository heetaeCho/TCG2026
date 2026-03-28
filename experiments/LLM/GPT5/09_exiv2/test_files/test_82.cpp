#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "riffvideo.h"
#include "basicio.h"

namespace Exiv2 {

// Mock class for BasicIo
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(bool, good, (), (const, override));
};

// Test Fixture
class RiffVideoTest : public ::testing::Test {
protected:
    std::unique_ptr<MockBasicIo> mockIo;

    void SetUp() override {
        mockIo = std::make_unique<MockBasicIo>();
    }

    void TearDown() override {
        mockIo.reset();
    }
};

// Normal Operation: Image creation succeeds when IO is good
TEST_F(RiffVideoTest, CreateRiffVideo_Success_82) {
    // Arrange
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(true));

    // Act
    auto image = newRiffInstance(std::move(mockIo), true);

    // Assert
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

// Boundary Condition: Image creation fails when IO is not good
TEST_F(RiffVideoTest, CreateRiffVideo_Failure_82) {
    // Arrange
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(false));

    // Act
    auto image = newRiffInstance(std::move(mockIo), true);

    // Assert
    ASSERT_EQ(image, nullptr);
}

// Exceptional Case: Test that good() method is invoked once when creating the image
TEST_F(RiffVideoTest, VerifyGoodMethodCall_82) {
    // Arrange
    EXPECT_CALL(*mockIo, good()).WillOnce(testing::Return(true));

    // Act
    auto image = newRiffInstance(std::move(mockIo), true);

    // Assert
    ASSERT_NE(image, nullptr);
    testing::Mock::VerifyAndClearExpectations(mockIo.get());
}

// Error Case: Test when null io is passed
TEST_F(RiffVideoTest, NullIoPassed_82) {
    // Act
    auto image = newRiffInstance(nullptr, true);

    // Assert
    ASSERT_EQ(image, nullptr);
}

}  // namespace Exiv2