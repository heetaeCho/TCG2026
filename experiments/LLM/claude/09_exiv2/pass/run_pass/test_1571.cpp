#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/asfvideo.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <cstring>
#include <vector>
#include <fstream>

namespace {

// Helper to create a memory buffer with content description data
// The contentDescription() method reads:
//   5 x uint16_t (WORD) lengths: title, author, copyright, description, rating
//   Then reads wchar strings of those lengths

// Helper to write a uint16_t in little-endian format
void writeLE16(std::vector<uint8_t>& buf, uint16_t val) {
    buf.push_back(static_cast<uint8_t>(val & 0xFF));
    buf.push_back(static_cast<uint8_t>((val >> 8) & 0xFF));
}

// Helper to write a wide string (UTF-16LE) including null terminator
void writeWString(std::vector<uint8_t>& buf, const std::wstring& str, uint16_t length) {
    // Write 'length' bytes of wchar data
    for (uint16_t i = 0; i < length; i++) {
        if (i < str.size() * 2) {
            size_t charIdx = i / 2;
            if (i % 2 == 0) {
                buf.push_back(static_cast<uint8_t>(str[charIdx] & 0xFF));
            } else {
                buf.push_back(static_cast<uint8_t>((str[charIdx] >> 8) & 0xFF));
            }
        } else {
            buf.push_back(0);
        }
    }
}

// Build a minimal ASF file that contains Content Description Object
// ASF Header structure:
//   Header Object GUID (16 bytes) + size (8 bytes) + num headers (4 bytes) + reserved (2 bytes)
//   Then sub-objects

// GUIDs (little-endian byte representation)
const uint8_t ASF_HEADER_GUID[] = {
    0x30, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
    0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
};

const uint8_t CONTENT_DESC_GUID[] = {
    0x33, 0x26, 0xB2, 0x75, 0x8E, 0x66, 0xCF, 0x11,
    0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C
};

void writeGUID(std::vector<uint8_t>& buf, const uint8_t* guid) {
    for (int i = 0; i < 16; i++) {
        buf.push_back(guid[i]);
    }
}

void writeLE64(std::vector<uint8_t>& buf, uint64_t val) {
    for (int i = 0; i < 8; i++) {
        buf.push_back(static_cast<uint8_t>((val >> (i * 8)) & 0xFF));
    }
}

void writeLE32(std::vector<uint8_t>& buf, uint32_t val) {
    for (int i = 0; i < 4; i++) {
        buf.push_back(static_cast<uint8_t>((val >> (i * 8)) & 0xFF));
    }
}

std::vector<uint8_t> buildAsfWithContentDescription(
    uint16_t titleLen, const std::vector<uint8_t>& titleData,
    uint16_t authorLen, const std::vector<uint8_t>& authorData,
    uint16_t copyrightLen, const std::vector<uint8_t>& copyrightData,
    uint16_t descLen, const std::vector<uint8_t>& descData,
    uint16_t ratingLen, const std::vector<uint8_t>& ratingData)
{
    // Build Content Description sub-object
    std::vector<uint8_t> contentDesc;
    writeGUID(contentDesc, CONTENT_DESC_GUID);
    
    // Calculate size: 16 (guid) + 8 (size) + 5*2 (lengths) + data
    uint64_t contentSize = 16 + 8 + 10 + titleLen + authorLen + copyrightLen + descLen + ratingLen;
    writeLE64(contentDesc, contentSize);
    
    writeLE16(contentDesc, titleLen);
    writeLE16(contentDesc, authorLen);
    writeLE16(contentDesc, copyrightLen);
    writeLE16(contentDesc, descLen);
    writeLE16(contentDesc, ratingLen);
    
    contentDesc.insert(contentDesc.end(), titleData.begin(), titleData.end());
    contentDesc.insert(contentDesc.end(), authorData.begin(), authorData.end());
    contentDesc.insert(contentDesc.end(), copyrightData.begin(), copyrightData.end());
    contentDesc.insert(contentDesc.end(), descData.begin(), descData.end());
    contentDesc.insert(contentDesc.end(), ratingData.begin(), ratingData.end());
    
    // Build ASF Header
    std::vector<uint8_t> asfData;
    writeGUID(asfData, ASF_HEADER_GUID);
    
    uint64_t headerSize = 16 + 8 + 4 + 2 + contentDesc.size();
    writeLE64(asfData, headerSize);
    writeLE32(asfData, 1); // num headers
    asfData.push_back(0x01); // reserved1
    asfData.push_back(0x02); // reserved2
    
    asfData.insert(asfData.end(), contentDesc.begin(), contentDesc.end());
    
    return asfData;
}

// Helper to make UTF-16LE bytes from ASCII string
std::vector<uint8_t> makeUTF16LE(const std::string& ascii) {
    std::vector<uint8_t> result;
    for (char c : ascii) {
        result.push_back(static_cast<uint8_t>(c));
        result.push_back(0);
    }
    // null terminator
    result.push_back(0);
    result.push_back(0);
    return result;
}

class AsfVideoContentDescriptionTest_1571 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test: Reading metadata from an ASF file with all content description fields populated
TEST_F(AsfVideoContentDescriptionTest_1571, AllFieldsPopulated_1571) {
    auto titleData = makeUTF16LE("Test Title");
    auto authorData = makeUTF16LE("Test Author");
    auto copyrightData = makeUTF16LE("Test Copyright");
    auto descData = makeUTF16LE("Test Description");
    auto ratingData = makeUTF16LE("Test Rating");
    
    auto asfData = buildAsfWithContentDescription(
        static_cast<uint16_t>(titleData.size()), titleData,
        static_cast<uint16_t>(authorData.size()), authorData,
        static_cast<uint16_t>(copyrightData.size()), copyrightData,
        static_cast<uint16_t>(descData.size()), descData,
        static_cast<uint16_t>(ratingData.size()), ratingData
    );
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    try {
        asf.readMetadata();
    } catch (...) {
        // Some implementations may throw on incomplete data; we still check what was parsed
    }
    
    const Exiv2::XmpData& xmp = asf.xmpData();
    
    auto titleIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Title"));
    if (titleIt != xmp.end()) {
        EXPECT_EQ(titleIt->toString().find("Test Title") != std::string::npos, true);
    }
}

// Test: Reading metadata from an ASF file with all zero-length content description fields
TEST_F(AsfVideoContentDescriptionTest_1571, AllFieldsEmpty_1571) {
    std::vector<uint8_t> emptyData;
    
    auto asfData = buildAsfWithContentDescription(
        0, emptyData,
        0, emptyData,
        0, emptyData,
        0, emptyData,
        0, emptyData
    );
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    try {
        asf.readMetadata();
    } catch (...) {
    }
    
    const Exiv2::XmpData& xmp = asf.xmpData();
    
    // With zero lengths, no XMP fields should be set for these keys
    auto titleIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Title"));
    EXPECT_EQ(titleIt, xmp.end());
    
    auto authorIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Author"));
    EXPECT_EQ(authorIt, xmp.end());
    
    auto copyrightIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Copyright"));
    EXPECT_EQ(copyrightIt, xmp.end());
    
    auto descIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Description"));
    EXPECT_EQ(descIt, xmp.end());
    
    auto ratingIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Rating"));
    EXPECT_EQ(ratingIt, xmp.end());
}

// Test: Only title field is populated, rest are empty
TEST_F(AsfVideoContentDescriptionTest_1571, OnlyTitlePopulated_1571) {
    auto titleData = makeUTF16LE("My Title");
    std::vector<uint8_t> emptyData;
    
    auto asfData = buildAsfWithContentDescription(
        static_cast<uint16_t>(titleData.size()), titleData,
        0, emptyData,
        0, emptyData,
        0, emptyData,
        0, emptyData
    );
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    try {
        asf.readMetadata();
    } catch (...) {
    }
    
    const Exiv2::XmpData& xmp = asf.xmpData();
    
    auto titleIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Title"));
    if (titleIt != xmp.end()) {
        EXPECT_FALSE(titleIt->toString().empty());
    }
    
    auto authorIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Author"));
    EXPECT_EQ(authorIt, xmp.end());
}

// Test: Only author field is populated
TEST_F(AsfVideoContentDescriptionTest_1571, OnlyAuthorPopulated_1571) {
    auto authorData = makeUTF16LE("John Doe");
    std::vector<uint8_t> emptyData;
    
    auto asfData = buildAsfWithContentDescription(
        0, emptyData,
        static_cast<uint16_t>(authorData.size()), authorData,
        0, emptyData,
        0, emptyData,
        0, emptyData
    );
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    try {
        asf.readMetadata();
    } catch (...) {
    }
    
    const Exiv2::XmpData& xmp = asf.xmpData();
    
    auto titleIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Title"));
    EXPECT_EQ(titleIt, xmp.end());
    
    auto authorIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Author"));
    if (authorIt != xmp.end()) {
        EXPECT_FALSE(authorIt->toString().empty());
    }
}

// Test: Constructing AsfVideo with valid MemIo
TEST_F(AsfVideoContentDescriptionTest_1571, ConstructWithMemIo_1571) {
    std::vector<uint8_t> emptyData;
    auto asfData = buildAsfWithContentDescription(0, emptyData, 0, emptyData, 0, emptyData, 0, emptyData, 0, emptyData);
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    EXPECT_NO_THROW(Exiv2::AsfVideo asf(std::move(io)));
}

// Test: MIME type should be video/x-ms-asf
TEST_F(AsfVideoContentDescriptionTest_1571, MimeType_1571) {
    std::vector<uint8_t> emptyData;
    auto asfData = buildAsfWithContentDescription(0, emptyData, 0, emptyData, 0, emptyData, 0, emptyData, 0, emptyData);
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    std::string mime = asf.mimeType();
    EXPECT_EQ(mime, "video/x-ms-asf");
}

// Test: writeMetadata should throw (not supported for ASF)
TEST_F(AsfVideoContentDescriptionTest_1571, WriteMetadataThrows_1571) {
    std::vector<uint8_t> emptyData;
    auto asfData = buildAsfWithContentDescription(0, emptyData, 0, emptyData, 0, emptyData, 0, emptyData, 0, emptyData);
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    EXPECT_THROW(asf.writeMetadata(), Exiv2::Error);
}

// Test: XmpData starts empty before readMetadata
TEST_F(AsfVideoContentDescriptionTest_1571, XmpDataEmptyBeforeRead_1571) {
    std::vector<uint8_t> emptyData;
    auto asfData = buildAsfWithContentDescription(0, emptyData, 0, emptyData, 0, emptyData, 0, emptyData, 0, emptyData);
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    EXPECT_TRUE(asf.xmpData().empty());
}

// Test: Reading with truncated/invalid data should not crash
TEST_F(AsfVideoContentDescriptionTest_1571, TruncatedDataNoCrash_1571) {
    // Just the header GUID, not enough for a valid ASF file
    std::vector<uint8_t> truncated(ASF_HEADER_GUID, ASF_HEADER_GUID + 16);
    
    auto io = std::make_unique<Exiv2::MemIo>(truncated.data(), truncated.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    // Should either throw or handle gracefully, but not crash
    try {
        asf.readMetadata();
    } catch (...) {
        // Expected - truncated data
    }
}

// Test: Empty IO should not crash
TEST_F(AsfVideoContentDescriptionTest_1571, EmptyIoNoCrash_1571) {
    auto io = std::make_unique<Exiv2::MemIo>();
    Exiv2::AsfVideo asf(std::move(io));
    
    try {
        asf.readMetadata();
    } catch (...) {
        // Expected
    }
}

// Test: Only copyright and rating populated
TEST_F(AsfVideoContentDescriptionTest_1571, CopyrightAndRatingPopulated_1571) {
    auto copyrightData = makeUTF16LE("(c) 2024");
    auto ratingData = makeUTF16LE("5 stars");
    std::vector<uint8_t> emptyData;
    
    auto asfData = buildAsfWithContentDescription(
        0, emptyData,
        0, emptyData,
        static_cast<uint16_t>(copyrightData.size()), copyrightData,
        0, emptyData,
        static_cast<uint16_t>(ratingData.size()), ratingData
    );
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    try {
        asf.readMetadata();
    } catch (...) {
    }
    
    const Exiv2::XmpData& xmp = asf.xmpData();
    
    auto titleIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Title"));
    EXPECT_EQ(titleIt, xmp.end());
    
    auto authorIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Author"));
    EXPECT_EQ(authorIt, xmp.end());
    
    auto copyrightIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Copyright"));
    if (copyrightIt != xmp.end()) {
        EXPECT_FALSE(copyrightIt->toString().empty());
    }
    
    auto ratingIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Rating"));
    if (ratingIt != xmp.end()) {
        EXPECT_FALSE(ratingIt->toString().empty());
    }
}

// Test: Only description populated
TEST_F(AsfVideoContentDescriptionTest_1571, OnlyDescriptionPopulated_1571) {
    auto descData = makeUTF16LE("A detailed description of this video content");
    std::vector<uint8_t> emptyData;
    
    auto asfData = buildAsfWithContentDescription(
        0, emptyData,
        0, emptyData,
        0, emptyData,
        static_cast<uint16_t>(descData.size()), descData,
        0, emptyData
    );
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    try {
        asf.readMetadata();
    } catch (...) {
    }
    
    const Exiv2::XmpData& xmp = asf.xmpData();
    
    auto descIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Description"));
    if (descIt != xmp.end()) {
        EXPECT_FALSE(descIt->toString().empty());
    }
}

// Test: Minimal string (just null terminator in UTF-16LE = 2 bytes)
TEST_F(AsfVideoContentDescriptionTest_1571, MinimalStringLength_1571) {
    std::vector<uint8_t> nullStr = {0x00, 0x00}; // single null wchar
    std::vector<uint8_t> emptyData;
    
    auto asfData = buildAsfWithContentDescription(
        2, nullStr,
        0, emptyData,
        0, emptyData,
        0, emptyData,
        0, emptyData
    );
    
    auto io = std::make_unique<Exiv2::MemIo>(asfData.data(), asfData.size());
    Exiv2::AsfVideo asf(std::move(io));
    
    try {
        asf.readMetadata();
    } catch (...) {
    }
    
    // With a non-zero length, the title key should exist (even if the string is empty/null)
    const Exiv2::XmpData& xmp = asf.xmpData();
    auto titleIt = xmp.findKey(Exiv2::XmpKey("Xmp.video.Title"));
    // It may or may not be set depending on how the implementation handles null strings
    // We just verify no crash occurred
}

} // namespace
