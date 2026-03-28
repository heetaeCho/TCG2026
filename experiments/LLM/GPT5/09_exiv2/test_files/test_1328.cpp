// File: test_exiftags_taglist_1328.cpp
#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

#include <string>

namespace {

class ExifTagsTest_1328 : public ::testing::Test {};

TEST_F(ExifTagsTest_1328, KnownGroupReturnsNonNull_1328) {
  // Normal operation: a well-known Exif group name should resolve to a tag list.
  Exiv2::ExifTags tags;
  const Exiv2::TagInfo* list = tags.tagList("Exif.Image");
  EXPECT_NE(list, nullptr);
}

TEST_F(ExifTagsTest_1328, UnknownGroupReturnsNull_1328) {
  // Error/negative case: an invalid group name should not resolve to a tag list.
  Exiv2::ExifTags tags;
  const Exiv2::TagInfo* list = tags.tagList("This.Group.Does.Not.Exist.1328");
  EXPECT_EQ(list, nullptr);
}

TEST_F(ExifTagsTest_1328, EmptyGroupNameReturnsNull_1328) {
  // Boundary condition: empty group name should not resolve.
  Exiv2::ExifTags tags;
  const Exiv2::TagInfo* list = tags.tagList(std::string{});
  EXPECT_EQ(list, nullptr);
}

TEST_F(ExifTagsTest_1328, VeryLongGroupNameReturnsNull_1328) {
  // Boundary condition: very long group name should be handled gracefully.
  Exiv2::ExifTags tags;
  const std::string longName(10'000, 'A');
  const Exiv2::TagInfo* list = tags.tagList(longName);
  EXPECT_EQ(list, nullptr);
}

TEST_F(ExifTagsTest_1328, RepeatedCallsAreConsistent_1328) {
  // Observable behavior: repeated calls with the same group should be consistent.
  Exiv2::ExifTags tags;
  const Exiv2::TagInfo* first = tags.tagList("Exif.Image");
  const Exiv2::TagInfo* second = tags.tagList("Exif.Image");

  // If the group resolves, the pointer should typically be stable; otherwise both should be null.
  if (first == nullptr) {
    EXPECT_EQ(second, nullptr);
  } else {
    EXPECT_EQ(second, first);
  }
}

}  // namespace