// File: compile_capture_test_301.cc

#include <gtest/gtest.h>

// Include the headers that declare the types used by the interface under test.
// Adjust include paths as needed to match your project layout.
#include "re2/compile.cc"   // for re2::Compiler, Frag, PatchList (as declared in the prompt)
#include "re2/prog.h"       // for re2::Prog::Inst (type is used internally; we don't access it)

// We only use public surface/observable behavior. No private state access.

namespace re2 {

class CompilerCaptureTest_301 : public ::testing::Test {
 protected:
  // Helper: Compare two Frags by their observable public fields.
  static void ExpectFragEqual(const Frag& a, const Frag& b) {
    EXPECT_EQ(a.begin, b.begin);
    EXPECT_EQ(a.nullable, b.nullable);
    // Compare PatchList by its public fields.
    EXPECT_EQ(a.end.head, b.end.head);
    EXPECT_EQ(a.end.tail, b.end.tail);
  }

  // Helper: Build a PatchList expected by Capture's return value for a given id.
  static PatchList ExpectedEndForId(uint32_t id) {
    // Capture returns end = PatchList::Mk((id+1) << 1)
    return PatchList::Mk((id + 1) << 1);
  }
};

// --- Tests ---

// Normal behavior with a "real" fragment (non-NoMatch), null patchlist.
// Verifies: returned begin equals the id allocated by Capture,
//           returned end equals Mk((id+1)<<1),
//           nullable is propagated unchanged.
TEST_F(CompilerCaptureTest_301, Capture_ReturnsCorrectFrag_301) {
  Compiler c;

  // Construct an input fragment "a" with no pending patches (end is null patch list).
  Frag a;                // default leaves end as kNullPatchList (we don't depend on its exact value)
  a.begin = 123;         // arbitrary; Capture uses a.begin when initializing capture inst
  a.nullable = true;     // should be propagated to the output

  // Call Capture. We cannot observe the allocated id directly.
  Frag out = c.Capture(a, /*n=*/5);

  // To compute the id used by Capture, allocate one more instruction now.
  // Capture allocates exactly 2 instructions; the next AllocInst(1) should return id_after = id_used_by_capture + 2.
  int id_after = c.AllocInst(1);
  ASSERT_GE(id_after, 0);  // sanity

  int expected_id = id_after - 2;
  ASSERT_GE(expected_id, 0);  // sanity

  // Verify observable fields of the returned Frag.
  EXPECT_EQ(out.begin, static_cast<uint32_t>(expected_id));
  PatchList expected_end = ExpectedEndForId(expected_id);
  EXPECT_EQ(out.end.head, expected_end.head);
  EXPECT_EQ(out.end.tail, expected_end.tail);
  EXPECT_TRUE(out.nullable);
}

// Input is NoMatch -> Capture should return NoMatch (by spec in provided snippet).
// We validate equality by comparing observable fields of the two Frags.
TEST_F(CompilerCaptureTest_301, Capture_OnNoMatchInput_ReturnsNoMatch_301) {
  Compiler c;

  Frag nm = c.NoMatch();
  Frag out = c.Capture(nm, /*n=*/0);

  ExpectFragEqual(out, nm);
}

// Nullable propagation check when input is non-nullable.
// Ensures that Capture does not change the nullable flag.
TEST_F(CompilerCaptureTest_301, Capture_PropagatesNullableFalse_301) {
  Compiler c;

  Frag a;           // end remains a null patch list
  a.begin = 7;
  a.nullable = false;

  Frag out = c.Capture(a, /*n=*/1);

  // Compute expected id via the same post-allocation trick.
  int id_after = c.AllocInst(1);
  ASSERT_GE(id_after, 0);

  int expected_id = id_after - 2;
  ASSERT_GE(expected_id, 0);

  EXPECT_EQ(out.begin, static_cast<uint32_t>(expected_id));
  PatchList expected_end = PatchList::Mk((expected_id + 1) << 1);
  EXPECT_EQ(out.end.head, expected_end.head);
  EXPECT_EQ(out.end.tail, expected_end.tail);
  EXPECT_FALSE(out.nullable);
}

// Sequential calls: Ensure each Capture reserves exactly two instructions.
// We observe this by checking the distance between the two begin ids using a trailing AllocInst(1).
TEST_F(CompilerCaptureTest_301, Capture_SequentialCalls_AdvanceByTwo_301) {
  Compiler c;

  Frag a1; a1.begin = 10; a1.nullable = true;
  Frag r1 = c.Capture(a1, /*n=*/2);

  Frag a2; a2.begin = 20; a2.nullable = false;
  Frag r2 = c.Capture(a2, /*n=*/3);

  // Next allocation's id should be r2.begin + 2.
  int id_after = c.AllocInst(1);
  ASSERT_GE(id_after, 0);

  int expected_r2_begin = id_after - 2;
  ASSERT_GE(expected_r2_begin, 0);

  EXPECT_EQ(r2.begin, static_cast<uint32_t>(expected_r2_begin));

  // And r1.begin should be two less than r2.begin.
  EXPECT_EQ(r2.begin, r1.begin + 2u);

  // Also verify end fields are consistent with each begin id.
  PatchList expected_end_r1 = PatchList::Mk((static_cast<int>(r1.begin) + 1) << 1);
  PatchList expected_end_r2 = PatchList::Mk((static_cast<int>(r2.begin) + 1) << 1);

  EXPECT_EQ(r1.end.head, expected_end_r1.head);
  EXPECT_EQ(r1.end.tail, expected_end_r1.tail);
  EXPECT_EQ(r2.end.head, expected_end_r2.head);
  EXPECT_EQ(r2.end.tail, expected_end_r2.tail);

  // Nullable propagation check for both cases.
  EXPECT_TRUE(r1.nullable);
  EXPECT_FALSE(r2.nullable);
}

}  // namespace re2
