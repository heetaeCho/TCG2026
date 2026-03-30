// File: prog_inst_match_id_test.cc

#include <climits>
#include "gtest/gtest.h"
#include "re2/prog.h"

using re2::Prog;
using re2::kInstMatch;

//
// Normal operation: InitMatch should set opcode to kInstMatch,
// and match_id() should return the value provided to InitMatch.
//

TEST(ProgInstTest_108, InitMatch_SetsOpcodeToMatch_108) {
  Prog::Inst inst;
  inst.InitMatch(123);
  EXPECT_EQ(inst.opcode(), kInstMatch);
}

TEST(ProgInstTest_108, MatchId_ReturnsProvidedValue_108) {
  Prog::Inst inst;
  inst.InitMatch(42);
  EXPECT_EQ(inst.match_id(), 42);
}

//
// Boundary conditions: verify observable behavior with edge-ish values
// allowed by the interface (int32_t for InitMatch parameter).
//

TEST(ProgInstTest_108, MatchId_Zero_108) {
  Prog::Inst inst;
  inst.InitMatch(0);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 0);
}

TEST(ProgInstTest_108, MatchId_NegativeValue_108) {
  Prog::Inst inst;
  inst.InitMatch(-1);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), -1);
}

TEST(ProgInstTest_108, MatchId_Int32Max_108) {
  Prog::Inst inst;
  inst.InitMatch(INT32_MAX);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), INT32_MAX);
}

TEST(ProgInstTest_108, MatchId_Int32Min_108) {
  Prog::Inst inst;
  inst.InitMatch(INT32_MIN);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), INT32_MIN);
}

//
// Re-initialization: calling InitMatch again should update the
// observable match_id() result.
//

TEST(ProgInstTest_108, ReinitMatch_UpdatesMatchId_108) {
  Prog::Inst inst;
  inst.InitMatch(7);
  EXPECT_EQ(inst.match_id(), 7);

  inst.InitMatch(99);
  EXPECT_EQ(inst.opcode(), kInstMatch);
  EXPECT_EQ(inst.match_id(), 99);
}

//
// Copy & assignment: defaulted copy/assignment should preserve
// observable state (opcode and match_id()).
//

TEST(ProgInstTest_108, CopyConstructor_PreservesOpcodeAndMatchId_108) {
  Prog::Inst original;
  original.InitMatch(314);

  Prog::Inst copy(original);
  EXPECT_EQ(copy.opcode(), kInstMatch);
  EXPECT_EQ(copy.match_id(), 314);
}

TEST(ProgInstTest_108, AssignmentOperator_PreservesOpcodeAndMatchId_108) {
  Prog::Inst a, b;
  a.InitMatch(1);
  b.InitMatch(2024);

  a = b;
  EXPECT_EQ(a.opcode(), kInstMatch);
  EXPECT_EQ(a.match_id(), 2024);
}
