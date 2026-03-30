#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mocks for any external dependencies (if needed)
class MockBaseStream {
public:
    MOCK_METHOD(bool, isBinary, (bool last), (const));
};

class BaseStreamStreamTest_1491 : public testing::Test {
protected:
    // You can setup any necessary test fixtures here
    MockBaseStream* mockBaseStream;

    virtual void SetUp() {
        mockBaseStream = new MockBaseStream();
    }

    virtual void TearDown() {
        delete mockBaseStream;
    }
};

TEST_F(BaseStreamStreamTest_1491, isBinaryReturnsTrue_1491) {
    // Arrange
    BaseStreamStream baseStream;
    EXPECT_CALL(*mockBaseStream, isBinary(testing::_))
        .WillOnce(testing::Return(true));

    // Act
    bool result = baseStream.isBinary();

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(BaseStreamStreamTest_1491, isBinaryReturnsFalse_1491) {
    // Arrange
    BaseStreamStream baseStream;
    EXPECT_CALL(*mockBaseStream, isBinary(testing::_))
        .WillOnce(testing::Return(false));

    // Act
    bool result = baseStream.isBinary();

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(BaseStreamStreamTest_1491, isBinaryWithFalseLast_1491) {
    // Arrange
    BaseStreamStream baseStream;
    EXPECT_CALL(*mockBaseStream, isBinary(testing::_))
        .WillOnce(testing::Return(true));

    // Act
    bool result = baseStream.isBinary(false);

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(BaseStreamStreamTest_1491, isBinaryExceptionHandling_1491) {
    // Arrange
    BaseStreamStream baseStream;
    EXPECT_CALL(*mockBaseStream, isBinary(testing::_))
        .WillOnce(testing::Throw(std::runtime_error("Test Exception")));

    // Act & Assert
    try {
        bool result = baseStream.isBinary();
        FAIL() << "Expected exception but none thrown";
    } catch (const std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Test Exception");
    }
}