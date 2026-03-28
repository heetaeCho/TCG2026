#include <gtest/gtest.h>
#include <cstring>
#include <string>

// We need to declare the function since it's in an internal namespace
namespace re2 {
namespace re2_internal {
const char* TerminateNumber(char* buf, size_t nbuf, const char* str, size_t* np, bool accept_spaces);
}
}

using re2::re2_internal::TerminateNumber;

class TerminateNumberTest_272 : public ::testing::Test {
protected:
    char buf[256];
    size_t n;
};

// Test empty input (n == 0)
TEST_F(TerminateNumberTest_272, EmptyInput_ReturnsEmptyString_272) {
    n = 0;
    const char* result = TerminateNumber(buf, sizeof(buf), "123", &n, false);
    EXPECT_STREQ("", result);
}

// Test normal number without spaces or sign
TEST_F(TerminateNumberTest_272, NormalNumber_CopiedToBuffer_272) {
    const char* str = "12345";
    n = 5;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    EXPECT_STREQ("12345", result);
    EXPECT_EQ(5u, n);
}

// Test leading spaces with accept_spaces = false
TEST_F(TerminateNumberTest_272, LeadingSpaces_NotAccepted_ReturnsEmpty_272) {
    const char* str = " 123";
    n = 4;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    EXPECT_STREQ("", result);
}

// Test leading spaces with accept_spaces = true
TEST_F(TerminateNumberTest_272, LeadingSpaces_Accepted_SkipsSpaces_272) {
    const char* str = "  123";
    n = 5;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, true);
    EXPECT_STREQ("123", result);
    EXPECT_EQ(3u, n);
}

// Test negative number
TEST_F(TerminateNumberTest_272, NegativeNumber_PreservesMinus_272) {
    const char* str = "-456";
    n = 4;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    EXPECT_STREQ("-456", result);
    EXPECT_EQ(4u, n);
}

// Test leading zeros removal (triple zero case: 00X where X is 0)
TEST_F(TerminateNumberTest_272, LeadingZeros_Compressed_272) {
    const char* str = "00042";
    n = 5;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    // str[0]='0', str[1]='0', so we enter the while loop
    // str[2]='0' -> skip, n=4, str becomes "0042"
    // str[2]='4' -> stop
    EXPECT_STREQ("0042", result);
    EXPECT_EQ(4u, n);
}

// Test leading zeros with all zeros
TEST_F(TerminateNumberTest_272, AllZeros_CompressedToMinimal_272) {
    const char* str = "00000";
    n = 5;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    // Starts with 00, enters while: str[2]='0' -> skip repeatedly
    // After loop: n=3, str points to "000" (the last three zeros)
    // Actually let's trace: initial str="00000", n=5
    // str[0]='0', str[1]='0' -> enter while
    // n>=3(5>=3) and str[2]='0' -> n=4, str="0000"
    // n>=3(4>=3) and str[2]='0' -> n=3, str="000"
    // n>=3(3>=3) and str[2]='0' -> n=2, str="00"  -- wait, n>=3 check: n=3>=3 yes, str[2]='0' yes -> n=2, str++
    // Now n=2, n>=3 is false, exit
    // result = "00" with n=2
    EXPECT_STREQ("00", result);
    EXPECT_EQ(2u, n);
}

// Test negative with leading zeros
TEST_F(TerminateNumberTest_272, NegativeWithLeadingZeros_272) {
    const char* str = "-00042";
    n = 6;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    // neg=true, n=5, str="00042"
    // str[0]='0', str[1]='0' -> enter while
    // str[2]='0' -> n=4, str="0042"
    // str[2]='4' -> stop
    // neg: n=5, str-- -> str points to one before "0042"
    // Then memmove copies 5 bytes, buf[0] set to '-'
    // So result should be "-0042"
    EXPECT_STREQ("-0042", result);
    EXPECT_EQ(5u, n);
}

// Test buffer too small
TEST_F(TerminateNumberTest_272, BufferTooSmall_ReturnsEmpty_272) {
    char smallbuf[3];
    const char* str = "12345";
    n = 5;
    const char* result = TerminateNumber(smallbuf, sizeof(smallbuf), str, &n, false);
    // n(5) > nbuf-1(2) -> returns ""
    EXPECT_STREQ("", result);
}

// Test buffer exactly fits
TEST_F(TerminateNumberTest_272, BufferExactFit_272) {
    char exactbuf[4];  // nbuf=4, so can hold n up to 3
    const char* str = "123";
    n = 3;
    const char* result = TerminateNumber(exactbuf, sizeof(exactbuf), str, &n, false);
    EXPECT_STREQ("123", result);
    EXPECT_EQ(3u, n);
}

// Test buffer one too small
TEST_F(TerminateNumberTest_272, BufferOneTooSmall_ReturnsEmpty_272) {
    char smallbuf[3];  // nbuf=3, so can hold n up to 2
    const char* str = "123";
    n = 3;
    const char* result = TerminateNumber(smallbuf, sizeof(smallbuf), str, &n, false);
    EXPECT_STREQ("", result);
}

// Test single digit
TEST_F(TerminateNumberTest_272, SingleDigit_272) {
    const char* str = "7";
    n = 1;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    EXPECT_STREQ("7", result);
    EXPECT_EQ(1u, n);
}

// Test just a minus sign
TEST_F(TerminateNumberTest_272, JustMinus_272) {
    const char* str = "-";
    n = 1;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    // neg=true, n=0, str++ (past '-')
    // n<3 so no leading zero removal
    // neg: n=1, str--
    // n(1) <= nbuf-1(255), memmove 1 byte, buf[0]='-', buf[1]='\0'
    EXPECT_STREQ("-", result);
    EXPECT_EQ(1u, n);
}

// Test multiple spaces then number with accept_spaces
TEST_F(TerminateNumberTest_272, MultipleSpacesThenNumber_272) {
    const char* str = "   42";
    n = 5;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, true);
    EXPECT_STREQ("42", result);
    EXPECT_EQ(2u, n);
}

// Test tab as space character with accept_spaces
TEST_F(TerminateNumberTest_272, TabAsSpace_Accepted_272) {
    const char* str = "\t99";
    n = 3;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, true);
    EXPECT_STREQ("99", result);
    EXPECT_EQ(2u, n);
}

// Test all spaces with accept_spaces - results in n=0
TEST_F(TerminateNumberTest_272, AllSpaces_AcceptSpaces_ReturnsEmpty_272) {
    const char* str = "   ";
    n = 3;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, true);
    // After skipping spaces, n=0, then the function checks n==0 at the beginning?
    // No, actually the space-skipping is after the n==0 check
    // After spaces: n=0, str past all spaces
    // Then neg check: n>=1 is false
    // Then leading zeros: n>=3 is false
    // neg is false
    // n(0) > nbuf-1? 0 > 255? No
    // memmove 0 bytes, buf[0]='\0'
    // *np = 0
    EXPECT_EQ(0u, n);
    EXPECT_STREQ("", result);
}

// Test spaces then negative number
TEST_F(TerminateNumberTest_272, SpacesThenNegative_AcceptSpaces_272) {
    const char* str = "  -123";
    n = 6;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, true);
    EXPECT_STREQ("-123", result);
    EXPECT_EQ(4u, n);
}

// Test "00" exactly (two zeros, n < 3 so no leading zero loop)
TEST_F(TerminateNumberTest_272, TwoZeros_NoCompression_272) {
    const char* str = "00";
    n = 2;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    // n>=3 is false, so no leading zero removal
    EXPECT_STREQ("00", result);
    EXPECT_EQ(2u, n);
}

// Test "001" - three chars starting with 00, but str[2] is not 0
TEST_F(TerminateNumberTest_272, DoubleZeroThenNonZero_272) {
    const char* str = "001";
    n = 3;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    // str[0]='0', str[1]='0' -> enter while
    // str[2]='1' -> condition false, don't skip
    EXPECT_STREQ("001", result);
    EXPECT_EQ(3u, n);
}

// Test "000" - three zeros
TEST_F(TerminateNumberTest_272, TripleZero_272) {
    const char* str = "000";
    n = 3;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    // str[0]='0', str[1]='0' -> enter while
    // n>=3(3>=3) and str[2]='0' -> n=2, str++
    // n>=3? 2>=3? No -> exit
    EXPECT_STREQ("00", result);
    EXPECT_EQ(2u, n);
}

// Test that result pointer equals buf for valid cases
TEST_F(TerminateNumberTest_272, ResultPointerEqualsBuf_272) {
    const char* str = "42";
    n = 2;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    EXPECT_EQ(buf, result);
}

// Test negative with buffer barely fitting
TEST_F(TerminateNumberTest_272, NegativeBufferBareFit_272) {
    char smallbuf[5];  // can hold up to 4 chars + null
    const char* str = "-123";
    n = 4;
    const char* result = TerminateNumber(smallbuf, sizeof(smallbuf), str, &n, false);
    EXPECT_STREQ("-123", result);
    EXPECT_EQ(4u, n);
}

// Test negative with buffer too small
TEST_F(TerminateNumberTest_272, NegativeBufferTooSmall_272) {
    char smallbuf[4];  // can hold up to 3 chars + null
    const char* str = "-123";
    n = 4;
    const char* result = TerminateNumber(smallbuf, sizeof(smallbuf), str, &n, false);
    EXPECT_STREQ("", result);
}

// Test that np is updated correctly after space skipping
TEST_F(TerminateNumberTest_272, NpUpdatedAfterSpaceSkipping_272) {
    const char* str = "    5";
    n = 5;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, true);
    EXPECT_STREQ("5", result);
    EXPECT_EQ(1u, n);
}

// Test non-00 prefix doesn't trigger zero compression
TEST_F(TerminateNumberTest_272, NonDoubleZeroPrefix_NoCompression_272) {
    const char* str = "10042";
    n = 5;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    EXPECT_STREQ("10042", result);
    EXPECT_EQ(5u, n);
}

// Test "0" prefix alone (single zero, no 00)
TEST_F(TerminateNumberTest_272, SingleZeroPrefix_NoCompression_272) {
    const char* str = "042";
    n = 3;
    const char* result = TerminateNumber(buf, sizeof(buf), str, &n, false);
    // str[0]='0', str[1]='4' -> condition str[1]=='0' is false
    EXPECT_STREQ("042", result);
    EXPECT_EQ(3u, n);
}
