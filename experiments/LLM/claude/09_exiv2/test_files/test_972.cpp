#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <cstring>
#include <vector>
#include <memory>

#include "exiv2/pngimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

namespace {

// PNG signature bytes
const uint8_t pngSignature[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};

// Helper to create a PNG chunk
std::vector<uint8_t> makeChunk(const std::string& type, const std::vector<uint8_t>& data) {
    std::vector<uint8_t> chunk;
    // Length (4 bytes, big-endian)
    uint32_t len = static_cast<uint32_t>(data.size());
    chunk.push_back((len >> 24) & 0xFF);
    chunk.push_back((len >> 16) & 0xFF);
    chunk.push_back((len >> 8) & 0xFF);
    chunk.push_back(len & 0xFF);
    // Type (4 bytes)
    for (int i = 0; i < 4; i++) {
        chunk.push_back(static_cast<uint8_t>(type[i]));
    }
    // Data
    chunk.insert(chunk.end(), data.begin(), data.end());
    // CRC (4 bytes) - compute CRC32 over type + data
    // For simplicity, use a basic CRC calculation
    // We'll use zlib's crc32 since exiv2 depends on zlib
    uint32_t crc = 0xFFFFFFFF;
    // CRC over type
    for (int i = 0; i < 4; i++) {
        uint8_t byte = static_cast<uint8_t>(type[i]);
        crc ^= byte;
        for (int j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }
    // CRC over data
    for (auto byte : data) {
        crc ^= byte;
        for (int j = 0; j < 8; j++) {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            else
                crc >>= 1;
        }
    }
    crc ^= 0xFFFFFFFF;
    chunk.push_back((crc >> 24) & 0xFF);
    chunk.push_back((crc >> 16) & 0xFF);
    chunk.push_back((crc >> 8) & 0xFF);
    chunk.push_back(crc & 0xFF);
    return chunk;
}

// Helper to build a minimal valid PNG with IHDR and IEND
std::vector<uint8_t> buildMinimalPng() {
    std::vector<uint8_t> png(pngSignature, pngSignature + 8);

    // IHDR chunk: 13 bytes of data
    std::vector<uint8_t> ihdrData = {
        0x00, 0x00, 0x00, 0x01, // width = 1
        0x00, 0x00, 0x00, 0x01, // height = 1
        0x08,                   // bit depth = 8
        0x02,                   // color type = RGB
        0x00,                   // compression method
        0x00,                   // filter method
        0x00                    // interlace method
    };
    auto ihdrChunk = makeChunk("IHDR", ihdrData);
    png.insert(png.end(), ihdrChunk.begin(), ihdrChunk.end());

    // IEND chunk: 0 bytes of data
    auto iendChunk = makeChunk("IEND", {});
    png.insert(png.end(), iendChunk.begin(), iendChunk.end());

    return png;
}

// Helper to build a PNG with additional chunks between IHDR and IEND
std::vector<uint8_t> buildPngWithChunks(const std::vector<std::pair<std::string, std::vector<uint8_t>>>& extraChunks) {
    std::vector<uint8_t> png(pngSignature, pngSignature + 8);

    // IHDR chunk
    std::vector<uint8_t> ihdrData = {
        0x00, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x00, 0x01,
        0x08, 0x02, 0x00, 0x00, 0x00
    };
    auto ihdrChunk = makeChunk("IHDR", ihdrData);
    png.insert(png.end(), ihdrChunk.begin(), ihdrChunk.end());

    // Extra chunks
    for (const auto& [type, data] : extraChunks) {
        auto chunk = makeChunk(type, data);
        png.insert(png.end(), chunk.begin(), chunk.end());
    }

    // IEND chunk
    auto iendChunk = makeChunk("IEND", {});
    png.insert(png.end(), iendChunk.begin(), iendChunk.end());

    return png;
}

} // anonymous namespace

class PngImageTest_972 : public ::testing::Test {
protected:
    std::unique_ptr<PngImage> createPngImage(const std::vector<uint8_t>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<PngImage>(std::move(io), false);
    }

    std::unique_ptr<PngImage> createPngImageFromEmpty() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<PngImage>(std::move(io), false);
    }
};

// Test that printStructure with kpsBasic on a minimal valid PNG produces expected header
TEST_F(PngImageTest_972, PrintStructureBasicMinimalPng_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 0));
    
    std::string output = out.str();
    // Should contain the structure header
    EXPECT_NE(output.find("STRUCTURE OF PNG FILE"), std::string::npos);
    EXPECT_NE(output.find("address"), std::string::npos);
    EXPECT_NE(output.find("chunk"), std::string::npos);
    EXPECT_NE(output.find("length"), std::string::npos);
    // Should contain IHDR and IEND chunks
    EXPECT_NE(output.find("IHDR"), std::string::npos);
    EXPECT_NE(output.find("IEND"), std::string::npos);
}

// Test that printStructure throws on non-PNG data
TEST_F(PngImageTest_972, PrintStructureThrowsOnNonPngData_972) {
    std::vector<uint8_t> notPng = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    auto img = createPngImage(notPng);
    std::ostringstream out;
    
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Exiv2::Error);
}

// Test that printStructure throws on empty data
TEST_F(PngImageTest_972, PrintStructureThrowsOnEmptyData_972) {
    auto img = createPngImageFromEmpty();
    std::ostringstream out;
    
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Exiv2::Error);
}

// Test that printStructure with kpsXMP on a minimal PNG (no XMP) produces no output
TEST_F(PngImageTest_972, PrintStructureXmpNoXmpChunk_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsXMP, 0));
    
    std::string output = out.str();
    // No XMP data, so output should not contain XMP-related content
    // The header is not printed for kpsXMP (bPrint is false)
    EXPECT_EQ(output.find("STRUCTURE OF PNG FILE"), std::string::npos);
}

// Test that printStructure with kpsIccProfile on a minimal PNG produces no output
TEST_F(PngImageTest_972, PrintStructureIccProfileNoIccChunk_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsIccProfile, 0));
    
    std::string output = out.str();
    EXPECT_EQ(output.find("STRUCTURE OF PNG FILE"), std::string::npos);
}

// Test that printStructure with kpsRecursive on a minimal PNG includes header
TEST_F(PngImageTest_972, PrintStructureRecursiveMinimalPng_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsRecursive, 0));
    
    std::string output = out.str();
    EXPECT_NE(output.find("STRUCTURE OF PNG FILE"), std::string::npos);
    EXPECT_NE(output.find("IHDR"), std::string::npos);
    EXPECT_NE(output.find("IEND"), std::string::npos);
}

// Test that printStructure throws when given a JPEG signature
TEST_F(PngImageTest_972, PrintStructureThrowsOnJpegData_972) {
    std::vector<uint8_t> jpegData = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 0x4A, 0x46};
    auto img = createPngImage(jpegData);
    std::ostringstream out;
    
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Exiv2::Error);
}

// Test that printStructure with kpsBasic on a PNG with a tEXt chunk
TEST_F(PngImageTest_972, PrintStructureBasicWithTextChunk_972) {
    // Create a tEXt chunk with "Comment\0Hello World"
    std::vector<uint8_t> textData;
    std::string keyword = "Comment";
    textData.insert(textData.end(), keyword.begin(), keyword.end());
    textData.push_back(0x00); // null separator
    std::string text = "Hello World";
    textData.insert(textData.end(), text.begin(), text.end());
    
    auto pngData = buildPngWithChunks({{"tEXt", textData}});
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 0));
    
    std::string output = out.str();
    EXPECT_NE(output.find("tEXt"), std::string::npos);
    EXPECT_NE(output.find("IHDR"), std::string::npos);
    EXPECT_NE(output.find("IEND"), std::string::npos);
}

// Test that printStructure with kpsNone does not output structure info
// Note: kpsNone is not in the handled list, so it should not do anything special
TEST_F(PngImageTest_972, PrintStructureNoneOption_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    // kpsNone is 0, not in the if-condition, so the function may do nothing or call base
    // The base Image::printStructure is a virtual function that may or may not throw
    // We just test it doesn't crash or it throws (implementation dependent)
    try {
        img->printStructure(out, kpsNone, 0);
    } catch (const Exiv2::Error&) {
        // Acceptable
    }
}

// Test printStructure with truncated PNG (signature only, no chunks)
TEST_F(PngImageTest_972, PrintStructureThrowsOnTruncatedPng_972) {
    std::vector<uint8_t> truncated(pngSignature, pngSignature + 8);
    auto img = createPngImage(truncated);
    std::ostringstream out;
    
    // Should throw because there's no chunk data after the signature
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Exiv2::Error);
}

// Test printStructure with corrupted chunk length (too large)
TEST_F(PngImageTest_972, PrintStructureThrowsOnCorruptedChunkLength_972) {
    std::vector<uint8_t> png(pngSignature, pngSignature + 8);
    // Add a chunk with impossibly large length
    png.push_back(0xFF); // length byte 1
    png.push_back(0xFF); // length byte 2
    png.push_back(0xFF); // length byte 3
    png.push_back(0xFF); // length byte 4
    png.push_back('I');
    png.push_back('H');
    png.push_back('D');
    png.push_back('R');
    
    auto img = createPngImage(png);
    std::ostringstream out;
    
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Exiv2::Error);
}

// Test mimeType returns "image/png"
TEST_F(PngImageTest_972, MimeTypeReturnsPng_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    
    EXPECT_EQ(img->mimeType(), "image/png");
}

// Test printStructure with kpsBasic outputs checksum information
TEST_F(PngImageTest_972, PrintStructureBasicContainsChecksum_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 0));
    
    std::string output = out.str();
    // Checksums should appear as "0x" prefixed hex values
    EXPECT_NE(output.find("0x"), std::string::npos);
}

// Test printStructure on PNG with multiple text-type chunks
TEST_F(PngImageTest_972, PrintStructureBasicMultipleChunks_972) {
    std::vector<uint8_t> textData1;
    std::string kw1 = "Comment";
    textData1.insert(textData1.end(), kw1.begin(), kw1.end());
    textData1.push_back(0x00);
    std::string t1 = "First comment";
    textData1.insert(textData1.end(), t1.begin(), t1.end());

    std::vector<uint8_t> textData2;
    std::string kw2 = "Software";
    textData2.insert(textData2.end(), kw2.begin(), kw2.end());
    textData2.push_back(0x00);
    std::string t2 = "TestSoftware";
    textData2.insert(textData2.end(), t2.begin(), t2.end());

    auto pngData = buildPngWithChunks({{"tEXt", textData1}, {"tEXt", textData2}});
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 0));
    
    std::string output = out.str();
    // Both tEXt chunks should be listed
    // Count occurrences of "tEXt"
    size_t pos = 0;
    int count = 0;
    while ((pos = output.find("tEXt", pos)) != std::string::npos) {
        count++;
        pos += 4;
    }
    EXPECT_GE(count, 2);
}

// Test printStructure with partially valid PNG (valid signature, incomplete chunk header)
TEST_F(PngImageTest_972, PrintStructureThrowsOnIncompleteChunkHeader_972) {
    std::vector<uint8_t> png(pngSignature, pngSignature + 8);
    // Only 4 bytes of chunk header instead of 8
    png.push_back(0x00);
    png.push_back(0x00);
    png.push_back(0x00);
    png.push_back(0x0D);
    
    auto img = createPngImage(png);
    std::ostringstream out;
    
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Exiv2::Error);
}

// Test that printStructure on PNG with only signature bytes (exactly 8 bytes) throws
TEST_F(PngImageTest_972, PrintStructureThrowsOnSignatureOnly_972) {
    std::vector<uint8_t> sigOnly(pngSignature, pngSignature + 8);
    auto img = createPngImage(sigOnly);
    std::ostringstream out;
    
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Exiv2::Error);
}

// Test printStructure depth parameter doesn't break basic output
TEST_F(PngImageTest_972, PrintStructureBasicWithDepth_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 5));
    
    std::string output = out.str();
    EXPECT_NE(output.find("STRUCTURE OF PNG FILE"), std::string::npos);
}

// Test that the PNG with an IDAT chunk between IHDR and IEND works
TEST_F(PngImageTest_972, PrintStructureBasicWithIdatChunk_972) {
    std::vector<uint8_t> idatData = {0x08, 0xD7, 0x63, 0xF8, 0x0F, 0x00, 0x00, 0x01, 0x01, 0x00};
    auto pngData = buildPngWithChunks({{"IDAT", idatData}});
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 0));
    
    std::string output = out.str();
    EXPECT_NE(output.find("IDAT"), std::string::npos);
}

// Test that bad PNG signature (one byte off) throws error
TEST_F(PngImageTest_972, PrintStructureThrowsOnBadSignature_972) {
    std::vector<uint8_t> badSig = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0B}; // last byte wrong
    // Add some more data to avoid EOF issues before signature check
    for (int i = 0; i < 100; i++) badSig.push_back(0x00);
    
    auto img = createPngImage(badSig);
    std::ostringstream out;
    
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Exiv2::Error);
}

// Test readMetadata on non-PNG data throws
TEST_F(PngImageTest_972, ReadMetadataThrowsOnNonPng_972) {
    std::vector<uint8_t> notPng = {0x00, 0x01, 0x02, 0x03};
    auto img = createPngImage(notPng);
    
    EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test readMetadata on a minimal valid PNG doesn't throw
TEST_F(PngImageTest_972, ReadMetadataMinimalPng_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    
    EXPECT_NO_THROW(img->readMetadata());
}

// Test that the PngImage constructor with create=true works
TEST_F(PngImageTest_972, ConstructorWithCreateTrue_972) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW(PngImage(std::move(io), true));
}

// Test that the PngImage constructor with create=false works
TEST_F(PngImageTest_972, ConstructorWithCreateFalse_972) {
    auto io = std::make_unique<MemIo>();
    EXPECT_NO_THROW(PngImage(std::move(io), false));
}

// Test printStructure output format - address column starts at 0 for first chunk
TEST_F(PngImageTest_972, PrintStructureBasicAddressFormat_972) {
    auto pngData = buildMinimalPng();
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    img->printStructure(out, kpsBasic, 0);
    
    std::string output = out.str();
    // First chunk (IHDR) should start at address 8 (after 8-byte PNG signature)
    EXPECT_NE(output.find("8"), std::string::npos);
}

// Test that printStructure with kpsRecursive and a Software tEXt chunk outputs software info
TEST_F(PngImageTest_972, PrintStructureRecursiveWithSoftwareChunk_972) {
    std::vector<uint8_t> textData;
    std::string keyword = "Software";
    textData.insert(textData.end(), keyword.begin(), keyword.end());
    textData.push_back(0x00);
    std::string text = "Exiv2 Test Suite";
    textData.insert(textData.end(), text.begin(), text.end());
    
    auto pngData = buildPngWithChunks({{"tEXt", textData}});
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsRecursive, 0));
    
    std::string output = out.str();
    EXPECT_NE(output.find("Software"), std::string::npos);
}

// Test that printStructure with kpsRecursive and a Comment tEXt chunk outputs comment
TEST_F(PngImageTest_972, PrintStructureRecursiveWithCommentChunk_972) {
    std::vector<uint8_t> textData;
    std::string keyword = "Comment";
    textData.insert(textData.end(), keyword.begin(), keyword.end());
    textData.push_back(0x00);
    std::string text = "This is a test comment for PNG";
    textData.insert(textData.end(), text.begin(), text.end());
    
    auto pngData = buildPngWithChunks({{"tEXt", textData}});
    auto img = createPngImage(pngData);
    std::ostringstream out;
    
    EXPECT_NO_THROW(img->printStructure(out, kpsRecursive, 0));
    
    std::string output = out.str();
    EXPECT_NE(output.find("Comment"), std::string::npos);
}
