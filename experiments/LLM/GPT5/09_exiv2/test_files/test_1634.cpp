// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1634
//
// File: test_tifffinder_visitSizeEntry_1634.cpp

#include <gtest/gtest.h>

#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"

namespace Exiv2::Internal {
namespace {

class TiffFinderTest_1634 : public ::testing::Test {};

TEST_F(TiffFinderTest_1634, DefaultResultIsNullAfterConstruction_1634) {
  const uint16_t kTag = 0x0100;
  const IfdId kGroup = static_cast<IfdId>(0);

  const TiffFinder finder(kTag, kGroup);
  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1634, VisitSizeEntryWithMatchingTagGroupSetsResult_1634) {
  const uint16_t kTag = 0x0100;
  const IfdId kGroup = static_cast<IfdId>(0);

  TiffFinder finder(kTag, kGroup);

  TiffSizeEntry entry(/*tag=*/kTag, /*group=*/kGroup,
                      /*dtTag=*/0x0201, /*dtGroup=*/static_cast<IfdId>(1));

  finder.visitSizeEntry(&entry);

  // Observable behavior: result() reflects the found component.
  EXPECT_EQ(finder.result(), &entry);
}

TEST_F(TiffFinderTest_1634, VisitSizeEntryWithNonMatchingTagDoesNotSetResult_1634) {
  const uint16_t kWantedTag = 0x0100;
  const IfdId kGroup = static_cast<IfdId>(0);

  TiffFinder finder(kWantedTag, kGroup);

  TiffSizeEntry nonMatching(/*tag=*/static_cast<uint16_t>(kWantedTag + 1),
                            /*group=*/kGroup,
                            /*dtTag=*/0x0201, /*dtGroup=*/static_cast<IfdId>(1));

  finder.visitSizeEntry(&nonMatching);

  EXPECT_EQ(finder.result(), nullptr);
}

TEST_F(TiffFinderTest_1634, InitThenVisitSizeEntryFindsWithNewCriteria_1634) {
  const uint16_t kTag1 = 0x0100;
  const uint16_t kTag2 = 0x0101;
  const IfdId kGroup1 = static_cast<IfdId>(0);
  const IfdId kGroup2 = static_cast<IfdId>(1);

  TiffFinder finder(kTag1, kGroup1);

  TiffSizeEntry entry1(/*tag=*/kTag1, /*group=*/kGroup1,
                       /*dtTag=*/0x0201, /*dtGroup=*/static_cast<IfdId>(2));
  finder.visitSizeEntry(&entry1);
  ASSERT_EQ(finder.result(), &entry1);

  // Change search criteria and verify a new matching entry can be found.
  finder.init(kTag2, kGroup2);

  TiffSizeEntry entry2(/*tag=*/kTag2, /*group=*/kGroup2,
                       /*dtTag=*/0x0202, /*dtGroup=*/static_cast<IfdId>(3));
  finder.visitSizeEntry(&entry2);

  EXPECT_EQ(finder.result(), &entry2);
}

}  // namespace
}  // namespace Exiv2::Internal