// -------------------------------------------------------------------------------------------------
// TEST_ID: 1581
// File: test_rw2parser_decode_1581.cpp
// Unit tests for Exiv2::Rw2Parser::decode (rw2image.cpp)
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/rw2image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/xmp_exiv2.hpp>

namespace {

using Exiv2::byte;

// Build a minimal RW2/TIFF-like buffer consistent with the public RW2 header parameters shown:
// - Byte order: little endian ("II")
// - Magic: 0x0055
// - IFD0 offset: 0x00000018 (24)
// Provide room for an empty IFD at offset 24: [2-byte count=0][4-byte nextIFD=0].
std::vector<byte> makeMinimalRw2LittleEndianBuffer() {
  std::vector<byte> buf(30, static_cast<byte>(0x00));

  // Endianness "II"
  buf[0] = static_cast<byte>('I');
  buf[1] = static_cast<byte>('I');

  // Magic 0x0055 (little endian)
  buf[2] = static_cast<byte>(0x55);
  buf[3] = static_cast<byte>(0x00);

  // IFD0 offset = 24 (0x18) little endian (4 bytes)
  buf[4] = static_cast<byte>(0x18);
  buf[5] = static_cast<byte>(0x00);
  buf[6] = static_cast<byte>(0x00);
  buf[7] = static_cast<byte>(0x00);

  // At offset 24: entry count (2 bytes) = 0
  buf[24] = static_cast<byte>(0x00);
  buf[25] = static_cast<byte>(0x00);

  // Next IFD offset (4 bytes) = 0 already zeroed: buf[26..29]
  return buf;
}

std::vector<byte> makeTooSmallBuffer(std::size_t n) {
  return std::vector<byte>(n, static_cast<byte>(0x00));
}

std::vector<byte> makeBigEndianRw2LikeHeaderBuffer() {
  // Same as minimal but "MM" big-endian header + magic in big-endian order.
  std::vector<byte> buf(30, static_cast<byte>(0x00));
  buf[0] = static_cast<byte>('M');
  buf[1] = static_cast<byte>('M');

  // Magic 0x0055 (big endian)
  buf[2] = static_cast<byte>(0x00);
  buf[3] = static_cast<byte>(0x55);

  // IFD0 offset = 24 in big-endian
  buf[4] = static_cast<byte>(0x00);
  buf[5] = static_cast<byte>(0x00);
  buf[6] = static_cast<byte>(0x00);
  buf[7] = static_cast<byte>(0x18);

  // Empty IFD at offset 24 (count=0, next=0)
  buf[24] = static_cast<byte>(0x00);
  buf[25] = static_cast<byte>(0x00);
  return buf;
}

class Rw2ParserTest_1581 : public ::testing::Test {};

}  // namespace

// Normal operation: decoding a minimal RW2 buffer should not crash and should return a ByteOrder.
TEST_F(Rw2ParserTest_1581, Decode_MinimalLittleEndianBuffer_ReturnsLittleEndian_1581) {
  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;

  const auto buf = makeMinimalRw2LittleEndianBuffer();

  Exiv2::ByteOrder bo = Exiv2::invalidByteOrder;
  ASSERT_NO_THROW({
    bo = Exiv2::Rw2Parser::decode(exif, iptc, xmp, buf.data(), buf.size());
  });

  EXPECT_EQ(Exiv2::littleEndian, bo);

  // With an empty IFD, metadata should remain empty (observable via public API).
  EXPECT_TRUE(exif.empty());
  EXPECT_TRUE(iptc.empty());
  EXPECT_TRUE(xmp.empty());
}

// Boundary: smallest “reasonable” size around the header/IFD boundary.
// This checks that the function handles short buffers (likely error/exception path).
TEST_F(Rw2ParserTest_1581, Decode_BufferTooSmall_Throws_1581) {
  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;

  // Much smaller than the RW2 header length (24) shown in Rw2Header.
  const auto buf = makeTooSmallBuffer(10);

  EXPECT_ANY_THROW({
    (void)Exiv2::Rw2Parser::decode(exif, iptc, xmp, buf.data(), buf.size());
  });
}

// Boundary: exact header size (24) but no space for an IFD at offset 24.
// This is a tight boundary that should be handled (commonly by throwing).
TEST_F(Rw2ParserTest_1581, Decode_ExactHeaderSize_NoIfdRoom_Throws_1581) {
  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;

  auto buf = makeMinimalRw2LittleEndianBuffer();
  buf.resize(24);  // truncate to exactly the header size

  EXPECT_ANY_THROW({
    (void)Exiv2::Rw2Parser::decode(exif, iptc, xmp, buf.data(), buf.size());
  });
}

// Error case: invalid pointer/size combination.
// If size is zero, passing nullptr should be safely handled (typically by throwing).
TEST_F(Rw2ParserTest_1581, Decode_NullDataWithZeroSize_Throws_1581) {
  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;

  EXPECT_ANY_THROW({
    (void)Exiv2::Rw2Parser::decode(exif, iptc, xmp, nullptr, 0);
  });
}

// Error case: RW2 header is expected to be little-endian per the shown Rw2Header ctor.
// A big-endian "RW2-like" header should be rejected (observable via throw).
TEST_F(Rw2ParserTest_1581, Decode_BigEndianHeader_IsRejected_1581) {
  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;

  const auto buf = makeBigEndianRw2LikeHeaderBuffer();

  EXPECT_ANY_THROW({
    (void)Exiv2::Rw2Parser::decode(exif, iptc, xmp, buf.data(), buf.size());
  });
}

// Boundary/robustness: non-null data with zero size should behave like empty input.
TEST_F(Rw2ParserTest_1581, Decode_NonNullDataWithZeroSize_Throws_1581) {
  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;
  Exiv2::XmpData xmp;

  std::vector<byte> buf;  // empty; data() may be non-null but size is 0

  EXPECT_ANY_THROW({
    (void)Exiv2::Rw2Parser::decode(exif, iptc, xmp, buf.data(), buf.size());
  });
}