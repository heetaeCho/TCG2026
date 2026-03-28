#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>

#include <memory>
#include <sstream>
#include <cstring>

// A concrete subclass of Image for testing purposes, since Image is abstract
// (readMetadata and writeMetadata are pure virtual or need implementation)
class TestImage : public Exiv2::Image {
 public:
  TestImage(std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

  TestImage(Exiv2::ImageType type, uint16_t supportedMetadata,
            std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(type, supportedMetadata, std::move(io)) {}

  void readMetadata() override {}
  void writeMetadata() override {}
};

static std::unique_ptr<Exiv2::BasicIo> makeMemIo() {
  return std::make_unique<Exiv2::MemIo>();
}

class ImageTest_55 : public ::testing::Test {
 protected:
  void SetUp() override {
    image_ = std::make_unique<TestImage>(makeMemIo());
  }

  std::unique_ptr<TestImage> image_;
};

// --- ICC Profile Tests ---

TEST_F(ImageTest_55, IccProfileInitiallyEmpty_55) {
  const Exiv2::DataBuf& profile = image_->iccProfile();
  EXPECT_EQ(profile.size(), 0u);
}

TEST_F(ImageTest_55, IccProfileDefinedReturnsFalseInitially_55) {
  EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageTest_55, SetIccProfileMakesItDefined_55) {
  // Create a minimal valid-ish ICC profile buffer (at least 132 bytes for header)
  Exiv2::DataBuf buf(132);
  std::memset(buf.data(), 0, 132);
  // Set profile size in big-endian at offset 0
  buf.data()[0] = 0;
  buf.data()[1] = 0;
  buf.data()[2] = 0;
  buf.data()[3] = 132;

  image_->setIccProfile(std::move(buf), false);
  EXPECT_TRUE(image_->iccProfileDefined());
  EXPECT_GT(image_->iccProfile().size(), 0u);
}

TEST_F(ImageTest_55, ClearIccProfile_55) {
  Exiv2::DataBuf buf(132);
  std::memset(buf.data(), 0, 132);
  image_->setIccProfile(std::move(buf), false);
  EXPECT_TRUE(image_->iccProfileDefined());

  image_->clearIccProfile();
  EXPECT_FALSE(image_->iccProfileDefined());
  EXPECT_EQ(image_->iccProfile().size(), 0u);
}

// --- Comment Tests ---

TEST_F(ImageTest_55, CommentInitiallyEmpty_55) {
  EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageTest_55, SetAndGetComment_55) {
  image_->setComment("Hello World");
  EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageTest_55, ClearComment_55) {
  image_->setComment("Test comment");
  image_->clearComment();
  EXPECT_TRUE(image_->comment().empty());
}

// --- ExifData Tests ---

TEST_F(ImageTest_55, ExifDataInitiallyEmpty_55) {
  EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageTest_55, SetExifData_55) {
  Exiv2::ExifData exifData;
  exifData["Exif.Image.Make"] = "TestMake";
  image_->setExifData(exifData);
  EXPECT_FALSE(image_->exifData().empty());
}

TEST_F(ImageTest_55, ClearExifData_55) {
  Exiv2::ExifData exifData;
  exifData["Exif.Image.Make"] = "TestMake";
  image_->setExifData(exifData);
  EXPECT_FALSE(image_->exifData().empty());

  image_->clearExifData();
  EXPECT_TRUE(image_->exifData().empty());
}

// --- IptcData Tests ---

TEST_F(ImageTest_55, IptcDataInitiallyEmpty_55) {
  EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageTest_55, SetIptcData_55) {
  Exiv2::IptcData iptcData;
  iptcData["Iptc.Application2.Caption"] = "Test caption";
  image_->setIptcData(iptcData);
  EXPECT_FALSE(image_->iptcData().empty());
}

TEST_F(ImageTest_55, ClearIptcData_55) {
  Exiv2::IptcData iptcData;
  iptcData["Iptc.Application2.Caption"] = "Test caption";
  image_->setIptcData(iptcData);
  image_->clearIptcData();
  EXPECT_TRUE(image_->iptcData().empty());
}

// --- XmpData Tests ---

TEST_F(ImageTest_55, XmpDataInitiallyEmpty_55) {
  EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageTest_55, SetXmpData_55) {
  Exiv2::XmpData xmpData;
  xmpData["Xmp.dc.title"] = "Test Title";
  image_->setXmpData(xmpData);
  EXPECT_FALSE(image_->xmpData().empty());
}

TEST_F(ImageTest_55, ClearXmpData_55) {
  Exiv2::XmpData xmpData;
  xmpData["Xmp.dc.title"] = "Test Title";
  image_->setXmpData(xmpData);
  image_->clearXmpData();
  EXPECT_TRUE(image_->xmpData().empty());
}

// --- XmpPacket Tests ---

TEST_F(ImageTest_55, XmpPacketInitiallyEmpty_55) {
  EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_55, SetXmpPacket_55) {
  image_->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
  EXPECT_FALSE(image_->xmpPacket().empty());
}

TEST_F(ImageTest_55, ClearXmpPacket_55) {
  image_->setXmpPacket("<x:xmpmeta>test</x:xmpmeta>");
  image_->clearXmpPacket();
  EXPECT_TRUE(image_->xmpPacket().empty());
}

// --- Pixel Dimensions Tests ---

TEST_F(ImageTest_55, PixelWidthInitiallyZero_55) {
  EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageTest_55, PixelHeightInitiallyZero_55) {
  EXPECT_EQ(image_->pixelHeight(), 0u);
}

// --- ByteOrder Tests ---

TEST_F(ImageTest_55, ByteOrderInitiallyInvalid_55) {
  EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_55, SetByteOrder_55) {
  image_->setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);

  image_->setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

// --- writeXmpFromPacket Tests ---

TEST_F(ImageTest_55, WriteXmpFromPacketInitiallyFalse_55) {
  EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageTest_55, SetWriteXmpFromPacket_55) {
  image_->writeXmpFromPacket(true);
  EXPECT_TRUE(image_->writeXmpFromPacket());

  image_->writeXmpFromPacket(false);
  EXPECT_FALSE(image_->writeXmpFromPacket());
}

// --- good() Tests ---

TEST_F(ImageTest_55, GoodReturnsTrueForMemIo_55) {
  // MemIo should be good by default
  EXPECT_TRUE(image_->good());
}

// --- clearMetadata Tests ---

TEST_F(ImageTest_55, ClearMetadataClearsAll_55) {
  // Set various metadata
  image_->setComment("Comment");
  Exiv2::ExifData exifData;
  exifData["Exif.Image.Make"] = "Test";
  image_->setExifData(exifData);
  Exiv2::IptcData iptcData;
  iptcData["Iptc.Application2.Caption"] = "Cap";
  image_->setIptcData(iptcData);

  image_->clearMetadata();

  EXPECT_TRUE(image_->comment().empty());
  EXPECT_TRUE(image_->exifData().empty());
  EXPECT_TRUE(image_->iptcData().empty());
  EXPECT_TRUE(image_->xmpData().empty());
}

// --- setMetadata Tests ---

TEST_F(ImageTest_55, SetMetadataFromAnotherImage_55) {
  auto otherImage = std::make_unique<TestImage>(makeMemIo());
  otherImage->setComment("Other comment");
  Exiv2::ExifData exifData;
  exifData["Exif.Image.Make"] = "OtherMake";
  otherImage->setExifData(exifData);

  image_->setMetadata(*otherImage);

  EXPECT_EQ(image_->comment(), "Other comment");
  EXPECT_FALSE(image_->exifData().empty());
}

// --- nativePreviews Tests ---

TEST_F(ImageTest_55, NativePreviewsInitiallyEmpty_55) {
  EXPECT_TRUE(image_->nativePreviews().empty());
}

// --- ImageType Tests ---

TEST_F(ImageTest_55, ImageTypeReturnsCorrectType_55) {
  EXPECT_EQ(image_->imageType(), Exiv2::ImageType::none);
}

// --- Static byteSwap Tests ---

TEST_F(ImageTest_55, ByteSwap16NoSwap_55) {
  uint16_t val = 0x1234;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234u);
}

TEST_F(ImageTest_55, ByteSwap16WithSwap_55) {
  uint16_t val = 0x1234;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412u);
}

TEST_F(ImageTest_55, ByteSwap32NoSwap_55) {
  uint32_t val = 0x12345678;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST_F(ImageTest_55, ByteSwap32WithSwap_55) {
  uint32_t val = 0x12345678;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST_F(ImageTest_55, ByteSwap64NoSwap_55) {
  uint64_t val = 0x0102030405060708ULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST_F(ImageTest_55, ByteSwap64WithSwap_55) {
  uint64_t val = 0x0102030405060708ULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

// --- Static byteSwap2/4/8 with DataBuf Tests ---

TEST_F(ImageTest_55, ByteSwap2FromBuf_55) {
  Exiv2::DataBuf buf(4);
  buf.data()[0] = 0x12;
  buf.data()[1] = 0x34;
  EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 0, false), 0x1234u);
  EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 0, true), 0x3412u);
}

TEST_F(ImageTest_55, ByteSwap4FromBuf_55) {
  Exiv2::DataBuf buf(8);
  buf.data()[0] = 0x12;
  buf.data()[1] = 0x34;
  buf.data()[2] = 0x56;
  buf.data()[3] = 0x78;
  EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 0, false), 0x12345678u);
  EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 0, true), 0x78563412u);
}

TEST_F(ImageTest_55, ByteSwap8FromBuf_55) {
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

// --- Platform endianness tests ---

TEST_F(ImageTest_55, PlatformEndianness_55) {
  // One of these must be true
  bool big = Exiv2::Image::isBigEndianPlatform();
  bool little = Exiv2::Image::isLittleEndianPlatform();
  EXPECT_TRUE(big || little);
  // They should be mutually exclusive
  EXPECT_NE(big, little);
}

// --- Static type classification tests ---

TEST_F(ImageTest_55, IsStringType_55) {
  // Type 2 is ASCII in TIFF
  EXPECT_TRUE(Exiv2::Image::isStringType(2));
  EXPECT_FALSE(Exiv2::Image::isStringType(3));  // SHORT
}

TEST_F(ImageTest_55, IsShortType_55) {
  // Type 3 is SHORT, type 8 is SSHORT
  EXPECT_TRUE(Exiv2::Image::isShortType(3));
  EXPECT_TRUE(Exiv2::Image::isShortType(8));
  EXPECT_FALSE(Exiv2::Image::isShortType(4));
}

TEST_F(ImageTest_55, IsLongType_55) {
  // Type 4 is LONG, type 9 is SLONG
  EXPECT_TRUE(Exiv2::Image::isLongType(4));
  EXPECT_TRUE(Exiv2::Image::isLongType(9));
  EXPECT_FALSE(Exiv2::Image::isLongType(3));
}

TEST_F(ImageTest_55, IsRationalType_55) {
  // Type 5 is RATIONAL, type 10 is SRATIONAL
  EXPECT_TRUE(Exiv2::Image::isRationalType(5));
  EXPECT_TRUE(Exiv2::Image::isRationalType(10));
  EXPECT_FALSE(Exiv2::Image::isRationalType(4));
}

TEST_F(ImageTest_55, Is2ByteType_55) {
  // SHORT types are 2-byte
  EXPECT_TRUE(Exiv2::Image::is2ByteType(3));
  EXPECT_TRUE(Exiv2::Image::is2ByteType(8));
  EXPECT_FALSE(Exiv2::Image::is2ByteType(4));
}

TEST_F(ImageTest_55, Is4ByteType_55) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(4));
  EXPECT_TRUE(Exiv2::Image::is4ByteType(9));
  EXPECT_FALSE(Exiv2::Image::is4ByteType(3));
}

TEST_F(ImageTest_55, Is8ByteType_55) {
  // RATIONAL (5) and SRATIONAL (10) are 8-byte
  EXPECT_TRUE(Exiv2::Image::is8ByteType(5));
  EXPECT_TRUE(Exiv2::Image::is8ByteType(10));
  EXPECT_FALSE(Exiv2::Image::is8ByteType(4));
}

// --- io() Tests ---

TEST_F(ImageTest_55, IoReturnsReference_55) {
  const Exiv2::BasicIo& io = image_->io();
  // Just verify we can call it without crashing
  (void)io;
}

// --- setTypeSupported Tests ---

TEST_F(ImageTest_55, SetTypeSupportedChangesImageType_55) {
  image_->setTypeSupported(Exiv2::ImageType::jpeg, 0xFFFF);
  EXPECT_EQ(image_->imageType(), Exiv2::ImageType::jpeg);
}

// --- Boundary: byteSwap with zero ---

TEST_F(ImageTest_55, ByteSwap16Zero_55) {
  EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), 0u);
  EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), false), 0u);
}

TEST_F(ImageTest_55, ByteSwap32Zero_55) {
  EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), 0u);
  EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), false), 0u);
}

TEST_F(ImageTest_55, ByteSwap64Zero_55) {
  EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), 0u);
  EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), false), 0u);
}

// --- Boundary: byteSwap with max values ---

TEST_F(ImageTest_55, ByteSwap16Max_55) {
  uint16_t val = 0xFFFF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFu);
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFu);
}

TEST_F(ImageTest_55, ByteSwap32Max_55) {
  uint32_t val = 0xFFFFFFFF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0xFFFFFFFFu);
}

// --- MimeType Tests ---

TEST_F(ImageTest_55, MimeTypeReturnsString_55) {
  std::string mime = image_->mimeType();
  // For ImageType::none, it should return something (possibly empty or a default)
  // We just verify it doesn't crash
  (void)mime;
}

// --- appendIccProfile Tests ---

TEST_F(ImageTest_55, AppendIccProfileBuildsProfile_55) {
  uint8_t data1[64];
  std::memset(data1, 0, sizeof(data1));
  uint8_t data2[68];
  std::memset(data2, 0, sizeof(data2));

  // Append two parts to build a 132-byte profile (minimum for validity check)
  image_->appendIccProfile(data1, sizeof(data1), false);
  image_->appendIccProfile(data2, sizeof(data2), false);

  EXPECT_TRUE(image_->iccProfileDefined());
  EXPECT_EQ(image_->iccProfile().size(), 132u);
}

// --- Multiple clear/set cycles ---

TEST_F(ImageTest_55, MultipleClearSetCycles_55) {
  for (int i = 0; i < 3; ++i) {
    image_->setComment("Comment " + std::to_string(i));
    EXPECT_EQ(image_->comment(), "Comment " + std::to_string(i));
    image_->clearComment();
    EXPECT_TRUE(image_->comment().empty());
  }
}

// --- ByteSwap2 with offset ---

TEST_F(ImageTest_55, ByteSwap2WithOffset_55) {
  Exiv2::DataBuf buf(8);
  buf.data()[0] = 0x00;
  buf.data()[1] = 0x00;
  buf.data()[2] = 0xAB;
  buf.data()[3] = 0xCD;
  EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 2, false), 0xABCDu);
  EXPECT_EQ(Exiv2::Image::byteSwap2(buf, 2, true), 0xCDABu);
}

TEST_F(ImageTest_55, ByteSwap4WithOffset_55) {
  Exiv2::DataBuf buf(8);
  buf.data()[2] = 0xDE;
  buf.data()[3] = 0xAD;
  buf.data()[4] = 0xBE;
  buf.data()[5] = 0xEF;
  EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 2, false), 0xDEADBEEFu);
  EXPECT_EQ(Exiv2::Image::byteSwap4(buf, 2, true), 0xEFBEADDEu);
}

// --- isLongLongType ---

TEST_F(ImageTest_55, IsLongLongType_55) {
  // Type 16 is typically LONG8, type 17 is SLONG8
  // If not, we just test known non-long-long types return false
  EXPECT_FALSE(Exiv2::Image::isLongLongType(3));
  EXPECT_FALSE(Exiv2::Image::isLongLongType(4));
}
