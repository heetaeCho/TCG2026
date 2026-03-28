#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <memory>

// Helper: Create a minimal Image-derived class for testing since Image is abstract
// We need a concrete subclass to test the non-virtual and static methods.
class TestImage : public Exiv2::Image {
public:
  TestImage(std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

  void readMetadata() override {}
  void writeMetadata() override {}
};

static std::unique_ptr<TestImage> createTestImage() {
  auto io = std::make_unique<Exiv2::MemIo>();
  return std::make_unique<TestImage>(std::move(io));
}

// ===== isRationalType tests =====

TEST(ImageStaticTest_1051, IsRationalType_UnsignedRational_1051) {
  EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::unsignedRational));
}

TEST(ImageStaticTest_1051, IsRationalType_SignedRational_1051) {
  EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::signedRational));
}

TEST(ImageStaticTest_1051, IsRationalType_UnsignedByte_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedByte));
}

TEST(ImageStaticTest_1051, IsRationalType_UnsignedShort_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedShort));
}

TEST(ImageStaticTest_1051, IsRationalType_UnsignedLong_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedLong));
}

TEST(ImageStaticTest_1051, IsRationalType_AsciiString_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::asciiString));
}

TEST(ImageStaticTest_1051, IsRationalType_Undefined_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::undefined));
}

TEST(ImageStaticTest_1051, IsRationalType_TiffDouble_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::tiffDouble));
}

TEST(ImageStaticTest_1051, IsRationalType_Zero_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(0));
}

TEST(ImageStaticTest_1051, IsRationalType_MaxUint16_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(0xFFFF));
}

// ===== isStringType tests =====

TEST(ImageStaticTest_1051, IsStringType_AsciiString_1051) {
  EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::asciiString));
}

TEST(ImageStaticTest_1051, IsStringType_UnsignedByte_1051) {
  EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedByte));
}

TEST(ImageStaticTest_1051, IsStringType_UnsignedRational_1051) {
  EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedRational));
}

// ===== isShortType tests =====

TEST(ImageStaticTest_1051, IsShortType_UnsignedShort_1051) {
  EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::unsignedShort));
}

TEST(ImageStaticTest_1051, IsShortType_SignedShort_1051) {
  EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::signedShort));
}

TEST(ImageStaticTest_1051, IsShortType_UnsignedLong_1051) {
  EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedLong));
}

TEST(ImageStaticTest_1051, IsShortType_UnsignedByte_1051) {
  EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedByte));
}

// ===== isLongType tests =====

TEST(ImageStaticTest_1051, IsLongType_UnsignedLong_1051) {
  EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::unsignedLong));
}

TEST(ImageStaticTest_1051, IsLongType_SignedLong_1051) {
  EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::signedLong));
}

TEST(ImageStaticTest_1051, IsLongType_UnsignedShort_1051) {
  EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedShort));
}

// ===== isLongLongType tests =====

TEST(ImageStaticTest_1051, IsLongLongType_UnsignedLongLong_1051) {
  EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::unsignedLongLong));
}

TEST(ImageStaticTest_1051, IsLongLongType_SignedLongLong_1051) {
  EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::signedLongLong));
}

TEST(ImageStaticTest_1051, IsLongLongType_UnsignedLong_1051) {
  EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedLong));
}

// ===== is2ByteType tests =====

TEST(ImageStaticTest_1051, Is2ByteType_UnsignedShort_1051) {
  EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::unsignedShort));
}

TEST(ImageStaticTest_1051, Is2ByteType_SignedShort_1051) {
  EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::signedShort));
}

TEST(ImageStaticTest_1051, Is2ByteType_UnsignedLong_1051) {
  EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedLong));
}

// ===== is4ByteType tests =====

TEST(ImageStaticTest_1051, Is4ByteType_UnsignedLong_1051) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::unsignedLong));
}

TEST(ImageStaticTest_1051, Is4ByteType_SignedLong_1051) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::signedLong));
}

TEST(ImageStaticTest_1051, Is4ByteType_TiffFloat_1051) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffFloat));
}

TEST(ImageStaticTest_1051, Is4ByteType_UnsignedShort_1051) {
  EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedShort));
}

// ===== is8ByteType tests =====

TEST(ImageStaticTest_1051, Is8ByteType_UnsignedRational_1051) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedRational));
}

TEST(ImageStaticTest_1051, Is8ByteType_SignedRational_1051) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedRational));
}

TEST(ImageStaticTest_1051, Is8ByteType_TiffDouble_1051) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffDouble));
}

TEST(ImageStaticTest_1051, Is8ByteType_UnsignedLong_1051) {
  EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedLong));
}

// ===== Platform endianness tests =====

TEST(ImageStaticTest_1051, PlatformEndianness_Consistent_1051) {
  // One must be true, one must be false (mutually exclusive)
  bool big = Exiv2::Image::isBigEndianPlatform();
  bool little = Exiv2::Image::isLittleEndianPlatform();
  EXPECT_NE(big, little);
}

// ===== byteSwap tests =====

TEST(ImageStaticTest_1051, ByteSwap16_NoSwap_1051) {
  uint16_t val = 0x1234;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST(ImageStaticTest_1051, ByteSwap16_Swap_1051) {
  uint16_t val = 0x1234;
  uint16_t swapped = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(swapped, static_cast<uint16_t>(0x3412));
}

TEST(ImageStaticTest_1051, ByteSwap32_NoSwap_1051) {
  uint32_t val = 0x12345678;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST(ImageStaticTest_1051, ByteSwap32_Swap_1051) {
  uint32_t val = 0x12345678;
  uint32_t swapped = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(swapped, static_cast<uint32_t>(0x78563412));
}

TEST(ImageStaticTest_1051, ByteSwap64_NoSwap_1051) {
  uint64_t val = 0x0102030405060708ULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST(ImageStaticTest_1051, ByteSwap64_Swap_1051) {
  uint64_t val = 0x0102030405060708ULL;
  uint64_t swapped = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(swapped, 0x0807060504030201ULL);
}

TEST(ImageStaticTest_1051, ByteSwap16_Zero_1051) {
  uint16_t val = 0;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint16_t>(0));
}

TEST(ImageStaticTest_1051, ByteSwap32_Zero_1051) {
  uint32_t val = 0;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint32_t>(0));
}

TEST(ImageStaticTest_1051, ByteSwap16_DoubleSwapIsIdentity_1051) {
  uint16_t val = 0xABCD;
  EXPECT_EQ(Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true), val);
}

TEST(ImageStaticTest_1051, ByteSwap32_DoubleSwapIsIdentity_1051) {
  uint32_t val = 0xDEADBEEF;
  EXPECT_EQ(Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true), val);
}

TEST(ImageStaticTest_1051, ByteSwap64_DoubleSwapIsIdentity_1051) {
  uint64_t val = 0xDEADBEEFCAFEBABEULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true), val);
}

// ===== byteSwap2, byteSwap4, byteSwap8 with DataBuf =====

TEST(ImageStaticTest_1051, ByteSwap2_NoSwap_1051) {
  Exiv2::DataBuf buf(4);
  buf.data()[0] = 0x12;
  buf.data()[1] = 0x34;
  uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
  // Without swap, it should read as-is in memory order
  uint16_t expected;
  std::memcpy(&expected, buf.data(), 2);
  EXPECT_EQ(result, expected);
}

TEST(ImageStaticTest_1051, ByteSwap2_Swap_1051) {
  Exiv2::DataBuf buf(4);
  buf.data()[0] = 0x12;
  buf.data()[1] = 0x34;
  uint16_t noSwap = Exiv2::Image::byteSwap2(buf, 0, false);
  uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
  EXPECT_EQ(swapped, Exiv2::Image::byteSwap(noSwap, true));
}

TEST(ImageStaticTest_1051, ByteSwap4_NoSwap_1051) {
  Exiv2::DataBuf buf(8);
  buf.data()[0] = 0x12;
  buf.data()[1] = 0x34;
  buf.data()[2] = 0x56;
  buf.data()[3] = 0x78;
  uint32_t result = Exiv2::Image::byteSwap4(buf, 0, false);
  uint32_t expected;
  std::memcpy(&expected, buf.data(), 4);
  EXPECT_EQ(result, expected);
}

TEST(ImageStaticTest_1051, ByteSwap8_NoSwap_1051) {
  Exiv2::DataBuf buf(16);
  for (int i = 0; i < 8; i++) {
    buf.data()[i] = static_cast<uint8_t>(i + 1);
  }
  uint64_t result = Exiv2::Image::byteSwap8(buf, 0, false);
  uint64_t expected;
  std::memcpy(&expected, buf.data(), 8);
  EXPECT_EQ(result, expected);
}

// ===== Instance method tests =====

class ImageInstanceTest_1051 : public ::testing::Test {
protected:
  std::unique_ptr<TestImage> img;

  void SetUp() override {
    img = createTestImage();
  }
};

TEST_F(ImageInstanceTest_1051, DefaultPixelWidth_1051) {
  EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(ImageInstanceTest_1051, DefaultPixelHeight_1051) {
  EXPECT_EQ(img->pixelHeight(), 0u);
}

TEST_F(ImageInstanceTest_1051, DefaultComment_1051) {
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageInstanceTest_1051, SetComment_1051) {
  img->setComment("test comment");
  EXPECT_EQ(img->comment(), "test comment");
}

TEST_F(ImageInstanceTest_1051, ClearComment_1051) {
  img->setComment("hello");
  img->clearComment();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageInstanceTest_1051, SetAndClearExifData_1051) {
  Exiv2::ExifData exifData;
  img->setExifData(exifData);
  img->clearExifData();
  EXPECT_TRUE(img->exifData().empty());
}

TEST_F(ImageInstanceTest_1051, SetAndClearIptcData_1051) {
  Exiv2::IptcData iptcData;
  img->setIptcData(iptcData);
  img->clearIptcData();
  EXPECT_TRUE(img->iptcData().empty());
}

TEST_F(ImageInstanceTest_1051, SetAndClearXmpData_1051) {
  Exiv2::XmpData xmpData;
  img->setXmpData(xmpData);
  img->clearXmpData();
  EXPECT_TRUE(img->xmpData().empty());
}

TEST_F(ImageInstanceTest_1051, SetXmpPacket_1051) {
  img->setXmpPacket("<xmp>test</xmp>");
  EXPECT_EQ(img->xmpPacket(), "<xmp>test</xmp>");
}

TEST_F(ImageInstanceTest_1051, ClearXmpPacket_1051) {
  img->setXmpPacket("<xmp>test</xmp>");
  img->clearXmpPacket();
  EXPECT_TRUE(img->xmpPacket().empty());
}

TEST_F(ImageInstanceTest_1051, WriteXmpFromPacketFlag_1051) {
  EXPECT_FALSE(img->writeXmpFromPacket());
  img->writeXmpFromPacket(true);
  EXPECT_TRUE(img->writeXmpFromPacket());
  img->writeXmpFromPacket(false);
  EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageInstanceTest_1051, DefaultByteOrder_1051) {
  EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageInstanceTest_1051, SetByteOrder_1051) {
  img->setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
  img->setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageInstanceTest_1051, Good_1051) {
  // MemIo should be good after construction
  EXPECT_TRUE(img->good());
}

TEST_F(ImageInstanceTest_1051, IoAccessible_1051) {
  // io() should return a valid reference
  Exiv2::BasicIo& io = img->io();
  (void)io; // just ensure no crash
}

TEST_F(ImageInstanceTest_1051, ClearMetadata_1051) {
  img->setComment("test");
  img->clearMetadata();
  EXPECT_TRUE(img->comment().empty());
  EXPECT_TRUE(img->exifData().empty());
  EXPECT_TRUE(img->iptcData().empty());
  EXPECT_TRUE(img->xmpData().empty());
  EXPECT_TRUE(img->xmpPacket().empty());
}

TEST_F(ImageInstanceTest_1051, NativePreviewsEmpty_1051) {
  EXPECT_TRUE(img->nativePreviews().empty());
}

TEST_F(ImageInstanceTest_1051, IccProfileNotDefined_1051) {
  EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1051, ClearIccProfile_1051) {
  img->clearIccProfile();
  EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1051, SetMetadataFromAnotherImage_1051) {
  auto img2 = createTestImage();
  img2->setComment("copy me");
  img->setMetadata(*img2);
  EXPECT_EQ(img->comment(), "copy me");
}

TEST_F(ImageInstanceTest_1051, ImageType_1051) {
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
}

// ===== isPrintXMP / isPrintICC tests =====

TEST(ImageStaticTest_1051, IsPrintXMP_WithPrintXMP_1051) {
  // type == string (asciiString=2) and option == kpsXMP
  // We don't know exact logic but we can probe known combinations
  bool result = Exiv2::Image::isPrintXMP(Exiv2::asciiString, Exiv2::kpsXMP);
  // Just verify it doesn't crash and returns a bool
  (void)result;
}

TEST(ImageStaticTest_1051, IsPrintICC_WithPrintICC_1051) {
  bool result = Exiv2::Image::isPrintICC(Exiv2::undefined, Exiv2::kpsIccProfile);
  (void)result;
}

// ===== Boundary: isRationalType with boundary type values =====

TEST(ImageStaticTest_1051, IsRationalType_SignedByte_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::signedByte));
}

TEST(ImageStaticTest_1051, IsRationalType_TiffIfd_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::tiffIfd));
}

TEST(ImageStaticTest_1051, IsRationalType_TiffIfd8_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::tiffIfd8));
}

TEST(ImageStaticTest_1051, IsRationalType_SignedLong_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::signedLong));
}

TEST(ImageStaticTest_1051, IsRationalType_TiffFloat_1051) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::tiffFloat));
}
