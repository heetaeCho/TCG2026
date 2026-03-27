#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include "XMLParserAdapter.hpp"

using namespace ::testing;

// Mock class for XMLParserAdapter
class MockXMLParserAdapter : public XMLParserAdapter {
public:
    MOCK_METHOD(void, ParseBuffer, (const void* buffer, size_t length, bool last), (override));
};

// Test suite for ProcessUTF8Portion function
class ProcessUTF8PortionTest : public testing::Test {
protected:
    MockXMLParserAdapter mockParser;
};

// TEST_ID: 1973
TEST_F(ProcessUTF8PortionTest, NormalOperation_ValidUTF8) {
    // Prepare input for a valid UTF-8 portion
    const unsigned char buffer[] = {0xE2, 0x82, 0xAC};  // Example of a valid UTF-8 character (Euro symbol)
    size_t length = sizeof(buffer);
    
    // Set up expectations: ParseBuffer should be called
    EXPECT_CALL(mockParser, ParseBuffer(_, _, _)).Times(1);

    // Call the function
    size_t result = ProcessUTF8Portion(&mockParser, buffer, length, true);

    // Verify the result is the length of the buffer (since it's a valid UTF-8 sequence)
    EXPECT_EQ(result, length);
}

// TEST_ID: 1974
TEST_F(ProcessUTF8PortionTest, BoundaryCondition_SingleByteCharacter) {
    // Test a single byte character (valid ASCII)
    const unsigned char buffer[] = {0x41};  // 'A' in ASCII
    size_t length = sizeof(buffer);

    // Expect ParseBuffer to be called with the input buffer
    EXPECT_CALL(mockParser, ParseBuffer(_, _, _)).Times(1);

    // Call the function
    size_t result = ProcessUTF8Portion(&mockParser, buffer, length, true);

    // The length should be the same
    EXPECT_EQ(result, length);
}

// TEST_ID: 1975
TEST_F(ProcessUTF8PortionTest, InvalidUTF8_OverlongSequence) {
    // Test an overlong UTF-8 sequence (invalid)
    const unsigned char buffer[] = {0xF0, 0x80, 0x80, 0x80};  // Invalid overlong UTF-8 sequence
    size_t length = sizeof(buffer);

    // Expect ParseBuffer to be called with an invalid sequence
    EXPECT_CALL(mockParser, ParseBuffer(_, _, _)).Times(1);

    // Call the function and verify the result
    size_t result = ProcessUTF8Portion(&mockParser, buffer, length, true);
    EXPECT_EQ(result, length);
}

// TEST_ID: 1976
TEST_F(ProcessUTF8PortionTest, ErrorCase_InvalidCharacterInBuffer) {
    // Test an invalid character in the buffer (ASCII control character)
    const unsigned char buffer[] = {0x19};  // Control character (non-printable)
    size_t length = sizeof(buffer);

    // Expect ParseBuffer to be called with a replacement for the invalid character
    EXPECT_CALL(mockParser, ParseBuffer(_, _, _)).Times(1);

    // Call the function
    size_t result = ProcessUTF8Portion(&mockParser, buffer, length, true);

    // The result should still be the length of the buffer, with the invalid character replaced
    EXPECT_EQ(result, length);
}

// TEST_ID: 1977
TEST_F(ProcessUTF8PortionTest, BoundaryCondition_EscapedCharacter) {
    // Test a character that requires escape processing
    const unsigned char buffer[] = {0x26};  // '&' character, requires escaping
    size_t length = sizeof(buffer);

    // Expect ParseBuffer to be called with the escaped form
    EXPECT_CALL(mockParser, ParseBuffer(_, _, _)).Times(1);

    // Call the function
    size_t result = ProcessUTF8Portion(&mockParser, buffer, length, true);

    // The result should be the length of the buffer
    EXPECT_EQ(result, length);
}

// TEST_ID: 1978
TEST_F(ProcessUTF8PortionTest, ErrorCase_UnexpectedEndOfBuffer) {
    // Test case where the buffer ends unexpectedly (mid-sequence)
    const unsigned char buffer[] = {0xE2, 0x82};  // Incomplete UTF-8 sequence
    size_t length = sizeof(buffer);

    // Expect ParseBuffer to be called with partial data
    EXPECT_CALL(mockParser, ParseBuffer(_, _, _)).Times(1);

    // Call the function and check that it handles the error properly
    size_t result = ProcessUTF8Portion(&mockParser, buffer, length, false);

    // Return should be the length of processed portion
    EXPECT_EQ(result, 2);
}