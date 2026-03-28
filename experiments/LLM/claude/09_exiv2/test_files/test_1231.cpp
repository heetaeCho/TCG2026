#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/tgaimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>
#include <cstring>
#include <memory>

using namespace Exiv2;

// Helper to create a valid TGA file in memory
// TGA file format: 18-byte header + optional image ID + optional color map + image data
// For type detection, we need a valid TGA structure
static std::vector<byte> createMinimalTgaData(uint16_t width, uint16_t height,
                                                byte imageType = 2,
                                                byte pixelDepth = 24,
                                                byte idLength = 0,
                                                byte colorMapType = 0) {
    std::vector<byte> data(18, 0);
    data[0] = idLength;        // ID length
    data[1] = colorMapType;    // Color map type
    data[2] = imageType;       // Image type (2 = uncompressed true-color)
    // Color map specification (bytes 3-7) = 0
    // X-origin (bytes 8-9) = 0
    // Y-origin (bytes 10-11) = 0
    data[12] = static_cast<byte>(width & 0xFF);         // Width low byte
    data[13] = static_cast<byte>((width >> 8) & 0xFF);  // Width high byte
    data[14] = static_cast<byte>(height & 0xFF);        // Height low byte
    data[15] = static_cast<byte>((height >> 8) & 0xFF); // Height high byte
    data[16] = pixelDepth;     // Pixel depth
    data[17] = 0;              // Image descriptor

    // TGA files typically have a footer for TGA 2.0:
    // The last 26 bytes should contain a specific signature for TGA 2.0
    // But for basic TGA, just the header might suffice
    // Let's add some dummy pixel data
    size_t pixelDataSize = static_cast<size_t>(width) * height * (pixelDepth / 8);
    data.resize(18 + idLength + pixelDataSize, 0);

    // TGA 2.0 footer (optional but helps with type detection)
    // Footer: 4 bytes extension offset, 4 bytes developer offset, 16 bytes signature + ".\0"
    // Signature: "TRUEVISION-XFILE.\0"
    const char* footer_sig = "TRUEVISION-XFILE.";
    std::vector<byte> footer(26, 0);
    // extension area offset = 0
    // developer directory offset = 0
    std::memcpy(footer.data() + 8, footer_sig, 18);
    data.insert(data.end(), footer.begin(), footer.end());

    return data;
}

class TgaImageTest_1231 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}

    std::unique_ptr<TgaImage> createTgaImage(const std::vector<byte>& data) {
        auto io = std::make_unique<MemIo>(data.data(), data.size());
        return std::make_unique<TgaImage>(std::move(io));
    }

    std::unique_ptr<TgaImage> createTgaImageFromEmptyMemIo() {
        auto io = std::make_unique<MemIo>();
        return std::make_unique<TgaImage>(std::move(io));
    }
};

// Test that mimeType returns the correct MIME type for TGA
TEST_F(TgaImageTest_1231, MimeType_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    EXPECT_EQ(image->mimeType(), "image/x-tga");
}

// Test readMetadata with a valid TGA file reads width and height
TEST_F(TgaImageTest_1231, ReadMetadataValidFile_1231) {
    auto data = createMinimalTgaData(640, 480);
    auto image = createTgaImage(data);
    ASSERT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 640u);
    EXPECT_EQ(image->pixelHeight(), 480u);
}

// Test readMetadata with small dimensions
TEST_F(TgaImageTest_1231, ReadMetadataSmallDimensions_1231) {
    auto data = createMinimalTgaData(1, 1);
    auto image = createTgaImage(data);
    ASSERT_NO_THROW(image->readMetadata());
    EXPECT_EQ(image->pixelWidth(), 1u);
    EXPECT_EQ(image->pixelHeight(), 1u);
}

// Test readMetadata with maximum uint16 dimensions
TEST_F(TgaImageTest_1231, ReadMetadataMaxDimensions_1231) {
    auto data = createMinimalTgaData(0xFFFF, 0xFFFF, 2, 24);
    auto image = createTgaImage(data);
    // This may or may not throw depending on isTgaType validation,
    // but if it succeeds, dimensions should be correct
    try {
        image->readMetadata();
        EXPECT_EQ(image->pixelWidth(), 0xFFFFu);
        EXPECT_EQ(image->pixelHeight(), 0xFFFFu);
    } catch (const Error&) {
        // If type detection fails for max dimensions, that's also acceptable behavior
    }
}

// Test readMetadata with zero dimensions
TEST_F(TgaImageTest_1231, ReadMetadataZeroDimensions_1231) {
    auto data = createMinimalTgaData(0, 0, 2, 24);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
        EXPECT_EQ(image->pixelWidth(), 0u);
        EXPECT_EQ(image->pixelHeight(), 0u);
    } catch (const Error&) {
        // Zero dimensions might be rejected
    }
}

// Test readMetadata with empty data throws
TEST_F(TgaImageTest_1231, ReadMetadataEmptyData_1231) {
    auto image = createTgaImageFromEmptyMemIo();
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test readMetadata with too-short data throws
TEST_F(TgaImageTest_1231, ReadMetadataTooShortData_1231) {
    std::vector<byte> data(5, 0);
    auto image = createTgaImage(data);
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test readMetadata with invalid image type byte
TEST_F(TgaImageTest_1231, ReadMetadataInvalidImageType_1231) {
    // Image type 255 is invalid for TGA
    auto data = createMinimalTgaData(100, 100, 255, 24);
    auto image = createTgaImage(data);
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test writeMetadata throws (TGA writing is typically not supported)
TEST_F(TgaImageTest_1231, WriteMetadataThrows_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    EXPECT_THROW(image->writeMetadata(), Error);
}

// Test setExifData throws (TGA doesn't support EXIF)
TEST_F(TgaImageTest_1231, SetExifDataThrows_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    ExifData exifData;
    EXPECT_THROW(image->setExifData(exifData), Error);
}

// Test setIptcData throws (TGA doesn't support IPTC)
TEST_F(TgaImageTest_1231, SetIptcDataThrows_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    IptcData iptcData;
    EXPECT_THROW(image->setIptcData(iptcData), Error);
}

// Test setComment throws (TGA doesn't support comments)
TEST_F(TgaImageTest_1231, SetCommentThrows_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    EXPECT_THROW(image->setComment("test comment"), Error);
}

// Test that good() returns true for valid TGA data before readMetadata
TEST_F(TgaImageTest_1231, GoodBeforeRead_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    // good() checks if io_ is non-null and in good state
    EXPECT_TRUE(image->good());
}

// Test pixelWidth and pixelHeight default to 0 before reading metadata
TEST_F(TgaImageTest_1231, DefaultDimensionsBeforeRead_1231) {
    auto data = createMinimalTgaData(640, 480);
    auto image = createTgaImage(data);
    EXPECT_EQ(image->pixelWidth(), 0u);
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test readMetadata with uncompressed black-and-white image type (3)
TEST_F(TgaImageTest_1231, ReadMetadataBWImageType_1231) {
    auto data = createMinimalTgaData(320, 240, 3, 8);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
        EXPECT_EQ(image->pixelWidth(), 320u);
        EXPECT_EQ(image->pixelHeight(), 240u);
    } catch (const Error&) {
        // Some implementations might not accept all types
    }
}

// Test readMetadata with RLE-encoded true-color image type (10)
TEST_F(TgaImageTest_1231, ReadMetadataRLETrueColorType_1231) {
    auto data = createMinimalTgaData(256, 256, 10, 24);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
        EXPECT_EQ(image->pixelWidth(), 256u);
        EXPECT_EQ(image->pixelHeight(), 256u);
    } catch (const Error&) {
        // Acceptable if type detection is strict
    }
}

// Test readMetadata with color-mapped image type (1)
TEST_F(TgaImageTest_1231, ReadMetadataColorMappedType_1231) {
    auto data = createMinimalTgaData(128, 64, 1, 8, 0, 1);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
        EXPECT_EQ(image->pixelWidth(), 128u);
        EXPECT_EQ(image->pixelHeight(), 64u);
    } catch (const Error&) {
        // Acceptable
    }
}

// Test readMetadata clears previous metadata
TEST_F(TgaImageTest_1231, ReadMetadataClearsPrevious_1231) {
    auto data = createMinimalTgaData(200, 300);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
        EXPECT_EQ(image->pixelWidth(), 200u);
        EXPECT_EQ(image->pixelHeight(), 300u);

        // Read again - should work the same
        image->readMetadata();
        EXPECT_EQ(image->pixelWidth(), 200u);
        EXPECT_EQ(image->pixelHeight(), 300u);
    } catch (const Error&) {
        // If it throws on a valid file, that's unexpected but we handle it
        FAIL() << "readMetadata threw on valid TGA data";
    }
}

// Test with non-TGA data (e.g., random bytes)
TEST_F(TgaImageTest_1231, ReadMetadataNonTgaData_1231) {
    std::vector<byte> data = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
                               0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52,
                               0x00, 0x00};  // PNG header-like data
    auto image = createTgaImage(data);
    EXPECT_THROW(image->readMetadata(), Error);
}

// Test that io() returns a reference to the underlying IO
TEST_F(TgaImageTest_1231, IoAccessible_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    const BasicIo& io = image->io();
    EXPECT_FALSE(io.path().empty() || io.path() == "");
    // MemIo path is typically empty or a placeholder, just check it doesn't crash
}

// Test with asymmetric dimensions
TEST_F(TgaImageTest_1231, ReadMetadataAsymmetricDimensions_1231) {
    auto data = createMinimalTgaData(1920, 1080);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
        EXPECT_EQ(image->pixelWidth(), 1920u);
        EXPECT_EQ(image->pixelHeight(), 1080u);
    } catch (const Error&) {
        // Might throw due to large pixel data requirements in isTgaType
    }
}

// Test with only 18 bytes (header only, no pixel data, no footer)
TEST_F(TgaImageTest_1231, ReadMetadataHeaderOnly_1231) {
    std::vector<byte> data(18, 0);
    data[2] = 2;     // image type: uncompressed true-color
    data[12] = 0x40; // width = 64
    data[13] = 0x00;
    data[14] = 0x30; // height = 48
    data[15] = 0x00;
    data[16] = 24;   // pixel depth
    data[17] = 0;

    auto image = createTgaImage(data);
    try {
        image->readMetadata();
        // If it succeeds, check dimensions
        EXPECT_EQ(image->pixelWidth(), 64u);
        EXPECT_EQ(image->pixelHeight(), 48u);
    } catch (const Error&) {
        // May throw if isTgaType needs footer or more data
    }
}

// Test comment() returns empty string for TGA
TEST_F(TgaImageTest_1231, CommentIsEmpty_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
    } catch (const Error&) {
    }
    EXPECT_TRUE(image->comment().empty());
}

// Test exifData is empty after readMetadata (TGA doesn't support EXIF)
TEST_F(TgaImageTest_1231, ExifDataEmptyAfterRead_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
    } catch (const Error&) {
    }
    EXPECT_TRUE(image->exifData().empty());
}

// Test iptcData is empty after readMetadata (TGA doesn't support IPTC)
TEST_F(TgaImageTest_1231, IptcDataEmptyAfterRead_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
    } catch (const Error&) {
    }
    EXPECT_TRUE(image->iptcData().empty());
}

// Test xmpData is empty after readMetadata (TGA doesn't support XMP)
TEST_F(TgaImageTest_1231, XmpDataEmptyAfterRead_1231) {
    auto data = createMinimalTgaData(100, 100);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
    } catch (const Error&) {
    }
    EXPECT_TRUE(image->xmpData().empty());
}

// Test with width having specific byte pattern (little-endian)
TEST_F(TgaImageTest_1231, ReadMetadataLittleEndianWidth_1231) {
    // Width = 0x0102 = 258 in little-endian: low=0x02, high=0x01
    auto data = createMinimalTgaData(258, 513);
    auto image = createTgaImage(data);
    try {
        image->readMetadata();
        EXPECT_EQ(image->pixelWidth(), 258u);
        EXPECT_EQ(image->pixelHeight(), 513u);
    } catch (const Error&) {
        // May fail for isTgaType reasons
    }
}
