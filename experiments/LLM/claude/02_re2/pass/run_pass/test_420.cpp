#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

// Helper to create a Prog with a configured prefix via ConfigurePrefixAccel
class PrefixAccelFrontAndBackTest_420 : public ::testing::Test {
 protected:
  // We use RE2 to compile patterns that produce a Prog with prefix acceleration.
  // Alternatively, we can create a Prog directly and call ConfigurePrefixAccel.
};

// Test: When data size is less than prefix_size_, returns NULL
TEST_F(PrefixAccelFrontAndBackTest_420, SizeSmallerThanPrefixReturnsNull_420) {
  Prog prog;
  // Configure a prefix of length 2: prefix_front_ = 'a', prefix_back_ = 'b'
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured (unexpected)";
  }
  
  // size=1, which is less than prefix_size_=2
  const char data[] = "x";
  const void* result = prog.PrefixAccel_FrontAndBack(data, 1);
  EXPECT_EQ(result, nullptr);
}

// Test: Exact match at the beginning of data
TEST_F(PrefixAccelFrontAndBackTest_420, ExactMatchAtBeginning_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  const char data[] = "abcdef";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data);
}

// Test: Match not at the beginning
TEST_F(PrefixAccelFrontAndBackTest_420, MatchInMiddle_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  const char data[] = "xxab";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data + 2);
}

// Test: No match returns NULL
TEST_F(PrefixAccelFrontAndBackTest_420, NoMatchReturnsNull_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  const char data[] = "xyzxyz";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  EXPECT_EQ(result, nullptr);
}

// Test: Prefix front char exists but back doesn't match
TEST_F(PrefixAccelFrontAndBackTest_420, FrontMatchesButBackDoesNot_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  const char data[] = "acad";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  EXPECT_EQ(result, nullptr);
}

// Test: Data exactly matches the prefix (boundary)
TEST_F(PrefixAccelFrontAndBackTest_420, DataExactlyMatchesPrefix_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  const char data[] = "ab";
  const void* result = prog.PrefixAccel_FrontAndBack(data, 2);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data);
}

// Test: Longer prefix (3 chars)
TEST_F(PrefixAccelFrontAndBackTest_420, LongerPrefixMatch_420) {
  Prog prog;
  std::string prefix = "abc";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  // "xxabc" - 'a' at index 2, 'c' at index 4 (prefix_size_-1=2 offset)
  const char data[] = "xxabc";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data + 2);
}

// Test: Longer prefix with no match
TEST_F(PrefixAccelFrontAndBackTest_420, LongerPrefixNoMatch_420) {
  Prog prog;
  std::string prefix = "abc";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  // 'a' is present but 'c' at the right offset is not
  const char data[] = "abx";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  EXPECT_EQ(result, nullptr);
}

// Test: Multiple potential front matches, only later one has correct back
TEST_F(PrefixAccelFrontAndBackTest_420, MultiplePartialMatchesFirstCorrect_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  // 'a' at index 0 with 'c' at index 1 (no match), 'a' at index 2 with 'b' at index 3 (match)
  const char data[] = "acab";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data + 2);
}

// Test: Size exactly equal to prefix_size_ with no match
TEST_F(PrefixAccelFrontAndBackTest_420, SizeEqualToPrefixNoMatch_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  const char data[] = "xx";
  const void* result = prog.PrefixAccel_FrontAndBack(data, 2);
  EXPECT_EQ(result, nullptr);
}

// Test: Large data with match near the end
TEST_F(PrefixAccelFrontAndBackTest_420, LargeDataMatchNearEnd_420) {
  Prog prog;
  std::string prefix = "xy";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  // Create a large buffer filled with 'z' and place "xy" near the end
  std::string data(1000, 'z');
  data[997] = 'x';
  data[998] = 'y';
  
  const void* result = prog.PrefixAccel_FrontAndBack(data.data(), data.size());
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data.data() + 997);
}

// Test: Large data with no match
TEST_F(PrefixAccelFrontAndBackTest_420, LargeDataNoMatch_420) {
  Prog prog;
  std::string prefix = "xy";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  std::string data(1000, 'z');
  const void* result = prog.PrefixAccel_FrontAndBack(data.data(), data.size());
  EXPECT_EQ(result, nullptr);
}

// Test: Match at the very first position with trailing data
TEST_F(PrefixAccelFrontAndBackTest_420, MatchAtFirstPosition_420) {
  Prog prog;
  std::string prefix = "he";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  const char data[] = "hello world";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data);
}

// Test: Data with repeated front char but back only matches once
TEST_F(PrefixAccelFrontAndBackTest_420, RepeatedFrontCharSingleBackMatch_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  const char data[] = "aaaaab";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  ASSERT_NE(result, nullptr);
  // Should find 'a' followed by 'b' - the 'a' at index 4, 'b' at index 5
  EXPECT_EQ(result, data + 4);
}

// Test: Very large data to potentially trigger SIMD path
TEST_F(PrefixAccelFrontAndBackTest_420, VeryLargeDataSIMDPath_420) {
  Prog prog;
  std::string prefix = "mn";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  // 256 bytes should be enough to trigger AVX2 path if available
  std::string data(256, 'a');
  data[200] = 'm';
  data[201] = 'n';
  
  const void* result = prog.PrefixAccel_FrontAndBack(data.data(), data.size());
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data.data() + 200);
}

// Test: can_prefix_accel returns false when no prefix configured
TEST_F(PrefixAccelFrontAndBackTest_420, NoPrefixConfigured_420) {
  Prog prog;
  EXPECT_FALSE(prog.can_prefix_accel());
}

// Test: can_prefix_accel returns true after configuring a prefix of length >= 2
TEST_F(PrefixAccelFrontAndBackTest_420, PrefixConfiguredCanAccel_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  // For prefix of length >= 2, can_prefix_accel should be true
  // (It may use FrontAndBack or ShiftDFA depending on implementation)
  // We just test that the prefix was configured
  // The actual method used depends on internal heuristics
  // At minimum, if prefix is short, it should be configured
  EXPECT_TRUE(prog.can_prefix_accel());
}

// Test: Single char prefix - ConfigurePrefixAccel might still work 
// but PrefixAccel_FrontAndBack requires prefix_size_ >= 2
TEST_F(PrefixAccelFrontAndBackTest_420, SingleCharPrefixBehavior_420) {
  Prog prog;
  std::string prefix = "a";
  prog.ConfigurePrefixAccel(prefix, false);
  // Single char prefix may use a different acceleration method
  // Just verify the object is in a valid state
  // can_prefix_accel might or might not be true depending on implementation
  // This test just ensures no crash
}

// Test: Prefix with same front and back char
TEST_F(PrefixAccelFrontAndBackTest_420, SameFrontAndBackChar_420) {
  Prog prog;
  std::string prefix = "aa";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  const char data[] = "xaaxbb";
  const void* result = prog.PrefixAccel_FrontAndBack(data, strlen(data));
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data + 1);
}

// Test: Data containing null bytes
TEST_F(PrefixAccelFrontAndBackTest_420, DataWithNullBytes_420) {
  Prog prog;
  std::string prefix = "ab";
  prog.ConfigurePrefixAccel(prefix, false);
  
  if (!prog.can_prefix_accel()) {
    GTEST_SKIP() << "Prefix accel not configured";
  }
  
  // Data with embedded null bytes followed by "ab"
  const char data[] = "\0\0\0ab";
  const void* result = prog.PrefixAccel_FrontAndBack(data, 5);
  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result, data + 3);
}

}  // namespace re2
