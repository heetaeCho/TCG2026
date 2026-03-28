// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_nikon3_mnheader_test_1470.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstring>
#include <vector>

#if __has_include("makernote_int.hpp")
#include "makernote_int.hpp"
#elif __has_include("exiv2/makernote_int.hpp")
#include "exiv2/makernote_int.hpp"
#elif __has_include(<exiv2/makernote_int.hpp>)
#include <exiv2/makernote_int.hpp>
#else
// Fall back to the common Exiv2 umbrella header in case internal headers are exposed through it.
#include <exiv2/exiv2.hpp>
#endif

namespace {

#if defined(Exiv2::littleEndian) || defined(littleEndian) || defined(bigEndian)
static Exiv2::ByteOrder GetLittleEndian() {
#if defined(Exiv2::littleEndian)
  return Exiv2::littleEndian;
#else
  return littleEndian;
#endif
}
#else
static Exiv2::ByteOrder GetLittleEndian() { return Exiv2::ByteOrder::littleEndian; }
#endif

static std::vector<Exiv2::byte> MakeValidNikon3HeaderBytes() {
  // Construct a minimal Nikon Type 3 MakerNote header that satisfies the observable checks:
  // - First 6 bytes match "Nikon\0"
  // - A valid TIFF header exists starting at offset 10 (8 bytes)
  std::vector<Exiv2::byte> buf(18, Exiv2::byte{0});

  // Signature: "Nikon\0" (6 bytes)
  const unsigned char sig[6] = {'N', 'i', 'k', 'o', 'n', '\0'};
  std::memcpy(buf.data(), sig, sizeof(sig));

  // Bytes [6..9] are not part of the 6-byte signature comparison in the shown code path.
  // Keep them as a conventional Nikon marker; contents should not matter unless implementation checks them.
  buf[6] = 0x02;
  buf[7] = 0x00;
  buf[8] = 0x00;
  buf[9] = 0x00;

  // TIFF header at offset 10 (8 bytes):
  // Byte order: 'I''I' (little endian)
  // Magic: 42 (0x2A)
  // IFD offset: 8
  buf[10] = 'I';
  buf[11] = 'I';
  buf[12] = 0x2A;
  buf[13] = 0x00;
  buf[14] = 0x08;
  buf[15] = 0x00;
  buf[16] = 0x00;
  buf[17] = 0x00;

  return buf;
}

}  // namespace

TEST(Nikon3MnHeaderTest_1470, ReadReturnsFalseWhenDataIsNull_1470) {
  Exiv2::Internal::Nikon3MnHeader header;
  EXPECT_FALSE(header.read(nullptr, 0, GetLittleEndian()));
}

TEST(Nikon3MnHeaderTest_1470, ReadReturnsFalseWhenSizeIsZero_1470) {
  Exiv2::Internal::Nikon3MnHeader header;
  const Exiv2::byte b = 0;
  EXPECT_FALSE(header.read(&b, 0, GetLittleEndian()));
}

TEST(Nikon3MnHeaderTest_1470, ReadReturnsFalseWhenSizeTooSmallForSignature_1470) {
  Exiv2::Internal::Nikon3MnHeader header;

  // Provide fewer than 6 bytes so it cannot contain the "Nikon\0" signature.
  std::array<Exiv2::byte, 5> small{};
  EXPECT_FALSE(header.read(small.data(), small.size(), GetLittleEndian()));
}

TEST(Nikon3MnHeaderTest_1470, ReadReturnsFalseWhenSignatureDoesNotMatch_1470) {
  Exiv2::Internal::Nikon3MnHeader header;

  auto buf = MakeValidNikon3HeaderBytes();
  ASSERT_GE(buf.size(), 6u);

  // Corrupt the first byte of the 6-byte signature.
  buf[0] = static_cast<Exiv2::byte>('X');

  EXPECT_FALSE(header.read(buf.data(), buf.size(), GetLittleEndian()));
}

TEST(Nikon3MnHeaderTest_1470, ReadReturnsFalseWhenTiffHeaderIsInvalid_1470) {
  Exiv2::Internal::Nikon3MnHeader header;

  auto buf = MakeValidNikon3HeaderBytes();
  ASSERT_GE(buf.size(), 18u);

  // Corrupt the TIFF byte order marker at offset 10.
  buf[10] = static_cast<Exiv2::byte>('X');
  buf[11] = static_cast<Exiv2::byte>('X');

  EXPECT_FALSE(header.read(buf.data(), buf.size(), GetLittleEndian()));
}

TEST(Nikon3MnHeaderTest_1470, ReadReturnsTrueForWellFormedHeaderBytes_1470) {
  Exiv2::Internal::Nikon3MnHeader header;

  auto buf = MakeValidNikon3HeaderBytes();
  EXPECT_TRUE(header.read(buf.data(), buf.size(), GetLittleEndian()));
}

TEST(Nikon3MnHeaderTest_1470, ReadAllowsExtraTrailingBytesBeyondHeader_1470) {
  Exiv2::Internal::Nikon3MnHeader header;

  auto buf = MakeValidNikon3HeaderBytes();
  buf.resize(buf.size() + 32, Exiv2::byte{0});  // trailing data should not prevent reading the header

  EXPECT_TRUE(header.read(buf.data(), buf.size(), GetLittleEndian()));
}