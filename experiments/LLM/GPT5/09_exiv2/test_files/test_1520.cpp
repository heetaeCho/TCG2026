// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_newNikon3Mn2_1520.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <type_traits>

#include "makernote_int.hpp"  // Exiv2::Internal::newNikon3Mn2

namespace {

using Exiv2::Internal::newNikon3Mn2;

class Nikon3Mn2FactoryTest_1520 : public ::testing::Test {};

TEST_F(Nikon3Mn2FactoryTest_1520, ReturnsNonNullUniquePtr_1520) {
  const uint16_t tag = 0;
  const auto group   = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  auto mn = newNikon3Mn2(tag, group, mnGroup);
  EXPECT_NE(mn, nullptr);
}

TEST_F(Nikon3Mn2FactoryTest_1520, HandlesBoundaryTagValues_1520) {
  const auto group   = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  auto mn_min = newNikon3Mn2(static_cast<uint16_t>(0), group, mnGroup);
  EXPECT_NE(mn_min, nullptr);

  auto mn_max = newNikon3Mn2(static_cast<uint16_t>(0xFFFF), group, mnGroup);
  EXPECT_NE(mn_max, nullptr);
}

TEST_F(Nikon3Mn2FactoryTest_1520, AcceptsArbitraryIfdIdValues_1520) {
  const uint16_t tag = 0x1234;

  // Use a couple of distinct underlying values without assuming any specific enum members exist.
  const auto group_a   = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup_a = static_cast<Exiv2::IfdId>(1);

  const auto group_b   = static_cast<Exiv2::IfdId>(-1);
  const auto mnGroup_b = static_cast<Exiv2::IfdId>(42);

  auto mn_a = newNikon3Mn2(tag, group_a, mnGroup_a);
  EXPECT_NE(mn_a, nullptr);

  auto mn_b = newNikon3Mn2(tag, group_b, mnGroup_b);
  EXPECT_NE(mn_b, nullptr);
}

TEST_F(Nikon3Mn2FactoryTest_1520, ReturnedUniquePtrIsMovableAndTransfersOwnership_1520) {
  const uint16_t tag = 1;
  const auto group   = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  auto mn = newNikon3Mn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);

  auto moved = std::move(mn);
  EXPECT_EQ(mn, nullptr);
  EXPECT_NE(moved, nullptr);
}

TEST_F(Nikon3Mn2FactoryTest_1520, MultipleCallsReturnDistinctObjects_1520) {
  const uint16_t tag = 2;
  const auto group   = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  auto mn1 = newNikon3Mn2(tag, group, mnGroup);
  auto mn2 = newNikon3Mn2(tag, group, mnGroup);

  ASSERT_NE(mn1, nullptr);
  ASSERT_NE(mn2, nullptr);
  EXPECT_NE(mn1.get(), mn2.get());
}

// A lightweight compile-time check: the factory returns a std::unique_ptr of something.
TEST_F(Nikon3Mn2FactoryTest_1520, ReturnTypeIsUniquePtr_1520) {
  const uint16_t tag = 3;
  const auto group   = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  using RetT = decltype(newNikon3Mn2(tag, group, mnGroup));
  EXPECT_TRUE((std::is_same_v<RetT, std::unique_ptr<Exiv2::Internal::TiffIfdMakernote>>));
}

}  // namespace