#include <gtest/gtest.h>
#include <exiv2/mrwimage.hpp>
#include <exiv2/error.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <memory>

class MrwImageTest_982 : public ::testing::Test {
protected:
  std::unique_ptr<Exiv2::MrwImage> createMrwImage() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::MrwImage>(std::move(io), false);
  }

  std::unique_ptr<Exiv2::MrwImage> createMrwImageWithCreate() {
    auto io = std::make_unique<Exiv2::MemIo>();
    return std::make_unique<Exiv2::MrwImage>(std::move(io), true);
  }
};

// Test that writeMetadata throws an error indicating writing is unsupported
TEST_F(MrwImageTest_982, WriteMetadataThrowsUnsupported_982) {
  auto image = createMrwImage();
  EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test that the thrown error from writeMetadata has the correct error code
TEST_F(MrwImageTest_982, WriteMetadataThrowsCorrectErrorCode_982) {
  auto image = createMrwImage();
  try {
    image->writeMetadata();
    FAIL() << "Expected Exiv2::Error to be thrown";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerWritingImageFormatUnsupported);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error but caught a different exception";
  }
}

// Test that mimeType returns the correct MIME type for MRW images
TEST_F(MrwImageTest_982, MimeTypeReturnsMrwMimeType_982) {
  auto image = createMrwImage();
  std::string mime = image->mimeType();
  EXPECT_EQ(mime, "image/x-minolta-mrw");
}

// Test that setExifData does not throw (but is effectively a no-op for MRW)
TEST_F(MrwImageTest_982, SetExifDataDoesNotThrow_982) {
  auto image = createMrwImage();
  Exiv2::ExifData exifData;
  EXPECT_NO_THROW(image->setExifData(exifData));
}

// Test that setIptcData does not throw (but is effectively a no-op for MRW)
TEST_F(MrwImageTest_982, SetIptcDataDoesNotThrow_982) {
  auto image = createMrwImage();
  Exiv2::IptcData iptcData;
  EXPECT_NO_THROW(image->setIptcData(iptcData));
}

// Test that setComment does not throw (but is effectively a no-op for MRW)
TEST_F(MrwImageTest_982, SetCommentDoesNotThrow_982) {
  auto image = createMrwImage();
  EXPECT_NO_THROW(image->setComment("test comment"));
}

// Test that setComment with empty string does not throw
TEST_F(MrwImageTest_982, SetCommentEmptyStringDoesNotThrow_982) {
  auto image = createMrwImage();
  EXPECT_NO_THROW(image->setComment(""));
}

// Test that readMetadata on empty/invalid data throws or handles gracefully
TEST_F(MrwImageTest_982, ReadMetadataOnEmptyIoThrows_982) {
  auto image = createMrwImage();
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}

// Test that pixelWidth returns 0 when no metadata is loaded
TEST_F(MrwImageTest_982, PixelWidthDefaultIsZero_982) {
  auto image = createMrwImage();
  EXPECT_EQ(image->pixelWidth(), 0u);
}

// Test that pixelHeight returns 0 when no metadata is loaded
TEST_F(MrwImageTest_982, PixelHeightDefaultIsZero_982) {
  auto image = createMrwImage();
  EXPECT_EQ(image->pixelHeight(), 0u);
}

// Test construction with create=true
TEST_F(MrwImageTest_982, ConstructWithCreateTrue_982) {
  auto image = createMrwImageWithCreate();
  EXPECT_NE(image, nullptr);
}

// Test construction with create=false
TEST_F(MrwImageTest_982, ConstructWithCreateFalse_982) {
  auto image = createMrwImage();
  EXPECT_NE(image, nullptr);
}

// Test that writeMetadata throws even after setting exif data
TEST_F(MrwImageTest_982, WriteMetadataThrowsAfterSetExifData_982) {
  auto image = createMrwImage();
  Exiv2::ExifData exifData;
  image->setExifData(exifData);
  EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test that writeMetadata throws even after setting iptc data
TEST_F(MrwImageTest_982, WriteMetadataThrowsAfterSetIptcData_982) {
  auto image = createMrwImage();
  Exiv2::IptcData iptcData;
  image->setIptcData(iptcData);
  EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test that writeMetadata throws even after setting comment
TEST_F(MrwImageTest_982, WriteMetadataThrowsAfterSetComment_982) {
  auto image = createMrwImage();
  image->setComment("test");
  EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test multiple calls to writeMetadata consistently throw
TEST_F(MrwImageTest_982, WriteMetadataMultipleCallsThrow_982) {
  auto image = createMrwImage();
  EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
  EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
  EXPECT_THROW(image->writeMetadata(), Exiv2::Error);
}

// Test reading metadata from invalid MRW data (non-MRW content)
TEST_F(MrwImageTest_982, ReadMetadataFromInvalidDataThrows_982) {
  auto io = std::make_unique<Exiv2::MemIo>();
  const unsigned char fakeData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  io->write(fakeData, sizeof(fakeData));
  auto image = std::make_unique<Exiv2::MrwImage>(std::move(io), false);
  EXPECT_THROW(image->readMetadata(), Exiv2::Error);
}
