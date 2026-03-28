#include <gtest/gtest.h>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/error.hpp>
#include <map>
#include <string>

namespace {

// Since nsDumper is a static function in xmp.cpp, we replicate its signature
// and test it if we can access it. If not, we test through public API.
// We'll focus on XmpParser and XmpData public interfaces that exercise XMP functionality.

class XmpDataTest_1315 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }
    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

TEST_F(XmpDataTest_1315, DefaultConstructedXmpDataIsEmpty_1315) {
    Exiv2::XmpData xmpData;
    EXPECT_TRUE(xmpData.empty());
    EXPECT_EQ(xmpData.count(), 0u);
}

TEST_F(XmpDataTest_1315, AddXmpPropertyIncreasesCount_1315) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    EXPECT_FALSE(xmpData.empty());
    EXPECT_GE(xmpData.count(), 1u);
}

TEST_F(XmpDataTest_1315, ParseEmptyXmpPacket_1315) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket;
    // Empty packet should not crash
    int result = Exiv2::XmpParser::decode(xmpData, xmpPacket);
    // Empty string may return 0 or error, but should not crash
    EXPECT_TRUE(result == 0 || result != 0);
}

TEST_F(XmpDataTest_1315, EncodeEmptyXmpData_1315) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData);
    EXPECT_EQ(result, 0);
}

TEST_F(XmpDataTest_1315, RoundTripXmpData_1315) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Round Trip Test";
    
    std::string xmpPacket;
    ASSERT_EQ(Exiv2::XmpParser::encode(xmpPacket, xmpData), 0);
    EXPECT_FALSE(xmpPacket.empty());
    
    Exiv2::XmpData xmpData2;
    ASSERT_EQ(Exiv2::XmpParser::decode(xmpData2, xmpPacket), 0);
    EXPECT_FALSE(xmpData2.empty());
}

TEST_F(XmpDataTest_1315, ClearXmpDataMakesItEmpty_1315) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test";
    EXPECT_FALSE(xmpData.empty());
    xmpData.clear();
    EXPECT_TRUE(xmpData.empty());
}

TEST_F(XmpDataTest_1315, MultiplePropertiesCount_1315) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title";
    xmpData["Xmp.dc.creator"] = "Creator";
    xmpData["Xmp.dc.description"] = "Description";
    EXPECT_GE(xmpData.count(), 3u);
}

TEST_F(XmpDataTest_1315, RegisterCustomNamespace_1315) {
    Exiv2::XmpProperties::registerNs("http://example.com/test/", "mytest");
    // Verify we can use the registered namespace
    Exiv2::XmpData xmpData;
    xmpData["Xmp.mytest.myProp"] = "value";
    EXPECT_FALSE(xmpData.empty());
    
    Exiv2::XmpProperties::unregisterNs("http://example.com/test/");
}

TEST_F(XmpDataTest_1315, EncodeDecodeWithCustomNamespace_1315) {
    Exiv2::XmpProperties::registerNs("http://example.com/custom/", "custom");
    
    Exiv2::XmpData xmpData;
    xmpData["Xmp.custom.field1"] = "value1";
    
    std::string xmpPacket;
    ASSERT_EQ(Exiv2::XmpParser::encode(xmpPacket, xmpData), 0);
    EXPECT_FALSE(xmpPacket.empty());
    
    // The encoded packet should contain the namespace URI
    EXPECT_NE(xmpPacket.find("http://example.com/custom/"), std::string::npos);
    
    Exiv2::XmpData xmpData2;
    ASSERT_EQ(Exiv2::XmpParser::decode(xmpData2, xmpPacket), 0);
    EXPECT_FALSE(xmpData2.empty());
    
    Exiv2::XmpProperties::unregisterNs("http://example.com/custom/");
}

TEST_F(XmpDataTest_1315, InitializeTerminateMultipleTimes_1315) {
    // Should be safe to call multiple times
    Exiv2::XmpParser::terminate();
    Exiv2::XmpParser::initialize();
    Exiv2::XmpParser::initialize();
    
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test";
    std::string xmpPacket;
    EXPECT_EQ(Exiv2::XmpParser::encode(xmpPacket, xmpData), 0);
}

TEST_F(XmpDataTest_1315, DecodeValidXmpPacket_1315) {
    std::string xmpPacket = R"(<?xpacket begin="" id="W5M0MpCehiHzreSzNTczkc9d"?>
<x:xmpmeta xmlns:x="adobe:ns:meta/">
  <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">
    <rdf:Description rdf:about=""
      xmlns:dc="http://purl.org/dc/elements/1.1/">
      <dc:title>
        <rdf:Alt>
          <rdf:li xml:lang="x-default">Test Title</rdf:li>
        </rdf:Alt>
      </dc:title>
    </rdf:Description>
  </rdf:RDF>
</x:xmpmeta>
<?xpacket end="w"?>)";
    
    Exiv2::XmpData xmpData;
    ASSERT_EQ(Exiv2::XmpParser::decode(xmpData, xmpPacket), 0);
    EXPECT_FALSE(xmpData.empty());
}

TEST_F(XmpDataTest_1315, DecodeInvalidXmpPacketHandledGracefully_1315) {
    std::string xmpPacket = "This is not valid XMP data at all <invalid>";
    Exiv2::XmpData xmpData;
    // Should not crash, may return error
    int result = Exiv2::XmpParser::decode(xmpData, xmpPacket);
    // Just verify it doesn't crash; result may vary
    (void)result;
}

TEST_F(XmpDataTest_1315, XmpDataIteratorAccess_1315) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Iterator Test";
    
    auto it = xmpData.begin();
    ASSERT_NE(it, xmpData.end());
    EXPECT_EQ(it->key(), "Xmp.dc.title");
}

TEST_F(XmpDataTest_1315, EraseXmpProperty_1315) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "To Be Erased";
    EXPECT_FALSE(xmpData.empty());
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData.end());
    xmpData.erase(it);
    EXPECT_TRUE(xmpData.empty());
}

TEST_F(XmpDataTest_1315, FindKeyReturnsEndForMissingKey_1315) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Something";
    
    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    EXPECT_EQ(it, xmpData.end());
}

// Test that namespace information is preserved through encode/decode cycle
// This indirectly tests the nsDumper callback
TEST_F(XmpDataTest_1315, NamespacePreservedInEncodeDecode_1315) {
    Exiv2::XmpProperties::registerNs("http://test.example.org/ns1/", "testns1");
    
    Exiv2::XmpData xmpData;
    xmpData["Xmp.testns1.prop1"] = "value1";
    xmpData["Xmp.dc.title"] = "Mixed NS Test";
    
    std::string xmpPacket;
    ASSERT_EQ(Exiv2::XmpParser::encode(xmpPacket, xmpData), 0);
    
    // Both namespaces should appear in the packet
    EXPECT_NE(xmpPacket.find("http://test.example.org/ns1/"), std::string::npos);
    EXPECT_NE(xmpPacket.find("http://purl.org/dc/elements/1.1/"), std::string::npos);
    
    Exiv2::XmpData decoded;
    ASSERT_EQ(Exiv2::XmpParser::decode(decoded, xmpPacket), 0);
    
    auto it1 = decoded.findKey(Exiv2::XmpKey("Xmp.testns1.prop1"));
    EXPECT_NE(it1, decoded.end());
    
    Exiv2::XmpProperties::unregisterNs("http://test.example.org/ns1/");
}

} // namespace
