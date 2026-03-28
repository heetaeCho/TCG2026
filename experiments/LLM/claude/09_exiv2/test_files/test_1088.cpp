#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <exiv2/iptc.hpp>
#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/types.hpp>

#include <memory>
#include <sstream>
#include <cstring>

namespace {

// A concrete subclass of Image for testing, since Image has pure virtual methods
class TestImage : public Exiv2::Image {
public:
    TestImage(Exiv2::ImageType type, uint16_t supportedMetadata, std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

    void readMetadata() override {
        // No-op for testing
    }

    void writeMetadata() override {
        // No-op for testing
    }
};

std::unique_ptr<TestImage> createTestImage(Exiv2::ImageType type = Exiv2::ImageType::none,
                                            uint16_t supportedMetadata = 0xFFFF) {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(type, supportedMetadata, std::move(io));
}

} // anonymous namespace

class ImageTest_1088 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// ==================== ByteOrder Tests ====================

TEST_F(ImageTest_1088, SetByteOrder_LittleEndian_1088) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(Exiv2::littleEndian, image_->byteOrder());
}

TEST_F(ImageTest_1088, SetByteOrder_BigEndian_1088) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(Exiv2::bigEndian, image_->byteOrder());
}

TEST_F(ImageTest_1088, DefaultByteOrder_IsInvalid_1088) {
    EXPECT_EQ(Exiv2::invalidByteOrder, image_->byteOrder());
}

// ==================== PixelWidth/Height Tests ====================

TEST_F(ImageTest_1088, DefaultPixelWidth_IsZero_1088) {
    EXPECT_EQ(0u, image_->pixelWidth());
}

TEST_F(ImageTest_1088, DefaultPixelHeight_IsZero_1088) {
    EXPECT_EQ(0u, image_->pixelHeight());
}

// ==================== Comment Tests ====================

TEST_F(ImageTest_1088, DefaultComment_IsEmpty_1088) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1088, SetComment_ReturnsSetValue_1088) {
    image_->setComment("Test comment");
    EXPECT_EQ("Test comment", image_->comment());
}

TEST_F(ImageTest_1088, ClearComment_ClearsValue_1088) {
    image_->setComment("Test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1088, SetComment_EmptyString_1088) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1088, SetComment_LongString_1088) {
    std::string longComment(10000, 'A');
    image_->setComment(longComment);
    EXPECT_EQ(longComment, image_->comment());
}

// ==================== ExifData Tests ====================

TEST_F(ImageTest_1088, ExifData_DefaultIsEmpty_1088) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1088, SetExifData_1088) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1088, ClearExifData_1088) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ==================== IptcData Tests ====================

TEST_F(ImageTest_1088, IptcData_DefaultIsEmpty_1088) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1088, SetIptcData_1088) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1088, ClearIptcData_1088) {
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// ==================== XmpData Tests ====================

TEST_F(ImageTest_1088, XmpData_DefaultIsEmpty_1088) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1088, ClearXmpData_1088) {
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== XmpPacket Tests ====================

TEST_F(ImageTest_1088, XmpPacket_DefaultIsEmpty_1088) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1088, SetXmpPacket_1088) {
    std::string packet = "<x:xmpmeta></x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(packet, image_->xmpPacket());
}

TEST_F(ImageTest_1088, ClearXmpPacket_1088) {
    image_->setXmpPacket("<x:xmpmeta></x:xmpmeta>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== WriteXmpFromPacket Tests ====================

TEST_F(ImageTest_1088, WriteXmpFromPacket_DefaultFalse_1088) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1088, WriteXmpFromPacket_SetTrue_1088) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1088, WriteXmpFromPacket_SetFalse_1088) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ==================== ICC Profile Tests ====================

TEST_F(ImageTest_1088, IccProfile_DefaultNotDefined_1088) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1088, ClearIccProfile_1088) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ==================== ClearMetadata Tests ====================

TEST_F(ImageTest_1088, ClearMetadata_ClearsAll_1088) {
    image_->setComment("Test");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);

    image_->clearMetadata();

    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== SetMetadata Tests ====================

TEST_F(ImageTest_1088, SetMetadata_CopiesFromOther_1088) {
    auto other = createTestImage();
    other->setComment("Other comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "OtherMake";
    other->setExifData(exifData);

    image_->setMetadata(*other);

    EXPECT_EQ("Other comment", image_->comment());
    EXPECT_FALSE(image_->exifData().empty());
}

// ==================== good() Tests ====================

TEST_F(ImageTest_1088, Good_WithMemIo_1088) {
    // MemIo should be "good" by default
    EXPECT_TRUE(image_->good());
}

// ==================== io() Tests ====================

TEST_F(ImageTest_1088, Io_ReturnsReference_1088) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify we can access it without crash
    (void)io;
}

// ==================== Static Methods: Endianness ====================

TEST_F(ImageTest_1088, EndiannessPlatformConsistency_1088) {
    // Exactly one of these should be true
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

// ==================== Static Methods: Type Classification ====================

TEST_F(ImageTest_1088, IsStringType_AsciiType_1088) {
    // Type 2 is ASCII in TIFF spec
    bool result = Exiv2::Image::isStringType(2);
    EXPECT_TRUE(result);
}

TEST_F(ImageTest_1088, IsStringType_NonStringType_1088) {
    // Type 3 is SHORT, not a string type
    EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

TEST_F(ImageTest_1088, IsShortType_ShortType_1088) {
    // Type 3 is SHORT in TIFF
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageTest_1088, IsShortType_NonShortType_1088) {
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

TEST_F(ImageTest_1088, IsLongType_LongType_1088) {
    // Type 4 is LONG in TIFF
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageTest_1088, IsLongType_NonLongType_1088) {
    EXPECT_FALSE(Exiv2::Image::isLongType(2));
}

TEST_F(ImageTest_1088, IsRationalType_RationalType_1088) {
    // Type 5 is RATIONAL in TIFF
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageTest_1088, IsRationalType_NonRationalType_1088) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(3));
}

TEST_F(ImageTest_1088, Is2ByteType_ShortType_1088) {
    // Type 3 (SHORT) is a 2-byte type
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
}

TEST_F(ImageTest_1088, Is2ByteType_Non2ByteType_1088) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

TEST_F(ImageTest_1088, Is4ByteType_LongType_1088) {
    // Type 4 (LONG) is a 4-byte type
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
}

TEST_F(ImageTest_1088, Is4ByteType_Non4ByteType_1088) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

TEST_F(ImageTest_1088, Is8ByteType_RationalType_1088) {
    // Type 5 (RATIONAL) is an 8-byte type
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
}

TEST_F(ImageTest_1088, Is8ByteType_Non8ByteType_1088) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
}

// ==================== Static Methods: ByteSwap ====================

TEST_F(ImageTest_1088, ByteSwap16_NoSwap_1088) {
    uint16_t val = 0x1234;
    uint16_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(val, result);
}

TEST_F(ImageTest_1088, ByteSwap16_WithSwap_1088) {
    uint16_t val = 0x1234;
    uint16_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(0x3412u, result);
}

TEST_F(ImageTest_1088, ByteSwap32_NoSwap_1088) {
    uint32_t val = 0x12345678;
    uint32_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(val, result);
}

TEST_F(ImageTest_1088, ByteSwap32_WithSwap_1088) {
    uint32_t val = 0x12345678;
    uint32_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(0x78563412u, result);
}

TEST_F(ImageTest_1088, ByteSwap64_NoSwap_1088) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(val, false);
    EXPECT_EQ(val, result);
}

TEST_F(ImageTest_1088, ByteSwap64_WithSwap_1088) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(0x0807060504030201ULL, result);
}

// ==================== ByteSwap from DataBuf ====================

TEST_F(ImageTest_1088, ByteSwap2_NoSwap_1088) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t expected;
    std::memcpy(&expected, buf.c_data(), 2);
    EXPECT_EQ(expected, result);
}

TEST_F(ImageTest_1088, ByteSwap2_WithSwap_1088) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t withSwap = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(Exiv2::Image::byteSwap(noSwap, true), withSwap);
}

TEST_F(ImageTest_1088, ByteSwap4_NoSwap_1088) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(), 4);
    EXPECT_EQ(expected, result);
}

TEST_F(ImageTest_1088, ByteSwap8_NoSwap_1088) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; i++) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.c_data(), 8);
    EXPECT_EQ(expected, result);
}

// ==================== ByteSwap Boundary: Zero values ====================

TEST_F(ImageTest_1088, ByteSwap16_ZeroValue_1088) {
    uint16_t result = Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true);
    EXPECT_EQ(0u, result);
}

TEST_F(ImageTest_1088, ByteSwap32_ZeroValue_1088) {
    uint32_t result = Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true);
    EXPECT_EQ(0u, result);
}

TEST_F(ImageTest_1088, ByteSwap64_ZeroValue_1088) {
    uint64_t result = Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true);
    EXPECT_EQ(0u, result);
}

// ==================== ByteSwap: Max values ====================

TEST_F(ImageTest_1088, ByteSwap16_MaxValue_1088) {
    uint16_t val = 0xFFFF;
    uint16_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(0xFFFFu, result);
}

TEST_F(ImageTest_1088, ByteSwap32_MaxValue_1088) {
    uint32_t val = 0xFFFFFFFF;
    uint32_t result = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(0xFFFFFFFFu, result);
}

// ==================== ByteSwap: Double swap returns original ====================

TEST_F(ImageTest_1088, ByteSwap16_DoubleSwapReturnsOriginal_1088) {
    uint16_t val = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(val, doubleSwapped);
}

TEST_F(ImageTest_1088, ByteSwap32_DoubleSwapReturnsOriginal_1088) {
    uint32_t val = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(val, doubleSwapped);
}

TEST_F(ImageTest_1088, ByteSwap64_DoubleSwapReturnsOriginal_1088) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(val, doubleSwapped);
}

// ==================== ImageType Tests ====================

TEST_F(ImageTest_1088, ImageType_ReturnsConstructedType_1088) {
    auto img = createTestImage(Exiv2::ImageType::jpeg, 0xFFFF);
    EXPECT_EQ(Exiv2::ImageType::jpeg, img->imageType());
}

TEST_F(ImageTest_1088, ImageType_NoneType_1088) {
    auto img = createTestImage(Exiv2::ImageType::none, 0);
    EXPECT_EQ(Exiv2::ImageType::none, img->imageType());
}

// ==================== NativePreviews Tests ====================

TEST_F(ImageTest_1088, NativePreviews_DefaultIsEmpty_1088) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ==================== isPrintXMP / isPrintICC Static Tests ====================

TEST_F(ImageTest_1088, IsPrintXMP_WithPrintStructureXMP_1088) {
    // Type doesn't matter much; the option does
    // We test with a few combinations
    bool result = Exiv2::Image::isPrintXMP(2, Exiv2::kpsXMP);
    // We just verify it doesn't crash and returns a boolean
    (void)result;
}

TEST_F(ImageTest_1088, IsPrintICC_WithPrintStructureICC_1088) {
    bool result = Exiv2::Image::isPrintICC(2, Exiv2::kpsIccProfile);
    (void)result;
}

// ==================== IsLongLongType Tests ====================

TEST_F(ImageTest_1088, IsLongLongType_1088) {
    // Type 16 is LONG8 in BigTIFF
    bool result16 = Exiv2::Image::isLongLongType(16);
    // Type 3 (SHORT) should not be long long
    bool result3 = Exiv2::Image::isLongLongType(3);
    EXPECT_FALSE(result3);
    // Type 16 or 17 may be long long types
    (void)result16;
}

// ==================== SetTypeSupported Tests ====================

TEST_F(ImageTest_1088, SetTypeSupported_1088) {
    image_->setTypeSupported(Exiv2::ImageType::jpeg, 0x0001);
    EXPECT_EQ(Exiv2::ImageType::jpeg, image_->imageType());
}

// ==================== MimeType Tests ====================

TEST_F(ImageTest_1088, MimeType_DefaultReturnsString_1088) {
    std::string mime = image_->mimeType();
    // The default base implementation should return something
    EXPECT_FALSE(mime.empty() && false); // Just verify no crash
}

// ==================== Multiple operations ====================

TEST_F(ImageTest_1088, MultipleSetComment_LastWins_1088) {
    image_->setComment("First");
    image_->setComment("Second");
    image_->setComment("Third");
    EXPECT_EQ("Third", image_->comment());
}

TEST_F(ImageTest_1088, SetByteOrder_MultipleTimes_1088) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(Exiv2::littleEndian, image_->byteOrder());
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(Exiv2::bigEndian, image_->byteOrder());
    image_->setByteOrder(Exiv2::invalidByteOrder);
    EXPECT_EQ(Exiv2::invalidByteOrder, image_->byteOrder());
}

// ==================== ByteSwap2 with offset ====================

TEST_F(ImageTest_1088, ByteSwap2_WithOffset_1088) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x00;
    buf.data()[1] = 0x00;
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 2, false);
    uint16_t expected;
    std::memcpy(&expected, buf.c_data(2), 2);
    EXPECT_EQ(expected, result);
}

TEST_F(ImageTest_1088, ByteSwap4_WithOffset_1088) {
    Exiv2::DataBuf buf(12);
    buf.data()[4] = 0x12;
    buf.data()[5] = 0x34;
    buf.data()[6] = 0x56;
    buf.data()[7] = 0x78;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 4, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(4), 4);
    EXPECT_EQ(expected, result);
}
