// File: inst_last_test_100.cc
#include <gtest/gtest.h>
#include "TestProjects/re2/re2/prog.h"

using re2::Prog;

// Test fixture kept minimal to honor black-box constraints.
class InstLastTest_100 : public ::testing::Test {
protected:
  Prog::Inst inst_;  // default-constructed; will be initialized via public API
};

// --- Normal operation: last() should return a boolean-like value (0 or 1) ---

TEST_F(InstLastTest_100, InitMatch_LastReturns0or1_100) {
  // Arrange
  Prog::Inst inst;
  inst.InitMatch(123);  // Use a valid public initializer

  // Act
  int v = inst.last();

  // Assert
  EXPECT_TRUE(v == 0 || v == 1) << "last() must be 0 or 1";
}

TEST_F(InstLastTest_100, InitNop_LastReturns0or1_100) {
  Prog::Inst inst;
  inst.InitNop(/*out=*/0u);

  int v = inst.last();
  EXPECT_TRUE(v == 0 || v == 1);
}

TEST_F(InstLastTest_100, InitFail_LastReturns0or1_100) {
  Prog::Inst inst;
  inst.InitFail();

  int v = inst.last();
  EXPECT_TRUE(v == 0 || v == 1);
}

TEST_F(InstLastTest_100, InitAlt_LastReturns0or1_100) {
  Prog::Inst inst;
  inst.InitAlt(/*out=*/1u, /*out1=*/2u);

  int v = inst.last();
  EXPECT_TRUE(v == 0 || v == 1);
}

TEST_F(InstLastTest_100, InitByteRange_LastReturns0or1_100) {
  Prog::Inst inst;
  // Use a small valid range and foldcase flag as per public signature.
  inst.InitByteRange(/*lo=*/'a', /*hi=*/'z', /*foldcase=*/0, /*out=*/0u);

  int v = inst.last();
  EXPECT_TRUE(v == 0 || v == 1);
}

TEST_F(InstLastTest_100, InitCapture_LastReturns0or1_100) {
  Prog::Inst inst;
  inst.InitCapture(/*cap=*/2, /*out=*/0u);

  int v = inst.last();
  EXPECT_TRUE(v == 0 || v == 1);
}

// --- Boundary-ish behavior (stability & copy/assign semantics) ---

TEST_F(InstLastTest_100, LastIsStableAcrossMultipleCalls_100) {
  Prog::Inst inst;
  inst.InitMatch(7);

  int first = inst.last();
  // Call multiple times; value should be stable for a given state.
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(first, inst.last());
  }
}

TEST_F(InstLastTest_100, CopyConstructorPreservesLast_100) {
  Prog::Inst inst;
  inst.InitAlt(3u, 4u);
  int before = inst.last();

  Prog::Inst copy(inst);
  int after = copy.last();

  EXPECT_TRUE(before == 0 || before == 1);
  EXPECT_EQ(before, after);
}

TEST_F(InstLastTest_100, AssignmentOperatorPreservesLast_100) {
  Prog::Inst a;
  a.InitNop(5u);
  int before = a.last();

  Prog::Inst b;
  b = a;  // use public operator=

  int after = b.last();
  EXPECT_EQ(before, after);
}

// --- Re-initialization via public API should yield a valid (0/1) result ---

TEST_F(InstLastTest_100, ReinitializeWithDifferentInits_StillValid_100) {
  Prog::Inst inst;

  inst.InitFail();
  EXPECT_TRUE(inst.last() == 0 || inst.last() == 1);

  inst.InitNop(0u);
  EXPECT_TRUE(inst.last() == 0 || inst.last() == 1);

  inst.InitMatch(0);
  EXPECT_TRUE(inst.last() == 0 || inst.last() == 1);

  inst.InitAlt(1u, 2u);
  EXPECT_TRUE(inst.last() == 0 || inst.last() == 1);

  inst.InitByteRange('A', 'Z', 0, 0u);
  EXPECT_TRUE(inst.last() == 0 || inst.last() == 1);

  inst.InitCapture(1, 0u);
  EXPECT_TRUE(inst.last() == 0 || inst.last() == 1);
}
