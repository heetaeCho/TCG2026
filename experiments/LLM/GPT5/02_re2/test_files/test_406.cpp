// File: prog_optimize_test_406.cc
#include <gtest/gtest.h>
#include "re2/prog.h"

namespace re2 {

class ProgOptimizeTest_406 : public ::testing::Test {
protected:
  Prog p_;

  // Convenience to get opcode/out/out1 quickly.
  static InstOp Op(Prog* p, int id) { return p->inst(id)->opcode(); }
  static int Out(Prog* p, int id)    { return p->inst(id)->out(); }
  static int Out1(Prog* p, int id)   { return p->inst(id)->out1(); }
};

//
// 1) NOP-skipping on the main out-edge
//
TEST_F(ProgOptimizeTest_406, CollapseNopChainOnOut_406) {
  // Program:
  //   start -> (1)
  //   (1): NOP -> 2
  //   (2): NOP -> 3
  //   (3): MATCH
  p_.set_start(1);
  p_.inst(1)->InitNop(/*out=*/2);
  p_.inst(2)->InitNop(/*out=*/3);
  p_.inst(3)->InitMatch(/*id=*/0);

  p_.Optimize();

  // After Optimize(), NOP chains on out-edges are bypassed.
  EXPECT_EQ(Op(&p_, 1), kInstNop);
  EXPECT_EQ(Out(&p_, 1), 3);
  // Target should remain MATCH.
  EXPECT_EQ(Op(&p_, 3), kInstMatch);
}

//
// 2) NOP-skipping on both arms of an ALT
//
TEST_F(ProgOptimizeTest_406, CollapseNopChainsOnAltArms_406) {
  // Program:
  //   start -> (1)
  //   (1): ALT out=2, out1=4
  //   (2): NOP -> 3
  //   (3): MATCH
  //   (4): NOP -> 5
  //   (5): MATCH
  p_.set_start(1);
  p_.inst(1)->InitAlt(/*out=*/2, /*out1=*/4);
  p_.inst(2)->InitNop(/*out=*/3);
  p_.inst(3)->InitMatch(/*id=*/0);
  p_.inst(4)->InitNop(/*out=*/5);
  p_.inst(5)->InitMatch(/*id=*/1);

  p_.Optimize();

  // After Optimize(), both arms should bypass the NOPs.
  EXPECT_EQ(Op(&p_, 1), kInstAlt);
  EXPECT_EQ(Out(&p_, 1), 3);
  EXPECT_EQ(Out1(&p_, 1), 5);
  EXPECT_EQ(Op(&p_, 3), kInstMatch);
  EXPECT_EQ(Op(&p_, 5), kInstMatch);
}

//
// 3) ALT -> ALTMATCH when left is ByteRange[0x00..0xFF] looping back,
//    and right is a (reachable) MATCH
//
TEST_F(ProgOptimizeTest_406, AltBecomesAltMatch_LeftByteRangeLoop_RightMatch_406) {
  // Program shape the optimizer checks:
  //   (1): ALT out=2, out1=3
  //   (2): ByteRange[0x00..0xFF] -> out=1  (loops back to ALT)
  //   (3): MATCH
  //
  // Expectation: opcode(1) becomes kInstAltMatch.
  p_.set_start(1);
  p_.inst(1)->InitAlt(/*out=*/2, /*out1=*/3);
  p_.inst(2)->InitByteRange(/*lo=*/0x00, /*hi=*/0xFF, /*foldcase=*/0, /*out=*/1);
  p_.inst(3)->InitMatch(/*id=*/0);

  p_.Optimize();

  EXPECT_EQ(Op(&p_, 1), kInstAltMatch);
}

//
// 4) ALT -> ALTMATCH when right is ByteRange[0x00..0xFF] looping back,
//    and left is a (reachable) MATCH
//
TEST_F(ProgOptimizeTest_406, AltBecomesAltMatch_RightByteRangeLoop_LeftMatch_406) {
  //   (1): ALT out=3, out1=2
  //   (2): ByteRange[0x00..0xFF] -> out=1 (loops back)
  //   (3): MATCH
  p_.set_start(1);
  p_.inst(1)->InitAlt(/*out=*/3, /*out1=*/2);
  p_.inst(2)->InitByteRange(/*lo=*/0x00, /*hi=*/0xFF, /*foldcase=*/0, /*out=*/1);
  p_.inst(3)->InitMatch(/*id=*/0);

  p_.Optimize();

  EXPECT_EQ(Op(&p_, 1), kInstAltMatch);
}

//
// 5) No ALTMATCH conversion if the ByteRange isn't full [0x00..0xFF]
//
TEST_F(ProgOptimizeTest_406, NoAltMatchWhenByteRangeNotFull_406) {
  // Same as test (3) but the ByteRange is partial.
  //   (1): ALT out=2, out1=3
  //   (2): ByteRange[0x00..0xFE] -> out=1 (loops back)
  //   (3): MATCH
  p_.set_start(1);
  p_.inst(1)->InitAlt(/*out=*/2, /*out1=*/3);
  p_.inst(2)->InitByteRange(/*lo=*/0x00, /*hi=*/0xFE, /*foldcase=*/0, /*out=*/1);
  p_.inst(3)->InitMatch(/*id=*/0);

  p_.Optimize();

  // Should remain a normal ALT.
  EXPECT_EQ(Op(&p_, 1), kInstAlt);
  EXPECT_EQ(Out(&p_, 1), 2);
  EXPECT_EQ(Out1(&p_, 1), 3);
}

//
// 6) No ALTMATCH conversion if the ByteRange does not loop back to the ALT
//
TEST_F(ProgOptimizeTest_406, NoAltMatchWhenByteRangeDoesNotLoop_406) {
  //   (1): ALT out=2, out1=3
  //   (2): ByteRange[0x00..0xFF] -> out=4 (does NOT loop back)
  //   (3): MATCH
  //   (4): NOP -> 1 (irrelevant, not a direct out==id)
  p_.set_start(1);
  p_.inst(1)->InitAlt(/*out=*/2, /*out1=*/3);
  p_.inst(2)->InitByteRange(/*lo=*/0x00, /*hi=*/0xFF, /*foldcase=*/0, /*out=*/4);
  p_.inst(3)->InitMatch(/*id=*/0);
  p_.inst(4)->InitNop(/*out=*/1);

  p_.Optimize();

  // Should remain ALT because j->out() != id directly.
  EXPECT_EQ(Op(&p_, 1), kInstAlt);
}

}  // namespace re2
