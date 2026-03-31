#include <gtest/gtest.h>
#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/image_types.hpp>
#include <exiv2/error.hpp>

#include <cstring>
#include <fstream>
#include <vector>

namespace {

class ImageFactoryTest_1111 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// =============================================================================
// Tests for ImageFactory::create(ImageType, BasicIo::UniquePtr)
// =============================================================================

TEST_F(ImageFactoryTest_1111, CreateWithNoneTypeReturnsNull_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::none, std::move(io));
  EXPECT_EQ(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateJpegTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateExvTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateCr2TypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::cr2, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateCrwTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::crw, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateTiffTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::tiff, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreatePngTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::png, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateWebPTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::webp, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateBmpTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::bmp, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateGifTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::gif, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateXmpTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::xmp, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreatePsdTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::psd, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateJp2TypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jp2, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateDngTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::dng, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateEpsTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::eps, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateMrwTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::mrw, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateNefTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::nef, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateOrfTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::orf, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreatePefTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::pef, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateRafTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::raf, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateRw2TypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::rw2, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateTgaTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::tga, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateArwTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::arw, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateSr2TypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::sr2, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateSrwTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::srw, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreatePgfTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::pgf, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateBmffTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::bmff, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateQTimeTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::qtime, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateAsfTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::asf, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateRiffTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::riff, std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateMkvTypeReturnsValidImage_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::mkv, std::move(io));
  EXPECT_NE(image, nullptr);
}

// =============================================================================
// Tests for ImageFactory::create(ImageType) - MemIo variant
// =============================================================================

TEST_F(ImageFactoryTest_1111, CreateNoIoJpegReturnsValidImage_1111) {
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg);
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, CreateNoIoNoneReturnsNull_1111) {
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::none);
  EXPECT_EQ(image, nullptr);
}

// =============================================================================
// Tests for ImageFactory::checkMode
// =============================================================================

TEST_F(ImageFactoryTest_1111, CheckModeJpegExifReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeJpegIptcReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdIptc);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeJpegXmpReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdXmp);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeJpegCommentReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeCrwIptcReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::crw, Exiv2::MetadataId::mdIptc);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeCrwXmpReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::crw, Exiv2::MetadataId::mdXmp);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeCrwCommentReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::crw, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeGifExifReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::gif, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeGifIptcReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::gif, Exiv2::MetadataId::mdIptc);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeEpsExifReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::eps, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeEpsXmpReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::eps, Exiv2::MetadataId::mdXmp);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeMrwExifReturnsRead_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::mrw, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryTest_1111, CheckModeRw2ExifReturnsRead_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::rw2, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryTest_1111, CheckModeNoneTypeReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::none, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeTiffExifReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::tiff, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeTiffCommentReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::tiff, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeWebpExifReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::webp, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeWebpIptcReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::webp, Exiv2::MetadataId::mdIptc);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeWebpXmpReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::webp, Exiv2::MetadataId::mdXmp);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

// =============================================================================
// Tests for ImageFactory::open with byte data
// =============================================================================

TEST_F(ImageFactoryTest_1111, OpenFromJpegBytesReturnsValidImage_1111) {
  // Minimal JPEG: SOI marker
  const Exiv2::byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                                   0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
                                   0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
                                   0x00, 0x00, 0xFF, 0xD9};
  auto image = Exiv2::ImageFactory::open(jpegData, sizeof(jpegData));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, OpenFromEmptyDataThrows_1111) {
  const Exiv2::byte emptyData[] = {0x00};
  EXPECT_THROW(Exiv2::ImageFactory::open(emptyData, 0), Exiv2::Error);
}

TEST_F(ImageFactoryTest_1111, OpenFromNullDataThrows_1111) {
  EXPECT_THROW(Exiv2::ImageFactory::open(nullptr, 0), Exiv2::Error);
}

TEST_F(ImageFactoryTest_1111, OpenFromInvalidDataThrows_1111) {
  const Exiv2::byte invalidData[] = {0x00, 0x01, 0x02, 0x03};
  EXPECT_THROW(Exiv2::ImageFactory::open(invalidData, sizeof(invalidData)), Exiv2::Error);
}

// =============================================================================
// Tests for ImageFactory::getType with byte data
// =============================================================================

TEST_F(ImageFactoryTest_1111, GetTypeFromJpegBytesReturnsJpeg_1111) {
  const Exiv2::byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                                   0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
                                   0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
                                   0x00, 0x00, 0xFF, 0xD9};
  auto type = Exiv2::ImageFactory::getType(jpegData, sizeof(jpegData));
  EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

TEST_F(ImageFactoryTest_1111, GetTypeFromInvalidDataReturnsNone_1111) {
  const Exiv2::byte invalidData[] = {0x00, 0x01, 0x02, 0x03};
  auto type = Exiv2::ImageFactory::getType(invalidData, sizeof(invalidData));
  EXPECT_EQ(type, Exiv2::ImageType::none);
}

TEST_F(ImageFactoryTest_1111, GetTypeFromPngBytesReturnsPng_1111) {
  // PNG signature
  const Exiv2::byte pngData[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
                                  0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52};
  auto type = Exiv2::ImageFactory::getType(pngData, sizeof(pngData));
  EXPECT_EQ(type, Exiv2::ImageType::png);
}

// =============================================================================
// Tests for ImageFactory::open with BasicIo::UniquePtr
// =============================================================================

TEST_F(ImageFactoryTest_1111, OpenFromMemIoWithJpegData_1111) {
  const Exiv2::byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                                   0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
                                   0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
                                   0x00, 0x00, 0xFF, 0xD9};
  auto io = std::make_unique<Exiv2::MemIo>(jpegData, sizeof(jpegData));
  auto image = Exiv2::ImageFactory::open(std::move(io));
  EXPECT_NE(image, nullptr);
}

TEST_F(ImageFactoryTest_1111, OpenFromMemIoWithInvalidDataThrows_1111) {
  const Exiv2::byte invalidData[] = {0x00, 0x01, 0x02, 0x03};
  auto io = std::make_unique<Exiv2::MemIo>(invalidData, sizeof(invalidData));
  EXPECT_THROW(Exiv2::ImageFactory::open(std::move(io)), Exiv2::Error);
}

// =============================================================================
// Tests for bigtiff type - which is not in registry
// =============================================================================

TEST_F(ImageFactoryTest_1111, CreateBigtiffTypeReturnsNull_1111) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::bigtiff, std::move(io));
  // bigtiff is not in the registry, so should return null
  EXPECT_EQ(image, nullptr);
}

// =============================================================================
// Tests for all registered types support checks
// =============================================================================

TEST_F(ImageFactoryTest_1111, CheckModePngCommentReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::png, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModePgfCommentReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::pgf, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeBmffExifReturnsRead_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmff, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryTest_1111, CheckModeBmffCommentReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmff, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeQtimeExifReturnsRead_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::qtime, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryTest_1111, CheckModeQtimeIptcReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::qtime, Exiv2::MetadataId::mdIptc);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeAsfExifReturnsRead_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::asf, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryTest_1111, CheckModeRiffExifReturnsRead_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::riff, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryTest_1111, CheckModeMkvExifReturnsRead_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::mkv, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryTest_1111, CheckModeBmpExifReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmp, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeTgaExifReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::tga, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModePsdExifReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::psd, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModePsdCommentReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::psd, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryTest_1111, CheckModeJp2ExifReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jp2, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeJp2CommentReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jp2, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

// =============================================================================
// Tests for getType with MemIo (BasicIo&)
// =============================================================================

TEST_F(ImageFactoryTest_1111, GetTypeFromMemIoJpegReturnsJpeg_1111) {
  const Exiv2::byte jpegData[] = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                                   0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
                                   0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
                                   0x00, 0x00, 0xFF, 0xD9};
  Exiv2::MemIo io(jpegData, sizeof(jpegData));
  auto type = Exiv2::ImageFactory::getType(io);
  EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

TEST_F(ImageFactoryTest_1111, GetTypeFromMemIoInvalidReturnsNone_1111) {
  const Exiv2::byte invalidData[] = {0x00, 0x01, 0x02, 0x03};
  Exiv2::MemIo io(invalidData, sizeof(invalidData));
  auto type = Exiv2::ImageFactory::getType(io);
  EXPECT_EQ(type, Exiv2::ImageType::none);
}

// =============================================================================
// Tests for ImageFactory::create(ImageType, const std::string&)
// =============================================================================

TEST_F(ImageFactoryTest_1111, CreateWithPathJpegReturnsValidImage_1111) {
  std::string tmpPath = "test_create_1111.jpg";
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, tmpPath);
  EXPECT_NE(image, nullptr);
  // Cleanup
  std::remove(tmpPath.c_str());
}

TEST_F(ImageFactoryTest_1111, CreateWithPathNoneReturnsNull_1111) {
  std::string tmpPath = "test_create_none_1111.bin";
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::none, tmpPath);
  EXPECT_EQ(image, nullptr);
  // Cleanup just in case
  std::remove(tmpPath.c_str());
}

// =============================================================================
// Test for Cr2 specific access modes
// =============================================================================

TEST_F(ImageFactoryTest_1111, CheckModeCr2ExifReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::cr2, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeCr2CommentReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::cr2, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

// =============================================================================
// Test for Raf specific access modes
// =============================================================================

TEST_F(ImageFactoryTest_1111, CheckModeRafExifReturnsRead_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::raf, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryTest_1111, CheckModeRafCommentReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::raf, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

// =============================================================================
// Test for Xmp specific access modes
// =============================================================================

TEST_F(ImageFactoryTest_1111, CheckModeXmpExifReturnsReadWrite_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::xmp, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryTest_1111, CheckModeXmpCommentReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::xmp, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

// =============================================================================
// Test bigtiff is not in registry for checkMode
// =============================================================================

TEST_F(ImageFactoryTest_1111, CheckModeBigtiffReturnsNone_1111) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bigtiff, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

}  // namespace
