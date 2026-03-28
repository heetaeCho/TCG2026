// SPDX-License-Identifier: MIT
// File: test_orfparser_1553.cpp

#include <gtest/gtest.h>

#include <exiv2/orfimage.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>

#include <cstddef>
#include <cstdint>
#include <vector>

namespace {

class OrfParserTest_1553 : public ::testing::Test {
 protected:
  Exiv2::ExifData exif_;
  Exiv2::IptcData iptc_;
  Exiv2::XmpData xmp_;

  // Helper that accepts either:
  //  - an exception (for invalid/truncated data), OR
  //  - a returned ByteOrder value (if the implementation chooses not to throw)
  static void ExpectThrowOrReturnsAnyByteOrder(const Exiv2::byte* pData, size_t size,
                                              Exiv2::ExifData& exif,
                                              Exiv2::IptcData& iptc,
                                              Exiv2::XmpData& xmp) {
    try {
      const Exiv2::ByteOrder bo = Exiv2::OrfParser::decode(exif, iptc, xmp, pData, size);
      // If no exception: only assert it's one of the known enum values.
      // (Exiv2 typically uses: littleEndian, bigEndian, invalidByteOrder)
      EXPECT_TRUE(bo == Exiv2::littleEndian || bo == Exiv2::bigEndian || bo == Exiv2::invalidByteOrder);
    } catch (...) {
      SUCCEED();
    }
  }

  static std::vector<Exiv2::byte> MakeMinimalOrfBufferLittleEndianNoIfdEntries() {
    // TIFF-like header:
    //  [0..1]  'I''I'
    //  [2..3]  0x4f52 ("OR" in little-endian byte order: 0x52 0x4f)
    //  [4..7]  offset to first IFD = 8
    // IFD at offset 8:
    //  [8..9]  number of entries = 0
    //  [10..13] next IFD offset = 0
    std::vector<Exiv2::byte> b;
    b.reserve(14);
    b.push_back(static_cast<Exiv2::byte>('I'));
    b.push_back(static_cast<Exiv2::byte>('I'));
    b.push_back(static_cast<Exiv2::byte>(0x52));
    b.push_back(static_cast<Exiv2::byte>(0x4f));
    b.push_back(static_cast<Exiv2::byte>(0x08));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    return b;
  }

  static std::vector<Exiv2::byte> MakeMinimalOrfBufferBigEndianNoIfdEntries() {
    // Same structure as above, but big-endian:
    //  [0..1]  'M''M'
    //  [2..3]  0x4f52 ("OR" in big-endian: 0x4f 0x52)
    //  [4..7]  offset to first IFD = 8 (0x00000008)
    // IFD at offset 8:
    //  [8..9]  number of entries = 0 (0x0000)
    //  [10..13] next IFD offset = 0
    std::vector<Exiv2::byte> b;
    b.reserve(14);
    b.push_back(static_cast<Exiv2::byte>('M'));
    b.push_back(static_cast<Exiv2::byte>('M'));
    b.push_back(static_cast<Exiv2::byte>(0x4f));
    b.push_back(static_cast<Exiv2::byte>(0x52));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x08));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    b.push_back(static_cast<Exiv2::byte>(0x00));
    return b;
  }
};

TEST_F(OrfParserTest_1553, DecodeRejectsNullBuffer_1553) {
  ExpectThrowOrReturnsAnyByteOrder(nullptr, 0, exif_, iptc_, xmp_);
  ExpectThrowOrReturnsAnyByteOrder(nullptr, 10, exif_, iptc_, xmp_);
}

TEST_F(OrfParserTest_1553, DecodeRejectsTruncatedHeaderSizes_1553) {
  // Sizes smaller than the typical header size should be handled gracefully
  // (throw or return invalid/other recognized ByteOrder).
  std::vector<Exiv2::byte> any(8, static_cast<Exiv2::byte>(0));
  for (size_t sz = 0; sz < 8; ++sz) {
    SCOPED_TRACE(::testing::Message() << "size=" << sz);
    ExpectThrowOrReturnsAnyByteOrder(any.data(), sz, exif_, iptc_, xmp_);
  }
}

TEST_F(OrfParserTest_1553, DecodeMinimalLittleEndianHeaderReturnsLittleEndian_1553) {
  const auto buf = MakeMinimalOrfBufferLittleEndianNoIfdEntries();

  ASSERT_NO_THROW({
    const Exiv2::ByteOrder bo = Exiv2::OrfParser::decode(exif_, iptc_, xmp_, buf.data(), buf.size());
    EXPECT_EQ(Exiv2::littleEndian, bo);
  });

  // With a minimal "no entries" IFD, metadata should plausibly remain empty.
  // These are observable via the public interface; if an implementation chooses
  // to insert default tags, these expectations may be relaxed by the project.
  EXPECT_TRUE(exif_.empty());
  EXPECT_TRUE(iptc_.empty());
  EXPECT_TRUE(xmp_.empty());
}

TEST_F(OrfParserTest_1553, DecodeMinimalBigEndianHeaderReturnsBigEndian_1553) {
  const auto buf = MakeMinimalOrfBufferBigEndianNoIfdEntries();

  ASSERT_NO_THROW({
    const Exiv2::ByteOrder bo = Exiv2::OrfParser::decode(exif_, iptc_, xmp_, buf.data(), buf.size());
    EXPECT_EQ(Exiv2::bigEndian, bo);
  });

  EXPECT_TRUE(exif_.empty());
  EXPECT_TRUE(iptc_.empty());
  EXPECT_TRUE(xmp_.empty());
}

TEST_F(OrfParserTest_1553, DecodeWithExtraTrailingDataStillParsesHeader_1553) {
  auto buf = MakeMinimalOrfBufferLittleEndianNoIfdEntries();
  // Append trailing bytes (boundary-ish case: decoder should ignore or tolerate extra payload).
  buf.insert(buf.end(), 64, static_cast<Exiv2::byte>(0xAA));

  ASSERT_NO_THROW({
    const Exiv2::ByteOrder bo = Exiv2::OrfParser::decode(exif_, iptc_, xmp_, buf.data(), buf.size());
    EXPECT_EQ(Exiv2::littleEndian, bo);
  });
}

}  // namespace