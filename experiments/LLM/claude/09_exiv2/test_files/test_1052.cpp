#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <sstream>
#include <memory>

// We need a concrete Image subclass since Image has pure virtual methods (readMetadata, writeMetadata)
// We'll use a minimal concrete subclass for testing purposes.
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

    void readMetadata() override {}
    void writeMetadata() override {}
};

std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
}

} // anonymous namespace

// ==================== Type checking static methods ====================

class ImageStaticMethodsTest_1052 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }
    std::unique_ptr<TestImage> image_;
};

// TIFF type constants (from Exiv2 internal definitions)
// 1=BYTE, 2=ASCII, 3=SHORT, 4=LONG, 5=RATIONAL, 6=SBYTE, 7=UNDEFINED,
// 8=SSHORT, 9=SLONG, 10=SRATIONAL, 11=FLOAT, 12=DOUBLE,
// 13=IFD, 16=LONG8, 17=SLONG8, 18=IFD8

TEST_F(ImageStaticMethodsTest_1052, IsShortType_Short_1052) {
    // type 3 = SHORT
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageStaticMethodsTest_1052, IsShortType_SShort_1052) {
    // type 8 = SSHORT
    EXPECT_TRUE(Exiv2::Image::isShortType(8));
}

TEST_F(ImageStaticMethodsTest_1052, IsShortType_NotShort_1052) {
    EXPECT_FALSE(Exiv2::Image::isShortType(1));
    EXPECT_FALSE(Exiv2::Image::isShortType(4));
    EXPECT_FALSE(Exiv2::Image::isShortType(0));
}

TEST_F(ImageStaticMethodsTest_1052, Is2ByteType_EqualsIsShortType_1052) {
    // is2ByteType should return the same as isShortType
    for (uint16_t t = 0; t < 20; ++t) {
        EXPECT_EQ(Exiv2::Image::is2ByteType(t), Exiv2::Image::isShortType(t))
            << "Mismatch for type " << t;
    }
}

TEST_F(ImageStaticMethodsTest_1052, IsLongType_Long_1052) {
    // type 4 = LONG
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageStaticMethodsTest_1052, IsLongType_SLong_1052) {
    // type 9 = SLONG
    EXPECT_TRUE(Exiv2::Image::isLongType(9));
}

TEST_F(ImageStaticMethodsTest_1052, IsLongType_NotLong_1052) {
    EXPECT_FALSE(Exiv2::Image::isLongType(1));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
    EXPECT_FALSE(Exiv2::Image::isLongType(5));
}

TEST_F(ImageStaticMethodsTest_1052, IsLongLongType_1052) {
    // type 16 = LONG8, 17 = SLONG8
    EXPECT_TRUE(Exiv2::Image::isLongLongType(16));
    EXPECT_TRUE(Exiv2::Image::isLongLongType(17));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(0));
}

TEST_F(ImageStaticMethodsTest_1052, IsRationalType_Rational_1052) {
    // type 5 = RATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageStaticMethodsTest_1052, IsRationalType_SRational_1052) {
    // type 10 = SRATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(10));
}

TEST_F(ImageStaticMethodsTest_1052, IsRationalType_NotRational_1052) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(1));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

TEST_F(ImageStaticMethodsTest_1052, IsStringType_ASCII_1052) {
    // type 2 = ASCII
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageStaticMethodsTest_1052, IsStringType_NotString_1052) {
    EXPECT_FALSE(Exiv2::Image::isStringType(1));
    EXPECT_FALSE(Exiv2::Image::isStringType(3));
    EXPECT_FALSE(Exiv2::Image::isStringType(4));
}

TEST_F(ImageStaticMethodsTest_1052, Is4ByteType_1052) {
    // 4-byte types: LONG(4), SLONG(9), FLOAT(11), IFD(13)
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(5));
}

TEST_F(ImageStaticMethodsTest_1052, Is8ByteType_1052) {
    // 8-byte types: RATIONAL(5), SRATIONAL(10), DOUBLE(12), LONG8(16), SLONG8(17), IFD8(18)
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(3));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

// ==================== Endian platform checks ====================

TEST_F(ImageStaticMethodsTest_1052, EndianPlatformMutuallyExclusive_1052) {
    bool isBig = Exiv2::Image::isBigEndianPlatform();
    bool isLittle = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(isBig, isLittle);
}

// ==================== ByteSwap tests ====================

TEST_F(ImageStaticMethodsTest_1052, ByteSwap16_NoSwap_1052) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap16_Swap_1052) {
    uint16_t val = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint16_t>(0x3412));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap32_NoSwap_1052) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap32_Swap_1052) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint32_t>(0x78563412));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap64_NoSwap_1052) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap64_Swap_1052) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint64_t>(0x0807060504030201ULL));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap16_Zero_1052) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), static_cast<uint16_t>(0));
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false), static_cast<uint16_t>(0));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap32_Zero_1052) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), static_cast<uint32_t>(0));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap64_Zero_1052) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), static_cast<uint64_t>(0));
}

// ==================== ByteSwap from DataBuf ====================

TEST_F(ImageStaticMethodsTest_1052, ByteSwap2_FromBuf_NoSwap_1052) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Without swap, should read as-is (little endian interpretation or big endian depending on platform)
    // The value should be consistent with reading 2 bytes from offset 0
    uint16_t expected;
    std::memcpy(&expected, buf.data(), 2);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap2_FromBuf_Swap_1052) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    // Swapped should be the byte-swapped version of noSwap
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noSwap, true));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap4_FromBuf_NoSwap_1052) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.data(), 4);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap4_FromBuf_Swap_1052) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noSwap, true));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap8_FromBuf_NoSwap_1052) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; ++i) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.data(), 8);
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap8_FromBuf_Swap_1052) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; ++i) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noSwap, true));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap2_WithOffset_1052) {
    Exiv2::DataBuf buf(8);
    buf.data()[2] = 0xAB;
    buf.data()[3] = 0xCD;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 2, false);
    uint16_t expected;
    std::memcpy(&expected, buf.data() + 2, 2);
    EXPECT_EQ(result, expected);
}

// ==================== Instance method tests ====================

class ImageInstanceTest_1052 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }
    std::unique_ptr<TestImage> image_;
};

TEST_F(ImageInstanceTest_1052, DefaultByteOrder_1052) {
    // Default byte order should be invalidByteOrder
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageInstanceTest_1052, SetByteOrder_1052) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);

    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageInstanceTest_1052, DefaultPixelWidthAndHeight_1052) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

TEST_F(ImageInstanceTest_1052, DefaultComment_1052) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageInstanceTest_1052, SetAndGetComment_1052) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageInstanceTest_1052, ClearComment_1052) {
    image_->setComment("Test comment");
    EXPECT_EQ(image_->comment(), "Test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageInstanceTest_1052, DefaultWriteXmpFromPacket_1052) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageInstanceTest_1052, SetWriteXmpFromPacket_1052) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageInstanceTest_1052, ExifDataAccess_1052) {
    Exiv2::ExifData& exif = image_->exifData();
    EXPECT_TRUE(exif.empty());
}

TEST_F(ImageInstanceTest_1052, IptcDataAccess_1052) {
    Exiv2::IptcData& iptc = image_->iptcData();
    EXPECT_TRUE(iptc.empty());
}

TEST_F(ImageInstanceTest_1052, XmpDataAccess_1052) {
    Exiv2::XmpData& xmp = image_->xmpData();
    EXPECT_TRUE(xmp.empty());
}

TEST_F(ImageInstanceTest_1052, XmpPacketAccess_1052) {
    std::string& xmpPacket = image_->xmpPacket();
    EXPECT_TRUE(xmpPacket.empty());
}

TEST_F(ImageInstanceTest_1052, SetAndClearExifData_1052) {
    Exiv2::ExifData exif;
    image_->setExifData(exif);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageInstanceTest_1052, SetAndClearIptcData_1052) {
    Exiv2::IptcData iptc;
    image_->setIptcData(iptc);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageInstanceTest_1052, SetXmpPacket_1052) {
    std::string packet = "<xmp>test</xmp>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageInstanceTest_1052, ClearXmpPacket_1052) {
    image_->setXmpPacket("<xmp>test</xmp>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageInstanceTest_1052, SetAndClearXmpData_1052) {
    Exiv2::XmpData xmp;
    image_->setXmpData(xmp);
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageInstanceTest_1052, ClearMetadata_1052) {
    image_->setComment("test");
    image_->clearMetadata();
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageInstanceTest_1052, IoAccess_1052) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify it's accessible
    SUCCEED();
}

TEST_F(ImageInstanceTest_1052, Good_1052) {
    // MemIo with no data should still be "good" in some sense
    // This depends on implementation but we test the call doesn't crash
    image_->good();
}

TEST_F(ImageInstanceTest_1052, NativePreviews_1052) {
    const Exiv2::NativePreviewList& previews = image_->nativePreviews();
    EXPECT_TRUE(previews.empty());
}

TEST_F(ImageInstanceTest_1052, IccProfileNotDefined_1052) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1052, ClearIccProfile_1052) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1052, SetIccProfile_1052) {
    // Create a minimal ICC profile buffer (at least needs to look valid or bTestValid=false)
    Exiv2::DataBuf iccBuf(128);
    std::memset(iccBuf.data(), 0, 128);
    image_->setIccProfile(std::move(iccBuf), false);
    EXPECT_TRUE(image_->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1052, SetAndClearIccProfile_1052) {
    Exiv2::DataBuf iccBuf(128);
    std::memset(iccBuf.data(), 0, 128);
    image_->setIccProfile(std::move(iccBuf), false);
    EXPECT_TRUE(image_->iccProfileDefined());
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1052, ImageType_1052) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

TEST_F(ImageInstanceTest_1052, SetMetadataFromAnotherImage_1052) {
    auto other = createTestImage();
    other->setComment("from other");
    image_->setMetadata(*other);
    EXPECT_EQ(image_->comment(), "from other");
}

// ==================== isPrintXMP / isPrintICC ====================

TEST_F(ImageStaticMethodsTest_1052, IsPrintXMP_1052) {
    // We can test with XMP type (700 decimal = 0x02BC) and kpsXMP option
    // Without knowing exact types, we test boundary: type 0 should return false
    EXPECT_FALSE(Exiv2::Image::isPrintXMP(0, Exiv2::kpsNone));
}

TEST_F(ImageStaticMethodsTest_1052, IsPrintICC_1052) {
    EXPECT_FALSE(Exiv2::Image::isPrintICC(0, Exiv2::kpsNone));
}

// ==================== Double swap invariant ====================

TEST_F(ImageStaticMethodsTest_1052, ByteSwap16_DoubleSwapIdentity_1052) {
    uint16_t val = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap32_DoubleSwapIdentity_1052) {
    uint32_t val = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap64_DoubleSwapIdentity_1052) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

// ==================== Boundary: type 0 and max uint16 ====================

TEST_F(ImageStaticMethodsTest_1052, TypeZero_AllFalse_1052) {
    EXPECT_FALSE(Exiv2::Image::isShortType(0));
    EXPECT_FALSE(Exiv2::Image::isLongType(0));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(0));
    EXPECT_FALSE(Exiv2::Image::isRationalType(0));
    EXPECT_FALSE(Exiv2::Image::isStringType(0));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(0));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(0));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(0));
}

TEST_F(ImageStaticMethodsTest_1052, TypeMaxUint16_AllFalse_1052) {
    uint16_t maxVal = 0xFFFF;
    EXPECT_FALSE(Exiv2::Image::isShortType(maxVal));
    EXPECT_FALSE(Exiv2::Image::isLongType(maxVal));
    EXPECT_FALSE(Exiv2::Image::isLongLongType(maxVal));
    EXPECT_FALSE(Exiv2::Image::isRationalType(maxVal));
    EXPECT_FALSE(Exiv2::Image::isStringType(maxVal));
    EXPECT_FALSE(Exiv2::Image::is2ByteType(maxVal));
    EXPECT_FALSE(Exiv2::Image::is4ByteType(maxVal));
    EXPECT_FALSE(Exiv2::Image::is8ByteType(maxVal));
}

// ==================== ByteSwap edge cases ====================

TEST_F(ImageStaticMethodsTest_1052, ByteSwap16_MaxValue_1052) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint16_t>(0xFFFF));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap32_MaxValue_1052) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint32_t>(0xFFFFFFFF));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap64_MaxValue_1052) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint64_t>(0xFFFFFFFFFFFFFFFFULL));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap16_One_1052) {
    uint16_t val = 1;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint16_t>(0x0100));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap32_One_1052) {
    uint32_t val = 1;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint32_t>(0x01000000));
}

TEST_F(ImageStaticMethodsTest_1052, ByteSwap64_One_1052) {
    uint64_t val = 1;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, static_cast<uint64_t>(0x0100000000000000ULL));
}

// ==================== Comment edge cases ====================

TEST_F(ImageInstanceTest_1052, SetEmptyComment_1052) {
    image_->setComment("");
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageInstanceTest_1052, SetLongComment_1052) {
    std::string longComment(10000, 'x');
    image_->setComment(longComment);
    EXPECT_EQ(image_->comment(), longComment);
}

TEST_F(ImageInstanceTest_1052, SetCommentOverwrite_1052) {
    image_->setComment("first");
    EXPECT_EQ(image_->comment(), "first");
    image_->setComment("second");
    EXPECT_EQ(image_->comment(), "second");
}

// ==================== printStructure doesn't crash ====================

TEST_F(ImageInstanceTest_1052, PrintStructureDoesNotCrash_1052) {
    std::ostringstream oss;
    EXPECT_NO_THROW(image_->printStructure(oss, Exiv2::kpsNone, 0));
}
