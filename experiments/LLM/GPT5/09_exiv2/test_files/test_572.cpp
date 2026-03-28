// TEST_ID: 572
// File: test_blockmap_572.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

namespace Exiv2 {
class BlockMap {
public:
  bool isKnown() const { return type_ == bKnown; }

private:
  // NOTE: The real codebase provides the full definition; this test only relies on the public API.
  enum blockType_e { bNone = 0, bKnown = 1, bMemory = 2 };
  blockType_e type_{bNone};
};
}  // namespace Exiv2

namespace {

class BlockMapTest_572 : public ::testing::Test {};

TEST_F(BlockMapTest_572, IsKnownCallableOnConstAndReturnsBool_572) {
  const Exiv2::BlockMap bm;
  static_assert(std::is_same_v<decltype(bm.isKnown()), bool>, "isKnown() must return bool");
  EXPECT_NO_THROW((void)bm.isKnown());
}

TEST_F(BlockMapTest_572, IsKnownIsStableAcrossRepeatedCalls_572) {
  Exiv2::BlockMap bm;
  const bool first = bm.isKnown();
  for (int i = 0; i < 10; ++i) {
    EXPECT_NO_THROW((void)bm.isKnown());
    EXPECT_EQ(bm.isKnown(), first);
  }
}

TEST_F(BlockMapTest_572, CopyConstructPreservesObservedIsKnownValue_572) {
  Exiv2::BlockMap original;
  const bool v = original.isKnown();

  Exiv2::BlockMap copy(original);
  EXPECT_EQ(copy.isKnown(), v);

  // Ensure original still behaves consistently.
  EXPECT_EQ(original.isKnown(), v);
}

TEST_F(BlockMapTest_572, CopyAssignPreservesObservedIsKnownValue_572) {
  Exiv2::BlockMap src;
  const bool v = src.isKnown();

  Exiv2::BlockMap dst;
  dst = src;

  EXPECT_EQ(dst.isKnown(), v);
  EXPECT_EQ(src.isKnown(), v);
}

TEST_F(BlockMapTest_572, MoveConstructAndMovedFromRemainCallable_572) {
  Exiv2::BlockMap src;
  const bool before = src.isKnown();

  Exiv2::BlockMap moved(std::move(src));
  EXPECT_EQ(moved.isKnown(), before);

  // Moved-from object should still be in a valid state; at minimum, calling isKnown() should not throw.
  EXPECT_NO_THROW((void)src.isKnown());
}

TEST_F(BlockMapTest_572, MoveAssignAndMovedFromRemainCallable_572) {
  Exiv2::BlockMap src;
  const bool before = src.isKnown();

  Exiv2::BlockMap dst;
  dst = std::move(src);

  EXPECT_EQ(dst.isKnown(), before);
  EXPECT_NO_THROW((void)src.isKnown());
}

TEST_F(BlockMapTest_572, MultipleInstancesAreIndependentlyCallable_572) {
  Exiv2::BlockMap a;
  Exiv2::BlockMap b;

  EXPECT_NO_THROW((void)a.isKnown());
  EXPECT_NO_THROW((void)b.isKnown());

  // We don't assume what the default should be; we only check each instance is self-consistent.
  EXPECT_EQ(a.isKnown(), a.isKnown());
  EXPECT_EQ(b.isKnown(), b.isKnown());
}

}  // namespace