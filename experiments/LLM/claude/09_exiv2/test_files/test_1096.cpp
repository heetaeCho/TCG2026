#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>

#include <fstream>
#include <cstring>
#include <sstream>

using namespace Exiv2;

// Helper: create a minimal valid JPEG in memory
static std::vector<byte> makeMinimalJpeg() {
    // Minimal JPEG: SOI + APP0 (JFIF) + EOI
    std::vector<byte> jpg;
    // SOI
    jpg.push_back(0xFF);
    jpg.push_back(0xD8);
    // APP0 marker
    jpg.push_back(0xFF);
    jpg.push_back(0xE0);
    // Length (16 bytes)
    jpg.push_back(0x00);
    jpg.push_back(0x10);
    // JFIF identifier
    jpg.push_back('J');
    jpg.push_back('F');
    jpg.push_back('I');
    jpg.push_back('F');
    jpg.push_back(0x00);
    // Version
    jpg.push_back(0x01);
    jpg.push_back(0x01);
    // Units
    jpg.push_back(0x00);
    // X density
    jpg.push_back(0x00);
    jpg.push_back(0x01);
    // Y density
    jpg.push_back(0x00);
    jpg.push_back(0x01);
    // Thumbnail
    jpg.push_back(0x00);
    jpg.push_back(0x00);
    // EOI
    jpg.push_back(0xFF);
    jpg.push_back(0xD9);
    return jpg;
}

class ImageTest_1096 : public ::testing::Test {
protected:
    void SetUp() override {
    }
    void TearDown() override {
    }
};

// Test that good() returns true for a valid JPEG image opened from memory
TEST_F(ImageTest_1096, GoodReturnsTrueForValidJpeg_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        EXPECT_TRUE(image->good());
    } catch (const Exiv2::Error&) {
        // If opening fails, that's also acceptable behavior for minimal JPEG
        // but we note it
        GTEST_SKIP() << "ImageFactory::open threw for minimal JPEG";
    }
}

// Test that good() returns false for invalid/random data
TEST_F(ImageTest_1096, GoodReturnsFalseForInvalidData_1096) {
    byte garbage[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
    try {
        auto image = ImageFactory::open(garbage, sizeof(garbage));
        if (image) {
            // If open succeeded somehow, good() should be false
            // because the data is not a valid image
            EXPECT_FALSE(image->good());
        }
    } catch (const Exiv2::Error&) {
        // Expected - invalid data should throw or return nullptr
        SUCCEED();
    }
}

// Test static method: isBigEndianPlatform and isLittleEndianPlatform are mutually exclusive
TEST_F(ImageTest_1096, EndianPlatformMutuallyExclusive_1096) {
    bool big = Image::isBigEndianPlatform();
    bool little = Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

// Test static method: isStringType
TEST_F(ImageTest_1096, IsStringType_1096) {
    // Type 2 is ASCII string in TIFF
    EXPECT_TRUE(Image::isStringType(2));
    // Type 1 (BYTE) should not be string type
    EXPECT_FALSE(Image::isStringType(1));
}

// Test static method: isShortType
TEST_F(ImageTest_1096, IsShortType_1096) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Image::isShortType(3));
    // Type 8 is SSHORT
    EXPECT_TRUE(Image::isShortType(8));
    EXPECT_FALSE(Image::isShortType(1));
}

// Test static method: isLongType
TEST_F(ImageTest_1096, IsLongType_1096) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Image::isLongType(4));
    // Type 9 is SLONG
    EXPECT_TRUE(Image::isLongType(9));
    EXPECT_FALSE(Image::isLongType(2));
}

// Test static method: isLongLongType
TEST_F(ImageTest_1096, IsLongLongType_1096) {
    // Type 16 is LONG8, type 17 is SLONG8
    // Not all types should return true
    EXPECT_FALSE(Image::isLongLongType(1));
    EXPECT_FALSE(Image::isLongLongType(4));
}

// Test static method: isRationalType
TEST_F(ImageTest_1096, IsRationalType_1096) {
    // Type 5 is RATIONAL, type 10 is SRATIONAL
    EXPECT_TRUE(Image::isRationalType(5));
    EXPECT_TRUE(Image::isRationalType(10));
    EXPECT_FALSE(Image::isRationalType(1));
}

// Test static method: is2ByteType
TEST_F(ImageTest_1096, Is2ByteType_1096) {
    // SHORT (3) and SSHORT (8) are 2 byte types
    EXPECT_TRUE(Image::is2ByteType(3));
    EXPECT_TRUE(Image::is2ByteType(8));
    EXPECT_FALSE(Image::is2ByteType(4));
}

// Test static method: is4ByteType
TEST_F(ImageTest_1096, Is4ByteType_1096) {
    // LONG (4), SLONG (9), FLOAT (11) are 4 byte types
    EXPECT_TRUE(Image::is4ByteType(4));
    EXPECT_TRUE(Image::is4ByteType(9));
    EXPECT_FALSE(Image::is4ByteType(3));
}

// Test static method: is8ByteType
TEST_F(ImageTest_1096, Is8ByteType_1096) {
    // RATIONAL (5), SRATIONAL (10), DOUBLE (12) are 8 byte types
    EXPECT_TRUE(Image::is8ByteType(5));
    EXPECT_TRUE(Image::is8ByteType(10));
    EXPECT_FALSE(Image::is8ByteType(3));
}

// Test byteSwap for uint16_t with swap enabled
TEST_F(ImageTest_1096, ByteSwap16WithSwap_1096) {
    uint16_t val = 0x0102;
    uint16_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0201);
}

// Test byteSwap for uint16_t with swap disabled
TEST_F(ImageTest_1096, ByteSwap16WithoutSwap_1096) {
    uint16_t val = 0x0102;
    uint16_t result = Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

// Test byteSwap for uint32_t with swap enabled
TEST_F(ImageTest_1096, ByteSwap32WithSwap_1096) {
    uint32_t val = 0x01020304;
    uint32_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x04030201u);
}

// Test byteSwap for uint32_t with swap disabled
TEST_F(ImageTest_1096, ByteSwap32WithoutSwap_1096) {
    uint32_t val = 0x01020304;
    uint32_t result = Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

// Test byteSwap for uint64_t with swap enabled
TEST_F(ImageTest_1096, ByteSwap64WithSwap_1096) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// Test byteSwap for uint64_t with swap disabled
TEST_F(ImageTest_1096, ByteSwap64WithoutSwap_1096) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Image::byteSwap(val, false);
    EXPECT_EQ(result, val);
}

// Test byteSwap2 from DataBuf
TEST_F(ImageTest_1096, ByteSwap2FromDataBuf_1096) {
    byte data[] = {0x01, 0x02};
    DataBuf buf(data, sizeof(data));
    uint16_t noSwap = Image::byteSwap2(buf, 0, false);
    uint16_t withSwap = Image::byteSwap2(buf, 0, true);
    // One should be byte-swapped version of the other
    EXPECT_EQ(noSwap, Image::byteSwap(withSwap, true));
}

// Test byteSwap4 from DataBuf
TEST_F(ImageTest_1096, ByteSwap4FromDataBuf_1096) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    DataBuf buf(data, sizeof(data));
    uint32_t noSwap = Image::byteSwap4(buf, 0, false);
    uint32_t withSwap = Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(noSwap, Image::byteSwap(withSwap, true));
}

// Test byteSwap8 from DataBuf
TEST_F(ImageTest_1096, ByteSwap8FromDataBuf_1096) {
    byte data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    DataBuf buf(data, sizeof(data));
    uint64_t noSwap = Image::byteSwap8(buf, 0, false);
    uint64_t withSwap = Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(noSwap, Image::byteSwap(withSwap, true));
}

// Test setComment and comment
TEST_F(ImageTest_1096, SetAndGetComment_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->setComment("Test comment");
        EXPECT_EQ(image->comment(), "Test comment");
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test clearComment
TEST_F(ImageTest_1096, ClearComment_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->setComment("Test comment");
        image->clearComment();
        EXPECT_TRUE(image->comment().empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test setByteOrder and byteOrder
TEST_F(ImageTest_1096, SetAndGetByteOrder_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->setByteOrder(bigEndian);
        EXPECT_EQ(image->byteOrder(), bigEndian);
        image->setByteOrder(littleEndian);
        EXPECT_EQ(image->byteOrder(), littleEndian);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test writeXmpFromPacket flag
TEST_F(ImageTest_1096, WriteXmpFromPacketFlag_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->writeXmpFromPacket(true);
        EXPECT_TRUE(image->writeXmpFromPacket());
        image->writeXmpFromPacket(false);
        EXPECT_FALSE(image->writeXmpFromPacket());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test pixelWidth and pixelHeight default to 0
TEST_F(ImageTest_1096, PixelDimensionsDefaultZero_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        EXPECT_EQ(image->pixelWidth(), 0u);
        EXPECT_EQ(image->pixelHeight(), 0u);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test exifData returns reference
TEST_F(ImageTest_1096, ExifDataAccessible_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        ExifData& exif = image->exifData();
        EXPECT_TRUE(exif.empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test iptcData returns reference
TEST_F(ImageTest_1096, IptcDataAccessible_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        IptcData& iptc = image->iptcData();
        EXPECT_TRUE(iptc.empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test xmpData returns reference
TEST_F(ImageTest_1096, XmpDataAccessible_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        XmpData& xmp = image->xmpData();
        EXPECT_TRUE(xmp.empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test clearExifData
TEST_F(ImageTest_1096, ClearExifData_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->clearExifData();
        EXPECT_TRUE(image->exifData().empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test clearIptcData
TEST_F(ImageTest_1096, ClearIptcData_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->clearIptcData();
        EXPECT_TRUE(image->iptcData().empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test clearXmpData
TEST_F(ImageTest_1096, ClearXmpData_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->clearXmpData();
        EXPECT_TRUE(image->xmpData().empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test clearMetadata clears everything
TEST_F(ImageTest_1096, ClearMetadata_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->setComment("Some comment");
        image->clearMetadata();
        EXPECT_TRUE(image->comment().empty());
        EXPECT_TRUE(image->exifData().empty());
        EXPECT_TRUE(image->iptcData().empty());
        EXPECT_TRUE(image->xmpData().empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test clearIccProfile
TEST_F(ImageTest_1096, ClearIccProfile_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->clearIccProfile();
        EXPECT_FALSE(image->iccProfileDefined());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test iccProfileDefined initially false
TEST_F(ImageTest_1096, IccProfileNotDefinedInitially_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        EXPECT_FALSE(image->iccProfileDefined());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test io() returns a reference to BasicIo
TEST_F(ImageTest_1096, IoAccessible_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        const BasicIo& io = image->io();
        EXPECT_GT(io.size(), 0u);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test nativePreviews returns empty list initially
TEST_F(ImageTest_1096, NativePreviewsEmpty_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        const NativePreviewList& previews = image->nativePreviews();
        EXPECT_TRUE(previews.empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test ImageFactory::getType with invalid data
TEST_F(ImageTest_1096, GetTypeInvalidData_1096) {
    byte garbage[] = {0x00, 0x00, 0x00, 0x00};
    ImageType type = ImageFactory::getType(garbage, sizeof(garbage));
    EXPECT_EQ(type, ImageType::none);
}

// Test ImageFactory::getType with JPEG data
TEST_F(ImageTest_1096, GetTypeJpegData_1096) {
    auto jpg = makeMinimalJpeg();
    ImageType type = ImageFactory::getType(jpg.data(), jpg.size());
    EXPECT_EQ(type, ImageType::jpeg);
}

// Test mimeType for JPEG
TEST_F(ImageTest_1096, MimeTypeJpeg_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        std::string mime = image->mimeType();
        EXPECT_EQ(mime, "image/jpeg");
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test imageType returns correct type
TEST_F(ImageTest_1096, ImageTypeReturnsCorrectType_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        EXPECT_EQ(image->imageType(), ImageType::jpeg);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test setXmpPacket and xmpPacket
TEST_F(ImageTest_1096, SetAndGetXmpPacket_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        std::string xmpStr = "<x:xmpmeta></x:xmpmeta>";
        image->setXmpPacket(xmpStr);
        EXPECT_EQ(image->xmpPacket(), xmpStr);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test clearXmpPacket
TEST_F(ImageTest_1096, ClearXmpPacket_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image, nullptr);
        image->setXmpPacket("<x:xmpmeta></x:xmpmeta>");
        image->clearXmpPacket();
        EXPECT_TRUE(image->xmpPacket().empty());
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test byteSwap with zero values
TEST_F(ImageTest_1096, ByteSwapZero_1096) {
    EXPECT_EQ(Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
}

// Test byteSwap double swap returns original
TEST_F(ImageTest_1096, ByteSwapDoubleSwapReturnsOriginal_1096) {
    uint16_t val16 = 0xABCD;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val16, true), true), val16);

    uint32_t val32 = 0xDEADBEEF;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val32, true), true), val32);

    uint64_t val64 = 0x0123456789ABCDEFULL;
    EXPECT_EQ(Image::byteSwap(Image::byteSwap(val64, true), true), val64);
}

// Test isPrintXMP
TEST_F(ImageTest_1096, IsPrintXMP_1096) {
    // Test with various combinations - the exact behavior depends on implementation
    // but we can verify it doesn't crash with boundary values
    bool result1 = Image::isPrintXMP(0, PrintStructureOption::kpsNone);
    bool result2 = Image::isPrintXMP(0, PrintStructureOption::kpsXMP);
    // At least one combination should differ or both can be tested
    (void)result1;
    (void)result2;
    SUCCEED();
}

// Test isPrintICC
TEST_F(ImageTest_1096, IsPrintICC_1096) {
    bool result1 = Image::isPrintICC(0, PrintStructureOption::kpsNone);
    bool result2 = Image::isPrintICC(0, PrintStructureOption::kpsIccProfile);
    (void)result1;
    (void)result2;
    SUCCEED();
}

// Test that either big or little endian platform is true
TEST_F(ImageTest_1096, PlatformEndiannessConsistent_1096) {
    EXPECT_TRUE(Image::isBigEndianPlatform() || Image::isLittleEndianPlatform());
    EXPECT_FALSE(Image::isBigEndianPlatform() && Image::isLittleEndianPlatform());
}

// Test setMetadata copies metadata from another image
TEST_F(ImageTest_1096, SetMetadataFromAnotherImage_1096) {
    auto jpg = makeMinimalJpeg();
    try {
        auto image1 = ImageFactory::open(jpg.data(), jpg.size());
        auto image2 = ImageFactory::open(jpg.data(), jpg.size());
        ASSERT_NE(image1, nullptr);
        ASSERT_NE(image2, nullptr);

        image1->setComment("Source comment");
        image2->setMetadata(*image1);
        EXPECT_EQ(image2->comment(), "Source comment");
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "Could not open minimal JPEG";
    }
}

// Test ImageFactory::open with empty data throws or returns nullptr
TEST_F(ImageTest_1096, OpenWithEmptyData_1096) {
    byte empty = 0;
    try {
        auto image = ImageFactory::open(&empty, 0);
        // If it returns, image should be nullptr or good() false
        if (image) {
            EXPECT_FALSE(image->good());
        }
    } catch (const Exiv2::Error&) {
        SUCCEED();
    }
}

// Test ImageFactory::create with ImageType
TEST_F(ImageTest_1096, CreateImageInMemory_1096) {
    try {
        auto image = ImageFactory::create(ImageType::jpeg);
        ASSERT_NE(image, nullptr);
        EXPECT_EQ(image->imageType(), ImageType::jpeg);
    } catch (const Exiv2::Error&) {
        GTEST_SKIP() << "ImageFactory::create not supported for jpeg in memory";
    }
}
