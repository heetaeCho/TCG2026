// File: test_tags_int_groupname_1371.cpp
#include <gtest/gtest.h>

#include <exiv2/tags.hpp>
#include <exiv2/tags_int.hpp>

namespace {

// The function under test lives in Exiv2::Internal:
//   const char* groupName(IfdId ifdId);
class GroupNameTest_1371 : public ::testing::Test {};

TEST_F(GroupNameTest_1371, ReturnsExpectedGroupNameForKnownIfd0Id_1371) {
  const char* name = Exiv2::Internal::groupName(Exiv2::IfdId::ifd0Id);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Image");
}

TEST_F(GroupNameTest_1371, ReturnsExpectedGroupNameForKnownExifId_1371) {
  const char* name = Exiv2::Internal::groupName(Exiv2::IfdId::exifId);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Photo");
}

TEST_F(GroupNameTest_1371, ReturnsExpectedGroupNameForKnownGpsId_1371) {
  const char* name = Exiv2::Internal::groupName(Exiv2::IfdId::gpsId);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "GPSInfo");
}

TEST_F(GroupNameTest_1371, ReturnsExpectedGroupNameForKnownMnId_1371) {
  const char* name = Exiv2::Internal::groupName(Exiv2::IfdId::mnId);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "MakerNote");
}

TEST_F(GroupNameTest_1371, ReturnsExpectedGroupNameForIfdIdNotSet_1371) {
  const char* name = Exiv2::Internal::groupName(Exiv2::IfdId::ifdIdNotSet);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Unknown");
}

TEST_F(GroupNameTest_1371, ReturnsDefaultGroupNameForUnknownIfdIdNegative_1371) {
  // Boundary / error-ish input: value not expected to exist in the table.
  const auto unknown = static_cast<Exiv2::IfdId>(-1);
  const char* name = Exiv2::Internal::groupName(unknown);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Unknown");
}

TEST_F(GroupNameTest_1371, ReturnsDefaultGroupNameForUnknownIfdIdLarge_1371) {
  // Boundary / error-ish input: value not expected to exist in the table.
  const auto unknown = static_cast<Exiv2::IfdId>(999999);
  const char* name = Exiv2::Internal::groupName(unknown);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Unknown");
}

TEST_F(GroupNameTest_1371, ReturnsExpectedGroupNameForLastIdBoundary_1371) {
  // Boundary condition: last enumerator that is present in the table.
  const char* name = Exiv2::Internal::groupName(Exiv2::IfdId::lastId);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "(Last IFD item)");
}

}  // namespace