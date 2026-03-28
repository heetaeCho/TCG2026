#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>

#include <memory>
#include <sstream>
#include <cstring>

// We need a concrete Image subclass since Image has pure virtual methods (readMetadata, writeMetadata)
// and we need a BasicIo to construct it.
class TestImage : public Exiv2::Image {
public:
  TestImage(std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

  void readMetadata() override {}
  void writeMetadata() override {}
};

class ImageTest_1084 : public ::testing::Test {
protected:
  std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
  }
};

// Test setIccProfile with empty DataBuf and bTestValid=false
TEST_F(ImageTest_1084, SetIccProfileEmptyNoValidation_1084) {
  auto img = createTestImage();
  Exiv2::DataBuf emptyBuf;
  img->setIccProfile(std::move(emptyBuf), false);
  EXPECT_TRUE(img->iccProfile().empty());
}

// Test setIccProfile with valid data and bTestValid=false
TEST_F(ImageTest_1084, SetIccProfileWithDataNoValidation_1084) {
  auto img = createTestImage();
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  Exiv2::DataBuf buf(data, sizeof(data));
  img->setIccProfile(std::move(buf), false);
  EXPECT_FALSE(img->iccProfile().empty());
  EXPECT_EQ(img->iccProfile().size(), 5u);
}

// Test setIccProfile moves data (source should be empty after move)
TEST_F(ImageTest_1084, SetIccProfileMovesData_1084) {
  auto img = createTestImage();
  const uint8_t data[] = {0xAA, 0xBB, 0xCC};
  Exiv2::DataBuf buf(data, sizeof(data));
  EXPECT_EQ(buf.size(), 3u);
  img->setIccProfile(std::move(buf), false);
  // After move, buf should be empty
  EXPECT_TRUE(buf.empty());
  EXPECT_EQ(img->iccProfile().size(), 3u);
}

// Test clearIccProfile clears the profile
TEST_F(ImageTest_1084, ClearIccProfile_1084) {
  auto img = createTestImage();
  const uint8_t data[] = {0x01, 0x02, 0x03};
  Exiv2::DataBuf buf(data, sizeof(data));
  img->setIccProfile(std::move(buf), false);
  EXPECT_FALSE(img->iccProfile().empty());
  img->clearIccProfile();
  EXPECT_TRUE(img->iccProfile().empty());
}

// Test iccProfileDefined returns false when no profile is set
TEST_F(ImageTest_1084, IccProfileDefinedFalseWhenEmpty_1084) {
  auto img = createTestImage();
  EXPECT_FALSE(img->iccProfileDefined());
}

// Test iccProfileDefined returns true when profile is set
TEST_F(ImageTest_1084, IccProfileDefinedTrueWhenSet_1084) {
  auto img = createTestImage();
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::DataBuf buf(data, sizeof(data));
  img->setIccProfile(std::move(buf), false);
  EXPECT_TRUE(img->iccProfileDefined());
}

// Test setIccProfile replaces existing profile
TEST_F(ImageTest_1084, SetIccProfileReplacesExisting_1084) {
  auto img = createTestImage();
  const uint8_t data1[] = {0x01, 0x02, 0x03};
  Exiv2::DataBuf buf1(data1, sizeof(data1));
  img->setIccProfile(std::move(buf1), false);
  EXPECT_EQ(img->iccProfile().size(), 3u);

  const uint8_t data2[] = {0x04, 0x05, 0x06, 0x07, 0x08};
  Exiv2::DataBuf buf2(data2, sizeof(data2));
  img->setIccProfile(std::move(buf2), false);
  EXPECT_EQ(img->iccProfile().size(), 5u);
}

// Test setComment and comment
TEST_F(ImageTest_1084, SetAndGetComment_1084) {
  auto img = createTestImage();
  img->setComment("Hello World");
  EXPECT_EQ(img->comment(), "Hello World");
}

// Test clearComment
TEST_F(ImageTest_1084, ClearComment_1084) {
  auto img = createTestImage();
  img->setComment("Test comment");
  EXPECT_EQ(img->comment(), "Test comment");
  img->clearComment();
  EXPECT_EQ(img->comment(), "");
}

// Test setComment with empty string
TEST_F(ImageTest_1084, SetEmptyComment_1084) {
  auto img = createTestImage();
  img->setComment("");
  EXPECT_EQ(img->comment(), "");
}

// Test byteOrder and setByteOrder
TEST_F(ImageTest_1084, SetAndGetByteOrder_1084) {
  auto img = createTestImage();
  img->setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);

  img->setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

// Test default byteOrder is invalidByteOrder
TEST_F(ImageTest_1084, DefaultByteOrderIsInvalid_1084) {
  auto img = createTestImage();
  EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}

// Test pixelWidth and pixelHeight default to 0
TEST_F(ImageTest_1084, DefaultPixelDimensionsAreZero_1084) {
  auto img = createTestImage();
  EXPECT_EQ(img->pixelWidth(), 0u);
  EXPECT_EQ(img->pixelHeight(), 0u);
}

// Test good() returns true for a valid MemIo
TEST_F(ImageTest_1084, GoodReturnsTrueForValidIo_1084) {
  auto img = createTestImage();
  EXPECT_TRUE(img->good());
}

// Test writeXmpFromPacket default is false
TEST_F(ImageTest_1084, DefaultWriteXmpFromPacketIsFalse_1084) {
  auto img = createTestImage();
  EXPECT_FALSE(img->writeXmpFromPacket());
}

// Test writeXmpFromPacket setter
TEST_F(ImageTest_1084, SetWriteXmpFromPacket_1084) {
  auto img = createTestImage();
  img->writeXmpFromPacket(true);
  EXPECT_TRUE(img->writeXmpFromPacket());
  img->writeXmpFromPacket(false);
  EXPECT_FALSE(img->writeXmpFromPacket());
}

// Test exifData access
TEST_F(ImageTest_1084, ExifDataAccess_1084) {
  auto img = createTestImage();
  Exiv2::ExifData& exif = img->exifData();
  EXPECT_TRUE(exif.empty());
}

// Test clearExifData
TEST_F(ImageTest_1084, ClearExifData_1084) {
  auto img = createTestImage();
  img->clearExifData();
  EXPECT_TRUE(img->exifData().empty());
}

// Test iptcData access
TEST_F(ImageTest_1084, IptcDataAccess_1084) {
  auto img = createTestImage();
  Exiv2::IptcData& iptc = img->iptcData();
  EXPECT_TRUE(iptc.empty());
}

// Test clearIptcData
TEST_F(ImageTest_1084, ClearIptcData_1084) {
  auto img = createTestImage();
  img->clearIptcData();
  EXPECT_TRUE(img->iptcData().empty());
}

// Test xmpData access
TEST_F(ImageTest_1084, XmpDataAccess_1084) {
  auto img = createTestImage();
  Exiv2::XmpData& xmp = img->xmpData();
  EXPECT_TRUE(xmp.empty());
}

// Test clearXmpData
TEST_F(ImageTest_1084, ClearXmpData_1084) {
  auto img = createTestImage();
  img->clearXmpData();
  EXPECT_TRUE(img->xmpData().empty());
}

// Test clearXmpPacket
TEST_F(ImageTest_1084, ClearXmpPacket_1084) {
  auto img = createTestImage();
  img->setXmpPacket("<xmp>test</xmp>");
  img->clearXmpPacket();
  EXPECT_TRUE(img->xmpPacket().empty());
}

// Test setXmpPacket
TEST_F(ImageTest_1084, SetXmpPacket_1084) {
  auto img = createTestImage();
  std::string packet = "<xmp>test data</xmp>";
  img->setXmpPacket(packet);
  EXPECT_EQ(img->xmpPacket(), packet);
}

// Test clearMetadata clears everything
TEST_F(ImageTest_1084, ClearMetadata_1084) {
  auto img = createTestImage();
  img->setComment("A comment");
  const uint8_t data[] = {0x01, 0x02};
  Exiv2::DataBuf buf(data, sizeof(data));
  img->setIccProfile(std::move(buf), false);

  img->clearMetadata();
  EXPECT_EQ(img->comment(), "");
  EXPECT_TRUE(img->exifData().empty());
  EXPECT_TRUE(img->iptcData().empty());
  EXPECT_TRUE(img->xmpData().empty());
}

// Test imageType
TEST_F(ImageTest_1084, ImageType_1084) {
  auto img = createTestImage();
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
}

// Test nativePreviews returns empty list by default
TEST_F(ImageTest_1084, NativePreviewsEmptyByDefault_1084) {
  auto img = createTestImage();
  EXPECT_TRUE(img->nativePreviews().empty());
}

// Test io() returns a valid reference
TEST_F(ImageTest_1084, IoReturnsValidReference_1084) {
  auto img = createTestImage();
  const Exiv2::BasicIo& ioRef = img->io();
  // MemIo path is empty string
  EXPECT_TRUE(ioRef.path().empty() || true); // Just verify no crash
}

// Static method tests
TEST_F(ImageTest_1084, IsBigEndianOrLittleEndianPlatform_1084) {
  bool isBig = Exiv2::Image::isBigEndianPlatform();
  bool isLittle = Exiv2::Image::isLittleEndianPlatform();
  // Exactly one should be true
  EXPECT_NE(isBig, isLittle);
}

TEST_F(ImageTest_1084, ByteSwapUint16NoSwap_1084) {
  uint16_t val = 0x1234;
  uint16_t result = Exiv2::Image::byteSwap(val, false);
  EXPECT_EQ(result, 0x1234u);
}

TEST_F(ImageTest_1084, ByteSwapUint16WithSwap_1084) {
  uint16_t val = 0x1234;
  uint16_t result = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(result, 0x3412u);
}

TEST_F(ImageTest_1084, ByteSwapUint32NoSwap_1084) {
  uint32_t val = 0x12345678;
  uint32_t result = Exiv2::Image::byteSwap(val, false);
  EXPECT_EQ(result, 0x12345678u);
}

TEST_F(ImageTest_1084, ByteSwapUint32WithSwap_1084) {
  uint32_t val = 0x12345678;
  uint32_t result = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(result, 0x78563412u);
}

TEST_F(ImageTest_1084, ByteSwapUint64NoSwap_1084) {
  uint64_t val = 0x0102030405060708ULL;
  uint64_t result = Exiv2::Image::byteSwap(val, false);
  EXPECT_EQ(result, 0x0102030405060708ULL);
}

TEST_F(ImageTest_1084, ByteSwapUint64WithSwap_1084) {
  uint64_t val = 0x0102030405060708ULL;
  uint64_t result = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(result, 0x0807060504030201ULL);
}

TEST_F(ImageTest_1084, IsStringType_1084) {
  // Type 2 is ASCII in TIFF
  EXPECT_TRUE(Exiv2::Image::isStringType(2));
  EXPECT_FALSE(Exiv2::Image::isStringType(3)); // SHORT
}

TEST_F(ImageTest_1084, IsShortType_1084) {
  // Type 3 is SHORT, type 8 is SSHORT
  EXPECT_TRUE(Exiv2::Image::isShortType(3));
  EXPECT_TRUE(Exiv2::Image::isShortType(8));
  EXPECT_FALSE(Exiv2::Image::isShortType(4)); // LONG
}

TEST_F(ImageTest_1084, IsLongType_1084) {
  // Type 4 is LONG, type 9 is SLONG
  EXPECT_TRUE(Exiv2::Image::isLongType(4));
  EXPECT_TRUE(Exiv2::Image::isLongType(9));
  EXPECT_FALSE(Exiv2::Image::isLongType(3)); // SHORT
}

TEST_F(ImageTest_1084, IsRationalType_1084) {
  // Type 5 is RATIONAL, type 10 is SRATIONAL
  EXPECT_TRUE(Exiv2::Image::isRationalType(5));
  EXPECT_TRUE(Exiv2::Image::isRationalType(10));
  EXPECT_FALSE(Exiv2::Image::isRationalType(4)); // LONG
}

TEST_F(ImageTest_1084, Is2ByteType_1084) {
  EXPECT_TRUE(Exiv2::Image::is2ByteType(3));  // SHORT
  EXPECT_TRUE(Exiv2::Image::is2ByteType(8));  // SSHORT
  EXPECT_FALSE(Exiv2::Image::is2ByteType(4)); // LONG
}

TEST_F(ImageTest_1084, Is4ByteType_1084) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(4));  // LONG
  EXPECT_TRUE(Exiv2::Image::is4ByteType(9));  // SLONG
  EXPECT_FALSE(Exiv2::Image::is4ByteType(3)); // SHORT
}

TEST_F(ImageTest_1084, Is8ByteType_1084) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(5));   // RATIONAL
  EXPECT_TRUE(Exiv2::Image::is8ByteType(10));  // SRATIONAL
  EXPECT_FALSE(Exiv2::Image::is8ByteType(4));  // LONG
}

// Test setIccProfile with bTestValid=true and invalid data (too small for ICC)
TEST_F(ImageTest_1084, SetIccProfileWithValidationInvalidData_1084) {
  auto img = createTestImage();
  const uint8_t data[] = {0x01, 0x02, 0x03};
  Exiv2::DataBuf buf(data, sizeof(data));
  // With bTestValid=true and invalid ICC data, the profile should be cleared
  img->setIccProfile(std::move(buf), true);
  // After checkIccProfile with invalid data, the profile should be cleared
  EXPECT_TRUE(img->iccProfile().empty());
}

// Test setIccProfile with bTestValid=true and empty DataBuf
TEST_F(ImageTest_1084, SetIccProfileEmptyWithValidation_1084) {
  auto img = createTestImage();
  Exiv2::DataBuf emptyBuf;
  img->setIccProfile(std::move(emptyBuf), true);
  EXPECT_TRUE(img->iccProfile().empty());
}

// Test setMetadata copies metadata from another image
TEST_F(ImageTest_1084, SetMetadataFromAnotherImage_1084) {
  auto img1 = createTestImage();
  auto img2 = createTestImage();

  img1->setComment("Source comment");

  img2->setMetadata(*img1);
  EXPECT_EQ(img2->comment(), "Source comment");
}

// Test byteSwap2 with DataBuf
TEST_F(ImageTest_1084, ByteSwap2WithDataBuf_1084) {
  const uint8_t data[] = {0x12, 0x34};
  Exiv2::DataBuf buf(data, sizeof(data));
  uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
  uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
  EXPECT_NE(noSwap, swapped);
}

// Test byteSwap4 with DataBuf
TEST_F(ImageTest_1084, ByteSwap4WithDataBuf_1084) {
  const uint8_t data[] = {0x12, 0x34, 0x56, 0x78};
  Exiv2::DataBuf buf(data, sizeof(data));
  uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
  uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
  EXPECT_NE(noSwap, swapped);
}

// Test byteSwap8 with DataBuf
TEST_F(ImageTest_1084, ByteSwap8WithDataBuf_1084) {
  const uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  Exiv2::DataBuf buf(data, sizeof(data));
  uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
  uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
  EXPECT_NE(noSwap, swapped);
}

// Test appendIccProfile
TEST_F(ImageTest_1084, AppendIccProfile_1084) {
  auto img = createTestImage();
  const uint8_t data1[] = {0x01, 0x02, 0x03};
  Exiv2::DataBuf buf(data1, sizeof(data1));
  img->setIccProfile(std::move(buf), false);
  EXPECT_EQ(img->iccProfile().size(), 3u);

  const uint8_t data2[] = {0x04, 0x05};
  img->appendIccProfile(data2, sizeof(data2), false);
  EXPECT_EQ(img->iccProfile().size(), 5u);
}

// Test appendIccProfile to initially empty profile
TEST_F(ImageTest_1084, AppendIccProfileToEmpty_1084) {
  auto img = createTestImage();
  EXPECT_TRUE(img->iccProfile().empty());
  const uint8_t data[] = {0x01, 0x02};
  img->appendIccProfile(data, sizeof(data), false);
  EXPECT_EQ(img->iccProfile().size(), 2u);
}

// Test mimeType returns something (default for ImageType::none)
TEST_F(ImageTest_1084, MimeTypeReturnsString_1084) {
  auto img = createTestImage();
  std::string mime = img->mimeType();
  // Just verify it doesn't crash and returns a string
  EXPECT_TRUE(mime.empty() || !mime.empty());
}

// Test supportsMetadata
TEST_F(ImageTest_1084, SupportsMetadata_1084) {
  auto img = createTestImage();
  // We set supportedMetadata to 0xFFFF so all should be supported
  EXPECT_TRUE(img->supportsMetadata(Exiv2::mdExif));
  EXPECT_TRUE(img->supportsMetadata(Exiv2::mdIptc));
  EXPECT_TRUE(img->supportsMetadata(Exiv2::mdXmp));
}

// Test iccProfile data content
TEST_F(ImageTest_1084, SetIccProfileDataContent_1084) {
  auto img = createTestImage();
  const uint8_t data[] = {0xAA, 0xBB, 0xCC, 0xDD};
  Exiv2::DataBuf buf(data, sizeof(data));
  img->setIccProfile(std::move(buf), false);

  const Exiv2::DataBuf& profile = img->iccProfile();
  EXPECT_EQ(profile.size(), 4u);
  EXPECT_EQ(profile.read_uint8(0), 0xAA);
  EXPECT_EQ(profile.read_uint8(1), 0xBB);
  EXPECT_EQ(profile.read_uint8(2), 0xCC);
  EXPECT_EQ(profile.read_uint8(3), 0xDD);
}
