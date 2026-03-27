// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_bmpimage_1039.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/bmpimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

namespace {

using Exiv2::byte;

// A small controllable BasicIo for black-box testing BmpImage.
// It is an external collaborator, so mocking/implementing it is allowed.
class FakeBasicIo final : public Exiv2::BasicIo {
 public:
  explicit FakeBasicIo(std::vector<byte> data, std::string path = "mem://fake.bmp")
      : data_(std::move(data)), path_(std::move(path)) {}

  // Controls
  void setOpenRc(int rc) { open_rc_ = rc; }
  void setErrorFlag(int e) { error_ = e; }
  void setEofFlag(bool e) { eof_ = e; }

  // Observability
  int openCount() const { return open_count_; }
  int closeCount() const { return close_count_; }
  bool isClosed() const { return close_count_ > 0; }

  // BasicIo overrides
  int open() override {
    ++open_count_;
    is_open_ = (open_rc_ == 0);
    return open_rc_;
  }

  int close() override {
    ++close_count_;
    is_open_ = false;
    return 0;
  }

  size_t read(byte* buf, size_t rcount) override {
    if (!buf || rcount == 0) return 0;
    if (pos_ >= data_.size()) {
      eof_ = true;
      return 0;
    }
    const size_t remain = data_.size() - pos_;
    const size_t n = std::min(remain, rcount);
    std::copy_n(data_.data() + pos_, n, buf);
    pos_ += n;
    if (pos_ >= data_.size()) eof_ = true;
    return n;
  }

  Exiv2::DataBuf read(size_t rcount) override {
    Exiv2::DataBuf buf(rcount);
    const size_t n = read(buf.data(), rcount);
    // DataBuf keeps its original size; that’s fine for our purposes.
    (void)n;
    return buf;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    size_t base = 0;
    switch (pos) {
      case Exiv2::beg:
        base = 0;
        break;
      case Exiv2::cur:
        base = pos_;
        break;
      case Exiv2::end:
        base = data_.size();
        break;
      default:
        base = pos_;
        break;
    }

    // Clamp to [0, size]
    int64_t next = static_cast<int64_t>(base) + offset;
    if (next < 0) next = 0;
    if (static_cast<size_t>(next) > data_.size()) next = static_cast<int64_t>(data_.size());
    pos_ = static_cast<size_t>(next);
    eof_ = (pos_ >= data_.size());
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return is_open_; }
  const int error() override { return error_; }
  const bool eof() override { return eof_; }
  const std::string& path() override { return path_; }

 private:
  std::vector<byte> data_;
  std::string path_;
  size_t pos_ = 0;

  int open_rc_ = 0;
  int open_count_ = 0;
  int close_count_ = 0;

  bool is_open_ = false;
  int error_ = 0;
  bool eof_ = false;
};

static void putU32LE(std::vector<byte>& v, size_t off, uint32_t val) {
  ASSERT_GE(v.size(), off + 4u);
  v[off + 0] = static_cast<byte>(val & 0xFFu);
  v[off + 1] = static_cast<byte>((val >> 8) & 0xFFu);
  v[off + 2] = static_cast<byte>((val >> 16) & 0xFFu);
  v[off + 3] = static_cast<byte>((val >> 24) & 0xFFu);
}

static std::vector<byte> makeBmpHeaderBytes(uint32_t width, uint32_t height) {
  // Minimal BMP file header + BITMAPINFOHEADER (54 bytes total)
  std::vector<byte> b(54, 0);

  // Signature "BM"
  b[0] = static_cast<byte>('B');
  b[1] = static_cast<byte>('M');

  // File size (dummy)
  putU32LE(b, 2, static_cast<uint32_t>(b.size()));

  // Pixel data offset (54)
  putU32LE(b, 10, 54);

  // DIB header size (40 = BITMAPINFOHEADER)
  putU32LE(b, 14, 40);

  // Width/Height at offsets 18/22
  putU32LE(b, 18, width);
  putU32LE(b, 22, height);

  // Planes (1) at 26..27
  b[26] = 1;
  b[27] = 0;

  // Bits per pixel (24) at 28..29
  b[28] = 24;
  b[29] = 0;

  // Compression (0) at 30..33 already zeros
  return b;
}

class BmpImageTest_1039 : public ::testing::Test {};

TEST_F(BmpImageTest_1039, ReadMetadataValidBmpSetsPixelDimensions_1039) {
  auto bytes = makeBmpHeaderBytes(/*width=*/640u, /*height=*/480u);
  auto io = std::make_unique<FakeBasicIo>(bytes, "mem://valid.bmp");
  FakeBasicIo* io_raw = io.get();

  Exiv2::BmpImage image(std::move(io));

  EXPECT_NO_THROW(image.readMetadata());
  EXPECT_EQ(io_raw->openCount(), 1);
  EXPECT_EQ(io_raw->closeCount(), 1);

  EXPECT_EQ(image.pixelWidth(), 640u);
  EXPECT_EQ(image.pixelHeight(), 480u);
}

TEST_F(BmpImageTest_1039, ReadMetadataShortReadDoesNotSetDimensions_1039) {
  // Provide fewer than 26 bytes so the observable width/height assignment path
  // cannot succeed.
  std::vector<byte> bytes(10, 0);
  bytes[0] = static_cast<byte>('B');
  bytes[1] = static_cast<byte>('M');

  auto io = std::make_unique<FakeBasicIo>(bytes, "mem://short.bmp");
  FakeBasicIo* io_raw = io.get();

  Exiv2::BmpImage image(std::move(io));

  // If the bytes are still considered BMP by the library, readMetadata should not throw.
  // Regardless, if fewer than 26 bytes are available, pixel dimensions should remain at defaults.
  try {
    image.readMetadata();
  } catch (const Exiv2::Error&) {
    // Acceptable: interface allows exceptions for non-image / read failures.
  }

  EXPECT_EQ(io_raw->openCount(), 1);
  // If open succeeded, IoCloser should close on both success and later-throw paths.
  EXPECT_EQ(io_raw->closeCount(), 1);

  EXPECT_EQ(image.pixelWidth(), 0u);
  EXPECT_EQ(image.pixelHeight(), 0u);
}

TEST_F(BmpImageTest_1039, ReadMetadataOpenFailureThrowsAndDoesNotClose_1039) {
  auto bytes = makeBmpHeaderBytes(/*width=*/1u, /*height=*/1u);
  auto io = std::make_unique<FakeBasicIo>(bytes, "mem://openfail.bmp");
  FakeBasicIo* io_raw = io.get();
  io_raw->setOpenRc(1);  // non-zero -> open failure

  Exiv2::BmpImage image(std::move(io));

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);
  EXPECT_EQ(io_raw->openCount(), 1);
  // open failure throws before IoCloser lifetime begins (as observed via no close call).
  EXPECT_EQ(io_raw->closeCount(), 0);
}

TEST_F(BmpImageTest_1039, ReadMetadataNonBmpThrowsAndClosesIo_1039) {
  auto bytes = makeBmpHeaderBytes(/*width=*/100u, /*height=*/200u);
  // Break signature so it's not a BMP.
  bytes[0] = static_cast<byte>('Z');
  bytes[1] = static_cast<byte>('Z');

  auto io = std::make_unique<FakeBasicIo>(bytes, "mem://notbmp.bmp");
  FakeBasicIo* io_raw = io.get();

  Exiv2::BmpImage image(std::move(io));

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);
  EXPECT_EQ(io_raw->openCount(), 1);
  // IoCloser should close when throwing after open succeeds.
  EXPECT_EQ(io_raw->closeCount(), 1);
}

TEST_F(BmpImageTest_1039, ReadMetadataNonBmpWithEofFlagThrowsAndClosesIo_1039) {
  auto bytes = makeBmpHeaderBytes(/*width=*/10u, /*height=*/20u);
  bytes[0] = static_cast<byte>('N');
  bytes[1] = static_cast<byte>('O');

  auto io = std::make_unique<FakeBasicIo>(bytes, "mem://notbmp_eof.bmp");
  FakeBasicIo* io_raw = io.get();
  io_raw->setEofFlag(true);  // make EOF observable to readMetadata error path

  Exiv2::BmpImage image(std::move(io));

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);
  EXPECT_EQ(io_raw->openCount(), 1);
  EXPECT_EQ(io_raw->closeCount(), 1);
}

TEST_F(BmpImageTest_1039, SettersDoNotThrow_1039) {
  auto bytes = makeBmpHeaderBytes(/*width=*/1u, /*height=*/1u);
  auto io = std::make_unique<FakeBasicIo>(bytes, "mem://setters.bmp");

  Exiv2::BmpImage image(std::move(io));

  Exiv2::ExifData exif;
  Exiv2::IptcData iptc;

  EXPECT_NO_THROW(image.setExifData(exif));
  EXPECT_NO_THROW(image.setIptcData(iptc));
  EXPECT_NO_THROW(image.setComment(std::string("hello")));
}

}  // namespace