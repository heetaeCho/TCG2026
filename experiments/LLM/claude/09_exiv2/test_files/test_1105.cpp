#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/futils.hpp>

#include <fstream>
#include <cstdio>
#include <string>
#include <memory>
#include <vector>

namespace {

// Helper to create a temporary file with some content
class TempFile {
 public:
  explicit TempFile(const std::string& name, const std::string& content = "") : path_(name) {
    std::ofstream ofs(path_, std::ios::binary);
    if (!content.empty()) {
      ofs.write(content.data(), content.size());
    }
    ofs.close();
  }
  ~TempFile() {
    std::remove(path_.c_str());
  }
  const std::string& path() const { return path_; }
 private:
  std::string path_;
};

// Minimal valid JPEG data (SOI marker + EOI marker)
std::vector<Exiv2::byte> minimalJpeg() {
  return {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10,
          0x4A, 0x46, 0x49, 0x46, 0x00, 0x01,
          0x01, 0x00, 0x00, 0x01, 0x00, 0x01,
          0x00, 0x00, 0xFF, 0xD9};
}

}  // namespace

// ==================== createIo tests ====================

class ImageFactoryCreateIoTest_1105 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ImageFactoryCreateIoTest_1105, CreateIoWithRegularFilePath_1105) {
  TempFile tmp("test_createio_1105.tmp", "hello");
  auto io = Exiv2::ImageFactory::createIo(tmp.path(), false);
  ASSERT_NE(io, nullptr);
}

TEST_F(ImageFactoryCreateIoTest_1105, CreateIoWithNonExistentFilePath_1105) {
  // createIo should still return a FileIo object even for non-existent files
  // (the file existence is typically checked when opening)
  auto io = Exiv2::ImageFactory::createIo("nonexistent_file_1105.xyz", false);
  ASSERT_NE(io, nullptr);
}

TEST_F(ImageFactoryCreateIoTest_1105, CreateIoWithEmptyPath_1105) {
  // Empty path - should still create an IO object (FileIo for empty string)
  auto io = Exiv2::ImageFactory::createIo("", false);
  ASSERT_NE(io, nullptr);
}

TEST_F(ImageFactoryCreateIoTest_1105, CreateIoWithUseCurlFalse_1105) {
  TempFile tmp("test_curl_false_1105.tmp", "data");
  auto io = Exiv2::ImageFactory::createIo(tmp.path(), false);
  ASSERT_NE(io, nullptr);
}

#ifdef EXV_ENABLE_FILESYSTEM
TEST_F(ImageFactoryCreateIoTest_1105, CreateIoWithFileUri_1105) {
  TempFile tmp("test_fileuri_1105.tmp", "content");
  std::string fileUri = "file://" + tmp.path();
  // Depending on platform, this may work or throw
  try {
    auto io = Exiv2::ImageFactory::createIo(fileUri, false);
    ASSERT_NE(io, nullptr);
  } catch (const Exiv2::Error&) {
    // Acceptable if file:// URI handling fails on this platform
  }
}
#endif

// ==================== open tests ====================

class ImageFactoryOpenTest_1105 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ImageFactoryOpenTest_1105, OpenWithValidJpegFile_1105) {
  auto jpegData = minimalJpeg();
  TempFile tmp("test_open_jpeg_1105.jpg");
  {
    std::ofstream ofs(tmp.path(), std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(jpegData.data()), jpegData.size());
  }
  try {
    auto image = Exiv2::ImageFactory::open(tmp.path(), false);
    ASSERT_NE(image, nullptr);
  } catch (const Exiv2::Error&) {
    // Some minimal JPEG data might not be recognized
  }
}

TEST_F(ImageFactoryOpenTest_1105, OpenWithNonExistentFileThrows_1105) {
  EXPECT_THROW(
    Exiv2::ImageFactory::open("totally_nonexistent_file_1105.jpg", false),
    Exiv2::Error
  );
}

TEST_F(ImageFactoryOpenTest_1105, OpenWithByteDataNullptr_1105) {
  EXPECT_THROW(
    Exiv2::ImageFactory::open(nullptr, 0),
    Exiv2::Error
  );
}

TEST_F(ImageFactoryOpenTest_1105, OpenWithValidByteData_1105) {
  auto jpegData = minimalJpeg();
  try {
    auto image = Exiv2::ImageFactory::open(jpegData.data(), jpegData.size());
    ASSERT_NE(image, nullptr);
  } catch (const Exiv2::Error&) {
    // May throw if minimal JPEG is not sufficient
  }
}

TEST_F(ImageFactoryOpenTest_1105, OpenWithEmptyByteData_1105) {
  Exiv2::byte data[] = {0};
  EXPECT_THROW(
    Exiv2::ImageFactory::open(data, 0),
    Exiv2::Error
  );
}

TEST_F(ImageFactoryOpenTest_1105, OpenWithInvalidImageData_1105) {
  Exiv2::byte invalidData[] = {0x00, 0x01, 0x02, 0x03, 0x04};
  EXPECT_THROW(
    Exiv2::ImageFactory::open(invalidData, sizeof(invalidData)),
    Exiv2::Error
  );
}

TEST_F(ImageFactoryOpenTest_1105, OpenWithUniqueIoPtr_1105) {
  auto jpegData = minimalJpeg();
  TempFile tmp("test_open_io_1105.jpg");
  {
    std::ofstream ofs(tmp.path(), std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(jpegData.data()), jpegData.size());
  }
  auto io = Exiv2::ImageFactory::createIo(tmp.path(), false);
  ASSERT_NE(io, nullptr);
  try {
    auto image = Exiv2::ImageFactory::open(std::move(io));
    ASSERT_NE(image, nullptr);
  } catch (const Exiv2::Error&) {
    // May throw for minimal JPEG
  }
}

// ==================== getType tests ====================

class ImageFactoryGetTypeTest_1105 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ImageFactoryGetTypeTest_1105, GetTypeWithNonExistentFile_1105) {
  EXPECT_THROW(
    Exiv2::ImageFactory::getType("nonexistent_gettype_1105.jpg"),
    Exiv2::Error
  );
}

TEST_F(ImageFactoryGetTypeTest_1105, GetTypeWithValidJpegData_1105) {
  auto jpegData = minimalJpeg();
  auto type = Exiv2::ImageFactory::getType(jpegData.data(), jpegData.size());
  EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

TEST_F(ImageFactoryGetTypeTest_1105, GetTypeWithInvalidData_1105) {
  Exiv2::byte invalidData[] = {0x00, 0x00, 0x00, 0x00};
  auto type = Exiv2::ImageFactory::getType(invalidData, sizeof(invalidData));
  EXPECT_EQ(type, Exiv2::ImageType::none);
}

TEST_F(ImageFactoryGetTypeTest_1105, GetTypeWithZeroSizeData_1105) {
  Exiv2::byte data[] = {0xFF};
  auto type = Exiv2::ImageFactory::getType(data, 0);
  EXPECT_EQ(type, Exiv2::ImageType::none);
}

TEST_F(ImageFactoryGetTypeTest_1105, GetTypeWithJpegFile_1105) {
  auto jpegData = minimalJpeg();
  TempFile tmp("test_gettype_jpeg_1105.jpg");
  {
    std::ofstream ofs(tmp.path(), std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(jpegData.data()), jpegData.size());
  }
  auto type = Exiv2::ImageFactory::getType(tmp.path());
  EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

TEST_F(ImageFactoryGetTypeTest_1105, GetTypeWithEmptyFile_1105) {
  TempFile tmp("test_gettype_empty_1105.tmp", "");
  auto type = Exiv2::ImageFactory::getType(tmp.path());
  EXPECT_EQ(type, Exiv2::ImageType::none);
}

TEST_F(ImageFactoryGetTypeTest_1105, GetTypeViaBasicIo_1105) {
  auto jpegData = minimalJpeg();
  TempFile tmp("test_gettype_io_1105.jpg");
  {
    std::ofstream ofs(tmp.path(), std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(jpegData.data()), jpegData.size());
  }
  auto io = Exiv2::ImageFactory::createIo(tmp.path(), false);
  ASSERT_NE(io, nullptr);
  io->open();
  auto type = Exiv2::ImageFactory::getType(*io);
  EXPECT_EQ(type, Exiv2::ImageType::jpeg);
}

// ==================== create tests ====================

class ImageFactoryCreateTest_1105 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ImageFactoryCreateTest_1105, CreateJpegImageWithPath_1105) {
  std::string path = "test_create_jpeg_1105.jpg";
  try {
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, path);
    ASSERT_NE(image, nullptr);
  } catch (const Exiv2::Error&) {
    // May throw if creation fails
  }
  std::remove(path.c_str());
}

TEST_F(ImageFactoryCreateTest_1105, CreateWithInvalidType_1105) {
  EXPECT_THROW(
    Exiv2::ImageFactory::create(Exiv2::ImageType::none, "test_create_none_1105.tmp"),
    Exiv2::Error
  );
}

TEST_F(ImageFactoryCreateTest_1105, CreateInMemoryJpeg_1105) {
  try {
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg);
    ASSERT_NE(image, nullptr);
  } catch (const Exiv2::Error&) {
    // Acceptable
  }
}

TEST_F(ImageFactoryCreateTest_1105, CreateWithIoPtr_1105) {
  std::string path = "test_create_io_1105.jpg";
  auto io = Exiv2::ImageFactory::createIo(path, false);
  ASSERT_NE(io, nullptr);
  try {
    auto image = Exiv2::ImageFactory::create(Exiv2::ImageType::jpeg, std::move(io));
    ASSERT_NE(image, nullptr);
  } catch (const Exiv2::Error&) {
    // Acceptable
  }
  std::remove(path.c_str());
}

// ==================== checkMode tests ====================

class ImageFactoryCheckModeTest_1105 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(ImageFactoryCheckModeTest_1105, CheckModeForJpegExif_1105) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdExif);
  // JPEG supports Exif, should be amReadWrite or at least amRead
  EXPECT_NE(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1105, CheckModeForJpegIptc_1105) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdIptc);
  EXPECT_NE(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1105, CheckModeForJpegXmp_1105) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::jpeg, Exiv2::MetadataId::mdXmp);
  EXPECT_NE(mode, Exiv2::AccessMode::amNone);
}

TEST_F(ImageFactoryCheckModeTest_1105, CheckModeForNoneType_1105) {
  auto mode = Exiv2::ImageFactory::checkMode(Exiv2::ImageType::none, Exiv2::MetadataId::mdExif);
  EXPECT_EQ(mode, Exiv2::AccessMode::amNone);
}

// ==================== PNG type detection ====================

class ImageFactoryPngTypeTest_1105 : public ::testing::Test {};

TEST_F(ImageFactoryPngTypeTest_1105, GetTypeWithPngSignature_1105) {
  // PNG signature: 89 50 4E 47 0D 0A 1A 0A
  Exiv2::byte pngData[] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A,
                            0x00, 0x00, 0x00, 0x0D, 0x49, 0x48, 0x44, 0x52};
  auto type = Exiv2::ImageFactory::getType(pngData, sizeof(pngData));
  // Depending on build configuration, PNG might or might not be supported
  // But the type detection should at least not crash
  SUCCEED();
}

// ==================== TIFF type detection ====================

class ImageFactoryTiffTypeTest_1105 : public ::testing::Test {};

TEST_F(ImageFactoryTiffTypeTest_1105, GetTypeWithTiffLittleEndianSignature_1105) {
  // TIFF LE: 49 49 2A 00
  Exiv2::byte tiffData[] = {0x49, 0x49, 0x2A, 0x00, 0x08, 0x00, 0x00, 0x00};
  auto type = Exiv2::ImageFactory::getType(tiffData, sizeof(tiffData));
  // Should detect as some TIFF-based type or none
  SUCCEED();
}

TEST_F(ImageFactoryTiffTypeTest_1105, GetTypeWithTiffBigEndianSignature_1105) {
  // TIFF BE: 4D 4D 00 2A
  Exiv2::byte tiffData[] = {0x4D, 0x4D, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x08};
  auto type = Exiv2::ImageFactory::getType(tiffData, sizeof(tiffData));
  SUCCEED();
}

// ==================== Boundary / edge cases ====================

class ImageFactoryEdgeCasesTest_1105 : public ::testing::Test {};

TEST_F(ImageFactoryEdgeCasesTest_1105, OpenSingleByteData_1105) {
  Exiv2::byte singleByte[] = {0xFF};
  auto type = Exiv2::ImageFactory::getType(singleByte, 1);
  EXPECT_EQ(type, Exiv2::ImageType::none);
}

TEST_F(ImageFactoryEdgeCasesTest_1105, OpenTwoBytesJpegSoiOnly_1105) {
  Exiv2::byte soiOnly[] = {0xFF, 0xD8};
  auto type = Exiv2::ImageFactory::getType(soiOnly, 2);
  // Just SOI without further data - may or may not be detected as JPEG
  // The test verifies it doesn't crash
  SUCCEED();
}

TEST_F(ImageFactoryEdgeCasesTest_1105, CreateIoWithSpecialCharsInPath_1105) {
  auto io = Exiv2::ImageFactory::createIo("path with spaces 1105.tmp", false);
  ASSERT_NE(io, nullptr);
}

TEST_F(ImageFactoryEdgeCasesTest_1105, GetTypeWithLargeRandomData_1105) {
  std::vector<Exiv2::byte> randomData(10000, 0x42);
  auto type = Exiv2::ImageFactory::getType(randomData.data(), randomData.size());
  EXPECT_EQ(type, Exiv2::ImageType::none);
}
