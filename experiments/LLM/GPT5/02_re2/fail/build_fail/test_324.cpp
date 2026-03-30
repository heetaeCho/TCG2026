// File: re2_compiler_setup_test_324.cc

#include "gtest/gtest.h"

// Public headers from the project:
#include "re2/regexp.h"
#include "re2/re2.h"
#include "re2/compile.h"  // Declares re2::Compiler, Prog, Prog::Inst

using re2::Compiler;
using re2::Prog;
using re2::Regexp;

class CompilerSetupTest_324 : public ::testing::Test {
protected:
  Compiler c_;
};

// Verifies: When max_mem <= 0, Setup allows normal allocations (very high cap).
TEST_F(CompilerSetupTest_324, NonPositiveMaxMem_AllowsSmallAlloc_324) {
  c_.Setup(Regexp::NoParseFlags, /*max_mem=*/0, RE2::UNANCHORED);

  // Expect a small allocation to succeed.
  int id = c_.AllocInst(1);
  EXPECT_GE(id, 0) << "AllocInst(1) should succeed when max_mem <= 0";
}

// Verifies the boundary: when max_mem <= sizeof(Prog), capacity is zero ⇒ allocations fail.
TEST_F(CompilerSetupTest_324, MaxMemEqualToProgSize_DisallowsAnyAlloc_324) {
  const int64_t prog_size = static_cast<int64_t>(sizeof(Prog));

  c_.Setup(Regexp::NoParseFlags, /*max_mem=*/prog_size, RE2::UNANCHORED);

  int id = c_.AllocInst(1);
  // On failure AllocInst should indicate an error (e.g., negative). We assert failure is indicated.
  EXPECT_LT(id, 0) << "AllocInst(1) should fail when max_mem == sizeof(Prog)";
}

// Also check strictly less than sizeof(Prog) behaves the same (still zero capacity).
TEST_F(CompilerSetupTest_324, MaxMemLessThanProgSize_DisallowsAnyAlloc_324) {
  const int64_t prog_size = static_cast<int64_t>(sizeof(Prog));

  c_.Setup(Regexp::NoParseFlags, /*max_mem=*/prog_size - 1, RE2::UNANCHORED);

  int id = c_.AllocInst(1);
  EXPECT_LT(id, 0) << "AllocInst(1) should fail when max_mem < sizeof(Prog)";
}

// Verifies: For a small positive budget, capacity is respected. Craft max_mem so m == 2.
TEST_F(CompilerSetupTest_324, SmallPositiveBudget_RespectsCapacity_324) {
  const int64_t max_mem =
      static_cast<int64_t>(sizeof(Prog)) +
      static_cast<int64_t>(sizeof(Prog::Inst)) * 2;  // m = 2

  c_.Setup(Regexp::NoParseFlags, max_mem, RE2::UNANCHORED);

  int id1 = c_.AllocInst(1);
  int id2 = c_.AllocInst(1);
  int id3 = c_.AllocInst(1);  // should exceed the capacity derived from max_mem

  EXPECT_GE(id1, 0) << "First allocation within budget should succeed";
  EXPECT_GE(id2, 0) << "Second allocation within budget should succeed";
  EXPECT_LT(id3, 0) << "Third allocation should fail once capacity is exhausted";
}

// Sanity check: Setting Latin1 flag should not prevent normal allocation behavior.
TEST_F(CompilerSetupTest_324, Latin1Flag_AllowsAllocation_324) {
  c_.Setup(Regexp::Latin1, /*max_mem=*/0, RE2::UNANCHORED);
  int id = c_.AllocInst(1);
  EXPECT_GE(id, 0) << "AllocInst(1) should succeed even with Latin1 flag when budget is ample";
}
