// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_fuji_mn_header_1458.cpp

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>

#include "makernote_int.hpp"   // Exiv2::Internal::FujiMnHeader (declared here in Exiv2)
#include "types.hpp"           // Exiv2::byte, Exiv2::ByteOrder (typically)

namespace {

class FujiMnHeaderTest_1458 : public ::testing::Test {
 protected:
  static constexpr const char kSignature[8] = {'F','U','J','I','F','I','L','M'};

  static std::array<Exiv2::byte, 12> MakeValidHeaderBytesLittleEndian() {
    std::array<Exiv2::byte, 12> data{};
    // Signature (8 bytes)
    for (size_t i = 0; i < 8; ++i) data[i] = static_cast<Exiv2::byte>(kSignature[i]);

    // A plausible "start" value at offset 8 (uint32). Value itself is not observable via interface.
    // Use 12 (0x0000000c) in little-endian.
    data[8]  = static_cast<Exiv2::byte>(0x0c);
    data[9]  = static_cast<Exiv2::byte>(0x00);
    data[10] = static_cast<Exiv2::byte>(0x00);
    data[11] = static_cast<Exiv2::byte>(0x00);
    return data;
  }
};

TEST_F(FujiMnHeaderTest_1458, ReadReturnsFalseWhenDataIsNull_1458) {
  Exiv2::Internal::FujiMnHeader header;
  EXPECT_FALSE(header.read(nullptr, 0, Exiv2::littleEndian));
  EXPECT_FALSE(header.read(nullptr, 100, Exiv2::littleEndian));  // still null => false
}

TEST_F(FujiMnHeaderTest_1458, ReadReturnsFalseWhenSizeIsTooSmall_1458) {
  Exiv2::Internal::FujiMnHeader header;

  // Provide a non-null pointer but a definitely-too-small size (0 and 7 are both safe lower bounds).
  std::array<Exiv2::byte, 8> buf{};
  EXPECT_FALSE(header.read(buf.data(), 0, Exiv2::littleEndian));
  EXPECT_FALSE(header.read(buf.data(), 7, Exiv2::littleEndian));
}

TEST_F(FujiMnHeaderTest_1458, ReadReturnsFalseWhenSignatureDoesNotMatch_1458) {
  Exiv2::Internal::FujiMnHeader header;

  auto data = MakeValidHeaderBytesLittleEndian();
  data[0] = static_cast<Exiv2::byte>('X');  // break the signature
  EXPECT_FALSE(header.read(data.data(), data.size(), Exiv2::littleEndian));
}

TEST_F(FujiMnHeaderTest_1458, ReadReturnsTrueForValidSignatureAndSufficientSize_1458) {
  Exiv2::Internal::FujiMnHeader header;

  auto data = MakeValidHeaderBytesLittleEndian();
  EXPECT_TRUE(header.read(data.data(), data.size(), Exiv2::littleEndian));
}

}  // namespace