#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <memory>
#include <cstring>

#include "exiv2/bmffimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"
#include "exiv2/image.hpp"

using namespace Exiv2;

// A mock/fake BasicIo that we can use to construct BmffImage
// We need a minimal implementation that supports tell() and other operations
class FakeBasicIo : public BasicIo {
 public:
  FakeBasicIo() : position_(0), size_(1024) {
    data_.resize(size_, 0);
  }

  int open() override { return 0; }
  int close() override { return 0; }

  size_t write(const byte* data, size_t wcount) override { return wcount; }
  size_t write(BasicIo& src) override { return 0; }
  int putb(byte data) override { return 0; }

  DataBuf read(size_t rcount) override {
    DataBuf buf(rcount);
    return buf;
  }

  size_t read(byte* buf, size_t rcount) override {
    size_t toRead = std::min(rcount, size_ - position_);
    std::memcpy(buf, data_.data() + position_, toRead);
    position_ += toRead;
    return toRead;
  }

  int getb() override {
    if (position_ >= size_) return EOF;
    return data_[position_++];
  }

  void transfer(BasicIo& src) override {}

  int seek(int64_t offset, Position pos) override {
    switch (pos) {
      case BasicIo::beg:
        position_ = static_cast<size_t>(offset);
        break;
      case BasicIo::cur:
        position_ += static_cast<size_t>(offset);
        break;
      case BasicIo::end:
        position_ = size_ + static_cast<size_t>(offset);
        break;
    }
    return 0;
  }

  byte* mmap(bool isWriteable) override { return data_.data(); }
  int munmap() override { return 0; }

  size_t tell() const override { return position_; }
  size_t size() const override { return size_; }
  bool isopen() const override { return true; }
  int error() const override { return 0; }
  bool eof() const override { return position_ >= size_; }
  const std::string& path() const noexcept override {
    static std::string p = "fake.cr3";
    return p;
  }
  void populateFakeData() override {}

  void setPosition(size_t pos) { position_ = pos; }

 private:
  std::vector<byte> data_;
  size_t position_;
  size_t size_;
};

class BmffImageParseCr3PreviewTest_1199 : public ::testing::Test {
 protected:
  void SetUp() override {
    auto io = std::make_unique<FakeBasicIo>();
    fakeIo_ = io.get();
    // BmffImage constructor: (unique_ptr<BasicIo>, bool create, size_t max_box_depth)
    image_ = std::make_unique<BmffImage>(std::move(io), true, 100);
    // Set byte order to little endian for predictable behavior
    image_->setByteOrder(littleEndian);
  }

  // Helper to create a DataBuf with specific values at given offsets
  DataBuf createDataBuf(size_t bufSize, size_t widthOffset, uint16_t width,
                        size_t heightOffset, uint16_t height,
                        size_t sizeOffset, uint32_t size, ByteOrder endian) {
    DataBuf data(bufSize);
    // Zero out
    std::memset(data.data(0), 0, bufSize);
    data.write_uint16(widthOffset, width, endian);
    data.write_uint16(heightOffset, height, endian);
    data.write_uint32(sizeOffset, size, endian);
    return data;
  }

  FakeBasicIo* fakeIo_;
  std::unique_ptr<BmffImage> image_;
};

// Test that parseCr3Preview with version 0 adds a preview with JPEG mime type
TEST_F(BmffImageParseCr3PreviewTest_1199, Version0ProducesJpegMimeType_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;
  uint16_t width = 640;
  uint16_t height = 480;
  uint32_t previewSize = 12345;

  DataBuf data = createDataBuf(16, widthOffset, width, heightOffset, height, sizeOffset, previewSize, endian);

  std::ostringstream out;
  fakeIo_->setPosition(100);

  image_->parseCr3Preview(data, out, false, 0, widthOffset, heightOffset, sizeOffset, 50);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].mimeType_, "image/jpeg");
  EXPECT_EQ(previews[0].width_, width);
  EXPECT_EQ(previews[0].height_, height);
  EXPECT_EQ(previews[0].size_, previewSize);
  EXPECT_EQ(previews[0].position_, 150u);  // here(100) + relative_position(50)
  EXPECT_EQ(previews[0].filter_, "");
}

// Test that parseCr3Preview with version != 0 produces octet-stream mime type
TEST_F(BmffImageParseCr3PreviewTest_1199, NonZeroVersionProducesOctetStreamMimeType_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;

  DataBuf data = createDataBuf(16, widthOffset, 320, heightOffset, 240, sizeOffset, 9999, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, false, 1, widthOffset, heightOffset, sizeOffset, 0);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].mimeType_, "application/octet-stream");
}

// Test that bTrace=true produces output with width, height, size
TEST_F(BmffImageParseCr3PreviewTest_1199, TraceEnabledProducesOutput_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;
  uint16_t width = 1920;
  uint16_t height = 1080;
  uint32_t previewSize = 500000;

  DataBuf data = createDataBuf(16, widthOffset, width, heightOffset, height, sizeOffset, previewSize, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, true, 0, widthOffset, heightOffset, sizeOffset, 0);

  std::string output = out.str();
  EXPECT_NE(output.find("1920"), std::string::npos);
  EXPECT_NE(output.find("1080"), std::string::npos);
  EXPECT_NE(output.find("500000"), std::string::npos);
}

// Test that bTrace=false produces no output
TEST_F(BmffImageParseCr3PreviewTest_1199, TraceDisabledProducesNoOutput_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;

  DataBuf data = createDataBuf(16, widthOffset, 100, heightOffset, 200, sizeOffset, 300, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, false, 0, widthOffset, heightOffset, sizeOffset, 0);

  EXPECT_TRUE(out.str().empty());
}

// Test that position is correctly computed as io_->tell() + relative_position
TEST_F(BmffImageParseCr3PreviewTest_1199, PositionIsCorrectlyComputed_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;

  DataBuf data = createDataBuf(16, widthOffset, 10, heightOffset, 20, sizeOffset, 30, endian);

  std::ostringstream out;
  fakeIo_->setPosition(200);

  image_->parseCr3Preview(data, out, false, 0, widthOffset, heightOffset, sizeOffset, 300);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].position_, 500u);  // 200 + 300
}

// Test that relative_position of 0 works correctly
TEST_F(BmffImageParseCr3PreviewTest_1199, ZeroRelativePosition_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;

  DataBuf data = createDataBuf(16, widthOffset, 10, heightOffset, 20, sizeOffset, 30, endian);

  std::ostringstream out;
  fakeIo_->setPosition(42);

  image_->parseCr3Preview(data, out, false, 0, widthOffset, heightOffset, sizeOffset, 0);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].position_, 42u);
}

// Test multiple calls to parseCr3Preview accumulate previews
TEST_F(BmffImageParseCr3PreviewTest_1199, MultipleParseCr3PreviewAccumulatePreviews_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;

  DataBuf data1 = createDataBuf(16, widthOffset, 100, heightOffset, 200, sizeOffset, 300, endian);
  DataBuf data2 = createDataBuf(16, widthOffset, 400, heightOffset, 500, sizeOffset, 600, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);
  image_->parseCr3Preview(data1, out, false, 0, widthOffset, heightOffset, sizeOffset, 0);

  fakeIo_->setPosition(10);
  image_->parseCr3Preview(data2, out, false, 1, widthOffset, heightOffset, sizeOffset, 5);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 2u);

  EXPECT_EQ(previews[0].width_, 100u);
  EXPECT_EQ(previews[0].height_, 200u);
  EXPECT_EQ(previews[0].size_, 300u);
  EXPECT_EQ(previews[0].mimeType_, "image/jpeg");

  EXPECT_EQ(previews[1].width_, 400u);
  EXPECT_EQ(previews[1].height_, 500u);
  EXPECT_EQ(previews[1].size_, 600u);
  EXPECT_EQ(previews[1].mimeType_, "application/octet-stream");
  EXPECT_EQ(previews[1].position_, 15u);  // 10 + 5
}

// Test with zero width, height, and size
TEST_F(BmffImageParseCr3PreviewTest_1199, ZeroWidthHeightSize_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;

  DataBuf data = createDataBuf(16, widthOffset, 0, heightOffset, 0, sizeOffset, 0, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, false, 0, widthOffset, heightOffset, sizeOffset, 0);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].width_, 0u);
  EXPECT_EQ(previews[0].height_, 0u);
  EXPECT_EQ(previews[0].size_, 0u);
}

// Test with big endian byte order
TEST_F(BmffImageParseCr3PreviewTest_1199, BigEndianByteOrder_1199) {
  ByteOrder endian = bigEndian;
  image_->setByteOrder(bigEndian);

  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;
  uint16_t width = 1024;
  uint16_t height = 768;
  uint32_t previewSize = 100000;

  DataBuf data = createDataBuf(16, widthOffset, width, heightOffset, height, sizeOffset, previewSize, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, false, 0, widthOffset, heightOffset, sizeOffset, 0);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].width_, width);
  EXPECT_EQ(previews[0].height_, height);
  EXPECT_EQ(previews[0].size_, previewSize);
}

// Test with maximum uint16 width and height, and max uint32 size
TEST_F(BmffImageParseCr3PreviewTest_1199, MaxValues_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;
  uint16_t width = 0xFFFF;
  uint16_t height = 0xFFFF;
  uint32_t previewSize = 0xFFFFFFFF;

  DataBuf data = createDataBuf(16, widthOffset, width, heightOffset, height, sizeOffset, previewSize, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, false, 0, widthOffset, heightOffset, sizeOffset, 0);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].width_, 0xFFFF);
  EXPECT_EQ(previews[0].height_, 0xFFFF);
  EXPECT_EQ(previews[0].size_, 0xFFFFFFFF);
}

// Test with version=255 (max uint8_t) still gets octet-stream
TEST_F(BmffImageParseCr3PreviewTest_1199, Version255ProducesOctetStream_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;

  DataBuf data = createDataBuf(16, widthOffset, 100, heightOffset, 200, sizeOffset, 300, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, false, 255, widthOffset, heightOffset, sizeOffset, 0);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].mimeType_, "application/octet-stream");
}

// Test that filter_ is always empty string
TEST_F(BmffImageParseCr3PreviewTest_1199, FilterIsEmptyString_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;

  DataBuf data = createDataBuf(16, widthOffset, 100, heightOffset, 200, sizeOffset, 300, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, false, 0, widthOffset, heightOffset, sizeOffset, 0);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].filter_, "");
}

// Test with different offsets within the data buffer
TEST_F(BmffImageParseCr3PreviewTest_1199, DifferentOffsetsInDataBuf_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 4;
  size_t heightOffset = 8;
  size_t sizeOffset = 12;

  DataBuf data(20);
  std::memset(data.data(0), 0, 20);
  data.write_uint16(widthOffset, 800, endian);
  data.write_uint16(heightOffset, 600, endian);
  data.write_uint32(sizeOffset, 50000, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, false, 0, widthOffset, heightOffset, sizeOffset, 10);

  const NativePreviewList& previews = image_->nativePreviews();
  ASSERT_EQ(previews.size(), 1u);
  EXPECT_EQ(previews[0].width_, 800u);
  EXPECT_EQ(previews[0].height_, 600u);
  EXPECT_EQ(previews[0].size_, 50000u);
  EXPECT_EQ(previews[0].position_, 10u);
}

// Test trace output format contains expected pattern
TEST_F(BmffImageParseCr3PreviewTest_1199, TraceOutputContainsWidthHeightSizeLabel_1199) {
  ByteOrder endian = littleEndian;
  size_t widthOffset = 0;
  size_t heightOffset = 2;
  size_t sizeOffset = 4;

  DataBuf data = createDataBuf(16, widthOffset, 320, heightOffset, 240, sizeOffset, 1000, endian);

  std::ostringstream out;
  fakeIo_->setPosition(0);

  image_->parseCr3Preview(data, out, true, 0, widthOffset, heightOffset, sizeOffset, 0);

  std::string output = out.str();
  // The format string is "width,height,size = {},{},{}"
  EXPECT_NE(output.find("width,height,size"), std::string::npos);
  EXPECT_NE(output.find("320"), std::string::npos);
  EXPECT_NE(output.find("240"), std::string::npos);
  EXPECT_NE(output.find("1000"), std::string::npos);
}
