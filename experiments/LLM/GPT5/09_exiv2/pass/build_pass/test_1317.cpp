// ============================================================================
// TEST_ID: 1317
// Unit tests for Exiv2::XmpParser::decode (black-box)
// File: ./TestProjects/exiv2/src/xmp.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <string>

#include <exiv2/error.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/xmp_exiv2.hpp>

namespace {

class XmpParserDecodeTest_1317 : public ::testing::Test {
 protected:
  // Prefer calling the member function directly (it is public in the provided interface).
  // This avoids ambiguity if a static overload/wrapper also exists in some builds.
  static int Decode(Exiv2::XmpData& xmpData, const std::string& packet) {
    Exiv2::XmpParser parser;
    return parser.decode(xmpData, packet);
  }

  static std::string MinimalValidXmpPacketWithCreatorTool(const std::string& value) {
    // A minimal, valid RDF/XMP packet with one simple property in the xmp namespace.
    // Keep it small and schema-standard to reduce environmental dependencies.
    std::string pkt;
    pkt += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    pkt += "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">\n";
    pkt += " <rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n";
    pkt += "  <rdf:Description xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\" ";
    pkt += "xmp:CreatorTool=\"";
    pkt += value;
    pkt += "\"/>\n";
    pkt += " </rdf:RDF>\n";
    pkt += "</x:xmpmeta>\n";
    return pkt;
  }
};

TEST_F(XmpParserDecodeTest_1317, EmptyPacketReturns0AndClearsData_1317) {
  Exiv2::XmpData xmp;

  // Pre-populate to verify decode() clears observable state.
  Exiv2::XmpKey preKey("Xmp.xmp.CreatorTool");
  Exiv2::XmpTextValue preVal;
  ASSERT_EQ(0, preVal.read("preexisting"));
  (void)xmp.add(preKey, &preVal);
  ASSERT_FALSE(xmp.empty());
  ASSERT_GT(xmp.count(), 0);

  const int rc = Decode(xmp, std::string{});
  EXPECT_EQ(0, rc);
  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0, xmp.count());
  EXPECT_EQ(std::string{}, xmp.xmpPacket());
}

TEST_F(XmpParserDecodeTest_1317, ValidPacketDecodesSimpleProperty_1317) {
  Exiv2::XmpData xmp;

  const std::string pkt = MinimalValidXmpPacketWithCreatorTool("UnitTestTool");
  const int rc = Decode(xmp, pkt);

  EXPECT_EQ(0, rc);
  EXPECT_EQ(pkt, xmp.xmpPacket());
  EXPECT_FALSE(xmp.empty());
  EXPECT_GE(xmp.count(), 1);

  // Verify we can find the expected key and its value is readable via public interface.
  Exiv2::XmpKey key("Xmp.xmp.CreatorTool");
  const auto it = xmp.findKey(key);
  ASSERT_NE(it, xmp.end());

  // Xmpdatum is part of the public API (used elsewhere in your suite); use its observable behavior.
  // If toString() returns the stored text, this should match.
  EXPECT_EQ(std::string("UnitTestTool"), it->toString());
}

TEST_F(XmpParserDecodeTest_1317, TrailingNullBytesAreIgnoredForParsing_1317) {
  Exiv2::XmpData xmp1;
  Exiv2::XmpData xmp2;

  const std::string base = MinimalValidXmpPacketWithCreatorTool("NullTrimTest");

  std::string withNulls = base;
  withNulls.push_back('\0');
  withNulls.push_back('\0');
  withNulls.push_back('\0');

  const int rc1 = Decode(xmp1, base);
  const int rc2 = Decode(xmp2, withNulls);

  EXPECT_EQ(0, rc1);
  EXPECT_EQ(0, rc2);

  // Packet should be stored exactly as given (observable via xmpPacket()).
  EXPECT_EQ(base, xmp1.xmpPacket());
  EXPECT_EQ(withNulls, xmp2.xmpPacket());

  // But decoded metadata should be equivalent for the property we set.
  Exiv2::XmpKey key("Xmp.xmp.CreatorTool");
  const auto it1 = xmp1.findKey(key);
  const auto it2 = xmp2.findKey(key);
  ASSERT_NE(it1, xmp1.end());
  ASSERT_NE(it2, xmp2.end());
  EXPECT_EQ(it1->toString(), it2->toString());
  EXPECT_EQ(std::string("NullTrimTest"), it1->toString());
}

TEST_F(XmpParserDecodeTest_1317, MalformedXmlThrowsExiv2Error_1317) {
  Exiv2::XmpData xmp;

  // Intentionally malformed XML (unclosed tag).
  const std::string badXml = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"><rdf:RDF>";

  // decode() does not advertise catching Exiv2::Error; malformed XML is expected to be observable
  // as an exception (black-box expectation).
  EXPECT_THROW(
      {
        (void)Decode(xmp, badXml);
      },
      Exiv2::Error);
}

TEST_F(XmpParserDecodeTest_1317, EmptyPacketDoesNotRequireInitializationAndDoesNotThrow_1317) {
  Exiv2::XmpData xmp;

  // Boundary: empty packet should short-circuit to 0 and be safe to call repeatedly.
  EXPECT_NO_THROW({
    EXPECT_EQ(0, Decode(xmp, std::string{}));
    EXPECT_EQ(0, Decode(xmp, std::string{}));
  });

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0, xmp.count());
  EXPECT_EQ(std::string{}, xmp.xmpPacket());
}

}  // namespace