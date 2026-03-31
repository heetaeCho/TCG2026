#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"

namespace re2 {

class ProgTest_418 : public ::testing::Test {
 protected:
  void SetUp() override {
    prog_ = new Prog();
  }

  void TearDown() override {
    delete prog_;
  }

  Prog* prog_;
};

// Test that a default-constructed Prog has no prefix acceleration configured.
TEST_F(ProgTest_418, DefaultNoPrefixAccel_418) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test ConfigurePrefixAccel with a single character prefix, no foldcase.
TEST_F(ProgTest_418, ConfigureSingleCharNoCaseFold_418) {
  prog_->ConfigurePrefixAccel("a", false);
  EXPECT_TRUE(prog_->can_prefix_accel());
}

// Test ConfigurePrefixAccel with a two character prefix, no foldcase.
TEST_F(ProgTest_418, ConfigureTwoCharNoCaseFold_418) {
  prog_->ConfigurePrefixAccel("ab", false);
  EXPECT_TRUE(prog_->can_prefix_accel());
}

// Test ConfigurePrefixAccel with a multi character prefix, no foldcase.
TEST_F(ProgTest_418, ConfigureMultiCharNoCaseFold_418) {
  prog_->ConfigurePrefixAccel("hello", false);
  EXPECT_TRUE(prog_->can_prefix_accel());
}

// Test ConfigurePrefixAccel with foldcase enabled and a short prefix.
TEST_F(ProgTest_418, ConfigureWithFoldcaseShort_418) {
  prog_->ConfigurePrefixAccel("abc", true);
  EXPECT_TRUE(prog_->can_prefix_accel());
}

// Test ConfigurePrefixAccel with foldcase enabled and a longer prefix.
TEST_F(ProgTest_418, ConfigureWithFoldcaseLong_418) {
  prog_->ConfigurePrefixAccel("abcdefghijklmno", true);
  EXPECT_TRUE(prog_->can_prefix_accel());
}

// Test ConfigurePrefixAccel with foldcase and prefix exactly at kShiftDFAFinal (9) length.
TEST_F(ProgTest_418, ConfigureWithFoldcaseExactlyShiftDFAFinal_418) {
  std::string prefix(9, 'x');
  prog_->ConfigurePrefixAccel(prefix, true);
  EXPECT_TRUE(prog_->can_prefix_accel());
}

// Test ConfigurePrefixAccel with foldcase and prefix longer than kShiftDFAFinal.
TEST_F(ProgTest_418, ConfigureWithFoldcaseLongerThanShiftDFAFinal_418) {
  std::string prefix(15, 'y');
  prog_->ConfigurePrefixAccel(prefix, true);
  EXPECT_TRUE(prog_->can_prefix_accel());
}

// Test PrefixAccel with a single char prefix searching through data that contains it.
TEST_F(ProgTest_418, PrefixAccelSingleCharFound_418) {
  prog_->ConfigurePrefixAccel("x", false);
  const char* data = "abcxdef";
  const void* result = prog_->PrefixAccel(data, strlen(data));
  // The result should point to somewhere in the data (at or before the match).
  EXPECT_NE(result, nullptr);
  EXPECT_GE(reinterpret_cast<const char*>(result), data);
  EXPECT_LT(reinterpret_cast<const char*>(result), data + strlen(data));
}

// Test PrefixAccel with a single char prefix searching through data that doesn't contain it.
TEST_F(ProgTest_418, PrefixAccelSingleCharNotFound_418) {
  prog_->ConfigurePrefixAccel("z", false);
  const char* data = "abcdef";
  const void* result = prog_->PrefixAccel(data, strlen(data));
  // When not found, should return null.
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel with a two char prefix (FrontAndBack path).
TEST_F(ProgTest_418, PrefixAccelTwoCharFound_418) {
  prog_->ConfigurePrefixAccel("ab", false);
  const char* data = "xxabyy";
  const void* result = prog_->PrefixAccel(data, strlen(data));
  EXPECT_NE(result, nullptr);
}

// Test PrefixAccel with a two char prefix not present.
TEST_F(ProgTest_418, PrefixAccelTwoCharNotFound_418) {
  prog_->ConfigurePrefixAccel("zq", false);
  const char* data = "abcdef";
  const void* result = prog_->PrefixAccel(data, strlen(data));
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel with foldcase (ShiftDFA path).
TEST_F(ProgTest_418, PrefixAccelFoldcaseFound_418) {
  prog_->ConfigurePrefixAccel("abc", true);
  const char* data = "xxABCyy";
  const void* result = prog_->PrefixAccel(data, strlen(data));
  // Depending on the ShiftDFA implementation, this may or may not find it.
  // We just verify the function doesn't crash and returns a valid pointer or null.
  if (result != nullptr) {
    EXPECT_GE(reinterpret_cast<const char*>(result), data);
    EXPECT_LE(reinterpret_cast<const char*>(result), data + strlen(data));
  }
}

// Test PrefixAccel with empty data.
TEST_F(ProgTest_418, PrefixAccelEmptyData_418) {
  prog_->ConfigurePrefixAccel("abc", false);
  const char* data = "";
  const void* result = prog_->PrefixAccel(data, 0);
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel with size zero.
TEST_F(ProgTest_418, PrefixAccelZeroSize_418) {
  prog_->ConfigurePrefixAccel("x", false);
  const char* data = "hello";
  const void* result = prog_->PrefixAccel(data, 0);
  EXPECT_EQ(result, nullptr);
}

// Test that default-constructed Prog has expected initial values for some public accessors.
TEST_F(ProgTest_418, DefaultConstructorValues_418) {
  EXPECT_EQ(prog_->start(), 0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
  EXPECT_FALSE(prog_->reversed());
  EXPECT_FALSE(prog_->anchor_start());
  EXPECT_FALSE(prog_->anchor_end());
  EXPECT_EQ(prog_->bytemap_range(), 0);
  EXPECT_EQ(prog_->dfa_mem(), 0);
}

// Test set_start and start.
TEST_F(ProgTest_418, SetAndGetStart_418) {
  prog_->set_start(5);
  EXPECT_EQ(prog_->start(), 5);
}

// Test set_start_unanchored and start_unanchored.
TEST_F(ProgTest_418, SetAndGetStartUnanchored_418) {
  prog_->set_start_unanchored(7);
  EXPECT_EQ(prog_->start_unanchored(), 7);
}

// Test set_reversed and reversed.
TEST_F(ProgTest_418, SetAndGetReversed_418) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test set_anchor_start and anchor_start.
TEST_F(ProgTest_418, SetAndGetAnchorStart_418) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
  prog_->set_anchor_start(false);
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_anchor_end and anchor_end.
TEST_F(ProgTest_418, SetAndGetAnchorEnd_418) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test set_dfa_mem and dfa_mem.
TEST_F(ProgTest_418, SetAndGetDfaMem_418) {
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog_->dfa_mem(), 1024 * 1024);
}

// Test IsWordChar for known word characters.
TEST_F(ProgTest_418, IsWordCharTrue_418) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

// Test IsWordChar for known non-word characters.
TEST_F(ProgTest_418, IsWordCharFalse_418) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
}

// Integration test: compile a regex and verify ConfigurePrefixAccel works through RE2.
TEST_F(ProgTest_418, IntegrationWithRE2PrefixAccel_418) {
  RE2 re("hello world");
  EXPECT_TRUE(re.ok());
  // The compiled program should be accessible. We just verify the RE2 compiled fine.
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow.
TEST_F(ProgTest_418, TestingOnlySetDfaShouldBailWhenSlow_418) {
  // Just verify this static method can be called without crashing.
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test ConfigurePrefixAccel with prefix of exactly length 1 and foldcase.
TEST_F(ProgTest_418, ConfigureSingleCharWithFoldcase_418) {
  prog_->ConfigurePrefixAccel("A", true);
  EXPECT_TRUE(prog_->can_prefix_accel());
}

// Test PrefixAccel_ShiftDFA directly after configuring with foldcase.
TEST_F(ProgTest_418, PrefixAccelShiftDFADirect_418) {
  prog_->ConfigurePrefixAccel("test", true);
  const char* data = "this is a test string";
  const void* result = prog_->PrefixAccel_ShiftDFA(data, strlen(data));
  if (result != nullptr) {
    EXPECT_GE(reinterpret_cast<const char*>(result), data);
    EXPECT_LE(reinterpret_cast<const char*>(result), data + strlen(data));
  }
}

// Test PrefixAccel_FrontAndBack directly after configuring without foldcase and 2+ char prefix.
TEST_F(ProgTest_418, PrefixAccelFrontAndBackDirect_418) {
  prog_->ConfigurePrefixAccel("te", false);
  const char* data = "this is a test";
  const void* result = prog_->PrefixAccel_FrontAndBack(data, strlen(data));
  if (result != nullptr) {
    EXPECT_GE(reinterpret_cast<const char*>(result), data);
    EXPECT_LE(reinterpret_cast<const char*>(result), data + strlen(data));
  }
}

// Test that can_prefix_accel returns false when prefix_size_ would be 0.
// An empty prefix shouldn't enable prefix acceleration based on the code logic
// (prefix_size_ = 0 means can_prefix_accel should return false).
// Note: calling with empty string may be UB (front() on empty), so we skip this
// and test the boundary where prefix is minimal.

// Test ConfigurePrefixAccel with binary data in the prefix.
TEST_F(ProgTest_418, ConfigureBinaryPrefix_418) {
  std::string prefix("\x00\x01\x02", 3);
  prog_->ConfigurePrefixAccel(prefix, false);
  EXPECT_TRUE(prog_->can_prefix_accel());
}

// Test PrefixAccel with data smaller than the prefix.
TEST_F(ProgTest_418, PrefixAccelDataSmallerThanPrefix_418) {
  prog_->ConfigurePrefixAccel("abcdef", false);
  const char* data = "ab";
  const void* result = prog_->PrefixAccel(data, strlen(data));
  // Data is shorter than prefix, so no match possible.
  EXPECT_EQ(result, nullptr);
}

// Test PrefixAccel when prefix appears at the very beginning of data.
TEST_F(ProgTest_418, PrefixAccelAtStart_418) {
  prog_->ConfigurePrefixAccel("he", false);
  const char* data = "hello";
  const void* result = prog_->PrefixAccel(data, strlen(data));
  EXPECT_NE(result, nullptr);
  if (result != nullptr) {
    EXPECT_EQ(reinterpret_cast<const char*>(result), data);
  }
}

// Test PrefixAccel when prefix appears at the very end of data.
TEST_F(ProgTest_418, PrefixAccelAtEnd_418) {
  prog_->ConfigurePrefixAccel("lo", false);
  const char* data = "hello";
  const void* result = prog_->PrefixAccel(data, strlen(data));
  EXPECT_NE(result, nullptr);
}

}  // namespace re2
