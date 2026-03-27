// -----------------------------------------------------------------------------
// Unit tests for Exiv2::IptcParser::encode
// File: test_iptc_parser_encode_704.cpp
// -----------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <cstring>
#include <string>

#include "exiv2/iptc.hpp"
#include "exiv2/types.hpp"

namespace {

class IptcParserEncodeTest_704 : public ::testing::Test {
 protected:
  static Exiv2::IptcData MakeSimpleIptcData() {
    Exiv2::IptcData iptc;
    // Use common, well-known IPTC keys that exist in Exiv2.
    iptc["Iptc.Application2.ObjectName"] = std::string("Example Object");
    iptc["Iptc.Application2.Caption"] = std::string("Example caption");
    // A key from a different record (Envelope vs Application2) to exercise ordering across records.
    iptc["Iptc.Envelope.ModelVersion"] = static_cast<uint16_t>(4);
    return iptc;
  }

  static bool DataBufEquals(const Exiv2::DataBuf& a, const Exiv2::DataBuf& b) {
    if (a.size() != b.size()) return false;
    if (a.size() == 0) return true;
    return std::memcmp(a.c_data(0), b.c_data(0), a.size()) == 0;
  }
};

TEST_F(IptcParserEncodeTest_704, EncodeEmptyReturnsEmptyBuffer_704) {
  Exiv2::IptcData empty;
  ASSERT_TRUE(empty.empty());

  const Exiv2::DataBuf buf = Exiv2::IptcParser::encode(empty);

  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(buf.size(), 0u);
}

TEST_F(IptcParserEncodeTest_704, EncodeNonEmptyReturnsNonEmptyAndSizeMatchesIptcDataSize_704) {
  Exiv2::IptcData iptc = MakeSimpleIptcData();
  ASSERT_FALSE(iptc.empty());

  const size_t expectedSize = iptc.size();
  const Exiv2::DataBuf buf = Exiv2::IptcParser::encode(iptc);

  EXPECT_FALSE(buf.empty());
  EXPECT_EQ(buf.size(), expectedSize);
}

TEST_F(IptcParserEncodeTest_704, EncodeIsDeterministicForSameLogicalContent_704) {
  // Same fields, assigned in the same order -> byte-for-byte deterministic.
  Exiv2::IptcData iptc1 = MakeSimpleIptcData();
  Exiv2::IptcData iptc2 = MakeSimpleIptcData();

  const Exiv2::DataBuf buf1 = Exiv2::IptcParser::encode(iptc1);
  const Exiv2::DataBuf buf2 = Exiv2::IptcParser::encode(iptc2);

  EXPECT_TRUE(DataBufEquals(buf1, buf2));
}

TEST_F(IptcParserEncodeTest_704, EncodeOutputIndependentOfInsertionOrderAcrossRecords_704) {
  // Construct two IptcData instances with the same logical content but inserted in different order.
  Exiv2::IptcData a;
  a["Iptc.Application2.ObjectName"] = std::string("Obj");
  a["Iptc.Envelope.ModelVersion"] = static_cast<uint16_t>(4);
  a["Iptc.Application2.Caption"] = std::string("Cap");

  Exiv2::IptcData b;
  b["Iptc.Envelope.ModelVersion"] = static_cast<uint16_t>(4);
  b["Iptc.Application2.Caption"] = std::string("Cap");
  b["Iptc.Application2.ObjectName"] = std::string("Obj");

  const Exiv2::DataBuf bufA = Exiv2::IptcParser::encode(a);
  const Exiv2::DataBuf bufB = Exiv2::IptcParser::encode(b);

  // Observable behavior: encoding should be deterministic for same logical content.
  EXPECT_TRUE(DataBufEquals(bufA, bufB));
}

TEST_F(IptcParserEncodeTest_704, EncodeThenDecodeRoundTripPreservesValues_704) {
  Exiv2::IptcData original = MakeSimpleIptcData();

  const Exiv2::DataBuf encoded = Exiv2::IptcParser::encode(original);
  ASSERT_FALSE(encoded.empty());

  Exiv2::IptcData decoded;
  const int rc = Exiv2::IptcParser::decode(decoded, encoded.c_data(0), encoded.size());
  EXPECT_EQ(rc, 0);

  // Verify observable values through the public interface.
  EXPECT_EQ(decoded["Iptc.Application2.ObjectName"].toString(),
            original["Iptc.Application2.ObjectName"].toString());
  EXPECT_EQ(decoded["Iptc.Application2.Caption"].toString(),
            original["Iptc.Application2.Caption"].toString());
  EXPECT_EQ(decoded["Iptc.Envelope.ModelVersion"].toString(),
            original["Iptc.Envelope.ModelVersion"].toString());
}

TEST_F(IptcParserEncodeTest_704, EncodeWithLargeValueDoesNotThrowAndReturnsBuffer_704) {
  Exiv2::IptcData iptc;
  // Large payload to stress boundary behavior; the exact internal encoding is treated as a black box.
  const std::string largeText(40000, 'x');
  iptc["Iptc.Application2.Caption"] = largeText;

  EXPECT_NO_THROW({
    const Exiv2::DataBuf buf = Exiv2::IptcParser::encode(iptc);
    EXPECT_FALSE(buf.empty());
    EXPECT_EQ(buf.size(), iptc.size());
  });
}

}  // namespace