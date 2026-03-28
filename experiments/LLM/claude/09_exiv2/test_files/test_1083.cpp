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

// A concrete subclass of Image for testing purposes, since Image has pure virtual methods
class TestImage : public Exiv2::Image {
public:
    TestImage(Exiv2::ImageType type, uint16_t supportedMetadata, std::unique_ptr<Exiv2::BasicIo> io)
        : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

    void readMetadata() override {
        // no-op for testing
    }

    void writeMetadata() override {
        // no-op for testing
    }

    std::string mimeType() const override {
        return "application/octet-stream";
    }
};

std::unique_ptr<TestImage> createTestImage(uint16_t supportedMetadata = 0xFFFF) {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(Exiv2::ImageType::none, supportedMetadata, std::move(io));
}

} // anonymous namespace

class ImageTest_1083 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// --- setComment / comment / clearComment ---

TEST_F(ImageTest_1083, SetCommentAndRetrieve_1083) {
    image_->setComment("Hello World");
    EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageTest_1083, SetCommentEmpty_1083) {
    image_->setComment("");
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageTest_1083, ClearComment_1083) {
    image_->setComment("Some comment");
    image_->clearComment();
    EXPECT_EQ(image_->comment(), "");
}

TEST_F(ImageTest_1083, SetCommentOverwrite_1083) {
    image_->setComment("First");
    image_->setComment("Second");
    EXPECT_EQ(image_->comment(), "Second");
}

TEST_F(ImageTest_1083, SetCommentLongString_1083) {
    std::string longComment(10000, 'x');
    image_->setComment(longComment);
    EXPECT_EQ(image_->comment(), longComment);
}

TEST_F(ImageTest_1083, SetCommentSpecialChars_1083) {
    std::string special = "こんにちは\n\t\"'\\";
    image_->setComment(special);
    EXPECT_EQ(image_->comment(), special);
}

// --- ExifData ---

TEST_F(ImageTest_1083, ExifDataInitiallyEmpty_1083) {
    EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_1083, SetExifData_1083) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    EXPECT_FALSE(image_->exifData().empty());
    EXPECT_EQ(image_->exifData()["Exif.Image.Make"].toString(), "TestMake");
}

TEST_F(ImageTest_1083, ClearExifData_1083) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// --- IptcData ---

TEST_F(ImageTest_1083, IptcDataInitiallyEmpty_1083) {
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1083, SetIptcData_1083) {
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test Caption");
    iptcData.add(key, value.get());
    image_->setIptcData(iptcData);
    EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_1083, ClearIptcData_1083) {
    Exiv2::IptcData iptcData;
    Exiv2::IptcKey key("Iptc.Application2.Caption");
    Exiv2::Value::UniquePtr value = Exiv2::Value::create(Exiv2::string);
    value->read("Test Caption");
    iptcData.add(key, value.get());
    image_->setIptcData(iptcData);
    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

// --- XmpData ---

TEST_F(ImageTest_1083, XmpDataInitiallyEmpty_1083) {
    EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_1083, SetXmpData_1083) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);
    EXPECT_FALSE(image_->xmpData().empty());
}

TEST_F(ImageTest_1083, ClearXmpData_1083) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);
    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// --- XmpPacket ---

TEST_F(ImageTest_1083, XmpPacketInitiallyEmpty_1083) {
    EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_1083, SetXmpPacket_1083) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    image_->setXmpPacket(packet);
    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1083, ClearXmpPacket_1083) {
    image_->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// --- writeXmpFromPacket ---

TEST_F(ImageTest_1083, WriteXmpFromPacketDefault_1083) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1083, WriteXmpFromPacketSetTrue_1083) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1083, WriteXmpFromPacketSetFalse_1083) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// --- byteOrder ---

TEST_F(ImageTest_1083, ByteOrderDefaultInvalid_1083) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1083, SetByteOrderLittleEndian_1083) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageTest_1083, SetByteOrderBigEndian_1083) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

// --- pixelWidth / pixelHeight ---

TEST_F(ImageTest_1083, PixelWidthDefaultZero_1083) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1083, PixelHeightDefaultZero_1083) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// --- good ---

TEST_F(ImageTest_1083, GoodOnFreshMemIo_1083) {
    // MemIo should be good initially
    EXPECT_TRUE(image_->good());
}

// --- io ---

TEST_F(ImageTest_1083, IoReturnsValidReference_1083) {
    const Exiv2::BasicIo& io = image_->io();
    // Should not throw, just verify we can access it
    (void)io;
}

// --- clearMetadata ---

TEST_F(ImageTest_1083, ClearMetadataClearsAll_1083) {
    image_->setComment("A comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);
    image_->setXmpPacket("<test/>");

    image_->clearMetadata();

    EXPECT_EQ(image_->comment(), "");
    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// --- setMetadata ---

TEST_F(ImageTest_1083, SetMetadataFromAnotherImage_1083) {
    auto other = createTestImage();
    other->setComment("Other comment");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Model"] = "TestModel";
    other->setExifData(exifData);

    image_->setMetadata(*other);

    EXPECT_EQ(image_->comment(), "Other comment");
    EXPECT_FALSE(image_->exifData().empty());
}

// --- ICC Profile ---

TEST_F(ImageTest_1083, IccProfileNotDefinedByDefault_1083) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1083, ClearIccProfile_1083) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1083, SetIccProfileValid_1083) {
    // Minimal ICC profile-like data (at least 132 bytes with correct header)
    // ICC profile signature at offset 36: 'acsp'
    std::vector<uint8_t> iccData(132, 0);
    // Set profile size in first 4 bytes (big-endian)
    iccData[0] = 0; iccData[1] = 0; iccData[2] = 0; iccData[3] = 132;
    // Set 'acsp' signature at offset 36
    iccData[36] = 'a'; iccData[37] = 'c'; iccData[38] = 's'; iccData[39] = 'p';

    Exiv2::DataBuf buf(iccData.data(), iccData.size());
    image_->setIccProfile(std::move(buf), true);
    EXPECT_TRUE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1083, SetIccProfileNoValidation_1083) {
    std::vector<uint8_t> iccData(100, 0x42);
    Exiv2::DataBuf buf(iccData.data(), iccData.size());
    image_->setIccProfile(std::move(buf), false);
    EXPECT_TRUE(image_->iccProfileDefined());
}

// --- nativePreviews ---

TEST_F(ImageTest_1083, NativePreviewsInitiallyEmpty_1083) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// --- imageType ---

TEST_F(ImageTest_1083, ImageTypeReturnsSetType_1083) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// --- Static helper methods ---

TEST_F(ImageTest_1083, IsBigOrLittleEndianPlatform_1083) {
    // Exactly one of these should be true
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

TEST_F(ImageTest_1083, ByteSwap16NoSwap_1083) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234);
}

TEST_F(ImageTest_1083, ByteSwap16WithSwap_1083) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412);
}

TEST_F(ImageTest_1083, ByteSwap32NoSwap_1083) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST_F(ImageTest_1083, ByteSwap32WithSwap_1083) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST_F(ImageTest_1083, ByteSwap64NoSwap_1083) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_1083, ByteSwap64WithSwap_1083) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

TEST_F(ImageTest_1083, ByteSwap2FromBuf_1083) {
    uint8_t data[] = {0x12, 0x34, 0x00, 0x00};
    Exiv2::DataBuf buf(data, sizeof(data));
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(noSwap, 0x1234);
    EXPECT_EQ(swapped, 0x3412);
}

TEST_F(ImageTest_1083, ByteSwap4FromBuf_1083) {
    uint8_t data[] = {0x12, 0x34, 0x56, 0x78};
    Exiv2::DataBuf buf(data, sizeof(data));
    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(noSwap, 0x12345678u);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageTest_1083, ByteSwap8FromBuf_1083) {
    uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    Exiv2::DataBuf buf(data, sizeof(data));
    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(noSwap, 0x0102030405060708ULL);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// --- Type checking static methods ---

TEST_F(ImageTest_1083, IsStringType_1083) {
    // Exiv2 TIFF type 2 = ASCII
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    EXPECT_FALSE(Exiv2::Image::isStringType(3)); // SHORT
}

TEST_F(ImageTest_1083, IsShortType_1083) {
    // Type 3 = SHORT, Type 8 = SSHORT
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_TRUE(Exiv2::Image::isShortType(8));
    EXPECT_FALSE(Exiv2::Image::isShortType(4)); // LONG
}

TEST_F(ImageTest_1083, IsLongType_1083) {
    // Type 4 = LONG, Type 9 = SLONG
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_TRUE(Exiv2::Image::isLongType(9));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

TEST_F(ImageTest_1083, IsRationalType_1083) {
    // Type 5 = RATIONAL, Type 10 = SRATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_TRUE(Exiv2::Image::isRationalType(10));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

TEST_F(ImageTest_1083, Is2ByteType_1083) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));  // SHORT
    EXPECT_TRUE(Exiv2::Image::is2ByteType(8));  // SSHORT
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4)); // LONG
}

TEST_F(ImageTest_1083, Is4ByteType_1083) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));  // LONG
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));  // SLONG
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3)); // SHORT
}

TEST_F(ImageTest_1083, Is8ByteType_1083) {
    // Type 5 = RATIONAL (two LONGs = 8 bytes)
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10)); // SRATIONAL
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4)); // LONG
}

// --- Copy semantics disabled ---

TEST_F(ImageTest_1083, ImageIsNotCopyConstructible_1083) {
    EXPECT_FALSE(std::is_copy_constructible<TestImage>::value);
}

TEST_F(ImageTest_1083, ImageIsNotCopyAssignable_1083) {
    EXPECT_FALSE(std::is_copy_assignable<TestImage>::value);
}

// --- mimeType ---

TEST_F(ImageTest_1083, MimeTypeReturnsExpected_1083) {
    EXPECT_EQ(image_->mimeType(), "application/octet-stream");
}

// --- Boundary: ByteSwap with zero ---

TEST_F(ImageTest_1083, ByteSwap16Zero_1083) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_1083, ByteSwap32Zero_1083) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST_F(ImageTest_1083, ByteSwap64Zero_1083) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// --- Boundary: ByteSwap with max values ---

TEST_F(ImageTest_1083, ByteSwap16Max_1083) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFF);
}

TEST_F(ImageTest_1083, ByteSwap32Max_1083) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
}

TEST_F(ImageTest_1083, ByteSwap64Max_1083) {
    uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFFFFFFFFFULL);
}

// --- setTypeSupported ---

TEST_F(ImageTest_1083, SetTypeSupportedChangesType_1083) {
    image_->setTypeSupported(Exiv2::ImageType::jpeg, 0x0001);
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::jpeg);
}

// --- isPrintXMP / isPrintICC ---

TEST_F(ImageTest_1083, IsPrintXMP_1083) {
    // type 700 is typically XMP in TIFF
    // When option is kpsXMP, should return true for XMP tag
    bool result = Exiv2::Image::isPrintXMP(700, Exiv2::kpsXMP);
    EXPECT_TRUE(result);
}

TEST_F(ImageTest_1083, IsPrintXMPFalseForOtherOption_1083) {
    bool result = Exiv2::Image::isPrintXMP(700, Exiv2::kpsBasic);
    EXPECT_FALSE(result);
}

TEST_F(ImageTest_1083, IsPrintICC_1083) {
    // type 34675 is ICC Profile tag
    bool result = Exiv2::Image::isPrintICC(34675, Exiv2::kpsIccProfile);
    EXPECT_TRUE(result);
}

TEST_F(ImageTest_1083, IsPrintICCFalseForOtherOption_1083) {
    bool result = Exiv2::Image::isPrintICC(34675, Exiv2::kpsBasic);
    EXPECT_FALSE(result);
}

// --- Multiple operations sequence ---

TEST_F(ImageTest_1083, SequenceOfOperations_1083) {
    // Set various metadata
    image_->setComment("Test");
    image_->setByteOrder(Exiv2::bigEndian);
    image_->writeXmpFromPacket(true);

    EXPECT_EQ(image_->comment(), "Test");
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
    EXPECT_TRUE(image_->writeXmpFromPacket());

    // Clear everything
    image_->clearMetadata();
    EXPECT_EQ(image_->comment(), "");

    // byteOrder and writeXmpFromPacket are not cleared by clearMetadata
    // (they are not metadata in the same sense), but comment should be cleared
}
