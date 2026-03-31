#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>

#include <memory>
#include <sstream>
#include <cstring>

// We need a concrete Image subclass since Image is abstract (readMetadata/writeMetadata are pure virtual in some builds)
// We'll use a MemIo-based approach and try to use ImageFactory or a known image type.
// Since Image has pure virtual methods, we create a minimal concrete subclass for testing.

namespace {

class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 
                        static_cast<uint16_t>(Exiv2::MetadataId::mdExif) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdIptc) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdXmp) |
                        static_cast<uint16_t>(Exiv2::MetadataId::mdComment),
                        std::move(io)) {}

    void readMetadata() override {
        // No-op for testing
    }

    void writeMetadata() override {
        // No-op for testing
    }
};

std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
}

} // anonymous namespace

class ImageTest_1074 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// =============================================================================
// ExifData tests
// =============================================================================

TEST_F(ImageTest_1074, SetExifData_SetsExifDataCorrectly_1074) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    image_->setExifData(exifData);
    
    EXPECT_FALSE(image_->exifData().empty());
    EXPECT_EQ(image_->exifData().count(), 1u);
}

TEST_F(ImageTest_1074, ClearExifData_ClearsAllExifData_1074) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    image_->setExifData(exifData);
    
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_EQ(image_->exifData().count(), 0u);
}

TEST_F(ImageTest_1074, ExifData_InitiallyEmpty_1074) {
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_EQ(image_->exifData().count(), 0u);
}

TEST_F(ImageTest_1074, SetExifData_OverwritesPreviousData_1074) {
    Exiv2::ExifData exifData1;
    exifData1["Exif.Image.Make"] = "Camera1";
    image_->setExifData(exifData1);
    
    Exiv2::ExifData exifData2;
    exifData2["Exif.Image.Model"] = "Model2";
    exifData2["Exif.Image.Artist"] = "Artist2";
    image_->setExifData(exifData2);
    
    EXPECT_EQ(image_->exifData().count(), 2u);
    auto it = image_->exifData().findKey(Exiv2::ExifKey("Exif.Image.Make"));
    EXPECT_EQ(it, image_->exifData().end());
}

TEST_F(ImageTest_1074, SetExifData_EmptyExifData_1074) {
    // First set some data
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
    
    // Now set empty data
    Exiv2::ExifData emptyData;
    image_->setExifData(emptyData);
    EXPECT_TRUE(image_->exifData().empty());
}

// =============================================================================
// IptcData tests
// =============================================================================

TEST_F(ImageTest_1074, IptcData_InitiallyEmpty_1074) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1074, SetIptcData_SetsIptcDataCorrectly_1074) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    image_->setIptcData(iptcData);
    
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1074, ClearIptcData_ClearsAllIptcData_1074) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    image_->setIptcData(iptcData);
    
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// =============================================================================
// XmpData tests
// =============================================================================

TEST_F(ImageTest_1074, XmpData_InitiallyEmpty_1074) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1074, SetXmpData_SetsXmpDataCorrectly_1074) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test title";
    image_->setXmpData(xmpData);
    
    EXPECT_FALSE(image_->xmpData().empty());
}

TEST_F(ImageTest_1074, ClearXmpData_ClearsAllXmpData_1074) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test title";
    image_->setXmpData(xmpData);
    
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// =============================================================================
// XmpPacket tests
// =============================================================================

TEST_F(ImageTest_1074, XmpPacket_InitiallyEmpty_1074) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1074, SetXmpPacket_SetsPacketCorrectly_1074) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    image_->setXmpPacket(packet);
    
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1074, ClearXmpPacket_ClearsPacket_1074) {
    image_->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
    image_->clearXmpPacket();
    
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// =============================================================================
// Comment tests
// =============================================================================

TEST_F(ImageTest_1074, Comment_InitiallyEmpty_1074) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1074, SetComment_SetsCommentCorrectly_1074) {
    std::string comment = "Test comment";
    image_->setComment(comment);
    
    EXPECT_EQ(image_->comment(), comment);
}

TEST_F(ImageTest_1074, ClearComment_ClearsComment_1074) {
    image_->setComment("Test comment");
    image_->clearComment();
    
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1074, SetComment_EmptyString_1074) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1074, SetComment_LongString_1074) {
    std::string longComment(10000, 'A');
    image_->setComment(longComment);
    EXPECT_EQ(image_->comment(), longComment);
}

// =============================================================================
// ClearMetadata tests
// =============================================================================

TEST_F(ImageTest_1074, ClearMetadata_ClearsAll_1074) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    image_->setExifData(exifData);
    
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    image_->setIptcData(iptcData);
    
    image_->setComment("Test comment");
    
    image_->clearMetadata();
    
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->comment().empty());
}

// =============================================================================
// SetMetadata tests
// =============================================================================

TEST_F(ImageTest_1074, SetMetadata_CopiesFromAnotherImage_1074) {
    auto sourceImage = createTestImage();
    
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "SourceCamera";
    sourceImage->setExifData(exifData);
    sourceImage->setComment("Source comment");
    
    image_->setMetadata(*sourceImage);
    
    EXPECT_FALSE(image_->exifData().empty());
    EXPECT_EQ(image_->comment(), "Source comment");
}

// =============================================================================
// ByteOrder tests
// =============================================================================

TEST_F(ImageTest_1074, ByteOrder_DefaultIsInvalid_1074) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1074, SetByteOrder_BigEndian_1074) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1074, SetByteOrder_LittleEndian_1074) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// =============================================================================
// WriteXmpFromPacket tests
// =============================================================================

TEST_F(ImageTest_1074, WriteXmpFromPacket_DefaultIsFalse_1074) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1074, WriteXmpFromPacket_SetTrue_1074) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1074, WriteXmpFromPacket_SetFalse_1074) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// =============================================================================
// PixelWidth/Height tests
// =============================================================================

TEST_F(ImageTest_1074, PixelWidth_DefaultIsZero_1074) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1074, PixelHeight_DefaultIsZero_1074) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// =============================================================================
// Good tests
// =============================================================================

TEST_F(ImageTest_1074, Good_ReturnsTrueForValidIo_1074) {
    // MemIo with no data should still be considered "good" in terms of IO state
    // The actual value depends on the implementation, but we test it doesn't crash
    bool result = image_->good();
    // Just ensure it returns a boolean without crashing
    (void)result;
}

// =============================================================================
// IO tests
// =============================================================================

TEST_F(ImageTest_1074, Io_ReturnsBasicIoReference_1074) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify we can access the IO reference
    (void)io;
}

// =============================================================================
// NativePreviews tests
// =============================================================================

TEST_F(ImageTest_1074, NativePreviews_InitiallyEmpty_1074) {
    const Exiv2::NativePreviewList& previews = image_->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

// =============================================================================
// ICC Profile tests
// =============================================================================

TEST_F(ImageTest_1074, IccProfileDefined_InitiallyFalse_1074) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1074, ClearIccProfile_WhenNoneExists_1074) {
    // Should not crash
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// =============================================================================
// Static method tests: type checking
// =============================================================================

TEST_F(ImageTest_1074, IsStringType_CheckKnownStringTypes_1074) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    // Type 1 (BYTE) should not be string
    EXPECT_FALSE(Exiv2::Image::isStringType(1));
}

TEST_F(ImageTest_1074, IsShortType_CheckKnownShortTypes_1074) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    // Type 8 is SSHORT
    EXPECT_TRUE(Exiv2::Image::isShortType(8));
    EXPECT_FALSE(Exiv2::Image::isShortType(1));
}

TEST_F(ImageTest_1074, IsLongType_CheckKnownLongTypes_1074) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    // Type 9 is SLONG
    EXPECT_TRUE(Exiv2::Image::isLongType(9));
    EXPECT_FALSE(Exiv2::Image::isLongType(1));
}

TEST_F(ImageTest_1074, IsRationalType_CheckKnownRationalTypes_1074) {
    // Type 5 is RATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    // Type 10 is SRATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(10));
    EXPECT_FALSE(Exiv2::Image::isRationalType(1));
}

TEST_F(ImageTest_1074, Is2ByteType_CheckTypes_1074) {
    // SHORT (3) and SSHORT (8) are 2-byte types
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
    EXPECT_TRUE(Exiv2::Image::is2ByteType(8));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

TEST_F(ImageTest_1074, Is4ByteType_CheckTypes_1074) {
    // LONG (4) and SLONG (9) are 4-byte types
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

TEST_F(ImageTest_1074, Is8ByteType_CheckTypes_1074) {
    // RATIONAL (5) and SRATIONAL (10) are 8-byte types
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// =============================================================================
// Static method tests: endianness
// =============================================================================

TEST_F(ImageTest_1074, EndiannessPlatform_MutuallyExclusive_1074) {
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    
    // Exactly one should be true
    EXPECT_NE(isBig, isLittle);
}

// =============================================================================
// Static method tests: byte swap
// =============================================================================

TEST_F(ImageTest_1074, ByteSwap16_NoSwap_1074) {
    uint16_t value = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0x1234u);
}

TEST_F(ImageTest_1074, ByteSwap16_WithSwap_1074) {
    uint16_t value = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0x3412u);
}

TEST_F(ImageTest_1074, ByteSwap32_NoSwap_1074) {
    uint32_t value = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0x12345678u);
}

TEST_F(ImageTest_1074, ByteSwap32_WithSwap_1074) {
    uint32_t value = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0x78563412u);
}

TEST_F(ImageTest_1074, ByteSwap64_NoSwap_1074) {
    uint64_t value = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_1074, ByteSwap64_WithSwap_1074) {
    uint64_t value = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0x0807060504030201ULL);
}

TEST_F(ImageTest_1074, ByteSwap16_Zero_1074) {
    uint16_t value = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0u);
}

TEST_F(ImageTest_1074, ByteSwap32_Zero_1074) {
    uint32_t value = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0u);
}

TEST_F(ImageTest_1074, ByteSwap64_Zero_1074) {
    uint64_t value = 0;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0ULL);
}

TEST_F(ImageTest_1074, ByteSwap16_MaxValue_1074) {
    uint16_t value = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0xFFFFu);
}

TEST_F(ImageTest_1074, ByteSwap32_MaxValue_1074) {
    uint32_t value = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(value, true), 0xFFFFFFFFu);
}

// =============================================================================
// ImageType tests
// =============================================================================

TEST_F(ImageTest_1074, ImageType_ReturnsCorrectType_1074) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// =============================================================================
// ExifData reference access tests
// =============================================================================

TEST_F(ImageTest_1074, ExifData_ReturnsMutableReference_1074) {
    Exiv2::ExifData& data = image_->exifData();
    data["Exif.Image.Make"] = "DirectAccess";
    
    EXPECT_FALSE(image_->exifData().empty());
    EXPECT_EQ(image_->exifData().count(), 1u);
}

TEST_F(ImageTest_1074, IptcData_ReturnsMutableReference_1074) {
    Exiv2::IptcData& data = image_->iptcData();
    data["Iptc.Application2.Caption"] = "DirectAccess";
    
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1074, XmpData_ReturnsMutableReference_1074) {
    Exiv2::XmpData& data = image_->xmpData();
    data["Xmp.dc.title"] = "DirectAccess";
    
    EXPECT_FALSE(image_->xmpData().empty());
}

// =============================================================================
// IsLongLongType tests
// =============================================================================

TEST_F(ImageTest_1074, IsLongLongType_CheckTypes_1074) {
    // Type 16 is LONG8, Type 17 is SLONG8 (BigTIFF)
    // Standard types should not match
    EXPECT_FALSE(Exiv2::Image::isLongLongType(1));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4));
}

// =============================================================================
// Multiple set/clear cycles
// =============================================================================

TEST_F(ImageTest_1074, MultipleClearSetCycles_ExifData_1074) {
    for (int i = 0; i < 5; ++i) {
        Exiv2::ExifData exifData;
        exifData["Exif.Image.Make"] = "Camera" + std::to_string(i);
        image_->setExifData(exifData);
        EXPECT_EQ(image_->exifData().count(), 1u);
        
        image_->clearExifData();
        EXPECT_TRUE(image_->exifData().empty());
    }
}

TEST_F(ImageTest_1074, MultipleClearSetCycles_Comment_1074) {
    for (int i = 0; i < 5; ++i) {
        std::string comment = "Comment " + std::to_string(i);
        image_->setComment(comment);
        EXPECT_EQ(image_->comment(), comment);
        
        image_->clearComment();
        EXPECT_TRUE(image_->comment().empty());
    }
}

// =============================================================================
// ByteSwap with DataBuf
// =============================================================================

TEST_F(ImageTest_1074, ByteSwap2_FromDataBuf_NoSwap_1074) {
    Exiv2::DataBuf buf(4);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Without swap, it reads bytes as-is in native order
    // The exact expected value depends on implementation, but we test no crash
    (void)result;
}

TEST_F(ImageTest_1074, ByteSwap4_FromDataBuf_NoSwap_1074) {
    Exiv2::DataBuf buf(8);
    buf.write_uint8(0, 0x12);
    buf.write_uint8(1, 0x34);
    buf.write_uint8(2, 0x56);
    buf.write_uint8(3, 0x78);
    
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    (void)result;
}

TEST_F(ImageTest_1074, ByteSwap8_FromDataBuf_NoSwap_1074) {
    Exiv2::DataBuf buf(16);
    for (size_t i = 0; i < 8; ++i) {
        buf.write_uint8(i, static_cast<uint8_t>(i + 1));
    }
    
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    (void)result;
}

// =============================================================================
// SetIccProfile tests
// =============================================================================

TEST_F(ImageTest_1074, SetIccProfile_ValidProfile_1074) {
    // A minimal ICC profile header is 128 bytes + tag table
    // We'll just test that setting an empty or minimal profile works or throws as expected
    // ICC profile starts with size (4 bytes), then "acsp" at offset 36
    Exiv2::DataBuf profile(128);
    std::memset(profile.data(), 0, 128);
    // Set the profile size at bytes 0-3 (big-endian)
    profile.write_uint8(0, 0);
    profile.write_uint8(1, 0);
    profile.write_uint8(2, 0);
    profile.write_uint8(3, 128);
    // Set "acsp" signature at offset 36
    profile.write_uint8(36, 'a');
    profile.write_uint8(37, 'c');
    profile.write_uint8(38, 's');
    profile.write_uint8(39, 'p');
    
    // bTestValid=false to skip validation
    image_->setIccProfile(std::move(profile), false);
    EXPECT_TRUE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1074, ClearIccProfile_AfterSetting_1074) {
    Exiv2::DataBuf profile(128);
    std::memset(profile.data(), 0, 128);
    profile.write_uint8(3, 128);
    profile.write_uint8(36, 'a');
    profile.write_uint8(37, 'c');
    profile.write_uint8(38, 's');
    profile.write_uint8(39, 'p');
    
    image_->setIccProfile(std::move(profile), false);
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}
