// File: compile_isnomatch_test.cc
#include <gtest/gtest.h>
#include <cstdint>

//
// Minimal interfaces from the prompt so the tests can build.
// We DO NOT re-implement IsNoMatch; we only declare it.
// The struct matches the provided interface and is used strictly
// to construct inputs for observable-behavior testing.
//
namespace re2 {

// Minimal stand-ins so Frag can be constructed without relying on internal code.
using PatchList = uint32_t;
constexpr PatchList kNullPatchList = 0;

// Interface per prompt.
struct Frag {
 public:
  uint32_t begin;
  PatchList end;
  bool nullable;

  Frag() : begin(0), end(kNullPatchList), nullable(false) {}
  Frag(uint32_t begin_, PatchList end_, bool nullable_)
      : begin(begin_), end(end_), nullable(nullable_) {}
};

// Function under test (implementation provided elsewhere in the codebase).
bool IsNoMatch(Frag a);

}  // namespace re2

// ---------- Tests ----------

// Normal operation: begin == 0 should be treated as "no match".
TEST(IsNoMatchTest_291, ReturnsTrueWhenBeginIsZero_291) {
  re2::Frag f_default;  // begin defaults to 0 per interface
  EXPECT_TRUE(re2::IsNoMatch(f_default));

  re2::Frag f_zero_ctor(0u, re2::kNullPatchList, /*nullable=*/false);
  EXPECT_TRUE(re2::IsNoMatch(f_zero_ctor));
}

// Normal operation: any non-zero begin should not be "no match".
TEST(IsNoMatchTest_291, ReturnsFalseWhenBeginIsNonZero_291) {
  re2::Frag f1(1u, re2::kNullPatchList, /*nullable=*/false);
  EXPECT_FALSE(re2::IsNoMatch(f1));

  re2::Frag f123(123u, re2::kNullPatchList, /*nullable=*/true);
  EXPECT_FALSE(re2::IsNoMatch(f123));
}

// Boundary condition: maximum 32-bit value remains a valid (non-zero) begin.
TEST(IsNoMatchTest_291, ReturnsFalseAtUint32MaxBegin_291) {
  re2::Frag f_max(std::numeric_limits<uint32_t>::max(), re2::kNullPatchList, /*nullable=*/false);
  EXPECT_FALSE(re2::IsNoMatch(f_max));
}

// Observable independence: 'end' and 'nullable' should not affect result;
// only 'begin' determines the outcome. We vary end/nullable to confirm.
TEST(IsNoMatchTest_291, IgnoresEndAndNullable_291) {
  // begin == 0 -> true regardless of other fields
  re2::Frag f_zero_a(0u, /*end=*/42u, /*nullable=*/true);
  re2::Frag f_zero_b(0u, /*end=*/999u, /*nullable=*/false);
  EXPECT_TRUE(re2::IsNoMatch(f_zero_a));
  EXPECT_TRUE(re2::IsNoMatch(f_zero_b));

  // begin != 0 -> false regardless of other fields
  re2::Frag f_nonzero_a(10u, /*end=*/0u, /*nullable=*/true);
  re2::Frag f_nonzero_b(5u,  /*end=*/777u, /*nullable=*/false);
  EXPECT_FALSE(re2::IsNoMatch(f_nonzero_a));
  EXPECT_FALSE(re2::IsNoMatch(f_nonzero_b));
}
