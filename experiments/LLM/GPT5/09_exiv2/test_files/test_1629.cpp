// TEST_ID 1629
#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"

namespace {

using Exiv2::Internal::TiffFinder;
using Exiv2::Internal::TiffVisitor::GoEvent;
using Exiv2::Internal::TiffVisitor::geTraverse;

class TiffFinderTest_1629 : public ::testing::Test {
 protected:
  // Use numeric casts to avoid depending on specific IfdId enumerator names.
  static constexpr uint16_t kTagA = 0x0001;
  static constexpr uint16_t kTagB = 0x00FF;

  static constexpr Exiv2::IfdId kGroupA = static_cast<Exiv2::IfdId>(0);
  static constexpr Exiv2::IfdId kGroupB = static_cast<Exiv2::IfdId>(1);

  TiffFinder finder_{kTagA, kGroupA};
};

TEST_F(TiffFinderTest_1629, InitSetsTraverseGoTrueWhenPreviouslyFalse_1629) {
  // Arrange: explicitly disable traversal first.
  finder_.setGo(static_cast<GoEvent>(geTraverse), false);
  EXPECT_FALSE(finder_.go(static_cast<GoEvent>(geTraverse)));

  // Act: init with new tag/group.
  EXPECT_NO_THROW(finder_.init(kTagB, kGroupB));

  // Assert: traversal must be enabled after init (observable via public go()).
  EXPECT_TRUE(finder_.go(static_cast<GoEvent>(geTraverse)));
}

TEST_F(TiffFinderTest_1629, InitResetsResultToNullptr_1629) {
  // Act
  EXPECT_NO_THROW(finder_.init(kTagB, kGroupB));

  // Assert: result() is publicly observable and should be reset by init().
  EXPECT_EQ(finder_.result(), nullptr);
}

TEST_F(TiffFinderTest_1629, MultipleInitCallsKeepTraverseEnabledAndResultNull_1629) {
  // First init
  finder_.setGo(static_cast<GoEvent>(geTraverse), false);
  finder_.init(kTagA, kGroupA);
  EXPECT_TRUE(finder_.go(static_cast<GoEvent>(geTraverse)));
  EXPECT_EQ(finder_.result(), nullptr);

  // Change state again, then init again
  finder_.setGo(static_cast<GoEvent>(geTraverse), false);
  finder_.init(kTagB, kGroupB);

  EXPECT_TRUE(finder_.go(static_cast<GoEvent>(geTraverse)));
  EXPECT_EQ(finder_.result(), nullptr);
}

}  // namespace