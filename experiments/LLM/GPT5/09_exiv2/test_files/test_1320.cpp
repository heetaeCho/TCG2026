// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_groupinfo_operator_eq_ifdid_1320.cpp
//
// Unit tests for Exiv2::GroupInfo::operator==(IfdId) const
//
// Constraints note:
// - Treat implementation as a black box.
// - Only test observable behavior via public interface.

#include <gtest/gtest.h>

#include <exiv2/tags.hpp>

namespace {

class GroupInfoTest_1320 : public ::testing::Test {};

TEST_F(GroupInfoTest_1320, ReturnsTrueWhenIfdIdMatches_1320) {
  Exiv2::GroupInfo gi{};
  // Use a value-initialized IfdId to avoid assuming any particular enumerator exists.
  Exiv2::IfdId id = static_cast<Exiv2::IfdId>(0);

  gi.ifdId_ = id;

  EXPECT_TRUE(gi == id);
}

TEST_F(GroupInfoTest_1320, ReturnsFalseWhenIfdIdDoesNotMatch_1320) {
  Exiv2::GroupInfo gi{};
  const Exiv2::IfdId id1 = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId id2 = static_cast<Exiv2::IfdId>(1);

  gi.ifdId_ = id1;

  EXPECT_FALSE(gi == id2);
}

TEST_F(GroupInfoTest_1320, BoundaryLargeUnderlyingValueMatches_1320) {
  Exiv2::GroupInfo gi{};

  // Boundary-style check using a "large" value; avoids relying on real enum members.
  const Exiv2::IfdId big = static_cast<Exiv2::IfdId>(0x7fffffff);

  gi.ifdId_ = big;

  EXPECT_TRUE(gi == big);
}

TEST_F(GroupInfoTest_1320, BoundaryLargeUnderlyingValueDoesNotMatch_1320) {
  Exiv2::GroupInfo gi{};

  const Exiv2::IfdId big = static_cast<Exiv2::IfdId>(0x7fffffff);
  const Exiv2::IfdId other = static_cast<Exiv2::IfdId>(0x7ffffffe);

  gi.ifdId_ = big;

  EXPECT_FALSE(gi == other);
}

TEST_F(GroupInfoTest_1320, WorksWithConstObject_1320) {
  Exiv2::GroupInfo gi{};
  const Exiv2::IfdId id = static_cast<Exiv2::IfdId>(42);
  gi.ifdId_ = id;

  const Exiv2::GroupInfo& cgi = gi;

  EXPECT_TRUE(cgi == id);
}

}  // namespace