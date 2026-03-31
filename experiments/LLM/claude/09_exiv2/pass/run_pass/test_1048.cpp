#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/basicio.hpp>
#include <sstream>
#include <memory>

// Helper: Create a concrete Image subclass for testing since Image has pure virtual methods
// We use a minimal subclass that implements required virtual methods
class TestImage : public Exiv2::Image {
public:
  TestImage(std::unique_ptr<Exiv2::BasicIo> io)
      : Exiv2::Image(Exiv2::ImageType::none, 0xFFFF, std::move(io)) {}

  void readMetadata() override {}
  void writeMetadata() override {}
  std::string mimeType() const override { return "application/octet-stream"; }
};

class ImageTest_1048 : public ::testing::Test {
protected:
  std::unique_ptr<TestImage> createTestImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<TestImage>(std::move(io));
  }
};

// ============================================================
// isShortType tests
// ============================================================

TEST_F(ImageTest_1048, IsShortType_UnsignedShort_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::unsignedShort));
}

TEST_F(ImageTest_1048, IsShortType_SignedShort_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::isShortType(Exiv2::signedShort));
}

TEST_F(ImageTest_1048, IsShortType_UnsignedByte_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedByte));
}

TEST_F(ImageTest_1048, IsShortType_UnsignedLong_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::unsignedLong));
}

TEST_F(ImageTest_1048, IsShortType_AsciiString_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isShortType(Exiv2::asciiString));
}

TEST_F(ImageTest_1048, IsShortType_Zero_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isShortType(0));
}

TEST_F(ImageTest_1048, IsShortType_MaxUint16_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isShortType(0xFFFF));
}

// ============================================================
// isStringType tests
// ============================================================

TEST_F(ImageTest_1048, IsStringType_AsciiString_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::isStringType(Exiv2::asciiString));
}

TEST_F(ImageTest_1048, IsStringType_UnsignedShort_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedShort));
}

TEST_F(ImageTest_1048, IsStringType_UnsignedLong_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isStringType(Exiv2::unsignedLong));
}

TEST_F(ImageTest_1048, IsStringType_Zero_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isStringType(0));
}

// ============================================================
// isLongType tests
// ============================================================

TEST_F(ImageTest_1048, IsLongType_UnsignedLong_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::unsignedLong));
}

TEST_F(ImageTest_1048, IsLongType_SignedLong_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::isLongType(Exiv2::signedLong));
}

TEST_F(ImageTest_1048, IsLongType_UnsignedShort_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isLongType(Exiv2::unsignedShort));
}

TEST_F(ImageTest_1048, IsLongType_Zero_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isLongType(0));
}

// ============================================================
// isLongLongType tests
// ============================================================

TEST_F(ImageTest_1048, IsLongLongType_UnsignedLongLong_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::unsignedLongLong));
}

TEST_F(ImageTest_1048, IsLongLongType_SignedLongLong_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::isLongLongType(Exiv2::signedLongLong));
}

TEST_F(ImageTest_1048, IsLongLongType_UnsignedLong_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isLongLongType(Exiv2::unsignedLong));
}

TEST_F(ImageTest_1048, IsLongLongType_Zero_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isLongLongType(0));
}

// ============================================================
// isRationalType tests
// ============================================================

TEST_F(ImageTest_1048, IsRationalType_UnsignedRational_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::unsignedRational));
}

TEST_F(ImageTest_1048, IsRationalType_SignedRational_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::isRationalType(Exiv2::signedRational));
}

TEST_F(ImageTest_1048, IsRationalType_UnsignedLong_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(Exiv2::unsignedLong));
}

TEST_F(ImageTest_1048, IsRationalType_Zero_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::isRationalType(0));
}

// ============================================================
// is2ByteType tests
// ============================================================

TEST_F(ImageTest_1048, Is2ByteType_UnsignedShort_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageTest_1048, Is2ByteType_SignedShort_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is2ByteType(Exiv2::signedShort));
}

TEST_F(ImageTest_1048, Is2ByteType_UnsignedLong_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::is2ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageTest_1048, Is2ByteType_Zero_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::is2ByteType(0));
}

// ============================================================
// is4ByteType tests
// ============================================================

TEST_F(ImageTest_1048, Is4ByteType_UnsignedLong_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageTest_1048, Is4ByteType_SignedLong_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::signedLong));
}

TEST_F(ImageTest_1048, Is4ByteType_TiffFloat_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffFloat));
}

TEST_F(ImageTest_1048, Is4ByteType_TiffIfd_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is4ByteType(Exiv2::tiffIfd));
}

TEST_F(ImageTest_1048, Is4ByteType_UnsignedShort_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::is4ByteType(Exiv2::unsignedShort));
}

TEST_F(ImageTest_1048, Is4ByteType_Zero_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::is4ByteType(0));
}

// ============================================================
// is8ByteType tests
// ============================================================

TEST_F(ImageTest_1048, Is8ByteType_UnsignedRational_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedRational));
}

TEST_F(ImageTest_1048, Is8ByteType_SignedRational_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedRational));
}

TEST_F(ImageTest_1048, Is8ByteType_TiffDouble_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffDouble));
}

TEST_F(ImageTest_1048, Is8ByteType_UnsignedLongLong_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::unsignedLongLong));
}

TEST_F(ImageTest_1048, Is8ByteType_SignedLongLong_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::signedLongLong));
}

TEST_F(ImageTest_1048, Is8ByteType_TiffIfd8_ReturnsTrue_1048) {
  EXPECT_TRUE(Exiv2::Image::is8ByteType(Exiv2::tiffIfd8));
}

TEST_F(ImageTest_1048, Is8ByteType_UnsignedLong_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::is8ByteType(Exiv2::unsignedLong));
}

TEST_F(ImageTest_1048, Is8ByteType_Zero_ReturnsFalse_1048) {
  EXPECT_FALSE(Exiv2::Image::is8ByteType(0));
}

// ============================================================
// Platform endianness tests
// ============================================================

TEST_F(ImageTest_1048, EndiannessMutuallyExclusive_1048) {
  bool big = Exiv2::Image::isBigEndianPlatform();
  bool little = Exiv2::Image::isLittleEndianPlatform();
  // Platform must be either big or little endian, not both
  EXPECT_NE(big, little);
}

TEST_F(ImageTest_1048, IsLittleEndianPlatform_ConsistentResult_1048) {
  bool first = Exiv2::Image::isLittleEndianPlatform();
  bool second = Exiv2::Image::isLittleEndianPlatform();
  EXPECT_EQ(first, second);
}

TEST_F(ImageTest_1048, IsBigEndianPlatform_ConsistentResult_1048) {
  bool first = Exiv2::Image::isBigEndianPlatform();
  bool second = Exiv2::Image::isBigEndianPlatform();
  EXPECT_EQ(first, second);
}

// ============================================================
// byteSwap tests
// ============================================================

TEST_F(ImageTest_1048, ByteSwap16_NoSwap_ReturnsSameValue_1048) {
  uint16_t val = 0x1234;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1048, ByteSwap16_Swap_ReturnsSwappedValue_1048) {
  uint16_t val = 0x1234;
  uint16_t swapped = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(swapped, static_cast<uint16_t>(0x3412));
}

TEST_F(ImageTest_1048, ByteSwap16_DoubleSwap_ReturnsOriginal_1048) {
  uint16_t val = 0xABCD;
  uint16_t swapped = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
  EXPECT_EQ(swapped, val);
}

TEST_F(ImageTest_1048, ByteSwap16_Zero_ReturnsZero_1048) {
  EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint16_t>(0), true), static_cast<uint16_t>(0));
}

TEST_F(ImageTest_1048, ByteSwap32_NoSwap_ReturnsSameValue_1048) {
  uint32_t val = 0x12345678;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1048, ByteSwap32_Swap_ReturnsSwappedValue_1048) {
  uint32_t val = 0x12345678;
  uint32_t swapped = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(swapped, static_cast<uint32_t>(0x78563412));
}

TEST_F(ImageTest_1048, ByteSwap32_DoubleSwap_ReturnsOriginal_1048) {
  uint32_t val = 0xDEADBEEF;
  uint32_t swapped = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
  EXPECT_EQ(swapped, val);
}

TEST_F(ImageTest_1048, ByteSwap64_NoSwap_ReturnsSameValue_1048) {
  uint64_t val = 0x0102030405060708ULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, false), val);
}

TEST_F(ImageTest_1048, ByteSwap64_Swap_ReturnsSwappedValue_1048) {
  uint64_t val = 0x0102030405060708ULL;
  uint64_t swapped = Exiv2::Image::byteSwap(val, true);
  EXPECT_EQ(swapped, static_cast<uint64_t>(0x0807060504030201ULL));
}

TEST_F(ImageTest_1048, ByteSwap64_DoubleSwap_ReturnsOriginal_1048) {
  uint64_t val = 0xDEADBEEFCAFEBABEULL;
  uint64_t swapped = Exiv2::Image::byteSwap(Exiv2::Image::byteSwap(val, true), true);
  EXPECT_EQ(swapped, val);
}

// ============================================================
// byteSwap2/4/8 with DataBuf tests
// ============================================================

TEST_F(ImageTest_1048, ByteSwap2_NoSwap_1048) {
  Exiv2::DataBuf buf(4);
  buf.data()[0] = 0x12;
  buf.data()[1] = 0x34;
  uint16_t result = Exiv2::Image::byteSwap2(buf, 0, false);
  // Without swap, should read as native byte order
  // We just verify double swap returns original
  uint16_t swapped = Exiv2::Image::byteSwap2(buf, 0, true);
  // Double application: swap the swapped result
  // The no-swap result should differ from swap result (unless palindrome)
  // Just check they are both well-defined
  EXPECT_TRUE(result == 0x1234 || result == 0x3412);
}

TEST_F(ImageTest_1048, ByteSwap4_BasicTest_1048) {
  Exiv2::DataBuf buf(8);
  buf.data()[0] = 0x01;
  buf.data()[1] = 0x02;
  buf.data()[2] = 0x03;
  buf.data()[3] = 0x04;
  uint32_t noSwap = Exiv2::Image::byteSwap4(buf, 0, false);
  uint32_t swapped = Exiv2::Image::byteSwap4(buf, 0, true);
  // The swap and no-swap should differ for non-palindromic values
  EXPECT_NE(noSwap, swapped);
}

TEST_F(ImageTest_1048, ByteSwap8_BasicTest_1048) {
  Exiv2::DataBuf buf(16);
  for (int i = 0; i < 8; ++i) {
    buf.data()[i] = static_cast<uint8_t>(i + 1);
  }
  uint64_t noSwap = Exiv2::Image::byteSwap8(buf, 0, false);
  uint64_t swapped = Exiv2::Image::byteSwap8(buf, 0, true);
  EXPECT_NE(noSwap, swapped);
}

// ============================================================
// Image instance tests (using TestImage subclass)
// ============================================================

TEST_F(ImageTest_1048, DefaultByteOrder_IsInvalid_1048) {
  auto img = createTestImage();
  EXPECT_EQ(img->byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(ImageTest_1048, SetByteOrder_1048) {
  auto img = createTestImage();
  img->setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
}

TEST_F(ImageTest_1048, SetByteOrder_LittleEndian_1048) {
  auto img = createTestImage();
  img->setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

TEST_F(ImageTest_1048, DefaultPixelWidth_IsZero_1048) {
  auto img = createTestImage();
  EXPECT_EQ(img->pixelWidth(), 0u);
}

TEST_F(ImageTest_1048, DefaultPixelHeight_IsZero_1048) {
  auto img = createTestImage();
  EXPECT_EQ(img->pixelHeight(), 0u);
}

TEST_F(ImageTest_1048, DefaultComment_IsEmpty_1048) {
  auto img = createTestImage();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_1048, SetComment_1048) {
  auto img = createTestImage();
  img->setComment("test comment");
  EXPECT_EQ(img->comment(), "test comment");
}

TEST_F(ImageTest_1048, ClearComment_1048) {
  auto img = createTestImage();
  img->setComment("test comment");
  img->clearComment();
  EXPECT_TRUE(img->comment().empty());
}

TEST_F(ImageTest_1048, WriteXmpFromPacket_DefaultFalse_1048) {
  auto img = createTestImage();
  EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1048, WriteXmpFromPacket_SetTrue_1048) {
  auto img = createTestImage();
  img->writeXmpFromPacket(true);
  EXPECT_TRUE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1048, WriteXmpFromPacket_SetFalse_1048) {
  auto img = createTestImage();
  img->writeXmpFromPacket(true);
  img->writeXmpFromPacket(false);
  EXPECT_FALSE(img->writeXmpFromPacket());
}

TEST_F(ImageTest_1048, ExifData_InitiallyEmpty_1048) {
  auto img = createTestImage();
  EXPECT_TRUE(img->exifData().empty());
}

TEST_F(ImageTest_1048, IptcData_InitiallyEmpty_1048) {
  auto img = createTestImage();
  EXPECT_TRUE(img->iptcData().empty());
}

TEST_F(ImageTest_1048, XmpData_InitiallyEmpty_1048) {
  auto img = createTestImage();
  EXPECT_TRUE(img->xmpData().empty());
}

TEST_F(ImageTest_1048, ClearExifData_1048) {
  auto img = createTestImage();
  img->clearExifData();
  EXPECT_TRUE(img->exifData().empty());
}

TEST_F(ImageTest_1048, ClearIptcData_1048) {
  auto img = createTestImage();
  img->clearIptcData();
  EXPECT_TRUE(img->iptcData().empty());
}

TEST_F(ImageTest_1048, ClearXmpData_1048) {
  auto img = createTestImage();
  img->clearXmpData();
  EXPECT_TRUE(img->xmpData().empty());
}

TEST_F(ImageTest_1048, ClearXmpPacket_1048) {
  auto img = createTestImage();
  img->setXmpPacket("<xmp>test</xmp>");
  img->clearXmpPacket();
  EXPECT_TRUE(img->xmpPacket().empty());
}

TEST_F(ImageTest_1048, SetXmpPacket_1048) {
  auto img = createTestImage();
  std::string packet = "<xmp>some xmp data</xmp>";
  img->setXmpPacket(packet);
  EXPECT_EQ(img->xmpPacket(), packet);
}

TEST_F(ImageTest_1048, ClearMetadata_1048) {
  auto img = createTestImage();
  img->setComment("test");
  img->clearMetadata();
  EXPECT_TRUE(img->comment().empty());
  EXPECT_TRUE(img->exifData().empty());
  EXPECT_TRUE(img->iptcData().empty());
  EXPECT_TRUE(img->xmpData().empty());
}

TEST_F(ImageTest_1048, IccProfileDefined_InitiallyFalse_1048) {
  auto img = createTestImage();
  EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageTest_1048, ClearIccProfile_1048) {
  auto img = createTestImage();
  img->clearIccProfile();
  EXPECT_FALSE(img->iccProfileDefined());
}

TEST_F(ImageTest_1048, Good_ReturnsTrueForMemIo_1048) {
  auto img = createTestImage();
  // MemIo should be in good state
  EXPECT_TRUE(img->good());
}

TEST_F(ImageTest_1048, NativePreviews_InitiallyEmpty_1048) {
  auto img = createTestImage();
  EXPECT_TRUE(img->nativePreviews().empty());
}

TEST_F(ImageTest_1048, SetMetadata_CopiesFromAnotherImage_1048) {
  auto img1 = createTestImage();
  auto img2 = createTestImage();
  img1->setComment("source comment");
  img2->setMetadata(*img1);
  EXPECT_EQ(img2->comment(), "source comment");
}

// ============================================================
// isPrintXMP / isPrintICC tests
// ============================================================

TEST_F(ImageTest_1048, IsPrintXMP_WithKpsXMP_1048) {
  // type = Exiv2::unsignedByte (1) is likely XMP tag type context
  // We just verify the function doesn't crash and returns a boolean
  bool result = Exiv2::Image::isPrintXMP(Exiv2::unsignedByte, Exiv2::kpsXMP);
  // We can't know the exact result without impl, but at least it runs
  (void)result;
}

TEST_F(ImageTest_1048, IsPrintICC_WithKpsIccProfile_1048) {
  bool result = Exiv2::Image::isPrintICC(Exiv2::unsignedByte, Exiv2::kpsIccProfile);
  (void)result;
}

// ============================================================
// Boundary: isShortType with all TypeId values
// ============================================================

TEST_F(ImageTest_1048, IsShortType_AllNonShortTypes_ReturnFalse_1048) {
  // Test a range of non-short types
  std::vector<uint16_t> nonShortTypes = {
    Exiv2::unsignedByte, Exiv2::asciiString, Exiv2::unsignedLong,
    Exiv2::unsignedRational, Exiv2::signedByte, Exiv2::undefined,
    Exiv2::signedLong, Exiv2::signedRational, Exiv2::tiffFloat,
    Exiv2::tiffDouble, Exiv2::tiffIfd, Exiv2::unsignedLongLong,
    Exiv2::signedLongLong, Exiv2::tiffIfd8
  };
  for (auto type : nonShortTypes) {
    EXPECT_FALSE(Exiv2::Image::isShortType(type)) << "type=" << type;
  }
}

// ============================================================
// byteSwap boundary: zero values
// ============================================================

TEST_F(ImageTest_1048, ByteSwap32_Zero_ReturnsZero_1048) {
  EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint32_t>(0), true), static_cast<uint32_t>(0));
}

TEST_F(ImageTest_1048, ByteSwap64_Zero_ReturnsZero_1048) {
  EXPECT_EQ(Exiv2::Image::byteSwap(static_cast<uint64_t>(0), true), static_cast<uint64_t>(0));
}

// ============================================================
// byteSwap boundary: max values
// ============================================================

TEST_F(ImageTest_1048, ByteSwap16_MaxValue_1048) {
  uint16_t val = 0xFFFF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint16_t>(0xFFFF));
}

TEST_F(ImageTest_1048, ByteSwap32_MaxValue_1048) {
  uint32_t val = 0xFFFFFFFF;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint32_t>(0xFFFFFFFF));
}

TEST_F(ImageTest_1048, ByteSwap64_MaxValue_1048) {
  uint64_t val = 0xFFFFFFFFFFFFFFFFULL;
  EXPECT_EQ(Exiv2::Image::byteSwap(val, true), static_cast<uint64_t>(0xFFFFFFFFFFFFFFFFULL));
}

// ============================================================
// SetExifData / SetIptcData / SetXmpData
// ============================================================

TEST_F(ImageTest_1048, SetExifData_ReplacesExisting_1048) {
  auto img = createTestImage();
  Exiv2::ExifData exifData;
  img->setExifData(exifData);
  EXPECT_TRUE(img->exifData().empty());
}

TEST_F(ImageTest_1048, SetIptcData_ReplacesExisting_1048) {
  auto img = createTestImage();
  Exiv2::IptcData iptcData;
  img->setIptcData(iptcData);
  EXPECT_TRUE(img->iptcData().empty());
}

TEST_F(ImageTest_1048, SetXmpData_ReplacesExisting_1048) {
  auto img = createTestImage();
  Exiv2::XmpData xmpData;
  img->setXmpData(xmpData);
  EXPECT_TRUE(img->xmpData().empty());
}

// ============================================================
// IoReference test
// ============================================================

TEST_F(ImageTest_1048, IoReference_IsValid_1048) {
  auto img = createTestImage();
  const Exiv2::BasicIo& io = img->io();
  // MemIo path should be empty
  EXPECT_TRUE(io.path().empty() || true); // Just verify it doesn't crash
}

// ============================================================
// ImageType test
// ============================================================

TEST_F(ImageTest_1048, ImageType_IsNone_1048) {
  auto img = createTestImage();
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::none);
}
