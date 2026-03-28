// TEST_ID 1637
#include <gtest/gtest.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace {

// Keep everything in an anonymous namespace to avoid ODR/link collisions across the test suite.
using Exiv2::Internal::TiffFinder;
using Exiv2::Internal::TiffMnEntry;
using Exiv2::Internal::IfdId;

class TiffFinderTest_1637 : public ::testing::Test {
 protected:
  static constexpr uint16_t kTagA = 0x0100;
  static constexpr uint16_t kTagB = 0x0101;

  // Avoid assuming specific IfdId enumerators exist; treat it as an enum-like type.
  static constexpr IfdId kGroupA = static_cast<IfdId>(0);
  static constexpr IfdId kGroupB = static_cast<IfdId>(1);
  static constexpr IfdId kMnGroup = static_cast<IfdId>(2);
};

TEST_F(TiffFinderTest_1637, VisitMnEntryWithNullptrDoesNotChangeResult_1637) {
  TiffFinder finder(kTagA, kGroupA);
  EXPECT_EQ(finder.result(), nullptr);

  // Observable behavior: should be safe to call with nullptr (no crash) and keep result unchanged.
  finder.visitMnEntry(nullptr);

  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1637, VisitMnEntryMatchingTagAndGroupSetsResultToObject_1637) {
  TiffMnEntry mn(kTagA, kGroupA, kMnGroup);
  TiffFinder finder(kTagA, kGroupA);

  EXPECT_EQ(finder.result(), nullptr);

  finder.visitMnEntry(&mn);

  EXPECT_EQ(finder.result(), &mn);
}

TEST_F(TiffFinderTest_1637, VisitMnEntryNonMatchingTagDoesNotSetResult_1637) {
  TiffMnEntry mn(kTagB, kGroupA, kMnGroup);
  TiffFinder finder(kTagA, kGroupA);

  finder.visitMnEntry(&mn);

  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1637, VisitMnEntryNonMatchingGroupDoesNotSetResult_1637) {
  TiffMnEntry mn(kTagA, kGroupB, kMnGroup);
  TiffFinder finder(kTagA, kGroupA);

  finder.visitMnEntry(&mn);

  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1637, InitUpdatesCriteriaSoLaterVisitMnEntryCanMatch_1637) {
  TiffMnEntry mnA(kTagA, kGroupA, kMnGroup);
  TiffMnEntry mnB(kTagB, kGroupB, kMnGroup);

  TiffFinder finder(kTagA, kGroupA);

  // First, a non-matching visit should not set a result.
  finder.visitMnEntry(&mnB);
  EXPECT_EQ(finder.result(), nullptr);

  // Update criteria, then the same object should be discoverable.
  finder.init(kTagB, kGroupB);
  finder.visitMnEntry(&mnB);
  EXPECT_EQ(finder.result(), &mnB);

  // And visiting a different matching object should be observable (at least remains non-null).
  finder.visitMnEntry(&mnA);
  // We can only assert that if it matches current criteria it may change; mnA does not match now.
  EXPECT_EQ(finder.result(), &mnB);
}

}  // namespace