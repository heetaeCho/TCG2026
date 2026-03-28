// File: onepass_checks_test.cc
#include <gtest/gtest.h>

// Public enum with kEmptyAllFlags
#include "re2/prog.h"

// The function under test lives in a .cc with no header; declare it extern.
namespace re2 {
  void OnePass_Checks();
  extern const int kEmptyShift;
  extern const int kMaxCap;
  // Prog::kMaxOnePassCapture should be declared in prog.h (or a transitively
  // included header) as part of the public API we can observe.
  class Prog {
   public:
    static const int kMaxOnePassCapture;  // provided by the codebase
  };
}  // namespace re2

using namespace re2;

class OnePassChecksTest_564 : public ::testing::Test {};

// Sanity: calling the function should be valid and not crash/throw.
TEST_F(OnePassChecksTest_564, OnePassChecksCallable_564) {
  // Observable behavior: the function is callable and returns (void).
  // If the compile-time assertions embedded in it fail, this won’t link/build.
  OnePass_Checks();
  SUCCEED();
}

// The bitmask formed by kEmptyShift must exactly cover all empty flags.
TEST_F(OnePassChecksTest_564, EmptyMaskMatchesAllFlags_564) {
  const int mask = (1 << kEmptyShift) - 1;
  EXPECT_EQ(mask, kEmptyAllFlags) << "Mask derived from kEmptyShift must equal kEmptyAllFlags";
  // Boundary check: next bit beyond all flags should be exactly one greater.
  EXPECT_EQ((1 << kEmptyShift), kEmptyAllFlags + 1)
      << "Next bit beyond all empty flags must be 1<<kEmptyShift";
}

// Public constant value expectation: kEmptyShift should be 6 (as exposed).
TEST_F(OnePassChecksTest_564, EmptyShiftIsSix_564) {
  // This checks the observable constant published by the library.
  EXPECT_EQ(kEmptyShift, 6);
}

// Max capture slots consistency with Prog::kMaxOnePassCapture.
TEST_F(OnePassChecksTest_564, MaxCapMatchesProgContract_564) {
  // Observable contract: kMaxCap equals Prog::kMaxOnePassCapture * 2.
  EXPECT_EQ(kMaxCap, Prog::kMaxOnePassCapture * 2);
}
