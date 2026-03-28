// TEST_ID 574
// File: test_blockmap_getsize_574.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

// BlockMap is implemented in basicio.cpp (per prompt). Include it directly to access the type.
#include "basicio.cpp"

namespace {

class BlockMapTest_574 : public ::testing::Test {};

TEST_F(BlockMapTest_574, GetSizeHasExpectedSignature_574) {
  using Expected = size_t (Exiv2::BlockMap::*)() const;
  static_assert(std::is_same_v<decltype(&Exiv2::BlockMap::getSize), Expected>,
                "BlockMap::getSize must be: size_t getSize() const");
  SUCCEED();
}

TEST_F(BlockMapTest_574, DefaultConstructedGetSizeIsStableAcrossCalls_574) {
  Exiv2::BlockMap bm;

  const size_t first = bm.getSize();
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(first, bm.getSize()) << "getSize() should be stable across repeated calls";
  }
}

TEST_F(BlockMapTest_574, ConstAndNonConstAccessReturnSameValue_574) {
  Exiv2::BlockMap bm;

  const size_t nonConstValue = bm.getSize();
  const Exiv2::BlockMap& cbm = bm;

  EXPECT_EQ(nonConstValue, cbm.getSize());
}

TEST_F(BlockMapTest_574, CopyAndAssignmentPreserveObservableSizeAtCopyTime_574) {
  Exiv2::BlockMap original;
  const size_t originalSize = original.getSize();

  Exiv2::BlockMap copyConstructed(original);
  EXPECT_EQ(originalSize, copyConstructed.getSize());

  Exiv2::BlockMap assigned;
  assigned = original;
  EXPECT_EQ(originalSize, assigned.getSize());
}

}  // namespace