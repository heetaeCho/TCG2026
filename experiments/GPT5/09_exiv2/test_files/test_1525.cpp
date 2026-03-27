// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <memory>

// Function under test (declaration) and required types.
#include "makernote_int.hpp"

namespace {

using Exiv2::IfdId;

class NewPentaxDngMn2Test_1525 : public ::testing::Test {};

TEST_F(NewPentaxDngMn2Test_1525, ReturnsNonNullForTypicalInputs_1525) {
  const uint16_t tag = 0x1234;
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(1);

  auto mn = Exiv2::Internal::newPentaxDngMn2(tag, group, mnGroup);

  ASSERT_NE(mn, nullptr);
}

TEST_F(NewPentaxDngMn2Test_1525, ReturnsNonNullForZeroTagBoundary_1525) {
  const uint16_t tag = 0;
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  auto mn = Exiv2::Internal::newPentaxDngMn2(tag, group, mnGroup);

  ASSERT_NE(mn, nullptr);
}

TEST_F(NewPentaxDngMn2Test_1525, ReturnsNonNullForMaxTagBoundary_1525) {
  const uint16_t tag = std::numeric_limits<uint16_t>::max();
  const IfdId group = static_cast<IfdId>(0);
  const IfdId mnGroup = static_cast<IfdId>(0);

  auto mn = Exiv2::Internal::newPentaxDngMn2(tag, group, mnGroup);

  ASSERT_NE(mn, nullptr);
}

TEST_F(NewPentaxDngMn2Test_1525, AcceptsArbitraryIfdIdValues_1525) {
  // Black-box: we only verify that construction succeeds and returns an object.
  const uint16_t tag = 0x0001;
  const IfdId group = static_cast<IfdId>(std::numeric_limits<int>::min());
  const IfdId mnGroup = static_cast<IfdId>(std::numeric_limits<int>::max());

  EXPECT_NO_THROW({
    auto mn = Exiv2::Internal::newPentaxDngMn2(tag, group, mnGroup);
    ASSERT_NE(mn, nullptr);
  });
}

TEST_F(NewPentaxDngMn2Test_1525, EachCallReturnsDistinctInstance_1525) {
  const uint16_t tag = 0x00AA;
  const IfdId group = static_cast<IfdId>(2);
  const IfdId mnGroup = static_cast<IfdId>(3);

  auto a = Exiv2::Internal::newPentaxDngMn2(tag, group, mnGroup);
  auto b = Exiv2::Internal::newPentaxDngMn2(tag, group, mnGroup);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a.get(), b.get());
}

TEST_F(NewPentaxDngMn2Test_1525, ReturnedUniquePtrIsMoveable_1525) {
  const uint16_t tag = 0x0F0F;
  const IfdId group = static_cast<IfdId>(4);
  const IfdId mnGroup = static_cast<IfdId>(5);

  auto mn = Exiv2::Internal::newPentaxDngMn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);

  auto moved = std::move(mn);
  EXPECT_EQ(mn, nullptr);
  EXPECT_NE(moved, nullptr);
}

}  // namespace