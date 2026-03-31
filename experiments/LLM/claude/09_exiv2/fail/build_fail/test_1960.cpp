#include <gtest/gtest.h>
#include <string>

// Include necessary headers for the XMP SDK
#define TXMP_STRING_TYPE std::string
#include "XMP.hpp"
#include "XMP.incl_cpp"

class FindRootNodeTest_1960 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        static bool initialized = false;
        if (!initialized) {
            SXMPMeta::Initialize();
            initialized = true;
        }
    }

    void SetUp() override {
        // Each test gets a fresh XMPMeta object
    }

    void TearDown() override {
    }
};

// Helper to build XMP packet with a specific toolkit version
static std::string MakeXMPPacket(const std::string& tkVersion, bool useXmpmeta = true) {
    std::string result;
    if (useXmpmeta) {
        result = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"";
        if (!tkVersion.empty()) {
            result += " x:xmptk=\"" + tkVersion + "\"";
        }
        result += ">\n";
    }
    result += "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n";
    result += "  <rdf:Description rdf:about=\"\"\n";
    result += "    xmlns:dc=\"http://purl.org/dc/elements/1.1/\">\n";
    result += "    <dc:creator><rdf:Seq><rdf:li>Test</rdf:li></rdf:Seq></dc:creator>\n";
    result += "  </rdf:Description>\n";
    result += "</rdf:RDF>\n";
    if (useXmpmeta) {
        result += "</x:xmpmeta>\n";
    }
    return result;
}

// Test: Parse valid XMP with version string "1.2.3-456"
TEST_F(FindRootNodeTest_1960, ParseVersionString_Full_1960) {
    std::string xmp = MakeXMPPacket("XMP Core 1.2.3-456");
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    // Verify the XMP was parsed (check that a known property exists)
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
    EXPECT_EQ("Test", value);
}

// Test: Parse valid XMP with no toolkit version
TEST_F(FindRootNodeTest_1960, ParseNoVersion_1960) {
    std::string xmp = MakeXMPPacket("");
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
    EXPECT_EQ("Test", value);
}

// Test: kXMP_RequireXMPMeta with x:xmpmeta present should succeed
TEST_F(FindRootNodeTest_1960, RequireXMPMetaWithWrapper_1960) {
    std::string xmp = MakeXMPPacket("XMP Core 5.0.0-1", true);
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_RequireXMPMeta));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
}

// Test: kXMP_RequireXMPMeta without x:xmpmeta wrapper should yield empty/no properties
TEST_F(FindRootNodeTest_1960, RequireXMPMetaWithoutWrapper_1960) {
    std::string xmp = MakeXMPPacket("", false); // No x:xmpmeta wrapper
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_RequireXMPMeta));
    // Without the wrapper and kXMP_RequireXMPMeta, root should be rejected
    std::string value;
    EXPECT_FALSE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
}

// Test: Without kXMP_RequireXMPMeta, bare rdf:RDF should work
TEST_F(FindRootNodeTest_1960, NoRequireXMPMetaWithoutWrapper_1960) {
    std::string xmp = MakeXMPPacket("", false);
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
    EXPECT_EQ("Test", value);
}

// Test: Empty buffer parsing
TEST_F(FindRootNodeTest_1960, ParseEmptyBuffer_1960) {
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer("", 0, 0));
    std::string value;
    EXPECT_FALSE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
}

// Test: Parse version with large version numbers (boundary: >99 gets clamped to 99)
TEST_F(FindRootNodeTest_1960, ParseVersionLargeNumbers_1960) {
    // Version "999.999.999-9999" should be clamped
    std::string xmp = MakeXMPPacket("XMP Core 999.999.999-9999");
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
}

// Test: Parse version with only major version
TEST_F(FindRootNodeTest_1960, ParseVersionMajorOnly_1960) {
    std::string xmp = MakeXMPPacket("XMP Core 5");
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
}

// Test: Parse version with major.minor only (no patch/build)
TEST_F(FindRootNodeTest_1960, ParseVersionMajorMinor_1960) {
    std::string xmp = MakeXMPPacket("XMP Core 5.6");
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
}

// Test: Parse version with zeros
TEST_F(FindRootNodeTest_1960, ParseVersionZeros_1960) {
    std::string xmp = MakeXMPPacket("XMP Core 0.0.0-0");
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
}

// Test: x:xapmeta wrapper should also be accepted
TEST_F(FindRootNodeTest_1960, XapmataWrapperAccepted_1960) {
    std::string xmp;
    xmp = "<x:xapmeta xmlns:x=\"adobe:ns:meta/\" x:xaptk=\"XMP Core 3.4.1-100\">\n";
    xmp += "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n";
    xmp += "  <rdf:Description rdf:about=\"\"\n";
    xmp += "    xmlns:dc=\"http://purl.org/dc/elements/1.1/\">\n";
    xmp += "    <dc:creator><rdf:Seq><rdf:li>Author</rdf:li></rdf:Seq></dc:creator>\n";
    xmp += "  </rdf:Description>\n";
    xmp += "</rdf:RDF>\n";
    xmp += "</x:xapmeta>\n";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), kXMP_RequireXMPMeta));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
    EXPECT_EQ("Author", value);
}

// Test: Invalid XML should throw or not crash
TEST_F(FindRootNodeTest_1960, ParseInvalidXML_1960) {
    std::string invalid = "<not valid xml at all<<<>>>";
    SXMPMeta meta;
    EXPECT_ANY_THROW(meta.ParseFromBuffer(invalid.c_str(), static_cast<XMP_StringLen>(invalid.size()), 0));
}

// Test: Incremental parsing with kXMP_ParseMoreBuffers
TEST_F(FindRootNodeTest_1960, IncrementalParsing_1960) {
    std::string xmp = MakeXMPPacket("XMP Core 4.1.1-100");
    SXMPMeta meta;
    size_t half = xmp.size() / 2;
    // First half
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(half), kXMP_ParseMoreBuffers));
    // Second half (last buffer)
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str() + half, static_cast<XMP_StringLen>(xmp.size() - half), 0));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
    EXPECT_EQ("Test", value);
}

// Test: Version string with no digits
TEST_F(FindRootNodeTest_1960, ParseVersionNoDigits_1960) {
    std::string xmp = MakeXMPPacket("No Version Here");
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
}

// Test: Version string boundary - exactly 99.99.99-999
TEST_F(FindRootNodeTest_1960, ParseVersionBoundaryExact_1960) {
    std::string xmp = MakeXMPPacket("XMP Core 99.99.99-999");
    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
}

// Test: Multiple properties after parsing
TEST_F(FindRootNodeTest_1960, ParseMultipleProperties_1960) {
    std::string xmp;
    xmp = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\" x:xmptk=\"XMP Core 5.1.2-100\">\n";
    xmp += "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">\n";
    xmp += "  <rdf:Description rdf:about=\"\"\n";
    xmp += "    xmlns:dc=\"http://purl.org/dc/elements/1.1/\"\n";
    xmp += "    xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\">\n";
    xmp += "    <dc:creator><rdf:Seq><rdf:li>Author</rdf:li></rdf:Seq></dc:creator>\n";
    xmp += "    <xmp:CreatorTool>TestTool</xmp:CreatorTool>\n";
    xmp += "  </rdf:Description>\n";
    xmp += "</rdf:RDF>\n";
    xmp += "</x:xmpmeta>\n";

    SXMPMeta meta;
    EXPECT_NO_THROW(meta.ParseFromBuffer(xmp.c_str(), static_cast<XMP_StringLen>(xmp.size()), 0));
    
    std::string value;
    EXPECT_TRUE(meta.GetArrayItem("http://purl.org/dc/elements/1.1/", "creator", 1, &value, 0));
    EXPECT_EQ("Author", value);
    
    EXPECT_TRUE(meta.GetProperty("http://ns.adobe.com/xap/1.0/", "CreatorTool", &value, 0));
    EXPECT_EQ("TestTool", value);
}
