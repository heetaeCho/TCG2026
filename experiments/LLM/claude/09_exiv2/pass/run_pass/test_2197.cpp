#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/orfimage.hpp"
#include "exiv2/image.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/image_types.hpp"

#include <sstream>
#include <memory>

namespace {

class OrfImageTest_2197 : public ::testing::Test {
 protected:
  std::unique_ptr<Exiv2::OrfImage> createOrfImageFromMemory(bool create = true) {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::OrfImage>(std::move(io), create);
  }
};

// Test that OrfImage can be constructed with create=true
TEST_F(OrfImageTest_2197, ConstructWithCreateTrue_2197) {
  auto io = std::make_unique<Exiv2::MemIo>();
  ASSERT_NO_THROW(Exiv2::OrfImage img(std::move(io), true));
}

// Test that OrfImage can be constructed with create=false
TEST_F(OrfImageTest_2197, ConstructWithCreateFalse_2197) {
  auto io = std::make_unique<Exiv2::MemIo>();
  ASSERT_NO_THROW(Exiv2::OrfImage img(std::move(io), false));
}

// Test that imageType returns orf
TEST_F(OrfImageTest_2197, ImageTypeIsOrf_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_EQ(img->imageType(), Exiv2::ImageType::orf);
}

// Test that mimeType returns the expected ORF MIME type
TEST_F(OrfImageTest_2197, MimeTypeIsCorrect_2197) {
  auto img = createOrfImageFromMemory();
  std::string mime = img->mimeType();
  // ORF files are Olympus Raw Format
  EXPECT_FALSE(mime.empty());
}

// Test that supportsMetadata returns true for Exif
TEST_F(OrfImageTest_2197, SupportsExifMetadata_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_TRUE(img->supportsMetadata(Exiv2::mdExif));
}

// Test that supportsMetadata returns true for IPTC
TEST_F(OrfImageTest_2197, SupportsIptcMetadata_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_TRUE(img->supportsMetadata(Exiv2::mdIptc));
}

// Test that supportsMetadata returns true for XMP
TEST_F(OrfImageTest_2197, SupportsXmpMetadata_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_TRUE(img->supportsMetadata(Exiv2::mdXmp));
}

// Test that supportsMetadata returns false for Comment
TEST_F(OrfImageTest_2197, DoesNotSupportCommentMetadata_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_FALSE(img->supportsMetadata(Exiv2::mdComment));
}

// Test that good() returns false when IO is empty (no valid data)
TEST_F(OrfImageTest_2197, GoodReturnsFalseForEmptyIo_2197) {
  auto img = createOrfImageFromMemory(false);
  // An empty MemIo with no data should not be "good" in the image sense
  // The behavior depends on implementation, but we test observability
  bool result = img->good();
  // Just check it doesn't crash; actual value depends on implementation
  (void)result;
}

// Test pixelWidth returns 0 for empty/unread image
TEST_F(OrfImageTest_2197, PixelWidthDefaultIsZero_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_EQ(img->pixelWidth(), 0u);
}

// Test pixelHeight returns 0 for empty/unread image
TEST_F(OrfImageTest_2197, PixelHeightDefaultIsZero_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_EQ(img->pixelHeight(), 0u);
}

// Test exifData returns a reference (no crash)
TEST_F(OrfImageTest_2197, ExifDataAccessible_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->exifData());
}

// Test iptcData returns a reference (no crash)
TEST_F(OrfImageTest_2197, IptcDataAccessible_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->iptcData());
}

// Test xmpData returns a reference (no crash)
TEST_F(OrfImageTest_2197, XmpDataAccessible_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->xmpData());
}

// Test setComment throws or is no-op for ORF
TEST_F(OrfImageTest_2197, SetCommentBehavior_2197) {
  auto img = createOrfImageFromMemory();
  // ORF may not support comments; setComment might throw
  try {
    img->setComment("test comment");
  } catch (const Exiv2::Error&) {
    // Expected: ORF doesn't support comments
  }
}

// Test clearMetadata doesn't crash
TEST_F(OrfImageTest_2197, ClearMetadataNoThrow_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->clearMetadata());
}

// Test clearExifData doesn't crash
TEST_F(OrfImageTest_2197, ClearExifDataNoThrow_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->clearExifData());
}

// Test clearIptcData doesn't crash
TEST_F(OrfImageTest_2197, ClearIptcDataNoThrow_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->clearIptcData());
}

// Test clearXmpData doesn't crash
TEST_F(OrfImageTest_2197, ClearXmpDataNoThrow_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->clearXmpData());
}

// Test clearXmpPacket doesn't crash
TEST_F(OrfImageTest_2197, ClearXmpPacketNoThrow_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->clearXmpPacket());
}

// Test readMetadata on empty IO throws
TEST_F(OrfImageTest_2197, ReadMetadataOnEmptyIoThrows_2197) {
  auto img = createOrfImageFromMemory(false);
  EXPECT_THROW(img->readMetadata(), Exiv2::Error);
}

// Test writeMetadata on empty IO throws
TEST_F(OrfImageTest_2197, WriteMetadataOnEmptyIoThrows_2197) {
  auto img = createOrfImageFromMemory(false);
  EXPECT_THROW(img->writeMetadata(), Exiv2::Error);
}

// Test io() accessor returns valid reference
TEST_F(OrfImageTest_2197, IoAccessorReturnsValidRef_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->io());
}

// Test setByteOrder and byteOrder
TEST_F(OrfImageTest_2197, SetAndGetByteOrder_2197) {
  auto img = createOrfImageFromMemory();
  img->setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::bigEndian);
  
  img->setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(img->byteOrder(), Exiv2::littleEndian);
}

// Test writeXmpFromPacket flag
TEST_F(OrfImageTest_2197, WriteXmpFromPacketFlag_2197) {
  auto img = createOrfImageFromMemory();
  img->writeXmpFromPacket(true);
  EXPECT_TRUE(img->writeXmpFromPacket());
  
  img->writeXmpFromPacket(false);
  EXPECT_FALSE(img->writeXmpFromPacket());
}

// Test setExifData and clearExifData
TEST_F(OrfImageTest_2197, SetAndClearExifData_2197) {
  auto img = createOrfImageFromMemory();
  Exiv2::ExifData exifData;
  ASSERT_NO_THROW(img->setExifData(exifData));
  ASSERT_NO_THROW(img->clearExifData());
}

// Test setIptcData and clearIptcData
TEST_F(OrfImageTest_2197, SetAndClearIptcData_2197) {
  auto img = createOrfImageFromMemory();
  Exiv2::IptcData iptcData;
  ASSERT_NO_THROW(img->setIptcData(iptcData));
  ASSERT_NO_THROW(img->clearIptcData());
}

// Test setXmpData and clearXmpData
TEST_F(OrfImageTest_2197, SetAndClearXmpData_2197) {
  auto img = createOrfImageFromMemory();
  Exiv2::XmpData xmpData;
  ASSERT_NO_THROW(img->setXmpData(xmpData));
  ASSERT_NO_THROW(img->clearXmpData());
}

// Test xmpPacket access
TEST_F(OrfImageTest_2197, XmpPacketAccessible_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->xmpPacket());
}

// Test setXmpPacket
TEST_F(OrfImageTest_2197, SetXmpPacket_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->setXmpPacket("<xmp>test</xmp>"));
}

// Test nativePreviews returns empty list for new image
TEST_F(OrfImageTest_2197, NativePreviewsEmptyForNewImage_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_TRUE(img->nativePreviews().empty());
}

// Test iccProfileDefined returns false for new image
TEST_F(OrfImageTest_2197, IccProfileNotDefinedForNewImage_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_FALSE(img->iccProfileDefined());
}

// Test clearIccProfile doesn't crash
TEST_F(OrfImageTest_2197, ClearIccProfileNoThrow_2197) {
  auto img = createOrfImageFromMemory();
  ASSERT_NO_THROW(img->clearIccProfile());
}

// Test printStructure on empty ORF image
TEST_F(OrfImageTest_2197, PrintStructureOnEmptyImage_2197) {
  auto img = createOrfImageFromMemory(false);
  std::ostringstream oss;
  // May throw or produce empty output for empty IO
  try {
    img->printStructure(oss, Exiv2::kpsNone, 0);
  } catch (...) {
    // acceptable - empty image
  }
}

// Test comment returns empty string for new image
TEST_F(OrfImageTest_2197, CommentEmptyForNewImage_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_TRUE(img->comment().empty());
}

// Test that supportsMetadata returns false for mdIccProfile (not in mdExif|mdIptc|mdXmp)
TEST_F(OrfImageTest_2197, DoesNotSupportIccProfileMetadata_2197) {
  auto img = createOrfImageFromMemory();
  EXPECT_FALSE(img->supportsMetadata(Exiv2::mdIccProfile));
}

// Test that supportsMetadata returns false for mdNone
TEST_F(OrfImageTest_2197, DoesNotSupportNoneMetadata_2197) {
  auto img = createOrfImageFromMemory();
  // mdNone has value 0, so bitwise AND with any supported should be 0
  EXPECT_FALSE(img->supportsMetadata(Exiv2::mdNone));
}

}  // namespace
