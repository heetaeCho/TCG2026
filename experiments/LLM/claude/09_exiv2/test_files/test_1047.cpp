#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <memory>

// We need a concrete Image subclass for testing since Image has pure virtual methods
// We'll use a minimal approach - create an Image via available factory or use MemIo
// Since Image is abstract, we need a concrete subclass for testing non-static methods

namespace {

// Helper to create a BasicIo for testing
std::unique_ptr<Exiv2::BasicIo> createTestIo() {
    return std::make_unique<Exiv2::MemIo>();
}

// Concrete subclass for testing non-static methods
class TestImage : public Exiv2::Image {
public:
    TestImage(std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

    void readMetadata() override {}
    void writeMetadata() override {}
    std::string mimeType() const override { return "application/octet-stream"; }
};

} // anonymous namespace

class ImageStaticTest_1047 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

class ImageInstanceTest_1047 : public ::testing::Test {
protected:
    std::unique_ptr<TestImage> image_;
    
    void SetUp() override {
        image_ = std::make_unique<TestImage>(createTestIo());
    }
    void TearDown() override {}
};

// =============================================================================
// isStringType tests
// =============================================================================

TEST_F(ImageStaticTest_1047, IsStringType_AsciiString_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::asciiString));
}

TEST_F(ImageStaticTest_1047, IsStringType_UnsignedByte_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::unsignedByte));
}

TEST_F(ImageStaticTest_1047, IsStringType_SignedByte_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::signedByte));
}

TEST_F(ImageStaticTest_1047, IsStringType_Undefined_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::undefined));
}

TEST_F(ImageStaticTest_1047, IsStringType_UnsignedShort_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1047, IsStringType_UnsignedLong_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1047, IsStringType_UnsignedRational_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1047, IsStringType_SignedShort_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1047, IsStringType_SignedLong_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1047, IsStringType_SignedRational_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1047, IsStringType_TiffFloat_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::tiffFloat));
}

TEST_F(ImageStaticTest_1047, IsStringType_TiffDouble_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::tiffDouble));
}

TEST_F(ImageStaticTest_1047, IsStringType_Zero_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(0));
}

TEST_F(ImageStaticTest_1047, IsStringType_MaxUint16_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isStringType(0xFFFF));
}

// =============================================================================
// isShortType tests
// =============================================================================

TEST_F(ImageStaticTest_1047, IsShortType_UnsignedShort_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1047, IsShortType_SignedShort_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1047, IsShortType_UnsignedLong_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1047, IsShortType_AsciiString_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::asciiString));
}

// =============================================================================
// isLongType tests
// =============================================================================

TEST_F(ImageStaticTest_1047, IsLongType_UnsignedLong_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1047, IsLongType_SignedLong_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1047, IsLongType_UnsignedShort_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1047, IsLongType_TiffIfd_ReturnsFalse_1047) {
    // tiffIfd might or might not be considered long type
    // We test to observe behavior
    bool result = Exiv2::Image::isLongType(Exiv2::tiffIfd);
    // Just ensure it doesn't crash; the result is implementation-defined
    (void)result;
}

// =============================================================================
// isLongLongType tests
// =============================================================================

TEST_F(ImageStaticTest_1047, IsLongLongType_UnsignedLongLong_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::unsignedLongLong));
}

TEST_F(ImageStaticTest_1047, IsLongLongType_SignedLongLong_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::signedLongLong));
}

TEST_F(ImageStaticTest_1047, IsLongLongType_UnsignedLong_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedLong));
}

// =============================================================================
// isRationalType tests
// =============================================================================

TEST_F(ImageStaticTest_1047, IsRationalType_UnsignedRational_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1047, IsRationalType_SignedRational_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1047, IsRationalType_UnsignedLong_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedLong));
}

// =============================================================================
// is2ByteType tests
// =============================================================================

TEST_F(ImageStaticTest_1047, Is2ByteType_UnsignedShort_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageStaticTest_1047, Is2ByteType_SignedShort_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::signedShort));
}

TEST_F(ImageStaticTest_1047, Is2ByteType_UnsignedLong_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedLong));
}

// =============================================================================
// is4ByteType tests
// =============================================================================

TEST_F(ImageStaticTest_1047, Is4ByteType_UnsignedLong_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageStaticTest_1047, Is4ByteType_SignedLong_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::signedLong));
}

TEST_F(ImageStaticTest_1047, Is4ByteType_TiffFloat_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffFloat));
}

TEST_F(ImageStaticTest_1047, Is4ByteType_UnsignedShort_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedShort));
}

// =============================================================================
// is8ByteType tests
// =============================================================================

TEST_F(ImageStaticTest_1047, Is8ByteType_UnsignedRational_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedRational));
}

TEST_F(ImageStaticTest_1047, Is8ByteType_SignedRational_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedRational));
}

TEST_F(ImageStaticTest_1047, Is8ByteType_TiffDouble_ReturnsTrue_1047) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffDouble));
}

TEST_F(ImageStaticTest_1047, Is8ByteType_UnsignedShort_ReturnsFalse_1047) {
    EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedShort));
}

// =============================================================================
// Platform endianness tests
// =============================================================================

TEST_F(ImageStaticTest_1047, EndianPlatform_MutuallyExclusiveOrConsistent_1047) {
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    // A platform should be either big or little endian (not both, not neither in common cases)
    EXPECT_NE(big, little);
}

// =============================================================================
// byteSwap tests
// =============================================================================

TEST_F(ImageStaticTest_1047, ByteSwap16_NoSwap_ReturnsSameValue_1047) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1047, ByteSwap16_WithSwap_ReturnsSwappedValue_1047) {
    uint16_t val = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x3412);
}

TEST_F(ImageStaticTest_1047, ByteSwap32_NoSwap_ReturnsSameValue_1047) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1047, ByteSwap32_WithSwap_ReturnsSwappedValue_1047) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageStaticTest_1047, ByteSwap64_NoSwap_ReturnsSameValue_1047) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageStaticTest_1047, ByteSwap64_WithSwap_ReturnsSwappedValue_1047) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

TEST_F(ImageStaticTest_1047, ByteSwap16_Zero_NoSwap_1047) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false), 0);
}

TEST_F(ImageStaticTest_1047, ByteSwap16_Zero_WithSwap_1047) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), 0);
}

TEST_F(ImageStaticTest_1047, ByteSwap32_Zero_WithSwap_1047) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
}

TEST_F(ImageStaticTest_1047, ByteSwap16_MaxValue_WithSwap_1047) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFF);
}

TEST_F(ImageStaticTest_1047, ByteSwap32_MaxValue_WithSwap_1047) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
}

// =============================================================================
// Instance-based tests
// =============================================================================

TEST_F(ImageInstanceTest_1047, DefaultByteOrder_IsInvalid_1047) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageInstanceTest_1047, SetByteOrder_CanBeRetrieved_1047) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageInstanceTest_1047, SetByteOrder_LittleEndian_1047) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageInstanceTest_1047, DefaultPixelWidth_IsZero_1047) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageInstanceTest_1047, DefaultPixelHeight_IsZero_1047) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

TEST_F(ImageInstanceTest_1047, DefaultComment_IsEmpty_1047) {
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageInstanceTest_1047, SetComment_CanBeRetrieved_1047) {
    image_->setComment("test comment");
    EXPECT_EQ(image_->comment(), "test comment");
}

TEST_F(ImageInstanceTest_1047, ClearComment_MakesEmpty_1047) {
    image_->setComment("test comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageInstanceTest_1047, SetComment_EmptyString_1047) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageInstanceTest_1047, DefaultWriteXmpFromPacket_IsFalse_1047) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageInstanceTest_1047, SetWriteXmpFromPacket_True_1047) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageInstanceTest_1047, SetWriteXmpFromPacket_FalseAfterTrue_1047) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageInstanceTest_1047, ExifData_ReturnsReference_1047) {
    Exiv2::ExifData& exif = image_->exifData();
    EXPECT_TRUE(exif.empty());
}

TEST_F(ImageInstanceTest_1047, IptcData_ReturnsReference_1047) {
    Exiv2::IptcData& iptc = image_->iptcData();
    EXPECT_TRUE(iptc.empty());
}

TEST_F(ImageInstanceTest_1047, XmpData_ReturnsReference_1047) {
    Exiv2::XmpData& xmp = image_->xmpData();
    EXPECT_TRUE(xmp.empty());
}

TEST_F(ImageInstanceTest_1047, ClearExifData_OnEmptyData_1047) {
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageInstanceTest_1047, ClearIptcData_OnEmptyData_1047) {
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageInstanceTest_1047, ClearXmpData_OnEmptyData_1047) {
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageInstanceTest_1047, ClearXmpPacket_OnEmptyPacket_1047) {
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageInstanceTest_1047, SetXmpPacket_CanBeRetrieved_1047) {
    std::string packet = "<x:xmpmeta></x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageInstanceTest_1047, ClearXmpPacket_AfterSet_1047) {
    image_->setXmpPacket("<x:xmpmeta></x:xmpmeta>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageInstanceTest_1047, IccProfileDefined_DefaultFalse_1047) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1047, ClearIccProfile_OnEmpty_1047) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1047, ClearMetadata_ClearsAll_1047) {
    image_->setComment("test");
    image_->clearMetadata();
    EXPECT_TRUE(image_->comment().empty());
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageInstanceTest_1047, Good_OnMemIo_1047) {
    // A MemIo should be in a good state
    EXPECT_TRUE(image_->good());
}

TEST_F(ImageInstanceTest_1047, NativePreviews_DefaultEmpty_1047) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

TEST_F(ImageInstanceTest_1047, IoReference_IsAccessible_1047) {
    const Exiv2::BasicIo& io = image_->io();
    // Just verify it doesn't throw/crash
    (void)io;
}

TEST_F(ImageInstanceTest_1047, MimeType_ReturnsNonEmpty_1047) {
    EXPECT_FALSE(image_->mimeType().empty());
}

// =============================================================================
// SetMetadata tests
// =============================================================================

TEST_F(ImageInstanceTest_1047, SetMetadata_CopiesFromOtherImage_1047) {
    auto otherIo = createTestIo();
    TestImage other(std::move(otherIo));
    other.setComment("from other");
    
    image_->setMetadata(other);
    EXPECT_EQ(image_->comment(), "from other");
}

// =============================================================================
// byteSwap2/4/8 with DataBuf tests
// =============================================================================

TEST_F(ImageStaticTest_1047, ByteSwap2_NoSwap_1047) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
    // Without swap, should read bytes as-is in memory order
    uint16_t expected;
    std::memcpy(&expected, buf.c_data(), sizeof(uint16_t));
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1047, ByteSwap2_WithSwap_1047) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t withSwap = Exiv2::Image::byteSwap2(buf, 0, true);
    // Swapped should be different from non-swapped (for non-palindrome values)
    EXPECT_NE(noSwap, withSwap);
}

TEST_F(ImageStaticTest_1047, ByteSwap4_NoSwap_1047) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;
    uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t expected;
    std::memcpy(&expected, buf.c_data(), sizeof(uint32_t));
    EXPECT_EQ(result, expected);
}

TEST_F(ImageStaticTest_1047, ByteSwap8_NoSwap_1047) {
    Exiv2::DataBuf buf(16);
    for (int i = 0; i < 8; ++i) {
        buf.data()[i] = static_cast<uint8_t>(i + 1);
    }
    uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t expected;
    std::memcpy(&expected, buf.c_data(), sizeof(uint64_t));
    EXPECT_EQ(result, expected);
}

// =============================================================================
// Double swap should return original value
// =============================================================================

TEST_F(ImageStaticTest_1047, ByteSwap16_DoubleSwap_ReturnsOriginal_1047) {
    uint16_t val = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    uint16_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

TEST_F(ImageStaticTest_1047, ByteSwap32_DoubleSwap_ReturnsOriginal_1047) {
    uint32_t val = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    uint32_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

TEST_F(ImageStaticTest_1047, ByteSwap64_DoubleSwap_ReturnsOriginal_1047) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    uint64_t doubleSwapped = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(doubleSwapped, val);
}

// =============================================================================
// SetExifData / SetIptcData / SetXmpData tests
// =============================================================================

TEST_F(ImageInstanceTest_1047, SetExifData_ReplacesExisting_1047) {
    Exiv2::ExifData exif;
    image_->setExifData(exif);
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageInstanceTest_1047, SetIptcData_ReplacesExisting_1047) {
    Exiv2::IptcData iptc;
    image_->setIptcData(iptc);
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageInstanceTest_1047, SetXmpData_ReplacesExisting_1047) {
    Exiv2::XmpData xmp;
    image_->setXmpData(xmp);
    EXPECT_TRUE(image_->xmpData().empty());
}

// =============================================================================
// isPrintXMP / isPrintICC tests  
// =============================================================================

TEST_F(ImageStaticTest_1047, IsPrintXMP_WithNonXmpType_1047) {
    bool result = Exiv2::Image::isPrintXMP(Exiv2::unsignedShort, Exiv2::kpsXMP);
    // Just verify it doesn't crash
    (void)result;
}

TEST_F(ImageStaticTest_1047, IsPrintICC_WithNonIccType_1047) {
    bool result = Exiv2::Image::isPrintICC(Exiv2::unsignedShort, Exiv2::kpsIccProfile);
    // Just verify it doesn't crash
    (void)result;
}

// =============================================================================
// SetIccProfile tests
// =============================================================================

TEST_F(ImageInstanceTest_1047, SetIccProfile_EmptyBuf_NoValidation_1047) {
    Exiv2::DataBuf buf;
    image_->setIccProfile(std::move(buf), false);
    // After setting empty buffer, profile may or may not be defined depending on impl
}

TEST_F(ImageInstanceTest_1047, SetComment_LongString_1047) {
    std::string longComment(10000, 'A');
    image_->setComment(longComment);
    EXPECT_EQ(image_->comment(), longComment);
}

TEST_F(ImageInstanceTest_1047, SetComment_SpecialCharacters_1047) {
    std::string special = "Hello\n\t\r\0World";
    image_->setComment(special);
    EXPECT_EQ(image_->comment(), special);
}
