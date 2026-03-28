#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/jpgimage.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <fstream>
#include <cstring>
#include <sstream>

namespace {

// Minimal JPEG data: SOI marker + EOI marker
const Exiv2::byte minimalJpegData[] = {0xFF, 0xD8, 0xFF, 0xD9};
const size_t minimalJpegDataSize = sizeof(minimalJpegData);

// JFIF JPEG header for a more complete minimal JPEG
const Exiv2::byte jpegHeader[] = {
    0xFF, 0xD8,                         // SOI
    0xFF, 0xE0,                         // APP0 marker
    0x00, 0x10,                         // Length = 16
    0x4A, 0x46, 0x49, 0x46, 0x00,      // "JFIF\0"
    0x01, 0x01,                         // Version 1.1
    0x00,                               // Aspect ratio units
    0x00, 0x01,                         // X density
    0x00, 0x01,                         // Y density
    0x00, 0x00,                         // Thumbnail size
    0xFF, 0xD9                          // EOI
};
const size_t jpegHeaderSize = sizeof(jpegHeader);

// Helper to create a temporary JPEG file and return a MemIo with JPEG data
std::unique_ptr<Exiv2::BasicIo> createMemIoWithJpegData(const Exiv2::byte* data, size_t size) {
    auto memIo = std::make_unique<Exiv2::MemIo>(data, size);
    return memIo;
}

// Helper to create a MemIo with empty data
std::unique_ptr<Exiv2::BasicIo> createEmptyMemIo() {
    return std::make_unique<Exiv2::MemIo>();
}

} // anonymous namespace

// Since JpegBase is protected constructor, we need to use JpegImage which derives from it
// JpegImage is the concrete class that uses JpegBase

class JpegImageTest_2176 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Creating a JpegImage from valid JPEG data in memory
TEST_F(JpegImageTest_2176, CreateFromValidJpegMemIo_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    ASSERT_NE(memIo, nullptr);
    
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

// Test: Image type is JPEG
TEST_F(JpegImageTest_2176, ImageTypeIsJpeg_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->imageType(), Exiv2::ImageType::jpeg);
}

// Test: MIME type for JPEG image
TEST_F(JpegImageTest_2176, MimeTypeIsJpeg_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->mimeType(), "image/jpeg");
}

// Test: Supports EXIF metadata
TEST_F(JpegImageTest_2176, SupportsExifMetadata_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdExif));
}

// Test: Supports IPTC metadata
TEST_F(JpegImageTest_2176, SupportsIptcMetadata_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdIptc));
}

// Test: Supports XMP metadata
TEST_F(JpegImageTest_2176, SupportsXmpMetadata_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdXmp));
}

// Test: Supports Comment metadata
TEST_F(JpegImageTest_2176, SupportsCommentMetadata_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->supportsMetadata(Exiv2::MetadataId::mdComment));
}

// Test: Opening invalid data throws or fails
TEST_F(JpegImageTest_2176, OpenInvalidDataThrows_2176) {
    const Exiv2::byte invalidData[] = {0x00, 0x00, 0x00, 0x00};
    auto memIo = std::make_unique<Exiv2::MemIo>(invalidData, sizeof(invalidData));
    
    EXPECT_THROW(Exiv2::ImageFactory::open(std::move(memIo)), Exiv2::Error);
}

// Test: Opening empty data throws
TEST_F(JpegImageTest_2176, OpenEmptyDataThrows_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    EXPECT_THROW(Exiv2::ImageFactory::open(std::move(memIo)), Exiv2::Error);
}

// Test: readMetadata on minimal JPEG data
TEST_F(JpegImageTest_2176, ReadMetadataMinimalJpeg_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    // readMetadata should not throw on valid minimal JPEG
    EXPECT_NO_THROW(image->readMetadata());
}

// Test: ExifData is initially empty on minimal JPEG
TEST_F(JpegImageTest_2176, ExifDataInitiallyEmpty_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    EXPECT_TRUE(image->exifData().empty());
}

// Test: IptcData is initially empty on minimal JPEG
TEST_F(JpegImageTest_2176, IptcDataInitiallyEmpty_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    EXPECT_TRUE(image->iptcData().empty());
}

// Test: XmpData is initially empty on minimal JPEG
TEST_F(JpegImageTest_2176, XmpDataInitiallyEmpty_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    EXPECT_TRUE(image->xmpData().empty());
}

// Test: Comment is initially empty on minimal JPEG
TEST_F(JpegImageTest_2176, CommentInitiallyEmpty_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    EXPECT_TRUE(image->comment().empty());
}

// Test: Set and clear comment
TEST_F(JpegImageTest_2176, SetAndClearComment_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    std::string testComment = "Test comment for JPEG";
    image->setComment(testComment);
    EXPECT_EQ(image->comment(), testComment);
    
    image->clearComment();
    EXPECT_TRUE(image->comment().empty());
}

// Test: Set and clear EXIF data
TEST_F(JpegImageTest_2176, SetAndClearExifData_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image->setExifData(exifData);
    EXPECT_FALSE(image->exifData().empty());
    
    image->clearExifData();
    EXPECT_TRUE(image->exifData().empty());
}

// Test: Set and clear IPTC data
TEST_F(JpegImageTest_2176, SetAndClearIptcData_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    image->setIptcData(iptcData);
    EXPECT_FALSE(image->iptcData().empty());
    
    image->clearIptcData();
    EXPECT_TRUE(image->iptcData().empty());
}

// Test: Set and clear XMP data
TEST_F(JpegImageTest_2176, SetAndClearXmpData_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test title";
    image->setXmpData(xmpData);
    EXPECT_FALSE(image->xmpData().empty());
    
    image->clearXmpData();
    EXPECT_TRUE(image->xmpData().empty());
}

// Test: clearMetadata clears everything
TEST_F(JpegImageTest_2176, ClearMetadataClearsAll_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    // Set some data
    image->setComment("Test");
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image->setExifData(exifData);
    
    image->clearMetadata();
    
    EXPECT_TRUE(image->comment().empty());
    EXPECT_TRUE(image->exifData().empty());
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_TRUE(image->xmpData().empty());
}

// Test: good() returns true for valid JPEG
TEST_F(JpegImageTest_2176, GoodReturnsTrueForValidJpeg_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

// Test: pixelWidth and pixelHeight default to 0 on minimal JPEG
TEST_F(JpegImageTest_2176, PixelDimensionsDefaultZero_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    // Minimal JPEG without SOF, dimensions may be 0
    EXPECT_EQ(image->pixelWidth(), 0u);
    EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test: printStructure does not throw for valid JPEG
TEST_F(JpegImageTest_2176, PrintStructureNoThrow_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    std::ostringstream oss;
    EXPECT_NO_THROW(image->printStructure(oss, Exiv2::kpsBasic, 0));
}

// Test: writeXmpFromPacket flag
TEST_F(JpegImageTest_2176, WriteXmpFromPacketFlag_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    // Default should be false
    EXPECT_FALSE(image->writeXmpFromPacket());
    
    image->writeXmpFromPacket(true);
    EXPECT_TRUE(image->writeXmpFromPacket());
    
    image->writeXmpFromPacket(false);
    EXPECT_FALSE(image->writeXmpFromPacket());
}

// Test: byteOrder manipulation
TEST_F(JpegImageTest_2176, ByteOrderManipulation_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    image->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image->byteOrder(), Exiv2::bigEndian);
    
    image->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image->byteOrder(), Exiv2::littleEndian);
}

// Test: io() returns a reference to BasicIo
TEST_F(JpegImageTest_2176, IoReturnsReference_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    Exiv2::BasicIo& io = image->io();
    // The io should have data
    EXPECT_GT(io.size(), 0u);
}

// Test: nativePreviews returns a list (possibly empty for minimal JPEG)
TEST_F(JpegImageTest_2176, NativePreviewsEmpty_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    const Exiv2::NativePreviewList& previews = image->nativePreviews();
    // Minimal JPEG should have no native previews
    EXPECT_TRUE(previews.empty());
}

// Test: ICC profile is not defined on minimal JPEG
TEST_F(JpegImageTest_2176, IccProfileNotDefined_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    EXPECT_FALSE(image->iccProfileDefined());
}

// Test: Clear ICC profile
TEST_F(JpegImageTest_2176, ClearIccProfile_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    image->clearIccProfile();
    EXPECT_FALSE(image->iccProfileDefined());
}

// Test: readMetadata on SOI-only (just SOI + EOI) JPEG
TEST_F(JpegImageTest_2176, ReadMetadataMinimalSoiEoi_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(minimalJpegData, minimalJpegDataSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    // Even minimal SOI+EOI should be parseable (or throw a specific error)
    // This depends on the implementation. We just check it doesn't crash.
    try {
        image->readMetadata();
    } catch (const Exiv2::Error&) {
        // Expected for very minimal JPEG
    }
}

// Test: checkMode for supported metadata types
TEST_F(JpegImageTest_2176, CheckModeExif_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    auto mode = image->checkMode(Exiv2::MetadataId::mdExif);
    EXPECT_NE(mode, Exiv2::amNone);
}

// Test: checkMode for IPTC
TEST_F(JpegImageTest_2176, CheckModeIptc_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    auto mode = image->checkMode(Exiv2::MetadataId::mdIptc);
    EXPECT_NE(mode, Exiv2::amNone);
}

// Test: checkMode for XMP
TEST_F(JpegImageTest_2176, CheckModeXmp_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    auto mode = image->checkMode(Exiv2::MetadataId::mdXmp);
    EXPECT_NE(mode, Exiv2::amNone);
}

// Test: checkMode for Comment
TEST_F(JpegImageTest_2176, CheckModeComment_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    auto mode = image->checkMode(Exiv2::MetadataId::mdComment);
    EXPECT_NE(mode, Exiv2::amNone);
}

// Test: XMP packet is initially empty
TEST_F(JpegImageTest_2176, XmpPacketInitiallyEmpty_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    EXPECT_TRUE(image->xmpPacket().empty());
}

// Test: Set XMP packet
TEST_F(JpegImageTest_2176, SetXmpPacket_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    std::string xmpPacket = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\"></x:xmpmeta>";
    image->setXmpPacket(xmpPacket);
    EXPECT_EQ(image->xmpPacket(), xmpPacket);
    
    image->clearXmpPacket();
    EXPECT_TRUE(image->xmpPacket().empty());
}

// Test: Creating JPEG via ImageFactory::create (new image)
TEST_F(JpegImageTest_2176, CreateNewJpegImage_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, std::move(memIo));
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->imageType(), Exiv2::ImageType::jpeg);
    EXPECT_TRUE(image->good());
}

// Test: Writing metadata on a newly created JPEG
TEST_F(JpegImageTest_2176, WriteMetadataOnNewJpeg_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    image->setComment("New JPEG comment");
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test: Read back metadata after write
TEST_F(JpegImageTest_2176, WriteAndReadBackComment_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    std::string testComment = "Roundtrip test comment";
    image->setComment(testComment);
    image->writeMetadata();
    
    // Re-read
    image->readMetadata();
    EXPECT_EQ(image->comment(), testComment);
}

// Test: Write and read back EXIF data
TEST_F(JpegImageTest_2176, WriteAndReadBackExif_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestManufacturer";
    image->setExifData(exifData);
    image->writeMetadata();
    
    image->readMetadata();
    auto it = image->exifData().findKey(Exiv2::ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, image->exifData().end());
    EXPECT_EQ(it->toString(), "TestManufacturer");
}

// Test: printStructure with kpsNone option
TEST_F(JpegImageTest_2176, PrintStructureKpsNone_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>(jpegHeader, jpegHeaderSize);
    auto image = Exiv2::ImageFactory::open(std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    std::ostringstream oss;
    EXPECT_NO_THROW(image->printStructure(oss, Exiv2::kpsNone, 0));
}

// Test: Single byte data is not valid JPEG
TEST_F(JpegImageTest_2176, SingleByteInvalid_2176) {
    const Exiv2::byte singleByte[] = {0xFF};
    auto memIo = std::make_unique<Exiv2::MemIo>(singleByte, 1);
    EXPECT_THROW(Exiv2::ImageFactory::open(std::move(memIo)), Exiv2::Error);
}

// Test: Data starting with 0xFF but not 0xD8 is not valid JPEG
TEST_F(JpegImageTest_2176, InvalidSecondByte_2176) {
    const Exiv2::byte badData[] = {0xFF, 0x00, 0xFF, 0xD9};
    auto memIo = std::make_unique<Exiv2::MemIo>(badData, sizeof(badData));
    EXPECT_THROW(Exiv2::ImageFactory::open(std::move(memIo)), Exiv2::Error);
}

// Test: io size matches for created image
TEST_F(JpegImageTest_2176, IoSizeAfterCreate_2176) {
    auto memIo = std::make_unique<Exiv2::MemIo>();
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, std::move(memIo));
    ASSERT_NE(image, nullptr);
    
    // After creation, io should have at least SOI + EOI (4 bytes)
    EXPECT_GE(image->io().size(), 4u);
}
