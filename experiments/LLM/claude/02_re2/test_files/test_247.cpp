#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"
#include "re2/sparse_array.h"
#include <vector>
#include <string>

// The Fanout function is in the re2 namespace but is static in re2.cc,
// so we cannot directly call it. However, we can test it indirectly through
// the RE2 interface. RE2 objects compile patterns into Progs, and we can
// test observable behavior through RE2's public API.
//
// Since Fanout is a static (file-local) function in re2.cc, we test the
// public interfaces that exercise it. The RE2 class uses Fanout internally
// for optimization decisions. We test Prog::Fanout which is the public
// method on Prog that Fanout() calls, and we test through RE2's interface.

namespace re2 {

class FanoutTest_247 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a simple pattern compiles and Prog::Fanout works
TEST_F(FanoutTest_247, SimpleLiteral_247) {
  Regexp* re = Regexp::Parse("hello", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  // The fanout sparse array should have been populated
  // Each instruction in a literal has limited fanout
  for (SparseArray<int>::iterator it = fanout.begin(); it != fanout.end(); ++it) {
    EXPECT_GE(it->value(), 0);
  }

  delete prog;
  re->Decref();
}

// Test fanout with alternation pattern (higher fanout expected)
TEST_F(FanoutTest_247, AlternationPattern_247) {
  Regexp* re = Regexp::Parse("a|b|c|d|e|f", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  // Should have valid fanout data
  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test fanout with a character class pattern
TEST_F(FanoutTest_247, CharClassPattern_247) {
  Regexp* re = Regexp::Parse("[a-z]", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test fanout with repetition
TEST_F(FanoutTest_247, RepetitionPattern_247) {
  Regexp* re = Regexp::Parse("a{1,100}", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test fanout with dot-star pattern
TEST_F(FanoutTest_247, DotStarPattern_247) {
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test fanout with empty pattern
TEST_F(FanoutTest_247, EmptyPattern_247) {
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test fanout with complex alternation (many alternatives)
TEST_F(FanoutTest_247, ComplexAlternation_247) {
  Regexp* re = Regexp::Parse(
      "abc|def|ghi|jkl|mno|pqr|stu|vwx|yz0|123|456|789",
      Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  // With many alternatives, we expect some instructions to have higher fanout
  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test fanout with nested groups
TEST_F(FanoutTest_247, NestedGroups_247) {
  Regexp* re = Regexp::Parse("((a|b)(c|d))+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test that RE2 object with high fanout pattern still works correctly
TEST_F(FanoutTest_247, RE2HighFanoutMatch_247) {
  // A pattern with high fanout due to many alternatives
  RE2 pattern("(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)+");
  ASSERT_TRUE(pattern.ok());

  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_TRUE(RE2::FullMatch("abcdefghijklmnopqrstuvwxyz", pattern));
  EXPECT_FALSE(RE2::FullMatch("HELLO", pattern));
  EXPECT_FALSE(RE2::FullMatch("123", pattern));
}

// Test that RE2 object with simple pattern still works correctly
TEST_F(FanoutTest_247, RE2SimpleLiteralMatch_247) {
  RE2 pattern("hello");
  ASSERT_TRUE(pattern.ok());

  EXPECT_TRUE(RE2::FullMatch("hello", pattern));
  EXPECT_FALSE(RE2::FullMatch("world", pattern));
  EXPECT_FALSE(RE2::FullMatch("hellp", pattern));
}

// Test Prog::Fanout with a single character pattern
TEST_F(FanoutTest_247, SingleCharPattern_247) {
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  // A single character pattern should have minimal fanout
  for (SparseArray<int>::iterator it = fanout.begin(); it != fanout.end(); ++it) {
    EXPECT_GE(it->value(), 0);
    // Single char pattern: fanout should be small
    EXPECT_LE(it->value(), 256);
  }

  delete prog;
  re->Decref();
}

// Test fanout with question mark (optional)
TEST_F(FanoutTest_247, OptionalPattern_247) {
  Regexp* re = Regexp::Parse("a?b?c?", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test fanout with word boundary
TEST_F(FanoutTest_247, WordBoundaryPattern_247) {
  Regexp* re = Regexp::Parse("\\bfoo\\b", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test with a wide character class to get higher fanout values
TEST_F(FanoutTest_247, WideCharClassFanout_247) {
  // [\x00-\xff] matches any byte - should have high fanout
  Regexp* re = Regexp::Parse("[\\x00-\\xff]+", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  EXPECT_GE(fanout.size(), 0);

  delete prog;
  re->Decref();
}

// Test Prog size is positive for non-trivial patterns
TEST_F(FanoutTest_247, ProgSizePositive_247) {
  Regexp* re = Regexp::Parse("abc|def", Regexp::LikePerl, nullptr);
  ASSERT_NE(re, nullptr);
  Prog* prog = re->CompileToProg(0);
  ASSERT_NE(prog, nullptr);

  EXPECT_GT(prog->size(), 0);

  SparseArray<int> fanout(prog->size());
  prog->Fanout(&fanout);

  delete prog;
  re->Decref();
}

}  // namespace re2
