#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RequiredPrefixForAccelTest_369 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Regexp objects are ref-counted; we use Decref to clean up.
  }
};

// Test that a simple literal prefix is extracted correctly.
TEST_F(RequiredPrefixForAccelTest_369, SimpleLiteralPrefix_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc.*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = true;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// Test that a single literal character prefix works.
TEST_F(RequiredPrefixForAccelTest_369, SingleLiteralChar_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("x.*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "x");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// Test that a pattern with no literal prefix returns false.
TEST_F(RequiredPrefixForAccelTest_369, NoLiteralPrefix_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_FALSE(result);

  re->Decref();
}

// Test alternation — no common prefix should be extractable.
TEST_F(RequiredPrefixForAccelTest_369, AlternationNoPrefix_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc|def)", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  // Alternation at top level means no single literal prefix.
  // The result depends on the actual structure, but alternation itself
  // is not a literal.
  // We just check that it returns some valid result.
  // For alternation, it should return false.
  EXPECT_FALSE(result);

  re->Decref();
}

// Test case-insensitive prefix sets foldcase to true.
TEST_F(RequiredPrefixForAccelTest_369, CaseInsensitivePrefix_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)abc.*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");
  EXPECT_TRUE(foldcase);

  re->Decref();
}

// Test a capturing group wrapping a literal prefix.
TEST_F(RequiredPrefixForAccelTest_369, CapturingGroupPrefix_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(abc).*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// Test empty pattern returns false.
TEST_F(RequiredPrefixForAccelTest_369, EmptyPattern_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_FALSE(result);

  re->Decref();
}

// Test dot-star only pattern returns false.
TEST_F(RequiredPrefixForAccelTest_369, DotStarOnly_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_FALSE(result);

  re->Decref();
}

// Test character class at start returns false.
TEST_F(RequiredPrefixForAccelTest_369, CharClassNoPrefix_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("[abc]def", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_FALSE(result);

  re->Decref();
}

// Test a longer literal string prefix.
TEST_F(RequiredPrefixForAccelTest_369, LongLiteralPrefix_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("helloworld.*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "helloworld");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// Test prefix is cleared even on failure.
TEST_F(RequiredPrefixForAccelTest_369, PrefixClearedOnFailure_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse(".*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix = "leftover";
  bool foldcase = true;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_FALSE(result);
  EXPECT_TRUE(prefix.empty());
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// Test nested capturing groups.
TEST_F(RequiredPrefixForAccelTest_369, NestedCapturingGroups_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("((abc)).*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// Test a literal-only pattern (no wildcard after).
TEST_F(RequiredPrefixForAccelTest_369, PureLiteral_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// Test a single literal character pattern.
TEST_F(RequiredPrefixForAccelTest_369, SingleCharLiteral_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "a");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// Test a question mark (optional) at start returns false.
TEST_F(RequiredPrefixForAccelTest_369, OptionalAtStart_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a?bc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  // 'a?' is kRegexpQuest, not a literal, so should return false.
  EXPECT_FALSE(result);

  re->Decref();
}

// Test Latin1 flag affects encoding.
TEST_F(RequiredPrefixForAccelTest_369, Latin1Flag_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc.*",
      static_cast<Regexp::ParseFlags>(Regexp::LikePerl | Regexp::Latin1),
      &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// Test star at beginning returns false.
TEST_F(RequiredPrefixForAccelTest_369, StarAtBeginning_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*bc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  // 'a*' is kRegexpStar, not a literal
  EXPECT_FALSE(result);

  re->Decref();
}

// Test plus at beginning — 'a+' starts with kRegexpPlus, not literal
TEST_F(RequiredPrefixForAccelTest_369, PlusAtBeginning_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a+bc", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  // 'a+' is kRegexpPlus, not a literal at start
  EXPECT_FALSE(result);

  re->Decref();
}

// Test anchor at start with literal after.
TEST_F(RequiredPrefixForAccelTest_369, AnchoredLiteral_369) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*", Regexp::LikePerl, &status);
  ASSERT_TRUE(re != nullptr);

  std::string prefix;
  bool foldcase = false;
  bool result = re->RequiredPrefixForAccel(&prefix, &foldcase);
  // ^abc starts with kRegexpBeginLine or kRegexpBeginText, not literal
  // The concat's first sub is the anchor, so should return false.
  EXPECT_FALSE(result);

  re->Decref();
}

}  // namespace re2
