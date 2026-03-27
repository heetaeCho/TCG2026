// File: compiler_match_test_299.cc
#include <gtest/gtest.h>
#include <cstdint>

// Headers from the project under test
// (Keep these includes consistent with your tree layout)
#include "re2/compile.cc"   // or the proper header that declares re2::Compiler / Frag / kNullPatchList
#include "re2/prog.h"

namespace {

using re2::Compiler;
using re2::PatchList;

// Fixture kept minimal since we treat the class as a black box.
class CompilerMatchTest_299 : public ::testing::Test {
protected:
  Compiler c_;  // default-construct and use directly
};

}  // namespace

// --- Tests ---

// Normal case: Match returns a Frag with a valid begin id, a null PatchList, and non-nullable.
// We do NOT assume anything else about internal state or allocation details.
TEST_F(CompilerMatchTest_299, MatchReturnsFragShape_299) {
  const int32_t kAnyMatchId = 123;

  re2::Frag f = c_.Match(kAnyMatchId);

  // Observable expectations based on the provided implementation:
  // 1) Frag(begin_id, kNullPatchList, false)
  // We cannot assert exact 'begin' value (depends on allocator), but it must be non-negative
  // on success; if allocator failed, Match would have returned NoMatch(), which should differ
  // from the shape (nullable=false + kNullPatchList) asserted below.
  EXPECT_GE(f.begin, 0) << "Expected a non-negative begin id on successful allocation.";

  // kNullPatchList is a public constant: {0, 0}
  EXPECT_EQ(f.end.head, re2::kNullPatchList.head);
  EXPECT_EQ(f.end.tail, re2::kNullPatchList.tail);

  // Match returns a non-nullable fragment per the provided code.
  EXPECT_FALSE(f.nullable);
}

// Boundary-ish input: large positive match id should still produce a valid Frag shape.
// We cannot (and do not) verify any internal instruction fields.
TEST_F(CompilerMatchTest_299, MatchWithLargePositiveId_299) {
  const int32_t kLargeId = INT32_MAX;

  re2::Frag f = c_.Match(kLargeId);

  EXPECT_GE(f.begin, 0);
  EXPECT_EQ(f.end.head, re2::kNullPatchList.head);
  EXPECT_EQ(f.end.tail, re2::kNullPatchList.tail);
  EXPECT_FALSE(f.nullable);
}

// Boundary-ish input: negative match id is still an int32_t.
// The observable contract for Match’s return Frag remains the same if allocation succeeds.
// (We do not assert anything about internal Prog::Inst content.)
TEST_F(CompilerMatchTest_299, MatchWithNegativeId_299) {
  const int32_t kNegativeId = -1;

  re2::Frag f = c_.Match(kNegativeId);

  EXPECT_GE(f.begin, 0);
  EXPECT_EQ(f.end.head, re2::kNullPatchList.head);
  EXPECT_EQ(f.end.tail, re2::kNullPatchList.tail);
  EXPECT_FALSE(f.nullable);
}

/*
Notes / Rationale (kept in comments, not assertions):

- We intentionally avoid any verification of internal state (e.g., inst_ array, opcodes,
  or whether Prog::Inst::InitMatch actually set the match id), because that would require
  peeking into private state or relying on non-public behavior.

- The failure path (AllocInst < 0 -> NoMatch()) is not forced here because AllocInst and
  NoMatch are methods on the class under test and are not declared virtual in the provided
  interface; we therefore avoid trying to override or interpose them. If your test harness
  provides a supported way to simulate allocation failure via public API (e.g., a setup
  function or a memory cap), you can add a test that asserts Match returns exactly the
  Frag produced by NoMatch() (comparing its public fields).

- The tests above stick strictly to observable effects of Match’s public return value:
  begin is a non-negative id on success, end equals kNullPatchList, and nullable is false.
*/
