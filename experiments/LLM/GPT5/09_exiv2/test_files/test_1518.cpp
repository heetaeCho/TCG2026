// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_newnikonmn_1518.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

// Exiv2 internal interface under test
#include "makernote_int.hpp"

namespace {

using Exiv2::byte;

class NewNikonMnTest_1518 : public ::testing::Test {
 protected:
  static std::vector<byte> MakeBufWithPrefix(const std::vector<byte>& prefix, size_t totalSize, byte fill = 0x00) {
    std::vector<byte> buf(totalSize, fill);
    for (size_t i = 0; i < prefix.size() && i < buf.size(); ++i) buf[i] = prefix[i];
    return buf;
  }

  // Nikon maker-note "Nikon\0" signature at offset 0, and (optionally) a TIFF header at offset 10.
  static std::vector<byte> MakeNikonSigBuf(size_t totalSize, bool putValidTiffHeaderAt10) {
    const std::vector<byte> nikonSig = {'N','i','k','o','n','\0'};
    auto buf = MakeBufWithPrefix(nikonSig, totalSize, 0x00);

    if (putValidTiffHeaderAt10 && totalSize >= 18) {
      // Classic TIFF header (8 bytes) at offset 10:
      // Byte order "II", tag 0x002a, offset 0x00000008 (little-endian)
      buf[10] = 'I';
      buf[11] = 'I';
      buf[12] = 0x2a;
      buf[13] = 0x00;
      buf[14] = 0x08;
      buf[15] = 0x00;
      buf[16] = 0x00;
      buf[17] = 0x00;
    }
    return buf;
  }

  static Exiv2::IfdId AnyIfdId() { return static_cast<Exiv2::IfdId>(0); }
  static Exiv2::ByteOrder AnyByteOrder() { return static_cast<Exiv2::ByteOrder>(0); }
};

TEST_F(NewNikonMnTest_1518, ReturnsNullWhenSizeLessThan18AndNoNikonSignature_1518) {
  // size < 6 => enters "no Nikon signature" path, and because size < 18 returns nullptr.
  auto buf = MakeBufWithPrefix({'X','X','X','X','X'}, 5);
  auto mn = Exiv2::Internal::newNikonMn(/*tag*/0x0001, AnyIfdId(), AnyIfdId(), buf.data(), buf.size(), AnyByteOrder());
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewNikonMnTest_1518, ReturnsNullWhenSignatureMismatchAndSizeBetween6And17_1518) {
  // size >= 6 but signature mismatches; still size < 18 => nullptr.
  auto buf = MakeBufWithPrefix({'N','o','t','N','i','k'}, 17);
  auto mn = Exiv2::Internal::newNikonMn(/*tag*/0x0002, AnyIfdId(), AnyIfdId(), buf.data(), buf.size(), AnyByteOrder());
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewNikonMnTest_1518, ReturnsNonNullWhenSignatureMismatchAndSizeAtLeast18_1518) {
  // "no Nikon signature" path with size >= 18 returns a non-null maker-note (newIfdMn2).
  auto buf = MakeBufWithPrefix({'B','A','D','S','I','G'}, 18);
  auto mn = Exiv2::Internal::newNikonMn(/*tag*/0x0003, AnyIfdId(), AnyIfdId(), buf.data(), buf.size(), AnyByteOrder());
  EXPECT_NE(mn, nullptr);
}

TEST_F(NewNikonMnTest_1518, ReturnsNullWhenHasNikonSignatureButSizeLessThan18_1518) {
  // Nikon signature present, but size < 18 triggers the TIFF-header failure path and then
  // requires Nikon2 signature size + 18; with < 18 it must be nullptr.
  auto buf = MakeNikonSigBuf(6, /*putValidTiffHeaderAt10*/false);
  auto mn = Exiv2::Internal::newNikonMn(/*tag*/0x0004, AnyIfdId(), AnyIfdId(), buf.data(), buf.size(), AnyByteOrder());
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewNikonMnTest_1518, ReturnsNullWhenNikonSignatureAndInsufficientForNikon2SignaturePlus18_1518) {
  // Nikon signature present. Force the "TIFF header invalid" path by NOT placing a valid TIFF header.
  // If total size is less than Nikon2MnHeader::sizeOfSignature() + 18 => nullptr.
  const size_t need = Exiv2::Internal::Nikon2MnHeader::sizeOfSignature() + 18;
  ASSERT_GT(need, 0u);
  auto buf = MakeNikonSigBuf(need - 1, /*putValidTiffHeaderAt10*/false);
  auto mn = Exiv2::Internal::newNikonMn(/*tag*/0x0005, AnyIfdId(), AnyIfdId(), buf.data(), buf.size(), AnyByteOrder());
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewNikonMnTest_1518, ReturnsNonNullWhenNikonSignatureAndMeetsNikon2SignaturePlus18_1518) {
  // Nikon signature present, and enough bytes for Nikon2 signature size + 18.
  // With an invalid/missing TIFF header, this should select the Nikon2 maker-note path.
  const size_t need = Exiv2::Internal::Nikon2MnHeader::sizeOfSignature() + 18;
  auto buf = MakeNikonSigBuf(need, /*putValidTiffHeaderAt10*/false);
  auto mn = Exiv2::Internal::newNikonMn(/*tag*/0x0006, AnyIfdId(), AnyIfdId(), buf.data(), buf.size(), AnyByteOrder());
  EXPECT_NE(mn, nullptr);
}

TEST_F(NewNikonMnTest_1518, ReturnsNullWhenValidTiffHeaderButInsufficientForNikon3SignaturePlus18_1518) {
  // Nikon signature present and a valid TIFF header (tag 0x002a) at offset 10.
  // Then it requires Nikon3MnHeader::sizeOfSignature() + 18.
  const size_t need3 = Exiv2::Internal::Nikon3MnHeader::sizeOfSignature() + 18;
  ASSERT_GT(need3, 0u);
  auto buf = MakeNikonSigBuf(need3 - 1, /*putValidTiffHeaderAt10*/true);
  auto mn = Exiv2::Internal::newNikonMn(/*tag*/0x0007, AnyIfdId(), AnyIfdId(), buf.data(), buf.size(), AnyByteOrder());
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewNikonMnTest_1518, ReturnsNonNullWhenValidTiffHeaderAndMeetsNikon3SignaturePlus18_1518) {
  // Nikon signature present and valid TIFF header (tag 0x002a) at offset 10.
  // If size is at least Nikon3MnHeader::sizeOfSignature() + 18 => non-null (Nikon3 path).
  const size_t need3 = Exiv2::Internal::Nikon3MnHeader::sizeOfSignature() + 18;
  auto buf = MakeNikonSigBuf(need3, /*putValidTiffHeaderAt10*/true);
  auto mn = Exiv2::Internal::newNikonMn(/*tag*/0x0008, AnyIfdId(), AnyIfdId(), buf.data(), buf.size(), AnyByteOrder());
  EXPECT_NE(mn, nullptr);
}

}  // namespace