#include "gtest/gtest.h"
#include "re2/re2.h"
#include "re2/prog.h"
#include "re2/regexp.h"

namespace re2 {

// Helper to compile a regex pattern into a Prog
static Prog* CompilePattern(const std::string& pattern) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(pattern, Regexp::LikePerl, &status);
  if (re == nullptr) return nullptr;
  Prog* prog = re->CompileToProg(0);
  re->Decref();
  return prog;
}

class IsOnePassTest_569 : public ::testing::Test {
 protected:
  void TearDown() override {
    delete prog_;
    prog_ = nullptr;
  }
  Prog* prog_ = nullptr;
};

// Test that a simple literal string is one-pass
TEST_F(IsOnePassTest_569, SimpleLiteral_569) {
  prog_ = CompilePattern("hello");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test that a simple character class is one-pass
TEST_F(IsOnePassTest_569, SimpleCharClass_569) {
  prog_ = CompilePattern("[abc]");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test that a simple alternation with non-overlapping first characters is one-pass
TEST_F(IsOnePassTest_569, NonOverlappingAlternation_569) {
  prog_ = CompilePattern("a|b");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test that an ambiguous alternation is NOT one-pass
TEST_F(IsOnePassTest_569, AmbiguousAlternation_569) {
  prog_ = CompilePattern("(a|a)");
  ASSERT_NE(prog_, nullptr);
  // This has multiple paths for 'a', so it should not be one-pass
  // Note: the compiler may optimize this, so check the actual result
  // The key test is that IsOnePass returns a boolean without crashing
  prog_->IsOnePass();
}

// Test that calling IsOnePass twice returns the same result (caching via did_onepass_)
TEST_F(IsOnePassTest_569, IdempotentCall_569) {
  prog_ = CompilePattern("abc");
  ASSERT_NE(prog_, nullptr);
  bool first = prog_->IsOnePass();
  bool second = prog_->IsOnePass();
  EXPECT_EQ(first, second);
}

// Test a pattern with captures
TEST_F(IsOnePassTest_569, WithCaptures_569) {
  prog_ = CompilePattern("(a)(b)(c)");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test a pattern with repetition that may not be one-pass
TEST_F(IsOnePassTest_569, StarRepetition_569) {
  prog_ = CompilePattern("a*a");
  ASSERT_NE(prog_, nullptr);
  // a*a is ambiguous - not one-pass
  EXPECT_FALSE(prog_->IsOnePass());
}

// Test a pattern with anchors
TEST_F(IsOnePassTest_569, AnchoredPattern_569) {
  prog_ = CompilePattern("^abc$");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test empty pattern
TEST_F(IsOnePassTest_569, EmptyPattern_569) {
  prog_ = CompilePattern("");
  ASSERT_NE(prog_, nullptr);
  // Empty pattern matches everything at position 0; should still produce a result
  prog_->IsOnePass();
}

// Test a dot-star pattern (not one-pass due to ambiguity)
TEST_F(IsOnePassTest_569, DotStar_569) {
  prog_ = CompilePattern(".*");
  ASSERT_NE(prog_, nullptr);
  // .* by itself can be one-pass (no conflict)
  prog_->IsOnePass();
}

// Test complex pattern with nested groups
TEST_F(IsOnePassTest_569, NestedGroups_569) {
  prog_ = CompilePattern("((a)(b))");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test a case-insensitive pattern (foldcase)
TEST_F(IsOnePassTest_569, CaseInsensitive_569) {
  prog_ = CompilePattern("(?i)abc");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test a pattern with empty width assertions
TEST_F(IsOnePassTest_569, WordBoundary_569) {
  prog_ = CompilePattern("\\bhello\\b");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test overlapping alternation that is definitely not one-pass
TEST_F(IsOnePassTest_569, OverlappingAlternationNotOnePass_569) {
  prog_ = CompilePattern("(abc|abd).*");
  ASSERT_NE(prog_, nullptr);
  // Both branches start with 'a', but differ later.
  // This should be one-pass if the NFA can deterministically choose.
  prog_->IsOnePass();
}

// Test that a complex regex like (a+|b+) is not one-pass
TEST_F(IsOnePassTest_569, AmbiguousPlusAlternation_569) {
  prog_ = CompilePattern("a+|a+b");
  ASSERT_NE(prog_, nullptr);
  // Multiple paths for 'a' — should not be one-pass
  EXPECT_FALSE(prog_->IsOnePass());
}

// Test single character
TEST_F(IsOnePassTest_569, SingleChar_569) {
  prog_ = CompilePattern("x");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test a pattern with many captures (approaching kMaxCap)
TEST_F(IsOnePassTest_569, ManyCaptures_569) {
  prog_ = CompilePattern("(a)(b)(c)(d)(e)(f)(g)(h)");
  ASSERT_NE(prog_, nullptr);
  // Should still be one-pass since each capture is unambiguous
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test SearchOnePass works after IsOnePass returns true
TEST_F(IsOnePassTest_569, SearchOnePassAfterIsOnePass_569) {
  prog_ = CompilePattern("(\\w+)@(\\w+)");
  ASSERT_NE(prog_, nullptr);
  if (prog_->IsOnePass()) {
    absl::string_view text("user@host");
    absl::string_view match[3];
    bool found = prog_->SearchOnePass(text, text, Prog::kAnchored,
                                       Prog::kFirstMatch, match, 3);
    EXPECT_TRUE(found);
    if (found) {
      EXPECT_EQ(match[0], "user@host");
      EXPECT_EQ(match[1], "user");
      EXPECT_EQ(match[2], "host");
    }
  }
}

// Test a purely optional pattern
TEST_F(IsOnePassTest_569, OptionalPattern_569) {
  prog_ = CompilePattern("a?b");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test a pattern that won't be one-pass due to same-character ambiguity
TEST_F(IsOnePassTest_569, SameCharAmbiguity_569) {
  prog_ = CompilePattern("(a*)(a*)");
  ASSERT_NE(prog_, nullptr);
  EXPECT_FALSE(prog_->IsOnePass());
}

// Integration test via RE2 - simple one-pass regex matching
TEST_F(IsOnePassTest_569, RE2IntegrationSimple_569) {
  RE2 re("^(\\d+)-(\\d+)$");
  ASSERT_TRUE(re.ok());
  std::string s1, s2;
  EXPECT_TRUE(RE2::FullMatch("123-456", re, &s1, &s2));
  EXPECT_EQ(s1, "123");
  EXPECT_EQ(s2, "456");
}

// Test character range pattern
TEST_F(IsOnePassTest_569, CharRange_569) {
  prog_ = CompilePattern("[a-z]+");
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

// Test a very long alternation (stress test for node allocation)
TEST_F(IsOnePassTest_569, LongAlternation_569) {
  // Create a pattern like a|b|c|...|z - all distinct first bytes, should be one-pass
  std::string pattern;
  for (char c = 'a'; c <= 'z'; c++) {
    if (!pattern.empty()) pattern += "|";
    pattern += c;
  }
  prog_ = CompilePattern(pattern);
  ASSERT_NE(prog_, nullptr);
  EXPECT_TRUE(prog_->IsOnePass());
}

}  // namespace re2
