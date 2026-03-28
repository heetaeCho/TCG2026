// File: test_tags_int_groupid_1369.cpp
// Unit tests for Exiv2::Internal::groupId(const std::string&)
// TEST_ID: 1369

#include <gtest/gtest.h>

#include <string>

// The function under test lives in Exiv2::Internal.
// In the Exiv2 codebase this is typically declared from an internal header.
// Include the most likely header(s) that declare Internal::groupId.
#include <exiv2/tags.hpp>

// Some builds expose Internal declarations via an internal header.
// If your build fails to find groupId with only <exiv2/tags.hpp>, include the
// appropriate internal header from your tree (e.g. "tags_int.hpp").
// #include "tags_int.hpp"

namespace {

// If the declaration is not visible via <exiv2/tags.hpp> in your build,
// you can uncomment this forward declaration (it does not re-implement logic).
// namespace Exiv2 { namespace Internal { Exiv2::IfdId groupId(const std::string& groupName); } }

class GroupIdTest_1369 : public ::testing::Test {};

}  // namespace

TEST_F(GroupIdTest_1369, ReturnsExpectedIfdId_ForKnownGroup_Image_1369) {
  // "Image" is listed in groupInfo with IfdId::ifd0Id in the provided snippet.
  EXPECT_EQ(Exiv2::Internal::groupId("Image"), Exiv2::IfdId::ifd0Id);
}

TEST_F(GroupIdTest_1369, ReturnsExpectedIfdId_ForKnownGroup_Thumbnail_1369) {
  // "Thumbnail" is listed in groupInfo with IfdId::ifd1Id in the provided snippet.
  EXPECT_EQ(Exiv2::Internal::groupId("Thumbnail"), Exiv2::IfdId::ifd1Id);
}

TEST_F(GroupIdTest_1369, ReturnsExpectedIfdId_ForKnownGroup_Photo_1369) {
  // "Photo" is listed in groupInfo with IfdId::exifId in the provided snippet.
  EXPECT_EQ(Exiv2::Internal::groupId("Photo"), Exiv2::IfdId::exifId);
}

TEST_F(GroupIdTest_1369, ReturnsExpectedIfdId_ForKnownGroup_GPSInfo_1369) {
  // "GPSInfo" is listed in groupInfo with IfdId::gpsId in the provided snippet.
  EXPECT_EQ(Exiv2::Internal::groupId("GPSInfo"), Exiv2::IfdId::gpsId);
}

TEST_F(GroupIdTest_1369, ReturnsExpectedIfdId_ForKnownGroup_MakerNote_1369) {
  // "MakerNote" is listed in groupInfo with IfdId::mnId in the provided snippet.
  EXPECT_EQ(Exiv2::Internal::groupId("MakerNote"), Exiv2::IfdId::mnId);
}

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSet_ForUnknownGroup_1369) {
  EXPECT_EQ(Exiv2::Internal::groupId("ThisGroupDoesNotExist"),
            Exiv2::IfdId::ifdIdNotSet);
}

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSet_ForEmptyString_1369) {
  EXPECT_EQ(Exiv2::Internal::groupId(std::string{}), Exiv2::IfdId::ifdIdNotSet);
}

TEST_F(GroupIdTest_1369, ReturnsIfdIdNotSet_ForSimilarButDifferentString_1369) {
  // Boundary-ish case: visually similar but not an exact known group name.
  // We avoid assuming case-insensitivity and only check an obviously different value.
  EXPECT_EQ(Exiv2::Internal::groupId("Image "), Exiv2::IfdId::ifdIdNotSet);
}

TEST_F(GroupIdTest_1369, DoesNotThrow_AndReturnsNotSet_ForVeryLongGroupName_1369) {
  std::string longName(4096, 'A');
  Exiv2::IfdId result = Exiv2::IfdId::ifdIdNotSet;

  EXPECT_NO_THROW({ result = Exiv2::Internal::groupId(longName); });
  EXPECT_EQ(result, Exiv2::IfdId::ifdIdNotSet);
}

TEST_F(GroupIdTest_1369, IsDeterministic_ForRepeatedCalls_1369) {
  const auto a1 = Exiv2::Internal::groupId("Photo");
  const auto a2 = Exiv2::Internal::groupId("Photo");
  EXPECT_EQ(a1, a2);

  const auto b1 = Exiv2::Internal::groupId("NoSuchGroup");
  const auto b2 = Exiv2::Internal::groupId("NoSuchGroup");
  EXPECT_EQ(b1, b2);
}