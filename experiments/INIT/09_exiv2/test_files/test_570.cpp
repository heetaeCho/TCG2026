// TEST_ID 570
// Unit tests for Exiv2::BlockMap::markKnown
//
// Notes:
// - These tests treat BlockMap as a black box and verify only observable behavior
//   through the public interface (isNone/isKnown/getSize/getData).
// - BlockMap appears to be implemented in src/basicio.cpp (not a public header),
//   so we include the implementation file to access the class definition.

#include <gtest/gtest.h>

#include <cstddef>
#include <limits>

// If BlockMap is not exposed via a header in your build, including the .cpp is a
// common pattern for testing internal translation-unit types.
#include "basicio.cpp"  // NOLINT(bugprone-suspicious-include)

namespace {

class BlockMapTest_570 : public ::testing::Test {};

TEST_F(BlockMapTest_570, DefaultStateIsQueryable_570) {
  Exiv2::BlockMap bm;

  // We don't assume which state is default, only that queries are callable and consistent.
  const bool none = bm.isNone();
  const bool known = bm.isKnown();

  // A block shouldn't be both "none" and "known" at the same time.
  EXPECT_FALSE(none && known);

  // Size should be queryable in default state.
  (void)bm.getSize();

  // Data should be queryable in default state.
  const auto& data = bm.getData();
  (void)data;
}

TEST_F(BlockMapTest_570, MarkKnownZeroSetsKnownAndSizeZero_570) {
  Exiv2::BlockMap bm;

  EXPECT_NO_THROW(bm.markKnown(0u));

  EXPECT_TRUE(bm.isKnown());
  EXPECT_FALSE(bm.isNone());
  EXPECT_EQ(bm.getSize(), 0u);

  const auto& data = bm.getData();
  (void)data;
}

TEST_F(BlockMapTest_570, MarkKnownNonZeroSetsKnownAndSize_570) {
  Exiv2::BlockMap bm;

  constexpr std::size_t kNum = 17u;
  bm.markKnown(kNum);

  EXPECT_TRUE(bm.isKnown());
  EXPECT_FALSE(bm.isNone());
  EXPECT_EQ(bm.getSize(), kNum);

  const auto& data = bm.getData();
  (void)data;
}

TEST_F(BlockMapTest_570, MarkKnownCanBeCalledRepeatedlyAndUpdatesSize_570) {
  Exiv2::BlockMap bm;

  bm.markKnown(1u);
  EXPECT_TRUE(bm.isKnown());
  EXPECT_EQ(bm.getSize(), 1u);

  bm.markKnown(99u);
  EXPECT_TRUE(bm.isKnown());
  EXPECT_EQ(bm.getSize(), 99u);

  bm.markKnown(0u);
  EXPECT_TRUE(bm.isKnown());
  EXPECT_EQ(bm.getSize(), 0u);
}

TEST_F(BlockMapTest_570, MarkKnownAcceptsMaxSizeTWithoutThrowing_570) {
  Exiv2::BlockMap bm;

  const std::size_t maxv = (std::numeric_limits<std::size_t>::max)();
  EXPECT_NO_THROW(bm.markKnown(maxv));

  EXPECT_TRUE(bm.isKnown());
  EXPECT_FALSE(bm.isNone());
  EXPECT_EQ(bm.getSize(), maxv);
}

TEST_F(BlockMapTest_570, MarkKnownAfterPopulateStillReportsKnownAndSize_570) {
  Exiv2::BlockMap bm;

  // Use a minimal buffer; we don't assume populate semantics beyond it being callable.
  const unsigned char bytes[] = {0x01, 0x02, 0x03, 0x04};

  EXPECT_NO_THROW(bm.populate(reinterpret_cast<const Exiv2::byte*>(bytes), sizeof(bytes)));

  // markKnown should set the block to known with the requested size (observable via getSize/isKnown).
  bm.markKnown(sizeof(bytes));

  EXPECT_TRUE(bm.isKnown());
  EXPECT_FALSE(bm.isNone());
  EXPECT_EQ(bm.getSize(), sizeof(bytes));

  const auto& data = bm.getData();
  (void)data;
}

TEST_F(BlockMapTest_570, MarkKnownIsNoThrowForTypicalValues_570) {
  Exiv2::BlockMap bm;

  EXPECT_NO_THROW(bm.markKnown(1u));
  EXPECT_NO_THROW(bm.markKnown(1024u));
  EXPECT_NO_THROW(bm.markKnown(0u));
}

}  // namespace