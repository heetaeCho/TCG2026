// File: test_makernote_int_tiffmncreator_1431.cpp
#include <gtest/gtest.h>

#include "makernote_int.hpp"

#include <array>
#include <cstdint>
#include <string_view>
#include <utility>
#include <vector>

namespace {

class TiffMnCreatorTest_1431 : public ::testing::Test {
 protected:
  static constexpr uint16_t kTag = 0x0001;

  // Use a common IFD group that should be valid for calls; behavior is treated as black-box.
  static constexpr Exiv2::IfdId kGroup = Exiv2::ifd0Id;

  static constexpr Exiv2::ByteOrder kByteOrder = Exiv2::littleEndian;

  std::array<Exiv2::byte, 8> buf_{{0, 1, 2, 3, 4, 5, 6, 7}};
};

TEST_F(TiffMnCreatorTest_1431, UnknownMakeReturnsNullptr_1431) {
  const std::string_view make = "__definitely_not_a_real_camera_make__1431__";
  auto mn = Exiv2::Internal::TiffMnCreator::create(kTag, kGroup, make, buf_.data(), buf_.size(), kByteOrder);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(TiffMnCreatorTest_1431, EmptyMakeReturnsNullptr_1431) {
  const std::string_view make = "";
  auto mn = Exiv2::Internal::TiffMnCreator::create(kTag, kGroup, make, buf_.data(), buf_.size(), kByteOrder);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(TiffMnCreatorTest_1431, WhitespaceOnlyMakeReturnsNullptr_1431) {
  const std::string_view make = "   ";
  auto mn = Exiv2::Internal::TiffMnCreator::create(kTag, kGroup, make, buf_.data(), buf_.size(), kByteOrder);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(TiffMnCreatorTest_1431, NullDataWithZeroSizeDoesNotCrashAndReturnsNullForUnknownMake_1431) {
  const std::string_view make = "__unknown_make__1431__";
  auto mn = Exiv2::Internal::TiffMnCreator::create(kTag, kGroup, make, /*pData=*/nullptr, /*size=*/0, kByteOrder);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(TiffMnCreatorTest_1431, ReturnsNonNullForAtLeastOneCommonMakeOrNullForAll_1431) {
  // This test is written to be resilient to exact make-string matching in the registry:
  // it tries several common makes and asserts that at least one produces a makernote,
  // which is expected for typical Exiv2 builds. If none match, the failure highlights
  // a registry/matching change.
  const std::vector<std::string_view> candidates = {
      "Nikon", "NIKON", "NIKON CORPORATION",
      "Canon", "CANON", "Canon Inc.",
      "SONY", "Sony", "Sony Corporation",
      "FUJIFILM", "Fujifilm", "FUJIFILM Corporation",
      "OLYMPUS", "Olympus",
      "Panasonic", "PANASONIC",
      "PENTAX", "Pentax",
      "KODAK", "Kodak",
  };

  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> found;
  std::string_view found_make;

  for (auto make : candidates) {
    auto mn = Exiv2::Internal::TiffMnCreator::create(kTag, kGroup, make, buf_.data(), buf_.size(), kByteOrder);
    if (mn != nullptr) {
      found = std::move(mn);
      found_make = make;
      break;
    }
  }

  ASSERT_NE(found, nullptr) << "No candidate make matched the makernote registry.";
  EXPECT_FALSE(found_make.empty());

  // Basic ownership / lifecycle sanity: releasing and resetting should be safe.
  found.reset();
  EXPECT_EQ(found, nullptr);
}

TEST_F(TiffMnCreatorTest_1431, UnknownMakeRemainsNullEvenWithDifferentTagAndByteOrder_1431) {
  const std::string_view make = "__unknown_make__1431__";

  auto mn1 = Exiv2::Internal::TiffMnCreator::create(/*tag=*/0x0000, kGroup, make, buf_.data(), buf_.size(), Exiv2::littleEndian);
  auto mn2 = Exiv2::Internal::TiffMnCreator::create(/*tag=*/0xFFFF, kGroup, make, buf_.data(), buf_.size(), Exiv2::bigEndian);

  EXPECT_EQ(mn1, nullptr);
  EXPECT_EQ(mn2, nullptr);
}

}  // namespace