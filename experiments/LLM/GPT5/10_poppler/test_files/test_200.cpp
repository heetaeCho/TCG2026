#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <optional>
#include "Stream.h" // Include the relevant header

// Mocking the Stream class to test EOFStream's behavior.
class MockStream : public Stream {
public:
    MOCK_METHOD(int, getChar, (), (override));
    MOCK_METHOD(int, lookChar, (), (override));
    MOCK_METHOD(StreamKind, getKind, (), (const, override));
    MOCK_METHOD(bool, rewind, (), (override));
    MOCK_METHOD(std::optional<std::string>, getPSFilter, (int, const char*), (override));
    MOCK_METHOD(bool, isBinary, (bool), (const, override));
};

class EOFStreamTest : public ::testing::Test {
protected:
    // MockStream is used to inject controlled behavior in EOFStream
    std::unique_ptr<MockStream> mockStream;

    void SetUp() override {
        mockStream = std::make_unique<MockStream>();
    }
};

TEST_F(EOFStreamTest, LookCharReturnsEOF_200) {
    // Arrange
    EXPECT_CALL(*mockStream, lookChar())
        .WillOnce(testing::Return(EOF));  // simulate EOFStream behavior

    EOFStream eofStream(std::move(mockStream));

    // Act
    int result = eofStream.lookChar();

    // Assert
    EXPECT_EQ(result, EOF) << "Expected EOF to be returned by lookChar";
}

TEST_F(EOFStreamTest, GetCharReturnsEOF_201) {
    // Arrange
    EXPECT_CALL(*mockStream, getChar())
        .WillOnce(testing::Return(EOF));  // simulate EOFStream behavior

    EOFStream eofStream(std::move(mockStream));

    // Act
    int result = eofStream.getChar();

    // Assert
    EXPECT_EQ(result, EOF) << "Expected EOF to be returned by getChar";
}

TEST_F(EOFStreamTest, RewindReturnsTrue_202) {
    // Arrange
    EXPECT_CALL(*mockStream, rewind())
        .WillOnce(testing::Return(true));  // simulate successful rewind

    EOFStream eofStream(std::move(mockStream));

    // Act
    bool result = eofStream.rewind();

    // Assert
    EXPECT_TRUE(result) << "Expected rewind to return true";
}

TEST_F(EOFStreamTest, RewindReturnsFalse_203) {
    // Arrange
    EXPECT_CALL(*mockStream, rewind())
        .WillOnce(testing::Return(false));  // simulate failed rewind

    EOFStream eofStream(std::move(mockStream));

    // Act
    bool result = eofStream.rewind();

    // Assert
    EXPECT_FALSE(result) << "Expected rewind to return false";
}

TEST_F(EOFStreamTest, GetPSFilterReturnsOptionalString_204) {
    // Arrange
    EXPECT_CALL(*mockStream, getPSFilter(testing::_, testing::_))
        .WillOnce(testing::Return(std::make_optional<std::string>("filterString"))); // simulate getting filter

    EOFStream eofStream(std::move(mockStream));

    // Act
    auto result = eofStream.getPSFilter(1, "indent");

    // Assert
    ASSERT_TRUE(result.has_value()) << "Expected a value from getPSFilter";
    EXPECT_EQ(result.value(), "filterString") << "Expected filter string to match";
}

TEST_F(EOFStreamTest, IsBinaryReturnsTrue_205) {
    // Arrange
    EXPECT_CALL(*mockStream, isBinary(testing::_))
        .WillOnce(testing::Return(true));  // simulate binary stream detection

    EOFStream eofStream(std::move(mockStream));

    // Act
    bool result = eofStream.isBinary(true);

    // Assert
    EXPECT_TRUE(result) << "Expected isBinary to return true";
}

TEST_F(EOFStreamTest, IsBinaryReturnsFalse_206) {
    // Arrange
    EXPECT_CALL(*mockStream, isBinary(testing::_))
        .WillOnce(testing::Return(false));  // simulate non-binary stream detection

    EOFStream eofStream(std::move(mockStream));

    // Act
    bool result = eofStream.isBinary(false);

    // Assert
    EXPECT_FALSE(result) << "Expected isBinary to return false";
}