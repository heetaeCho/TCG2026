// File: test_newolympusmn_1511.cpp
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

#include "makernote_int.hpp"  // Exiv2::Internal::newOlympusMn + header types (Olympus*/OMSystem*)

// Some builds place internal headers under exiv2/; fall back if needed.
#if __has_include("exiv2/makernote_int.hpp")
#include "exiv2/makernote_int.hpp"
#endif

namespace {

using Exiv2::ByteOrder;
using Exiv2::Internal::IfdId;
using Exiv2::Internal::newOlympusMn;

static std::vector<Exiv2::byte> MakeBufferWithPrefix(const char* bytes, size_t prefixLen, size_t totalSize) {
  std::vector<Exiv2::byte> buf(totalSize, Exiv2::byte{0});
  const size_t n = (prefixLen < totalSize) ? prefixLen : totalSize;
  for (size_t i = 0; i < n; ++i) {
    buf[i] = static_cast<Exiv2::byte>(static_cast<unsigned char>(bytes[i]));
  }
  return buf;
}

class NewOlympusMnTest_1511 : public ::testing::Test {
 protected:
  uint16_t tag_ = 0x1234;
  IfdId group_ = IfdId::olympusId;
  IfdId ignoredIfd_ = IfdId::ifd0Id;  // Third IfdId parameter is ignored by implementation.
  ByteOrder order_ = Exiv2::littleEndian;
};

}  // namespace

TEST_F(NewOlympusMnTest_1511, OMSystemSignature_SizeJustBelowThreshold_ReturnsNullptr_1511) {
  const size_t threshold = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature() + 18;

  // Prefix must match exactly 14 bytes: "OM SYSTEM\0\0\0II"
  const char sig14[] = {'O','M',' ','S','Y','S','T','E','M','\0','\0','\0','I','I'};
  ASSERT_GE(sizeof(sig14), 14u);

  ASSERT_GT(threshold, 0u);
  const size_t size = (threshold > 0) ? (threshold - 1) : 0;

  auto data = MakeBufferWithPrefix(sig14, 14, size);
  auto mn = newOlympusMn(tag_, group_, ignoredIfd_, data.data(), data.size(), order_);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewOlympusMnTest_1511, OMSystemSignature_SizeAtThreshold_ReturnsNonNull_1511) {
  const size_t threshold = Exiv2::Internal::OMSystemMnHeader::sizeOfSignature() + 18;

  const char sig14[] = {'O','M',' ','S','Y','S','T','E','M','\0','\0','\0','I','I'};
  auto data = MakeBufferWithPrefix(sig14, 14, threshold);

  auto mn = newOlympusMn(tag_, group_, ignoredIfd_, data.data(), data.size(), order_);
  EXPECT_NE(mn, nullptr);
}

TEST_F(NewOlympusMnTest_1511, OlympusClassicSignature_SizeJustBelowThreshold_ReturnsNullptr_1511) {
  const size_t threshold = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature() + 18;

  // Prefix must match exactly 10 bytes: "OLYMPUS\0II"
  const char sig10[] = {'O','L','Y','M','P','U','S','\0','I','I'};
  ASSERT_GE(sizeof(sig10), 10u);

  ASSERT_GT(threshold, 0u);
  const size_t size = (threshold > 0) ? (threshold - 1) : 0;

  auto data = MakeBufferWithPrefix(sig10, 10, size);
  auto mn = newOlympusMn(tag_, group_, ignoredIfd_, data.data(), data.size(), order_);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewOlympusMnTest_1511, OlympusClassicSignature_SizeAtThreshold_ReturnsNonNull_1511) {
  const size_t threshold = Exiv2::Internal::Olympus2MnHeader::sizeOfSignature() + 18;

  const char sig10[] = {'O','L','Y','M','P','U','S','\0','I','I'};
  auto data = MakeBufferWithPrefix(sig10, 10, threshold);

  auto mn = newOlympusMn(tag_, group_, ignoredIfd_, data.data(), data.size(), order_);
  EXPECT_NE(mn, nullptr);
}

TEST_F(NewOlympusMnTest_1511, NonMatchingPrefix_SizeBelowOlympusMnThreshold_ReturnsNullptr_1511) {
  const size_t threshold = Exiv2::Internal::OlympusMnHeader::sizeOfSignature() + 18;

  // Ensure it does NOT match "OM SYSTEM\0\0\0II" nor "OLYMPUS\0II".
  const char junk[] = {'N','O','T','_','O','L','Y','_','X','X','X','X','X','X'};
  ASSERT_GT(threshold, 0u);
  const size_t size = (threshold > 0) ? (threshold - 1) : 0;

  auto data = MakeBufferWithPrefix(junk, sizeof(junk), size);
  auto mn = newOlympusMn(tag_, group_, ignoredIfd_, data.data(), data.size(), order_);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewOlympusMnTest_1511, NonMatchingPrefix_SizeAtOlympusMnThreshold_ReturnsNonNull_1511) {
  const size_t threshold = Exiv2::Internal::OlympusMnHeader::sizeOfSignature() + 18;

  const char junk[] = {'N','O','T','_','O','L','Y','_','X','X','X','X','X','X'};
  auto data = MakeBufferWithPrefix(junk, sizeof(junk), threshold);

  auto mn = newOlympusMn(tag_, group_, ignoredIfd_, data.data(), data.size(), order_);
  EXPECT_NE(mn, nullptr);
}

TEST_F(NewOlympusMnTest_1511, SizeLessThan10ForcesNonOlympusClassicPath_StillReturnsNullWhenBelowThreshold_1511) {
  const size_t threshold = Exiv2::Internal::OlympusMnHeader::sizeOfSignature() + 18;

  // size < 10 triggers the "not OLYMPUS\0II" branch.
  const size_t size = 9;
  ASSERT_LT(size, 10u);
  ASSERT_GT(threshold, size);  // If this fails in some build, the test is not meaningful.

  std::vector<Exiv2::byte> data(size, Exiv2::byte{0});
  auto mn = newOlympusMn(tag_, group_, ignoredIfd_, data.data(), data.size(), order_);
  EXPECT_EQ(mn, nullptr);
}