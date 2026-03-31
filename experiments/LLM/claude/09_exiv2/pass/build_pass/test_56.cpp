#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/exiv2.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <memory>

// A concrete subclass of Image for testing purposes, since Image has pure virtual methods
class TestImage : public Exiv2::Image {
public:
  TestImage(Exiv2::ImageType type, uint16_t supportedMetadata, std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

  void readMetadata() override {}
  void writeMetadata() override {}
  std::string mimeType() const override { return "application/test"; }
};

class ImageTest_56 : public ::testing::Test {
protected:
  std::unique_ptr<TestImage> createTestImage(
      Exiv2::ImageType type = Exiv2::ImageType::none,
      uint16_t supportedMetadata = 0) {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(type, supportedMetadata, std::move(io));
  }
};

// ============ setTypeSupported / imageType tests ============

TEST_F(ImageTest_56, SetTypeSupportedChangesImageType_56) {
  auto img = createTestImage(Exiv2::ImageType::none, 0);
  img->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::jpeg);
}

TEST_F(ImageTest_56, ImageTypeReturnsInitialType_56) {
  auto img = createTestImage(Exiv2::ImageType::png, 0);
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::png);
}

// ============ ByteOrder tests ============

TEST_F(ImageTest_56, DefaultByteOrderIsInvalid_56) {
  auto img = createTestImage();
  EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_56, SetByteOrderBigEndian_56) {
  auto img = createTestImage();
  img->setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_56, SetByteOrderLittleEndian_56) {
  auto img = createTestImage();
  img->setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

// ============ Comment tests ============

TEST_F(ImageTest_56, DefaultCommentIsEmpty_56) {
  auto img = createTestImage();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_56, SetCommentStoresComment_56) {
  auto img = createTestImage();
  img->setComment("Hello World");
  EXPECT_EQ(img->comment(), "Hello World");
}

TEST_F(ImageTest_56, ClearCommentRemovesComment_56) {
  auto img = createTestImage();
  img->setComment("test comment");
  img->clearComment();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_56, SetCommentEmptyString_56) {
  auto img = createTestImage();
  img->setComment("");
  EXPECT_TRUE(img->comment().empty());
}

// ============ ExifData tests ============

TEST_F(ImageTest_56, ExifDataInitiallyEmpty_56) {
  auto img = createTestImage();
  EXPECT_TRUE(img->exifData().empty());
}

TEST_F(ImageTest_56, SetExifDataAndRetrieve_56) {
  auto img = createTestImage();
  Exiv2::ExifData exifData;
  exifData["Exif.Image.Make"] = "TestMake";
  img->setExifData(exifData);
  EXPECT_FALSE(img->exifData().empty());
}

TEST_F(ImageTest_56, ClearExifData_56) {
  auto img = createTestImage();
  Exiv2::ExifData exifData;
  exifData["Exif.Image.Make"] = "TestMake";
  img->setExifData(exifData);
  img->clearExifData();
  EXPECT_TRUE(img->exifData().empty());
}

// ============ IptcData tests ============

TEST_F(ImageTest_56, IptcDataInitiallyEmpty_56) {
  auto img = createTestImage();
  EXPECT_TRUE(img->iptcData().empty());
}

TEST_F(ImageTest_56, SetIptcDataAndRetrieve_56) {
  auto img = createTestImage();
  Exiv2::IptcData iptcData;
  iptcData["Iptc.Application2.Caption"] = "Test Caption";
  img->setIptcData(iptcData);
  EXPECT_FALSE(img->iptcData().empty());
}

TEST_F(ImageTest_56, ClearIptcData_56) {
  auto img = createTestImage();
  Exiv2::IptcData iptcData;
  iptcData["Iptc.Application2.Caption"] = "Test Caption";
  img->setIptcData(iptcData);
  img->clearIptcData();
  EXPECT_TRUE(img->iptcData().empty());
}

// ============ XmpData tests ============

TEST_F(ImageTest_56, XmpDataInitiallyEmpty_56) {
  auto img = createTestImage();
  EXPECT_TRUE(img->xmpData().empty());
}

TEST_F(ImageTest_56, SetXmpDataAndRetrieve_56) {
  auto img = createTestImage();
  Exiv2::XmpData xmpData;
  xmpData["Xmp.dc.title"] = "Test Title";
  img->setXmpData(xmpData);
  EXPECT_FALSE(img->xmpData().empty());
}

TEST_F(ImageTest_56, ClearXmpData_56) {
  auto img = createTestImage();
  Exiv2::XmpData xmpData;
  xmpData["Xmp.dc.title"] = "Test Title";
  img->setXmpData(xmpData);
  img->clearXmpData();
  EXPECT_TRUE(img->xmpData().empty());
}

// ============ XmpPacket tests ============

TEST_F(ImageTest_56, XmpPacketInitiallyEmpty_56) {
  auto img = createTestImage();
  EXPECT_TRUE(img->xmpPacket().empty());
}

TEST_F(ImageTest_56, SetXmpPacketAndRetrieve_56) {
  auto img = createTestImage();
  img->setXmpPacket("<xmp>test</xmp>");
  EXPECT_EQ(img->xmpPacket(), "<xmp>test</xmp>");
}

TEST_F(ImageTest_56, ClearXmpPacket_56) {
  auto img = createTestImage();
  img->setXmpPacket("<xmp>test</xmp>");
  img->clearXmpPacket();
  EXPECT_TRUE(img->xmpPacket().empty());
}

// ============ writeXmpFromPacket tests ============

TEST_F(ImageTest_56, WriteXmpFromPacketDefaultFalse_56) {
  auto img = createTestImage();
  EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_56, WriteXmpFromPacketSetTrue_56) {
  auto img = createTestImage();
  img->writeXmpFromPacket(true);
  EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_56, WriteXmpFromPacketSetFalse_56) {
  auto img = createTestImage();
  img->writeXmpFromPacket(true);
  img->writeXmpFromPacket(false);
  EXPECT_FALSE(img->writeXmpFromPacket());
}

// ============ ICC Profile tests ============

TEST_F(ImageTest_56, IccProfileInitiallyNotDefined_56) {
  auto img = createTestImage();
  EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageTest_56, SetIccProfileDefinesProfile_56) {
  auto img = createTestImage();
  // Create a minimal ICC profile-like data buffer
  // ICC profile header is 128 bytes minimum, with specific signature
  Exiv2::DataBuf buf(256);
  std::memset(buf.data(), 0, buf.size());
  // Set profile size at offset 0 (big-endian uint32)
  buf.data()[0] = 0;
  buf.data()[1] = 0;
  buf.data()[2] = 1;
  buf.data()[3] = 0; // size = 256
  // Set signature "acsp" at offset 36
  buf.data()[36] = 'a';
  buf.data()[37] = 'c';
  buf.data()[38] = 's';
  buf.data()[39] = 'p';
  img->setIccProfile(std::move(buf), false);
  EXPECT_TRUE(img->iccProfileDefined());
}

TEST_F(ImageTest_56, ClearIccProfileUndifinesProfile_56) {
  auto img = createTestImage();
  Exiv2::DataBuf buf(256);
  std::memset(buf.data(), 0, buf.size());
  img->setIccProfile(std::move(buf), false);
  img->clearIccProfile();
  EXPECT_FALSE(img->iccProfileDefined());
}

// ============ clearMetadata tests ============

TEST_F(ImageTest_56, ClearMetadataClearsAll_56) {
  auto img = createTestImage();
  img->setComment("test");
  Exiv2::ExifData exifData;
  exifData["Exif.Image.Make"] = "TestMake";
  img->setExifData(exifData);
  Exiv2::IptcData iptcData;
  iptcData["Iptc.Application2.Caption"] = "Test";
  img->setIptcData(iptcData);

  img->clearMetadata();

  EXPECT_TRUE(img->comment().empty());
  EXPECT_TRUE(img->exifData().empty());
  EXPECT_TRUE(img->iptcData().empty());
  EXPECT_TRUE(img->xmpData().empty());
  EXPECT_TRUE(img->xmpPacket().empty());
}

// ============ setMetadata tests ============

TEST_F(ImageTest_56, SetMetadataCopiesFromAnotherImage_56) {
  auto src = createTestImage();
  src->setComment("source comment");
  Exiv2::ExifData exifData;
  exifData["Exif.Image.Make"] = "SourceMake";
  src->setExifData(exifData);

  auto dst = createTestImage();
  dst->setMetadata(*src);

  EXPECT_EQ(dst->comment(), "source comment");
  EXPECT_FALSE(dst->exifData().empty());
}

// ============ pixelWidth / pixelHeight tests ============

TEST_F(ImageTest_56, DefaultPixelWidthIsZero_56) {
  auto img = createTestImage();
  EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(ImageTest_56, DefaultPixelHeightIsZero_56) {
  auto img = createTestImage();
  EXPECT_EQ(img->pixelHeight(), 0u);
}

// ============ good() tests ============

TEST_F(ImageTest_56, GoodReflectsIoState_56) {
  auto img = createTestImage();
  // With a freshly created MemIo, good() should reflect the IO state
  // MemIo should be in good state
  EXPECT_TRUE(img->good());
}

// ============ nativePreviews tests ============

TEST_F(ImageTest_56, NativePreviewsInitiallyEmpty_56) {
  auto img = createTestImage();
  EXPECT_TRUE(img->nativePreviews().empty());
}

// ============ mimeType tests ============

TEST_F(ImageTest_56, MimeTypeReturnsExpected_56) {
  auto img = createTestImage();
  EXPECT_EQ(img->mimeType(), "application/test");
}

// ============ io() tests ============

TEST_F(ImageTest_56, IoReturnsValidReference_56) {
  auto img = createTestImage();
  const Exiv2::BasicIo& io = img->io();
  // Just verify we can access it without crashing
  (void)io;
  SUCCEED();
}

// ============ Static method tests ============

TEST_F(ImageTest_56, PlatformEndianness_56) {
  bool big = Exiv2::Image::isBigEndianPlatform();
  bool little = Exiv2::Image::isLittleEndianPlatform();
  // Exactly one should be true
  EXPECT_NE(big, little);
}

TEST_F(ImageTest_56, ByteSwap16NoSwap_56) {
  uint16_t val = 0x1234;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234);
}

TEST_F(ImageTest_56, ByteSwap16WithSwap_56) {
  uint16_t val = 0x1234;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412);
}

TEST_F(ImageTest_56, ByteSwap32NoSwap_56) {
  uint32_t val = 0x12345678;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST_F(ImageTest_56, ByteSwap32WithSwap_56) {
  uint32_t val = 0x12345678;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST_F(ImageTest_56, ByteSwap64NoSwap_56) {
  uint64_t val = 0x0102030405060708ULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_56, ByteSwap64WithSwap_56) {
  uint64_t val = 0x0102030405060708ULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

TEST_F(ImageTest_56, ByteSwap16Zero_56) {
  uint16_t val = 0;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0);
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0);
}

TEST_F(ImageTest_56, ByteSwap32Zero_56) {
  uint32_t val = 0;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0u);
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0u);
}

TEST_F(ImageTest_56, ByteSwap2FromBuf_56) {
  Exiv2::DataBuf buf(4);
  buf.data()[0] = 0x12;
  buf.data()[1] = 0x34;
  EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 0, false), 0x1234);
  EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 0, true), 0x3412);
}

TEST_F(ImageTest_56, ByteSwap4FromBuf_56) {
  Exiv2::DataBuf buf(8);
  buf.data()[0] = 0x12;
  buf.data()[1] = 0x34;
  buf.data()[2] = 0x56;
  buf.data()[3] = 0x78;
  EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 0, false), 0x12345678u);
  EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 0, true), 0x78563412u);
}

TEST_F(ImageTest_56, ByteSwap8FromBuf_56) {
  Exiv2::DataBuf buf(16);
  buf.data()[0] = 0x01;
  buf.data()[1] = 0x02;
  buf.data()[2] = 0x03;
  buf.data()[3] = 0x04;
  buf.data()[4] = 0x05;
  buf.data()[5] = 0x06;
  buf.data()[6] = 0x07;
  buf.data()[7] = 0x08;
  EXPECT_EQ(Exiv2::Image::byteSwap8(buf, 0, false), 0x0102030405060708ULL);
  EXPECT_EQ(Exiv2::Image::byteSwap8(buf, 0, true), 0x0807060504030201ULL);
}

// ============ isStringType tests ============

TEST_F(ImageTest_56, IsStringTypeForAscii_56) {
  // TIFF type 2 = ASCII
  EXPECT_TRUE(Exiv2::Image::isStringType(2));
}

TEST_F(ImageTest_56, IsStringTypeForNonString_56) {
  // TIFF type 3 = SHORT, should not be string
  EXPECT_FALSE(Exiv2::Image::isStringType(3));
}

// ============ isShortType tests ============

TEST_F(ImageTest_56, IsShortTypeForShort_56) {
  // TIFF type 3 = SHORT
  EXPECT_TRUE(Exiv2::Image::isShortType(3));
}

TEST_F(ImageTest_56, IsShortTypeForNonShort_56) {
  EXPECT_FALSE(Exiv2::Image::isShortType(2));
}

// ============ isLongType tests ============

TEST_F(ImageTest_56, IsLongTypeForLong_56) {
  // TIFF type 4 = LONG
  EXPECT_TRUE(Exiv2::Image::isLongType(4));
}

TEST_F(ImageTest_56, IsLongTypeForNonLong_56) {
  EXPECT_FALSE(Exiv2::Image::isLongType(2));
}

// ============ isRationalType tests ============

TEST_F(ImageTest_56, IsRationalTypeForRational_56) {
  // TIFF type 5 = RATIONAL
  EXPECT_TRUE(Exiv2::Image::isRationalType(5));
}

TEST_F(ImageTest_56, IsRationalTypeForNonRational_56) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(3));
}

// ============ is2ByteType tests ============

TEST_F(ImageTest_56, Is2ByteTypeForShort_56) {
  // SHORT (3) is 2-byte type
  EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
}

// ============ is4ByteType tests ============

TEST_F(ImageTest_56, Is4ByteTypeForLong_56) {
  // LONG (4) is 4-byte type
  EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
}

// ============ is8ByteType tests ============

TEST_F(ImageTest_56, Is8ByteTypeForRational_56) {
  // RATIONAL (5) is 8-byte type
  EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
}

// ============ ByteSwap boundary: max values ============

TEST_F(ImageTest_56, ByteSwap16MaxValue_56) {
  uint16_t val = 0xFFFF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFF);
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFF);
}

TEST_F(ImageTest_56, ByteSwap32MaxValue_56) {
  uint32_t val = 0xFFFFFFFF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFu);
}

TEST_F(ImageTest_56, ByteSwap64MaxValue_56) {
  uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFFFFFFFFFULL);
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFFFFFFFFFULL);
}

// ============ ByteSwap2 with offset ============

TEST_F(ImageTest_56, ByteSwap2WithOffset_56) {
  Exiv2::DataBuf buf(8);
  buf.data()[2] = 0xAB;
  buf.data()[3] = 0xCD;
  EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 2, false), 0xABCD);
  EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 2, true), 0xCDAB);
}

TEST_F(ImageTest_56, ByteSwap4WithOffset_56) {
  Exiv2::DataBuf buf(12);
  buf.data()[4] = 0xDE;
  buf.data()[5] = 0xAD;
  buf.data()[6] = 0xBE;
  buf.data()[7] = 0xEF;
  EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 4, false), 0xDEADBEEFu);
  EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 4, true), 0xEFBEADDEu);
}

// ============ supportsMetadata tests ============

TEST_F(ImageTest_56, SupportsMetadataReflectsSupportedFlag_56) {
  // Create with no metadata support
  auto img = createTestImage(Exiv2::ImageType::none, 0);
  EXPECT_FALSE(img->supportsMetadata(Exiv2::MetadataId::mdExif));
  EXPECT_FALSE(img->supportsMetadata(Exiv2::MetadataId::mdIptc));
  EXPECT_FALSE(img->supportsMetadata(Exiv2::MetadataId::mdXmp));
}

// ============ Multiple set/clear cycles ============

TEST_F(ImageTest_56, MultipleSetClearCyclesComment_56) {
  auto img = createTestImage();
  for (int i = 0; i < 5; ++i) {
    img->setComment("iteration " + std::to_string(i));
    EXPECT_EQ(img->comment(), "iteration " + std::to_string(i));
    img->clearComment();
    EXPECT_TRUE(img->comment().empty());
  }
}

TEST_F(ImageTest_56, SetTypeSupportedMultipleTimes_56) {
  auto img = createTestImage(Exiv2::ImageType::none, 0);
  img->setTypeSupported(Exiv2::ImageType::jpeg, 0x01);
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::jpeg);
  img->setTypeSupported(Exiv2::ImageType::png, 0x02);
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::png);
}
