// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_quicktimevideo_newQTimeInstance_661.cpp
//
// Unit tests for:
//   Exiv2::newQTimeInstance(Exiv2::BasicIo::UniquePtr io, bool create)
//
// Constraints honored:
// - Treat implementation as a black box: only test observable behavior (nullptr vs non-null)
// - No access to private/internal state
// - No re-implementation of internal logic
//
// Notes:
// - These tests assume Exiv2 headers provide Exiv2::BasicIo and Exiv2::newQTimeInstance.
// - We provide small test BasicIo implementations to control the input stream.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "basicio.hpp"
#include "image.hpp"

// Some Exiv2 builds expose newQTimeInstance via image factory headers;
// if your build needs a different include, adjust accordingly.
#include "quicktimevideo.hpp"

namespace {

// Minimal BasicIo implementation for feeding bytes to Exiv2.
// We only implement methods typically used during construction/probing.
// If your Exiv2 version calls additional methods, extend accordingly
// (still black-box: we're just providing an IO source).
class VectorBasicIo final : public Exiv2::BasicIo {
 public:
  explicit VectorBasicIo(std::vector<Exiv2::byte> data) : data_(std::move(data)), pos_(0), open_(true) {}

  // BasicIo interface
  int open() override {
    open_ = true;
    return 0;
  }

  int close() override {
    open_ = false;
    return 0;
  }

  bool isopen() const override { return open_; }

  int error() const override { return 0; }
  void clearerr() override {}

  // Read up to rcount bytes into buf. Return number of bytes read.
  long read(Exiv2::byte* buf, long rcount) override {
    if (!open_ || buf == nullptr || rcount <= 0) return 0;
    const std::size_t remaining = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const std::size_t n = std::min<std::size_t>(static_cast<std::size_t>(rcount), remaining);
    if (n == 0) return 0;
    std::memcpy(buf, data_.data() + pos_, n);
    pos_ += n;
    return static_cast<long>(n);
  }

  // Write not required for these tests; return error (-1) to make it explicit.
  long write(const Exiv2::byte*, long) override { return -1; }

  int putb(Exiv2::byte) override { return -1; }

  Exiv2::DataBuf read(long rcount) override {
    if (!open_ || rcount <= 0) return Exiv2::DataBuf();
    std::vector<Exiv2::byte> tmp(static_cast<std::size_t>(rcount));
    const long got = read(tmp.data(), rcount);
    if (got <= 0) return Exiv2::DataBuf();
    return Exiv2::DataBuf(tmp.data(), static_cast<std::size_t>(got));
  }

  // Seek/tell support
  int seek(long offset, Position pos) override {
    if (!open_) return 1;
    long base = 0;
    switch (pos) {
      case beg:
        base = 0;
        break;
      case cur:
        base = static_cast<long>(pos_);
        break;
      case end:
        base = static_cast<long>(data_.size());
        break;
    }
    const long np = base + offset;
    if (np < 0) return 1;
    pos_ = static_cast<std::size_t>(np);
    return 0;
  }

  long tell() const override { return static_cast<long>(pos_); }

  long size() const override { return static_cast<long>(data_.size()); }

  // Map not required; return null.
  Exiv2::byte* mmap(bool /*isWriteable*/ = false) override { return nullptr; }
  int munmap() override { return 0; }

  // File name / path related (not used): return empty.
  std::string path() const override { return {}; }

  // Transfer/cloning
  Exiv2::BasicIo::UniquePtr transfer() override {
    // Transfer ownership of buffer into a new IO, leaving this empty.
    auto moved = std::make_unique<VectorBasicIo>(std::move(data_));
    data_.clear();
    pos_ = 0;
    return moved;
  }

  Exiv2::BasicIo::UniquePtr clone() const override { return std::make_unique<VectorBasicIo>(data_); }

 private:
  std::vector<Exiv2::byte> data_;
  std::size_t pos_;
  bool open_;
};

// BasicIo that simulates "not open" / unable to read.
class ClosedBasicIo final : public Exiv2::BasicIo {
 public:
  ClosedBasicIo() : open_(false) {}

  int open() override {
    open_ = false;  // simulate open failure / remains closed
    return 1;
  }

  int close() override {
    open_ = false;
    return 0;
  }

  bool isopen() const override { return open_; }

  int error() const override { return 1; }
  void clearerr() override {}

  long read(Exiv2::byte*, long) override { return 0; }
  long write(const Exiv2::byte*, long) override { return -1; }
  int putb(Exiv2::byte) override { return -1; }
  Exiv2::DataBuf read(long) override { return Exiv2::DataBuf(); }

  int seek(long, Position) override { return 1; }
  long tell() const override { return 0; }
  long size() const override { return 0; }

  Exiv2::byte* mmap(bool = false) override { return nullptr; }
  int munmap() override { return 0; }

  std::string path() const override { return {}; }

  Exiv2::BasicIo::UniquePtr transfer() override { return std::make_unique<ClosedBasicIo>(); }
  Exiv2::BasicIo::UniquePtr clone() const override { return std::make_unique<ClosedBasicIo>(); }

 private:
  bool open_;
};

// Helper: build a minimal QuickTime/MP4-ish header.
// We keep it tiny; the goal is just to provide plausible input.
std::vector<Exiv2::byte> MakeFtyp(const char major[4]) {
  // box size (24 bytes), 'ftyp', major brand, minor version, compatible brand
  const uint32_t size = 24;
  std::vector<Exiv2::byte> v;
  v.reserve(size);

  auto push_u32be = [&](uint32_t x) {
    v.push_back(static_cast<Exiv2::byte>((x >> 24) & 0xFF));
    v.push_back(static_cast<Exiv2::byte>((x >> 16) & 0xFF));
    v.push_back(static_cast<Exiv2::byte>((x >> 8) & 0xFF));
    v.push_back(static_cast<Exiv2::byte>((x) & 0xFF));
  };
  auto push_4cc = [&](const char c[4]) {
    v.push_back(static_cast<Exiv2::byte>(c[0]));
    v.push_back(static_cast<Exiv2::byte>(c[1]));
    v.push_back(static_cast<Exiv2::byte>(c[2]));
    v.push_back(static_cast<Exiv2::byte>(c[3]));
  };

  push_u32be(size);
  push_4cc("ftyp");
  push_4cc(major);
  push_u32be(0);        // minor version
  push_4cc("isom");     // compatible brand
  return v;
}

class NewQTimeInstanceTest_661 : public ::testing::Test {};

}  // namespace

TEST_F(NewQTimeInstanceTest_661, ReturnsNullptrForEmptyIo_661) {
  auto io = std::make_unique<VectorBasicIo>(std::vector<Exiv2::byte>{});
  auto img = Exiv2::newQTimeInstance(std::move(io), /*create*/ false);
  EXPECT_EQ(img, nullptr);
}

TEST_F(NewQTimeInstanceTest_661, ReturnsNullptrForClearlyInvalidHeader_661) {
  // Random bytes that should not represent a valid QuickTime/MP4 structure.
  std::vector<Exiv2::byte> garbage = {0x00, 0x01, 0x02, 0x03, 0xFF, 0xEE, 0xDD, 0xCC};
  auto io = std::make_unique<VectorBasicIo>(garbage);
  auto img = Exiv2::newQTimeInstance(std::move(io), /*create*/ false);
  EXPECT_EQ(img, nullptr);
}

TEST_F(NewQTimeInstanceTest_661, IgnoresCreateFlagForInvalidInput_ReturnsNullptr_661) {
  std::vector<Exiv2::byte> garbage = {0x10, 0x20, 0x30, 0x40};
  auto io = std::make_unique<VectorBasicIo>(garbage);
  auto img = Exiv2::newQTimeInstance(std::move(io), /*create*/ true);
  EXPECT_EQ(img, nullptr);
}

TEST_F(NewQTimeInstanceTest_661, ReturnsNullptrWhenIoCannotBeOpenedOrRead_661) {
  auto io = std::make_unique<ClosedBasicIo>();
  auto img = Exiv2::newQTimeInstance(std::move(io), /*create*/ false);
  EXPECT_EQ(img, nullptr);
}

TEST_F(NewQTimeInstanceTest_661, ReturnsNonNullForPlausibleFtypBoxIfRecognized_661) {
  // Provide a minimal MP4-ish ftyp. Depending on Exiv2 build/features, this may
  // or may not be considered "good". We only assert the documented observable:
  // newQTimeInstance returns non-null iff image->good() is true.
  //
  // If your Exiv2 build requires more atoms than ftyp to be "good", this test may
  // need to be adjusted to use a real sample file and FileIo instead.
  auto bytes = MakeFtyp("qt  ");  // QuickTime brand
  auto io = std::make_unique<VectorBasicIo>(bytes);
  auto img = Exiv2::newQTimeInstance(std::move(io), /*create*/ false);

  // Accept either outcome in a non-flaky way? No: unit test should be deterministic.
  // We keep this as a strict expectation for environments where ftyp is enough.
  // If it isn't, prefer using a known-good .mov/.mp4 test asset and FileIo.
  ASSERT_NE(img, nullptr);
}

TEST_F(NewQTimeInstanceTest_661, ReturnsNonNullForAlternativeMajorBrandIfRecognized_661) {
  auto bytes = MakeFtyp("isom");  // ISO Base Media
  auto io = std::make_unique<VectorBasicIo>(bytes);
  auto img = Exiv2::newQTimeInstance(std::move(io), /*create*/ false);

  ASSERT_NE(img, nullptr);
}