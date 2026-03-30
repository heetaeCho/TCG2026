// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_new_omsystem_mn2_1515.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>

#include "makernote_int.hpp"  // Exiv2::Internal::newOMSystemMn2, IfdId

namespace {

// TEST_ID = 1515
class OMSystemMn2FactoryTest_1515 : public ::testing::Test {};

TEST_F(OMSystemMn2FactoryTest_1515, ReturnsNonNullForTypicalInputs_1515) {
  const uint16_t tag = 0x1234;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(1);

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn;
  EXPECT_NO_THROW({ mn = Exiv2::Internal::newOMSystemMn2(tag, group, mnGroup); });
  ASSERT_NE(mn, nullptr);
}

TEST_F(OMSystemMn2FactoryTest_1515, ReturnsNonNullForBoundaryTagValues_1515) {
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(0);

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn0;
  EXPECT_NO_THROW({ mn0 = Exiv2::Internal::newOMSystemMn2(static_cast<uint16_t>(0), group, mnGroup); });
  ASSERT_NE(mn0, nullptr);

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mnMax;
  EXPECT_NO_THROW({ mnMax = Exiv2::Internal::newOMSystemMn2(static_cast<uint16_t>(0xFFFF), group, mnGroup); });
  ASSERT_NE(mnMax, nullptr);
}

TEST_F(OMSystemMn2FactoryTest_1515, ReturnsDistinctObjectsOnMultipleCalls_1515) {
  const uint16_t tag = 0x0001;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(2);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(3);

  auto a = Exiv2::Internal::newOMSystemMn2(tag, group, mnGroup);
  auto b = Exiv2::Internal::newOMSystemMn2(tag, group, mnGroup);

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);
  EXPECT_NE(a.get(), b.get());
}

TEST_F(OMSystemMn2FactoryTest_1515, SupportsMoveSemanticsUniquePtr_1515) {
  const uint16_t tag = 0x00AA;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(0);

  auto original = Exiv2::Internal::newOMSystemMn2(tag, group, mnGroup);
  ASSERT_NE(original, nullptr);

  auto moved = std::move(original);
  EXPECT_EQ(original, nullptr);
  EXPECT_NE(moved, nullptr);
}

TEST_F(OMSystemMn2FactoryTest_1515, NoThrowForVariousGroupValues_1515) {
  const uint16_t tag = 0x0F0F;

  for (int i = 0; i < 5; ++i) {
    const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(i);
    const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(i + 10);

    EXPECT_NO_THROW({
      auto mn = Exiv2::Internal::newOMSystemMn2(tag, group, mnGroup);
      ASSERT_NE(mn, nullptr);
    });
  }
}

}  // namespace