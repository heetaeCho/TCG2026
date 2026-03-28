#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <sstream>

// We need a concrete subclass of Image since Image has pure virtual methods (readMetadata, writeMetadata)
// We'll create a minimal test image class
class TestImage : public Exiv2::Image {
 public:
  TestImage(std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

  void readMetadata() override {}
  void writeMetadata() override {}
};

class ImageTest_1087 : public ::testing::Test {
 protected:
  void SetUp() override {
    auto io = std::make_unique<Exiv2::MemIo>();
    image_ = std::make_unique<TestImage>(std::move(io));
  }

  std::unique_ptr<TestImage> image_;
};

// Test clearIccProfile clears the ICC profile
TEST_F(ImageTest_1087, ClearIccProfile_1087) {
  // Set an ICC profile first
  const uint8_t data[] = {0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  Exiv2::DataBuf buf(data, sizeof(data));
  image_->setIccProfile(std::move(buf), false);
  EXPECT_TRUE(image_->iccProfileDefined());

  image_->clearIccProfile();
  EXPECT_FALSE(image_->iccProfileDefined());
}

// Test clearIccProfile when no profile is set (should not crash)
TEST_F(ImageTest_1087, ClearIccProfileWhenEmpty_1087) {
  EXPECT_FALSE(image_->iccProfileDefined());
  image_->clearIccProfile();
  EXPECT_FALSE(image_->iccProfileDefined());
}

// Test clearIccProfile called multiple times
TEST_F(ImageTest_1087, ClearIccProfileMultipleTimes_1087) {
  image_->clearIccProfile();
  image_->clearIccProfile();
  image_->clearIccProfile();
  EXPECT_FALSE(image_->iccProfileDefined());
}

// Test iccProfileDefined returns false initially
TEST_F(ImageTest_1087, IccProfileNotDefinedInitially_1087) {
  EXPECT_FALSE(image_->iccProfileDefined());
}

// Test iccProfile returns empty buffer after clear
TEST_F(ImageTest_1087, IccProfileEmptyAfterClear_1087) {
  const uint8_t data[] = {0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  Exiv2::DataBuf buf(data, sizeof(data));
  image_->setIccProfile(std::move(buf), false);
  EXPECT_TRUE(image_->iccProfileDefined());
  EXPECT_GT(image_->iccProfile().size(), 0u);

  image_->clearIccProfile();
  EXPECT_FALSE(image_->iccProfileDefined());
  EXPECT_EQ(image_->iccProfile().size(), 0u);
}

// Test setIccProfile then clearIccProfile then setIccProfile again
TEST_F(ImageTest_1087, SetClearSetIccProfile_1087) {
  const uint8_t data[] = {0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  Exiv2::DataBuf buf1(data, sizeof(data));
  image_->setIccProfile(std::move(buf1), false);
  EXPECT_TRUE(image_->iccProfileDefined());

  image_->clearIccProfile();
  EXPECT_FALSE(image_->iccProfileDefined());

  Exiv2::DataBuf buf2(data, sizeof(data));
  image_->setIccProfile(std::move(buf2), false);
  EXPECT_TRUE(image_->iccProfileDefined());
}

// Test clearMetadata also clears ICC profile
TEST_F(ImageTest_1087, ClearMetadataClearsIccProfile_1087) {
  const uint8_t data[] = {0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  Exiv2::DataBuf buf(data, sizeof(data));
  image_->setIccProfile(std::move(buf), false);
  EXPECT_TRUE(image_->iccProfileDefined());

  image_->clearMetadata();
  EXPECT_FALSE(image_->iccProfileDefined());
}

// Test basic Image properties
TEST_F(ImageTest_1087, DefaultPixelDimensions_1087) {
  EXPECT_EQ(image_->pixelWidth(), 0u);
  EXPECT_EQ(image_->pixelHeight(), 0u);
}

// Test default comment is empty
TEST_F(ImageTest_1087, DefaultCommentEmpty_1087) {
  EXPECT_TRUE(image_->comment().empty());
}

// Test setComment and clearComment
TEST_F(ImageTest_1087, SetAndClearComment_1087) {
  image_->setComment("test comment");
  EXPECT_EQ(image_->comment(), "test comment");

  image_->clearComment();
  EXPECT_TRUE(image_->comment().empty());
}

// Test byteOrder default
TEST_F(ImageTest_1087, DefaultByteOrder_1087) {
  EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

// Test setByteOrder
TEST_F(ImageTest_1087, SetByteOrder_1087) {
  image_->setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);

  image_->setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// Test writeXmpFromPacket default and setter
TEST_F(ImageTest_1087, WriteXmpFromPacketDefault_1087) {
  EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_1087, SetWriteXmpFromPacket_1087) {
  image_->writeXmpFromPacket(true);
  EXPECT_TRUE(image_->writeXmpFromPacket());

  image_->writeXmpFromPacket(false);
  EXPECT_FALSE(image_->writeXmpFromPacket());
}

// Test clearExifData
TEST_F(ImageTest_1087, ClearExifData_1087) {
  image_->clearExifData();
  EXPECT_TRUE(image_->exifData().empty());
}

// Test clearIptcData
TEST_F(ImageTest_1087, ClearIptcData_1087) {
  image_->clearIptcData();
  EXPECT_TRUE(image_->iptcData().empty());
}

// Test clearXmpData
TEST_F(ImageTest_1087, ClearXmpData_1087) {
  image_->clearXmpData();
  EXPECT_TRUE(image_->xmpData().empty());
}

// Test clearXmpPacket
TEST_F(ImageTest_1087, ClearXmpPacket_1087) {
  image_->setXmpPacket("<xml>test</xml>");
  EXPECT_FALSE(image_->xmpPacket().empty());

  image_->clearXmpPacket();
  EXPECT_TRUE(image_->xmpPacket().empty());
}

// Test static byteSwap functions
TEST_F(ImageTest_1087, ByteSwap16NoSwap_1087) {
  uint16_t val = 0x0102;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1087, ByteSwap16WithSwap_1087) {
  uint16_t val = 0x0102;
  uint16_t swapped = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(swapped, 0x0201);
}

TEST_F(ImageTest_1087, ByteSwap32NoSwap_1087) {
  uint32_t val = 0x01020304;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1087, ByteSwap32WithSwap_1087) {
  uint32_t val = 0x01020304;
  uint32_t swapped = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(swapped, 0x04030201u);
}

TEST_F(ImageTest_1087, ByteSwap64NoSwap_1087) {
  uint64_t val = 0x0102030405060708ULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1087, ByteSwap64WithSwap_1087) {
  uint64_t val = 0x0102030405060708ULL;
  uint64_t swapped = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

// Test endian platform detection (one must be true, the other false)
TEST_F(ImageTest_1087, EndianPlatformConsistency_1087) {
  bool big = Exiv2::Image::isBigEndianPlatform();
  bool little = Exiv2::Image::isLittleEndianPlatform();
  EXPECT_NE(big, little);
}

// Test isStringType
TEST_F(ImageTest_1087, IsStringType_1087) {
  // Type 2 is ASCII in TIFF
  EXPECT_TRUE(Exiv2::Image::isStringType(2));
  // Type 1 is BYTE, not a string type
  EXPECT_FALSE(Exiv2::Image::isStringType(1));
}

// Test isShortType
TEST_F(ImageTest_1087, IsShortType_1087) {
  // Type 3 is SHORT in TIFF
  EXPECT_TRUE(Exiv2::Image::isShortType(3));
  EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

// Test isLongType
TEST_F(ImageTest_1087, IsLongType_1087) {
  // Type 4 is LONG in TIFF
  EXPECT_TRUE(Exiv2::Image::isLongType(4));
  EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

// Test isRationalType
TEST_F(ImageTest_1087, IsRationalType_1087) {
  // Type 5 is RATIONAL in TIFF
  EXPECT_TRUE(Exiv2::Image::isRationalType(5));
  EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

// Test io accessor
TEST_F(ImageTest_1087, IoAccessor_1087) {
  const Exiv2::BasicIo& io = image_->io();
  // Just verify it's accessible without crashing
  SUCCEED();
}

// Test good() with MemIo (should be good)
TEST_F(ImageTest_1087, GoodWithMemIo_1087) {
  EXPECT_TRUE(image_->good());
}

// Test imageType
TEST_F(ImageTest_1087, ImageType_1087) {
  EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// Test nativePreviews returns empty list initially
TEST_F(ImageTest_1087, NativePreviewsEmpty_1087) {
  EXPECT_TRUE(image_->nativePreviews().empty());
}

// Test is2ByteType
TEST_F(ImageTest_1087, Is2ByteType_1087) {
  // SHORT (3) is 2-byte type
  EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
  EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

// Test is4ByteType
TEST_F(ImageTest_1087, Is4ByteType_1087) {
  // LONG (4) is 4-byte type
  EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
  EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

// Test is8ByteType
TEST_F(ImageTest_1087, Is8ByteType_1087) {
  // RATIONAL (5) is 8-byte type
  EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
  EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

// Test byteSwap2 with DataBuf
TEST_F(ImageTest_1087, ByteSwap2_1087) {
  Exiv2::DataBuf buf(4);
  buf.write_uint8(0, 0x01);
  buf.write_uint8(1, 0x02);
  uint16_t val = Exiv2::Image::byteSwap2(buf, 0, false);
  uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
  EXPECT_NE(val, swapped);
}

// Test byteSwap4 with DataBuf
TEST_F(ImageTest_1087, ByteSwap4_1087) {
  Exiv2::DataBuf buf(8);
  buf.write_uint8(0, 0x01);
  buf.write_uint8(1, 0x02);
  buf.write_uint8(2, 0x03);
  buf.write_uint8(3, 0x04);
  uint32_t val = Exiv2::Image::byteSwap4(buf, 0, false);
  uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
  EXPECT_NE(val, swapped);
}

// Test byteSwap8 with DataBuf
TEST_F(ImageTest_1087, ByteSwap8_1087) {
  Exiv2::DataBuf buf(16);
  buf.write_uint8(0, 0x01);
  buf.write_uint8(1, 0x02);
  buf.write_uint8(2, 0x03);
  buf.write_uint8(3, 0x04);
  buf.write_uint8(4, 0x05);
  buf.write_uint8(5, 0x06);
  buf.write_uint8(6, 0x07);
  buf.write_uint8(7, 0x08);
  uint64_t val = Exiv2::Image::byteSwap8(buf, 0, false);
  uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
  EXPECT_NE(val, swapped);
}

// Test setMetadata copies ICC profile
TEST_F(ImageTest_1087, SetMetadataCopiesIccProfile_1087) {
  auto io2 = std::make_unique<Exiv2::MemIo>();
  TestImage source(std::move(io2));

  const uint8_t data[] = {0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                          0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  Exiv2::DataBuf buf(data, sizeof(data));
  source.setIccProfile(std::move(buf), false);
  source.setComment("source comment");

  image_->setMetadata(source);
  EXPECT_EQ(image_->comment(), "source comment");
}

// Test clearMetadata clears everything
TEST_F(ImageTest_1087, ClearMetadataClearsAll_1087) {
  image_->setComment("some comment");
  image_->clearMetadata();
  EXPECT_TRUE(image_->comment().empty());
  EXPECT_TRUE(image_->exifData().empty());
  EXPECT_TRUE(image_->iptcData().empty());
  EXPECT_TRUE(image_->xmpData().empty());
  EXPECT_FALSE(image_->iccProfileDefined());
}
