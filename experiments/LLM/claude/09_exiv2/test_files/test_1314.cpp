#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/exiv2.hpp>
#include <string>

class XmpParserTest_1314 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure clean state before each test
        Exiv2::XmpParser::terminate();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

// Test that initialize returns true on first call with null lock function
TEST_F(XmpParserTest_1314, InitializeWithNullLockReturnsTrue_1314) {
    bool result = Exiv2::XmpParser::initialize(nullptr, nullptr);
    EXPECT_TRUE(result);
}

// Test that initialize returns true on subsequent calls (already initialized)
TEST_F(XmpParserTest_1314, InitializeCalledTwiceReturnsTrue_1314) {
    bool result1 = Exiv2::XmpParser::initialize(nullptr, nullptr);
    EXPECT_TRUE(result1);
    bool result2 = Exiv2::XmpParser::initialize(nullptr, nullptr);
    EXPECT_TRUE(result2);
}

// Test that terminate can be called without prior initialize
TEST_F(XmpParserTest_1314, TerminateWithoutInitialize_1314) {
    EXPECT_NO_THROW(Exiv2::XmpParser::terminate());
}

// Test that terminate followed by re-initialize works
TEST_F(XmpParserTest_1314, TerminateThenReinitialize_1314) {
    bool result1 = Exiv2::XmpParser::initialize(nullptr, nullptr);
    EXPECT_TRUE(result1);
    Exiv2::XmpParser::terminate();
    bool result2 = Exiv2::XmpParser::initialize(nullptr, nullptr);
    EXPECT_TRUE(result2);
}

// Test decode with empty XMP packet
TEST_F(XmpParserTest_1314, DecodeEmptyPacket_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    Exiv2::XmpData xmpData;
    std::string emptyPacket;
    int result = Exiv2::XmpParser::decode(xmpData, emptyPacket);
    EXPECT_EQ(0, result);
    EXPECT_TRUE(xmpData.empty());
}

// Test decode with valid minimal XMP packet
TEST_F(XmpParserTest_1314, DecodeValidMinimalXmpPacket_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    Exiv2::XmpData xmpData;
    std::string xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\""
        " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:creator><rdf:Seq><rdf:li>Test Author</rdf:li></rdf:Seq></dc:creator>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";
    int result = Exiv2::XmpParser::decode(xmpData, xmpPacket);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpData.empty());
}

// Test decode with invalid XMP packet
TEST_F(XmpParserTest_1314, DecodeInvalidXmpPacket_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    Exiv2::XmpData xmpData;
    std::string invalidPacket = "<not valid xml at all <<<>>>";
    int result = Exiv2::XmpParser::decode(xmpData, invalidPacket);
    // Non-zero indicates error
    EXPECT_NE(0, result);
}

// Test encode with empty XmpData
TEST_F(XmpParserTest_1314, EncodeEmptyXmpData_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    std::string xmpPacket;
    Exiv2::XmpData xmpData;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    EXPECT_EQ(0, result);
}

// Test round-trip: decode then encode
TEST_F(XmpParserTest_1314, RoundTripDecodeEncode_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    std::string originalPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\""
        " xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:subject><rdf:Bag><rdf:li>keyword1</rdf:li></rdf:Bag></dc:subject>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    Exiv2::XmpData xmpData;
    int decodeResult = Exiv2::XmpParser::decode(xmpData, originalPacket);
    EXPECT_EQ(0, decodeResult);
    EXPECT_FALSE(xmpData.empty());

    std::string encodedPacket;
    int encodeResult = Exiv2::XmpParser::encode(encodedPacket, xmpData, 0, 0);
    EXPECT_EQ(0, encodeResult);
    EXPECT_FALSE(encodedPacket.empty());

    // Decode encoded packet again to verify round-trip consistency
    Exiv2::XmpData xmpData2;
    int decodeResult2 = Exiv2::XmpParser::decode(xmpData2, encodedPacket);
    EXPECT_EQ(0, decodeResult2);
    EXPECT_EQ(xmpData.count(), xmpData2.count());
}

// Test that XmpData can be manipulated and then encoded
TEST_F(XmpParserTest_1314, EncodeManuallyConstructedXmpData_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";

    std::string xmpPacket;
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 0);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
    // The encoded packet should contain our title
    EXPECT_NE(std::string::npos, xmpPacket.find("Test Title"));
}

// Test initialize with a custom lock function
TEST_F(XmpParserTest_1314, InitializeWithCustomLockFunction_1314) {
    static int lockCallCount = 0;
    lockCallCount = 0;

    auto lockFct = [](void* pLockData, bool lockUnlock) {
        (void)pLockData;
        (void)lockUnlock;
        lockCallCount++;
    };

    int userData = 42;
    bool result = Exiv2::XmpParser::initialize(lockFct, &userData);
    EXPECT_TRUE(result);
}

// Test multiple terminate calls don't crash
TEST_F(XmpParserTest_1314, MultipleTerminateCalls_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    EXPECT_NO_THROW(Exiv2::XmpParser::terminate());
    EXPECT_NO_THROW(Exiv2::XmpParser::terminate());
    EXPECT_NO_THROW(Exiv2::XmpParser::terminate());
}

// Test decode with XMP packet containing multiple properties
TEST_F(XmpParserTest_1314, DecodeMultipleProperties_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    Exiv2::XmpData xmpData;
    std::string xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
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

// Test encode with formatting flags
TEST_F(XmpParserTest_1314, EncodeWithFormattingFlags_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.description"] = "A test description";

    std::string xmpPacket;
    // Use omit packet wrapper flag if available, otherwise just use 0
    int result = Exiv2::XmpParser::encode(xmpPacket, xmpData, 0, 2048);
    EXPECT_EQ(0, result);
    EXPECT_FALSE(xmpPacket.empty());
}

// Test decode clears existing data
TEST_F(XmpParserTest_1314, DecodeOverwritesExistingData_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);

    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Old Title";
    EXPECT_FALSE(xmpData.empty());

    std::string emptyPacket;
    int result = Exiv2::XmpParser::decode(xmpData, emptyPacket);
    EXPECT_EQ(0, result);
    // After decoding an empty packet, data should be cleared
    EXPECT_TRUE(xmpData.empty());
}

// Test that XmpData key access works after decode
TEST_F(XmpParserTest_1314, DecodeAndAccessSpecificKey_1314) {
    Exiv2::XmpParser::initialize(nullptr, nullptr);
    Exiv2::XmpData xmpData;
    std::string xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\""
        " xmlns:xmp=\"http://ns.adobe.com/xap/1.0/\">"
        "<xmp:Rating>3</xmp:Rating>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";
    int result = Exiv2::XmpParser::decode(xmpData, xmpPacket);
    EXPECT_EQ(0, result);

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.xmp.Rating"));
    EXPECT_NE(it, xmpData.end());
    if (it != xmpData.end()) {
        EXPECT_EQ("3", it->toString());
    }
}
