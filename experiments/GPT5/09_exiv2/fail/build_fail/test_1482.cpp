// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_pentaxdngmnheader_1482.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"  // Exiv2::Internal::PentaxDngMnHeader
#include "types.hpp"          // Exiv2::byte, Exiv2::ByteOrder

#include <array>
#include <cstddef>

namespace {

using Exiv2::ByteOrder;
using Exiv2::byte;
using Exiv2::Internal::PentaxDngMnHeader;

class PentaxDngMnHeaderTest_1482 : public ::testing::Test {
 protected:
  // Known Pentax DNG header signature used by Exiv2:
  // {'P','E','N','T','A','X',' ',0x00,'M','M'} with cmp on first 7 bytes ("PENTAX ").
  static constexpr std::array<byte, 10> kSignature = {
      static_cast<byte>('P'), static_cast<byte>('E'), static_cast<byte>('N'), static_cast<byte>('T'),
      static_cast<byte>('A'), static_cast<byte>('X'), static_cast<byte>(' '), static_cast<byte>(0x00),
      static_cast<byte>('M'), static_cast<byte>('M'),
  };
};

constexpr std::array<byte, 10> PentaxDngMnHeaderTest_1482::kSignature;

TEST_F(PentaxDngMnHeaderTest_1482, ReadReturnsFalseWhenDataIsNull_1482) {
  PentaxDngMnHeader header;
  EXPECT_FALSE(header.read(nullptr, 10, ByteOrder::invalidByteOrder));
  EXPECT_FALSE(header.read(nullptr, 0, ByteOrder::littleEndian));
}

TEST_F(PentaxDngMnHeaderTest_1482, ReadReturnsFalseWhenSizeIsSmallerThanSignature_1482) {
  PentaxDngMnHeader header;

  std::array<byte, 10> buf = kSignature;
  for (size_t sz = 0; sz < buf.size(); ++sz) {
    EXPECT_FALSE(header.read(buf.data(), sz, ByteOrder::invalidByteOrder)) << "sz=" << sz;
  }
}

TEST_F(PentaxDngMnHeaderTest_1482, ReadReturnsTrueForExactSignatureBuffer_1482) {
  PentaxDngMnHeader header;

  std::array<byte, 10> buf = kSignature;
  EXPECT_TRUE(header.read(buf.data(), buf.size(), ByteOrder::invalidByteOrder));
}

TEST_F(PentaxDngMnHeaderTest_1482, ReadChecksOnlyFirstSevenBytesOfSignature_1482) {
  PentaxDngMnHeader header;

  // First 7 bytes match: "PENTAX "
  std::array<byte, 10> buf = kSignature;
  buf[7] = static_cast<byte>(0x7f);
  buf[8] = static_cast<byte>('X');
  buf[9] = static_cast<byte>('X');

  EXPECT_TRUE(header.read(buf.data(), buf.size(), ByteOrder::invalidByteOrder));
}

TEST_F(PentaxDngMnHeaderTest_1482, ReadReturnsFalseWhenFirstSevenBytesDoNotMatch_1482) {
  PentaxDngMnHeader header;

  std::array<byte, 10> buf = kSignature;
  buf[0] = static_cast<byte>('Q');  // break the "PENTAX " prefix
  EXPECT_FALSE(header.read(buf.data(), buf.size(), ByteOrder::invalidByteOrder));

  // Also verify a mismatch within the first 7 bytes fails.
  buf = kSignature;
  buf[6] = static_cast<byte>('_');  // was ' '
  EXPECT_FALSE(header.read(buf.data(), buf.size(), ByteOrder::invalidByteOrder));
}

TEST_F(PentaxDngMnHeaderTest_1482, ReadResultIsIndependentOfByteOrderArgument_1482) {
  PentaxDngMnHeader header;

  std::array<byte, 10> good = kSignature;
  EXPECT_TRUE(header.read(good.data(), good.size(), ByteOrder::littleEndian));
  EXPECT_TRUE(header.read(good.data(), good.size(), ByteOrder::bigEndian));
  EXPECT_TRUE(header.read(good.data(), good.size(), ByteOrder::invalidByteOrder));

  std::array<byte, 10> bad = kSignature;
  bad[1] = static_cast<byte>('0');  // mismatch within first 7 bytes
  EXPECT_FALSE(header.read(bad.data(), bad.size(), ByteOrder::littleEndian));
  EXPECT_FALSE(header.read(bad.data(), bad.size(), ByteOrder::bigEndian));
  EXPECT_FALSE(header.read(bad.data(), bad.size(), ByteOrder::invalidByteOrder));
}

}  // namespace