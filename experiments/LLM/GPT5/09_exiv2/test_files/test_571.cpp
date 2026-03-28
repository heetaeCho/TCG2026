// TEST_ID: 571
//
// Unit tests for Exiv2::BlockMap::isNone()
// File under test: ./TestProjects/exiv2/src/basicio.cpp
//
// Notes:
// - Treat BlockMap as a black box: tests only use the observable public interface.
// - Since the provided public interface exposes only isNone(), tests focus on
//   construction/copy/move/const usage and the stability of the observable result.

#include <gtest/gtest.h>
#include <type_traits>

// The class is implemented in basicio.cpp and may not be exposed via a public header in this kata.
// Including the implementation file is a pragmatic way to access the real definition without
// re-implementing it here.
#include "basicio.cpp"

namespace {

class BlockMapTest_571 : public ::testing::Test {};

TEST_F(BlockMapTest_571, IsNoneReturnsBool_571) {
  Exiv2::BlockMap bm;
  static_assert(std::is_same_v<decltype(bm.isNone()), bool>,
                "BlockMap::isNone() must return bool");
}

TEST_F(BlockMapTest_571, DefaultConstructedReportsNone_571) {
  Exiv2::BlockMap bm;
  EXPECT_TRUE(bm.isNone());
}

TEST_F(BlockMapTest_571, ConstObjectCallableAndStable_571) {
  const Exiv2::BlockMap bm;
  const bool first = bm.isNone();
  const bool second = bm.isNone();
  EXPECT_EQ(first, second);
}

TEST_F(BlockMapTest_571, CopyConstructionPreservesObservableState_571) {
  Exiv2::BlockMap original;
  const bool before = original.isNone();

  Exiv2::BlockMap copy = original;
  EXPECT_EQ(copy.isNone(), before);

  // Also verify the original remains unchanged from the observer's perspective.
  EXPECT_EQ(original.isNone(), before);
}

TEST_F(BlockMapTest_571, MoveConstructionPreservesObservableState_571) {
  Exiv2::BlockMap original;
  const bool before = original.isNone();

  Exiv2::BlockMap moved = std::move(original);
  EXPECT_EQ(moved.isNone(), before);
}

}  // namespace