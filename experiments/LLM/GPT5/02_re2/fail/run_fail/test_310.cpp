// File: re2_compiler_ByteRangeEqual_test_310.cc
#include <gtest/gtest.h>

#include "re2/prog.h"      // Declares Prog::Inst interface (indirectly used by Compiler)
#include "re2/compile.cc"  // Provides re2::Compiler and the ByteRangeEqual definition

namespace re2 {

class CompilerByteRangeEqualTest_310 : public ::testing::Test {
protected:
  Compiler c_;
};

// [Normal] Same (lo, hi, foldcase) -> equal
TEST_F(CompilerByteRangeEqualTest_310, SameRangeSameFold_ReturnsTrue_310) {
  // 'A'..'A', foldcase=false
  int id1 = c_.UncachedRuneByteSuffix(static_cast<uint8_t>('A'),
                                      static_cast<uint8_t>('A'),
                                      /*foldcase=*/false,
                                      /*next=*/0);
  int id2 = c_.UncachedRuneByteSuffix(static_cast<uint8_t>('A'),
                                      static_cast<uint8_t>('A'),
                                      /*foldcase=*/false,
                                      /*next=*/0);

  EXPECT_TRUE(c_.ByteRangeEqual(id1, id2));
}

// [Normal] Different bounds -> not equal
TEST_F(CompilerByteRangeEqualTest_310, DifferentHiOrLo_ReturnsFalse_310) {
  int id_loA_hiA = c_.UncachedRuneByteSuffix(static_cast<uint8_t>('A'),
                                             static_cast<uint8_t>('A'),
                                             /*foldcase=*/false,
                                             /*next=*/0);
  int id_loA_hiB = c_.UncachedRuneByteSuffix(static_cast<uint8_t>('A'),
                                             static_cast<uint8_t>('B'),
                                             /*foldcase=*/false,
                                             /*next=*/0);

  EXPECT_FALSE(c_.ByteRangeEqual(id_loA_hiA, id_loA_hiB));
}

// [Normal] Same bounds, different foldcase flag -> not equal
TEST_F(CompilerByteRangeEqualTest_310, SameBoundsDifferentFoldcase_ReturnsFalse_310) {
  int id_fold_off = c_.UncachedRuneByteSuffix(static_cast<uint8_t>('a'),
                                              static_cast<uint8_t>('a'),
                                              /*foldcase=*/false,
                                              /*next=*/0);
  int id_fold_on = c_.UncachedRuneByteSuffix(static_cast<uint8_t>('a'),
                                             static_cast<uint8_t>('a'),
                                             /*foldcase=*/true,
                                             /*next=*/0);

  EXPECT_FALSE(c_.ByteRangeEqual(id_fold_off, id_fold_on));
}

// [Boundary] Minimum byte value 0x00 vs maximum 0xFF -> not equal
TEST_F(CompilerByteRangeEqualTest_310, BoundaryMinVsMax_NotEqual_310) {
  int id_min = c_.UncachedRuneByteSuffix(0x00, 0x00, /*foldcase=*/false, /*next=*/0);
  int id_max = c_.UncachedRuneByteSuffix(0xFF, 0xFF, /*foldcase=*/false, /*next=*/0);

  EXPECT_FALSE(c_.ByteRangeEqual(id_min, id_max));
}

// [Boundary] Self-comparison must always be true
TEST_F(CompilerByteRangeEqualTest_310, SelfComparison_True_310) {
  int id = c_.UncachedRuneByteSuffix(static_cast<uint8_t>('Z'),
                                     static_cast<uint8_t>('Z'),
                                     /*foldcase=*/true,
                                     /*next=*/0);

  EXPECT_TRUE(c_.ByteRangeEqual(id, id));
}

// [Interaction] Cached vs Uncached creation with identical params -> equal
TEST_F(CompilerByteRangeEqualTest_310, CachedVsUncachedSameParams_Equal_310) {
  uint8_t lo = static_cast<uint8_t>('x');
  uint8_t hi = static_cast<uint8_t>('x');
  bool foldcase = false;

  int id_uncached = c_.UncachedRuneByteSuffix(lo, hi, foldcase, /*next=*/0);
  int id_cached   = c_.CachedRuneByteSuffix  (lo, hi, foldcase, /*next=*/0);

  EXPECT_TRUE(c_.ByteRangeEqual(id_uncached, id_cached));
}

}  // namespace re2
