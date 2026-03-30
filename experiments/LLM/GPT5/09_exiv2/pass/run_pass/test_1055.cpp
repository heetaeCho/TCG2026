// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1055
//
// Unit tests for Exiv2::Image::isPrintXMP(uint16_t, Exiv2::PrintStructureOption)
//
// Constraints honored:
// - Treat implementation as black box: only verify observable return values.
// - No private state access.
// - No mocks needed: pure function behavior.

#include <gtest/gtest.h>

#include <cstdint>

// Include the public interface. Adjust include path if your test setup differs.
#include "exiv2/image.hpp"

namespace {

// Keep the fixture name aligned with your project’s convention.
class ImageIsPrintXmpTest_1055 : public ::testing::Test {};

}  // namespace

TEST_F(ImageIsPrintXmpTest_1055, ReturnsTrueOnlyForType700AndOptionKpsXmp_1055) {
  // "Normal operation" positive case (the only observable true combination).
  EXPECT_TRUE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(700), Exiv2::kpsXMP));
}

TEST_F(ImageIsPrintXmpTest_1055, ReturnsFalseForDifferentTypeWithKpsXmp_1055) {
  // Boundary-ish checks around the accepted type (699/701), plus a few typical tag-like values.
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(699), Exiv2::kpsXMP));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(701), Exiv2::kpsXMP));

  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(0), Exiv2::kpsXMP));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(1), Exiv2::kpsXMP));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(65535), Exiv2::kpsXMP));
}

TEST_F(ImageIsPrintXmpTest_1055, ReturnsFalseForType700WithNonXmpOptions_1055) {
  // Verify all other known PrintStructureOption values do not trigger XMP printing.
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(700), Exiv2::kpsNone));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(700), Exiv2::kpsBasic));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(700), Exiv2::kpsRecursive));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(700), Exiv2::kpsIccProfile));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(700), Exiv2::kpsIptcErase));
}

TEST_F(ImageIsPrintXmpTest_1055, ReturnsFalseForNon700AndNonXmpCombinations_1055) {
  // Cross-check representative combinations (normal + boundary inputs).
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(699), Exiv2::kpsNone));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(699), Exiv2::kpsBasic));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(701), Exiv2::kpsRecursive));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(0), Exiv2::kpsIccProfile));
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(65535), Exiv2::kpsIptcErase));
}

TEST_F(ImageIsPrintXmpTest_1055, ReturnsFalseForOutOfRangeOptionValueEvenWithType700_1055) {
  // "Exceptional/error case (if observable)": pass an invalid enum value.
  // This is still valid C++ via cast; we only assert the observable return value.
  const auto invalidOption = static_cast<Exiv2::PrintStructureOption>(-1);
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(700), invalidOption));

  const auto largeInvalidOption = static_cast<Exiv2::PrintStructureOption>(9999);
  EXPECT_FALSE(Exiv2::Image::isPrintXMP(static_cast<uint16_t>(700), largeInvalidOption));
}