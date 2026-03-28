// TEST_ID: 102
#include <limits>
#include "gtest/gtest.h"
#include "re2/prog.h"

using re2::Prog;
using re2::kInstAlt;
using re2::kInstAltMatch;

// Suite dedicated to Inst::out1() behavior.
class InstOut1Test_102 : public ::testing::Test {};

// Normal operation: After InitAlt, out1() returns the second successor.
TEST_F(InstOut1Test_102, InitAlt_SetsOut1_ReturnsGivenValue_102) {
  Prog::Inst inst;
  inst.InitAlt(/*out=*/10u, /*out1=*/20u);
  EXPECT_EQ(inst.out1(), 20);
}

// Boundary values that are still within the observable (int) return domain.
TEST_F(InstOut1Test_102, InitAlt_AllowsZeroAndIntMax_102) {
  {
    Prog::Inst inst;
    inst.InitAlt(/*out=*/0u, /*out1=*/0u);
    EXPECT_EQ(inst.out1(), 0);
  }
  {
    Prog::Inst inst;
    const uint32_t kVal = static_cast<uint32_t>(std::numeric_limits<int>::max());
    inst.InitAlt(/*out=*/1u, /*out1=*/kVal);
    EXPECT_EQ(inst.out1(), static_cast<int>(kVal));
  }
}

// Sanity: out() and out1() are distinct observable successors after InitAlt.
TEST_F(InstOut1Test_102, InitAlt_DistinguishesOutAndOut1_102) {
  Prog::Inst inst;
  inst.InitAlt(/*out=*/123u, /*out1=*/456u);
  // Verify each accessor reports its own observable value.
  EXPECT_NE(inst.out(), inst.out1());
  EXPECT_EQ(inst.out(), 123);
  EXPECT_EQ(inst.out1(), 456);
}

// Error/exceptional observable behavior: DCHECK triggers when opcode is not Alt/AltMatch.
// Run as a death test only when supported and when DCHECKs are enabled (debug builds).
TEST_F(InstOut1Test_102, Out1_DCHECKs_WhenOpcodeNotAlt_102) {
#if GTEST_HAS_DEATH_TEST && !defined(NDEBUG)
  Prog::Inst inst;
  inst.InitNop(/*out=*/7u);  // Initializes a non-Alt opcode.
  EXPECT_DEATH_IF_SUPPORTED(inst.out1(), "");  // Message is implementation-defined.
#else
  GTEST_SKIP() << "Death test skipped: either not supported or built without DCHECKs.";
#endif
}
