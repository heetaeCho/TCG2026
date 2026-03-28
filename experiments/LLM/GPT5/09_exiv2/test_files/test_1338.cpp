// File: test_exifkey_groupname_1338.cpp
// TEST_ID: 1338

#include <gtest/gtest.h>

#include <string>

#include <exiv2/tags.hpp>

namespace {

// Fixture kept minimal: we only test observable behavior via public API.
class ExifKeyTest_1338 : public ::testing::Test {};

TEST_F(ExifKeyTest_1338, GroupNameReturnsValuePassedToCtor_1338) {
  const std::string groupName = "Exif.Photo";
  Exiv2::ExifKey key(/*tag=*/0x010F, groupName);

  EXPECT_EQ(key.groupName(), groupName);
}

TEST_F(ExifKeyTest_1338, GroupNameAllowsEmptyString_1338) {
  const std::string groupName;
  Exiv2::ExifKey key(/*tag=*/0x0001, groupName);

  EXPECT_EQ(key.groupName(), groupName);
}

TEST_F(ExifKeyTest_1338, GroupNameHandlesNonAsciiAndPunctuation_1338) {
  const std::string groupName = "그룹-名/Exif.Photo_1.0";
  Exiv2::ExifKey key(/*tag=*/0x0002, groupName);

  EXPECT_EQ(key.groupName(), groupName);
}

TEST_F(ExifKeyTest_1338, GroupNameHandlesVeryLongString_1338) {
  const std::string groupName(4096, 'A');  // boundary-ish: large but reasonable
  Exiv2::ExifKey key(/*tag=*/0x0003, groupName);

  EXPECT_EQ(key.groupName(), groupName);
  EXPECT_EQ(key.groupName().size(), groupName.size());
}

TEST_F(ExifKeyTest_1338, CopyConstructorPreservesGroupName_1338) {
  const std::string groupName = "Exif.Image";
  Exiv2::ExifKey original(/*tag=*/0x0132, groupName);

  Exiv2::ExifKey copy(original);

  EXPECT_EQ(copy.groupName(), original.groupName());
  EXPECT_EQ(copy.groupName(), groupName);
}

TEST_F(ExifKeyTest_1338, CopyAssignmentPreservesGroupName_1338) {
  Exiv2::ExifKey lhs(/*tag=*/0x0004, "Left.Group");
  Exiv2::ExifKey rhs(/*tag=*/0x0005, "Right.Group");

  lhs = rhs;

  EXPECT_EQ(lhs.groupName(), rhs.groupName());
  EXPECT_EQ(lhs.groupName(), "Right.Group");
}

TEST_F(ExifKeyTest_1338, GroupNameCallableOnOtherConstructors_1338) {
  // We do not assume any particular groupName derivation for these constructors.
  // The test only verifies the call is observable (returns a std::string) and
  // does not crash/throw in typical usage.
  Exiv2::ExifKey fromKeyString(std::string("Exif.Photo.DateTimeOriginal"));
  (void)fromKeyString.groupName();

  // Also verify the call is safe on a copied instance from that path.
  Exiv2::ExifKey copied(fromKeyString);
  (void)copied.groupName();

  SUCCEED();
}

}  // namespace