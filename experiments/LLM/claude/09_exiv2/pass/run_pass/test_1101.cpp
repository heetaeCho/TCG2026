#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <fstream>
#include <cstring>
#include <vector>
#include <filesystem>

namespace {

// Helper function to create a temporary file with given content
class TempFile {
 public:
  TempFile(const std::string& name, const std::vector<Exiv2::byte>& data)
      : path_(std::filesystem::temp_directory_path() / name) {
    std::ofstream ofs(path_, std::ios::binary);
    if (!data.empty()) {
      ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    }
  }
  ~TempFile() {
    std::filesystem::remove(path_);
  }
  std::string path() const { return path_.string(); }

 private:
  std::filesystem::path path_;
};

// JPEG magic bytes: FF D8 FF
std::vector<Exiv2::byte> makeJpegData() {
  std::vector<Exiv2::byte> data = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
                                    'J',  'F',  'I',  'F',  0x00, 0x01,
                                    0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
                                    0x00, 0x00};
  return data;
}

// PNG magic bytes
std::vector<Exiv2::byte> makePngData() {
  std::vector<Exiv2::byte> data = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
                                    // IHDR chunk
                                    0x00, 0x00, 0x00, 0x0D, 'I', 'H', 'D', 'R',
                                    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01,
                                    0x08, 0x02, 0x00, 0x00, 0x00, 0x90, 0x77, 0x53,
                                    0xDE};
  return data;
}

// GIF magic bytes
std::vector<Exiv2::byte> makeGifData() {
  std::vector<Exiv2::byte> data = {'G', 'I', 'F', '8', '9', 'a',
                                    0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
  return data;
}

// TIFF magic bytes (little-endian)
std::vector<Exiv2::byte> makeTiffData() {
  std::vector<Exiv2::byte> data = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00,
                                    0x00, 0x00};
  return data;
}

}  // namespace

// ==================== checkType Tests ====================

class ImageFactoryCheckTypeTest_1101 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypeJpegWithJpegData_1101) {
  auto jpegData = makeJpegData();
  auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false);
  EXPECT_TRUE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypeJpegWithNonJpegData_1101) {
  auto pngData = makePngData();
  auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false);
  EXPECT_FALSE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypePngWithPngData_1101) {
  auto pngData = makePngData();
  auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::png, *io, false);
  EXPECT_TRUE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypePngWithJpegData_1101) {
  auto jpegData = makeJpegData();
  auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::png, *io, false);
  EXPECT_FALSE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypeGifWithGifData_1101) {
  auto gifData = makeGifData();
  auto io = std::make_unique<Exiv2::MemIo>(gifData.data(), gifData.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::gif, *io, false);
  EXPECT_TRUE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypeWithEmptyData_1101) {
  auto io = std::make_unique<Exiv2::MemIo>();
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false);
  EXPECT_FALSE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypeWithRandomData_1101) {
  std::vector<Exiv2::byte> randomData = {0x01, 0x02, 0x03, 0x04, 0x05};
  auto io = std::make_unique<Exiv2::MemIo>(randomData.data(), randomData.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false);
  EXPECT_FALSE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypeTiffWithTiffData_1101) {
  auto tiffData = makeTiffData();
  auto io = std::make_unique<Exiv2::MemIo>(tiffData.data(), tiffData.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::tiff, *io, false);
  EXPECT_TRUE(result);
}

// ==================== checkMode Tests ====================

class ImageFactoryCheckModeTest_1101 : public ::testing::Test {};

TEST_F(ImageFactoryCheckModeTest_1101, JpegExifSupport_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, JpegIptcSupport_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdIptc);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, JpegXmpSupport_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdXmp);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, JpegCommentSupport_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, MrwExifIsReadOnly_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::mrw, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryCheckModeTest_1101, GifExifIsNone_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::gif, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1101, GifCommentIsNone_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::gif, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1101, CrwIptcIsNone_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::crw, Exiv2::MetadataId::mdIptc);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1101, CrwCommentIsReadWrite_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::crw, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, EpsExifIsNone_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::eps, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1101, EpsXmpIsReadWrite_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::eps, Exiv2::MetadataId::mdXmp);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, BmpExifIsNone_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmp, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1101, WebpExifIsReadWrite_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::webp, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, WebpIptcIsNone_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::webp, Exiv2::MetadataId::mdIptc);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

// ==================== getType Tests ====================

class ImageFactoryGetTypeTest_1101 : public ::testing::Test {};

TEST_F(ImageFactoryGetTypeTest_1101, GetTypeFromJpegMemory_1101) {
  auto jpegData = makeJpegData();
  auto type = Exiv2::ImageFactory::getType(jpegData.data(), jpegData.size());
  EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

TEST_F(ImageFactoryGetTypeTest_1101, GetTypeFromPngMemory_1101) {
  auto pngData = makePngData();
  auto type = Exiv2::ImageFactory::getType(pngData.data(), pngData.size());
  EXPECT_EQ(type, Exiv2::ImageType::png);
}

TEST_F(ImageFactoryGetTypeTest_1101, GetTypeFromGifMemory_1101) {
  auto gifData = makeGifData();
  auto type = Exiv2::ImageFactory::getType(gifData.data(), gifData.size());
  EXPECT_EQ(type, Exiv2::ImageType::gif);
}

TEST_F(ImageFactoryGetTypeTest_1101, GetTypeFromTiffMemory_1101) {
  auto tiffData = makeTiffData();
  auto type = Exiv2::ImageFactory::getType(tiffData.data(), tiffData.size());
  EXPECT_EQ(type, Exiv2::ImageType::tiff);
}

TEST_F(ImageFactoryGetTypeTest_1101, GetTypeFromBasicIoJpeg_1101) {
  auto jpegData = makeJpegData();
  Exiv2::MemIo io(jpegData.data(), jpegData.size());
  auto type = Exiv2::ImageFactory::getType(io);
  EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

TEST_F(ImageFactoryGetTypeTest_1101, GetTypeFromEmptyMemory_1101) {
  std::vector<Exiv2::byte> emptyData;
  // With empty data, it should not match any type
  // This might throw or return none; we test for no crash
  EXPECT_NO_THROW({
    try {
      auto type = Exiv2::ImageFactory::getType(emptyData.data(), emptyData.size());
      EXPECT_EQ(type, Exiv2::ImageType::none);
    } catch (const Exiv2::Error&) {
      // Acceptable behavior
    }
  });
}

TEST_F(ImageFactoryGetTypeTest_1101, GetTypeFromRandomBytes_1101) {
  std::vector<Exiv2::byte> randomData = {0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x01, 0x02};
  try {
    auto type = Exiv2::ImageFactory::getType(randomData.data(), randomData.size());
    EXPECT_EQ(type, Exiv2::ImageType::none);
  } catch (const Exiv2::Error&) {
    // Also acceptable
  }
}

// ==================== open Tests ====================

class ImageFactoryOpenTest_1101 : public ::testing::Test {};

TEST_F(ImageFactoryOpenTest_1101, OpenJpegFromMemory_1101) {
  auto jpegData = makeJpegData();
  auto image = Exiv2::ImageFactory::open(jpegData.data(), jpegData.size());
  ASSERT_NE(image, nullptr);
}

TEST_F(ImageFactoryOpenTest_1101, OpenPngFromMemory_1101) {
  auto pngData = makePngData();
  auto image = Exiv2::ImageFactory::open(pngData.data(), pngData.size());
  ASSERT_NE(image, nullptr);
}

TEST_F(ImageFactoryOpenTest_1101, OpenFromFile_1101) {
  auto jpegData = makeJpegData();
  TempFile tmp("test_image_1101.jpg", jpegData);
  auto image = Exiv2::ImageFactory::open(tmp.path());
  ASSERT_NE(image, nullptr);
}

TEST_F(ImageFactoryOpenTest_1101, OpenNonExistentFileThrows_1101) {
  EXPECT_THROW(
      Exiv2::ImageFactory::open("/nonexistent/path/to/file_1101.jpg"),
      Exiv2::Error);
}

TEST_F(ImageFactoryOpenTest_1101, OpenFromMemIo_1101) {
  auto jpegData = makeJpegData();
  auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
  auto image = Exiv2::ImageFactory::open(std::move(io));
  ASSERT_NE(image, nullptr);
}

TEST_F(ImageFactoryOpenTest_1101, OpenEmptyDataThrows_1101) {
  std::vector<Exiv2::byte> emptyData;
  EXPECT_THROW(
      Exiv2::ImageFactory::open(emptyData.data(), emptyData.size()),
      Exiv2::Error);
}

TEST_F(ImageFactoryOpenTest_1101, OpenRandomDataThrows_1101) {
  std::vector<Exiv2::byte> randomData = {0xDE, 0xAD, 0xBE, 0xEF};
  EXPECT_THROW(
      Exiv2::ImageFactory::open(randomData.data(), randomData.size()),
      Exiv2::Error);
}

// ==================== create Tests ====================

class ImageFactoryCreateTest_1101 : public ::testing::Test {};

TEST_F(ImageFactoryCreateTest_1101, CreateJpegInMemory_1101) {
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg);
  ASSERT_NE(image, nullptr);
}

TEST_F(ImageFactoryCreateTest_1101, CreateJpegToFile_1101) {
  std::string path = (std::filesystem::temp_directory_path() / "create_test_1101.jpg").string();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, path);
  ASSERT_NE(image, nullptr);
  std::filesystem::remove(path);
}

TEST_F(ImageFactoryCreateTest_1101, CreateExvInMemory_1101) {
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::exv);
  ASSERT_NE(image, nullptr);
}

TEST_F(ImageFactoryCreateTest_1101, CreateWithMemIo_1101) {
  auto io = std::make_unique<Exiv2::MemIo>();
  auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, std::move(io));
  ASSERT_NE(image, nullptr);
}

// ==================== createIo Tests ====================

class ImageFactoryCreateIoTest_1101 : public ::testing::Test {};

TEST_F(ImageFactoryCreateIoTest_1101, CreateIoFromFilePath_1101) {
  auto jpegData = makeJpegData();
  TempFile tmp("create_io_test_1101.jpg", jpegData);
  auto io = Exiv2::ImageFactory::createIo(tmp.path());
  ASSERT_NE(io, nullptr);
}

TEST_F(ImageFactoryCreateIoTest_1101, CreateIoFromNonExistentPath_1101) {
  // createIo should still create a FileIo object even if file doesn't exist
  auto io = Exiv2::ImageFactory::createIo("/tmp/nonexistent_1101.jpg");
  ASSERT_NE(io, nullptr);
}

// ==================== checkType with advance parameter Tests ====================

class ImageFactoryCheckTypeAdvanceTest_1101 : public ::testing::Test {};

TEST_F(ImageFactoryCheckTypeAdvanceTest_1101, CheckTypeJpegAdvanceTrue_1101) {
  auto jpegData = makeJpegData();
  auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, true);
  EXPECT_TRUE(result);
}

TEST_F(ImageFactoryCheckTypeAdvanceTest_1101, CheckTypeJpegAdvanceFalse_1101) {
  auto jpegData = makeJpegData();
  auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false);
  EXPECT_TRUE(result);
}

TEST_F(ImageFactoryCheckTypeAdvanceTest_1101, CheckTypeWithAdvanceFalseDoesNotAdvance_1101) {
  auto jpegData = makeJpegData();
  auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());
  io->seek(0, Exiv2::BasicIo::beg);
  size_t posBefore = io->tell();
  Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false);
  size_t posAfter = io->tell();
  EXPECT_EQ(posBefore, posAfter);
}

// ==================== Multiple type checks on same IO ====================

class ImageFactoryMultipleCheckTest_1101 : public ::testing::Test {};

TEST_F(ImageFactoryMultipleCheckTest_1101, CheckMultipleTypesOnJpeg_1101) {
  auto jpegData = makeJpegData();
  auto io = std::make_unique<Exiv2::MemIo>(jpegData.data(), jpegData.size());

  EXPECT_TRUE(Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false));
  EXPECT_FALSE(Exiv2::ImageFactory::checkType(Exiv2::ImageType::png, *io, false));
  EXPECT_FALSE(Exiv2::ImageFactory::checkType(Exiv2::ImageType::gif, *io, false));
  EXPECT_FALSE(Exiv2::ImageFactory::checkType(Exiv2::ImageType::tiff, *io, false));
}

TEST_F(ImageFactoryMultipleCheckTest_1101, CheckMultipleTypesOnPng_1101) {
  auto pngData = makePngData();
  auto io = std::make_unique<Exiv2::MemIo>(pngData.data(), pngData.size());

  EXPECT_FALSE(Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false));
  EXPECT_TRUE(Exiv2::ImageFactory::checkType(Exiv2::ImageType::png, *io, false));
  EXPECT_FALSE(Exiv2::ImageFactory::checkType(Exiv2::ImageType::gif, *io, false));
}

// ==================== Boundary: single byte data ====================

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypeWithSingleByte_1101) {
  std::vector<Exiv2::byte> singleByte = {0xFF};
  auto io = std::make_unique<Exiv2::MemIo>(singleByte.data(), singleByte.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false);
  EXPECT_FALSE(result);
}

TEST_F(ImageFactoryCheckTypeTest_1101, CheckTypeWithTwoBytes_1101) {
  std::vector<Exiv2::byte> twoBytes = {0xFF, 0xD8};
  auto io = std::make_unique<Exiv2::MemIo>(twoBytes.data(), twoBytes.size());
  bool result = Exiv2::ImageFactory::checkType(Exiv2::ImageType::jpeg, *io, false);
  // Only 2 bytes may not be sufficient for full JPEG identification
  // (just testing it doesn't crash)
  (void)result;
}

// ==================== checkMode for various types ====================

TEST_F(ImageFactoryCheckModeTest_1101, Cr2CommentIsNone_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::cr2, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1101, Cr2ExifIsReadWrite_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::cr2, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, PgfCommentIsReadWrite_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::pgf, Exiv2::MetadataId::mdComment);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, Rw2ExifIsRead_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::rw2, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryCheckModeTest_1101, Jp2ExifIsReadWrite_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jp2, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, BmffExifIsRead_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::bmff, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryCheckModeTest_1101, PsdExifIsReadWrite_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::psd, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, TgaExifIsNone_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::tga, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1101, ArwExifIsRead_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::arw, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryCheckModeTest_1101, RafExifIsRead_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::raf, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amRead);
}

TEST_F(ImageFactoryCheckModeTest_1101, XmpExifIsReadWrite_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::xmp, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amReadWrite);
}

TEST_F(ImageFactoryCheckModeTest_1101, NoneTypeReturnsNone_1101) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::none, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}
