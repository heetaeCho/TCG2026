#include <gtest/gtest.h>
#include <cstdint>

// Include necessary headers from the exiv2 project
#include "tiffcomposite_int.hpp"

using namespace Exiv2::Internal;

// Test that newTiffEntry returns a non-null unique pointer for a valid tag and group
TEST(TiffCompositeTest_414, NewTiffEntryReturnsNonNull_414) {
  auto entry = newTiffEntry(0x0100, IfdId::ifd0Id);
  ASSERT_NE(entry, nullptr);
}

// Test that the returned TiffEntry has the correct tag
TEST(TiffCompositeTest_414, NewTiffEntryHasCorrectTag_414) {
  const uint16_t expectedTag = 0x0110;
  auto entry = newTiffEntry(expectedTag, IfdId::ifd0Id);
  ASSERT_NE(entry, nullptr);
  EXPECT_EQ(entry->tag(), expectedTag);
}

// Test that the returned TiffEntry has the correct group
TEST(TiffCompositeTest_414, NewTiffEntryHasCorrectGroup_414) {
  const IfdId expectedGroup = IfdId::exifId;
  auto entry = newTiffEntry(0x829A, expectedGroup);
  ASSERT_NE(entry, nullptr);
  EXPECT_EQ(entry->group(), expectedGroup);
}

// Test with tag value of 0 (boundary: minimum tag)
TEST(TiffCompositeTest_414, NewTiffEntryWithZeroTag_414) {
  auto entry = newTiffEntry(0x0000, IfdId::ifd0Id);
  ASSERT_NE(entry, nullptr);
  EXPECT_EQ(entry->tag(), 0x0000);
}

// Test with maximum tag value (boundary: maximum uint16_t)
TEST(TiffCompositeTest_414, NewTiffEntryWithMaxTag_414) {
  auto entry = newTiffEntry(0xFFFF, IfdId::ifd0Id);
  ASSERT_NE(entry, nullptr);
  EXPECT_EQ(entry->tag(), 0xFFFF);
}

// Test with different IfdId groups
TEST(TiffCompositeTest_414, NewTiffEntryWithDifferentGroups_414) {
  auto entry1 = newTiffEntry(0x0100, IfdId::ifd0Id);
  auto entry2 = newTiffEntry(0x0100, IfdId::ifd1Id);
  ASSERT_NE(entry1, nullptr);
  ASSERT_NE(entry2, nullptr);
  EXPECT_EQ(entry1->group(), IfdId::ifd0Id);
  EXPECT_EQ(entry2->group(), IfdId::ifd1Id);
}

// Test that two calls return distinct objects
TEST(TiffCompositeTest_414, NewTiffEntryReturnsDistinctObjects_414) {
  auto entry1 = newTiffEntry(0x0100, IfdId::ifd0Id);
  auto entry2 = newTiffEntry(0x0100, IfdId::ifd0Id);
  ASSERT_NE(entry1, nullptr);
  ASSERT_NE(entry2, nullptr);
  EXPECT_NE(entry1.get(), entry2.get());
}

// Test with GPS IFD group
TEST(TiffCompositeTest_414, NewTiffEntryWithGpsGroup_414) {
  auto entry = newTiffEntry(0x0001, IfdId::gpsId);
  ASSERT_NE(entry, nullptr);
  EXPECT_EQ(entry->tag(), 0x0001);
  EXPECT_EQ(entry->group(), IfdId::gpsId);
}

// Test that the returned entry has the correct tag and group combination
TEST(TiffCompositeTest_414, NewTiffEntryTagAndGroupCombination_414) {
  const uint16_t tag = 0x010F;
  const IfdId group = IfdId::ifd0Id;
  auto entry = newTiffEntry(tag, group);
  ASSERT_NE(entry, nullptr);
  EXPECT_EQ(entry->tag(), tag);
  EXPECT_EQ(entry->group(), group);
}

// Test with EXIF IFD and a typical EXIF tag
TEST(TiffCompositeTest_414, NewTiffEntryExifTag_414) {
  // ExposureTime tag in EXIF IFD
  const uint16_t tag = 0x829A;
  auto entry = newTiffEntry(tag, IfdId::exifId);
  ASSERT_NE(entry, nullptr);
  EXPECT_EQ(entry->tag(), tag);
  EXPECT_EQ(entry->group(), IfdId::exifId);
}
