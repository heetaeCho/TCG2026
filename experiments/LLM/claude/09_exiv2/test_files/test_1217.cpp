#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/jpgimage.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>

#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>

using namespace Exiv2;

// Helper to create a minimal valid JPEG in memory
static std::vector<byte> createMinimalJpeg() {
    // SOI + EOI
    std::vector<byte> data = {0xFF, 0xD8, 0xFF, 0xD9};
    return data;
}

// Helper to create a JPEG with a COM (comment) segment
static std::vector<byte> createJpegWithComment(const std::string& comment) {
    std::vector<byte> data;
    // SOI
    data.push_back(0xFF);
    data.push_back(0xD8);
    // COM marker
    data.push_back(0xFF);
    data.push_back(0xFE);
    uint16_t segSize = static_cast<uint16_t>(2 + comment.size());
    data.push_back(static_cast<byte>((segSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>(segSize & 0xFF));
    for (char c : comment) {
        data.push_back(static_cast<byte>(c));
    }
    // EOI
    data.push_back(0xFF);
    data.push_back(0xD9);
    return data;
}

// Helper to create a JPEG with SOF0 segment (to test pixel dimensions)
static std::vector<byte> createJpegWithSOF0(uint16_t height, uint16_t width, byte numComponents = 3) {
    std::vector<byte> data;
    // SOI
    data.push_back(0xFF);
    data.push_back(0xD8);
    // SOF0 marker (0xFFC0)
    data.push_back(0xFF);
    data.push_back(0xC0);
    // Segment size: 2(size) + 1(precision) + 2(height) + 2(width) + 1(num_components) + 3*numComponents
    uint16_t segSize = static_cast<uint16_t>(2 + 1 + 2 + 2 + 1 + 3 * numComponents);
    data.push_back(static_cast<byte>((segSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>(segSize & 0xFF));
    // Precision
    data.push_back(8);
    // Height (big endian)
    data.push_back(static_cast<byte>((height >> 8) & 0xFF));
    data.push_back(static_cast<byte>(height & 0xFF));
    // Width (big endian)
    data.push_back(static_cast<byte>((width >> 8) & 0xFF));
    data.push_back(static_cast<byte>(width & 0xFF));
    // Number of components
    data.push_back(numComponents);
    // Component data (3 bytes per component)
    for (int i = 0; i < numComponents; ++i) {
        data.push_back(static_cast<byte>(i + 1)); // component id
        data.push_back(0x11); // sampling factor
        data.push_back(0x00); // quantization table
    }
    // EOI
    data.push_back(0xFF);
    data.push_back(0xD9);
    return data;
}

// Helper: create JPEG with SOF0 and comment
static std::vector<byte> createJpegWithSOF0AndComment(uint16_t height, uint16_t width, const std::string& comment) {
    std::vector<byte> data;
    // SOI
    data.push_back(0xFF);
    data.push_back(0xD8);

    // COM marker
    data.push_back(0xFF);
    data.push_back(0xFE);
    uint16_t comSize = static_cast<uint16_t>(2 + comment.size());
    data.push_back(static_cast<byte>((comSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>(comSize & 0xFF));
    for (char c : comment) {
        data.push_back(static_cast<byte>(c));
    }

    // SOF0 marker
    byte numComponents = 3;
    data.push_back(0xFF);
    data.push_back(0xC0);
    uint16_t segSize = static_cast<uint16_t>(2 + 1 + 2 + 2 + 1 + 3 * numComponents);
    data.push_back(static_cast<byte>((segSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>(segSize & 0xFF));
    data.push_back(8);
    data.push_back(static_cast<byte>((height >> 8) & 0xFF));
    data.push_back(static_cast<byte>(height & 0xFF));
    data.push_back(static_cast<byte>((width >> 8) & 0xFF));
    data.push_back(static_cast<byte>(width & 0xFF));
    data.push_back(numComponents);
    for (int i = 0; i < numComponents; ++i) {
        data.push_back(static_cast<byte>(i + 1));
        data.push_back(0x11);
        data.push_back(0x00);
    }

    // EOI
    data.push_back(0xFF);
    data.push_back(0xD9);
    return data;
}

class JpegImageTest_1217 : public ::testing::Test {
protected:
    void SetUp() override {
        // Suppress warnings during tests
        LogMsg::setLevel(LogMsg::mute);
    }

    void TearDown() override {
        LogMsg::setLevel(LogMsg::warn);
    }

    // Helper to create a JpegImage from memory data
    static Image::UniquePtr createJpegFromMemory(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return ImageFactory::open(std::move(io));
    }
};

// Test: Reading metadata from a minimal valid JPEG (SOI + EOI)
TEST_F(JpegImageTest_1217, ReadMetadataMinimalJpeg_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_TRUE(image->exifData().empty());
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_TRUE(image->xmpData().empty());
    EXPECT_TRUE(image->comment().empty());
}

// Test: Reading comment from a JPEG with a COM segment
TEST_F(JpegImageTest_1217, ReadMetadataWithComment_1217) {
    std::string testComment = "Hello, World!";
    auto data = createJpegWithComment(testComment);
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->comment(), testComment);
}

// Test: Comment with trailing null bytes gets trimmed
TEST_F(JpegImageTest_1217, ReadMetadataCommentTrimsTrailingNulls_1217) {
    std::string commentWithNulls = std::string("Test\0\0", 6);
    auto data = createJpegWithComment(commentWithNulls);
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->comment(), "Test");
}

// Test: Empty comment segment
TEST_F(JpegImageTest_1217, ReadMetadataEmptyComment_1217) {
    auto data = createJpegWithComment("");
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    // Empty comment should remain empty
    EXPECT_TRUE(image->comment().empty());
}

// Test: Reading pixel dimensions from SOF0 segment
TEST_F(JpegImageTest_1217, ReadMetadataPixelDimensions_1217) {
    uint16_t expectedHeight = 480;
    uint16_t expectedWidth = 640;
    auto data = createJpegWithSOF0(expectedHeight, expectedWidth);
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelHeight(), expectedHeight);
    EXPECT_EQ(image->pixelWidth(), expectedWidth);
}

// Test: SOF0 with large dimensions
TEST_F(JpegImageTest_1217, ReadMetadataLargePixelDimensions_1217) {
    uint16_t expectedHeight = 65535;
    uint16_t expectedWidth = 65535;
    auto data = createJpegWithSOF0(expectedHeight, expectedWidth);
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelHeight(), expectedHeight);
    EXPECT_EQ(image->pixelWidth(), expectedWidth);
}

// Test: SOF0 with single color component
TEST_F(JpegImageTest_1217, ReadMetadataSingleColorComponent_1217) {
    uint16_t expectedHeight = 100;
    uint16_t expectedWidth = 200;
    auto data = createJpegWithSOF0(expectedHeight, expectedWidth, 1);
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelHeight(), expectedHeight);
    EXPECT_EQ(image->pixelWidth(), expectedWidth);
}

// Test: Reading metadata from non-JPEG data should throw
TEST_F(JpegImageTest_1217, ReadMetadataNotAJpegThrows_1217) {
    std::vector<byte> data = {0x00, 0x01, 0x02, 0x03};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    // ImageFactory::open may throw or return null for invalid data
    EXPECT_THROW(ImageFactory::open(std::move(io)), Error);
}

// Test: Reading from empty data should throw
TEST_F(JpegImageTest_1217, ReadMetadataEmptyDataThrows_1217) {
    std::vector<byte> data;
    auto io = std::make_unique<MemIo>(data.data(), 0);
    EXPECT_THROW(ImageFactory::open(std::move(io)), Error);
}

// Test: JPEG with both comment and SOF0
TEST_F(JpegImageTest_1217, ReadMetadataCommentAndDimensions_1217) {
    std::string comment = "Test image";
    uint16_t height = 768;
    uint16_t width = 1024;
    auto data = createJpegWithSOF0AndComment(height, width, comment);
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->comment(), comment);
    EXPECT_EQ(image->pixelHeight(), height);
    EXPECT_EQ(image->pixelWidth(), width);
}

// Test: Calling readMetadata clears previous metadata
TEST_F(JpegImageTest_1217, ReadMetadataClearsPreviousData_1217) {
    std::string comment = "Initial comment";
    auto data = createJpegWithComment(comment);
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);

    image->readMetadata();
    EXPECT_EQ(image->comment(), comment);

    // Read again - should still have the same comment (cleared and re-read)
    image->readMetadata();
    EXPECT_EQ(image->comment(), comment);
}

// Test: No exif data in minimal JPEG
TEST_F(JpegImageTest_1217, ReadMetadataNoExifData_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_TRUE(image->exifData().empty());
    EXPECT_EQ(image->exifData().count(), 0u);
}

// Test: No IPTC data in minimal JPEG
TEST_F(JpegImageTest_1217, ReadMetadataNoIptcData_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_EQ(image->iptcData().count(), 0u);
}

// Test: No XMP data in minimal JPEG
TEST_F(JpegImageTest_1217, ReadMetadataNoXmpData_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_TRUE(image->xmpData().empty());
    EXPECT_TRUE(image->xmpPacket().empty());
}

// Test: Pixel dimensions are zero when no SOF segment is present
TEST_F(JpegImageTest_1217, ReadMetadataNoSOFZeroDimensions_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_EQ(image->pixelHeight(), 0u);
    EXPECT_EQ(image->pixelWidth(), 0u);
}

// Test: JPEG with SOS marker stops parsing
TEST_F(JpegImageTest_1217, ReadMetadataSOSStopsParsing_1217) {
    std::vector<byte> data;
    // SOI
    data.push_back(0xFF);
    data.push_back(0xD8);
    // SOS marker with minimal segment
    data.push_back(0xFF);
    data.push_back(0xDA);
    // Segment length = 2 (just the length field)
    data.push_back(0x00);
    data.push_back(0x02);
    // Some scan data followed by EOI
    data.push_back(0xFF);
    data.push_back(0xD9);

    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
}

// Test: JPEG with only SOI (no EOI) - truncated file
TEST_F(JpegImageTest_1217, ReadMetadataTruncatedJpeg_1217) {
    std::vector<byte> data = {0xFF, 0xD8};
    auto io = std::make_unique<MemIo>(data.data(), data.size());
    // This might throw or handle gracefully
    try {
        auto image = ImageFactory::open(std::move(io));
        if (image) {
            // readMetadata may throw for truncated data
            try {
                image->readMetadata();
            } catch (const Error&) {
                // Expected - truncated data
            }
        }
    } catch (const Error&) {
        // Also acceptable
    }
}

// Test: Good state after reading minimal JPEG
TEST_F(JpegImageTest_1217, GoodStateAfterReadMetadata_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_TRUE(image->good());
}

// Test: JPEG mime type
TEST_F(JpegImageTest_1217, MimeType_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->mimeType(), "image/jpeg");
}

// Test: ICC profile not defined for minimal JPEG
TEST_F(JpegImageTest_1217, NoIccProfileInMinimalJpeg_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_FALSE(image->iccProfileDefined());
}

// Test: Byte order is invalid for JPEG without EXIF
TEST_F(JpegImageTest_1217, ByteOrderInvalidWithoutExif_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_EQ(image->byteOrder(), invalidByteOrder);
}

// Test: setComment and clearComment
TEST_F(JpegImageTest_1217, SetAndClearComment_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();

    image->setComment("New comment");
    EXPECT_EQ(image->comment(), "New comment");

    image->clearComment();
    EXPECT_TRUE(image->comment().empty());
}

// Test: clearMetadata clears everything
TEST_F(JpegImageTest_1217, ClearMetadata_1217) {
    std::string comment = "Test";
    auto data = createJpegWithComment(comment);
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_EQ(image->comment(), comment);

    image->clearMetadata();
    EXPECT_TRUE(image->comment().empty());
    EXPECT_TRUE(image->exifData().empty());
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_TRUE(image->xmpData().empty());
}

// Test: Reading a real JPEG file if available (test with actual test data)
// This tests with a programmatically created JPEG with APP1 Exif marker
TEST_F(JpegImageTest_1217, ReadMetadataWithExifSegment_1217) {
    std::vector<byte> data;
    // SOI
    data.push_back(0xFF);
    data.push_back(0xD8);

    // APP1 marker with Exif header but minimal/invalid Exif data
    data.push_back(0xFF);
    data.push_back(0xE1);

    // Exif ID: "Exif\0\0"
    std::vector<byte> exifId = {'E', 'x', 'i', 'f', 0x00, 0x00};

    // Minimal TIFF header (little endian, 42, offset to IFD0=8, IFD0 with 0 entries)
    std::vector<byte> tiffData = {
        'I', 'I',             // Little endian
        0x2A, 0x00,           // Magic number 42
        0x08, 0x00, 0x00, 0x00, // Offset to IFD0
        0x00, 0x00            // 0 entries in IFD0
    };

    uint16_t segSize = static_cast<uint16_t>(2 + exifId.size() + tiffData.size());
    data.push_back(static_cast<byte>((segSize >> 8) & 0xFF));
    data.push_back(static_cast<byte>(segSize & 0xFF));
    data.insert(data.end(), exifId.begin(), exifId.end());
    data.insert(data.end(), tiffData.begin(), tiffData.end());

    // EOI
    data.push_back(0xFF);
    data.push_back(0xD9);

    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    // Byte order should be set to littleEndian from the TIFF header
    EXPECT_EQ(image->byteOrder(), littleEndian);
}

// Test: SOF0 with zero height (DNL case)
TEST_F(JpegImageTest_1217, ReadMetadataSOF0ZeroHeight_1217) {
    auto data = createJpegWithSOF0(0, 640);
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    // Height of 0 means it wasn't counted as found
    EXPECT_EQ(image->pixelHeight(), 0u);
    EXPECT_EQ(image->pixelWidth(), 640u);
}

// Test: Multiple COM segments - only first should be read
TEST_F(JpegImageTest_1217, ReadMetadataMultipleComments_1217) {
    std::vector<byte> data;
    // SOI
    data.push_back(0xFF);
    data.push_back(0xD8);

    // First COM
    std::string comment1 = "First";
    data.push_back(0xFF);
    data.push_back(0xFE);
    uint16_t size1 = static_cast<uint16_t>(2 + comment1.size());
    data.push_back(static_cast<byte>((size1 >> 8) & 0xFF));
    data.push_back(static_cast<byte>(size1 & 0xFF));
    for (char c : comment1) data.push_back(static_cast<byte>(c));

    // Second COM
    std::string comment2 = "Second";
    data.push_back(0xFF);
    data.push_back(0xFE);
    uint16_t size2 = static_cast<uint16_t>(2 + comment2.size());
    data.push_back(static_cast<byte>((size2 >> 8) & 0xFF));
    data.push_back(static_cast<byte>(size2 & 0xFF));
    for (char c : comment2) data.push_back(static_cast<byte>(c));

    // EOI
    data.push_back(0xFF);
    data.push_back(0xD9);

    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    // Only the first comment should be stored
    EXPECT_EQ(image->comment(), "First");
}

// Test: Supports metadata check
TEST_F(JpegImageTest_1217, SupportsMetadata_1217) {
    auto data = createMinimalJpeg();
    auto image = createJpegFromMemory(data);
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->supportsMetadata(MetadataId::mdExif));
    EXPECT_TRUE(image->supportsMetadata(MetadataId::mdIptc));
    EXPECT_TRUE(image->supportsMetadata(MetadataId::mdXmp));
    EXPECT_TRUE(image->supportsMetadata(MetadataId::mdComment));
}
