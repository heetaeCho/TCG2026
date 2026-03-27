// TEST_ID 1186
// File: test_psdimage_readmetadata_1186.cpp

#include <gtest/gtest.h>

#include <exiv2/psdimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <exiv2/types.hpp>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

namespace {

using Byte = unsigned char;

static void putU16BE(std::vector<Byte>& v, uint16_t x) {
  v.push_back(static_cast<Byte>((x >> 8) & 0xff));
  v.push_back(static_cast<Byte>(x & 0xff));
}

static void putU32BE(std::vector<Byte>& v, uint32_t x) {
  v.push_back(static_cast<Byte>((x >> 24) & 0xff));
  v.push_back(static_cast<Byte>((x >> 16) & 0xff));
  v.push_back(static_cast<Byte>((x >> 8) & 0xff));
  v.push_back(static_cast<Byte>(x & 0xff));
}

// Minimal PSD-like buffer matching the layout referenced in PsdImage::readMetadata()
// plus:
//  - 4 bytes: color mode data length
//  - N bytes: color mode data
//  - 4 bytes: image resources length
//  - M bytes: resources
static std::vector<Byte> makeMinimalPsd(uint32_t width,
                                       uint32_t height,
                                       uint32_t colorModeDataLen,
                                       uint32_t resourcesLen,
                                       const std::vector<Byte>& colorModeData = {},
                                       const std::vector<Byte>& resourcesData = {}) {
  std::vector<Byte> v;

  // Signature '8BPS'
  v.push_back('8');
  v.push_back('B');
  v.push_back('P');
  v.push_back('S');

  // Version = 1
  putU16BE(v, 1);

  // Reserved 6 bytes = 0
  for (int i = 0; i < 6; ++i) v.push_back(0);

  // Channels (any valid-ish value)
  putU16BE(v, 3);

  // Rows (height)
  putU32BE(v, height);

  // Columns (width)
  putU32BE(v, width);

  // Depth
  putU16BE(v, 8);

  // Mode (RGB=3)
  putU16BE(v, 3);

  // Color mode data section length
  putU32BE(v, colorModeDataLen);

  // Color mode data bytes (pad/truncate to declared length)
  for (uint32_t i = 0; i < colorModeDataLen; ++i) {
    v.push_back(i < colorModeData.size() ? colorModeData[i] : 0);
  }

  // Image resources section length
  putU32BE(v, resourcesLen);

  // Resources bytes (pad/truncate to declared length)
  for (uint32_t i = 0; i < resourcesLen; ++i) {
    v.push_back(i < resourcesData.size() ? resourcesData[i] : 0);
  }

  // Add a little extra to ensure size() > resourcesLen is true even when resourcesLen==0
  // (and generally to avoid edge behavior in IO).
  v.push_back(0);
  v.push_back(0);

  return v;
}

class FakeBasicIo final : public Exiv2::BasicIo {
 public:
  explicit FakeBasicIo(std::vector<Byte> data, std::string path = "mem.psd")
      : data_(std::move(data)), path_(std::move(path)) {}

  // Controls for testing error paths
  void setOpenResult(int r) { openResult_ = r; }
  void setSeekAlwaysFail(bool v) { seekAlwaysFail_ = v; }
  void setReadLimit(size_t maxReadableBytesTotal) { readLimit_ = maxReadableBytesTotal; }

  int open() override {
    isOpen_ = (openResult_ == 0);
    return openResult_;
  }

  int close() override {
    isOpen_ = false;
    return 0;
  }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (!isOpen_) {
      error_ = 1;
      return 0;
    }

    // Optional total-read limiter (to simulate short reads)
    if (readLimit_.has_value() && totalRead_ >= *readLimit_) {
      eof_ = true;
      return 0;
    }

    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    size_t toRead = (rcount < avail) ? rcount : avail;

    if (readLimit_.has_value()) {
      const size_t remainingLimit = (*readLimit_ > totalRead_) ? (*readLimit_ - totalRead_) : 0;
      if (toRead > remainingLimit) toRead = remainingLimit;
    }

    if (toRead == 0) {
      eof_ = true;
      return 0;
    }

    std::memcpy(buf, data_.data() + pos_, toRead);
    pos_ += toRead;
    totalRead_ += toRead;

    if (pos_ >= data_.size()) eof_ = true;
    return toRead;
  }

  int seek(int64_t offset, Position pos) override {
    if (!isOpen_) {
      error_ = 1;
      return 1;
    }
    if (seekAlwaysFail_) return 1;

    int64_t base = 0;
    switch (pos) {
      case Exiv2::BasicIo::beg:
        base = 0;
        break;
      case Exiv2::BasicIo::cur:
        base = static_cast<int64_t>(pos_);
        break;
      case Exiv2::BasicIo::end:
        base = static_cast<int64_t>(data_.size());
        break;
      default:
        return 1;
    }

    const int64_t next = base + offset;
    if (next < 0) return 1;

    pos_ = static_cast<size_t>(next);
    eof_ = (pos_ >= data_.size());
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return isOpen_; }
  const int error() override { return error_; }
  const bool eof() override { return eof_; }
  const std::string& path() override { return path_; }

 private:
  std::vector<Byte> data_;
  std::string path_;

  size_t pos_ = 0;
  bool isOpen_ = false;
  int error_ = 0;
  bool eof_ = false;

  int openResult_ = 0;
  bool seekAlwaysFail_ = false;

  size_t totalRead_ = 0;
  std::optional<size_t> readLimit_;
};

class PsdImageReadMetadataTest_1186 : public ::testing::Test {};

TEST_F(PsdImageReadMetadataTest_1186, ReadMetadata_SetsPixelDimensions_1186) {
  const uint32_t kW = 16;
  const uint32_t kH = 32;

  auto bytes = makeMinimalPsd(kW, kH, /*colorModeDataLen*/ 0, /*resourcesLen*/ 0);
  auto io = std::make_unique<FakeBasicIo>(std::move(bytes), "valid.psd");

  Exiv2::PsdImage img(std::move(io));
  EXPECT_NO_THROW(img.readMetadata());
  EXPECT_EQ(img.pixelWidth(), kW);
  EXPECT_EQ(img.pixelHeight(), kH);
}

TEST_F(PsdImageReadMetadataTest_1186, ReadMetadata_WhenOpenFails_Throws_1186) {
  auto bytes = makeMinimalPsd(1, 1, 0, 0);
  auto io = std::make_unique<FakeBasicIo>(std::move(bytes), "cantopen.psd");
  io->setOpenResult(1);  // non-zero -> open failure

  Exiv2::PsdImage img(std::move(io));
  EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

TEST_F(PsdImageReadMetadataTest_1186, ReadMetadata_WhenHeaderTooShort_Throws_1186) {
  // Provide too little data so that read(buf,26) cannot return 26.
  std::vector<Byte> bytes;
  bytes.push_back('8');
  bytes.push_back('B');
  bytes.push_back('P');
  bytes.push_back('S');  // not enough beyond this

  auto io = std::make_unique<FakeBasicIo>(std::move(bytes), "short.psd");
  Exiv2::PsdImage img(std::move(io));

  EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

TEST_F(PsdImageReadMetadataTest_1186, ReadMetadata_WhenColorModeSeekFails_Throws_1186) {
  // Declare non-zero color mode data length so readMetadata will attempt seek(cur).
  auto bytes = makeMinimalPsd(/*w*/ 10, /*h*/ 20, /*colorModeDataLen*/ 4, /*resourcesLen*/ 0,
                             /*colorModeData*/ {0, 1, 2, 3});
  auto io = std::make_unique<FakeBasicIo>(std::move(bytes), "seekfail.psd");
  io->setSeekAlwaysFail(true);

  Exiv2::PsdImage img(std::move(io));
  EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

TEST_F(PsdImageReadMetadataTest_1186, ReadMetadata_WhenResourcesLengthNotLessThanSize_Throws_1186) {
  // Force resourcesLength >= io->size() by declaring a very large resources section length
  // while keeping actual buffer small.
  auto bytes = makeMinimalPsd(/*w*/ 1, /*h*/ 1, /*colorModeDataLen*/ 0,
                             /*resourcesLen*/ 0xFFFFFFFFu);

  auto io = std::make_unique<FakeBasicIo>(std::move(bytes), "corrupt.psd");
  Exiv2::PsdImage img(std::move(io));

  EXPECT_THROW(img.readMetadata(), Exiv2::Error);
}

}  // namespace