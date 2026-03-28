// =================================================================================================
// TEST_ID: 1509
// File: ./TestProjects/exiv2/src/makernote_int.cpp
//
// Unit tests for:
//   Exiv2::Internal::newIfdMn(uint16_t tag, IfdId group, IfdId mnGroup, const byte*, size_t size, ByteOrder)
//
// Constraints honored:
// - Treat implementation as a black box; assert only observable behavior via public interface.
// - No access to private/internal state.
// - Use gtest; no need for gmock here (no injectable collaborators).
// =================================================================================================

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

// Exiv2 internal headers may vary by project layout. Try the most likely internal header.
#if __has_include("makernote_int.hpp")
#  include "makernote_int.hpp"
#elif __has_include("makernote_int.h")
#  include "makernote_int.h"
#else
// Fallback: include the public exiv2 header if internal header isn't exposed in this build.
// If this fails in your tree, replace with the correct header that declares Exiv2::Internal::newIfdMn.
#  include "exiv2/exiv2.hpp"
#endif

namespace {

class NewIfdMnTest_1509 : public ::testing::Test {};

TEST_F(NewIfdMnTest_1509, ReturnsNullptrWhenSizeIsZero_1509) {
  // Size < 14 => nullptr (observable behavior).
  std::vector<Exiv2::byte> buf;  // empty
  const Exiv2::byte* p = nullptr;

  auto mn = Exiv2::Internal::newIfdMn(
      /*tag=*/0, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      p, /*size=*/0, /*byteOrder=*/Exiv2::littleEndian);

  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewIfdMnTest_1509, ReturnsNullptrWhenSizeIsJustBelowThreshold13_1509) {
  // Boundary: size = 13 (< 14) => nullptr.
  std::vector<Exiv2::byte> buf(13, 0x00);
  const Exiv2::byte* p = buf.data();

  auto mn = Exiv2::Internal::newIfdMn(
      /*tag=*/1, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      p, /*size=*/buf.size(), /*byteOrder=*/Exiv2::bigEndian);

  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewIfdMnTest_1509, ReturnsNonNullptrWhenSizeIsExactlyThreshold14_1509) {
  // Boundary: size = 14 (>= 14) => non-null (observable: unique_ptr not null).
  std::vector<Exiv2::byte> buf(14, 0x00);

  auto mn = Exiv2::Internal::newIfdMn(
      /*tag=*/0x1234, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      buf.data(), /*size=*/buf.size(), /*byteOrder=*/Exiv2::littleEndian);

  EXPECT_NE(mn, nullptr);
}

TEST_F(NewIfdMnTest_1509, ReturnsNonNullptrWhenSizeIsLargerThanThreshold_1509) {
  // Normal: size > 14 => non-null.
  std::vector<Exiv2::byte> buf(64, 0xAB);

  auto mn = Exiv2::Internal::newIfdMn(
      /*tag=*/0x0001, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      buf.data(), /*size=*/buf.size(), /*byteOrder=*/Exiv2::bigEndian);

  EXPECT_NE(mn, nullptr);
}

TEST_F(NewIfdMnTest_1509, SizeBelowThresholdReturnsNullptrEvenWithNonNullDataPointer_1509) {
  // Ensure decision is based on size (observable) regardless of pointer being non-null.
  std::vector<Exiv2::byte> buf(1, 0xFF);

  auto mn = Exiv2::Internal::newIfdMn(
      /*tag=*/0x9999, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      buf.data(), /*size=*/buf.size(), /*byteOrder=*/Exiv2::littleEndian);

  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewIfdMnTest_1509, SizeAtLeastThresholdDoesNotRequireNonNullDataPointer_1509) {
  // Exceptional-ish input: nullptr data pointer with size >= 14.
  // Observable: function should still return non-null based on size gate (no crash expected).
  const Exiv2::byte* p = nullptr;

  auto mn = Exiv2::Internal::newIfdMn(
      /*tag=*/0x0000, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      p, /*size=*/14, /*byteOrder=*/Exiv2::bigEndian);

  EXPECT_NE(mn, nullptr);
}

TEST_F(NewIfdMnTest_1509, ByteOrderDoesNotAffectNullptrOutcomeBelowThreshold_1509) {
  // Below threshold should return nullptr for any ByteOrder.
  std::vector<Exiv2::byte> buf(10, 0x11);

  auto mnLE = Exiv2::Internal::newIfdMn(
      /*tag=*/0x0101, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      buf.data(), /*size=*/buf.size(), /*byteOrder=*/Exiv2::littleEndian);

  auto mnBE = Exiv2::Internal::newIfdMn(
      /*tag=*/0x0101, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      buf.data(), /*size=*/buf.size(), /*byteOrder=*/Exiv2::bigEndian);

  EXPECT_EQ(mnLE, nullptr);
  EXPECT_EQ(mnBE, nullptr);
}

TEST_F(NewIfdMnTest_1509, ByteOrderDoesNotAffectNonNullptrOutcomeAtOrAboveThreshold_1509) {
  // At/above threshold should yield non-null for any ByteOrder (based on observable gate).
  std::vector<Exiv2::byte> buf(14, 0x22);

  auto mnLE = Exiv2::Internal::newIfdMn(
      /*tag=*/0x0202, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      buf.data(), /*size=*/buf.size(), /*byteOrder=*/Exiv2::littleEndian);

  auto mnBE = Exiv2::Internal::newIfdMn(
      /*tag=*/0x0202, /*group=*/static_cast<Exiv2::IfdId>(0), /*mnGroup=*/static_cast<Exiv2::IfdId>(0),
      buf.data(), /*size=*/buf.size(), /*byteOrder=*/Exiv2::bigEndian);

  EXPECT_NE(mnLE, nullptr);
  EXPECT_NE(mnBE, nullptr);
}

}  // namespace