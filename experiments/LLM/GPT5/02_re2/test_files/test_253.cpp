// File: re2_partialmatchn_test_253.cc
#include <string>
#include "gtest/gtest.h"

#include "re2/re2.h"
#include "absl/strings/string_view.h"

using re2::RE2;

class RE2_PartialMatchNTest_253 : public ::testing::Test {};

TEST_F(RE2_PartialMatchNTest_253, ReturnsTrueOnSubstringMatch_UnanchoredSemantics_253) {
  RE2 re("abc");                         // treat as black box regex object
  const RE2::Arg* args[] = {};           // no captures
  bool ok = re.PartialMatchN(absl::string_view("xxabcxx"), re, args, /*n=*/0);
  EXPECT_TRUE(ok);
}

TEST_F(RE2_PartialMatchNTest_253, ReturnsFalseWhenNoMatch_253) {
  RE2 re("abc");
  const RE2::Arg* args[] = {};
  bool ok = re.PartialMatchN(absl::string_view("xxxx"), re, args, /*n=*/0);
  EXPECT_FALSE(ok);
}

TEST_F(RE2_PartialMatchNTest_253, StartAnchorPatternDoesNotMatchInMiddle_253) {
  // Verifies observable unanchored search behavior of PartialMatchN by contrasting with a start-anchored pattern.
  RE2 re("^abc");
  const RE2::Arg* args[] = {};
  bool ok = re.PartialMatchN(absl::string_view("zabcz"), re, args, /*n=*/0);
  EXPECT_FALSE(ok);
}

TEST_F(RE2_PartialMatchNTest_253, EmptyPatternMatches_253) {
  RE2 re("");
  const RE2::Arg* args[] = {};
  bool ok = re.PartialMatchN(absl::string_view("anything here"), re, args, /*n=*/0);
  EXPECT_TRUE(ok);
}

TEST_F(RE2_PartialMatchNTest_253, ForwardsCapturesAndCount_OneCaptureToString_253) {
  RE2 re("([0-9]+)");
  std::string captured;
  RE2::Arg a_capture(&captured);
  const RE2::Arg* args[] = { &a_capture };

  bool ok = re.PartialMatchN(absl::string_view("ID=12345"), re, args, /*n=*/1);
  EXPECT_TRUE(ok);
  EXPECT_EQ(captured, "12345");
}

TEST_F(RE2_PartialMatchNTest_253, ForwardsCaptures_MultipleStrings_253) {
  RE2 re("([A-Za-z]+)-([A-Za-z]+)");
  std::string left, right;
  RE2::Arg a_left(&left), a_right(&right);
  const RE2::Arg* args[] = { &a_left, &a_right };

  bool ok = re.PartialMatchN(absl::string_view("token=foo-bar-baz"), re, args, /*n=*/2);
  EXPECT_TRUE(ok);
  EXPECT_EQ(left,  "foo");
  EXPECT_EQ(right, "bar");
}

TEST_F(RE2_PartialMatchNTest_253, ZeroCapturesWithNullArgsPointerIsOkay_253) {
  RE2 re("word");
  // Passing nullptr for args with n=0 should be a no-op for captures.
  const RE2::Arg* const* args = nullptr;
  bool ok = re.PartialMatchN(absl::string_view("some word here"), re, args, /*n=*/0);
  EXPECT_TRUE(ok);
}

TEST_F(RE2_PartialMatchNTest_253, InvalidPatternBehavesAsNoMatch_253) {
  RE2 re("("); // construct with an invalid pattern; treated as black box
  const RE2::Arg* args[] = {};
  bool ok = re.PartialMatchN(absl::string_view("anything"), re, args, /*n=*/0);
  EXPECT_FALSE(ok);
}
