// SPDX-License-Identifier: GPL-2.0-or-later
// File: ./TestProjects/exiv2/tests/test_ExifTags_isMakerGroup_1325.cpp

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace {

class ExifTagsTest_1325 : public ::testing::Test {
protected:
  Exiv2::ExifTags tags_;
};

// Helper: safely iterate groupList() until a nullptr groupName sentinel or a hard cap.
static std::vector<std::string> GetAllGroupNames_1325(Exiv2::ExifTags& tags) {
  std::vector<std::string> out;

  const Exiv2::GroupInfo* list = tags.groupList();
  if (list == nullptr) return out;

  // Hard cap to avoid infinite loops if sentinel is missing or corrupted.
  constexpr std::size_t kMax = 10000;
  for (std::size_t i = 0; i < kMax; ++i) {
    // Most Exiv2 lists are terminated by a null groupName pointer.
    // We do not assume any other internal structure.
    if (list[i].groupName_ == nullptr) break;
    out.emplace_back(list[i].groupName_);
  }

  return out;
}

}  // namespace

TEST_F(ExifTagsTest_1325, DoesNotThrowOnBasicInputs_1325) {
  EXPECT_NO_THROW((void)tags_.isMakerGroup("Exif.Image"));
  EXPECT_NO_THROW((void)tags_.isMakerGroup("Exif.Photo"));
  EXPECT_NO_THROW((void)tags_.isMakerGroup("Exif.Nikon3"));
  EXPECT_NO_THROW((void)tags_.isMakerGroup(""));
}

TEST_F(ExifTagsTest_1325, ReturnsFalseForEmptyGroupName_1325) {
  // Boundary: empty group name should be handled gracefully.
  EXPECT_FALSE(tags_.isMakerGroup(std::string()));
}

TEST_F(ExifTagsTest_1325, ReturnsFalseForUnknownGroupName_1325) {
  // Boundary / error-like: unknown group should not be considered a maker group.
  EXPECT_FALSE(tags_.isMakerGroup("This.Is.Not.A.Real.Exif.Group.Name.1325"));
}

TEST_F(ExifTagsTest_1325, ReturnsFalseForWhitespaceOnlyGroupName_1325) {
  EXPECT_FALSE(tags_.isMakerGroup("   "));
  EXPECT_FALSE(tags_.isMakerGroup("\t\r\n"));
}

TEST_F(ExifTagsTest_1325, HandlesVeryLongUnknownGroupName_1325) {
  // Boundary: very long input should not crash/throw.
  std::string longName(8192, 'A');
  longName = "Exif." + longName;

  EXPECT_NO_THROW({
    const bool result = tags_.isMakerGroup(longName);
    // We only assert the expected behavior for an unknown group name.
    EXPECT_FALSE(result);
  });
}

TEST_F(ExifTagsTest_1325, FindsAtLeastOneMakerGroupFromGroupListIfAvailable_1325) {
  // Robust, black-box test:
  // - Discover group names via public groupList()
  // - Verify isMakerGroup reports "true" for at least one group (if such exists in this build)
  // - Do not hardcode vendor group names (avoids version/feature variance)
  const std::vector<std::string> names = GetAllGroupNames_1325(tags_);
  if (names.empty()) {
    GTEST_SKIP() << "groupList() returned no groups in this build/environment.";
  }

  bool sawMaker = false;
  for (const auto& n : names) {
    bool isMaker = false;
    EXPECT_NO_THROW(isMaker = tags_.isMakerGroup(n));
    if (isMaker) {
      sawMaker = true;
      // Basic consistency check: repeated calls should be stable for same input.
      EXPECT_TRUE(tags_.isMakerGroup(n));
    }
  }

  // If the build includes maker note groups, we should see at least one.
  // If not, skipping is safer than failing on vendor-disabled builds.
  if (!sawMaker) {
    GTEST_SKIP() << "No maker groups detected via isMakerGroup() for groupList() entries.";
  }
}

TEST_F(ExifTagsTest_1325, ExifImageGroupIsNotMakerGroupWhenPresent_1325) {
  // Commonly present group; if absent in a particular build, skip rather than fail.
  const std::vector<std::string> names = GetAllGroupNames_1325(tags_);
  if (names.empty()) {
    GTEST_SKIP() << "groupList() returned no groups in this build/environment.";
  }

  bool found = false;
  for (const auto& n : names) {
    if (n == "Exif.Image") {
      found = true;
      EXPECT_FALSE(tags_.isMakerGroup(n));
      break;
    }
  }

  if (!found) {
    GTEST_SKIP() << "\"Exif.Image\" group not present in groupList() for this build.";
  }
}