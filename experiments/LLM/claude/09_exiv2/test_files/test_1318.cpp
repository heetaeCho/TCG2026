#include <gtest/gtest.h>
#include <string>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>

namespace {

class XmpParserEncodeTest_1318 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize(nullptr, nullptr);
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test encoding empty XmpData clears the packet and returns 0
TEST_F(XmpParserEncodeTest_1318, EncodeEmptyXmpDataReturnsZeroAndClearsPacket_1318) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket = "some existing content";
    
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_TRUE(xmpPacket.empty());
}

// Test encoding XmpData with a simple xmpText property
TEST_F(XmpParserEncodeTest_1318, EncodeSimpleXmpTextProperty_1318) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
    // The packet should contain the value we set
    EXPECT_NE(std::string::npos, xmpPacket.find("Test Title"));
}

// Test encoding XmpData with multiple properties
TEST_F(XmpParserEncodeTest_1318, EncodeMultipleProperties_1318) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.subject"] = "Subject1";
    xmpData["Xmp.dc.creator"] = "Creator1";
    
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
}

// Test encoding and then decoding produces consistent data
TEST_F(XmpParserEncodeTest_1318, EncodeDecodeRoundTrip_1318) {
    Exiv2::XmpData xmpDataOriginal;
    xmpDataOriginal["Xmp.dc.description"] = "A test description";
    
    std::string xmpPacket;
    int encodeResult = Exiv2::XmpParser::encode(xmpPacket, xmpDataOriginal, 0, 0);
    EXPECT_EQ(0, encodeResult);
    EXPECT_FALSE(xmpPacket.empty());
    
    Exiv2::XmpData xmpDataDecoded;
    int decodeResult = Exiv2::XmpParser::decode(xmpDataDecoded, xmpPacket);
    EXPECT_EQ(0, decodeResult);
    EXPECT_FALSE(xmpDataDecoded.empty());
}

// Test encoding with padding parameter
TEST_F(XmpParserEncodeTest_1318, EncodeWithPadding_1318) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Padded Title";
    
    std::string xmpPacketNoPadding;
    int result1 = Exiv2::XmpParser::encode(xmpPacketNoPadding, xmpData, 0, 0);
    EXPECT_EQ(0, result1);
    
    std::string xmpPacketWithPadding;
    int result2 = Exiv2::XmpParser::encode(xmpPacketWithPadding, xmpData, 0, 2048);
    EXPECT_EQ(0, result2);
    
    // Both should be valid but padding version may be larger or equal
    EXPECT_FALSE(xmpPacketNoPadding.empty());
    EXPECT_FALSE(xmpPacketWithPadding.empty());
}

// Test encoding with LangAlt value
TEST_F(XmpParserEncodeTest_1318, EncodeLangAltValue_1318) {
    Exiv2::XmpData xmpData;
    
    Exiv2::XmpKey key("Xmp.dc.title");
    Exiv2::LangAltValue langAltVal;
    langAltVal.read("lang=\"x-default\" My LangAlt Title");
    xmpData.add(key, &langAltVal);
    
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
    EXPECT_NE(std::string::npos, xmpPacket.find("My LangAlt Title"));
}

// Test encoding xmpBag type
TEST_F(XmpParserEncodeTest_1318, EncodeXmpBagProperty_1318) {
    Exiv2::XmpData xmpData;
    
    Exiv2::XmpKey key("Xmp.dc.subject");
    Exiv2::XmpTextValue val;
    val.setXmpArrayType(Exiv2::XmpValue::xaBag);
    val.read("keyword1");
    xmpData.add(key, &val);
    
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
}

// Test that encoding empty XmpData always returns 0 regardless of flags
TEST_F(XmpParserEncodeTest_1318, EncodeEmptyXmpDataIgnoresFlags_1318) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket;
    
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0xFFFF, 4096);
    
    EXPECT_EQ(0, result);
    EXPECT_TRUE(xmpPacket.empty());
}

// Test encoding clears pre-existing packet content when XmpData is empty
TEST_F(XmpParserEncodeTest_1318, EncodeEmptyClearsExistingPacket_1318) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket = "<xml>some old data</xml>";
    
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_TRUE(xmpPacket.empty());
}

// Test encoding with xmpText property having empty value
TEST_F(XmpParserEncodeTest_1318, EncodeXmpTextEmptyValue_1318) {
    Exiv2::XmpData xmpData;
    
    Exiv2::XmpKey key("Xmp.dc.format");
    Exiv2::XmpTextValue val;
    // Don't read any value, so count == 0
    xmpData.add(key, &val);
    
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
}

// Test encoding produces valid XML output
TEST_F(XmpParserEncodeTest_1318, EncodeProducesValidXmlOutput_1318) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.creator"] = "John Doe";
    
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
    // Check for XML header markers
    EXPECT_NE(std::string::npos, xmpPacket.find("<?xpacket"));
    EXPECT_NE(std::string::npos, xmpPacket.find("xpacket end"));
}

// Test that decode of the encoded packet preserves xmpText values
TEST_F(XmpParserEncodeTest_1318, EncodeDecodePreservesXmpTextValue_1318) {
    Exiv2::XmpData xmpDataOrig;
    xmpDataOrig["Xmp.dc.format"] = "image/jpeg";
    
    std::string xmpPacket;
    int encResult = Exiv2::XmpParser::encode(xmpPacket, xmpDataOrig, 0, 0);
    EXPECT_EQ(0, encResult);
    
    Exiv2::XmpData xmpDataDecoded;
    int decResult = Exiv2::XmpParser::decode(xmpDataDecoded, xmpPacket);
    EXPECT_EQ(0, decResult);
    
    auto it = xmpDataDecoded.findKey(Exiv2::XmpKey("Xmp.dc.format"));
    ASSERT_NE(it, xmpDataDecoded.end());
    EXPECT_EQ("image/jpeg", it->toString());
}

// Test encoding replaces packet content with non-empty XmpData
TEST_F(XmpParserEncodeTest_1318, EncodeReplacesExistingPacketContent_1318) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "New Title";
    
    std::string xmpPacket = "old content that should be replaced";
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_NE(std::string::npos, xmpPacket.find("New Title"));
    EXPECT_EQ(std::string::npos, xmpPacket.find("old content that should be replaced"));
}

// Test decode of empty string
TEST_F(XmpParserEncodeTest_1318, DecodeEmptyString_1318) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket;
    
    int result = Exiv2::XmpParser::decode(xmpData, xmpPacket);
    
    EXPECT_EQ(0, result);
    EXPECT_TRUE(xmpData.empty());
}

// Test encoding xmpSeq type
TEST_F(XmpParserEncodeTest_1318, EncodeXmpSeqProperty_1318) {
    Exiv2::XmpData xmpData;
    
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::XmpTextValue val;
    val.setXmpArrayType(Exiv2::XmpValue::xaSeq);
    val.read("Author1");
    xmpData.add(key, &val);
    
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
}

// Test encoding with registered custom namespace
TEST_F(XmpParserEncodeTest_1318, EncodeWithCustomNamespace_1318) {
    Exiv2::XmpProperties::registerNs("http://example.com/test/", "mytest");
    
    Exiv2::XmpData xmpData;
    xmpData["Xmp.mytest.CustomProp"] = "CustomValue";
    
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
    EXPECT_NE(std::string::npos, xmpPacket.find("CustomValue"));
    
    Exiv2::XmpProperties::unregisterNs("http://example.com/test/");
}

// Test LangAlt with multiple languages
TEST_F(XmpParserEncodeTest_1318, EncodeLangAltMultipleLanguages_1318) {
    Exiv2::XmpData xmpData;
    
    Exiv2::XmpKey key("Xmp.dc.description");
    Exiv2::LangAltValue langAltVal;
    langAltVal.read("lang=\"x-default\" Default description");
    // The LangAltValue stores values in its map
    xmpData.add(key, &langAltVal);
    
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
    EXPECT_NE(std::string::npos, xmpPacket.find("Default description"));
}

}  // namespace
