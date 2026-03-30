// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

namespace {

class ExifTagsTest_1327 : public ::testing::Test {};

TEST_F(ExifTagsTest_1327, GroupListReturnsNonNullPointer_1327) {
  Exiv2::ExifTags tags;
  const Exiv2::GroupInfo* groups = tags.groupList();
  ASSERT_NE(groups, nullptr);
}

TEST_F(ExifTagsTest_1327, GroupListIsStableAcrossRepeatedCalls_1327) {
  Exiv2::ExifTags tags;

  const Exiv2::GroupInfo* p1 = tags.groupList();
  const Exiv2::GroupInfo* p2 = tags.groupList();
  const Exiv2::GroupInfo* p3 = tags.groupList();

  ASSERT_NE(p1, nullptr);
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

TEST_F(ExifTagsTest_1327, GroupListIsConsistentAcrossInstances_1327) {
  Exiv2::ExifTags tagsA;
  Exiv2::ExifTags tagsB;

  const Exiv2::GroupInfo* pA = tagsA.groupList();
  const Exiv2::GroupInfo* pB = tagsB.groupList();

  ASSERT_NE(pA, nullptr);
  ASSERT_NE(pB, nullptr);
  EXPECT_EQ(pA, pB);
}

}  // namespace