#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <memory>
#include <sstream>

// We need a concrete subclass of Image since Image has pure virtual methods
// (readMetadata, writeMetadata) and is abstract. We create a minimal test subclass.
namespace {

class TestImage : public Exiv2::Image {
 public:
  TestImage(std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(Exiv2::ImageType::none, static_cast<uint16_t>(0xFFFF), std::move(io)) {}

  TestImage(Exiv2::ImageType type, uint16_t supportedMetadata, std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

  void readMetadata() override {}
  void writeMetadata() override {}
};

std::unique_ptr<Exiv2::BasicIo> createMemIo() {
  return std::make_unique<Exiv2::MemIo>();
}

}  // namespace

class ImageTest_54 : public ::testing::Test {
 protected:
  std::unique_ptr<TestImage> createTestImage() {
    return std::make_unique<TestImage>(createMemIo());
  }

  std::unique_ptr<TestImage> createTestImage(Exiv2::ImageType type, uint16_t supported) {
    return std::make_unique<TestImage>(type, supported, createMemIo());
  }
};

// --- iccProfileDefined tests ---

TEST_F(ImageTest_54, IccProfileNotDefinedByDefault_54) {
  auto img = createTestImage();
  EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageTest_54, IccProfileDefinedAfterSet_54) {
  auto img = createTestImage();
  // Create a minimal valid ICC profile (at least non-empty)
  // ICC profile header is 128 bytes minimum, but we pass bTestValid=false
  uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::DataBuf buf(data, sizeof(data));
  img->setIccProfile(std::move(buf), false);
  EXPECT_TRUE(img->iccProfileDefined());
}

TEST_F(ImageTest_54, IccProfileNotDefinedAfterClear_54) {
  auto img = createTestImage();
  uint8_t data[] = {0x01, 0x02, 0x03, 0x04};
  Exiv2::DataBuf buf(data, sizeof(data));
  img->setIccProfile(std::move(buf), false);
  EXPECT_TRUE(img->iccProfileDefined());
  img->clearIccProfile();
  EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageTest_54, IccProfileReturnsDataAfterSet_54) {
  auto img = createTestImage();
  uint8_t data[] = {0xAA, 0xBB, 0xCC, 0xDD};
  Exiv2::DataBuf buf(data, sizeof(data));
  img->setIccProfile(std::move(buf), false);
  const Exiv2::DataBuf& profile = img->iccProfile();
  EXPECT_EQ(profile.size(), 4u);
}

// --- Comment tests ---

TEST_F(ImageTest_54, CommentEmptyByDefault_54) {
  auto img = createTestImage();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_54, SetAndGetComment_54) {
  auto img = createTestImage();
  img->setComment("Hello World");
  EXPECT_EQ(img->comment(), "Hello World");
}

TEST_F(ImageTest_54, ClearComment_54) {
  auto img = createTestImage();
  img->setComment("test comment");
  EXPECT_EQ(img->comment(), "test comment");
  img->clearComment();
  EXPECT_TRUE(img->comment().empty());
}

// --- PixelWidth / PixelHeight tests ---

TEST_F(ImageTest_54, PixelWidthDefaultZero_54) {
  auto img = createTestImage();
  EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(ImageTest_54, PixelHeightDefaultZero_54) {
  auto img = createTestImage();
  EXPECT_EQ(img->pixelHeight(), 0u);
}

// --- ByteOrder tests ---

TEST_F(ImageTest_54, ByteOrderDefaultInvalid_54) {
  auto img = createTestImage();
  EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_54, SetByteOrderBigEndian_54) {
  auto img = createTestImage();
  img->setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_54, SetByteOrderLittleEndian_54) {
  auto img = createTestImage();
  img->setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

// --- writeXmpFromPacket tests ---

TEST_F(ImageTest_54, WriteXmpFromPacketDefaultFalse_54) {
  auto img = createTestImage();
  EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_54, SetWriteXmpFromPacketTrue_54) {
  auto img = createTestImage();
  img->writeXmpFromPacket(true);
  EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_54, SetWriteXmpFromPacketFalse_54) {
  auto img = createTestImage();
  img->writeXmpFromPacket(true);
  img->writeXmpFromPacket(false);
  EXPECT_FALSE(img->writeXmpFromPacket());
}

// --- ExifData tests ---

TEST_F(ImageTest_54, ExifDataAccessible_54) {
  auto img = createTestImage();
  Exiv2::ExifData& exif = img->exifData();
  // Default should be empty
  EXPECT_TRUE(exif.empty());
}

TEST_F(ImageTest_54, ClearExifData_54) {
  auto img = createTestImage();
  img->clearExifData();
  EXPECT_TRUE(img->exifData().empty());
}

// --- IptcData tests ---

TEST_F(ImageTest_54, IptcDataAccessible_54) {
  auto img = createTestImage();
  Exiv2::IptcData& iptc = img->iptcData();
  EXPECT_TRUE(iptc.empty());
}

TEST_F(ImageTest_54, ClearIptcData_54) {
  auto img = createTestImage();
  img->clearIptcData();
  EXPECT_TRUE(img->iptcData().empty());
}

// --- XmpData tests ---

TEST_F(ImageTest_54, XmpDataAccessible_54) {
  auto img = createTestImage();
  Exiv2::XmpData& xmp = img->xmpData();
  EXPECT_TRUE(xmp.empty());
}

TEST_F(ImageTest_54, ClearXmpData_54) {
  auto img = createTestImage();
  img->clearXmpData();
  EXPECT_TRUE(img->xmpData().empty());
}

// --- XmpPacket tests ---

TEST_F(ImageTest_54, XmpPacketEmptyByDefault_54) {
  auto img = createTestImage();
  EXPECT_TRUE(img->xmpPacket().empty());
}

TEST_F(ImageTest_54, SetXmpPacket_54) {
  auto img = createTestImage();
  std::string packet = "<x:xmpmeta>test</x:xmpmeta>";
  img->setXmpPacket(packet);
  EXPECT_EQ(img->xmpPacket(), packet);
}

TEST_F(ImageTest_54, ClearXmpPacket_54) {
  auto img = createTestImage();
  img->setXmpPacket("some packet");
  img->clearXmpPacket();
  EXPECT_TRUE(img->xmpPacket().empty());
}

// --- clearMetadata tests ---

TEST_F(ImageTest_54, ClearMetadataClearsAll_54) {
  auto img = createTestImage();
  img->setComment("a comment");
  img->setXmpPacket("xmp data");
  img->clearMetadata();
  EXPECT_TRUE(img->comment().empty());
  EXPECT_TRUE(img->exifData().empty());
  EXPECT_TRUE(img->iptcData().empty());
  EXPECT_TRUE(img->xmpData().empty());
  EXPECT_TRUE(img->xmpPacket().empty());
  EXPECT_FALSE(img->iccProfileDefined());
}

// --- good tests ---

TEST_F(ImageTest_54, GoodReturnsTrueForMemIo_54) {
  auto img = createTestImage();
  // MemIo with no data should still be "good" (open state)
  // The actual behavior depends on BasicIo::isopen() && !BasicIo::error()
  // For MemIo, this should be true
  EXPECT_TRUE(img->good());
}

// --- io tests ---

TEST_F(ImageTest_54, IoAccessible_54) {
  auto img = createTestImage();
  const Exiv2::BasicIo& io = img->io();
  // Just verify we can access it without crashing
  EXPECT_GE(io.size(), 0u);
}

// --- nativePreviews tests ---

TEST_F(ImageTest_54, NativePreviewsEmptyByDefault_54) {
  auto img = createTestImage();
  EXPECT_TRUE(img->nativePreviews().empty());
}

// --- imageType tests ---

TEST_F(ImageTest_54, ImageTypeReturnsConstructedType_54) {
  auto img = createTestImage(Exiv2::ImageType::none, 0xFFFF);
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
}

// --- setMetadata tests ---

TEST_F(ImageTest_54, SetMetadataCopiesFromAnotherImage_54) {
  auto src = createTestImage();
  src->setComment("source comment");

  auto dst = createTestImage();
  dst->setMetadata(*src);
  EXPECT_EQ(dst->comment(), "source comment");
}

// --- Static method tests ---

TEST_F(ImageTest_54, IsBigEndianOrLittleEndian_54) {
  // One of these must be true
  bool big = Exiv2::Image::isBigEndianPlatform();
  bool little = Exiv2::Image::isLittleEndianPlatform();
  EXPECT_TRUE(big || little);
  EXPECT_NE(big, little);
}

TEST_F(ImageTest_54, ByteSwapUint16NoSwap_54) {
  uint16_t val = 0x1234;
  uint16_t result = Exiv2::Image::byteSwap(val, false);
  EXPECT_EQ(result, val);
}

TEST_F(ImageTest_54, ByteSwapUint16Swap_54) {
  uint16_t val = 0x1234;
  uint16_t result = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(result, 0x3412);
}

TEST_F(ImageTest_54, ByteSwapUint32NoSwap_54) {
  uint32_t val = 0x12345678;
  uint32_t result = Exiv2::Image::byteSwap(val, false);
  EXPECT_EQ(result, val);
}

TEST_F(ImageTest_54, ByteSwapUint32Swap_54) {
  uint32_t val = 0x12345678;
  uint32_t result = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(result, 0x78563412u);
}

TEST_F(ImageTest_54, ByteSwapUint64NoSwap_54) {
  uint64_t val = 0x123456789ABCDEF0ULL;
  uint64_t result = Exiv2::Image::byteSwap(val, false);
  EXPECT_EQ(result, val);
}

TEST_F(ImageTest_54, ByteSwapUint64Swap_54) {
  uint64_t val = 0x123456789ABCDEF0ULL;
  uint64_t result = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(result, 0xF0DEBC9A78563412ULL);
}

// --- isStringType / isShortType / isLongType etc. static tests ---

TEST_F(ImageTest_54, IsStringTypeForAscii_54) {
  // TIFF type 2 is ASCII
  EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_54, IsStringTypeForNonString_54) {
  // TIFF type 3 is SHORT, not string
  EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

TEST_F(ImageTest_54, IsShortTypeForShort_54) {
  // TIFF type 3 is SHORT
  EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageTest_54, IsShortTypeForNonShort_54) {
  EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

TEST_F(ImageTest_54, IsLongTypeForLong_54) {
  // TIFF type 4 is LONG
  EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageTest_54, IsRationalTypeForRational_54) {
  // TIFF type 5 is RATIONAL
  EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageTest_54, Is2ByteTypeForShort_54) {
  EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
}

TEST_F(ImageTest_54, Is4ByteTypeForLong_54) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
}

TEST_F(ImageTest_54, Is8ByteTypeForRational_54) {
  // RATIONAL is 8 bytes (two LONGs)
  EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
}

// --- ByteSwap2/4/8 with DataBuf ---

TEST_F(ImageTest_54, ByteSwap2NoSwap_54) {
  uint8_t data[] = {0x12, 0x34};
  Exiv2::DataBuf buf(data, sizeof(data));
  uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
  // No swap: should read bytes as-is in native representation
  uint16_t expected;
  std::memcpy(&expected, data, 2);
  EXPECT_EQ(result, expected);
}

TEST_F(ImageTest_54, ByteSwap4NoSwap_54) {
  uint8_t data[] = {0x12, 0x34, 0x56, 0x78};
  Exiv2::DataBuf buf(data, sizeof(data));
  uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
  uint32_t expected;
  std::memcpy(&expected, data, 4);
  EXPECT_EQ(result, expected);
}

// --- appendIccProfile tests ---

TEST_F(ImageTest_54, AppendIccProfileToEmpty_54) {
  auto img = createTestImage();
  uint8_t data[] = {0x01, 0x02, 0x03};
  img->appendIccProfile(data, sizeof(data), false);
  EXPECT_TRUE(img->iccProfileDefined());
  EXPECT_EQ(img->iccProfile().size(), 3u);
}

TEST_F(ImageTest_54, AppendIccProfileMultipleTimes_54) {
  auto img = createTestImage();
  uint8_t data1[] = {0x01, 0x02};
  uint8_t data2[] = {0x03, 0x04, 0x05};
  img->appendIccProfile(data1, sizeof(data1), false);
  img->appendIccProfile(data2, sizeof(data2), false);
  EXPECT_TRUE(img->iccProfileDefined());
  EXPECT_EQ(img->iccProfile().size(), 5u);
}

// --- setTypeSupported tests ---

TEST_F(ImageTest_54, SetTypeSupportedChangesType_54) {
  auto img = createTestImage(Exiv2::ImageType::none, 0);
  img->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::jpeg);
}

// --- mimeType test ---

TEST_F(ImageTest_54, MimeTypeReturnsNonEmpty_54) {
  auto img = createTestImage();
  // Default mimeType for base Image should return something
  std::string mime = img->mimeType();
  // Just check it doesn't crash; the actual value depends on implementation
  EXPECT_FALSE(mime.empty());
}

// --- setIccProfile with empty buffer ---

TEST_F(ImageTest_54, SetEmptyIccProfile_54) {
  auto img = createTestImage();
  Exiv2::DataBuf emptyBuf;
  img->setIccProfile(std::move(emptyBuf), false);
  EXPECT_FALSE(img->iccProfileDefined());
}
