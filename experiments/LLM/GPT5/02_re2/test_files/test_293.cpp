// File: compiler_alt_test_293.cc
#include <gtest/gtest.h>

#include "re2/prog.h"
#include "re2/compile.h"

namespace re2 {

class CompilerAltTest_293 : public ::testing::Test {
protected:
  Compiler c_;  // Use the real compiler as a black box.

  // Helper to make a clearly non-NoMatch fragment using the public Frag ctor.
  // PatchList::Mk() is used as provided by the interface.
  static Frag MakeFrag(uint32_t begin, uint32_t end_patch, bool nullable) {
    return Frag(begin, PatchList::Mk(end_patch), nullable);
  }
};

// A is NoMatch -> should return B unchanged (short-circuit)
TEST_F(CompilerAltTest_293, Alt_ReturnsB_WhenAIsNoMatch_293) {
  Frag a = c_.NoMatch();                        // guaranteed "no match" via the public API
  Frag b = CompilerAltTest_293::MakeFrag(7, 42, /*nullable=*/true);

  Frag r = c_.Alt(a, b);

  // Observable expectations: r equals b (begin/end/nullable).
  EXPECT_EQ(r.begin, b.begin);
  EXPECT_EQ(r.end.head, b.end.head);
  EXPECT_EQ(r.end.tail, b.end.tail);
  EXPECT_EQ(r.nullable, b.nullable);
}

// B is NoMatch -> should return A unchanged (short-circuit)
TEST_F(CompilerAltTest_293, Alt_ReturnsA_WhenBIsNoMatch_293) {
  Frag a = CompilerAltTest_293::MakeFrag(11, 5, /*nullable=*/false);
  Frag b = c_.NoMatch();

  Frag r = c_.Alt(a, b);

  // Observable expectations: r equals a (begin/end/nullable).
  EXPECT_EQ(r.begin, a.begin);
  EXPECT_EQ(r.end.head, a.end.head);
  EXPECT_EQ(r.end.tail, a.end.tail);
  EXPECT_EQ(r.nullable, a.nullable);
}

// Both A and B are NoMatch -> returns NoMatch (the function returns B in the first branch,
// but since B is also NoMatch, the result must be a NoMatch fragment by observation)
TEST_F(CompilerAltTest_293, Alt_ReturnsNoMatch_WhenBothNoMatch_293) {
  Frag a = c_.NoMatch();
  Frag b = c_.NoMatch();

  Frag r = c_.Alt(a, b);

  // Use the public NoMatch() result to compare observable properties.
  Frag nm = c_.NoMatch();

  EXPECT_EQ(r.begin, nm.begin);
  EXPECT_EQ(r.end.head, nm.end.head);
  EXPECT_EQ(r.end.tail, nm.end.tail);
  EXPECT_EQ(r.nullable, nm.nullable);
}

// Short-circuit path preserves nullable flag of the returned operand
TEST_F(CompilerAltTest_293, Alt_PreservesNullable_OnShortCircuit_293) {
  // Case 1: A is NoMatch, B has nullable=false
  {
    Frag a = c_.NoMatch();
    Frag b = CompilerAltTest_293::MakeFrag(3, 9, /*nullable=*/false);
    Frag r = c_.Alt(a, b);
    EXPECT_FALSE(r.nullable);
  }
  // Case 2: B is NoMatch, A has nullable=true
  {
    Frag a = CompilerAltTest_293::MakeFrag(4, 12, /*nullable=*/true);
    Frag b = c_.NoMatch();
    Frag r = c_.Alt(a, b);
    EXPECT_TRUE(r.nullable);
  }
}

}  // namespace re2
