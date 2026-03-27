#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/Hints.cc"  // Adjust the include path as necessary

// Mock Stream class for external dependencies
class MockStream : public Stream {
public:
    MOCK_METHOD(int, getChar, (), (override));
};

// Unit test class
class StreamBitReaderTest_1978 : public ::testing::Test {
protected:
    // Test Setup: Initialize the necessary objects
    MockStream mockStream;
    StreamBitReader bitReader{&mockStream};

    StreamBitReaderTest_1978() {
        // Set up expectations for the MockStream if needed.
        ON_CALL(mockStream, getChar()).WillByDefault(testing::Return(1));
    }
};

// Test: Verifying the normal operation of readBit() method
TEST_F(StreamBitReaderTest_1978, ReadBit_ValidBit) {
    EXPECT_CALL(mockStream, getChar()).Times(testing::AtLeast(1)); // Expecting at least one call to getChar
    unsigned int bit = bitReader.readBit();
    EXPECT_NE(bit, (unsigned int)-1);  // Expect a valid bit value
}

// Test: Boundary condition - EOF (End of File)
TEST_F(StreamBitReaderTest_1978, ReadBit_EndOfFile) {
    // Simulate EOF by returning EOF from getChar()
    ON_CALL(mockStream, getChar()).WillByDefault(testing::Return(EOF));
    unsigned int bit = bitReader.readBit();
    EXPECT_EQ(bit, (unsigned int)-1);  // Expect EOF, hence -1 should be returned
}

// Test: Boundary condition - Reset input bits
TEST_F(StreamBitReaderTest_1978, ResetInputBits) {
    bitReader.resetInputBits();
    unsigned int bit = bitReader.readBit();
    EXPECT_NE(bit, (unsigned int)-1);  // Expect a valid bit after reset
}

// Test: Verifying the atEOF() method returns correct EOF state
TEST_F(StreamBitReaderTest_1978, AtEOF_CorrectState) {
    // Simulate EOF by setting the state directly
    bitReader.readBit();
    EXPECT_TRUE(bitReader.atEOF());  // Should indicate EOF after reading a bit that returned -1
}

// Test: Boundary condition - Edge case with a single bit read
TEST_F(StreamBitReaderTest_1978, ReadSingleBit_EdgeCase) {
    // Simulate a scenario where only 1 bit is being read
    ON_CALL(mockStream, getChar()).WillByDefault(testing::Return(0b10000000)); // Returning a byte with the first bit set
    unsigned int bit = bitReader.readBit();
    EXPECT_EQ(bit, 1);  // Expect the first bit (1)
}

// Test: Exceptional case - Invalid stream behavior (error handling)
TEST_F(StreamBitReaderTest_1978, ReadBit_InvalidStream) {
    // Simulate a failure in getChar() (e.g., throwing an exception or error state)
    ON_CALL(mockStream, getChar()).WillByDefault(testing::Return(EOF));
    unsigned int bit = bitReader.readBit();
    EXPECT_EQ(bit, (unsigned int)-1);  // Expect -1 (EOF) when stream fails
}