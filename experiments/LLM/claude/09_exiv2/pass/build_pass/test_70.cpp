#include <gtest/gtest.h>
#include <sstream>
#include <cstring>
#include <vector>

#include "exiv2/webpimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/image.hpp"
#include "exiv2/types.hpp"

using namespace Exiv2;

namespace {

// Helper to build a minimal valid WebP file in memory
// WebP file format:
//   bytes 0-3: "RIFF"
//   bytes 4-7: file size - 8 (little endian)
//   bytes 8-11: "WEBP"
//   Then chunks follow...
std::vector<byte> makeMinimalWebP() {
    // A minimal WebP with just RIFF header + WEBP signature + a VP8 chunk
    // VP8 chunk with minimal data
    std::vector<byte> data;

    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');

    // We'll compute file size later. Placeholder for now.
    // filesize = total - 8
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);

    // "WEBP"
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');

    // VP8 chunk
    data.push_back('V'); data.push_back('P'); data.push_back('8'); data.push_back(' ');

    // VP8 chunk size (10 bytes of payload)
    uint32_t vp8Size = 10;
    data.push_back(static_cast<byte>(vp8Size & 0xFF));
    data.push_back(static_cast<byte>((vp8Size >> 8) & 0xFF));
    data.push_back(static_cast<byte>((vp8Size >> 16) & 0xFF));
    data.push_back(static_cast<byte>((vp8Size >> 24) & 0xFF));

    // VP8 payload (10 bytes of zeros)
    for (uint32_t i = 0; i < vp8Size; i++) {
        data.push_back(0);
    }

    // Update file size field: total size - 8
    uint32_t filesize = static_cast<uint32_t>(data.size()) - 8;
    data[4] = static_cast<byte>(filesize & 0xFF);
    data[5] = static_cast<byte>((filesize >> 8) & 0xFF);
    data[6] = static_cast<byte>((filesize >> 16) & 0xFF);
    data[7] = static_cast<byte>((filesize >> 24) & 0xFF);

    return data;
}

// Helper to build a WebP file with an XMP chunk
std::vector<byte> makeWebPWithXMP(const std::string& xmpData) {
    std::vector<byte> data;

    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    // Placeholder for file size
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    // "WEBP"
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');

    // XMP chunk: "XMP " tag
    data.push_back('X'); data.push_back('M'); data.push_back('P'); data.push_back(' ');
    uint32_t xmpSize = static_cast<uint32_t>(xmpData.size());
    data.push_back(static_cast<byte>(xmpSize & 0xFF));
    data.push_back(static_cast<byte>((xmpSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>((xmpSize >> 16) & 0xFF));
    data.push_back(static_cast<byte>((xmpSize >> 24) & 0xFF));
    for (size_t i = 0; i < xmpData.size(); i++) {
        data.push_back(static_cast<byte>(xmpData[i]));
    }
    // Padding if odd size
    if (xmpSize % 2 != 0) {
        data.push_back(0);
    }

    // Update file size
    uint32_t filesize = static_cast<uint32_t>(data.size()) - 8;
    data[4] = static_cast<byte>(filesize & 0xFF);
    data[5] = static_cast<byte>((filesize >> 8) & 0xFF);
    data[6] = static_cast<byte>((filesize >> 16) & 0xFF);
    data[7] = static_cast<byte>((filesize >> 24) & 0xFF);

    return data;
}

// Helper to build a WebP file with an ICCP chunk
std::vector<byte> makeWebPWithICCP(const std::vector<byte>& iccData) {
    std::vector<byte> data;

    // "RIFF"
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    // "WEBP"
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');

    // ICCP chunk
    data.push_back('I'); data.push_back('C'); data.push_back('C'); data.push_back('P');
    uint32_t iccSize = static_cast<uint32_t>(iccData.size());
    data.push_back(static_cast<byte>(iccSize & 0xFF));
    data.push_back(static_cast<byte>((iccSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>((iccSize >> 16) & 0xFF));
    data.push_back(static_cast<byte>((iccSize >> 24) & 0xFF));
    for (size_t i = 0; i < iccData.size(); i++) {
        data.push_back(iccData[i]);
    }
    if (iccSize % 2 != 0) {
        data.push_back(0);
    }

    uint32_t filesize = static_cast<uint32_t>(data.size()) - 8;
    data[4] = static_cast<byte>(filesize & 0xFF);
    data[5] = static_cast<byte>((filesize >> 8) & 0xFF);
    data[6] = static_cast<byte>((filesize >> 16) & 0xFF);
    data[7] = static_cast<byte>((filesize >> 24) & 0xFF);

    return data;
}

} // anonymous namespace

class WebPImageTest_70 : public ::testing::Test {
protected:
    std::unique_ptr<WebPImage> createWebPImage(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<WebPImage>(std::move(io));
    }

    std::unique_ptr<WebPImage> createWebPImageFromEmpty() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<WebPImage>(std::move(io));
    }
};

// Test: mimeType returns correct MIME type for WebP
TEST_F(WebPImageTest_70, MimeTypeReturnsWebP_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    EXPECT_EQ(img->mimeType(), "image/webp");
}

// Test: printStructure with kpsBasic on a minimal valid WebP
TEST_F(WebPImageTest_70, PrintStructureBasicMinimalWebP_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 0));
    std::string output = out.str();
    // Should contain structural information
    EXPECT_NE(output.find("STRUCTURE OF WEBP FILE"), std::string::npos);
    EXPECT_NE(output.find("Chunk"), std::string::npos);
    EXPECT_NE(output.find("Length"), std::string::npos);
    EXPECT_NE(output.find("Offset"), std::string::npos);
}

// Test: printStructure with kpsBasic includes RIFF tag
TEST_F(WebPImageTest_70, PrintStructureBasicContainsRIFF_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    std::ostringstream out;
    img->printStructure(out, kpsBasic, 0);
    std::string output = out.str();
    EXPECT_NE(output.find("RIFF"), std::string::npos);
}

// Test: printStructure with kpsBasic includes VP8 chunk
TEST_F(WebPImageTest_70, PrintStructureBasicContainsVP8_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    std::ostringstream out;
    img->printStructure(out, kpsBasic, 0);
    std::string output = out.str();
    EXPECT_NE(output.find("VP8"), std::string::npos);
}

// Test: printStructure throws on non-WebP data
TEST_F(WebPImageTest_70, PrintStructureThrowsOnNonWebPData_70) {
    std::vector<byte> garbage = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    auto img = createWebPImage(garbage);
    std::ostringstream out;
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Error);
}

// Test: printStructure throws on empty data
TEST_F(WebPImageTest_70, PrintStructureThrowsOnEmptyData_70) {
    auto img = createWebPImageFromEmpty();
    std::ostringstream out;
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Error);
}

// Test: printStructure with kpsXMP outputs XMP payload
TEST_F(WebPImageTest_70, PrintStructureXMPOutputsPayload_70) {
    std::string xmpContent = "<x:xmpmeta>test xmp data</x:xmpmeta>";
    auto data = makeWebPWithXMP(xmpContent);
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsXMP, 0));
    std::string output = out.str();
    EXPECT_NE(output.find(xmpContent), std::string::npos);
}

// Test: printStructure with kpsIccProfile outputs ICC payload
TEST_F(WebPImageTest_70, PrintStructureIccProfileOutputsPayload_70) {
    std::vector<byte> iccPayload = {'I', 'C', 'C', '_', 'D', 'A', 'T', 'A'};
    auto data = makeWebPWithICCP(iccPayload);
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsIccProfile, 0));
    std::string output = out.str();
    // The ICC payload should appear in output
    EXPECT_NE(output.find("ICC_DATA"), std::string::npos);
}

// Test: printStructure with kpsNone produces no output for valid WebP
TEST_F(WebPImageTest_70, PrintStructureNoneProducesNoOutput_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsNone, 0));
    std::string output = out.str();
    EXPECT_TRUE(output.empty());
}

// Test: printStructure with kpsRecursive on minimal WebP (no EXIF)
TEST_F(WebPImageTest_70, PrintStructureRecursiveNoExif_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsRecursive, 0));
    std::string output = out.str();
    EXPECT_NE(output.find("STRUCTURE OF WEBP FILE"), std::string::npos);
}

// Test: printStructure with depth > 0 adds indentation
TEST_F(WebPImageTest_70, PrintStructureWithDepthIndentation_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 2));
    std::string output = out.str();
    // With depth=2 there should be indentation
    EXPECT_NE(output.find("STRUCTURE OF WEBP FILE"), std::string::npos);
}

// Test: printStructure throws NotAnImage for RIFF file that's not WEBP
TEST_F(WebPImageTest_70, PrintStructureThrowsForNonWebPRIFF_70) {
    std::vector<byte> data = {
        'R', 'I', 'F', 'F',
        4, 0, 0, 0,
        'A', 'V', 'I', ' '
    };
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Error);
}

// Test: printStructure with kpsXMP on WebP without XMP produces no XMP output
TEST_F(WebPImageTest_70, PrintStructureXMPNoXMPChunk_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsXMP, 0));
    std::string output = out.str();
    // No XMP payload, output should be empty or minimal
    EXPECT_TRUE(output.empty() || output.find("<x:xmpmeta") == std::string::npos);
}

// Test: printStructure with kpsIccProfile on WebP without ICCP produces no ICC output
TEST_F(WebPImageTest_70, PrintStructureIccNoIccChunk_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsIccProfile, 0));
    std::string output = out.str();
    EXPECT_TRUE(output.empty());
}

// Test: printStructure with kpsIptcErase doesn't throw on valid WebP
TEST_F(WebPImageTest_70, PrintStructureIptcEraseNoThrow_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsIptcErase, 0));
}

// Test: setComment does not throw (even though it may be a no-op)
TEST_F(WebPImageTest_70, SetCommentNoThrow_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    EXPECT_NO_THROW(img->setComment("test comment"));
}

// Test: setIptcData does not throw (even though it may be a no-op)
TEST_F(WebPImageTest_70, SetIptcDataNoThrow_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    IptcData iptc;
    EXPECT_NO_THROW(img->setIptcData(iptc));
}

// Test: Constructing WebPImage with MemIo works
TEST_F(WebPImageTest_70, ConstructWithMemIo_70) {
    auto data = makeMinimalWebP();
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    EXPECT_NO_THROW(WebPImage img(std::move(io)));
}

// Test: printStructure with very small (truncated) WebP-like data
TEST_F(WebPImageTest_70, PrintStructureTruncatedWebP_70) {
    // Just "RIFF" and size but no "WEBP" marker
    std::vector<byte> data = {'R', 'I', 'F', 'F', 0, 0, 0, 0};
    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_THROW(img->printStructure(out, kpsBasic, 0), Error);
}

// Test: WebP with odd-sized chunk (padding byte)
TEST_F(WebPImageTest_70, PrintStructureOddSizedChunkPadding_70) {
    std::vector<byte> data;

    // RIFF header
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');

    // VP8 chunk with odd payload size (11 bytes)
    data.push_back('V'); data.push_back('P'); data.push_back('8'); data.push_back(' ');
    uint32_t chunkSize = 11;
    data.push_back(static_cast<byte>(chunkSize & 0xFF));
    data.push_back(static_cast<byte>((chunkSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>((chunkSize >> 16) & 0xFF));
    data.push_back(static_cast<byte>((chunkSize >> 24) & 0xFF));
    for (uint32_t i = 0; i < chunkSize; i++) {
        data.push_back(0);
    }
    // Padding byte
    data.push_back(0);

    uint32_t filesize = static_cast<uint32_t>(data.size()) - 8;
    data[4] = static_cast<byte>(filesize & 0xFF);
    data[5] = static_cast<byte>((filesize >> 8) & 0xFF);
    data[6] = static_cast<byte>((filesize >> 16) & 0xFF);
    data[7] = static_cast<byte>((filesize >> 24) & 0xFF);

    auto img = createWebPImage(data);
    std::ostringstream out;
    EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 0));
    std::string output = out.str();
    EXPECT_NE(output.find("VP8"), std::string::npos);
}

// Test: Multiple chunks in WebP file
TEST_F(WebPImageTest_70, PrintStructureMultipleChunks_70) {
    std::vector<byte> data;

    // RIFF header
    data.push_back('R'); data.push_back('I'); data.push_back('F'); data.push_back('F');
    data.push_back(0); data.push_back(0); data.push_back(0); data.push_back(0);
    data.push_back('W'); data.push_back('E'); data.push_back('B'); data.push_back('P');

    // VP8 chunk
    data.push_back('V'); data.push_back('P'); data.push_back('8'); data.push_back(' ');
    uint32_t vp8Size = 8;
    data.push_back(static_cast<byte>(vp8Size & 0xFF));
    data.push_back(static_cast<byte>((vp8Size >> 8) & 0xFF));
    data.push_back(static_cast<byte>((vp8Size >> 16) & 0xFF));
    data.push_back(static_cast<byte>((vp8Size >> 24) & 0xFF));
    for (uint32_t i = 0; i < vp8Size; i++) {
        data.push_back(0);
    }

    // XMP chunk
    std::string xmpStr = "XMP_TEST_DATA";
    data.push_back('X'); data.push_back('M'); data.push_back('P'); data.push_back(' ');
    uint32_t xmpSize = static_cast<uint32_t>(xmpStr.size());
    data.push_back(static_cast<byte>(xmpSize & 0xFF));
    data.push_back(static_cast<byte>((xmpSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>((xmpSize >> 16) & 0xFF));
    data.push_back(static_cast<byte>((xmpSize >> 24) & 0xFF));
    for (size_t i = 0; i < xmpStr.size(); i++) {
        data.push_back(static_cast<byte>(xmpStr[i]));
    }
    if (xmpSize % 2 != 0) data.push_back(0);

    uint32_t filesize = static_cast<uint32_t>(data.size()) - 8;
    data[4] = static_cast<byte>(filesize & 0xFF);
    data[5] = static_cast<byte>((filesize >> 8) & 0xFF);
    data[6] = static_cast<byte>((filesize >> 16) & 0xFF);
    data[7] = static_cast<byte>((filesize >> 24) & 0xFF);

    auto img = createWebPImage(data);

    // Test basic print
    {
        std::ostringstream out;
        EXPECT_NO_THROW(img->printStructure(out, kpsBasic, 0));
        std::string output = out.str();
        EXPECT_NE(output.find("VP8"), std::string::npos);
        EXPECT_NE(output.find("XMP"), std::string::npos);
    }

    // Test XMP extraction
    {
        std::ostringstream out;
        EXPECT_NO_THROW(img->printStructure(out, kpsXMP, 0));
        std::string output = out.str();
        EXPECT_NE(output.find("XMP_TEST_DATA"), std::string::npos);
    }
}

// Test: good() returns true for valid in-memory data
TEST_F(WebPImageTest_70, GoodReturnsTrueForValidData_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    EXPECT_TRUE(img->good());
}

// Test: io() returns reference to the BasicIo object
TEST_F(WebPImageTest_70, IoReturnsValidReference_70) {
    auto data = makeMinimalWebP();
    auto img = createWebPImage(data);
    const BasicIo& io = img->io();
    EXPECT_EQ(io.size(), data.size());
}
