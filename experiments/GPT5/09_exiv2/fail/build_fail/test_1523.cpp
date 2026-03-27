// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_newpentaxmn_1523.cpp

#include <gtest/gtest.h>

#include "makernote_int.hpp"
#include "types.hpp"

#include <cstdint>
#include <vector>

namespace Exiv2::Internal {

class NewPentaxMnTest_1523 : public ::testing::Test {
 protected:
  static std::vector<byte> MakeBufferWithPrefix(size_t size, const std::vector<byte>& prefix) {
    std::vector<byte> buf(size, static_cast<byte>('X'));
    const size_t n = std::min(buf.size(), prefix.size());
    for (size_t i = 0; i < n; ++i) buf[i] = prefix[i];
    return buf;
  }

  static std::vector<byte> PentaxSignature() {
    // "PENTAX \0" (8 bytes)
    return {static_cast<byte>('P'), static_cast<byte>('E'), static_cast<byte>('N'), static_cast<byte>('T'),
            static_cast<byte>('A'), static_cast<byte>('X'), static_cast<byte>(' '), static_cast<byte>(0)};
  }

  static std::vector<byte> AocSignature() {
    // "AOC\0" (4 bytes)
    return {static_cast<byte>('A'), static_cast<byte>('O'), static_cast<byte>('C'), static_cast<byte>(0)};
  }
};

TEST_F(NewPentaxMnTest_1523, ReturnsNullptrWhenSignatureDoesNotMatch_1523) {
  const auto data = MakeBufferWithPrefix(32, {static_cast<byte>('N'), static_cast<byte>('O'), static_cast<byte>('P')});
  auto mn = newPentaxMn(/*tag*/ 0x0001, /*group*/ IfdId::exifId, /*unused*/ IfdId::ifd0Id, data.data(), data.size(),
                       Exiv2::littleEndian);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewPentaxMnTest_1523, PentaxSignatureRequiresSizeGreaterThanEight_1523) {
  // size == 8 should not enter the "PENTAX \0" branch (requires size > 8).
  const auto data = MakeBufferWithPrefix(8, PentaxSignature());
  auto mn = newPentaxMn(/*tag*/ 0x0001, /*group*/ IfdId::exifId, /*unused*/ IfdId::ifd0Id, data.data(), data.size(),
                       Exiv2::littleEndian);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewPentaxMnTest_1523, PentaxSignatureReturnsNullptrWhenTooSmallForHeader_1523) {
  const size_t minSize = PentaxDngMnHeader::sizeOfSignature() + 18;
  ASSERT_GT(minSize, 0u);

  const size_t sizeTooSmall = (minSize > 1) ? (minSize - 1) : 0;
  const auto data = MakeBufferWithPrefix(sizeTooSmall, PentaxSignature());

  auto mn = newPentaxMn(/*tag*/ 0x0001, /*group*/ IfdId::exifId, /*unused*/ IfdId::ifd0Id, data.data(), data.size(),
                       Exiv2::littleEndian);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewPentaxMnTest_1523, PentaxSignatureCreatesMakernoteWhenMinSizeAndTagC634_1523) {
  const size_t minSize = PentaxDngMnHeader::sizeOfSignature() + 18;
  const auto data = MakeBufferWithPrefix(minSize, PentaxSignature());

  auto mn = newPentaxMn(/*tag*/ 0xc634, /*group*/ IfdId::exifId, /*unused*/ IfdId::ifd0Id, data.data(), data.size(),
                       Exiv2::littleEndian);
  EXPECT_NE(mn, nullptr);
}

TEST_F(NewPentaxMnTest_1523, PentaxSignatureCreatesMakernoteWhenMinSizeAndOtherTag_1523) {
  const size_t minSize = PentaxDngMnHeader::sizeOfSignature() + 18;
  const auto data = MakeBufferWithPrefix(minSize, PentaxSignature());

  auto mn = newPentaxMn(/*tag*/ 0x1234, /*group*/ IfdId::exifId, /*unused*/ IfdId::ifd0Id, data.data(), data.size(),
                       Exiv2::littleEndian);
  EXPECT_NE(mn, nullptr);
}

TEST_F(NewPentaxMnTest_1523, AocSignatureRequiresSizeGreaterThanFour_1523) {
  // size == 4 should not enter the "AOC\0" branch (requires size > 4).
  const auto data = MakeBufferWithPrefix(4, AocSignature());
  auto mn = newPentaxMn(/*tag*/ 0x0001, /*group*/ IfdId::exifId, /*unused*/ IfdId::ifd0Id, data.data(), data.size(),
                       Exiv2::littleEndian);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewPentaxMnTest_1523, AocSignatureReturnsNullptrWhenTooSmallForHeader_1523) {
  const size_t minSize = PentaxMnHeader::sizeOfSignature() + 18;
  ASSERT_GT(minSize, 0u);

  const size_t sizeTooSmall = (minSize > 1) ? (minSize - 1) : 0;
  const auto data = MakeBufferWithPrefix(sizeTooSmall, AocSignature());

  auto mn = newPentaxMn(/*tag*/ 0x0001, /*group*/ IfdId::exifId, /*unused*/ IfdId::ifd0Id, data.data(), data.size(),
                       Exiv2::littleEndian);
  EXPECT_EQ(mn, nullptr);
}

TEST_F(NewPentaxMnTest_1523, AocSignatureCreatesMakernoteWhenMinSize_1523) {
  const size_t minSize = PentaxMnHeader::sizeOfSignature() + 18;
  const auto data = MakeBufferWithPrefix(minSize, AocSignature());

  auto mn = newPentaxMn(/*tag*/ 0x0001, /*group*/ IfdId::exifId, /*unused*/ IfdId::ifd0Id, data.data(), data.size(),
                       Exiv2::littleEndian);
  EXPECT_NE(mn, nullptr);
}

}  // namespace Exiv2::Internal