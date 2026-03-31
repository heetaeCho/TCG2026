#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/crwimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>

#include <memory>
#include <cstring>

namespace {

class CrwImageTest_1815 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that CrwImage can be constructed with a MemIo
TEST_F(CrwImageTest_1815, ConstructWithMemIo_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  ASSERT_NO_THROW(Exiv2::CrwImage img(std::move(io), true));
}

// Test mimeType returns the expected CRW MIME type
TEST_F(CrwImageTest_1815, MimeType_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  EXPECT_EQ(img.mimeType(), "image/x-canon-crw");
}

// Test pixelWidth returns 0 for a newly created (empty) CRW image
TEST_F(CrwImageTest_1815, PixelWidthDefault_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  EXPECT_EQ(img.pixelWidth(), 0u);
}

// Test pixelHeight returns 0 for a newly created (empty) CRW image
TEST_F(CrwImageTest_1815, PixelHeightDefault_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  EXPECT_EQ(img.pixelHeight(), 0u);
}

// Test setIptcData does not throw (CRW does not support IPTC, but the call should be safe)
TEST_F(CrwImageTest_1815, SetIptcDataNoOp_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  Exiv2::IptcData iptcData;
  ASSERT_NO_THROW(img.setIptcData(iptcData));
}

// Test that exifData() returns a reference to exif data on a new image (should be empty)
TEST_F(CrwImageTest_1815, ExifDataEmpty_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  EXPECT_TRUE(img.exifData().empty());
}

// Test that iptcData() returns empty data on a new image
TEST_F(CrwImageTest_1815, IptcDataEmpty_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  EXPECT_TRUE(img.iptcData().empty());
}

// Test that comment() returns empty string on a new image
TEST_F(CrwImageTest_1815, CommentEmpty_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  EXPECT_TRUE(img.comment().empty());
}

// Test that readMetadata on empty data throws an exception
TEST_F(CrwImageTest_1815, ReadMetadataFromEmptyThrows_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test that readMetadata on invalid (non-CRW) data throws
TEST_F(CrwImageTest_1815, ReadMetadataFromInvalidDataThrows_1815) {
  const Exiv2::byte invalidData[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
  auto io = std::make_unique<Exiv2::MemIo>(invalidData, sizeof(invalidData));
  Exiv2::CrwImage img(std::move(io), false);
  EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

// Test writeMetadata on a fresh (create=true) CRW image doesn't crash
TEST_F(CrwImageTest_1815, WriteMetadataOnNewImage_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  // Writing metadata on a newly created image with no data should work
  // (it creates a new CRW structure from scratch)
  ASSERT_NO_THROW(img.writeMetadata());
}

// Test that after writeMetadata, the io has some content
TEST_F(CrwImageTest_1815, WriteMetadataProducesOutput_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  img.writeMetadata();
  EXPECT_GT(img.io().size(), 0u);
}

// Test good() returns true after construction with valid io
TEST_F(CrwImageTest_1815, GoodAfterConstruction_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  EXPECT_TRUE(img.good());
}

// Test that setExifData and then writeMetadata doesn't crash
TEST_F(CrwImageTest_1815, SetExifDataAndWrite_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  Exiv2::ExifData exifData;
  img.setExifData(exifData);
  ASSERT_NO_THROW(img.writeMetadata());
}

// Test that setComment and then writeMetadata doesn't crash
TEST_F(CrwImageTest_1815, SetCommentAndWrite_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  img.setComment("Test comment");
  EXPECT_EQ(img.comment(), "Test comment");
  ASSERT_NO_THROW(img.writeMetadata());
}

// Test clearComment
TEST_F(CrwImageTest_1815, ClearComment_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  img.setComment("Test comment");
  img.clearComment();
  EXPECT_TRUE(img.comment().empty());
}

// Test clearExifData
TEST_F(CrwImageTest_1815, ClearExifData_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  img.clearExifData();
  EXPECT_TRUE(img.exifData().empty());
}

// Test that writing metadata twice doesn't crash
TEST_F(CrwImageTest_1815, WriteMetadataTwice_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  ASSERT_NO_THROW(img.writeMetadata());
  ASSERT_NO_THROW(img.writeMetadata());
}

// Test that after writing metadata, we can read it back (roundtrip on created image)
TEST_F(CrwImageTest_1815, WriteAndReadRoundtrip_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  img.setComment("Roundtrip test");
  ASSERT_NO_THROW(img.writeMetadata());

  // After write, read it back
  ASSERT_NO_THROW(img.readMetadata());
  EXPECT_EQ(img.comment(), "Roundtrip test");
}

// Test io() accessor returns a valid reference
TEST_F(CrwImageTest_1815, IoAccessor_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  const Exiv2::BasicIo& ioRef = img.io();
  // The path for MemIo is typically empty or a default
  EXPECT_NO_THROW(ioRef.path());
}

// Test that imageType is CRW
TEST_F(CrwImageTest_1815, ImageType_1815) {
  auto io = std::make_unique<Exiv2::MemIo>();
  Exiv2::CrwImage img(std::move(io), true);
  EXPECT_EQ(img.imageType(), Exiv2::ImageType::crw);
}

}  // namespace
