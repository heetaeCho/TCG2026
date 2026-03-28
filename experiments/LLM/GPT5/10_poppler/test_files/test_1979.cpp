#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock dependencies (if necessary)
class MockStream : public Stream {
public:
    MOCK_METHOD(unsigned int, readBit, (), (override));
    MOCK_METHOD(void, resetInputBits, (), (override));
    MOCK_METHOD(bool, atEOF, (), (const, override));
};

// Test fixture for StreamBitReader
class StreamBitReaderTest_1979 : public ::testing::Test {
protected:
    MockStream* mockStream;
    StreamBitReader* bitReader;

    void SetUp() override {
        mockStream = new MockStream();
        bitReader = new StreamBitReader(mockStream);
    }

    void TearDown() override {
        delete bitReader;
        delete mockStream;
    }
};

// Test case for normal operation (reading a single bit)
TEST_F(StreamBitReaderTest_1979, ReadBitNormalOperation_1979) {
    // Set expectations for the mock Stream
    EXPECT_CALL(*mockStream, readBit())
        .WillOnce(testing::Return(1)); // Simulating reading a bit

    // Act: Call readBits with n = 1
    unsigned int result = bitReader->readBits(1);

    // Assert: The result should be the single bit value
    EXPECT_EQ(result, 1);
}

// Test case for reading zero bits
TEST_F(StreamBitReaderTest_1979, ReadBitsZeroBits_1979) {
    // Act: Call readBits with n = 0
    unsigned int result = bitReader->readBits(0);

    // Assert: The result should be 0
    EXPECT_EQ(result, 0);
}

// Test case for exceptional case where readBits is called with negative bits
TEST_F(StreamBitReaderTest_1979, ReadBitsNegative_1979) {
    // Act: Call readBits with a negative number
    unsigned int result = bitReader->readBits(-1);

    // Assert: The result should be -1
    EXPECT_EQ(result, -1);
}

// Test case for reaching EOF while reading bits
TEST_F(StreamBitReaderTest_1979, ReadBitsAtEOF_1979) {
    // Set expectations for the mock Stream
    EXPECT_CALL(*mockStream, readBit())
        .WillOnce(testing::Return(1));
    EXPECT_CALL(*mockStream, atEOF())
        .WillOnce(testing::Return(true)); // Simulate EOF after one bit

    // Act: Call readBits with n = 2
    unsigned int result = bitReader->readBits(2);

    // Assert: The result should be -1 because we reached EOF
    EXPECT_EQ(result, -1);
}

// Test case for reading multiple bits
TEST_F(StreamBitReaderTest_1979, ReadMultipleBits_1979) {
    // Set expectations for the mock Stream
    EXPECT_CALL(*mockStream, readBit())
        .WillOnce(testing::Return(1))   // First bit
        .WillOnce(testing::Return(0));  // Second bit

    // Act: Call readBits with n = 2
    unsigned int result = bitReader->readBits(2);

    // Assert: The result should be 2 (binary 10)
    EXPECT_EQ(result, 2);
}

// Test case for reading bits when the stream is at EOF initially
TEST_F(StreamBitReaderTest_1979, ReadBitsAtStartEOF_1979) {
    // Set expectations for the mock Stream
    EXPECT_CALL(*mockStream, atEOF())
        .WillOnce(testing::Return(true)); // Simulate EOF at the start

    // Act: Call readBits with n = 3
    unsigned int result = bitReader->readBits(3);

    // Assert: The result should be -1 because we're at EOF
    EXPECT_EQ(result, -1);
}