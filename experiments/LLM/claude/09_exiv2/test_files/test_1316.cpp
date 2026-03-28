#include <gtest/gtest.h>
#include <string>
#include <sstream>

#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/xmpdata.hpp>
#include <exiv2/value.hpp>

namespace {

class XmpParserTest_1316 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test: Initialize returns true on first call
TEST_F(XmpParserTest_1316, InitializeReturnsTrue_1316) {
    // terminate first to reset state
    Exiv2::XmpParser::terminate();
    bool result = Exiv2::XmpParser::initialize();
    EXPECT_TRUE(result);
}

// Test: Initialize can be called multiple times without error
TEST_F(XmpParserTest_1316, InitializeMultipleTimes_1316) {
    bool result1 = Exiv2::XmpParser::initialize();
    bool result2 = Exiv2::XmpParser::initialize();
    // Both should succeed (or at least not crash)
    EXPECT_TRUE(result1);
    EXPECT_TRUE(result2);
}

// Test: Terminate does not crash when called after initialize
TEST_F(XmpParserTest_1316, TerminateAfterInitialize_1316) {
    Exiv2::XmpParser::initialize();
    EXPECT_NO_THROW(Exiv2::XmpParser::terminate());
}

// Test: Terminate can be called multiple times without error
TEST_F(XmpParserTest_1316, TerminateMultipleTimes_1316) {
    EXPECT_NO_THROW(Exiv2::XmpParser::terminate());
    EXPECT_NO_THROW(Exiv2::XmpParser::terminate());
}

// Test: Decode with empty XMP packet returns 0 and empty XmpData
TEST_F(XmpParserTest_1316, DecodeEmptyPacket_1316) {
    Exiv2::XmpData xmpData;
    std::string emptyPacket;
    int result = Exiv2::XmpParser::decode(xmpData, emptyPacket);
    EXPECT_EQ(0, result);
    EXPECT_TRUE(xmpData.empty());
}

// Test: Decode with valid XMP packet
TEST_F(XmpParserTest_1316, DecodeValidXmpPacket_1316) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket =
        "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:description>"
        "<rdf:Alt><rdf:li xml:lang=\"x-default\">Test description</rdf:li></rdf:Alt>"
        "</dc:description>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";
    int result = Exiv2::XmpParser::decode(xmpData, xmpPacket);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpData.empty());
}

// Test: Encode with empty XmpData produces empty or minimal packet
TEST_F(XmpParserTest_1316, EncodeEmptyXmpData_1316) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    EXPECT_EQ(0, result);
    // Empty XmpData should produce empty packet
    EXPECT_TRUE(xmpPacket.empty());
}

// Test: Decode then encode roundtrip
TEST_F(XmpParserTest_1316, DecodeEncodeRoundtrip_1316) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket =
        "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:creator>"
        "<rdf:Seq><rdf:li>Author Name</rdf:li></rdf:Seq>"
        "</dc:creator>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    int decResult = Exiv2::XmpParser::decode(xmpData, xmpPacket);
    EXPECT_EQ(0, decResult);
    EXPECT_FALSE(xmpData.empty());

    std::string encodedPacket;
    int encResult = Exiv2::XmpParser::encode(encodedPacket, xmpData, 0, 0);
    EXPECT_EQ(0, encResult);
    EXPECT_FALSE(encodedPacket.empty());

    // Decode the encoded packet and verify same data
    Exiv2::XmpData xmpData2;
    int decResult2 = Exiv2::XmpParser::decode(xmpData2, encodedPacket);
    EXPECT_EQ(0, decResult2);
    EXPECT_EQ(xmpData.count(), xmpData2.count());
}

// Test: Decode with malformed XMP packet
TEST_F(XmpParserTest_1316, DecodeMalformedPacket_1316) {
    Exiv2::XmpData xmpData;
    std::string malformedPacket = "This is not valid XMP at all <><><>";
    int result = Exiv2::XmpParser::decode(xmpData, malformedPacket);
    // Malformed XMP may return non-zero or still succeed partially
    // The key is it shouldn't crash
    (void)result;
}

// Test: Initialize with nullptr lock function
TEST_F(XmpParserTest_1316, InitializeWithNullLock_1316) {
    Exiv2::XmpParser::terminate();
    bool result = Exiv2::XmpParser::initialize(nullptr, nullptr);
    EXPECT_TRUE(result);
}

class XmpPropertiesTest_1316 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test: Register and lookup a custom namespace
TEST_F(XmpPropertiesTest_1316, RegisterCustomNamespace_1316) {
    const std::string ns = "http://example.com/test/1316/";
    const std::string prefix = "testns1316";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    std::string resultPrefix = Exiv2::XmpProperties::prefix(ns);
    EXPECT_EQ(prefix, resultPrefix);

    std::string resultNs = Exiv2::XmpProperties::ns(prefix);
    EXPECT_EQ(ns, resultNs);

    // Cleanup
    Exiv2::XmpProperties::unregisterNs(ns);
}

// Test: Unregister a custom namespace
TEST_F(XmpPropertiesTest_1316, UnregisterCustomNamespace_1316) {
    const std::string ns = "http://example.com/test/unreg1316/";
    const std::string prefix = "unreg1316";

    Exiv2::XmpProperties::registerNs(ns, prefix);
    std::string resultPrefix = Exiv2::XmpProperties::prefix(ns);
    EXPECT_EQ(prefix, resultPrefix);

    Exiv2::XmpProperties::unregisterNs(ns);

    // After unregistering, prefix lookup should fail or return empty
    std::string resultAfter = Exiv2::XmpProperties::prefix(ns);
    EXPECT_TRUE(resultAfter.empty());
}

// Test: Unregister all custom namespaces
TEST_F(XmpPropertiesTest_1316, UnregisterAllNamespaces_1316) {
    const std::string ns1 = "http://example.com/test/all1_1316/";
    const std::string prefix1 = "all1ns1316";
    const std::string ns2 = "http://example.com/test/all2_1316/";
    const std::string prefix2 = "all2ns1316";

    Exiv2::XmpProperties::registerNs(ns1, prefix1);
    Exiv2::XmpProperties::registerNs(ns2, prefix2);

    Exiv2::XmpProperties::unregisterNs();

    std::string result1 = Exiv2::XmpProperties::prefix(ns1);
    std::string result2 = Exiv2::XmpProperties::prefix(ns2);
    EXPECT_TRUE(result1.empty());
    EXPECT_TRUE(result2.empty());
}

// Test: Get registered namespaces dictionary
TEST_F(XmpPropertiesTest_1316, RegisteredNamespaces_1316) {
    const std::string ns = "http://example.com/test/dict1316/";
    const std::string prefix = "dict1316";

    Exiv2::XmpProperties::registerNs(ns, prefix);

    Exiv2::Dictionary nsDict;
    Exiv2::XmpProperties::registeredNamespaces(nsDict);

    // The registered namespace should appear in the dictionary
    auto it = nsDict.find(prefix);
    EXPECT_NE(it, nsDict.end());
    if (it != nsDict.end()) {
        EXPECT_EQ(ns, it->second);
    }

    Exiv2::XmpProperties::unregisterNs(ns);
}

// Test: Known namespace prefix (dc) returns correct namespace URI
TEST_F(XmpPropertiesTest_1316, KnownDcNamespace_1316) {
    std::string dcNs = Exiv2::XmpProperties::ns("dc");
    EXPECT_EQ("http://purl.org/dc/elements/1.1/", dcNs);
}

// Test: Known namespace URI returns correct prefix
TEST_F(XmpPropertiesTest_1316, KnownDcPrefix_1316) {
    std::string prefix = Exiv2::XmpProperties::prefix("http://purl.org/dc/elements/1.1/");
    EXPECT_EQ("dc", prefix);
}

// Test: nsInfo for known prefix returns non-null
TEST_F(XmpPropertiesTest_1316, NsInfoForKnownPrefix_1316) {
    const Exiv2::XmpNsInfo* info = Exiv2::XmpProperties::nsInfo("dc");
    EXPECT_NE(nullptr, info);
}

// Test: propertyList for known prefix returns non-null
TEST_F(XmpPropertiesTest_1316, PropertyListForKnownPrefix_1316) {
    const Exiv2::XmpPropertyInfo* propList = Exiv2::XmpProperties::propertyList("dc");
    EXPECT_NE(nullptr, propList);
}

// Test: nsDesc for known prefix returns non-null description
TEST_F(XmpPropertiesTest_1316, NsDescForKnownPrefix_1316) {
    const char* desc = Exiv2::XmpProperties::nsDesc("dc");
    EXPECT_NE(nullptr, desc);
    EXPECT_GT(strlen(desc), 0u);
}

// Test: Prefix for unknown namespace returns empty string
TEST_F(XmpPropertiesTest_1316, PrefixForUnknownNamespace_1316) {
    std::string prefix = Exiv2::XmpProperties::prefix("http://nonexistent.example.com/");
    EXPECT_TRUE(prefix.empty());
}

// Test: Namespace for unknown prefix returns empty string
TEST_F(XmpPropertiesTest_1316, NsForUnknownPrefix_1316) {
    std::string ns = Exiv2::XmpProperties::ns("nonexistentprefix");
    EXPECT_TRUE(ns.empty());
}

// Test: XmpKey property type for a known dc property
TEST_F(XmpPropertiesTest_1316, PropertyTypeForDcCreator_1316) {
    Exiv2::XmpKey key("Xmp.dc.creator");
    Exiv2::TypeId type = Exiv2::XmpProperties::propertyType(key);
    EXPECT_EQ(Exiv2::xmpSeq, type);
}

// Test: XmpKey property title for known property
TEST_F(XmpPropertiesTest_1316, PropertyTitleForDcDescription_1316) {
    Exiv2::XmpKey key("Xmp.dc.description");
    const char* title = Exiv2::XmpProperties::propertyTitle(key);
    EXPECT_NE(nullptr, title);
}

// Test: printProperties does not crash for known prefix
TEST_F(XmpPropertiesTest_1316, PrintPropertiesForDc_1316) {
    std::ostringstream oss;
    EXPECT_NO_THROW(Exiv2::XmpProperties::printProperties(oss, "dc"));
    EXPECT_FALSE(oss.str().empty());
}

// Test: Encode with format flags and padding
TEST_F(XmpParserTest_1316, EncodeWithPadding_1316) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket =
        "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:subject>"
        "<rdf:Bag><rdf:li>keyword</rdf:li></rdf:Bag>"
        "</dc:subject>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    int decResult = Exiv2::XmpParser::decode(xmpData, xmpPacket);
    EXPECT_EQ(0, decResult);

    std::string encodedPacket;
    int encResult = Exiv2::XmpParser::encode(encodedPacket, xmpData, 0, 2048);
    EXPECT_EQ(0, encResult);
    EXPECT_FALSE(encodedPacket.empty());
}

// Test: Terminate clears registered custom namespaces
TEST_F(XmpPropertiesTest_1316, TerminateClearsCustomNamespaces_1316) {
    const std::string ns = "http://example.com/test/termclear1316/";
    const std::string prefix = "termclear1316";

    Exiv2::XmpProperties::registerNs(ns, prefix);
    std::string resultBefore = Exiv2::XmpProperties::prefix(ns);
    EXPECT_EQ(prefix, resultBefore);

    Exiv2::XmpParser::terminate();

    // After terminate, custom namespace should be cleared
    // Re-initialize for subsequent operations
    Exiv2::XmpParser::initialize();
    std::string resultAfter = Exiv2::XmpProperties::prefix(ns);
    EXPECT_TRUE(resultAfter.empty());
}

// Test: Re-registering the same namespace with same prefix
TEST_F(XmpPropertiesTest_1316, ReregisterSameNamespace_1316) {
    const std::string ns = "http://example.com/test/rereg1316/";
    const std::string prefix = "rereg1316";

    Exiv2::XmpProperties::registerNs(ns, prefix);
    Exiv2::XmpProperties::registerNs(ns, prefix);

    std::string resultPrefix = Exiv2::XmpProperties::prefix(ns);
    EXPECT_EQ(prefix, resultPrefix);

    Exiv2::XmpProperties::unregisterNs(ns);
}

// Test: Decode with XMP packet containing multiple properties
TEST_F(XmpParserTest_1316, DecodeMultipleProperties_1316) {
    Exiv2::XmpData xmpData;
    std::string xmpPacket =
        "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\""
        " xmlns:dc=\"http://purl.org/dc/elements/1.1/\""
        " xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\">"
        "<dc:creator><rdf:Seq><rdf:li>Author</rdf:li></rdf:Seq></dc:creator>"
        "<xmp:Rating>5</xmp:Rating>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    int result = Exiv2::XmpParser::decode(xmpData, xmpPacket);
    EXPECT_EQ(0, result);
    EXPECT_GE(xmpData.count(), 2u);
}

}  // namespace
