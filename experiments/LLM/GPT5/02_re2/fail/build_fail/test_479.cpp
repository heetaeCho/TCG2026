// File: parse_state_flags_test_479.cc

#include <gtest/gtest.h>

// We include the production .cc to get the concrete, black-box type under test.
// (The task provides the class only in parse.cc, not a header.)
#include "re2/parse.cc"

// If absl string_view isn't already available via parse.cc includes in your build,
// ensure absl is on the include path. The provided partial code uses absl::string_view.

namespace {

using re2::Regexp;

// Helper alias to avoid assuming the exact underlying type of ParseFlags.
using ParseFlagsT = decltype(std::declval<Regexp::ParseState&>().flags());

// ---------- Tests ----------

TEST(ParseStateFlagsTest_479, ReturnsConstructorFlags_479) {
  const ParseFlagsT kFlags = static_cast<ParseFlagsT>(0);  // boundary: no flags
  Regexp::ParseState state{kFlags, absl::string_view("a(b|c)*"), /*status=*/nullptr};

  EXPECT_EQ(state.flags(), kFlags);
}

TEST(ParseStateFlagsTest_479, PreservesMultipleBitFlags_479) {
  // Use a few distinct bits without assuming specific enum constants.
  const ParseFlagsT kFlags =
      static_cast<ParseFlagsT>((1u << 0) | (1u << 3) | (1u << 10));

  Regexp::ParseState state{kFlags, absl::string_view("xyz"), /*status=*/nullptr};

  EXPECT_EQ(state.flags(), kFlags);
}

TEST(ParseStateFlagsTest_479, IndependentOfWholeRegexpArgument_479) {
  const ParseFlagsT kFlags = static_cast<ParseFlagsT>(0x1234);

  Regexp::ParseState s1{kFlags, absl::string_view(""), /*status=*/nullptr};              // empty regexp
  Regexp::ParseState s2{kFlags, absl::string_view("(?:alpha|beta){2,3}?"), nullptr};     // complex regexp

  EXPECT_EQ(s1.flags(), kFlags);
  EXPECT_EQ(s2.flags(), kFlags);
}

TEST(ParseStateFlagsTest_479, DistinctAcrossInstances_479) {
  const ParseFlagsT kFlagsA = static_cast<ParseFlagsT>(0x0);
  const ParseFlagsT kFlagsB = static_cast<ParseFlagsT>(0xFFFF);

  Regexp::ParseState a{kFlagsA, absl::string_view("foo"), /*status=*/nullptr};
  Regexp::ParseState b{kFlagsB, absl::string_view("bar"), /*status=*/nullptr};

  EXPECT_EQ(a.flags(), kFlagsA);
  EXPECT_EQ(b.flags(), kFlagsB);
}

TEST(ParseStateFlagsTest_479, RepeatedCallsAreStable_479) {
  const ParseFlagsT kFlags = static_cast<ParseFlagsT>((1u << 5));
  Regexp::ParseState state{kFlags, absl::string_view(".*"), /*status=*/nullptr};

  // Call flags() multiple times; observable result should remain unchanged.
  EXPECT_EQ(state.flags(), kFlags);
  EXPECT_EQ(state.flags(), kFlags);
  EXPECT_EQ(state.flags(), kFlags);
}

}  // namespace
