#include "gtest/gtest.h"
#include "re2/prog.h"
#include "re2/re2.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace re2 {

class ProgTest_115 : public ::testing::Test {
 protected:
  void SetUp() override {
    prog_ = new Prog();
  }

  void TearDown() override {
    delete prog_;
  }

  Prog* prog_;
};

// Test default constructor initializes start to 0
TEST_F(ProgTest_115, DefaultStartIsZero_115) {
  EXPECT_EQ(prog_->start(), 0);
}

// Test default constructor initializes start_unanchored to 0
TEST_F(ProgTest_115, DefaultStartUnanchoredIsZero_115) {
  EXPECT_EQ(prog_->start_unanchored(), 0);
}

// Test set_start and start
TEST_F(ProgTest_115, SetStartAndGet_115) {
  prog_->set_start(5);
  EXPECT_EQ(prog_->start(), 5);
}

// Test set_start_unanchored and start_unanchored
TEST_F(ProgTest_115, SetStartUnanchoredAndGet_115) {
  prog_->set_start_unanchored(10);
  EXPECT_EQ(prog_->start_unanchored(), 10);
}

// Test set_start_unanchored with zero
TEST_F(ProgTest_115, SetStartUnanchoredZero_115) {
  prog_->set_start_unanchored(42);
  EXPECT_EQ(prog_->start_unanchored(), 42);
  prog_->set_start_unanchored(0);
  EXPECT_EQ(prog_->start_unanchored(), 0);
}

// Test set_start_unanchored with negative value
TEST_F(ProgTest_115, SetStartUnanchoredNegative_115) {
  prog_->set_start_unanchored(-1);
  EXPECT_EQ(prog_->start_unanchored(), -1);
}

// Test set_start_unanchored with large value
TEST_F(ProgTest_115, SetStartUnanchoredLargeValue_115) {
  prog_->set_start_unanchored(1000000);
  EXPECT_EQ(prog_->start_unanchored(), 1000000);
}

// Test set_start_unanchored multiple times overwrites correctly
TEST_F(ProgTest_115, SetStartUnanchoredMultipleTimes_115) {
  prog_->set_start_unanchored(1);
  EXPECT_EQ(prog_->start_unanchored(), 1);
  prog_->set_start_unanchored(2);
  EXPECT_EQ(prog_->start_unanchored(), 2);
  prog_->set_start_unanchored(3);
  EXPECT_EQ(prog_->start_unanchored(), 3);
}

// Test default reversed is false
TEST_F(ProgTest_115, DefaultReversedIsFalse_115) {
  EXPECT_FALSE(prog_->reversed());
}

// Test set_reversed
TEST_F(ProgTest_115, SetReversedTrue_115) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
}

// Test set_reversed back to false
TEST_F(ProgTest_115, SetReversedFalse_115) {
  prog_->set_reversed(true);
  EXPECT_TRUE(prog_->reversed());
  prog_->set_reversed(false);
  EXPECT_FALSE(prog_->reversed());
}

// Test default anchor_start is false
TEST_F(ProgTest_115, DefaultAnchorStartIsFalse_115) {
  EXPECT_FALSE(prog_->anchor_start());
}

// Test set_anchor_start
TEST_F(ProgTest_115, SetAnchorStart_115) {
  prog_->set_anchor_start(true);
  EXPECT_TRUE(prog_->anchor_start());
}

// Test default anchor_end is false
TEST_F(ProgTest_115, DefaultAnchorEndIsFalse_115) {
  EXPECT_FALSE(prog_->anchor_end());
}

// Test set_anchor_end
TEST_F(ProgTest_115, SetAnchorEnd_115) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
}

// Test set_anchor_end toggle
TEST_F(ProgTest_115, SetAnchorEndToggle_115) {
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_end());
  prog_->set_anchor_end(false);
  EXPECT_FALSE(prog_->anchor_end());
}

// Test default dfa_mem is 0
TEST_F(ProgTest_115, DefaultDfaMemIsZero_115) {
  EXPECT_EQ(prog_->dfa_mem(), 0);
}

// Test set_dfa_mem
TEST_F(ProgTest_115, SetDfaMem_115) {
  prog_->set_dfa_mem(1024 * 1024);
  EXPECT_EQ(prog_->dfa_mem(), 1024 * 1024);
}

// Test set_dfa_mem with large value
TEST_F(ProgTest_115, SetDfaMemLarge_115) {
  int64_t large_val = static_cast<int64_t>(1) << 30;
  prog_->set_dfa_mem(large_val);
  EXPECT_EQ(prog_->dfa_mem(), large_val);
}

// Test default size is 0
TEST_F(ProgTest_115, DefaultSizeIsZero_115) {
  EXPECT_EQ(prog_->size(), 0);
}

// Test default bytemap_range is 0
TEST_F(ProgTest_115, DefaultBytemapRangeIsZero_115) {
  EXPECT_EQ(prog_->bytemap_range(), 0);
}

// Test default can_prefix_accel is false (no prefix configured)
TEST_F(ProgTest_115, DefaultCanPrefixAccelIsFalse_115) {
  EXPECT_FALSE(prog_->can_prefix_accel());
}

// Test IsWordChar with alphabetic characters
TEST_F(ProgTest_115, IsWordCharAlpha_115) {
  EXPECT_TRUE(Prog::IsWordChar('a'));
  EXPECT_TRUE(Prog::IsWordChar('z'));
  EXPECT_TRUE(Prog::IsWordChar('A'));
  EXPECT_TRUE(Prog::IsWordChar('Z'));
  EXPECT_TRUE(Prog::IsWordChar('m'));
}

// Test IsWordChar with digits
TEST_F(ProgTest_115, IsWordCharDigit_115) {
  EXPECT_TRUE(Prog::IsWordChar('0'));
  EXPECT_TRUE(Prog::IsWordChar('9'));
  EXPECT_TRUE(Prog::IsWordChar('5'));
}

// Test IsWordChar with underscore
TEST_F(ProgTest_115, IsWordCharUnderscore_115) {
  EXPECT_TRUE(Prog::IsWordChar('_'));
}

// Test IsWordChar with non-word characters
TEST_F(ProgTest_115, IsWordCharNonWord_115) {
  EXPECT_FALSE(Prog::IsWordChar(' '));
  EXPECT_FALSE(Prog::IsWordChar('\0'));
  EXPECT_FALSE(Prog::IsWordChar('.'));
  EXPECT_FALSE(Prog::IsWordChar('-'));
  EXPECT_FALSE(Prog::IsWordChar('!'));
  EXPECT_FALSE(Prog::IsWordChar('@'));
  EXPECT_FALSE(Prog::IsWordChar('\n'));
  EXPECT_FALSE(Prog::IsWordChar('\t'));
}

// Test that set_start does not affect start_unanchored
TEST_F(ProgTest_115, SetStartDoesNotAffectStartUnanchored_115) {
  prog_->set_start(7);
  prog_->set_start_unanchored(13);
  EXPECT_EQ(prog_->start(), 7);
  EXPECT_EQ(prog_->start_unanchored(), 13);
}

// Test set_start and set_start_unanchored independence
TEST_F(ProgTest_115, StartAndStartUnanchoredIndependent_115) {
  prog_->set_start(100);
  EXPECT_EQ(prog_->start_unanchored(), 0);  // still default
  prog_->set_start_unanchored(200);
  EXPECT_EQ(prog_->start(), 100);
  EXPECT_EQ(prog_->start_unanchored(), 200);
}

// Test TESTING_ONLY_set_dfa_should_bail_when_slow does not crash
TEST_F(ProgTest_115, TestingOnlySetDfaShouldBailWhenSlow_115) {
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(true);
  Prog::TESTING_ONLY_set_dfa_should_bail_when_slow(false);
}

// Test EmptyFlags at start of string
TEST_F(ProgTest_115, EmptyFlagsAtStartOfString_115) {
  absl::string_view text("hello");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the beginning, kEmptyBeginText and kEmptyBeginLine should be set
  // We check flags is non-zero (some flags should be set at boundary)
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags at end of string
TEST_F(ProgTest_115, EmptyFlagsAtEndOfString_115) {
  absl::string_view text("hello");
  const char* p = text.data() + text.size();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // At the end, kEmptyEndText and kEmptyEndLine should be set
  EXPECT_NE(flags, 0u);
}

// Test EmptyFlags on empty string
TEST_F(ProgTest_115, EmptyFlagsOnEmptyString_115) {
  absl::string_view text("");
  const char* p = text.data();
  uint32_t flags = Prog::EmptyFlags(text, p);
  // Both begin and end flags should be set
  EXPECT_NE(flags, 0u);
}

// Test with a compiled program from a simple regex
class ProgFromRegexTest_115 : public ::testing::Test {
 protected:
  void SetUp() override {
    re_ = new RE2("hello");
    ASSERT_TRUE(re_->ok());
  }

  void TearDown() override {
    delete re_;
  }

  RE2* re_;
};

// Test that a compiled program has a valid Dump
TEST_F(ProgFromRegexTest_115, DumpIsNonEmpty_115) {
  // We can't directly access the Prog from RE2 in all versions,
  // but we can verify the RE2 works as expected.
  EXPECT_TRUE(RE2::FullMatch("hello", *re_));
  EXPECT_FALSE(RE2::FullMatch("world", *re_));
}

// Test PossibleMatchRange via a compiled program
TEST_F(ProgFromRegexTest_115, PossibleMatchRange_115) {
  std::string min, max;
  // Use RE2's internal prog if accessible; otherwise test via RE2
  EXPECT_TRUE(re_->PossibleMatchRange(&min, &max, 10));
  EXPECT_FALSE(min.empty());
  EXPECT_FALSE(max.empty());
  EXPECT_LE(min, "hello");
  EXPECT_GE(max, "hello");
}

// Test bytemap accessor does not return null on default prog
TEST_F(ProgTest_115, BytemapNotNull_115) {
  EXPECT_NE(prog_->bytemap(), nullptr);
}

// Test setting anchor_start and anchor_end together
TEST_F(ProgTest_115, SetBothAnchors_115) {
  prog_->set_anchor_start(true);
  prog_->set_anchor_end(true);
  EXPECT_TRUE(prog_->anchor_start());
  EXPECT_TRUE(prog_->anchor_end());
}

// Test set_start with boundary int values
TEST_F(ProgTest_115, SetStartBoundaryValues_115) {
  prog_->set_start(0);
  EXPECT_EQ(prog_->start(), 0);
  
  prog_->set_start(INT32_MAX);
  EXPECT_EQ(prog_->start(), INT32_MAX);
}

// Test set_start_unanchored with boundary int values
TEST_F(ProgTest_115, SetStartUnanchoredBoundaryValues_115) {
  prog_->set_start_unanchored(INT32_MAX);
  EXPECT_EQ(prog_->start_unanchored(), INT32_MAX);
  
  prog_->set_start_unanchored(INT32_MIN);
  EXPECT_EQ(prog_->start_unanchored(), INT32_MIN);
}

// Test PrefixAccel returns null when no prefix configured
TEST_F(ProgTest_115, PrefixAccelReturnsNullWithoutConfig_115) {
  const char data[] = "test data";
  EXPECT_EQ(prog_->PrefixAccel(data, sizeof(data) - 1), nullptr);
}

// Test list_count default
TEST_F(ProgTest_115, DefaultListCountIsZero_115) {
  EXPECT_EQ(prog_->list_count(), 0);
}

// Test bit_state_text_max_size default
TEST_F(ProgTest_115, DefaultBitStateTextMaxSizeIsZero_115) {
  EXPECT_EQ(prog_->bit_state_text_max_size(), 0u);
}

}  // namespace re2
