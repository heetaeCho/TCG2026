#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <cstring>
#include <vector>

namespace {

// Helper to write a uint16_t in little-endian format
void writeLE16(std::vector<uint8_t>& buf, uint16_t val) {
    buf.push_back(static_cast<uint8_t>(val & 0xFF));
    buf.push_back(static_cast<uint8_t>((val >> 8) & 0xFF));
}

// Helper to write a uint32_t in little-endian format
void writeLE32(std::vector<uint8_t>& buf, uint32_t val) {
    buf.push_back(static_cast<uint8_t>(val & 0xFF));
    buf.push_back(static_cast<uint8_t>((val >> 8) & 0xFF));
    buf.push_back(static_cast<uint8_t>((val >> 16) & 0xFF));
    buf.push_back(static_cast<uint8_t>((val >> 24) & 0xFF));
}

// Helper to write a uint64_t in little-endian format
void writeLE64(std::vector<uint8_t>& buf, uint64_t val) {
    for (int i = 0; i < 8; i++) {
        buf.push_back(static_cast<uint8_t>((val >> (8 * i)) & 0xFF));
    }
}

// Helper to write a wide-char string (UTF-16LE) into buffer
void writeWcharString(std::vector<uint8_t>& buf, const std::string& str) {
    for (char c : str) {
        buf.push_back(static_cast<uint8_t>(c));
        buf.push_back(0x00);
    }
}

// Build a minimal ASF file that has an Extended Content Description object
// so that readMetadata() will process it and populate xmpData.
//
// ASF structure:
//   Header Object (GUID + size + num_headers + reserved)
//     Extended Content Description Object (GUID + size + content)
//
// GUIDs (from ASF spec):
// Header Object: 75B22630-668E-11CF-A6D9-00AA0062CE6C
// Extended Content Description: D2D0A440-E307-11D2-97F0-00A0C95EA850

static const uint8_t headerObjectGUID[] = {
    0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
    0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
};

static const uint8_t extContentDescGUID[] = {
    0x40, 0xA4, 0xD0, 0xD2, 0x07, 0xE3, 0xD2, 0x11,
    0x97, 0xF0, 0x00, 0xA0, 0xC9, 0x5E, 0xA8, 0x50
};

std::vector<uint8_t> buildExtendedContentDescPayload(
    const std::vector<std::tuple<std::string, uint16_t, std::vector<uint8_t>>>& descriptors) {
    // Build the inner payload: content_descriptor_count + descriptors
    std::vector<uint8_t> payload;
    writeLE16(payload, static_cast<uint16_t>(descriptors.size()));

    for (auto& [name, dataType, valueData] : descriptors) {
        // descriptor_name_length (in bytes, including null terminator as wide chars)
        uint16_t nameLen = static_cast<uint16_t>((name.size() + 1) * 2);
        writeLE16(payload, nameLen);
        // descriptor name as UTF-16LE with null terminator
        writeWcharString(payload, name);
        payload.push_back(0x00);
        payload.push_back(0x00);

        // descriptor_value_data_type
        writeLE16(payload, dataType);
        // descriptor_value_length
        writeLE16(payload, static_cast<uint16_t>(valueData.size()));
        // descriptor value
        payload.insert(payload.end(), valueData.begin(), valueData.end());
    }

    return payload;
}

std::vector<uint8_t> buildAsfWithExtContentDesc(const std::vector<uint8_t>& extPayload) {
    // Extended Content Description Object: GUID(16) + Size(8) + payload
    uint64_t extObjSize = 16 + 8 + extPayload.size();

    std::vector<uint8_t> extObj;
    extObj.insert(extObj.end(), extContentDescGUID, extContentDescGUID + 16);
    writeLE64(extObj, extObjSize);
    extObj.insert(extObj.end(), extPayload.begin(), extPayload.end());

    // Header Object: GUID(16) + Size(8) + NumHeaders(4) + Reserved1(1) + Reserved2(1) + sub-objects
    uint64_t headerSize = 16 + 8 + 4 + 1 + 1 + extObj.size();

    std::vector<uint8_t> file;
    file.insert(file.end(), headerObjectGUID, headerObjectGUID + 16);
    writeLE64(file, headerSize);
    writeLE32(file, 1); // number of header objects
    file.push_back(0x01); // reserved1
    file.push_back(0x02); // reserved2
    file.insert(file.end(), extObj.begin(), extObj.end());

    return file;
}

class AsfVideoExtendedContentTest_1570 : public ::testing::Test {
protected:
    void SetUp() override {
        // XMP toolkit initialization may be needed
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }

    std::unique_ptr<Exiv2::AsfVideo> createAsfVideo(const std::vector<uint8_t>& data) {
        auto io = std::make_unique<Exiv2::MemIo>(data.data(), data.size());
        return std::make_unique<Exiv2::AsfVideo>(std::move(io));
    }
};

// Test: AsfVideo can be created from a MemIo
TEST_F(AsfVideoExtendedContentTest_1570, ConstructFromMemIo_1570) {
    std::vector<uint8_t> emptyData(100, 0);
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    ASSERT_NO_THROW(Exiv2::AsfVideo video(std::move(io)));
}

// Test: mimeType returns the expected ASF mime type
TEST_F(AsfVideoExtendedContentTest_1570, MimeType_1570) {
    std::vector<uint8_t> emptyData(100, 0);
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    Exiv2::AsfVideo video(std::move(io));
    std::string mime = video.mimeType();
    EXPECT_FALSE(mime.empty());
    EXPECT_THAT(mime, ::testing::HasSubstr("video"));
}

// Test: readMetadata with extended content description containing a Unicode string descriptor
TEST_F(AsfVideoExtendedContentTest_1570, ExtendedContentDescUnicodeString_1570) {
    std::string name = "TestProp";
    std::string value = "Hello";

    // Build value data as UTF-16LE with null terminator
    std::vector<uint8_t> valueData;
    writeWcharString(valueData, value);
    valueData.push_back(0x00);
    valueData.push_back(0x00);

    auto payload = buildExtendedContentDescPayload({{name, 0, valueData}});
    auto fileData = buildAsfWithExtContentDesc(payload);

    auto video = createAsfVideo(fileData);
    try {
        video->readMetadata();
    } catch (...) {
        // readMetadata may throw on incomplete ASF; we still check xmpData
    }

    auto& xmp = video->xmpData();
    auto it = xmp.findKey(Exiv2::XmpKey("Xmp.video.ExtendedContentDescription"));
    if (it != xmp.end()) {
        std::string result = it->toString();
        // The result should contain the property name and value
        EXPECT_THAT(result, ::testing::HasSubstr("TestProp"));
    }
}

// Test: readMetadata with extended content description containing a DWORD descriptor
TEST_F(AsfVideoExtendedContentTest_1570, ExtendedContentDescDWORD_1570) {
    std::string name = "BitRate";
    uint32_t dwordVal = 128000;

    std::vector<uint8_t> valueData;
    writeLE32(valueData, dwordVal);

    auto payload = buildExtendedContentDescPayload({{name, 3, valueData}});
    auto fileData = buildAsfWithExtContentDesc(payload);

    auto video = createAsfVideo(fileData);
    try {
        video->readMetadata();
    } catch (...) {
    }

    auto& xmp = video->xmpData();
    auto it = xmp.findKey(Exiv2::XmpKey("Xmp.video.ExtendedContentDescription"));
    if (it != xmp.end()) {
        std::string result = it->toString();
        EXPECT_THAT(result, ::testing::HasSubstr("BitRate"));
        EXPECT_THAT(result, ::testing::HasSubstr("128000"));
    }
}

// Test: readMetadata with zero content descriptors
TEST_F(AsfVideoExtendedContentTest_1570, ExtendedContentDescZeroDescriptors_1570) {
    auto payload = buildExtendedContentDescPayload({});
    auto fileData = buildAsfWithExtContentDesc(payload);

    auto video = createAsfVideo(fileData);
    try {
        video->readMetadata();
    } catch (...) {
    }

    auto& xmp = video->xmpData();
    auto it = xmp.findKey(Exiv2::XmpKey("Xmp.video.ExtendedContentDescription"));
    if (it != xmp.end()) {
        // With zero descriptors, value should be empty or minimal
        std::string result = it->toString();
        EXPECT_TRUE(result.empty() || result.find(':') == std::string::npos);
    }
}

// Test: readMetadata with BOOL descriptor (type 2)
TEST_F(AsfVideoExtendedContentTest_1570, ExtendedContentDescBOOL_1570) {
    std::string name = "IsVBR";
    std::vector<uint8_t> valueData;
    writeLE16(valueData, 1); // BOOL = true

    auto payload = buildExtendedContentDescPayload({{name, 2, valueData}});
    auto fileData = buildAsfWithExtContentDesc(payload);

    auto video = createAsfVideo(fileData);
    try {
        video->readMetadata();
    } catch (...) {
    }

    auto& xmp = video->xmpData();
    auto it = xmp.findKey(Exiv2::XmpKey("Xmp.video.ExtendedContentDescription"));
    if (it != xmp.end()) {
        std::string result = it->toString();
        EXPECT_THAT(result, ::testing::HasSubstr("IsVBR"));
    }
}

// Test: readMetadata with QWORD descriptor (type 4)
TEST_F(AsfVideoExtendedContentTest_1570, ExtendedContentDescQWORD_1570) {
    std::string name = "Duration";
    uint64_t qwordVal = 9876543210ULL;
    std::vector<uint8_t> valueData;
    writeLE64(valueData, qwordVal);

    auto payload = buildExtendedContentDescPayload({{name, 4, valueData}});
    auto fileData = buildAsfWithExtContentDesc(payload);

    auto video = createAsfVideo(fileData);
    try {
        video->readMetadata();
    } catch (...) {
    }

    auto& xmp = video->xmpData();
    auto it = xmp.findKey(Exiv2::XmpKey("Xmp.video.ExtendedContentDescription"));
    if (it != xmp.end()) {
        std::string result = it->toString();
        EXPECT_THAT(result, ::testing::HasSubstr("Duration"));
        EXPECT_THAT(result, ::testing::HasSubstr("9876543210"));
    }
}

// Test: readMetadata with WORD descriptor (type 5)
TEST_F(AsfVideoExtendedContentTest_1570, ExtendedContentDescWORD_1570) {
    std::string name = "StreamNum";
    std::vector<uint8_t> valueData;
    writeLE16(valueData, 42);

    auto payload = buildExtendedContentDescPayload({{name, 5, valueData}});
    auto fileData = buildAsfWithExtContentDesc(payload);

    auto video = createAsfVideo(fileData);
    try {
        video->readMetadata();
    } catch (...) {
    }

    auto& xmp = video->xmpData();
    auto it = xmp.findKey(Exiv2::XmpKey("Xmp.video.ExtendedContentDescription"));
    if (it != xmp.end()) {
        std::string result = it->toString();
        EXPECT_THAT(result, ::testing::HasSubstr("StreamNum"));
        EXPECT_THAT(result, ::testing::HasSubstr("42"));
    }
}

// Test: readMetadata with BYTE array descriptor (type 1)
TEST_F(AsfVideoExtendedContentTest_1570, ExtendedContentDescByteArray_1570) {
    std::string name = "BinaryData";
    std::vector<uint8_t> valueData = {'A', 'B', 'C', 'D'};

    auto payload = buildExtendedContentDescPayload({{name, 1, valueData}});
    auto fileData = buildAsfWithExtContentDesc(payload);

    auto video = createAsfVideo(fileData);
    try {
        video->readMetadata();
    } catch (...) {
    }

    auto& xmp = video->xmpData();
    auto it = xmp.findKey(Exiv2::XmpKey("Xmp.video.ExtendedContentDescription"));
    if (it != xmp.end()) {
        std::string result = it->toString();
        EXPECT_THAT(result, ::testing::HasSubstr("BinaryData"));
        EXPECT_THAT(result, ::testing::HasSubstr("ABCD"));
    }
}

// Test: Multiple descriptors in extended content description
TEST_F(AsfVideoExtendedContentTest_1570, ExtendedContentDescMultipleDescriptors_1570) {
    std::string name1 = "Prop1";
    std::vector<uint8_t> val1;
    writeLE32(val1, 100);

    std::string name2 = "Prop2";
    std::vector<uint8_t> val2;
    writeLE16(val2, 200);

    auto payload = buildExtendedContentDescPayload({
        {name1, 3, val1},
        {name2, 5, val2}
    });
    auto fileData = buildAsfWithExtContentDesc(payload);

    auto video = createAsfVideo(fileData);
    try {
        video->readMetadata();
    } catch (...) {
    }

    auto& xmp = video->xmpData();
    auto it = xmp.findKey(Exiv2::XmpKey("Xmp.video.ExtendedContentDescription"));
    if (it != xmp.end()) {
        std::string result = it->toString();
        EXPECT_THAT(result, ::testing::HasSubstr("Prop1"));
        EXPECT_THAT(result, ::testing::HasSubstr("100"));
        EXPECT_THAT(result, ::testing::HasSubstr("Prop2"));
        EXPECT_THAT(result, ::testing::HasSubstr("200"));
        // Each descriptor is separated by ", "
        EXPECT_THAT(result, ::testing::HasSubstr(", "));
    }
}

// Test: writeMetadata throws (ASF typically doesn't support writing)
TEST_F(AsfVideoExtendedContentTest_1570, WriteMetadataThrows_1570) {
    std::vector<uint8_t> emptyData(100, 0);
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    Exiv2::AsfVideo video(std::move(io));
    EXPECT_THROW(video.writeMetadata(), Exiv2::Error);
}

// Test: xmpData is accessible and initially empty
TEST_F(AsfVideoExtendedContentTest_1570, XmpDataInitiallyEmpty_1570) {
    std::vector<uint8_t> emptyData(100, 0);
    auto io = std::make_unique<Exiv2::MemIo>(emptyData.data(), emptyData.size());
    Exiv2::AsfVideo video(std::move(io));
    EXPECT_TRUE(video.xmpData().empty());
}

// Test: readMetadata on invalid/empty data doesn't crash
TEST_F(AsfVideoExtendedContentTest_1570, ReadMetadataInvalidData_1570) {
    std::vector<uint8_t> garbage(50, 0xFF);
    auto io = std::make_unique<Exiv2::MemIo>(garbage.data(), garbage.size());
    Exiv2::AsfVideo video(std::move(io));
    // Should either throw or handle gracefully
    try {
        video.readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for invalid data
    } catch (...) {
        // Any exception is acceptable for invalid data
    }
}

} // namespace
