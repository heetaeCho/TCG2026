#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include "tiffvisitor_int.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffimage_int.hpp"

#include <cstring>
#include <string>
#include <vector>

using namespace Exiv2;
using namespace Exiv2::Internal;

namespace {

// A simple TiffEntry for testing
class TestTiffEntry : public TiffEntry {
public:
    TestTiffEntry(uint16_t tag, IfdId group)
        : TiffEntry(tag, group) {}
};

// Capture warnings
static std::vector<std::string> capturedWarnings;

void testWarningHandler(int level, const char* s) {
    if (level == LogMsg::warn) {
        capturedWarnings.push_back(s ? s : "");
    }
}

} // namespace

class TiffDecoderDecodeXmpTest_1658 : public ::testing::Test {
protected:
    void SetUp() override {
        capturedWarnings.clear();
        LogMsg::setHandler(testWarningHandler);
        LogMsg::setLevel(LogMsg::debug);
        XmpParser::initialize();
    }

    void TearDown() override {
        LogMsg::setHandler(LogMsg::defaultHandler);
        LogMsg::setLevel(LogMsg::warn);
        XmpParser::terminate();
    }
};

// Test decodeXmp with nullptr object - should handle gracefully or the entry has no data
TEST_F(TiffDecoderDecodeXmpTest_1658, DecodeXmpWithNullData_1658) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    // Create a TiffEntry with tag 0x02bc (XMP tag) in ifd0Id
    TestTiffEntry entry(0x02bc, IfdId::ifd0Id);

    // Entry has no data set, so getObjData should return nullptr
    TiffDecoder decoder(exifData, iptcData, xmpData, &entry, TiffMapping::findDecoder);

    // Should not crash when pData is nullptr
    decoder.decodeXmp(&entry);

    // XmpData should remain empty since no data was provided
    EXPECT_TRUE(xmpData.empty());
}

// Test decodeXmp with valid XMP data starting with '<'
TEST_F(TiffDecoderDecodeXmpTest_1658, DecodeXmpWithValidXmpPacket_1658) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    std::string xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:description><rdf:Alt><rdf:li xml:lang=\"x-default\">Test</rdf:li></rdf:Alt></dc:description>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    auto buf = std::make_shared<DataBuf>(
        reinterpret_cast<const byte*>(xmpPacket.data()), xmpPacket.size());

    TestTiffEntry entry(0x02bc, IfdId::ifd0Id);
    entry.setData(reinterpret_cast<byte*>(buf->data()), buf->size(), buf);

    TiffDecoder decoder(exifData, iptcData, xmpData, &entry, TiffMapping::findDecoder);
    decoder.decodeXmp(&entry);

    // XmpData should have been populated with the description
    EXPECT_FALSE(xmpData.empty());
}

// Test decodeXmp with XMP data that has leading characters before '<'
TEST_F(TiffDecoderDecodeXmpTest_1658, DecodeXmpWithLeadingCharacters_1658) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    // Add some leading whitespace/junk before the '<'
    std::string xmpPacket =
        "   "
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
        "<dc:description><rdf:Alt><rdf:li xml:lang=\"x-default\">Test</rdf:li></rdf:Alt></dc:description>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    auto buf = std::make_shared<DataBuf>(
        reinterpret_cast<const byte*>(xmpPacket.data()), xmpPacket.size());

    TestTiffEntry entry(0x02bc, IfdId::ifd0Id);
    entry.setData(reinterpret_cast<byte*>(buf->data()), buf->size(), buf);

    TiffDecoder decoder(exifData, iptcData, xmpData, &entry, TiffMapping::findDecoder);

    capturedWarnings.clear();
    decoder.decodeXmp(&entry);

#ifndef SUPPRESS_WARNINGS
    // Should have warned about removing leading characters
    bool foundRemovingWarning = false;
    for (const auto& w : capturedWarnings) {
        if (w.find("Removing") != std::string::npos && w.find("characters") != std::string::npos) {
            foundRemovingWarning = true;
            break;
        }
    }
    EXPECT_TRUE(foundRemovingWarning);
#endif
}

// Test decodeXmp with invalid/malformed XMP data
TEST_F(TiffDecoderDecodeXmpTest_1658, DecodeXmpWithInvalidXmpPacket_1658) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    // Malformed XMP data
    std::string xmpPacket = "<this is not valid xmp data>";

    auto buf = std::make_shared<DataBuf>(
        reinterpret_cast<const byte*>(xmpPacket.data()), xmpPacket.size());

    TestTiffEntry entry(0x02bc, IfdId::ifd0Id);
    entry.setData(reinterpret_cast<byte*>(buf->data()), buf->size(), buf);

    TiffDecoder decoder(exifData, iptcData, xmpData, &entry, TiffMapping::findDecoder);

    // Should not crash; may warn about failed decode
    decoder.decodeXmp(&entry);
}

// Test decodeXmp with empty data (zero size)
TEST_F(TiffDecoderDecodeXmpTest_1658, DecodeXmpWithEmptyData_1658) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    TestTiffEntry entry(0x02bc, IfdId::ifd0Id);

    // Empty buffer
    auto buf = std::make_shared<DataBuf>();
    entry.setData(buf);

    TiffDecoder decoder(exifData, iptcData, xmpData, &entry, TiffMapping::findDecoder);
    decoder.decodeXmp(&entry);

    EXPECT_TRUE(xmpData.empty());
}

// Test decodeXmp with a different tag (not 0x02bc) - getObjData should not find the data
TEST_F(TiffDecoderDecodeXmpTest_1658, DecodeXmpWithWrongTag_1658) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    std::string xmpPacket = "<?xpacket begin=\"\"?><x:xmpmeta/><?xpacket end=\"w\"?>";

    auto buf = std::make_shared<DataBuf>(
        reinterpret_cast<const byte*>(xmpPacket.data()), xmpPacket.size());

    // Use a different tag than 0x02bc
    TestTiffEntry entry(0x0100, IfdId::ifd0Id);
    entry.setData(reinterpret_cast<byte*>(buf->data()), buf->size(), buf);

    TiffDecoder decoder(exifData, iptcData, xmpData, &entry, TiffMapping::findDecoder);
    decoder.decodeXmp(&entry);

    // XmpData likely empty since getObjData looks for tag 0x02bc
    // (behavior depends on implementation of getObjData)
}

// Test decodeXmp with data that has no '<' character at all
TEST_F(TiffDecoderDecodeXmpTest_1658, DecodeXmpWithNoAngleBracket_1658) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    std::string xmpPacket = "no angle brackets here at all";

    auto buf = std::make_shared<DataBuf>(
        reinterpret_cast<const byte*>(xmpPacket.data()), xmpPacket.size());

    TestTiffEntry entry(0x02bc, IfdId::ifd0Id);
    entry.setData(reinterpret_cast<byte*>(buf->data()), buf->size(), buf);

    TiffDecoder decoder(exifData, iptcData, xmpData, &entry, TiffMapping::findDecoder);
    decoder.decodeXmp(&entry);

    // XmpParser::decode will likely fail on this, but should not crash
}

// Test decodeXmp where '<' is the first character (idx == 0, no trimming)
TEST_F(TiffDecoderDecodeXmpTest_1658, DecodeXmpNoLeadingTrim_1658) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    std::string xmpPacket =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
        "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\">"
        "<rdf:Description rdf:about=\"\"/>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end=\"w\"?>";

    auto buf = std::make_shared<DataBuf>(
        reinterpret_cast<const byte*>(xmpPacket.data()), xmpPacket.size());

    TestTiffEntry entry(0x02bc, IfdId::ifd0Id);
    entry.setData(reinterpret_cast<byte*>(buf->data()), buf->size(), buf);

    TiffDecoder decoder(exifData, iptcData, xmpData, &entry, TiffMapping::findDecoder);

    capturedWarnings.clear();
    decoder.decodeXmp(&entry);

    // Should NOT have a "Removing" warning since '<' is at index 0
    bool foundRemovingWarning = false;
    for (const auto& w : capturedWarnings) {
        if (w.find("Removing") != std::string::npos) {
            foundRemovingWarning = true;
            break;
        }
    }
    EXPECT_FALSE(foundRemovingWarning);
}

// Test decodeXmp with XMP data that has a single leading null byte before '<'
TEST_F(TiffDecoderDecodeXmpTest_1658, DecodeXmpWithNullByteLeading_1658) {
    ExifData exifData;
    IptcData iptcData;
    XmpData xmpData;

    std::string inner =
        "<?xpacket begin=\"\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>"
        "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"/>"
        "<?xpacket end=\"w\"?>";

    // Prepend a null byte
    std::string xmpPacket;
    xmpPacket.push_back('\0');
    xmpPacket.append(inner);

    auto buf = std::make_shared<DataBuf>(
        reinterpret_cast<const byte*>(xmpPacket.data()), xmpPacket.size());

    TestTiffEntry entry(0x02bc, IfdId::ifd0Id);
    entry.setData(reinterpret_cast<byte*>(buf->data()), buf->size(), buf);

    TiffDecoder decoder(exifData, iptcData, xmpData, &entry, TiffMapping::findDecoder);
    decoder.decodeXmp(&entry);

    // The null byte is before '<', so idx > 0, trimming should occur
}
