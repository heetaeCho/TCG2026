// File: test_casio2_mn_header_1507.cpp
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <vector>

#include "makernote_int.hpp"  // Exiv2::Internal::Casio2MnHeader, Exiv2::byte, Exiv2::ByteOrder

namespace {

using Exiv2::ByteOrder;
using Exiv2::byte;
using Exiv2::bigEndian;
using Exiv2::Internal::Casio2MnHeader;

std::vector<byte> MakeCasio2SignatureBuffer(size_t sigSize) {
  // Exiv2 docs indicate Casio2 header signature is "QVC\0\0\0" (6 bytes). :contentReference[oaicite:0]{index=0}
  // To avoid hard-coding the exact length, build "QVC" followed by zeros up to sigSize.
  std::vector<byte> buf(sigSize, static_cast<byte>(0x00));
  if (sigSize > 0) buf[0] = static_cast<byte>('Q');
  if (sigSize > 1) buf[1] = static_cast<byte>('V');
  if (sigSize > 2) buf[2] = static_cast<byte>('C');
  return buf;
}

}  // namespace

class Casio2MnHeaderTest_1507 : public ::testing::Test {
 protected:
  Casio2MnHeader header_;
};

TEST_F(Casio2MnHeaderTest_1507, ReadReturnsFalseWhenDataIsNull_1507) {
  const size_t size = Casio2MnHeader::sizeOfSignature();
  EXPECT_FALSE(header_.read(nullptr, size, bigEndian));
  EXPECT_FALSE(header_.read(nullptr, 0, bigEndian));
}

TEST_F(Casio2MnHeaderTest_1507, ReadReturnsFalseWhenSizeIsSmallerThanSignature_1507) {
  const size_t sigSize = Casio2MnHeader::sizeOfSignature();
  ASSERT_GT(sigSize, 0u);

  auto sigBuf = MakeCasio2SignatureBuffer(sigSize);

  // Boundary: just below the required size.
  EXPECT_FALSE(header_.read(sigBuf.data(), sigSize - 1, bigEndian));
}

TEST_F(Casio2MnHeaderTest_1507, ReadReturnsFalseWhenSignatureDoesNotMatch_1507) {
  const size_t sigSize = Casio2MnHeader::sizeOfSignature();
  ASSERT_GT(sigSize, 0u);

  auto buf = MakeCasio2SignatureBuffer(sigSize);
  // Corrupt first byte to force mismatch.
  buf[0] = static_cast<byte>('X');

  EXPECT_FALSE(header_.read(buf.data(), sigSize, bigEndian));
}

TEST_F(Casio2MnHeaderTest_1507, ReadReturnsTrueForExactSignatureAndExactSize_1507) {
  const size_t sigSize = Casio2MnHeader::sizeOfSignature();
  ASSERT_GT(sigSize, 0u);

  auto buf = MakeCasio2SignatureBuffer(sigSize);
  EXPECT_TRUE(header_.read(buf.data(), sigSize, bigEndian));
}

TEST_F(Casio2MnHeaderTest_1507, ReadReturnsTrueWhenBufferHasExtraTrailingData_1507) {
  const size_t sigSize = Casio2MnHeader::sizeOfSignature();
  ASSERT_GT(sigSize, 0u);

  // Signature at the start, extra bytes afterward.
  std::vector<byte> buf(sigSize + 16, static_cast<byte>(0xAB));
  auto sigPrefix = MakeCasio2SignatureBuffer(sigSize);
  std::copy(sigPrefix.begin(), sigPrefix.end(), buf.begin());

  EXPECT_TRUE(header_.read(buf.data(), buf.size(), bigEndian));
}

TEST_F(Casio2MnHeaderTest_1507, ReadCanBeCalledMultipleTimesIndependently_1507) {
  const size_t sigSize = Casio2MnHeader::sizeOfSignature();
  ASSERT_GT(sigSize, 0u);

  auto good = MakeCasio2SignatureBuffer(sigSize);
  auto bad = good;
  if (!bad.empty()) bad.back() = static_cast<byte>(0xFF);

  EXPECT_TRUE(header_.read(good.data(), good.size(), bigEndian));
  EXPECT_FALSE(header_.read(bad.data(), bad.size(), bigEndian));
  EXPECT_TRUE(header_.read(good.data(), good.size(), bigEndian));
}