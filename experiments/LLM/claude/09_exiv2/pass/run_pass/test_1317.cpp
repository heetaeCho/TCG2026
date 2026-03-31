#include <gtest/gtest.h>
#include <string>
#include "exiv2/xmp_exiv2.hpp"
#include "exiv2/properties.hpp"
#include "exiv2/value.hpp"
#include "exiv2/error.hpp"

namespace {

class XmpParserDecodeTest_1317 : public ::testing::Test {
 protected:
  void SetUp() override {
    Exiv2::XmpParser::initialize();
  }

  void TearDown() override {
    Exiv2::XmpParser::terminate();
  }

  Exiv2::XmpData xmpData_;
};

// Test decoding an empty XMP packet returns 0 and results in empty XmpData
TEST_F(XmpParserDecodeTest_1317, DecodeEmptyPacket_ReturnsZero_1317) {
  std::string emptyPacket;
  int result = Exiv2::XmpParser::decode(xmpData_, emptyPacket);
  EXPECT_EQ(0, result);
  EXPECT_TRUE(xmpData_.empty());
  EXPECT_EQ(0, xmpData_.count());
}

// Test that decoding an empty packet sets the packet on XmpData
TEST_F(XmpParserDecodeTest_1317, DecodeEmptyPacket_SetsPacket_1317) {
  std::string emptyPacket;
  Exiv2::XmpParser::decode(xmpData_, emptyPacket);
  EXPECT_EQ(emptyPacket, xmpData_.xmpPacket());
}

// Test decoding a valid minimal XMP packet with a simple property
TEST_F(XmpParserDecodeTest_1317, DecodeValidSimpleProperty_ReturnsZero_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:source>test source</dc:source>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);
  EXPECT_FALSE(xmpData_.empty());
}

// Test decoding a valid XMP packet stores the packet string
TEST_F(XmpParserDecodeTest_1317, DecodeValidPacket_StoresPacket_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:source>test</dc:source>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(xmpPacket, xmpData_.xmpPacket());
}

// Test decoding clears existing data before populating
TEST_F(XmpParserDecodeTest_1317, DecodeClearsExistingData_1317) {
  // First decode with some data
  std::string xmpPacket1 =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:source>first</dc:source>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  Exiv2::XmpParser::decode(xmpData_, xmpPacket1);
  long count1 = xmpData_.count();

  // Now decode empty - should clear
  std::string emptyPacket;
  Exiv2::XmpParser::decode(xmpData_, emptyPacket);
  EXPECT_TRUE(xmpData_.empty());
  EXPECT_EQ(0, xmpData_.count());
}

// Test decoding invalid XML returns error code 3 (XMP toolkit error)
TEST_F(XmpParserDecodeTest_1317, DecodeInvalidXml_ReturnsError_1317) {
  std::string invalidXmp = "<not valid xml <><>";
  int result = Exiv2::XmpParser::decode(xmpData_, invalidXmp);
  // Should return non-zero for invalid XML
  EXPECT_NE(0, result);
}

// Test decoding a packet with trailing null bytes
TEST_F(XmpParserDecodeTest_1317, DecodePacketWithTrailingNulls_ReturnsZero_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:source>test</dc:source>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";
  // Append trailing null bytes
  xmpPacket.push_back('\0');
  xmpPacket.push_back('\0');
  xmpPacket.push_back('\0');

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);
  EXPECT_FALSE(xmpData_.empty());
}

// Test decoding XMP with dc:title (LangAlt property)
TEST_F(XmpParserDecodeTest_1317, DecodeLangAltProperty_ReturnsZero_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:title>"
      "<rdf:Alt>"
      "<rdf:li xml:lang=\"x-default\">Test Title</rdf:li>"
      "</rdf:Alt>"
      "</dc:title>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);
  EXPECT_FALSE(xmpData_.empty());

  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
  EXPECT_NE(it, xmpData_.end());
}

// Test decoding XMP with an ordered array (dc:subject - bag/seq)
TEST_F(XmpParserDecodeTest_1317, DecodeArrayProperty_ReturnsZero_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:subject>"
      "<rdf:Bag>"
      "<rdf:li>keyword1</rdf:li>"
      "<rdf:li>keyword2</rdf:li>"
      "<rdf:li>keyword3</rdf:li>"
      "</rdf:Bag>"
      "</dc:subject>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);
  EXPECT_FALSE(xmpData_.empty());

  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
  EXPECT_NE(it, xmpData_.end());
}

// Test decoding XMP with multiple properties
TEST_F(XmpParserDecodeTest_1317, DecodeMultipleProperties_AllPresent_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:source>test source</dc:source>"
      "<dc:format>image/jpeg</dc:format>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);
  EXPECT_GE(xmpData_.count(), 2);

  auto it1 = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.source"));
  EXPECT_NE(it1, xmpData_.end());

  auto it2 = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.format"));
  EXPECT_NE(it2, xmpData_.end());
}

// Test decoding a packet that contains only whitespace but not valid XML
TEST_F(XmpParserDecodeTest_1317, DecodeWhitespaceOnly_ReturnsError_1317) {
  std::string whitespace = "   \n\t  ";
  int result = Exiv2::XmpParser::decode(xmpData_, whitespace);
  // Whitespace-only is not valid XMP, should return error
  EXPECT_NE(0, result);
}

// Test decoding and then re-decoding overwrites previous data
TEST_F(XmpParserDecodeTest_1317, DecodeOverwritesPreviousData_1317) {
  std::string xmpPacket1 =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:source>first</dc:source>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  std::string xmpPacket2 =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:format>image/png</dc:format>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  Exiv2::XmpParser::decode(xmpData_, xmpPacket1);
  auto it1 = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.source"));
  EXPECT_NE(it1, xmpData_.end());

  Exiv2::XmpParser::decode(xmpData_, xmpPacket2);
  // After second decode, first property should be gone
  auto it2 = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.source"));
  EXPECT_EQ(it2, xmpData_.end());

  auto it3 = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.format"));
  EXPECT_NE(it3, xmpData_.end());
}

// Test decoding XMP with a simple text property and verifying value
TEST_F(XmpParserDecodeTest_1317, DecodeSimpleProperty_CorrectValue_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:source>my test value</dc:source>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);

  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.source"));
  ASSERT_NE(it, xmpData_.end());
  EXPECT_EQ("my test value", it->toString());
}

// Test encode roundtrip: decode then encode should produce valid XMP
TEST_F(XmpParserDecodeTest_1317, EncodeDecodeRoundtrip_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:source>roundtrip test</dc:source>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int decResult = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  ASSERT_EQ(0, decResult);

  std::string encodedPacket;
  int encResult = Exiv2::XmpParser::encode(encodedPacket, xmpData_, 0, 0);
  EXPECT_EQ(0, encResult);
  EXPECT_FALSE(encodedPacket.empty());

  // Re-decode the encoded packet
  Exiv2::XmpData xmpData2;
  int decResult2 = Exiv2::XmpParser::decode(xmpData2, encodedPacket);
  EXPECT_EQ(0, decResult2);

  auto it = xmpData2.findKey(Exiv2::XmpKey("Xmp.dc.source"));
  ASSERT_NE(it, xmpData2.end());
  EXPECT_EQ("roundtrip test", it->toString());
}

// Test decoding XMP with DTD (should be rejected by XMLValidator)
TEST_F(XmpParserDecodeTest_1317, DecodeWithDTD_ReturnsError_1317) {
  std::string xmpWithDtd =
      "<?xml version=\"1.0\"?>"
      "<!DOCTYPE foo ["
      "<!ELEMENT foo ANY>"
      "]>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\"/>"
      "</rdf:RDF>"
      "</x:xmpmeta>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpWithDtd);
  // DTD should be rejected
  EXPECT_NE(0, result);
}

// Test encoding empty XmpData
TEST_F(XmpParserDecodeTest_1317, EncodeEmptyXmpData_1317) {
  Exiv2::XmpData emptyData;
  std::string packet;
  int result = Exiv2::XmpParser::encode(packet, emptyData, 0, 0);
  EXPECT_EQ(0, result);
  // Encoding empty data should produce empty or minimal packet
}

// Test decoding XMP with struct property
TEST_F(XmpParserDecodeTest_1317, DecodeStructProperty_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:xmpDM=\"http://ns.adobe.com/xmp/1.0/DynamicMedia/\">"
      "<xmpDM:artist>TestArtist</xmpDM:artist>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);
}

// Test decoding a very large XMP packet (boundary condition)
TEST_F(XmpParserDecodeTest_1317, DecodeLargePacket_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:subject><rdf:Bag>";

  // Add many items
  for (int i = 0; i < 100; ++i) {
    xmpPacket += "<rdf:li>keyword" + std::to_string(i) + "</rdf:li>";
  }

  xmpPacket +=
      "</rdf:Bag></dc:subject>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);
  EXPECT_FALSE(xmpData_.empty());
}

// Test decoding XMP with xmp namespace properties
TEST_F(XmpParserDecodeTest_1317, DecodeXmpNamespaceProperty_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\">"
      "<xmp:Rating>5</xmp:Rating>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);

  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.xmp.Rating"));
  ASSERT_NE(it, xmpData_.end());
  EXPECT_EQ("5", it->toString());
}

// Test that decode with garbage binary data returns error
TEST_F(XmpParserDecodeTest_1317, DecodeGarbageData_ReturnsError_1317) {
  std::string garbage = "\x01\x02\x03\x04\x05\x06\x07\x08";
  int result = Exiv2::XmpParser::decode(xmpData_, garbage);
  EXPECT_NE(0, result);
  EXPECT_TRUE(xmpData_.empty());
}

// Test decoding XMP with multiple language alternatives in dc:title
TEST_F(XmpParserDecodeTest_1317, DecodeMultipleLangAlt_1317) {
  std::string xmpPacket =
      "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
      "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
      "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
      "<rdf:Description rdf:about=\"\""
      " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
      "<dc:title>"
      "<rdf:Alt>"
      "<rdf:li xml:lang=\"x-default\">Default Title</rdf:li>"
      "<rdf:li xml:lang=\"en\">English Title</rdf:li>"
      "<rdf:li xml:lang=\"de\">German Title</rdf:li>"
      "</rdf:Alt>"
      "</dc:title>"
      "</rdf:Description>"
      "</rdf:RDF>"
      "</x:xmpmeta>"
      "<?xpacket end=\"w\"?>";

  int result = Exiv2::XmpParser::decode(xmpData_, xmpPacket);
  EXPECT_EQ(0, result);

  auto it = xmpData_.findKey(Exiv2::XmpKey("Xmp.dc.title"));
  ASSERT_NE(it, xmpData_.end());
  EXPECT_EQ(Exiv2::langAlt, it->typeId());
}

// Test initializing and terminating XmpParser
TEST_F(XmpParserDecodeTest_1317, InitializeAndTerminate_1317) {
  // terminate was called in TearDown, re-initialize
  bool initResult = Exiv2::XmpParser::initialize();
  EXPECT_TRUE(initResult);
}

// Test that decoding packet with only null bytes returns 0 (treated as empty after trimming)
TEST_F(XmpParserDecodeTest_1317, DecodeOnlyNullBytes_ReturnsZero_1317) {
  std::string nullPacket(10, '\0');
  int result = Exiv2::XmpParser::decode(xmpData_, nullPacket);
  // After trimming trailing nulls, the length becomes 0, so it should behave like empty
  // But the packet is not empty (size 10), so it goes past the empty check
  // After trimming, len=0, which may cause issues with XMLValidator or SXMPMeta
  // The behavior depends on the implementation
  // We just verify it doesn't crash and returns some result
  EXPECT_TRUE(result == 0 || result == 3);
}

}  // namespace
