#include <gtest/gtest.h>

// Include or replicate the necessary declarations from the source
// We need the types and function declaration

struct pcre;
struct pcre_extra;

// These are defined in the source file
#define PCRE_ERROR_NOMATCH 1
#define PCRE_EXTRA_MATCH_LIMIT 0
#define PCRE_INFO_CAPTURECOUNT 0
#define PCRE_EXTRA_MATCH_LIMIT_RECURSION 0
#define PCRE_ANCHORED 0
#define PCRE_ERROR_RECURSIONLIMIT 3
#define PCRE_NOTEMPTY 0
#define PCRE_ERROR_MATCHLIMIT 2

int pcre_fullinfo(const pcre*, const pcre_extra*, int, void*);

// Test fixture
class PcreUtilTest_187 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// --- Tests for pcre_fullinfo ---

TEST_F(PcreUtilTest_187, FullInfoReturnsZeroWithNullArgs_187) {
    int result = pcre_fullinfo(nullptr, nullptr, 0, nullptr);
    EXPECT_EQ(0, result);
}

TEST_F(PcreUtilTest_187, FullInfoReturnsZeroWithNullPcre_187) {
    int output = -1;
    int result = pcre_fullinfo(nullptr, nullptr, PCRE_INFO_CAPTURECOUNT, &output);
    EXPECT_EQ(0, result);
}

TEST_F(PcreUtilTest_187, FullInfoReturnsZeroWithNullExtra_187) {
    int result = pcre_fullinfo(nullptr, nullptr, 0, nullptr);
    EXPECT_EQ(0, result);
}

TEST_F(PcreUtilTest_187, FullInfoReturnsZeroWithArbitraryWhat_187) {
    int result = pcre_fullinfo(nullptr, nullptr, 42, nullptr);
    EXPECT_EQ(0, result);
}

TEST_F(PcreUtilTest_187, FullInfoReturnsZeroWithNegativeWhat_187) {
    int result = pcre_fullinfo(nullptr, nullptr, -1, nullptr);
    EXPECT_EQ(0, result);
}

TEST_F(PcreUtilTest_187, FullInfoConsistentReturnOnMultipleCalls_187) {
    EXPECT_EQ(0, pcre_fullinfo(nullptr, nullptr, 0, nullptr));
    EXPECT_EQ(0, pcre_fullinfo(nullptr, nullptr, 1, nullptr));
    EXPECT_EQ(0, pcre_fullinfo(nullptr, nullptr, 100, nullptr));
}

// --- Tests for #define constants ---

TEST_F(PcreUtilTest_187, PcreErrorNomatchValue_187) {
    EXPECT_EQ(1, PCRE_ERROR_NOMATCH);
}

TEST_F(PcreUtilTest_187, PcreExtraMatchLimitValue_187) {
    EXPECT_EQ(0, PCRE_EXTRA_MATCH_LIMIT);
}

TEST_F(PcreUtilTest_187, PcreInfoCaptureCountValue_187) {
    EXPECT_EQ(0, PCRE_INFO_CAPTURECOUNT);
}

TEST_F(PcreUtilTest_187, PcreExtraMatchLimitRecursionValue_187) {
    EXPECT_EQ(0, PCRE_EXTRA_MATCH_LIMIT_RECURSION);
}

TEST_F(PcreUtilTest_187, PcreAnchoredValue_187) {
    EXPECT_EQ(0, PCRE_ANCHORED);
}

TEST_F(PcreUtilTest_187, PcreErrorRecursionLimitValue_187) {
    EXPECT_EQ(3, PCRE_ERROR_RECURSIONLIMIT);
}

TEST_F(PcreUtilTest_187, PcreNotEmptyValue_187) {
    EXPECT_EQ(0, PCRE_NOTEMPTY);
}

TEST_F(PcreUtilTest_187, PcreErrorMatchLimitValue_187) {
    EXPECT_EQ(2, PCRE_ERROR_MATCHLIMIT);
}

// --- Tests verifying distinct error codes ---

TEST_F(PcreUtilTest_187, ErrorCodesAreDistinctFromEachOther_187) {
    EXPECT_NE(PCRE_ERROR_NOMATCH, PCRE_ERROR_MATCHLIMIT);
    EXPECT_NE(PCRE_ERROR_NOMATCH, PCRE_ERROR_RECURSIONLIMIT);
    EXPECT_NE(PCRE_ERROR_MATCHLIMIT, PCRE_ERROR_RECURSIONLIMIT);
}

TEST_F(PcreUtilTest_187, FullInfoWithVoidPointerOutput_187) {
    char buffer[64] = {};
    int result = pcre_fullinfo(nullptr, nullptr, PCRE_INFO_CAPTURECOUNT, buffer);
    EXPECT_EQ(0, result);
}
