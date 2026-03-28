// =================================================================================================
// TEST_ID: 1526
// File: test_new_samsung_mn_1526.cpp
// Unit tests for Exiv2::Internal::newSamsungMn (black-box via public/internal interface)
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <vector>

// Exiv2 headers (paths may vary by project setup)
#include "makernote_int.hpp"  // for Exiv2::Internal::newSamsungMn, TiffIfdMakernote, PentaxMnHeader (if exposed)
#include "types.hpp"          // for Exiv2::byte, Exiv2::ByteOrder, Exiv2::IfdId (if needed)

namespace {

using Exiv2::byte;

std::vector<byte> MakeDataWithPrefixAndSize(const char prefix4[4], size_t totalSize, byte fill = 0x00) {
  std::vector<byte> v(totalSize, fill);
  if (totalSize >= 4) {
    std::memcpy(v.data(), prefix4, 4);
  } else if (totalSize > 0) {
    std::memcpy(v.data(), prefix4, totalSize);
  }
  return v;
}

constexpr char kAocSig[4] = {'A', 'O', 'C', '\0'};
constexpr char kNotAocSig[4] = {'N', 'O', 'P', '\0'};

}  // namespace

TEST(NewSamsungMnTest_1526, ReturnsNullptrWhenSizeLessThan18AndNotAOC_1526) {
  const uint16_t tag = 0x0001;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(0);
  const Exiv2::ByteOrder bo = static_cast<Exiv2::ByteOrder>(0);

  auto data = MakeDataWithPrefixAndSize(kNotAocSig, 17);

  auto mn = Exiv2::Internal::newSamsungMn(tag, group, mnGroup, data.data(), data.size(), bo);
  EXPECT_EQ(mn, nullptr);
}

TEST(NewSamsungMnTest_1526, ReturnsNonNullptrWhenSizeExactly18AndNotAOC_1526) {
  const uint16_t tag = 0x0001;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(0);
  const Exiv2::ByteOrder bo = static_cast<Exiv2::ByteOrder>(0);

  auto data = MakeDataWithPrefixAndSize(kNotAocSig, 18);

  auto mn = Exiv2::Internal::newSamsungMn(tag, group, mnGroup, data.data(), data.size(), bo);

  // Observable behavior expectation: size >= 18 in non-AOC case should yield a makernote instance.
  // If the downstream factory returns nullptr for this input in your build, adjust the expectation.
  ASSERT_NE(mn, nullptr);
}

TEST(NewSamsungMnTest_1526, AOCSignatureNotConsideredWhenSizeIs4OrLess_1526) {
  const uint16_t tag = 0x0001;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(0);
  const Exiv2::ByteOrder bo = static_cast<Exiv2::ByteOrder>(0);

  // size == 4: even though prefix matches, signature check requires size > 4 (per provided implementation),
  // and then the non-AOC size < 18 guard is expected to apply.
  auto data = MakeDataWithPrefixAndSize(kAocSig, 4);

  auto mn = Exiv2::Internal::newSamsungMn(tag, group, mnGroup, data.data(), data.size(), bo);
  EXPECT_EQ(mn, nullptr);
}

TEST(NewSamsungMnTest_1526, ReturnsNullptrForAOCWhenBelowPentaxSignaturePlus18_1526) {
  const uint16_t tag = 0x0001;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(0);
  const Exiv2::ByteOrder bo = static_cast<Exiv2::ByteOrder>(0);

  // Boundary: AOC path requires size >= PentaxMnHeader::sizeOfSignature() + 18
  const size_t required = Exiv2::Internal::PentaxMnHeader::sizeOfSignature() + 18;
  ASSERT_GE(required, 19u);  // sanity: since AOC path also requires size > 4

  auto data = MakeDataWithPrefixAndSize(kAocSig, required - 1);

  auto mn = Exiv2::Internal::newSamsungMn(tag, group, mnGroup, data.data(), data.size(), bo);
  EXPECT_EQ(mn, nullptr);
}

TEST(NewSamsungMnTest_1526, ReturnsNonNullptrForAOCWhenAtLeastPentaxSignaturePlus18_1526) {
  const uint16_t tag = 0x0001;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(0);
  const Exiv2::ByteOrder bo = static_cast<Exiv2::ByteOrder>(0);

  const size_t required = Exiv2::Internal::PentaxMnHeader::sizeOfSignature() + 18;

  auto data = MakeDataWithPrefixAndSize(kAocSig, required);

  auto mn = Exiv2::Internal::newSamsungMn(tag, group, mnGroup, data.data(), data.size(), bo);

  // Observable behavior expectation: meeting the AOC minimum size should yield a makernote instance.
  // If the downstream factory returns nullptr for this input in your build, adjust the expectation.
  ASSERT_NE(mn, nullptr);
}

TEST(NewSamsungMnTest_1526, NonAOCIgnoresAOCCheckAndStillUses18ByteMinimum_1526) {
  const uint16_t tag = 0x0001;
  const Exiv2::IfdId group = static_cast<Exiv2::IfdId>(0);
  const Exiv2::IfdId mnGroup = static_cast<Exiv2::IfdId>(0);
  const Exiv2::ByteOrder bo = static_cast<Exiv2::ByteOrder>(0);

  // size > 4 but prefix is not AOC; boundary should remain 18.
  auto data17 = MakeDataWithPrefixAndSize(kNotAocSig, 17);
  auto mn17 = Exiv2::Internal::newSamsungMn(tag, group, mnGroup, data17.data(), data17.size(), bo);
  EXPECT_EQ(mn17, nullptr);

  auto data18 = MakeDataWithPrefixAndSize(kNotAocSig, 18);
  auto mn18 = Exiv2::Internal::newSamsungMn(tag, group, mnGroup, data18.data(), data18.size(), bo);
  ASSERT_NE(mn18, nullptr);
}