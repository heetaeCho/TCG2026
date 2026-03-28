#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPUtils.h"
#include "XMP_Const.h"

// Mock external dependencies (if needed)
class MockXMPUtils {
public:
    MOCK_METHOD(void, ThrowError, (const char*, int), ());
};

// TEST: Normal Operation

TEST_F(DecodeBase64CharTest_1982, DecodeBase64Char_UppercaseLetter_1982) {
    unsigned char ch = 'A';
    unsigned char result = DecodeBase64Char(ch);
    EXPECT_EQ(result, 0);
}

TEST_F(DecodeBase64CharTest_1983, DecodeBase64Char_LowercaseLetter_1983) {
    unsigned char ch = 'a';
    unsigned char result = DecodeBase64Char(ch);
    EXPECT_EQ(result, 26);
}

TEST_F(DecodeBase64CharTest_1984, DecodeBase64Char_NumericChar_1984) {
    unsigned char ch = '0';
    unsigned char result = DecodeBase64Char(ch);
    EXPECT_EQ(result, 52);
}

TEST_F(DecodeBase64CharTest_1985, DecodeBase64Char_PlusSign_1985) {
    unsigned char ch = '+';
    unsigned char result = DecodeBase64Char(ch);
    EXPECT_EQ(result, 62);
}

TEST_F(DecodeBase64CharTest_1986, DecodeBase64Char_Slash_1986) {
    unsigned char ch = '/';
    unsigned char result = DecodeBase64Char(ch);
    EXPECT_EQ(result, 63);
}

// TEST: Boundary Conditions

TEST_F(DecodeBase64CharTest_1987, DecodeBase64Char_SpaceChar_1987) {
    unsigned char ch = ' ';
    unsigned char result = DecodeBase64Char(ch);
    EXPECT_EQ(result, 0xFF);  // Ignored by the caller, but should still return this value
}

TEST_F(DecodeBase64CharTest_1988, DecodeBase64Char_TabChar_1988) {
    unsigned char ch = kTab;
    unsigned char result = DecodeBase64Char(ch);
    EXPECT_EQ(result, 0xFF);  // Ignored by the caller
}

TEST_F(DecodeBase64CharTest_1989, DecodeBase64Char_LineFeedChar_1989) {
    unsigned char ch = kLF;
    unsigned char result = DecodeBase64Char(ch);
    EXPECT_EQ(result, 0xFF);  // Ignored by the caller
}

TEST_F(DecodeBase64CharTest_1990, DecodeBase64Char_CarriageReturnChar_1990) {
    unsigned char ch = kCR;
    unsigned char result = DecodeBase64Char(ch);
    EXPECT_EQ(result, 0xFF);  // Ignored by the caller
}

// TEST: Exceptional or Error Cases

TEST_F(DecodeBase64CharTest_1991, DecodeBase64Char_InvalidChar_1991) {
    unsigned char ch = '#';  // Invalid base-64 character
    EXPECT_THROW({
        DecodeBase64Char(ch);
    }, const std::exception);  // XMP_Throw should throw an exception
}

// TEST: Mock Verification (External Dependency - XMP_Throw)

TEST_F(DecodeBase64CharTest_1992, DecodeBase64Char_InvalidChar_CallToThrow_1992) {
    unsigned char ch = '#';  // Invalid base-64 character
    MockXMPUtils mock;
    EXPECT_CALL(mock, ThrowError("Invalid base-64 encoded character", kXMPErr_BadParam))
        .Times(1);
    
    EXPECT_THROW({
        DecodeBase64Char(ch);
    }, const std::exception);  // XMP_Throw should throw an exception and call ThrowError
}