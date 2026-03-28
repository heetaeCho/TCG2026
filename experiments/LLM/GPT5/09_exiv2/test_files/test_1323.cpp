// TEST_ID 1323
// File: test_exiftags_defaultcount_1323.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <string>

#include <exiv2/tags.hpp>

namespace {

class ExifTagsTest_1323 : public ::testing::Test {
 protected:
  Exiv2::ExifTags tags_;  // Works whether ExifTags methods are static or not.
};

TEST_F(ExifTagsTest_1323, DefaultCount_MatchesTagInfoCountFromTagList_1323) {
  // Use tagList() to obtain a TagInfo from the real tag tables, then ensure
  // defaultCount(key) matches TagInfo::count_ for that tag.
  const Exiv2::TagInfo* list = tags_.tagList("Exif.Photo");
  ASSERT_NE(list, nullptr);

  const Exiv2::TagInfo& ti = list[0];

  Exiv2::ExifKey key(ti);

  const uint16_t got = tags_.defaultCount(key);
  const uint16_t expected = static_cast<uint16_t>(ti.count_);

  EXPECT_EQ(got, expected);
}

TEST_F(ExifTagsTest_1323, DefaultCount_UnknownTagInKnownGroup_ReturnsUnknownCount_1323) {
  // Construct a key in a known group but with a tag value that is very likely not present.
  // The implementation falls back to unknownTag.count_ (which is -1), returned as uint16_t.
  const uint16_t kUnknownSentinel = static_cast<uint16_t>(-1);

  Exiv2::ExifKey unknownInKnownGroup(/*tag=*/0xFFFF, /*groupName=*/"Exif.Photo");

  EXPECT_NO_THROW({
    const uint16_t got = tags_.defaultCount(unknownInKnownGroup);
    EXPECT_EQ(got, kUnknownSentinel);
  });
}

TEST_F(ExifTagsTest_1323, DefaultCount_DoesNotThrow_ForValidKeyFromTagList_1323) {
  // Smoke test: a TagInfo-derived key should be accepted and not throw.
  const Exiv2::TagInfo* list = tags_.tagList("Exif.Image");
  ASSERT_NE(list, nullptr);

  Exiv2::ExifKey key(list[0]);

  EXPECT_NO_THROW({
    (void)tags_.defaultCount(key);
  });
}

TEST_F(ExifTagsTest_1323, DefaultCount_DifferentGroups_FirstEntriesProduceTheirOwnCounts_1323) {
  // Boundary/robustness: ensure behavior is consistent across groups by comparing
  // defaultCount(key) against each group's TagInfo::count_ for a TagInfo-derived key.
  const Exiv2::TagInfo* imageList = tags_.tagList("Exif.Image");
  const Exiv2::TagInfo* photoList = tags_.tagList("Exif.Photo");
  ASSERT_NE(imageList, nullptr);
  ASSERT_NE(photoList, nullptr);

  const Exiv2::TagInfo& tiImage = imageList[0];
  const Exiv2::TagInfo& tiPhoto = photoList[0];

  Exiv2::ExifKey keyImage(tiImage);
  Exiv2::ExifKey keyPhoto(tiPhoto);

  const uint16_t gotImage = tags_.defaultCount(keyImage);
  const uint16_t gotPhoto = tags_.defaultCount(keyPhoto);

  EXPECT_EQ(gotImage, static_cast<uint16_t>(tiImage.count_));
  EXPECT_EQ(gotPhoto, static_cast<uint16_t>(tiPhoto.count_));
}

}  // namespace