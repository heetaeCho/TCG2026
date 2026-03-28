#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/exif.hpp>
#include <exiv2/types.hpp>
#include <fstream>
#include <cstdio>
#include <string>

namespace {

// Helper to create a temporary file with given content
class TempFile {
 public:
  TempFile(const std::string& filename, const std::vector<uint8_t>& content)
      : filename_(filename) {
    std::ofstream ofs(filename_, std::ios::binary);
    ofs.write(reinterpret_cast<const char*>(content.data()), content.size());
    ofs.close();
  }
  ~TempFile() {
    std::remove(filename_.c_str());
  }
  const std::string& path() const { return filename_; }
 private:
  std::string filename_;
};

// Minimal JPEG data (SOI + EOI markers)
std::vector<uint8_t> makeMinimalJpeg() {
  return {0xFF, 0xD8, 0xFF, 0xD9};
}

}  // namespace

class ExifThumbTest_772 : public ::testing::Test {
 protected:
  void SetUp() override {
    exifData_ = std::make_unique<Exiv2::ExifData>();
  }

  void TearDown() override {
    exifData_.reset();
  }

  std::unique_ptr<Exiv2::ExifData> exifData_;
};

// Test: Setting JPEG thumbnail from a valid file path
TEST_F(ExifThumbTest_772, SetJpegThumbnailFromValidPath_772) {
  auto jpegData = makeMinimalJpeg();
  TempFile tmpFile("test_thumb_772.jpg", jpegData);

  Exiv2::ExifThumb thumb(*exifData_);
  EXPECT_NO_THROW(thumb.setJpegThumbnail(tmpFile.path()));
}

// Test: Setting JPEG thumbnail from a non-existent file path throws
TEST_F(ExifThumbTest_772, SetJpegThumbnailFromNonExistentPathThrows_772) {
  Exiv2::ExifThumb thumb(*exifData_);
  EXPECT_THROW(thumb.setJpegThumbnail("/non/existent/path/file_772.jpg"), Exiv2::Error);
}

// Test: Setting JPEG thumbnail from a buffer
TEST_F(ExifThumbTest_772, SetJpegThumbnailFromBuffer_772) {
  auto jpegData = makeMinimalJpeg();
  Exiv2::ExifThumb thumb(*exifData_);
  EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData.data(), jpegData.size()));
}

// Test: Setting JPEG thumbnail from buffer with zero size
TEST_F(ExifThumbTest_772, SetJpegThumbnailFromBufferZeroSize_772) {
  Exiv2::ExifThumb thumb(*exifData_);
  Exiv2::byte data = 0;
  EXPECT_NO_THROW(thumb.setJpegThumbnail(&data, 0));
}

// Test: Setting JPEG thumbnail from path with resolution parameters
TEST_F(ExifThumbTest_772, SetJpegThumbnailFromPathWithResolution_772) {
  auto jpegData = makeMinimalJpeg();
  TempFile tmpFile("test_thumb_res_772.jpg", jpegData);

  Exiv2::ExifThumb thumb(*exifData_);
  Exiv2::URational xres = {72, 1};
  Exiv2::URational yres = {72, 1};
  uint16_t unit = 2;  // inches
  EXPECT_NO_THROW(thumb.setJpegThumbnail(tmpFile.path(), xres, yres, unit));
}

// Test: Setting JPEG thumbnail from buffer with resolution parameters
TEST_F(ExifThumbTest_772, SetJpegThumbnailFromBufferWithResolution_772) {
  auto jpegData = makeMinimalJpeg();
  Exiv2::ExifThumb thumb(*exifData_);
  Exiv2::URational xres = {72, 1};
  Exiv2::URational yres = {72, 1};
  uint16_t unit = 2;
  EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit));
}

// Test: Setting JPEG thumbnail from non-existent path with resolution throws
TEST_F(ExifThumbTest_772, SetJpegThumbnailFromNonExistentPathWithResThrows_772) {
  Exiv2::ExifThumb thumb(*exifData_);
  Exiv2::URational xres = {72, 1};
  Exiv2::URational yres = {72, 1};
  uint16_t unit = 2;
  EXPECT_THROW(thumb.setJpegThumbnail("/nonexistent_772.jpg", xres, yres, unit), Exiv2::Error);
}

// Test: Erase thumbnail on empty ExifData
TEST_F(ExifThumbTest_772, EraseOnEmptyExifData_772) {
  Exiv2::ExifThumb thumb(*exifData_);
  EXPECT_NO_THROW(thumb.erase());
}

// Test: Set then erase thumbnail
TEST_F(ExifThumbTest_772, SetThenEraseThumbnail_772) {
  auto jpegData = makeMinimalJpeg();
  Exiv2::ExifThumb thumb(*exifData_);
  thumb.setJpegThumbnail(jpegData.data(), jpegData.size());
  EXPECT_NO_THROW(thumb.erase());
}

// Test: Set thumbnail from path, then set again from buffer (overwrite)
TEST_F(ExifThumbTest_772, OverwriteThumbnail_772) {
  auto jpegData1 = makeMinimalJpeg();
  TempFile tmpFile("test_thumb_overwrite_772.jpg", jpegData1);

  Exiv2::ExifThumb thumb(*exifData_);
  thumb.setJpegThumbnail(tmpFile.path());

  std::vector<uint8_t> jpegData2 = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x02, 0x00, 0x00, 0xFF, 0xD9};
  EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData2.data(), jpegData2.size()));
}

// Test: Erase called multiple times does not crash
TEST_F(ExifThumbTest_772, MultipleEraseCalls_772) {
  Exiv2::ExifThumb thumb(*exifData_);
  EXPECT_NO_THROW(thumb.erase());
  EXPECT_NO_THROW(thumb.erase());
  EXPECT_NO_THROW(thumb.erase());
}

// Test: Setting JPEG thumbnail with resolution having zero denominator
TEST_F(ExifThumbTest_772, SetJpegThumbnailZeroDenominatorResolution_772) {
  auto jpegData = makeMinimalJpeg();
  Exiv2::ExifThumb thumb(*exifData_);
  Exiv2::URational xres = {72, 0};
  Exiv2::URational yres = {72, 0};
  uint16_t unit = 2;
  // Should not crash; the library may store the values as-is
  EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit));
}

// Test: Setting JPEG thumbnail from empty file path string throws
TEST_F(ExifThumbTest_772, SetJpegThumbnailFromEmptyPathThrows_772) {
  Exiv2::ExifThumb thumb(*exifData_);
  EXPECT_THROW(thumb.setJpegThumbnail(std::string("")), Exiv2::Error);
}

// Test: Large buffer thumbnail
TEST_F(ExifThumbTest_772, SetJpegThumbnailLargeBuffer_772) {
  // Create a large but valid-ish JPEG buffer (SOI at start, EOI at end)
  std::vector<uint8_t> largeJpeg(65536, 0x00);
  largeJpeg[0] = 0xFF;
  largeJpeg[1] = 0xD8;
  largeJpeg[65534] = 0xFF;
  largeJpeg[65535] = 0xD9;

  Exiv2::ExifThumb thumb(*exifData_);
  EXPECT_NO_THROW(thumb.setJpegThumbnail(largeJpeg.data(), largeJpeg.size()));
}

// Test: Constructor with ExifData reference
TEST_F(ExifThumbTest_772, ConstructorAcceptsExifData_772) {
  EXPECT_NO_THROW(Exiv2::ExifThumb thumb(*exifData_));
}

// Test: Set thumbnail with unit = 0 (no unit)
TEST_F(ExifThumbTest_772, SetJpegThumbnailUnitZero_772) {
  auto jpegData = makeMinimalJpeg();
  Exiv2::ExifThumb thumb(*exifData_);
  Exiv2::URational xres = {300, 1};
  Exiv2::URational yres = {300, 1};
  uint16_t unit = 0;
  EXPECT_NO_THROW(thumb.setJpegThumbnail(jpegData.data(), jpegData.size(), xres, yres, unit));
}
