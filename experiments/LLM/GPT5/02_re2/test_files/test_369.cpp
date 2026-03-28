// File: regexp_requiredprefixforaccel_test.cc
#include "re2/regexp.h"
#include <gtest/gtest.h>
#include <string>

using re2::Regexp;

class RequiredPrefixForAccelTest_369 : public ::testing::Test {
protected:
  // Decref only the top-level regexps we create; builders typically transfer ownership.
  void DecrefIfNonNull(Regexp* re) {
    if (re) re->Decref();
  }
};

// [Normal] Direct literal string at the start -> returns true, full prefix, no foldcase.
TEST_F(RequiredPrefixForAccelTest_369, LiteralStringTopLevelReturnsTrue_369) {
  Regexp* re = Regexp::Parse("abc", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  std::string prefix = "initialized";
  bool foldcase = true; // should be overwritten to false

  EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));
  EXPECT_EQ(prefix, "abc");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// [Normal] Leading literal inside a concat -> returns true with first-rune prefix.
TEST_F(RequiredPrefixForAccelTest_369, ConcatLeadingLiteralReturnsTrue_369) {
  Regexp* lit_a = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* lit_z = Regexp::NewLiteral('z', Regexp::NoParseFlags);
  ASSERT_NE(lit_a, nullptr);
  ASSERT_NE(lit_z, nullptr);

  Regexp* subs[] = {lit_a, lit_z};
  Regexp* cat = Regexp::Concat(subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(cat, nullptr);

  std::string prefix;
  bool foldcase = true;

  EXPECT_TRUE(cat->RequiredPrefixForAccel(&prefix, &foldcase));
  EXPECT_EQ(prefix, "a");
  EXPECT_FALSE(foldcase);

  // Only decref top-level unless you explicitly incref the children.
  cat->Decref();
}

// [Boundary] Skip a single capture that wraps a literal string -> returns true, full string.
TEST_F(RequiredPrefixForAccelTest_369, SkipsSingleCaptureAroundLiteralString_369) {
  Regexp* re = Regexp::Parse("(abc)", Regexp::NoParseFlags, nullptr);
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = true;

  EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));
  EXPECT_EQ(prefix, "abc");
  EXPECT_FALSE(foldcase);

  re->Decref();
}

// [Boundary] Capture whose first element is a concat -> picks first element of that concat.
TEST_F(RequiredPrefixForAccelTest_369, CaptureWithConcatChoosesFirstElement_369) {
  Regexp* a = Regexp::NewLiteral('a', Regexp::NoParseFlags);
  Regexp* b = Regexp::NewLiteral('b', Regexp::NoParseFlags);
  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  Regexp* inner_subs[] = {a, b};
  Regexp* inner_cat = Regexp::Concat(inner_subs, 2, Regexp::NoParseFlags);
  ASSERT_NE(inner_cat, nullptr);

  Regexp* cap = Regexp::Capture(inner_cat, Regexp::NoParseFlags, /*cap=*/1);
  ASSERT_NE(cap, nullptr);

  std::string prefix = "x";
  bool foldcase = true;

  EXPECT_TRUE(cap->RequiredPrefixForAccel(&prefix, &foldcase));
  EXPECT_EQ(prefix, "a");
  EXPECT_FALSE(foldcase);

  cap->Decref();
}

// [Exceptional/Negative] Non-literal start (e.g., Star node) -> returns false; outputs cleared/defaulted.
TEST_F(RequiredPrefixForAccelTest_369, NonLiteralStartReturnsFalseAndClearsOutputs_369) {
  Regexp* lit_x = Regexp::NewLiteral('x', Regexp::NoParseFlags);
  ASSERT_NE(lit_x, nullptr);

  Regexp* star = Regexp::Star(lit_x, Regexp::NoParseFlags);
  ASSERT_NE(star, nullptr);

  std::string prefix = "should be cleared";
  bool foldcase = true;

  EXPECT_FALSE(star->RequiredPrefixForAccel(&prefix, &foldcase));
  EXPECT_EQ(prefix, "");          // cleared
  EXPECT_FALSE(foldcase);         // reset to false

  star->Decref();
}

// [Flag behavior] FoldCase flag on the literal -> foldcase output should be true.
TEST_F(RequiredPrefixForAccelTest_369, FoldCaseFlagSetsFoldcaseTrue_369) {
  Regexp* re = Regexp::NewLiteral('a', static_cast<Regexp::ParseFlags>(Regexp::FoldCase));
  ASSERT_NE(re, nullptr);

  std::string prefix;
  bool foldcase = false;

  EXPECT_TRUE(re->RequiredPrefixForAccel(&prefix, &foldcase));
  EXPECT_EQ(prefix, "a");
  EXPECT_TRUE(foldcase);

  re->Decref();
}

// [Encoding flag] Latin1 vs UTF-8 affects byte length for non-ASCII rune (U+00E9).
TEST_F(RequiredPrefixForAccelTest_369, Latin1FlagAffectsByteLengthForNonAsciiLiteral_369) {
  // Without Latin1: expect UTF-8 encoding -> 2 bytes for U+00E9.
  Regexp* utf8_re = Regexp::NewLiteral(0x00E9, Regexp::NoParseFlags);
  ASSERT_NE(utf8_re, nullptr);
  std::string utf8_prefix;
  bool utf8_fold = false;
  EXPECT_TRUE(utf8_re->RequiredPrefixForAccel(&utf8_prefix, &utf8_fold));
  EXPECT_GE(utf8_prefix.size(), 1u); // sanity
  EXPECT_EQ(utf8_prefix.size(), 2u); // UTF-8 for U+00E9 is 0xC3 0xA9
  EXPECT_FALSE(utf8_fold);
  utf8_re->Decref();

  // With Latin1: expect single byte (0xE9).
  Regexp* latin1_re = Regexp::NewLiteral(0x00E9, static_cast<Regexp::ParseFlags>(Regexp::Latin1));
  ASSERT_NE(latin1_re, nullptr);
  std::string latin1_prefix;
  bool latin1_fold = false;
  EXPECT_TRUE(latin1_re->RequiredPrefixForAccel(&latin1_prefix, &latin1_fold));
  EXPECT_EQ(latin1_prefix.size(), 1u); // Latin-1 single byte
  EXPECT_FALSE(latin1_fold);
  latin1_re->Decref();
}
