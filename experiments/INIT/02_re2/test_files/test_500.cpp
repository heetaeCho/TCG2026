// File: parse_is_marker_test.cc

#include <gtest/gtest.h>
#include "re2/parse.h"  // Assumes the project exposes Regexp, ParseState, RegexpOp, ParseFlags, RegexpStatus
#include "absl/strings/string_view.h"

using re2::Regexp;
using re2::RegexpOp;
using re2::kLeftParen;

class ParseStateIsMarkerTest_500 : public ::testing::Test {
protected:
  // Helper to create a ParseState with minimal, harmless arguments.
  // We don't depend on or inspect any internal state.
  static Regexp::ParseState MakeState(absl::string_view pattern,
                                      re2::ParseFlags flags = static_cast<re2::ParseFlags>(0)) {
    re2::RegexpStatus status;
    return Regexp::ParseState(flags, pattern, &status);
  }
};

// Normal/boundary: op == kLeftParen should be considered a marker.
TEST_F(ParseStateIsMarkerTest_500, ReturnsTrueAtBoundary_500) {
  auto st = ParseStateIsMarkerTest_500::MakeState("");
  EXPECT_TRUE(st.IsMarker(kLeftParen));
}

// Boundary just below: any op immediately below kLeftParen is *not* a marker.
TEST_F(ParseStateIsMarkerTest_500, ReturnsFalseBelowBoundary_500) {
  auto st = ParseStateIsMarkerTest_500::MakeState("x");
  // Construct an op just below the boundary without relying on private internals.
  auto below = static_cast<RegexpOp>(static_cast<int>(kLeftParen) - 1);
  EXPECT_FALSE(st.IsMarker(below));
}

// Above boundary: ops greater than kLeftParen should be considered markers.
TEST_F(ParseStateIsMarkerTest_500, ReturnsTrueAboveBoundary_500) {
  auto st = ParseStateIsMarkerTest_500::MakeState("abc");
  auto above = static_cast<RegexpOp>(static_cast<int>(kLeftParen) + 3);
  EXPECT_TRUE(st.IsMarker(above));
}

// Independence from object state: IsMarker result depends only on the argument (observable).
TEST_F(ParseStateIsMarkerTest_500, IndependentOfState_500) {
  // Deliberately vary flags and input; result should remain identical for the same op.
  auto st1 = ParseStateIsMarkerTest_500::MakeState("one", static_cast<re2::ParseFlags>(0));
  auto st2 = ParseStateIsMarkerTest_500::MakeState("two", static_cast<re2::ParseFlags>(0xFFFF));

  EXPECT_TRUE(st1.IsMarker(kLeftParen));
  EXPECT_TRUE(st2.IsMarker(kLeftParen));

  auto below = static_cast<RegexpOp>(static_cast<int>(kLeftParen) - 1);
  EXPECT_FALSE(st1.IsMarker(below));
  EXPECT_FALSE(st2.IsMarker(below));
}
