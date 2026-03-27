// File: parse_state_constructor_tests_607.cc

#include "gtest/gtest.h"

// Public APIs & constants used by the tests.
#include "re2/regexp.h"
#include "re2/util/utf.h"

// The class under test (interface is declared/defined in this TU).
// We include the .cc solely to obtain the public interface of the nested type
// and to keep the class a black box (no private access).
#include "re2/parse.cc"

using re2::Runemax;

class ParseStateTest_607 : public ::testing::Test {
protected:
  re2::RegexpStatus status_;
};

// Normal operation: when Latin1 flag is NOT set, rune_max() should match Runemax.
TEST(ParseStateTest_607, RuneMax_DefaultUnicode_607) {
  re2::Regexp::ParseFlags flags = static_cast<re2::Regexp::ParseFlags>(0); // NoParseFlags
  absl::string_view pattern = "abc";
  re2::Regexp::ParseState ps(flags, pattern, &status_);

  EXPECT_EQ(ps.rune_max(), Runemax);
}

// Boundary/flag behavior: when Latin1 is set, rune_max() should be 0xFF.
TEST(ParseStateTest_607, RuneMax_Latin1_607) {
  re2::Regexp::ParseFlags flags = re2::Regexp::Latin1;
  absl::string_view pattern = "";
  re2::Regexp::ParseState ps(flags, pattern, &status_);

  EXPECT_EQ(ps.rune_max(), 0xFF);
}

// Combined flags: Latin1 together with other flags should still force rune_max() to 0xFF.
TEST(ParseStateTest_607, RuneMax_Latin1WithOtherFlags_607) {
  re2::Regexp::ParseFlags flags = static_cast<re2::Regexp::ParseFlags>(
      re2::Regexp::Latin1 | re2::Regexp::FoldCase | re2::Regexp::DotNL);
  absl::string_view pattern = "(?i)a.b";
  re2::Regexp::ParseState ps(flags, pattern, &status_);

  EXPECT_EQ(ps.rune_max(), 0xFF);
}

// Constructor echoes flags via flags() accessor (observable behavior only).
TEST(ParseStateTest_607, FlagsEchoedFromConstructor_607) {
  re2::Regexp::ParseFlags flags = static_cast<re2::Regexp::ParseFlags>(
      re2::Regexp::FoldCase | re2::Regexp::DotNL | re2::Regexp::PerlX);
  absl::string_view pattern = "x+y?";
  re2::Regexp::ParseState ps(flags, pattern, &status_);

  EXPECT_EQ(ps.flags(), flags);
}

// Exceptional-ish case (observable): construction with nullptr status must not crash,
// and accessors remain usable.
TEST(ParseStateTest_607, ConstructWithNullStatus_607) {
  re2::Regexp::ParseFlags flags = re2::Regexp::Latin1;
  absl::string_view pattern = "[]";
  re2::Regexp::ParseState ps(flags, pattern, /*status=*/nullptr);

  // Still check observable accessors.
  EXPECT_EQ(ps.flags(), flags);
  EXPECT_EQ(ps.rune_max(), 0xFF);
}
