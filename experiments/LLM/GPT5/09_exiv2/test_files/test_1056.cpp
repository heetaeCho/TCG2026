// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1056
//
// Unit tests for Exiv2::Image::isPrintICC(uint16_t, Exiv2::PrintStructureOption)
//
// Constraints observed:
// - Treat implementation as black box (assert only observable return values)
// - No private state access
// - No re-implementation beyond calling the public/static interface

#include <gtest/gtest.h>

#include <cstdint>

#include "exiv2/image.hpp"

namespace {

// Minimal fixture (no construction of Image instances required since isPrintICC is static in the interface)
class ImageIsPrintIccTest_1056 : public ::testing::Test {};

}  // namespace

TEST_F(ImageIsPrintIccTest_1056, ReturnsTrueForIccTagAndIccOption_1056) {
  // Observable behavior (from interface usage): should return true for ICC profile tag + ICC option.
  const uint16_t type = 0x8773;
  const Exiv2::PrintStructureOption option = Exiv2::kpsIccProfile;

  EXPECT_TRUE(Exiv2::Image::isPrintICC(type, option));
}

TEST_F(ImageIsPrintIccTest_1056, ReturnsFalseWhenTypeMatchesButOptionDifferent_1056) {
  const uint16_t type = 0x8773;

  EXPECT_FALSE(Exiv2::Image::isPrintICC(type, Exiv2::kpsNone));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(type, Exiv2::kpsBasic));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(type, Exiv2::kpsXMP));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(type, Exiv2::kpsRecursive));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(type, Exiv2::kpsIptcErase));
}

TEST_F(ImageIsPrintIccTest_1056, ReturnsFalseWhenOptionMatchesButTypeDifferent_1056) {
  const Exiv2::PrintStructureOption option = Exiv2::kpsIccProfile;

  // Boundary-ish values and common nearby values
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x0000), option));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x0001), option));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x8772), option));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x8774), option));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0xFFFF), option));
}

TEST_F(ImageIsPrintIccTest_1056, ReturnsFalseWhenBothTypeAndOptionDoNotMatch_1056) {
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x0000), Exiv2::kpsNone));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0xFFFF), Exiv2::kpsBasic));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x1234), Exiv2::kpsXMP));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x8774), Exiv2::kpsRecursive));
}

TEST_F(ImageIsPrintIccTest_1056, HandlesOptionCastedOutOfEnumRangeGracefully_1056) {
  // Error/edge case: option value outside known enum constants.
  // Observable expectation: should not crash; should return false unless it coincidentally matches required value.
  const uint16_t type = 0x8773;

  const auto invalidLow = static_cast<Exiv2::PrintStructureOption>(-1);
  const auto invalidHigh = static_cast<Exiv2::PrintStructureOption>(999);

  EXPECT_FALSE(Exiv2::Image::isPrintICC(type, invalidLow));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(type, invalidHigh));
}

TEST_F(ImageIsPrintIccTest_1056, BoundaryTypesAroundIccTagWithCorrectOption_1056) {
  // Boundary conditions around the specific tag constant
  const Exiv2::PrintStructureOption option = Exiv2::kpsIccProfile;

  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x8773 - 1), option));
  EXPECT_TRUE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x8773), option));
  EXPECT_FALSE(Exiv2::Image::isPrintICC(static_cast<uint16_t>(0x8773 + 1), option));
}