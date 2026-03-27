// File: test_tags_int_taglist_1426.cpp
#include <gtest/gtest.h>

#include <exiv2/tags.hpp>   // TagInfo
#include <string>

namespace Exiv2 {
namespace Internal {
// Forward declaration (implementation is in src/tags_int.cpp)
const TagInfo* tagList(const std::string& groupName);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class TagListTest_1426 : public ::testing::Test {};

TEST_F(TagListTest_1426, ReturnsNullptrForUnknownGroupName_1426) {
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList("ThisGroupDoesNotExist");
  EXPECT_EQ(nullptr, list);
}

TEST_F(TagListTest_1426, ReturnsNullptrForEmptyGroupName_1426) {
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList(std::string{});
  EXPECT_EQ(nullptr, list);
}

TEST_F(TagListTest_1426, ReturnsNullptrWhenGroupHasNoTagListFunction_1426) {
  // "Unknown" is present in groupInfo with nullptr tagList_ (per provided snippet).
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList("Unknown");
  EXPECT_EQ(nullptr, list);
}

TEST_F(TagListTest_1426, ReturnsNonNullptrForKnownIfdGroup_Image_1426) {
  // "Image" is present in groupInfo with a non-null tagList_ (per provided snippet).
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList("Image");
  EXPECT_NE(nullptr, list);
}

TEST_F(TagListTest_1426, ReturnsNonNullptrForKnownExifGroup_Photo_1426) {
  // "Photo" is present in groupInfo with a non-null tagList_ (per provided snippet).
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList("Photo");
  EXPECT_NE(nullptr, list);
}

TEST_F(TagListTest_1426, ReturnsNonNullptrForKnownGpsGroup_GPSInfo_1426) {
  // "GPSInfo" is present in groupInfo with a non-null tagList_ (per provided snippet).
  const Exiv2::TagInfo* list = Exiv2::Internal::tagList("GPSInfo");
  EXPECT_NE(nullptr, list);
}

TEST_F(TagListTest_1426, RepeatedCallsForSameKnownGroupReturnSamePointer_1426) {
  const Exiv2::TagInfo* list1 = Exiv2::Internal::tagList("Photo");
  const Exiv2::TagInfo* list2 = Exiv2::Internal::tagList("Photo");
  ASSERT_NE(nullptr, list1);
  ASSERT_NE(nullptr, list2);
  EXPECT_EQ(list1, list2);
}

TEST_F(TagListTest_1426, RepeatedCallsForUnknownGroupReturnNullptr_1426) {
  const Exiv2::TagInfo* list1 = Exiv2::Internal::tagList("DefinitelyNotARealGroup");
  const Exiv2::TagInfo* list2 = Exiv2::Internal::tagList("DefinitelyNotARealGroup");
  EXPECT_EQ(nullptr, list1);
  EXPECT_EQ(nullptr, list2);
}

}  // namespace