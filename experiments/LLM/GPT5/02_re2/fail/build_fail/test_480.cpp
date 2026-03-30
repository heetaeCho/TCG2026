// File: parse_state_rune_max_test_480.cc
#include "gtest/gtest.h"

// RE2 headers for types used in the public interface.
#include "re2/regexp.h"            // re2::Regexp, RegexpStatus, ParseFlags, flag enums
#include "absl/strings/string_view.h"

namespace {

using re2::Regexp;

// Fixture kept minimal; we don't assume any internal state/logic.
class ParseStateTest_480 : public ::testing::Test {};

// Normal operation (Unicode mode): rune_max() should reflect the Unicode maximum.
// We assert the widely used Unicode scalar max (0x10FFFF) which is stable for RE2.
TEST_F(ParseStateTest_480, RuneMax_DefaultUnicode_480) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0);  // no special flags
  re2::RegexpStatus status;
  Regexp::ParseState ps(flags, absl::string_view(""), &status);

  // Observable behavior: accessor returns a value.
  // Expect Unicode maximum code point.
  EXPECT_EQ(ps.rune_max(), 0x10FFFF);
}

// Boundary condition: Latin1 mode should clamp the maximum rune to 0xFF.
// This is observable via the public flag and the accessor.
TEST_F(ParseStateTest_480, RuneMax_Latin1_480) {
  Regexp::ParseFlags flags =
      static_cast<Regexp::ParseFlags>(Regexp::Latin1);
  re2::RegexpStatus status;
  Regexp::ParseState ps(flags, absl::string_view(""), &status);

  EXPECT_EQ(ps.rune_max(), 0xFF);
}

// Combination of flags (including Latin1) should still enforce the Latin1 bound.
// Verifies interaction with other flags via the public API without assuming internals.
TEST_F(ParseStateTest_480, RuneMax_Latin1WithOtherFlags_480) {
  Regexp::ParseFlags flags =
      static_cast<Regexp::ParseFlags>(Regexp::Latin1 | Regexp::OneLine | Regexp::PerlX);
  re2::RegexpStatus status;
  Regexp::ParseState ps(flags, absl::string_view("(?:test)"), &status);

  EXPECT_EQ(ps.rune_max(), 0xFF);
}

// Idempotence / stability: multiple calls to rune_max() should be consistent and have no side effects.
TEST_F(ParseStateTest_480, RuneMax_IsStableAcrossCalls_480) {
  Regexp::ParseFlags flags = static_cast<Regexp::ParseFlags>(0);
  re2::RegexpStatus status;
  Regexp::ParseState ps(flags, absl::string_view("abc|def"), &status);

  const int first = ps.rune_max();
  const int second = ps.rune_max();
  const int third = ps.rune_max();

  EXPECT_EQ(first, 0x10FFFF);
  EXPECT_EQ(second, first);
  EXPECT_EQ(third, first);
}

}  // namespace
