// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_pentax_mn_header_1487.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"
#include "types.hpp"

namespace {

using Exiv2::byte;
using Exiv2::ByteOrder;

class PentaxMnHeaderTest_1487 : public ::testing::Test {
 protected:
  Exiv2::Internal::PentaxMnHeader header;
};

TEST_F(PentaxMnHeaderTest_1487, NullDataReturnsFalse_1487) {
  EXPECT_FALSE(header.read(nullptr, Exiv2::Internal::PentaxMnHeader::sizeOfSignature(), Exiv2::littleEndian));
  EXPECT_FALSE(header.read(nullptr, 0, Exiv2::bigEndian));
}

TEST_F(PentaxMnHeaderTest_1487, ZeroSizeReturnsFalse_1487) {
  const byte data[] = {0x00};
  EXPECT_FALSE(header.read(data, 0, Exiv2::littleEndian));
}

TEST_F(PentaxMnHeaderTest_1487, SizeLessThanSignatureReturnsFalse_1487) {
  const size_t sigSize = Exiv2::Internal::PentaxMnHeader::sizeOfSignature();
  ASSERT_GT(sigSize, 0u);

  const byte data[] = {'A', 'O', 'C', 0x00, 'M', 'M', 0x00};  // has enough bytes in storage
  EXPECT_FALSE(header.read(data, sigSize - 1, Exiv2::littleEndian));
}

TEST_F(PentaxMnHeaderTest_1487, ValidSignatureReturnsTrueAtExactSignatureSize_1487) {
  const size_t sigSize = Exiv2::Internal::PentaxMnHeader::sizeOfSignature();
  ASSERT_GE(sigSize, 6u);  // signature typically includes at least "AOC\0MM"

  const byte data[] = {'A', 'O', 'C', 0x00, 'M', 'M'};
  EXPECT_TRUE(header.read(data, sigSize, Exiv2::littleEndian));
}

TEST_F(PentaxMnHeaderTest_1487, ValidSignatureReturnsTrueWithLargerBuffer_1487) {
  const size_t sigSize = Exiv2::Internal::PentaxMnHeader::sizeOfSignature();

  const byte data[] = {'A', 'O', 'C', 0x00, 'M', 'M', 0x12, 0x34, 0x56};
  ASSERT_GE(sizeof(data), sigSize);
  EXPECT_TRUE(header.read(data, sizeof(data), Exiv2::bigEndian));
}

TEST_F(PentaxMnHeaderTest_1487, InvalidSignatureReturnsFalse_1487) {
  const size_t sigSize = Exiv2::Internal::PentaxMnHeader::sizeOfSignature();

  const byte bad1[] = {'X', 'O', 'C', 0x00, 'M', 'M'};
  ASSERT_GE(sizeof(bad1), sigSize);
  EXPECT_FALSE(header.read(bad1, sigSize, Exiv2::littleEndian));

  const byte bad2[] = {'A', 'X', 'C', 0x00, 'M', 'M'};
  ASSERT_GE(sizeof(bad2), sigSize);
  EXPECT_FALSE(header.read(bad2, sigSize, Exiv2::littleEndian));

  const byte bad3[] = {'A', 'O', 'X', 0x00, 'M', 'M'};
  ASSERT_GE(sizeof(bad3), sigSize);
  EXPECT_FALSE(header.read(bad3, sigSize, Exiv2::littleEndian));
}

TEST_F(PentaxMnHeaderTest_1487, SubsequentReadCanFailAfterSuccess_1487) {
  const size_t sigSize = Exiv2::Internal::PentaxMnHeader::sizeOfSignature();

  const byte good[] = {'A', 'O', 'C', 0x00, 'M', 'M'};
  ASSERT_GE(sizeof(good), sigSize);
  EXPECT_TRUE(header.read(good, sigSize, Exiv2::littleEndian));

  const byte bad[] = {'B', 'A', 'D', 0x00, 'M', 'M'};
  ASSERT_GE(sizeof(bad), sigSize);
  EXPECT_FALSE(header.read(bad, sigSize, Exiv2::littleEndian));
}

}  // namespace