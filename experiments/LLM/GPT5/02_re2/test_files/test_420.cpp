// File: ./TestProjects/re2/re2/tests/prog_prefixaccel_frontandback_test.cc
#include "re2/prog.h"
#include <gtest/gtest.h>
#include <cstring>
#include <string>

using re2::Prog;

class PrefixAccelFrontBackTest_420 : public ::testing::Test {
protected:
    void SetUp() override {
        // Configure a 2-byte prefix so that:
        //  - front byte is 'a'
        //  - back  byte is 'b'
        // We do not assume anything else about internal state.
        prog_.ConfigurePrefixAccel("ab", /*prefix_foldcase=*/false);
    }
    Prog prog_;
};

// Size smaller than prefix size should return NULL (no dereference of data needed).
TEST_F(PrefixAccelFrontBackTest_420, ReturnsNullWhenSizeLessThanPrefix_420) {
    const std::string s = "a"; // size 1 < prefix size 2
    const void* out = prog_.PrefixAccel_FrontAndBack(s.data(), s.size());
    EXPECT_EQ(out, nullptr);
}

// Passing nullptr with size 0 should return NULL (observable behavior: no access).
TEST_F(PrefixAccelFrontBackTest_420, NullDataZeroSizeReturnsNull_420) {
    const void* out = prog_.PrefixAccel_FrontAndBack(nullptr, 0);
    EXPECT_EQ(out, nullptr);
}

// If there is no front byte in the buffer, result is NULL.
TEST_F(PrefixAccelFrontBackTest_420, NoFrontByteReturnsNull_420) {
    const std::string s = "cccccccc";
    const void* out = prog_.PrefixAccel_FrontAndBack(s.data(), s.size());
    EXPECT_EQ(out, nullptr);
}

// Finds the first position where front byte appears and the char (prefix_size_-1) later equals back byte.
// For prefix "ab", that means "ab" occurs; the returned pointer should point to the 'a'.
TEST_F(PrefixAccelFrontBackTest_420, ReturnsPointerToFirstFrontBackMatch_420) {
    // multiple candidates; only the first "ab" should be reported
    const std::string s = "zzzaazzabxxab";
    const char* base = s.data();

    const void* out = prog_.PrefixAccel_FrontAndBack(base, s.size());
    ASSERT_NE(out, nullptr);

    ptrdiff_t idx = static_cast<const char*>(out) - base;
    // "zzzaazzabxxab"
    //        ^^ first "ab" starts at index 7
    EXPECT_EQ(idx, 7);
}

// Ensures it skips front bytes that are NOT followed by the required back byte at offset (prefix_size_-1).
TEST_F(PrefixAccelFrontBackTest_420, SkipsMismatchedPairs_420) {
    // 'a' appears many times, but only one is followed by 'b' at the correct distance.
    const std::string s = "aaacaaadaaaeab"; // only the last "ab" is valid for prefix "ab"
    const char* base = s.data();

    const void* out = prog_.PrefixAccel_FrontAndBack(base, s.size());
    ASSERT_NE(out, nullptr);

    ptrdiff_t idx = static_cast<const char*>(out) - base;
    // index of the final "ab"
    EXPECT_EQ(idx, static_cast<ptrdiff_t>(s.size() - 2));
}

// Match located at the last possible start position in the buffer should be found.
TEST_F(PrefixAccelFrontBackTest_420, MatchAtBufferEnd_420) {
    // Last two bytes are "ab"
    const std::string s = "xxxxxxab";
    const char* base = s.data();

    const void* out = prog_.PrefixAccel_FrontAndBack(base, s.size());
    ASSERT_NE(out, nullptr);

    ptrdiff_t idx = static_cast<const char*>(out) - base;
    EXPECT_EQ(idx, static_cast<ptrdiff_t>(s.size() - 2)); // start of trailing "ab"
}

// When no valid front/back combo exists, expect NULL even if many front bytes occur.
TEST_F(PrefixAccelFrontBackTest_420, ManyFrontsNoBacksReturnsNull_420) {
    const std::string s = "aaaaaaaccccc"; // lots of 'a', but never 'b' at the needed spot
    const void* out = prog_.PrefixAccel_FrontAndBack(s.data(), s.size());
    EXPECT_EQ(out, nullptr);
}

// (Optional) Demonstrate behavior with data that begins with a match (index 0).
TEST_F(PrefixAccelFrontBackTest_420, MatchAtBeginning_420) {
    const std::string s = "abxxxxab";
    const char* base = s.data();

    const void* out = prog_.PrefixAccel_FrontAndBack(base, s.size());
    ASSERT_NE(out, nullptr);

    ptrdiff_t idx = static_cast<const char*>(out) - base;
    EXPECT_EQ(idx, 0);
}
