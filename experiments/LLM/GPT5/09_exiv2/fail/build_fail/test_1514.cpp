// -------------------------------------------------------------------------------------------------
// UNIT TESTS for Exiv2::Internal::newOMSystemMn (makernote_int.cpp)
// TEST_ID: 1514
//
// Constraints honored:
// - Black-box: tests only observable behavior from the interface (return value/nullness).
// - No private/internal state access.
// - No inference of internal logic beyond what is directly observable in the provided snippet.
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

// Exiv2 internal headers (adjust include paths if your build uses different layout)
#include "makernote_int.hpp"   // newOMSystemMn, TiffIfdMakernote
#include "tiffimage_int.hpp"   // IfdId (or wherever IfdId/ByteOrder are defined in your tree)
#include "types.hpp"           // Exiv2::byte, ByteOrder (if not in tiff headers)

namespace {

using Exiv2::byte;
using Exiv2::ByteOrder;
using Exiv2::Internal::newOMSystemMn;

// Helper: choose a ByteOrder value without assuming which one matters for behavior here.
// We only need a valid enum value to compile and call the function.
constexpr ByteOrder kAnyByteOrder = Exiv2::littleEndian;

class OMSystemMnTest_1514 : public ::testing::Test {
 protected:
  // Provide stable, arbitrary IDs for parameters. We don't assert anything about them.
  static constexpr uint16_t kTag = 0x1234;
  static constexpr Exiv2::IfdId kGroup = Exiv2::IfdId::ifd0Id;
  static constexpr Exiv2::IfdId kMnGroup = Exiv2::IfdId::ifd0Id;

  static const byte* ptrOrNull(const std::vector<byte>& v) {
    return v.empty() ? nullptr : v.data();
  }
};

}  // namespace

TEST_F(OMSystemMnTest_1514, ReturnsNullptrWhenSizeIsZero_1514) {
  std::vector<byte> buf;  // empty
  auto mn = newOMSystemMn(kTag, kGroup, kMnGroup, ptrOrNull(buf), /*size=*/0, kAnyByteOrder);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(OMSystemMnTest_1514, ReturnsNullptrWhenSizeIsSmallBoundaryMinusOne_1514) {
  // The function checks: size < OMSystemMnHeader::sizeOfSignature() + 18 => nullptr.
  // We test boundary-1 without assuming exact signature size by computing via the API.
  const std::size_t threshold = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature() + 18;
  ASSERT_GT(threshold, 0u);

  const std::size_t size = threshold - 1;
  std::vector<byte> buf(size, 0);
  auto mn = newOMSystemMn(kTag, kGroup, kMnGroup, buf.data(), size, kAnyByteOrder);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(OMSystemMnTest_1514, ReturnsNonNullptrWhenSizeEqualsThreshold_1514) {
  const std::size_t threshold = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature() + 18;

  std::vector<byte> buf(threshold, 0);
  auto mn = newOMSystemMn(kTag, kGroup, kMnGroup, buf.data(), buf.size(), kAnyByteOrder);

  // Observable behavior: should not be nullptr at boundary threshold.
  ASSERT_NE(mn, nullptr);
}

TEST_F(OMSystemMnTest_1514, ReturnsNonNullptrWhenSizeIsAboveThreshold_1514) {
  const std::size_t threshold = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature() + 18;

  std::vector<byte> buf(threshold + 1, 0);
  auto mn = newOMSystemMn(kTag, kGroup, kMnGroup, buf.data(), buf.size(), kAnyByteOrder);

  ASSERT_NE(mn, nullptr);
}

TEST_F(OMSystemMnTest_1514, NullptrWhenPointerIsNullAndSizeBelowThreshold_1514) {
  // Even with nullptr data pointer, size check alone should yield nullptr for small sizes.
  // (We do NOT assume behavior for nullptr when size >= threshold.)
  const std::size_t threshold = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature() + 18;
  ASSERT_GT(threshold, 0u);

  auto mn = newOMSystemMn(kTag, kGroup, kMnGroup, /*data=*/nullptr, /*size=*/threshold - 1,
                         kAnyByteOrder);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(OMSystemMnTest_1514, AcceptsDifferentByteOrderAtBoundaryAndReturnsNonNullptr_1514) {
  const std::size_t threshold = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature() + 18;

  std::vector<byte> buf(threshold, 0);

  auto mnLittle = newOMSystemMn(kTag, kGroup, kMnGroup, buf.data(), buf.size(), Exiv2::littleEndian);
  auto mnBig = newOMSystemMn(kTag, kGroup, kMnGroup, buf.data(), buf.size(), Exiv2::bigEndian);

  // We only verify the documented observable contract from provided code path:
  // size >= threshold => non-null return (the snippet doesn't branch on byte order for this check).
  ASSERT_NE(mnLittle, nullptr);
  ASSERT_NE(mnBig, nullptr);
}