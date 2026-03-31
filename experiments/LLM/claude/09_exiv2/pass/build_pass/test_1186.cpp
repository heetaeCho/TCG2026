#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/psdimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <cstring>
#include <vector>
#include <memory>

using namespace Exiv2;

// Helper function to create a minimal valid PSD file in memory
static std::vector<byte> createMinimalPsd(uint32_t width = 100, uint32_t height = 200) {
    std::vector<byte> data;
    
    // Signature: "8BPS" (4 bytes)
    data.push_back('8');
    data.push_back('B');
    data.push_back('P');
    data.push_back('S');
    
    // Version: 1 (2 bytes, big-endian)
    data.push_back(0x00);
    data.push_back(0x01);
    
    // Reserved: 6 bytes of zeros
    for (int i = 0; i < 6; i++)
        data.push_back(0x00);
    
    // Channels: 3 (2 bytes, big-endian)
    data.push_back(0x00);
    data.push_back(0x03);
    
    // Rows (height): 4 bytes, big-endian
    data.push_back((height >> 24) & 0xFF);
    data.push_back((height >> 16) & 0xFF);
    data.push_back((height >> 8) & 0xFF);
    data.push_back(height & 0xFF);
    
    // Columns (width): 4 bytes, big-endian
    data.push_back((width >> 24) & 0xFF);
    data.push_back((width >> 16) & 0xFF);
    data.push_back((width >> 8) & 0xFF);
    data.push_back(width & 0xFF);
    
    // Depth: 8 (2 bytes, big-endian)
    data.push_back(0x00);
    data.push_back(0x08);
    
    // Mode: RGB = 3 (2 bytes, big-endian)
    data.push_back(0x00);
    data.push_back(0x03);
    
    // Color mode data length: 0 (4 bytes, big-endian)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    
    // Image resources length: 0 (4 bytes, big-endian)
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    
    return data;
}

// Helper to create a PSD with a resource block
static std::vector<byte> createPsdWithResource(uint16_t resourceId, const std::vector<byte>& resourceData,
                                                uint32_t width = 100, uint32_t height = 200) {
    std::vector<byte> data;
    
    // Signature: "8BPS"
    data.push_back('8'); data.push_back('B'); data.push_back('P'); data.push_back('S');
    
    // Version: 1
    data.push_back(0x00); data.push_back(0x01);
    
    // Reserved: 6 zeros
    for (int i = 0; i < 6; i++) data.push_back(0x00);
    
    // Channels: 3
    data.push_back(0x00); data.push_back(0x03);
    
    // Rows (height)
    data.push_back((height >> 24) & 0xFF);
    data.push_back((height >> 16) & 0xFF);
    data.push_back((height >> 8) & 0xFF);
    data.push_back(height & 0xFF);
    
    // Columns (width)
    data.push_back((width >> 24) & 0xFF);
    data.push_back((width >> 16) & 0xFF);
    data.push_back((width >> 8) & 0xFF);
    data.push_back(width & 0xFF);
    
    // Depth: 8
    data.push_back(0x00); data.push_back(0x08);
    
    // Mode: RGB = 3
    data.push_back(0x00); data.push_back(0x03);
    
    // Color mode data length: 0
    data.push_back(0x00); data.push_back(0x00); data.push_back(0x00); data.push_back(0x00);
    
    // Build the resource block
    std::vector<byte> resourceBlock;
    // "8BIM" signature
    resourceBlock.push_back('8'); resourceBlock.push_back('B');
    resourceBlock.push_back('I'); resourceBlock.push_back('M');
    // Resource ID
    resourceBlock.push_back((resourceId >> 8) & 0xFF);
    resourceBlock.push_back(resourceId & 0xFF);
    // Pascal string (name): empty, padded to even
    resourceBlock.push_back(0x00); resourceBlock.push_back(0x00);
    // Resource size
    uint32_t resSize = static_cast<uint32_t>(resourceData.size());
    resourceBlock.push_back((resSize >> 24) & 0xFF);
    resourceBlock.push_back((resSize >> 16) & 0xFF);
    resourceBlock.push_back((resSize >> 8) & 0xFF);
    resourceBlock.push_back(resSize & 0xFF);
    // Resource data
    resourceBlock.insert(resourceBlock.end(), resourceData.begin(), resourceData.end());
    // Pad to even
    if (resourceData.size() % 2 != 0)
        resourceBlock.push_back(0x00);
    
    // Image resources length
    uint32_t resourcesLength = static_cast<uint32_t>(resourceBlock.size());
    data.push_back((resourcesLength >> 24) & 0xFF);
    data.push_back((resourcesLength >> 16) & 0xFF);
    data.push_back((resourcesLength >> 8) & 0xFF);
    data.push_back(resourcesLength & 0xFF);
    
    // Append resource block
    data.insert(data.end(), resourceBlock.begin(), resourceBlock.end());
    
    return data;
}

class PsdImageTest_1186 : public ::testing::Test {
protected:
    std::unique_ptr<PsdImage> createPsdImage(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<PsdImage>(std::move(io));
    }
    
    std::unique_ptr<PsdImage> createPsdImageFromEmpty() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<PsdImage>(std::move(io));
    }
};

// Test: Reading metadata from a minimal valid PSD file
TEST_F(PsdImageTest_1186, ReadMetadataValidMinimalPsd_1186) {
    auto data = createMinimalPsd(640, 480);
    auto image = createPsdImage(data);
    
    ASSERT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 640u);
    EXPECT_EQ(image->pixelHeight(), 480u);
}

// Test: Reading metadata from an empty/invalid file should throw
TEST_F(PsdImageTest_1186, ReadMetadataEmptyFileThrows_1186) {
    std::vector<byte> emptyData;
    auto io = std::make_unique<MemIo>();
    auto image = std::make_unique<PsdImage>(std::move(io));
    
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test: Reading metadata from a file with invalid signature should throw
TEST_F(PsdImageTest_1186, ReadMetadataInvalidSignatureThrows_1186) {
    auto data = createMinimalPsd();
    // Corrupt the signature
    data[0] = 'X';
    auto image = createPsdImage(data);
    
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test: Pixel dimensions are correctly read with various sizes
TEST_F(PsdImageTest_1186, ReadMetadataPixelDimensions_1186) {
    auto data = createMinimalPsd(1920, 1080);
    auto image = createPsdImage(data);
    
    ASSERT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 1920u);
    EXPECT_EQ(image->pixelHeight(), 1080u);
}

// Test: Pixel dimensions with maximum values
TEST_F(PsdImageTest_1186, ReadMetadataLargePixelDimensions_1186) {
    auto data = createMinimalPsd(30000, 30000);
    auto image = createPsdImage(data);
    
    ASSERT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 30000u);
    EXPECT_EQ(image->pixelHeight(), 30000u);
}

// Test: Pixel dimensions of 1x1
TEST_F(PsdImageTest_1186, ReadMetadataMinimalPixelDimensions_1186) {
    auto data = createMinimalPsd(1, 1);
    auto image = createPsdImage(data);
    
    ASSERT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 1u);
    EXPECT_EQ(image->pixelHeight(), 1u);
}

// Test: Truncated header (too short) should throw
TEST_F(PsdImageTest_1186, ReadMetadataTruncatedHeaderThrows_1186) {
    auto data = createMinimalPsd();
    // Truncate to less than 26 bytes after the signature check
    data.resize(20);
    auto image = createPsdImage(data);
    
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test: mimeType returns correct value
TEST_F(PsdImageTest_1186, MimeTypeReturnsCorrectValue_1186) {
    auto data = createMinimalPsd();
    auto image = createPsdImage(data);
    
    EXPECT_EQ(image->mimeType(), "image/x-photoshop");
}

// Test: setComment throws (PSD doesn't support comments)
TEST_F(PsdImageTest_1186, SetCommentThrows_1186) {
    auto data = createMinimalPsd();
    auto image = createPsdImage(data);
    
    EXPECT_THROW(image->setComment("test comment"), Error);
}

// Test: Reading a file with only 4 bytes (not valid PSD)
TEST_F(PsdImageTest_1186, ReadMetadataFourBytesOnlyThrows_1186) {
    std::vector<byte> data = {'8', 'B', 'P', 'S'};
    auto image = createPsdImage(data);
    
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test: Valid PSD with zero resource length
TEST_F(PsdImageTest_1186, ReadMetadataZeroResourceLength_1186) {
    auto data = createMinimalPsd(320, 240);
    auto image = createPsdImage(data);
    
    ASSERT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 320u);
    EXPECT_EQ(image->pixelHeight(), 240u);
}

// Test: PSD with resource block
TEST_F(PsdImageTest_1186, ReadMetadataWithResourceBlock_1186) {
    std::vector<byte> resourceData = {0x01, 0x02, 0x03, 0x04};
    auto data = createPsdWithResource(0x0404, resourceData, 800, 600);
    auto image = createPsdImage(data);
    
    ASSERT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 800u);
    EXPECT_EQ(image->pixelHeight(), 600u);
}

// Test: Data truncated right after color mode section
TEST_F(PsdImageTest_1186, ReadMetadataTruncatedAfterColorModeThrows_1186) {
    auto data = createMinimalPsd();
    // Remove the image resources length (last 4 bytes)
    data.resize(data.size() - 4);
    auto image = createPsdImage(data);
    
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test: Corrupted resources length (too large)
TEST_F(PsdImageTest_1186, ReadMetadataCorruptedResourcesLengthThrows_1186) {
    auto data = createMinimalPsd();
    // Set resources length to a very large value (last 4 bytes)
    size_t resLenOffset = data.size() - 4;
    data[resLenOffset] = 0xFF;
    data[resLenOffset + 1] = 0xFF;
    data[resLenOffset + 2] = 0xFF;
    data[resLenOffset + 3] = 0xFF;
    auto image = createPsdImage(data);
    
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test: PSD with corrupted resource block (non-8BIM signature in resource)
TEST_F(PsdImageTest_1186, ReadMetadataBadResourceSignature_1186) {
    std::vector<byte> resourceData = {0x00, 0x00};
    auto data = createPsdWithResource(0x0400, resourceData);
    // Corrupt the "8BIM" signature in the resource block
    // The resource block starts after: 26 (header) + 4 (color mode len) + 4 (resources len)
    size_t resourceStart = 26 + 4 + 4;
    if (resourceStart < data.size()) {
        data[resourceStart] = 'X'; // Change '8' to 'X'
    }
    auto image = createPsdImage(data);
    
    // Should not throw - it should just break out of the resource loop
    ASSERT_NO_THROW(image->readMetadata());
}

// Test: File that starts with correct signature but has wrong version
TEST_F(PsdImageTest_1186, ReadMetadataWrongVersionThrows_1186) {
    auto data = createMinimalPsd();
    // Change version from 1 to 99
    data[4] = 0x00;
    data[5] = 0x63; // 99
    auto image = createPsdImage(data);
    
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test: ExifData is initially empty after reading minimal PSD
TEST_F(PsdImageTest_1186, ReadMetadataExifDataEmpty_1186) {
    auto data = createMinimalPsd();
    auto image = createPsdImage(data);
    
    image->readMetadata();
    EXPECT_TRUE(image->exifData().empty());
}

// Test: IptcData is initially empty after reading minimal PSD
TEST_F(PsdImageTest_1186, ReadMetadataIptcDataEmpty_1186) {
    auto data = createMinimalPsd();
    auto image = createPsdImage(data);
    
    image->readMetadata();
    EXPECT_TRUE(image->iptcData().empty());
}

// Test: XmpData is initially empty after reading minimal PSD
TEST_F(PsdImageTest_1186, ReadMetadataXmpDataEmpty_1186) {
    auto data = createMinimalPsd();
    auto image = createPsdImage(data);
    
    image->readMetadata();
    EXPECT_TRUE(image->xmpData().empty());
}

// Test: Completely random garbage data should throw
TEST_F(PsdImageTest_1186, ReadMetadataGarbageDataThrows_1186) {
    std::vector<byte> garbage(100, 0xAB);
    auto image = createPsdImage(garbage);
    
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test: Resources length claiming data but file is truncated
TEST_F(PsdImageTest_1186, ReadMetadataResourcesLengthMismatchThrows_1186) {
    auto data = createMinimalPsd();
    // Change resources length to 100 but don't add any data
    size_t resLenOffset = data.size() - 4;
    data[resLenOffset] = 0x00;
    data[resLenOffset + 1] = 0x00;
    data[resLenOffset + 2] = 0x00;
    data[resLenOffset + 3] = 0x64; // 100
    auto image = createPsdImage(data);
    
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test: Good method should return true for valid data
TEST_F(PsdImageTest_1186, GoodReturnsTrueForValidIo_1186) {
    auto data = createMinimalPsd();
    auto image = createPsdImage(data);
    
    EXPECT_TRUE(image->good());
}

// Test: Verify that clearMetadata is called (metadata should be empty after read of minimal PSD)
TEST_F(PsdImageTest_1186, ReadMetadataClearsExistingMetadata_1186) {
    auto data = createMinimalPsd();
    auto image = createPsdImage(data);
    
    // Set some metadata
    image->exifData()["Exif.Image.Make"] = "TestMake";
    
    // Read should clear it
    image->readMetadata();
    EXPECT_TRUE(image->exifData().empty());
}

// Test: Reading metadata twice should work
TEST_F(PsdImageTest_1186, ReadMetadataTwiceWorks_1186) {
    auto data = createMinimalPsd(512, 512);
    auto image = createPsdImage(data);
    
    ASSERT_NO_THROW(image->readMetadata());
    ASSERT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 512u);
    EXPECT_EQ(image->pixelHeight(), 512u);
}

// Test: Resources with small length (less than 8) should throw corrupted metadata
TEST_F(PsdImageTest_1186, ReadMetadataResourcesLengthTooSmallThrows_1186) {
    auto data = createMinimalPsd();
    // Set resources length to 4 (less than 8 needed for a resource header)
    size_t resLenOffset = data.size() - 4;
    data[resLenOffset] = 0x00;
    data[resLenOffset + 1] = 0x00;
    data[resLenOffset + 2] = 0x00;
    data[resLenOffset + 3] = 0x04; // 4 bytes
    // Add 4 bytes of padding
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    data.push_back(0x00);
    auto image = createPsdImage(data);
    
    EXPECT_THROW(image->readMetadata(), Error);
}
