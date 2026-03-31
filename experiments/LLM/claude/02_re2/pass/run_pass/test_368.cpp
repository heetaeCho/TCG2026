#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "re2/re2.h"

namespace re2 {

class RequiredPrefixTest_368 : public ::testing::Test {
 protected:
  void TearDown() override {
    // Cleanup handled by Decref calls in tests
  }
};

// Test that a simple pattern with a required prefix starting with ^ returns true
TEST_F(RequiredPrefixTest_368, SimplePrefixWithBeginText_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");
  EXPECT_FALSE(foldcase);
  ASSERT_NE(suffix, nullptr);

  suffix->Decref();
  re->Decref();
}

// Test that a pattern without ^ at the beginning returns false
TEST_F(RequiredPrefixTest_368, NoPrefixWithoutBeginText_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(result);
  EXPECT_TRUE(prefix.empty());
  EXPECT_FALSE(foldcase);
  EXPECT_EQ(suffix, nullptr);

  re->Decref();
}

// Test that a pattern with ^ followed by a suffix returns the correct suffix
TEST_F(RequiredPrefixTest_368, PrefixWithSuffix_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc.*def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");
  ASSERT_NE(suffix, nullptr);

  suffix->Decref();
  re->Decref();
}

// Test that FoldCase is detected when case-insensitive flag is used
TEST_F(RequiredPrefixTest_368, PrefixWithFoldCase_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("(?i)^abc", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  if (result) {
    EXPECT_TRUE(foldcase);
    ASSERT_NE(suffix, nullptr);
    suffix->Decref();
  }

  re->Decref();
}

// Test a pattern that is just ^ (no literal after it)
TEST_F(RequiredPrefixTest_368, OnlyBeginText_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(result);

  re->Decref();
}

// Test a single literal pattern (no concat, no ^)
TEST_F(RequiredPrefixTest_368, SingleLiteral_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(result);

  re->Decref();
}

// Test a pattern with ^ followed by alternation (not a literal)
TEST_F(RequiredPrefixTest_368, BeginTextFollowedByNonLiteral_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^(a|b)c", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  // ^(a|b)c: after ^, next is a capture/alternation, not a literal
  // So RequiredPrefix should return false
  EXPECT_FALSE(result);

  if (suffix != nullptr) {
    suffix->Decref();
  }

  re->Decref();
}

// Test a pattern with ^ and a longer literal string prefix
TEST_F(RequiredPrefixTest_368, LongerLiteralPrefix_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^hello world.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "hello world");
  EXPECT_FALSE(foldcase);
  ASSERT_NE(suffix, nullptr);

  suffix->Decref();
  re->Decref();
}

// Test that an empty pattern returns false
TEST_F(RequiredPrefixTest_368, EmptyPattern_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(result);

  re->Decref();
}

// Test a pattern with ^prefix$ (full prefix, and suffix is empty match)
TEST_F(RequiredPrefixTest_368, PrefixWithEndText_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc$", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");
  ASSERT_NE(suffix, nullptr);

  suffix->Decref();
  re->Decref();
}

// Test a pattern ^a (single character prefix) with suffix
TEST_F(RequiredPrefixTest_368, SingleCharPrefix_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^a.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "a");
  ASSERT_NE(suffix, nullptr);

  suffix->Decref();
  re->Decref();
}

// Test that prefix and foldcase are properly cleared/reset on false return
TEST_F(RequiredPrefixTest_368, OutputsClearedOnFalse_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("a*b*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix = "leftover";
  bool foldcase = true;
  Regexp* suffix = reinterpret_cast<Regexp*>(0xdeadbeef);

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(result);
  EXPECT_TRUE(prefix.empty());
  EXPECT_FALSE(foldcase);
  EXPECT_EQ(suffix, nullptr);

  re->Decref();
}

// Test Latin1 mode prefix
TEST_F(RequiredPrefixTest_368, Latin1Prefix_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^abc", Regexp::Latin1 | Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_TRUE(result);
  EXPECT_EQ(prefix, "abc");

  if (suffix != nullptr) {
    suffix->Decref();
  }
  re->Decref();
}

// Test a character class after ^ (should return false since it's not a literal)
TEST_F(RequiredPrefixTest_368, CharClassAfterBeginText_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^[abc]def", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(result);

  if (suffix != nullptr) {
    suffix->Decref();
  }
  re->Decref();
}

// Test that ^.* (dot after ^) returns false since . is not a literal
TEST_F(RequiredPrefixTest_368, DotAfterBeginText_368) {
  RegexpStatus status;
  Regexp* re = Regexp::Parse("^.*", Regexp::LikePerl, &status);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;
  Regexp* suffix = nullptr;

  bool result = re->RequiredPrefix(&prefix, &foldcase, &suffix);
  EXPECT_FALSE(result);

  if (suffix != nullptr) {
    suffix->Decref();
  }
  re->Decref();
}

}  // namespace re2
