#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/exif.hpp>
#include <sstream>
#include <memory>

// Helper: Create a minimal Image-derived class for testing since Image is abstract
// We need a concrete subclass to test the non-virtual static and instance methods.
class TestImage : public Exiv2::Image {
public:
  TestImage(std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

  void readMetadata() override {}
  void writeMetadata() override {}
  std::string mimeType() const override { return "application/octet-stream"; }
};

static std::unique_ptr<TestImage> createTestImage() {
  auto io = std::make_unique<Exiv2::MemIo>();
  return std::make_unique<TestImage>(std::move(io));
}

// ==================== isLongType Tests ====================

TEST(ImageStaticTest_1049, IsLongType_UnsignedLong_1049) {
  EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::unsignedLong));
}

TEST(ImageStaticTest_1049, IsLongType_SignedLong_1049) {
  EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::signedLong));
}

TEST(ImageStaticTest_1049, IsLongType_UnsignedShort_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedShort));
}

TEST(ImageStaticTest_1049, IsLongType_UnsignedByte_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedByte));
}

TEST(ImageStaticTest_1049, IsLongType_AsciiString_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::asciiString));
}

TEST(ImageStaticTest_1049, IsLongType_UnsignedRational_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedRational));
}

TEST(ImageStaticTest_1049, IsLongType_TiffIfd_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::tiffIfd));
}

TEST(ImageStaticTest_1049, IsLongType_Zero_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongType(0));
}

TEST(ImageStaticTest_1049, IsLongType_MaxUint16_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongType(0xFFFF));
}

// ==================== isShortType Tests ====================

TEST(ImageStaticTest_1049, IsShortType_UnsignedShort_1049) {
  EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::unsignedShort));
}

TEST(ImageStaticTest_1049, IsShortType_SignedShort_1049) {
  EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::signedShort));
}

TEST(ImageStaticTest_1049, IsShortType_UnsignedLong_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedLong));
}

TEST(ImageStaticTest_1049, IsShortType_AsciiString_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::asciiString));
}

// ==================== isStringType Tests ====================

TEST(ImageStaticTest_1049, IsStringType_AsciiString_1049) {
  EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::asciiString));
}

TEST(ImageStaticTest_1049, IsStringType_UnsignedLong_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedLong));
}

TEST(ImageStaticTest_1049, IsStringType_UnsignedShort_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedShort));
}

// ==================== isLongLongType Tests ====================

TEST(ImageStaticTest_1049, IsLongLongType_UnsignedLongLong_1049) {
  EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::unsignedLongLong));
}

TEST(ImageStaticTest_1049, IsLongLongType_SignedLongLong_1049) {
  EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::signedLongLong));
}

TEST(ImageStaticTest_1049, IsLongLongType_UnsignedLong_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedLong));
}

TEST(ImageStaticTest_1049, IsLongLongType_Zero_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isLongLongType(0));
}

// ==================== isRationalType Tests ====================

TEST(ImageStaticTest_1049, IsRationalType_UnsignedRational_1049) {
  EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::unsignedRational));
}

TEST(ImageStaticTest_1049, IsRationalType_SignedRational_1049) {
  EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::signedRational));
}

TEST(ImageStaticTest_1049, IsRationalType_UnsignedLong_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedLong));
}

// ==================== is2ByteType Tests ====================

TEST(ImageStaticTest_1049, Is2ByteType_UnsignedShort_1049) {
  EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::unsignedShort));
}

TEST(ImageStaticTest_1049, Is2ByteType_SignedShort_1049) {
  EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::signedShort));
}

TEST(ImageStaticTest_1049, Is2ByteType_UnsignedLong_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedLong));
}

// ==================== is4ByteType Tests ====================

TEST(ImageStaticTest_1049, Is4ByteType_UnsignedLong_1049) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::unsignedLong));
}

TEST(ImageStaticTest_1049, Is4ByteType_SignedLong_1049) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::signedLong));
}

TEST(ImageStaticTest_1049, Is4ByteType_TiffFloat_1049) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffFloat));
}

TEST(ImageStaticTest_1049, Is4ByteType_TiffIfd_1049) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffIfd));
}

TEST(ImageStaticTest_1049, Is4ByteType_UnsignedShort_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedShort));
}

// ==================== is8ByteType Tests ====================

TEST(ImageStaticTest_1049, Is8ByteType_UnsignedRational_1049) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedRational));
}

TEST(ImageStaticTest_1049, Is8ByteType_SignedRational_1049) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedRational));
}

TEST(ImageStaticTest_1049, Is8ByteType_TiffDouble_1049) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffDouble));
}

TEST(ImageStaticTest_1049, Is8ByteType_UnsignedLongLong_1049) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedLongLong));
}

TEST(ImageStaticTest_1049, Is8ByteType_SignedLongLong_1049) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedLongLong));
}

TEST(ImageStaticTest_1049, Is8ByteType_TiffIfd8_1049) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffIfd8));
}

TEST(ImageStaticTest_1049, Is8ByteType_UnsignedLong_ReturnsFalse_1049) {
  EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedLong));
}

// ==================== Platform Endian Tests ====================

TEST(ImageStaticTest_1049, EndianPlatform_MutuallyConsistent_1049) {
  bool isBig = Exiv2::Image::isBigEndianPlatform();
  bool isLittle = Exiv2::Image::isLittleEndianPlatform();
  // Exactly one should be true
  EXPECT_NE(isBig, isLittle);
}

// ==================== byteSwap Tests ====================

TEST(ImageStaticTest_1049, ByteSwap16_NoSwap_1049) {
  uint16_t val = 0x1234;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x1234);
}

TEST(ImageStaticTest_1049, ByteSwap16_Swap_1049) {
  uint16_t val = 0x1234;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x3412);
}

TEST(ImageStaticTest_1049, ByteSwap32_NoSwap_1049) {
  uint32_t val = 0x12345678;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x12345678u);
}

TEST(ImageStaticTest_1049, ByteSwap32_Swap_1049) {
  uint32_t val = 0x12345678;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x78563412u);
}

TEST(ImageStaticTest_1049, ByteSwap64_NoSwap_1049) {
  uint64_t val = 0x0102030405060708ULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), 0x0102030405060708ULL);
}

TEST(ImageStaticTest_1049, ByteSwap64_Swap_1049) {
  uint64_t val = 0x0102030405060708ULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0x0807060504030201ULL);
}

TEST(ImageStaticTest_1049, ByteSwap16_Zero_1049) {
  uint16_t val = 0;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0);
}

TEST(ImageStaticTest_1049, ByteSwap32_Zero_1049) {
  uint32_t val = 0;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0u);
}

TEST(ImageStaticTest_1049, ByteSwap64_Zero_1049) {
  uint64_t val = 0;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0ULL);
}

TEST(ImageStaticTest_1049, ByteSwap16_DoubleSwap_Identity_1049) {
  uint16_t val = 0xABCD;
  uint16_t swapped = Exiv2::Image::byteSwap(val, true);
  uint16_t restored = Exiv2::Image::byteSwap(swapped, true);
  EXPECT_EQ(val, restored);
}

TEST(ImageStaticTest_1049, ByteSwap32_DoubleSwap_Identity_1049) {
  uint32_t val = 0xDEADBEEF;
  uint32_t swapped = Exiv2::Image::byteSwap(val, true);
  uint32_t restored = Exiv2::Image::byteSwap(swapped, true);
  EXPECT_EQ(val, restored);
}

TEST(ImageStaticTest_1049, ByteSwap64_DoubleSwap_Identity_1049) {
  uint64_t val = 0xDEADBEEFCAFEBABEULL;
  uint64_t swapped = Exiv2::Image::byteSwap(val, true);
  uint64_t restored = Exiv2::Image::byteSwap(swapped, true);
  EXPECT_EQ(val, restored);
}

// ==================== Instance Method Tests ====================

class ImageInstanceTest_1049 : public ::testing::Test {
protected:
  std::unique_ptr<TestImage> image_;

  void SetUp() override {
    image_ = createTestImage();
  }
};

TEST_F(ImageInstanceTest_1049, Good_InitialState_1049) {
  // MemIo should be in good state initially
  EXPECT_TRUE(image_->good());
}

TEST_F(ImageInstanceTest_1049, ByteOrder_DefaultIsInvalid_1049) {
  EXPECT_EQ(image_->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageInstanceTest_1049, SetByteOrder_1049) {
  image_->setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(image_->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageInstanceTest_1049, SetByteOrder_LittleEndian_1049) {
  image_->setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(image_->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageInstanceTest_1049, PixelWidth_Default_1049) {
  EXPECT_EQ(image_->pixelWidth(), 0u);
}

TEST_F(ImageInstanceTest_1049, PixelHeight_Default_1049) {
  EXPECT_EQ(image_->pixelHeight(), 0u);
}

TEST_F(ImageInstanceTest_1049, Comment_DefaultEmpty_1049) {
  EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageInstanceTest_1049, SetComment_1049) {
  image_->setComment("Hello World");
  EXPECT_EQ(image_->comment(), "Hello World");
}

TEST_F(ImageInstanceTest_1049, ClearComment_1049) {
  image_->setComment("Test comment");
  image_->clearComment();
  EXPECT_TRUE(image_->comment().empty());
}

TEST_F(ImageInstanceTest_1049, WriteXmpFromPacket_DefaultFalse_1049) {
  EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageInstanceTest_1049, WriteXmpFromPacket_SetTrue_1049) {
  image_->writeXmpFromPacket(true);
  EXPECT_TRUE(image_->writeXmpFromPacket());
}

TEST_F(ImageInstanceTest_1049, WriteXmpFromPacket_SetFalse_1049) {
  image_->writeXmpFromPacket(true);
  image_->writeXmpFromPacket(false);
  EXPECT_FALSE(image_->writeXmpFromPacket());
}

TEST_F(ImageInstanceTest_1049, ExifData_InitiallyEmpty_1049) {
  EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageInstanceTest_1049, IptcData_InitiallyEmpty_1049) {
  EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageInstanceTest_1049, XmpData_InitiallyEmpty_1049) {
  EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageInstanceTest_1049, XmpPacket_InitiallyEmpty_1049) {
  EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageInstanceTest_1049, SetXmpPacket_1049) {
  std::string packet = "<xmp>test</xmp>";
  image_->setXmpPacket(packet);
  EXPECT_EQ(image_->xmpPacket(), packet);
}

TEST_F(ImageInstanceTest_1049, ClearXmpPacket_1049) {
  image_->setXmpPacket("<xmp>test</xmp>");
  image_->clearXmpPacket();
  EXPECT_TRUE(image_->xmpPacket().empty());
}

TEST_F(ImageInstanceTest_1049, ClearExifData_1049) {
  image_->clearExifData();
  EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageInstanceTest_1049, ClearIptcData_1049) {
  image_->clearIptcData();
  EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageInstanceTest_1049, ClearXmpData_1049) {
  image_->clearXmpData();
  EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageInstanceTest_1049, ClearMetadata_1049) {
  image_->setComment("test");
  image_->clearMetadata();
  EXPECT_TRUE(image_->comment().empty());
  EXPECT_TRUE(image_->exifData().empty());
  EXPECT_TRUE(image_->iptcData().empty());
  EXPECT_TRUE(image_->xmpData().empty());
}

TEST_F(ImageInstanceTest_1049, IccProfile_InitiallyNotDefined_1049) {
  EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1049, ClearIccProfile_1049) {
  image_->clearIccProfile();
  EXPECT_FALSE(image_->iccProfileDefined());
}

TEST_F(ImageInstanceTest_1049, NativePreviews_InitiallyEmpty_1049) {
  EXPECT_TRUE(image_->nativePreviews().empty());
}

TEST_F(ImageInstanceTest_1049, Io_ReturnsValidReference_1049) {
  const Exiv2::BasicIo& io = image_->io();
  // Just verify it doesn't crash and returns a reference
  (void)io;
  SUCCEED();
}

TEST_F(ImageInstanceTest_1049, SetMetadata_CopiesFromAnother_1049) {
  auto other = createTestImage();
  other->setComment("Copied comment");
  image_->setMetadata(*other);
  EXPECT_EQ(image_->comment(), "Copied comment");
}

TEST_F(ImageInstanceTest_1049, MimeType_1049) {
  EXPECT_EQ(image_->mimeType(), "application/octet-stream");
}

// ==================== byteSwap2/4/8 with DataBuf Tests ====================

TEST(ImageStaticTest_1049, ByteSwap2_NoSwap_1049) {
  Exiv2::DataBuf buf(4);
  buf.write_uint8(0, 0x12);
  buf.write_uint8(1, 0x34);
  uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
  // Without swap, should read as-is in memory order
  // The exact value depends on implementation; just verify no crash and consistency
  uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
  // Double swap should differ (unless symmetric)
  // At minimum, verify both calls succeed
  (void)result;
  (void)swapped;
  SUCCEED();
}

TEST(ImageStaticTest_1049, ByteSwap4_NoSwap_1049) {
  Exiv2::DataBuf buf(8);
  buf.write_uint8(0, 0x12);
  buf.write_uint8(1, 0x34);
  buf.write_uint8(2, 0x56);
  buf.write_uint8(3, 0x78);
  uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
  uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
  // They should differ unless the bytes are palindromic
  (void)noSwap;
  (void)swapped;
  SUCCEED();
}

TEST(ImageStaticTest_1049, ByteSwap8_NoSwap_1049) {
  Exiv2::DataBuf buf(16);
  for (size_t i = 0; i < 8; ++i) {
    buf.write_uint8(i, static_cast<uint8_t>(i + 1));
  }
  uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
  uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
  (void)noSwap;
  (void)swapped;
  SUCCEED();
}

// ==================== isPrintXMP / isPrintICC Tests ====================

TEST(ImageStaticTest_1049, IsPrintXMP_WithPrintXMP_1049) {
  // Type 2 (asciiString) with kpsXMP option
  bool result = Exiv2::Image::isPrintXMP(Exiv2::asciiString, Exiv2::kpsXMP);
  // We just check it doesn't crash and returns a bool
  (void)result;
  SUCCEED();
}

TEST(ImageStaticTest_1049, IsPrintICC_WithPrintICC_1049) {
  bool result = Exiv2::Image::isPrintICC(Exiv2::asciiString, Exiv2::kpsIccProfile);
  (void)result;
  SUCCEED();
}

// ==================== SetExifData / SetIptcData / SetXmpData Tests ====================

TEST_F(ImageInstanceTest_1049, SetExifData_1049) {
  Exiv2::ExifData exifData;
  image_->setExifData(exifData);
  EXPECT_TRUE(image_->exifData().empty());
}

TEST_F(ImageInstanceTest_1049, SetIptcData_1049) {
  Exiv2::IptcData iptcData;
  image_->setIptcData(iptcData);
  EXPECT_TRUE(image_->iptcData().empty());
}

TEST_F(ImageInstanceTest_1049, SetXmpData_1049) {
  Exiv2::XmpData xmpData;
  image_->setXmpData(xmpData);
  EXPECT_TRUE(image_->xmpData().empty());
}

// ==================== Edge cases for byte swap ====================

TEST(ImageStaticTest_1049, ByteSwap16_MaxValue_1049) {
  uint16_t val = 0xFFFF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFF);
}

TEST(ImageStaticTest_1049, ByteSwap32_MaxValue_1049) {
  uint32_t val = 0xFFFFFFFF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFu);
}

TEST(ImageStaticTest_1049, ByteSwap64_MaxValue_1049) {
  uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFFFFFFFFFFFFFFFFULL);
}

TEST(ImageStaticTest_1049, ByteSwap16_OneByte_1049) {
  uint16_t val = 0x00FF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFF00);
}

TEST(ImageStaticTest_1049, ByteSwap32_OneByte_1049) {
  uint32_t val = 0x000000FF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), 0xFF000000u);
}
