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

// We need a concrete Image subclass since Image is abstract (readMetadata/writeMetadata are pure virtual)
// We'll use a minimal approach: create a MemIo-based image and use ImageFactory if available,
// or create a test subclass.

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
    std::string mimeType() const override { return "application/test"; }
};

std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
}

} // anonymous namespace

class ImageTest_1076 : public ::testing::Test {
protected:
    void SetUp() override {
        image_ = createTestImage();
    }

    std::unique_ptr<TestImage> image_;
};

// ==================== setIptcData / iptcData tests ====================

TEST_F(ImageTest_1076, SetIptcDataCopiesData_1076) {
    Exiv2::IptcData iptcData;
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test Caption");
    iptcData.add(datum);

    image_->setIptcData(iptcData);

    EXPECT_FALSE(image_->iptcData().empty());
    EXPECT_EQ(image_->iptcData().size(), 1u);
}

TEST_F(ImageTest_1076, SetIptcDataWithEmptyData_1076) {
    Exiv2::IptcData emptyData;
    image_->setIptcData(emptyData);

    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_EQ(image_->iptcData().size(), 0u);
}

TEST_F(ImageTest_1076, ClearIptcData_1076) {
    Exiv2::IptcData iptcData;
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test Caption");
    iptcData.add(datum);
    image_->setIptcData(iptcData);

    image_->clearIptcData();
    EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_1076, SetIptcDataOverwritesPrevious_1076) {
    Exiv2::IptcData iptcData1;
    Exiv2::Iptcdatum datum1(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum1.setValue("First");
    iptcData1.add(datum1);
    image_->setIptcData(iptcData1);
    EXPECT_EQ(image_->iptcData().size(), 1u);

    Exiv2::IptcData iptcData2;
    Exiv2::Iptcdatum datum2a(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum2a.setValue("Second");
    iptcData2.add(datum2a);
    Exiv2::Iptcdatum datum2b(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum2b.setValue("keyword");
    iptcData2.add(datum2b);
    image_->setIptcData(iptcData2);

    EXPECT_EQ(image_->iptcData().size(), 2u);
}

// ==================== setExifData / exifData / clearExifData tests ====================

TEST_F(ImageTest_1076, SetExifDataAndRetrieve_1076) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);

    EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_1076, ClearExifData_1076) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);

    image_->clearExifData();
    EXPECT_TRUE(image_->exifData().empty());
}

// ==================== setXmpData / xmpData / clearXmpData tests ====================

TEST_F(ImageTest_1076, SetXmpDataAndRetrieve_1076) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);

    EXPECT_FALSE(image_->xmpData().empty());
}

TEST_F(ImageTest_1076, ClearXmpData_1076) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image_->setXmpData(xmpData);

    image_->clearXmpData();
    EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== setXmpPacket / xmpPacket / clearXmpPacket tests ====================

TEST_F(ImageTest_1076, SetXmpPacketAndRetrieve_1076) {
    std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
    image_->setXmpPacket(packet);

    EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageTest_1076, ClearXmpPacket_1076) {
    image_->setXmpPacket("some packet");
    image_->clearXmpPacket();
    EXPECT_TRUE(image_->xmpPacket().empty());
}

// ==================== setComment / comment / clearComment tests ====================

TEST_F(ImageTest_1076, SetCommentAndRetrieve_1076) {
    std::string comment = "This is a test comment";
    image_->setComment(comment);

    EXPECT_EQ(image_->comment(), comment);
}

TEST_F(ImageTest_1076, SetEmptyComment_1076) {
    image_->setComment("");
    EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_1076, ClearComment_1076) {
    image_->setComment("A comment");
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== clearMetadata tests ====================

TEST_F(ImageTest_1076, ClearMetadataClearsAll_1076) {
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image_->setExifData(exifData);

    Exiv2::IptcData iptcData;
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Test Caption");
    iptcData.add(datum);
    image_->setIptcData(iptcData);

    image_->setComment("A comment");

    image_->clearMetadata();

    EXPECT_TRUE(image_->exifData().empty());
    EXPECT_TRUE(image_->iptcData().empty());
    EXPECT_TRUE(image_->comment().empty());
}

// ==================== setMetadata tests ====================

TEST_F(ImageTest_1076, SetMetadataFromAnotherImage_1076) {
    auto sourceImage = createTestImage();

    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "SourceMake";
    sourceImage->setExifData(exifData);

    Exiv2::IptcData iptcData;
    Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum.setValue("Source Caption");
    iptcData.add(datum);
    sourceImage->setIptcData(iptcData);

    sourceImage->setComment("Source Comment");

    image_->setMetadata(*sourceImage);

    EXPECT_FALSE(image_->exifData().empty());
    EXPECT_FALSE(image_->iptcData().empty());
    EXPECT_EQ(image_->comment(), "Source Comment");
}

// ==================== byteOrder / setByteOrder tests ====================

TEST_F(ImageTest_1076, DefaultByteOrderIsInvalid_1076) {
    EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1076, SetByteOrderBigEndian_1076) {
    image_->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1076, SetByteOrderLittleEndian_1076) {
    image_->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// ==================== writeXmpFromPacket tests ====================

TEST_F(ImageTest_1076, WriteXmpFromPacketDefaultFalse_1076) {
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1076, WriteXmpFromPacketSetTrue_1076) {
    image_->writeXmpFromPacket(true);
    EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1076, WriteXmpFromPacketSetFalse_1076) {
    image_->writeXmpFromPacket(true);
    image_->writeXmpFromPacket(false);
    EXPECT_FALSE(image_->writeXmpFromPacket());
}

// ==================== pixelWidth / pixelHeight tests ====================

TEST_F(ImageTest_1076, DefaultPixelWidthIsZero_1076) {
    EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_1076, DefaultPixelHeightIsZero_1076) {
    EXPECT_EQ(image_->pixelHeight(), 0u);
}

// ==================== good tests ====================

TEST_F(ImageTest_1076, GoodReturnsTrueForValidIo_1076) {
    // MemIo should be in a good state
    EXPECT_TRUE(image_->good());
}

// ==================== mimeType tests ====================

TEST_F(ImageTest_1076, MimeTypeReturnsExpected_1076) {
    EXPECT_EQ(image_->mimeType(), "application/test");
}

// ==================== imageType tests ====================

TEST_F(ImageTest_1076, ImageTypeReturnsNone_1076) {
    EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// ==================== nativePreviews tests ====================

TEST_F(ImageTest_1076, NativePreviewsInitiallyEmpty_1076) {
    EXPECT_TRUE(image_->nativePreviews().empty());
}

// ==================== iccProfile tests ====================

TEST_F(ImageTest_1076, IccProfileNotDefinedByDefault_1076) {
    EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_1076, ClearIccProfile_1076) {
    image_->clearIccProfile();
    EXPECT_FALSE(image_->iccProfileDefined());
}

// ==================== Static utility method tests ====================

TEST_F(ImageTest_1076, IsStringType_1076) {
    // Type 2 is ASCII in TIFF
    EXPECT_TRUE(Exiv2::Image::isStringType(2));
    EXPECT_FALSE(Exiv2::Image::isStringType(3)); // SHORT
}

TEST_F(ImageTest_1076, IsShortType_1076) {
    // Type 3 is SHORT, type 8 is SSHORT
    EXPECT_TRUE(Exiv2::Image::isShortType(3));
    EXPECT_TRUE(Exiv2::Image::isShortType(8));
    EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

TEST_F(ImageTest_1076, IsLongType_1076) {
    // Type 4 is LONG, type 9 is SLONG
    EXPECT_TRUE(Exiv2::Image::isLongType(4));
    EXPECT_TRUE(Exiv2::Image::isLongType(9));
    EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

TEST_F(ImageTest_1076, IsRationalType_1076) {
    // Type 5 is RATIONAL, type 10 is SRATIONAL
    EXPECT_TRUE(Exiv2::Image::isRationalType(5));
    EXPECT_TRUE(Exiv2::Image::isRationalType(10));
    EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

TEST_F(ImageTest_1076, Is2ByteType_1076) {
    EXPECT_TRUE(Exiv2::Image::is2ByteType(3));  // SHORT
    EXPECT_TRUE(Exiv2::Image::is2ByteType(8));  // SSHORT
    EXPECT_FALSE(Exiv2::Image::is2ByteType(4)); // LONG
}

TEST_F(ImageTest_1076, Is4ByteType_1076) {
    EXPECT_TRUE(Exiv2::Image::is4ByteType(4));  // LONG
    EXPECT_TRUE(Exiv2::Image::is4ByteType(9));  // SLONG
    EXPECT_FALSE(Exiv2::Image::is4ByteType(3)); // SHORT
}

TEST_F(ImageTest_1076, Is8ByteType_1076) {
    EXPECT_TRUE(Exiv2::Image::is8ByteType(5));   // RATIONAL
    EXPECT_TRUE(Exiv2::Image::is8ByteType(10));  // SRATIONAL
    EXPECT_FALSE(Exiv2::Image::is8ByteType(4));  // LONG
}

// ==================== Endianness tests ====================

TEST_F(ImageTest_1076, EndianPlatformConsistency_1076) {
    // Exactly one must be true
    bool big = Exiv2::Image::isBigEndianPlatform();
    bool little = Exiv2::Image::isLittleEndianPlatform();
    EXPECT_NE(big, little);
}

// ==================== ByteSwap tests ====================

TEST_F(ImageTest_1076, ByteSwap16NoSwap_1076) {
    uint16_t val = 0x1234;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1076, ByteSwap16WithSwap_1076) {
    uint16_t val = 0x1234;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x3412u);
}

TEST_F(ImageTest_1076, ByteSwap32NoSwap_1076) {
    uint32_t val = 0x12345678;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1076, ByteSwap32WithSwap_1076) {
    uint32_t val = 0x12345678;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageTest_1076, ByteSwap64NoSwap_1076) {
    uint64_t val = 0x0102030405060708ULL;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1076, ByteSwap64WithSwap_1076) {
    uint64_t val = 0x0102030405060708ULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// ==================== io() tests ====================

TEST_F(ImageTest_1076, IoReturnsReference_1076) {
    Exiv2::BasicIo& io = image_->io();
    // Just ensure we can access the io reference without crash
    (void)io;
    SUCCEED();
}

// ==================== Multiple set/clear cycles ====================

TEST_F(ImageTest_1076, MultipleClearSetCycles_1076) {
    for (int i = 0; i < 5; ++i) {
        Exiv2::IptcData iptcData;
        Exiv2::Iptcdatum datum(Exiv2::IptcKey("Iptc.Application2.Caption"));
        datum.setValue("Iteration " + std::to_string(i));
        iptcData.add(datum);
        image_->setIptcData(iptcData);
        EXPECT_EQ(image_->iptcData().size(), 1u);

        image_->clearIptcData();
        EXPECT_TRUE(image_->iptcData().empty());
    }
}

// ==================== setIptcData with multiple entries ====================

TEST_F(ImageTest_1076, SetIptcDataMultipleEntries_1076) {
    Exiv2::IptcData iptcData;
    
    Exiv2::Iptcdatum datum1(Exiv2::IptcKey("Iptc.Application2.Caption"));
    datum1.setValue("Caption");
    iptcData.add(datum1);

    Exiv2::Iptcdatum datum2(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum2.setValue("keyword1");
    iptcData.add(datum2);

    Exiv2::Iptcdatum datum3(Exiv2::IptcKey("Iptc.Application2.Keywords"));
    datum3.setValue("keyword2");
    iptcData.add(datum3);

    image_->setIptcData(iptcData);

    EXPECT_EQ(image_->iptcData().size(), 3u);
}

// ==================== IsLongLongType ====================

TEST_F(ImageTest_1076, IsLongLongType_1076) {
    // Type 16 is LONG8, type 17 is SLONG8 in BigTIFF
    // We just test that non-longlong types return false
    EXPECT_FALSE(Exiv2::Image::isLongLongType(4));  // LONG is not LONGLONG
    EXPECT_FALSE(Exiv2::Image::isLongLongType(3));  // SHORT
}

// ==================== ByteSwap2 from DataBuf ====================

TEST_F(ImageTest_1076, ByteSwap2FromDataBuf_1076) {
    Exiv2::DataBuf buf(4);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    
    uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
    EXPECT_EQ(noSwap, 0x1234u);

    uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
    EXPECT_EQ(swapped, 0x3412u);
}

TEST_F(ImageTest_1076, ByteSwap4FromDataBuf_1076) {
    Exiv2::DataBuf buf(8);
    buf.data()[0] = 0x12;
    buf.data()[1] = 0x34;
    buf.data()[2] = 0x56;
    buf.data()[3] = 0x78;

    uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
    EXPECT_EQ(noSwap, 0x12345678u);

    uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
    EXPECT_EQ(swapped, 0x78563412u);
}

TEST_F(ImageTest_1076, ByteSwap8FromDataBuf_1076) {
    Exiv2::DataBuf buf(16);
    buf.data()[0] = 0x01;
    buf.data()[1] = 0x02;
    buf.data()[2] = 0x03;
    buf.data()[3] = 0x04;
    buf.data()[4] = 0x05;
    buf.data()[5] = 0x06;
    buf.data()[6] = 0x07;
    buf.data()[7] = 0x08;

    uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
    EXPECT_EQ(noSwap, 0x0102030405060708ULL);

    uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
    EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// ==================== Boundary: ByteSwap with zero values ====================

TEST_F(ImageTest_1076, ByteSwap16Zero_1076) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_1076, ByteSwap32Zero_1076) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST_F(ImageTest_1076, ByteSwap64Zero_1076) {
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
    EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// ==================== Boundary: ByteSwap with max values ====================

TEST_F(ImageTest_1076, ByteSwap16Max_1076) {
    uint16_t val = 0xFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFu);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFu);
}

TEST_F(ImageTest_1076, ByteSwap32Max_1076) {
    uint32_t val = 0xFFFFFFFF;
    EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
    EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFu);
}

// ==================== Double swap should restore original ====================

TEST_F(ImageTest_1076, ByteSwap16DoubleSwapRestores_1076) {
    uint16_t val = 0xABCD;
    uint16_t swapped = Exiv2::Image::byteSwap(val, true);
    uint16_t restored = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, val);
}

TEST_F(ImageTest_1076, ByteSwap32DoubleSwapRestores_1076) {
    uint32_t val = 0xDEADBEEF;
    uint32_t swapped = Exiv2::Image::byteSwap(val, true);
    uint32_t restored = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, val);
}

TEST_F(ImageTest_1076, ByteSwap64DoubleSwapRestores_1076) {
    uint64_t val = 0xDEADBEEFCAFEBABEULL;
    uint64_t swapped = Exiv2::Image::byteSwap(val, true);
    uint64_t restored = Exiv2::Image::byteSwap(swapped, true);
    EXPECT_EQ(restored, val);
}
