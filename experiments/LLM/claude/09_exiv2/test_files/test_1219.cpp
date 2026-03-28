#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/jpgimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/image.hpp>

#include <cstring>
#include <fstream>
#include <sstream>

namespace {

// Minimal valid JPEG data: SOI marker + EOI marker
const Exiv2::byte kMinimalJpeg[] = {0xFF, 0xD8, 0xFF, 0xD9};

// JPEG SOI marker
const Exiv2::byte kJpegSoi[] = {0xFF, 0xD8};

// Helper to create a more complete minimal JPEG with APP0 segment
std::vector<Exiv2::byte> createMinimalJpegData() {
    // SOI + APP0 (JFIF) + SOF0 + SOS + EOI
    // This is a minimal but more realistic JPEG structure
    std::vector<Exiv2::byte> data;
    // SOI
    data.push_back(0xFF);
    data.push_back(0xD8);
    // APP0 JFIF marker
    data.push_back(0xFF);
    data.push_back(0xE0);
    // Length (16 bytes)
    data.push_back(0x00);
    data.push_back(0x10);
    // JFIF identifier
    data.push_back('J');
    data.push_back('F');
    data.push_back('I');
    data.push_back('F');
    data.push_back(0x00);
    // Version
    data.push_back(0x01);
    data.push_back(0x01);
    // Units
    data.push_back(0x00);
    // X density
    data.push_back(0x00);
    data.push_back(0x01);
    // Y density
    data.push_back(0x00);
    data.push_back(0x01);
    // Thumbnail
    data.push_back(0x00);
    data.push_back(0x00);
    // SOF0
    data.push_back(0xFF);
    data.push_back(0xC0);
    // Length (11 bytes)
    data.push_back(0x00);
    data.push_back(0x0B);
    // Precision
    data.push_back(0x08);
    // Height (1)
    data.push_back(0x00);
    data.push_back(0x01);
    // Width (1)
    data.push_back(0x00);
    data.push_back(0x01);
    // Number of components
    data.push_back(0x01);
    // Component 1
    data.push_back(0x01);
    data.push_back(0x11);
    data.push_back(0x00);
    // SOS
    data.push_back(0xFF);
    data.push_back(0xDA);
    // Length (8 bytes)
    data.push_back(0x00);
    data.push_back(0x08);
    // Number of components
    data.push_back(0x01);
    // Component selector
    data.push_back(0x01);
    data.push_back(0x00);
    // Spectral selection
    data.push_back(0x00);
    data.push_back(0x3F);
    data.push_back(0x00);
    // Scan data (minimal)
    data.push_back(0x00);
    // EOI
    data.push_back(0xFF);
    data.push_back(0xD9);
    return data;
}

// Helper to get a JPEG image from memory data
std::unique_ptr<Exiv2::Image> createJpegImageFromData(const Exiv2::byte* data, size_t size) {
    auto io = std::make_unique<Exiv2::MemIo>(data, size);
    return Exiv2::ImageFactory::open(std::move(io));
}

} // anonymous namespace

class JpegBaseTest_1219 : public ::testing::Test {
protected:
    void SetUp() override {
        jpegData_ = createMinimalJpegData();
    }

    std::vector<Exiv2::byte> jpegData_;
};

// Test that readMetadata works on a minimal JPEG
TEST_F(JpegBaseTest_1219, ReadMetadataOnMinimalJpeg_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
}

// Test that writeMetadata works on a minimal JPEG
TEST_F(JpegBaseTest_1219, WriteMetadataOnMinimalJpeg_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    EXPECT_NO_THROW(image->readMetadata());
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test that mimeType returns correct JPEG mime type
TEST_F(JpegBaseTest_1219, MimeTypeIsJpeg_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    EXPECT_EQ(image->mimeType(), "image/jpeg");
}

// Test that good() returns true for a valid JPEG
TEST_F(JpegBaseTest_1219, GoodReturnsTrueForValidJpeg_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->good());
}

// Test readMetadata on invalid data throws
TEST_F(JpegBaseTest_1219, ReadMetadataOnInvalidDataThrows_1219) {
    const Exiv2::byte invalidData[] = {0x00, 0x00, 0x00, 0x00};
    try {
        auto image = createJpegImageFromData(invalidData, sizeof(invalidData));
        if (image) {
            EXPECT_THROW(image->readMetadata(), Exiv2::Error);
        }
    } catch (const Exiv2::Error&) {
        // ImageFactory::open may also throw for invalid data
    }
}

// Test that exifData is initially empty after reading a minimal JPEG
TEST_F(JpegBaseTest_1219, ExifDataInitiallyEmpty_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_TRUE(image->exifData().empty());
}

// Test that iptcData is initially empty after reading a minimal JPEG
TEST_F(JpegBaseTest_1219, IptcDataInitiallyEmpty_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_TRUE(image->iptcData().empty());
}

// Test that xmpData is initially empty after reading a minimal JPEG
TEST_F(JpegBaseTest_1219, XmpDataInitiallyEmpty_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_TRUE(image->xmpData().empty());
}

// Test that comment is initially empty
TEST_F(JpegBaseTest_1219, CommentInitiallyEmpty_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_TRUE(image->comment().empty());
}

// Test setComment and writeMetadata roundtrip
TEST_F(JpegBaseTest_1219, SetCommentRoundTrip_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    const std::string testComment = "Test comment for JPEG";
    image->setComment(testComment);
    image->writeMetadata();
    
    // Re-read to verify
    image->readMetadata();
    EXPECT_EQ(image->comment(), testComment);
}

// Test clearComment
TEST_F(JpegBaseTest_1219, ClearComment_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    image->setComment("Some comment");
    image->writeMetadata();
    image->readMetadata();
    
    image->clearComment();
    image->writeMetadata();
    image->readMetadata();
    EXPECT_TRUE(image->comment().empty());
}

// Test that setExifData and writeMetadata doesn't throw
TEST_F(JpegBaseTest_1219, SetExifDataAndWrite_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image->setExifData(exifData);
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test that clearExifData removes exif
TEST_F(JpegBaseTest_1219, ClearExifData_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestMake";
    image->setExifData(exifData);
    image->writeMetadata();
    
    image->readMetadata();
    image->clearExifData();
    EXPECT_TRUE(image->exifData().empty());
}

// Test setIptcData and write
TEST_F(JpegBaseTest_1219, SetIptcDataAndWrite_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test caption";
    image->setIptcData(iptcData);
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test clearIptcData
TEST_F(JpegBaseTest_1219, ClearIptcData_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    image->clearIptcData();
    EXPECT_TRUE(image->iptcData().empty());
}

// Test pixelWidth and pixelHeight after reading minimal JPEG
TEST_F(JpegBaseTest_1219, PixelDimensionsAfterRead_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    // Our minimal JPEG has 1x1 dimensions
    EXPECT_EQ(image->pixelWidth(), 1u);
    EXPECT_EQ(image->pixelHeight(), 1u);
}

// Test that io() returns a valid reference
TEST_F(JpegBaseTest_1219, IoReturnsValidReference_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    const Exiv2::BasicIo& io = image->io();
    EXPECT_FALSE(io.path().empty());
}

// Test clearMetadata
TEST_F(JpegBaseTest_1219, ClearMetadata_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    image->setComment("Test");
    image->clearMetadata();
    EXPECT_TRUE(image->comment().empty());
    EXPECT_TRUE(image->exifData().empty());
    EXPECT_TRUE(image->iptcData().empty());
    EXPECT_TRUE(image->xmpData().empty());
}

// Test printStructure doesn't throw for valid JPEG
TEST_F(JpegBaseTest_1219, PrintStructureNoThrow_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    std::ostringstream oss;
    EXPECT_NO_THROW(image->printStructure(oss, Exiv2::kpsBasic, 0));
}

// Test writeMetadata after setting XMP data
TEST_F(JpegBaseTest_1219, SetXmpDataAndWrite_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";
    image->setXmpData(xmpData);
    EXPECT_NO_THROW(image->writeMetadata());
}

// Test clearXmpData
TEST_F(JpegBaseTest_1219, ClearXmpData_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    image->clearXmpData();
    EXPECT_TRUE(image->xmpData().empty());
}

// Test that writing metadata multiple times doesn't corrupt the image
TEST_F(JpegBaseTest_1219, MultipleWriteMetadata_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    image->setComment("First comment");
    EXPECT_NO_THROW(image->writeMetadata());
    
    image->readMetadata();
    image->setComment("Second comment");
    EXPECT_NO_THROW(image->writeMetadata());
    
    image->readMetadata();
    EXPECT_EQ(image->comment(), "Second comment");
}

// Test that supportsMetadata returns correct values for JPEG
TEST_F(JpegBaseTest_1219, SupportsMetadata_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    EXPECT_TRUE(image->supportsMetadata(Exiv2::mdExif));
    EXPECT_TRUE(image->supportsMetadata(Exiv2::mdIptc));
    EXPECT_TRUE(image->supportsMetadata(Exiv2::mdXmp));
    EXPECT_TRUE(image->supportsMetadata(Exiv2::mdComment));
}

// Test setByteOrder and byteOrder
TEST_F(JpegBaseTest_1219, ByteOrder_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    
    image->setByteOrder(Exiv2::bigEndian);
    EXPECT_EQ(image->byteOrder(), Exiv2::bigEndian);
    
    image->setByteOrder(Exiv2::littleEndian);
    EXPECT_EQ(image->byteOrder(), Exiv2::littleEndian);
}

// Test with only SOI marker (too small, should fail)
TEST_F(JpegBaseTest_1219, TooSmallJpegData_1219) {
    const Exiv2::byte tooSmall[] = {0xFF, 0xD8};
    try {
        auto image = createJpegImageFromData(tooSmall, sizeof(tooSmall));
        if (image) {
            EXPECT_THROW(image->readMetadata(), Exiv2::Error);
        }
    } catch (const Exiv2::Error&) {
        // May throw during open
    }
}

// Test empty data
TEST_F(JpegBaseTest_1219, EmptyDataThrows_1219) {
    const Exiv2::byte emptyData[] = {0};
    EXPECT_THROW(createJpegImageFromData(emptyData, 0), Exiv2::Error);
}

// Test writeXmpFromPacket flag
TEST_F(JpegBaseTest_1219, WriteXmpFromPacketFlag_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    
    image->writeXmpFromPacket(true);
    EXPECT_TRUE(image->writeXmpFromPacket());
    
    image->writeXmpFromPacket(false);
    EXPECT_FALSE(image->writeXmpFromPacket());
}

// Test ICC profile operations
TEST_F(JpegBaseTest_1219, IccProfileInitiallyUndefined_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    EXPECT_FALSE(image->iccProfileDefined());
}

// Test clearIccProfile
TEST_F(JpegBaseTest_1219, ClearIccProfile_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    image->clearIccProfile();
    EXPECT_FALSE(image->iccProfileDefined());
}

// Test Exif roundtrip: write then read back
TEST_F(JpegBaseTest_1219, ExifRoundTrip_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    Exiv2::ExifData exifData;
    exifData["Exif.Image.Make"] = "TestCamera";
    exifData["Exif.Image.Model"] = "TestModel";
    image->setExifData(exifData);
    image->writeMetadata();
    
    image->readMetadata();
    EXPECT_FALSE(image->exifData().empty());
    auto it = image->exifData().findKey(Exiv2::ExifKey("Exif.Image.Make"));
    ASSERT_NE(it, image->exifData().end());
    EXPECT_EQ(it->toString(), "TestCamera");
}

// Test IPTC roundtrip
TEST_F(JpegBaseTest_1219, IptcRoundTrip_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    
    Exiv2::IptcData iptcData;
    iptcData["Iptc.Application2.Caption"] = "Test IPTC Caption";
    image->setIptcData(iptcData);
    image->writeMetadata();
    
    image->readMetadata();
    EXPECT_FALSE(image->iptcData().empty());
}

// Test xmpPacket accessor
TEST_F(JpegBaseTest_1219, XmpPacketAccessor_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    // xmpPacket should be accessible (may be empty for minimal JPEG)
    std::string& packet = image->xmpPacket();
    EXPECT_TRUE(packet.empty());
}

// Test clearXmpPacket
TEST_F(JpegBaseTest_1219, ClearXmpPacket_1219) {
    auto image = createJpegImageFromData(jpegData_.data(), jpegData_.size());
    ASSERT_NE(image, nullptr);
    image->readMetadata();
    image->clearXmpPacket();
    EXPECT_TRUE(image->xmpPacket().empty());
}
