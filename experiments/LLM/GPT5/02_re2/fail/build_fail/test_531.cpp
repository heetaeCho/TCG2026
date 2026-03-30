// File: parse_charclass_test_531.cc
#include <gtest/gtest.h>
#include "re2/regexp.h"
#include "re2/unicode_groups.h"
#include "absl/strings/string_view.h"

using namespace re2;

class ParseCharClassTest_531 : public ::testing::Test {
protected:
  // Helper to invoke ParseCharClass with given input and flags, capturing outputs.
  bool Call(absl::string_view input,
            Regexp::ParseFlags flags,
            absl::string_view* rest,
            Regexp** out_re,
            RegexpStatus* status) {
    *rest = input;
    Regexp::ParseState ps(flags, /*whole_regexp=*/input, status);
    return ps.ParseCharClass(rest, out_re, status);
  }

  // Ensures we Decref any Regexp* we created on success.
  void SafeDecref(Regexp* re) {
    if (re) re->Decref();
  }
};

// --- Normal operation ---

// Single literal inside class: [a]
TEST_F(ParseCharClassTest_531, SingleLiteral_Succeeds_531) {
  absl::string_view rest;
  Regexp* out = nullptr;
  RegexpStatus st;

  ASSERT_TRUE(Call("[a]", Regexp::NoParseFlags, &rest, &out, &st));
  ASSERT_NE(out, nullptr);
  ASSERT_NE(out->ccb_, nullptr);

  // Observable behavior: the parsed class contains 'a' and not 'b'.
  EXPECT_TRUE(out->ccb_->Contains('a'));
  EXPECT_FALSE(out->ccb_->Contains('b'));

  // Input pointer advanced just past the closing bracket.
  EXPECT_EQ(rest, absl::string_view(""));

  SafeDecref(out);
}

// Character range: [a-c] includes a, b, c
TEST_F(ParseCharClassTest_531, Range_Inclusive_531) {
  absl::string_view rest;
  Regexp* out = nullptr;
  RegexpStatus st;

  ASSERT_TRUE(Call("[a-c]", Regexp::NoParseFlags, &rest, &out, &st));
  ASSERT_NE(out, nullptr);
  ASSERT_NE(out->ccb_, nullptr);

  EXPECT_TRUE(out->ccb_->Contains('a'));
  EXPECT_TRUE(out->ccb_->Contains('b'));
  EXPECT_TRUE(out->ccb_->Contains('c'));
  EXPECT_FALSE(out->ccb_->Contains('d'));

  EXPECT_EQ(rest, absl::string_view(""));
  SafeDecref(out);
}

// ']' allowed as the first char in class: []]  (class containing just ']')
TEST_F(ParseCharClassTest_531, RightBracketAsFirstChar_531) {
  absl::string_view rest;
  Regexp* out = nullptr;
  RegexpStatus st;

  ASSERT_TRUE(Call("[]]", Regexp::NoParseFlags, &rest, &out, &st));
  ASSERT_NE(out, nullptr);
  ASSERT_NE(out->ccb_, nullptr);

  EXPECT_TRUE(out->ccb_->Contains(']'));
  EXPECT_FALSE(out->ccb_->Contains('['));

  EXPECT_EQ(rest, absl::string_view(""));
  SafeDecref(out);
}

// Negated class: [^a] should exclude 'a' and include non-'a' characters.
TEST_F(ParseCharClassTest_531, NegatedClass_ExcludesMember_531) {
  absl::string_view rest;
  Regexp* out = nullptr;
  RegexpStatus st;

  ASSERT_TRUE(Call("[^a]", Regexp::NoParseFlags, &rest, &out, &st));
  ASSERT_NE(out, nullptr);
  ASSERT_NE(out->ccb_, nullptr);

  EXPECT_FALSE(out->ccb_->Contains('a'));
  EXPECT_TRUE(out->ccb_->Contains('b'));

  EXPECT_EQ(rest, absl::string_view(""));
  SafeDecref(out);
}

// --- Boundary / pointer-advancement check ---

// After a successful parse, *s should point after the closing ']'.
TEST_F(ParseCharClassTest_531, RestPointsAfterClassOnSuccess_531) {
  absl::string_view rest;
  Regexp* out = nullptr;
  RegexpStatus st;

  ASSERT_TRUE(Call("[x]tail", Regexp::NoParseFlags, &rest, &out, &st));
  ASSERT_NE(out, nullptr);
  ASSERT_EQ(rest, absl::string_view("tail"));

  SafeDecref(out);
}

// --- Exceptional / error cases ---

// Input not starting with '[' should fail with kRegexpInternalError.
TEST_F(ParseCharClassTest_531, NotStartingWithBracket_InternalError_531) {
  absl::string_view rest;
  Regexp* out = nullptr;
  RegexpStatus st;

  EXPECT_FALSE(Call("abc", Regexp::NoParseFlags, &rest, &out, &st));
  EXPECT_EQ(st.code(), kRegexpInternalError);
  EXPECT_EQ(st.error_arg(), absl::string_view()); // per implementation
  EXPECT_EQ(out, nullptr);
}

// Missing closing ']' should fail with kRegexpMissingBracket and error_arg=whole class.
TEST_F(ParseCharClassTest_531, MissingClosingBracket_531) {
  absl::string_view rest;
  Regexp* out = nullptr;
  RegexpStatus st;

  // Whole class is "[abc" (no closing bracket).
  absl::string_view input = "[abc";
  EXPECT_FALSE(Call(input, Regexp::NoParseFlags, &rest, &out, &st));
  EXPECT_EQ(st.code(), kRegexpMissingBracket);
  EXPECT_EQ(st.error_arg(), input);
  EXPECT_EQ(out, nullptr);
}
