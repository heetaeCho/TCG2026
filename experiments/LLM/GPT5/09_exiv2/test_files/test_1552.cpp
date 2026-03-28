// TEST_ID 1552
// File: test_orfimage_write_metadata_1552.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/orfimage.hpp"
#include "exiv2/types.hpp"

namespace {

class CountingIo final : public Exiv2::BasicIo {
 public:
  explicit CountingIo(std::string path, int open_ret = 1)
      : path_(std::move(path)), open_ret_(open_ret) {}

  // Configure basic backing buffer (only used if mmap() is called).
  void setBuffer(std::vector<Exiv2::byte> buf) { buf_ = std::move(buf); }

  // Counters / last-args for observable interactions.
  int open_calls = 0;
  int close_calls = 0;
  int mmap_calls = 0;
  int munmap_calls = 0;
  int size_calls = 0;
  int path_calls = 0;

  bool last_mmap_writeable = false;

  // BasicIo overrides used by OrfImage::writeMetadata().
  int open() override {
    ++open_calls;
    return open_ret_;
  }

  int close() override {
    ++close_calls;
    return 0;
  }

  Exiv2::byte* mmap(bool isWriteable) override {
    ++mmap_calls;
    last_mmap_writeable = isWriteable;
    return buf_.empty() ? nullptr : buf_.data();
  }

  int munmap() override {
    ++munmap_calls;
    return 0;
  }

  const size_t size() override {
    ++size_calls;
    return buf_.size();
  }

  const std::string& path() override {
    ++path_calls;
    return path_;
  }

 private:
  std::string path_;
  int open_ret_ = 1;
  std::vector<Exiv2::byte> buf_;
};

class OrfImageWriteMetadataTest_1552 : public ::testing::Test {};

TEST_F(OrfImageWriteMetadataTest_1552, OpenFails_DoesNotMmapOrSize_SetsLittleEndianWhenInvalid_1552) {
  auto io_up = std::make_unique<CountingIo>("dummy.orf", /*open_ret=*/1);
  CountingIo* io = io_up.get();

  Exiv2::OrfImage img(std::move(io_up), /*create=*/false);

  // Call and tolerate exceptions (encode may throw per comment).
  try {
    img.writeMetadata();
  } catch (...) {
  }

  // Observable behavior: invalid byte order becomes little-endian before encode.
  EXPECT_EQ(img.byteOrder(), Exiv2::littleEndian);

  // External interactions: open is attempted; mmap/size are not when open fails.
  EXPECT_EQ(io->open_calls, 1);
  EXPECT_EQ(io->mmap_calls, 0);
  EXPECT_EQ(io->size_calls, 0);
}

TEST_F(OrfImageWriteMetadataTest_1552, PresetByteOrderPreservedWhenOpenFails_NoMmapOrSize_1552) {
  auto io_up = std::make_unique<CountingIo>("dummy.orf", /*open_ret=*/1);
  CountingIo* io = io_up.get();

  Exiv2::OrfImage img(std::move(io_up), /*create=*/false);

  img.setByteOrder(Exiv2::bigEndian);

  try {
    img.writeMetadata();
  } catch (...) {
  }

  // If a valid byte order is already set, it should not be forced to little-endian.
  EXPECT_EQ(img.byteOrder(), Exiv2::bigEndian);

  EXPECT_EQ(io->open_calls, 1);
  EXPECT_EQ(io->mmap_calls, 0);
  EXPECT_EQ(io->size_calls, 0);
}

TEST_F(OrfImageWriteMetadataTest_1552, MultipleCalls_OpenAttemptEachTime_ByteOrderStaysDeterministic_1552) {
  auto io_up = std::make_unique<CountingIo>("dummy.orf", /*open_ret=*/1);
  CountingIo* io = io_up.get();

  Exiv2::OrfImage img(std::move(io_up), /*create=*/false);

  // First call should normalize invalid -> little-endian.
  try {
    img.writeMetadata();
  } catch (...) {
  }
  EXPECT_EQ(img.byteOrder(), Exiv2::littleEndian);

  // Second call should keep it at little-endian (since already valid).
  try {
    img.writeMetadata();
  } catch (...) {
  }
  EXPECT_EQ(img.byteOrder(), Exiv2::littleEndian);

  // open attempted on each invocation; still no mmap/size on open failure.
  EXPECT_EQ(io->open_calls, 2);
  EXPECT_EQ(io->mmap_calls, 0);
  EXPECT_EQ(io->size_calls, 0);
}

}  // namespace