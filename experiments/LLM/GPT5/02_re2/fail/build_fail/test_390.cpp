// File: prog_init_alt_test_390.cc

#include <cstdint>
#include <limits>
#include "gtest/gtest.h"

#include "re2/prog.h"  // assumes the headers in the prompt resolve to this path

using re2::Prog;
using re2::kInstAlt;

// ----- Normal operation ------------------------------------------------------

TEST(ProgInstTest_390, InitAlt_SetsOpcodeAndOuts_390) {
  Prog::Inst inst;

  const uint32_t out  = 123u;
  const uint32_t out1 = 456u;

  inst.InitAlt(out, out1);

  // Observable behavior through public API only.
  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(static_cast<uint32_t>(inst.out()),  out);
  EXPECT_EQ(static_cast<uint32_t>(inst.out1()), out1);
}

// ----- Boundary conditions ---------------------------------------------------

TEST(ProgInstTest_390, InitAlt_ZeroValues_390) {
  Prog::Inst inst;

  const uint32_t out  = 0u;
  const uint32_t out1 = 0u;

  inst.InitAlt(out, out1);

  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(static_cast<uint32_t>(inst.out()),  out);
  EXPECT_EQ(static_cast<uint32_t>(inst.out1()), out1);
}

TEST(ProgInstTest_390, InitAlt_MaxUint32Values_390) {
  Prog::Inst inst;

  const uint32_t out  = std::numeric_limits<uint32_t>::max();
  const uint32_t out1 = std::numeric_limits<uint32_t>::max();

  inst.InitAlt(out, out1);

  EXPECT_EQ(inst.opcode(), kInstAlt);
  EXPECT_EQ(static_cast<uint32_t>(inst.out()),  out);
  EXPECT_EQ(static_cast<uint32_t>(inst.out1()), out1);
}

// ----- Exceptional / debug-checked behavior ---------------------------------
// The implementation uses ABSL_DCHECK to enforce that InitAlt is called only
// on an uninitialized instruction. Calling it twice should fail in debug
// builds. In non-debug builds this check may be compiled out; we use
// EXPECT_DEBUG_DEATH which only asserts in debug-mode.

#if GTEST_HAS_DEATH_TEST
TEST(ProgInstTest_390, InitAlt_SecondCallTriggersDebugCheck_390) {
  // Ensure death tests run in a robust mode when supported.
  ::testing::GTEST_FLAG_SET(death_test_style, "threadsafe");

  auto should_crash = []() {
    Prog::Inst inst;
    inst.InitAlt(1u, 2u);
    // Second initialization violates the documented precondition and should
    // hit the debug check in debug builds.
    inst.InitAlt(3u, 4u);
  };

  EXPECT_DEBUG_DEATH(should_crash(), "");
}
#endif  // GTEST_HAS_DEATH_TEST
