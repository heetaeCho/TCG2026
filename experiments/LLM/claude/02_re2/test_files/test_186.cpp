#include <gtest/gtest.h>

// Include the header or declare the necessary types and functions
// Based on the provided code, we need these declarations:

struct pcre;
struct pcre_extra;

#define PCRE_ERROR_NOMATCH 1
#define PCRE_EXTRA_MATCH_LIMIT 0
#define PCRE_INFO_CAPTURECOUNT 0
#define PCRE_EXTRA_MATCH_LIMIT_RECURSION 0
#define PCRE_ANCHORED 0
#define PCRE_ERROR_RECURSIONLIMIT 3
#define PCRE_NOTEMPTY 0
#define PCRE_ERROR_MATCHLIMIT 2

extern int pcre_exec(const pcre*, const pcre_extra*, const char*, int, int, int, int*, int);

class PcreTest_186 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that PCRE error/option constants have expected values
TEST_F(PcreTest_186, ErrorNoMatchConstantValue_186) {
    EXPECT_EQ(PCRE_ERROR_NOMATCH, 1);
}

TEST_F(PcreTest_186, ErrorMatchLimitConstantValue_186) {
    EXPECT_EQ(PCRE_ERROR_MATCHLIMIT, 2);
}

TEST_F(PcreTest_186, ErrorRecursionLimitConstantValue_186) {
    EXPECT_EQ(PCRE_ERROR_RECURSIONLIMIT, 3);
}

TEST_F(PcreTest_186, ExtraMatchLimitConstantValue_186) {
    EXPECT_EQ(PCRE_EXTRA_MATCH_LIMIT, 0);
}

TEST_F(PcreTest_186, InfoCaptureCountConstantValue_186) {
    EXPECT_EQ(PCRE_INFO_CAPTURECOUNT, 0);
}

TEST_F(PcreTest_186, ExtraMatchLimitRecursionConstantValue_186) {
    EXPECT_EQ(PCRE_EXTRA_MATCH_LIMIT_RECURSION, 0);
}

TEST_F(PcreTest_186, AnchoredConstantValue_186) {
    EXPECT_EQ(PCRE_ANCHORED, 0);
}

TEST_F(PcreTest_186, NotEmptyConstantValue_186) {
    EXPECT_EQ(PCRE_NOTEMPTY, 0);
}

// Test pcre_exec with null pointers
TEST_F(PcreTest_186, PcreExecWithNullPointersReturnsZero_186) {
    int result = pcre_exec(nullptr, nullptr, nullptr, 0, 0, 0, nullptr, 0);
    EXPECT_EQ(result, 0);
}

// Test pcre_exec with valid subject string
TEST_F(PcreTest_186, PcreExecWithValidStringReturnsZero_186) {
    const char* subject = "hello world";
    int ovector[30];
    int result = pcre_exec(nullptr, nullptr, subject, 11, 0, 0, ovector, 30);
    EXPECT_EQ(result, 0);
}

// Test pcre_exec with empty string
TEST_F(PcreTest_186, PcreExecWithEmptyStringReturnsZero_186) {
    const char* subject = "";
    int ovector[30];
    int result = pcre_exec(nullptr, nullptr, subject, 0, 0, 0, ovector, 30);
    EXPECT_EQ(result, 0);
}

// Test pcre_exec with non-zero start offset
TEST_F(PcreTest_186, PcreExecWithNonZeroStartOffsetReturnsZero_186) {
    const char* subject = "hello world";
    int ovector[30];
    int result = pcre_exec(nullptr, nullptr, subject, 11, 5, 0, ovector, 30);
    EXPECT_EQ(result, 0);
}

// Test pcre_exec with various option flags
TEST_F(PcreTest_186, PcreExecWithAnchoredFlagReturnsZero_186) {
    const char* subject = "test";
    int ovector[30];
    int result = pcre_exec(nullptr, nullptr, subject, 4, 0, PCRE_ANCHORED, ovector, 30);
    EXPECT_EQ(result, 0);
}

TEST_F(PcreTest_186, PcreExecWithNotEmptyFlagReturnsZero_186) {
    const char* subject = "test";
    int ovector[30];
    int result = pcre_exec(nullptr, nullptr, subject, 4, 0, PCRE_NOTEMPTY, ovector, 30);
    EXPECT_EQ(result, 0);
}

// Test pcre_exec with zero ovector size
TEST_F(PcreTest_186, PcreExecWithZeroOvecSizeReturnsZero_186) {
    const char* subject = "test";
    int result = pcre_exec(nullptr, nullptr, subject, 4, 0, 0, nullptr, 0);
    EXPECT_EQ(result, 0);
}

// Test pcre_exec return value is consistent across multiple calls
TEST_F(PcreTest_186, PcreExecConsistentReturnValue_186) {
    const char* subject = "abc";
    int ovector[30];
    int result1 = pcre_exec(nullptr, nullptr, subject, 3, 0, 0, ovector, 30);
    int result2 = pcre_exec(nullptr, nullptr, subject, 3, 0, 0, ovector, 30);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, 0);
}

// Verify error constants are distinct where expected
TEST_F(PcreTest_186, ErrorConstantsAreDistinct_186) {
    EXPECT_NE(PCRE_ERROR_NOMATCH, PCRE_ERROR_MATCHLIMIT);
    EXPECT_NE(PCRE_ERROR_NOMATCH, PCRE_ERROR_RECURSIONLIMIT);
    EXPECT_NE(PCRE_ERROR_MATCHLIMIT, PCRE_ERROR_RECURSIONLIMIT);
}

// Test pcre_exec with large length parameter
TEST_F(PcreTest_186, PcreExecWithLargeLengthReturnsZero_186) {
    const char* subject = "test string";
    int ovector[30];
    int result = pcre_exec(nullptr, nullptr, subject, 1000000, 0, 0, ovector, 30);
    EXPECT_EQ(result, 0);
}

// Test pcre_exec with negative length
TEST_F(PcreTest_186, PcreExecWithNegativeLengthReturnsZero_186) {
    const char* subject = "test";
    int ovector[30];
    int result = pcre_exec(nullptr, nullptr, subject, -1, 0, 0, ovector, 30);
    EXPECT_EQ(result, 0);
}
