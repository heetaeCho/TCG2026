// File: test_tags_groupinfo_operator_eq_1321.cpp
// TEST_ID: 1321

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

#include <string>

namespace {

class GroupInfoTest_1321 : public ::testing::Test {
 protected:
  static Exiv2::GroupInfo MakeGroupInfo(const char* groupName) {
    Exiv2::GroupInfo gi{};
    gi.groupName_ = groupName;
    return gi;
  }
};

TEST_F(GroupInfoTest_1321, ReturnsTrueWhenGroupNameMatches_1321) {
  Exiv2::GroupInfo gi = MakeGroupInfo("Exif.Image");

  const Exiv2::GroupName same("Exif.Image");
  EXPECT_TRUE(gi == same);
}

TEST_F(GroupInfoTest_1321, ReturnsFalseWhenGroupNameDoesNotMatch_1321) {
  Exiv2::GroupInfo gi = MakeGroupInfo("Exif.Image");

  const Exiv2::GroupName different("Exif.Photo");
  EXPECT_FALSE(gi == different);
}

TEST_F(GroupInfoTest_1321, EmptyStringMatchesEmptyGroupName_1321) {
  Exiv2::GroupInfo gi = MakeGroupInfo("");

  const Exiv2::GroupName empty("");
  EXPECT_TRUE(gi == empty);
}

TEST_F(GroupInfoTest_1321, CaseSensitivityMismatchReturnsFalse_1321) {
  Exiv2::GroupInfo gi = MakeGroupInfo("Exif.Image");

  const Exiv2::GroupName differentCase("exif.image");
  EXPECT_FALSE(gi == differentCase);
}

TEST_F(GroupInfoTest_1321, WorksWithLongGroupNames_1321) {
  const std::string longName(512, 'A');  // boundary-ish: larger-than-typical input
  Exiv2::GroupInfo gi = MakeGroupInfo(longName.c_str());

  const Exiv2::GroupName same(longName);
  const Exiv2::GroupName different(longName + "X");

  EXPECT_TRUE(gi == same);
  EXPECT_FALSE(gi == different);
}

TEST_F(GroupInfoTest_1321, DoesNotModifyInputGroupName_1321) {
  Exiv2::GroupInfo gi = MakeGroupInfo("Xmp.xmp");

  Exiv2::GroupName input("Xmp.xmp");
  const Exiv2::GroupName before = input;

  (void)(gi == input);

  EXPECT_EQ(input, before);
}

}  // namespace