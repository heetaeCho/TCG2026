// File: parse_pushwordboundary_test_491.cc
#include "gtest/gtest.h"

// Public enum for opcodes
#include "re2/regexp.h"

// Bring the tested class definition into this TU.
// We do not re-implement anything; we compile against the actual implementation.
#include "re2/parse.cc"

namespace {

// Verifies that PushWordBoundary(true) behaves like PushSimpleOp(kRegexpWordBoundary).
TEST(ParseState_PushWordBoundaryTest_491, TrueMapsToWordBoundaryOp_491) {
  // Use separate instances to avoid any state interaction between calls.
  re2::Regexp::ParseState ps_for_expected(/*flags=*/0, /*whole_regexp=*/"", /*status=*/nullptr);
  re2::Regexp::ParseState ps_under_test(/*flags=*/0, /*whole_regexp=*/"", /*status=*/nullptr);

  // Expected behavior: same observable return as pushing the simple op directly.
  bool expected = ps_for_expected.PushSimpleOp(re2::kRegexpWordBoundary);
  bool got = ps_under_test.PushWordBoundary(/*word=*/true);

  ASSERT_EQ(got, expected);
}

// Verifies that PushWordBoundary(false) behaves like PushSimpleOp(kRegexpNoWordBoundary).
TEST(ParseState_PushWordBoundaryTest_491, FalseMapsToNoWordBoundaryOp_491) {
  re2::Regexp::ParseState ps_for_expected(/*flags=*/0, /*whole_regexp=*/"", /*status=*/nullptr);
  re2::Regexp::ParseState ps_under_test(/*flags=*/0, /*whole_regexp=*/"", /*status=*/nullptr);

  bool expected = ps_for_expected.PushSimpleOp(re2::kRegexpNoWordBoundary);
  bool got = ps_under_test.PushWordBoundary(/*word=*/false);

  ASSERT_EQ(got, expected);
}

}  // namespace
