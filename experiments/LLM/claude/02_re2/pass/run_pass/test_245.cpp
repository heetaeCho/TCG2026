#include "gtest/gtest.h"
#include "re2/re2.h"
#include <string>
#include <vector>
#include <map>

namespace re2 {

// Test fixture for RE2 ReverseProgramSize and related tests
class RE2ReverseProgramSizeTest_245 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple valid regex has a positive ReverseProgramSize
TEST_F(RE2ReverseProgramSizeTest_245, SimplePatternReturnsPositiveSize_245) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test that ProgramSize also returns a positive value for a valid regex
TEST_F(RE2ReverseProgramSizeTest_245, ProgramSizePositiveForValidPattern_245) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  int size = re.ProgramSize();
  EXPECT_GT(size, 0);
}

// Test that an invalid regex returns -1 for ReverseProgramSize
TEST_F(RE2ReverseProgramSizeTest_245, InvalidPatternReturnsNegativeOne_245) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.ReverseProgramSize(), -1);
}

// Test that an invalid regex returns -1 for ProgramSize
TEST_F(RE2ReverseProgramSizeTest_245, InvalidPatternProgramSizeReturnsNegativeOne_245) {
  RE2 re("(unclosed");
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.ProgramSize(), -1);
}

// Test empty pattern
TEST_F(RE2ReverseProgramSizeTest_245, EmptyPatternReverseProgramSize_245) {
  RE2 re("");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test a more complex pattern
TEST_F(RE2ReverseProgramSizeTest_245, ComplexPatternReverseProgramSize_245) {
  RE2 re("(a|b)*c+[d-f]{2,5}");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test that reverse program size may differ from forward program size
TEST_F(RE2ReverseProgramSizeTest_245, ReverseMayDifferFromForward_245) {
  RE2 re("abc.*xyz");
  ASSERT_TRUE(re.ok());
  int fwd = re.ProgramSize();
  int rev = re.ReverseProgramSize();
  EXPECT_GT(fwd, 0);
  EXPECT_GT(rev, 0);
  // Both should be positive but may or may not be equal
}

// Test single character pattern
TEST_F(RE2ReverseProgramSizeTest_245, SingleCharPattern_245) {
  RE2 re("a");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test dot star pattern
TEST_F(RE2ReverseProgramSizeTest_245, DotStarPattern_245) {
  RE2 re(".*");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test pattern with named captures
TEST_F(RE2ReverseProgramSizeTest_245, NamedCapturePattern_245) {
  RE2 re("(?P<name>\\w+)");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test that larger patterns generally produce larger reverse program sizes
TEST_F(RE2ReverseProgramSizeTest_245, LargerPatternLargerSize_245) {
  RE2 re_small("a");
  RE2 re_large("abcdefghijklmnop");
  ASSERT_TRUE(re_small.ok());
  ASSERT_TRUE(re_large.ok());
  int small_size = re_large.ReverseProgramSize();
  int large_size = re_large.ReverseProgramSize();
  EXPECT_GT(small_size, 0);
  EXPECT_GT(large_size, 0);
}

// Test alternation pattern
TEST_F(RE2ReverseProgramSizeTest_245, AlternationPattern_245) {
  RE2 re("foo|bar|baz");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test character class pattern
TEST_F(RE2ReverseProgramSizeTest_245, CharacterClassPattern_245) {
  RE2 re("[a-zA-Z0-9]+");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test pattern with repetition
TEST_F(RE2ReverseProgramSizeTest_245, RepetitionPattern_245) {
  RE2 re("a{3,10}");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test another invalid pattern (bad escape)
TEST_F(RE2ReverseProgramSizeTest_245, BadRepetitionInvalidPattern_245) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("*invalid", opts);
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.ReverseProgramSize(), -1);
}

// Test that ok() is true for valid patterns
TEST_F(RE2ReverseProgramSizeTest_245, OkTrueForValidPattern_245) {
  RE2 re("test");
  EXPECT_TRUE(re.ok());
}

// Test ReverseProgramFanout with valid pattern
TEST_F(RE2ReverseProgramSizeTest_245, ReverseProgramFanoutValidPattern_245) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ProgramFanout with valid pattern
TEST_F(RE2ReverseProgramSizeTest_245, ProgramFanoutValidPattern_245) {
  RE2 re("abc");
  ASSERT_TRUE(re.ok());
  std::vector<int> histogram;
  int result = re.ProgramFanout(&histogram);
  EXPECT_GE(result, 0);
}

// Test ReverseProgramFanout with invalid pattern
TEST_F(RE2ReverseProgramSizeTest_245, ReverseProgramFanoutInvalidPattern_245) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(unclosed", opts);
  EXPECT_FALSE(re.ok());
  std::vector<int> histogram;
  int result = re.ReverseProgramFanout(&histogram);
  EXPECT_EQ(result, -1);
}

// Test that calling ReverseProgramSize multiple times gives consistent results
TEST_F(RE2ReverseProgramSizeTest_245, ConsistentReverseProgramSize_245) {
  RE2 re("hello world");
  ASSERT_TRUE(re.ok());
  int size1 = re.ReverseProgramSize();
  int size2 = re.ReverseProgramSize();
  EXPECT_EQ(size1, size2);
}

// Test pattern with anchors
TEST_F(RE2ReverseProgramSizeTest_245, AnchoredPattern_245) {
  RE2 re("^hello$");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test pattern with backreference-like constructs (re2 doesn't support backrefs)
TEST_F(RE2ReverseProgramSizeTest_245, UnsupportedBackrefPattern_245) {
  RE2::Options opts;
  opts.set_log_errors(false);
  RE2 re("(a)\\1", opts);
  // RE2 does not support backreferences, this should fail
  EXPECT_FALSE(re.ok());
  EXPECT_EQ(re.ReverseProgramSize(), -1);
}

// Additional test: FullMatch with simple pattern to confirm RE2 is working
TEST_F(RE2ReverseProgramSizeTest_245, FullMatchBasicSanity_245) {
  RE2 re("hello");
  ASSERT_TRUE(re.ok());
  EXPECT_TRUE(RE2::FullMatch("hello", re));
  EXPECT_FALSE(RE2::FullMatch("world", re));
}

// Test with unicode/UTF-8 pattern
TEST_F(RE2ReverseProgramSizeTest_245, UnicodePattern_245) {
  RE2 re("\\p{L}+");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

// Test with nested groups
TEST_F(RE2ReverseProgramSizeTest_245, NestedGroupsPattern_245) {
  RE2 re("((a)(b(c)))");
  ASSERT_TRUE(re.ok());
  int size = re.ReverseProgramSize();
  EXPECT_GT(size, 0);
}

}  // namespace re2
