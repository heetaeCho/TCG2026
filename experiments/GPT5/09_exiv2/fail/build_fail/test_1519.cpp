// SPDX-License-Identifier: GPL-2.0-or-later
#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <vector>

#include "makernote_int.hpp"

namespace {

class Nikon2Mn2FactoryTest_1519 : public ::testing::Test {};

TEST_F(Nikon2Mn2FactoryTest_1519, ReturnsNonNullForTypicalInputs_1519) {
  const uint16_t tag = 0x0001;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(1);

  auto mn = Exiv2::Internal::newNikon2Mn2(tag, group, mnGroup);
  ASSERT_NE(mn, nullptr);
}

TEST_F(Nikon2Mn2FactoryTest_1519, ReturnsNonNullForBoundaryTags_1519) {
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);

  auto mn0 = Exiv2::Internal::newNikon2Mn2(static_cast<uint16_t>(0), group, mnGroup);
  ASSERT_NE(mn0, nullptr);

  auto mnMax = Exiv2::Internal::newNikon2Mn2(static_cast<uint16_t>(0xFFFF), group, mnGroup);
  ASSERT_NE(mnMax, nullptr);
}

TEST_F(Nikon2Mn2FactoryTest_1519, DoesNotThrowForVariousGroupValues_1519) {
  const uint16_t tag = 0x1234;
  const std::vector<Exiv2::IfdId> groups = {
      static_cast<Exiv2::IfdId>(0),
      static_cast<Exiv2::IfdId>(1),
      static_cast<Exiv2::IfdId>(2),
      static_cast<Exiv2::IfdId>(255),
  };

  for (const auto g : groups) {
    EXPECT_NO_THROW({
      auto mn = Exiv2::Internal::newNikon2Mn2(tag, g, g);
      ASSERT_NE(mn, nullptr);
    });
  }
}

TEST_F(Nikon2Mn2FactoryTest_1519, UniquePtrIsMovableAndNullsSource_1519) {
  auto mn = Exiv2::Internal::newNikon2Mn2(static_cast<uint16_t>(0x0002),
                                          static_cast<Exiv2::IfdId>(0),
                                          static_cast<Exiv2::IfdId>(1));
  ASSERT_NE(mn, nullptr);

  auto moved = std::move(mn);
  EXPECT_EQ(mn, nullptr);
  EXPECT_NE(moved, nullptr);
}

TEST_F(Nikon2Mn2FactoryTest_1519, CanResetReturnedUniquePtr_1519) {
  auto mn = Exiv2::Internal::newNikon2Mn2(static_cast<uint16_t>(0x0003),
                                          static_cast<Exiv2::IfdId>(0),
                                          static_cast<Exiv2::IfdId>(0));
  ASSERT_NE(mn, nullptr);

  mn.reset();
  EXPECT_EQ(mn, nullptr);
}

TEST_F(Nikon2Mn2FactoryTest_1519, RepeatedCallsReturnDistinctObjects_1519) {
  auto a = Exiv2::Internal::newNikon2Mn2(static_cast<uint16_t>(0x0100),
                                         static_cast<Exiv2::IfdId>(0),
                                         static_cast<Exiv2::IfdId>(0));
  auto b = Exiv2::Internal::newNikon2Mn2(static_cast<uint16_t>(0x0100),
                                         static_cast<Exiv2::IfdId>(0),
                                         static_cast<Exiv2::IfdId>(0));

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a.get(), b.get());
}

}  // namespace