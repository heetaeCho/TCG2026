// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_panasonic_mn_factory_1521.cpp
//
// Unit tests for Exiv2::Internal::newPanasonicMn (makernote_int.cpp)

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <vector>

#include "makernote_int.hpp"  // Exiv2::Internal::newPanasonicMn, PanasonicMnHeader
#include "types.hpp"          // Exiv2::byte, Exiv2::ByteOrder (and related types)

namespace {

using Exiv2::byte;

class PanasonicMnFactoryTest_1521 : public ::testing::Test {};

TEST_F(PanasonicMnFactoryTest_1521, ReturnsNullptrWhenSizeIsZero_1521) {
  const uint16_t tag = 0;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);
  const auto bo = static_cast<Exiv2::ByteOrder>(0);

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn =
      Exiv2::Internal::newPanasonicMn(tag, group, mnGroup, nullptr, 0U, bo);

  EXPECT_EQ(mn, nullptr);
}

TEST_F(PanasonicMnFactoryTest_1521, ReturnsNullptrWhenSizeJustBelowThreshold_1521) {
  const uint16_t tag = 0;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);
  const auto bo = static_cast<Exiv2::ByteOrder>(0);

  const size_t threshold = Exiv2::Internal::PanasonicMnHeader::sizeOfSignature() + 14U;
  ASSERT_GT(threshold, 0U);

  // Provide a valid buffer but keep size below the required minimum.
  std::vector<byte> buf(threshold - 1U, byte{0});

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn =
      Exiv2::Internal::newPanasonicMn(tag, group, mnGroup, buf.data(), buf.size(), bo);

  EXPECT_EQ(mn, nullptr);
}

TEST_F(PanasonicMnFactoryTest_1521, ReturnsNonNullptrWhenSizeAtThreshold_1521) {
  const uint16_t tag = 0;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);
  const auto bo = static_cast<Exiv2::ByteOrder>(0);

  const size_t threshold = Exiv2::Internal::PanasonicMnHeader::sizeOfSignature() + 14U;

  std::vector<byte> buf(threshold, byte{0});

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn =
      Exiv2::Internal::newPanasonicMn(tag, group, mnGroup, buf.data(), buf.size(), bo);

  EXPECT_NE(mn, nullptr);
}

TEST_F(PanasonicMnFactoryTest_1521, ReturnsNonNullptrWhenSizeAboveThreshold_1521) {
  const uint16_t tag = 0;
  const auto group = static_cast<Exiv2::IfdId>(0);
  const auto mnGroup = static_cast<Exiv2::IfdId>(0);
  const auto bo = static_cast<Exiv2::ByteOrder>(0);

  const size_t threshold = Exiv2::Internal::PanasonicMnHeader::sizeOfSignature() + 14U;

  std::vector<byte> buf(threshold + 64U, byte{0});

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> mn =
      Exiv2::Internal::newPanasonicMn(tag, group, mnGroup, buf.data(), buf.size(), bo);

  EXPECT_NE(mn, nullptr);
}

}  // namespace