// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::Image::printTiffStructure
// Test ID: 1066
// *****************************************************************

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/image.hpp"

namespace {

/*!
  A small in-memory BasicIo implementation sufficient for exercising
  Image::printTiffStructure via public/virtual BasicIo APIs.

  NOTE: This is a test double for IO only (external collaborator).
        It does NOT re-implement Image internals.
*/
class MemoryIo final : public Exiv2::BasicIo {
 public:
  explicit MemoryIo(std::vector<Exiv2::byte> data) : data_(std::move(data)) {}

  int open() override {
    isOpen_ = true;
    err_ = 0;
    eof_ = false;
    pos_ = 0;
    return 0;
  }

  int close() override {
    isOpen_ = false;
    return 0;
  }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (!isOpen_) {
      err_ = 1;
      return 0;
    }
    if (buf == nullptr && rcount != 0) {
      err_ = 1;
      return 0;
    }

    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (rcount < avail) ? rcount : avail;

    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }

    if (n < rcount) {
      eof_ = true;
    }
    return n;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    if (!isOpen_) {
      err_ = 1;
      return 1;
    }

    int64_t base = 0;
    switch (pos) {
      case Exiv2::beg:
        base = 0;
        break;
      case Exiv2::cur:
        base = static_cast<int64_t>(pos_);
        break;
      case Exiv2::end:
        base = static_cast<int64_t>(data_.size());
        break;
      default:
        err_ = 1;
        return 1;
    }

    const int64_t np = base + offset;
    if (np < 0) {
      err_ = 1;
      return 1;
    }

    pos_ = static_cast<size_t>(np);
    eof_ = (pos_ >= data_.size());
    err_ = 0;
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return isOpen_; }
  const int error() override { return err_; }
  const bool eof() override { return eof_; }
  const std::string& path() override { return path_; }

  // Unused by these tests; provide safe minimal behavior.
  size_t write(const Exiv2::byte*, size_t) override { return 0; }
  size_t write(Exiv2::BasicIo&) override { return 0; }
  int putb(Exiv2::byte) override { return EOF; }
  Exiv2::DataBuf read(size_t) override { return Exiv2::DataBuf(); }
  int getb() override { return EOF; }
  void transfer(Exiv2::BasicIo&) override {}
  Exiv2::byte* mmap(bool) override { return nullptr; }
  int munmap() override { return 0; }
  void populateFakeData() override {}

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_{0};
  bool isOpen_{true};
  bool eof_{false};
  int err_{0};
  std::string path_{"memory://"};
};

static std::vector<Exiv2::byte> MakeMinimalTiffLittleEndianWithEmptyIFD() {
  // Minimal TIFF-like bytes:
  // 0-1: 'I''I'
  // 2-3: 42 (0x2A00 little-endian)
  // 4-7: offset to first IFD = 8 (0x08000000 little-endian bytes: 08 00 00 00)
  // 8-9: number of directory entries = 0
  // 10-13: next IFD offset = 0
  std::vector<Exiv2::byte> d(14, 0);
  d[0] = static_cast<Exiv2::byte>('I');
  d[1] = static_cast<Exiv2::byte>('I');
  d[2] = static_cast<Exiv2::byte>(0x2A);
  d[3] = static_cast<Exiv2::byte>(0x00);
  d[4] = static_cast<Exiv2::byte>(0x08);
  d[5] = static_cast<Exiv2::byte>(0x00);
  d[6] = static_cast<Exiv2::byte>(0x00);
  d[7] = static_cast<Exiv2::byte>(0x00);
  d[8] = static_cast<Exiv2::byte>(0x00);
  d[9] = static_cast<Exiv2::byte>(0x00);
  d[10] = static_cast<Exiv2::byte>(0x00);
  d[11] = static_cast<Exiv2::byte>(0x00);
  d[12] = static_cast<Exiv2::byte>(0x00);
  d[13] = static_cast<Exiv2::byte>(0x00);

  // Pad to reduce risk of short reads if implementation reads more.
  d.resize(512, 0);
  return d;
}

class ImagePrintTiffStructureTest_1066 : public ::testing::Test {
 protected:
  static Exiv2::Image MakeImageWithDummyIo() {
    // Image::printTiffStructure takes a BasicIo& as an argument, but Image
    // construction requires an owned BasicIo. Provide an empty one.
    auto ownedIo = std::make_unique<MemoryIo>(std::vector<Exiv2::byte>{});
    // Avoid depending on specific ImageType enumerators (not shown in prompt).
    const auto type = static_cast<Exiv2::ImageType>(0);
    return Exiv2::Image(type, /*supportedMetadata=*/0, std::move(ownedIo));
  }
};

}  // namespace

// -----------------------------------------------------------------------------
// Option gating: for options NOT in {kpsBasic,kpsXMP,kpsRecursive,kpsIccProfile}
// the function should not attempt to read from the provided BasicIo.
// -----------------------------------------------------------------------------

TEST_F(ImagePrintTiffStructureTest_1066, DoesNotReadForKpsNone_1066) {
  Exiv2::Image img = MakeImageWithDummyIo();

  auto io = MemoryIo(std::vector<Exiv2::byte>{});
  io.open();

  std::ostringstream out;
  const size_t before = io.tell();

  EXPECT_NO_THROW(img.printTiffStructure(io, out, Exiv2::kpsNone, /*depth=*/0, /*offset=*/0));
  EXPECT_EQ(io.tell(), before) << "IO position should not change when option is kpsNone";
}

TEST_F(ImagePrintTiffStructureTest_1066, DoesNotReadForKpsIptcErase_1066) {
  Exiv2::Image img = MakeImageWithDummyIo();

  auto io = MemoryIo(std::vector<Exiv2::byte>{});
  io.open();

  std::ostringstream out;
  const size_t before = io.tell();

  EXPECT_NO_THROW(img.printTiffStructure(io, out, Exiv2::kpsIptcErase, /*depth=*/1, /*offset=*/0));
  EXPECT_EQ(io.tell(), before) << "IO position should not change when option is kpsIptcErase";
}

// -----------------------------------------------------------------------------
// Error case: for handled options, the function calls BasicIo::readOrThrow(..., 8, kerCorruptedMetadata)
// so providing fewer than 8 readable bytes should result in an observable exception.
// -----------------------------------------------------------------------------

TEST_F(ImagePrintTiffStructureTest_1066, ThrowsIfLessThan8BytesAvailableForKpsBasic_1066) {
  Exiv2::Image img = MakeImageWithDummyIo();

  // Only 7 bytes -> readOrThrow(8, kerCorruptedMetadata) should throw.
  std::vector<Exiv2::byte> tooShort(7, 0);
  MemoryIo io(std::move(tooShort));
  io.open();

  std::ostringstream out;

  EXPECT_ANY_THROW(img.printTiffStructure(io, out, Exiv2::kpsBasic, /*depth=*/0, /*offset=*/0));
}

// -----------------------------------------------------------------------------
// Normal-ish operation: provide a minimal TIFF-like buffer large enough so that
// the initial 8-byte read succeeds and subsequent parsing has a chance to proceed.
// We only assert "no throw" (observable behavior) without inferring internal logic.
// -----------------------------------------------------------------------------

TEST_F(ImagePrintTiffStructureTest_1066, DoesNotThrowWithMinimalTiffDataForKpsBasic_1066) {
  Exiv2::Image img = MakeImageWithDummyIo();

  MemoryIo io(MakeMinimalTiffLittleEndianWithEmptyIFD());
  io.open();

  std::ostringstream out;

  EXPECT_NO_THROW(img.printTiffStructure(io, out, Exiv2::kpsBasic, /*depth=*/1, /*offset=*/0));
}

TEST_F(ImagePrintTiffStructureTest_1066, DoesNotThrowWithMinimalTiffDataForKpsXmp_1066) {
  Exiv2::Image img = MakeImageWithDummyIo();

  MemoryIo io(MakeMinimalTiffLittleEndianWithEmptyIFD());
  io.open();

  std::ostringstream out;

  EXPECT_NO_THROW(img.printTiffStructure(io, out, Exiv2::kpsXMP, /*depth=*/1, /*offset=*/0));
}

TEST_F(ImagePrintTiffStructureTest_1066, DoesNotThrowWithMinimalTiffDataForKpsRecursive_1066) {
  Exiv2::Image img = MakeImageWithDummyIo();

  MemoryIo io(MakeMinimalTiffLittleEndianWithEmptyIFD());
  io.open();

  std::ostringstream out;

  EXPECT_NO_THROW(img.printTiffStructure(io, out, Exiv2::kpsRecursive, /*depth=*/1, /*offset=*/0));
}

TEST_F(ImagePrintTiffStructureTest_1066, DoesNotThrowWithMinimalTiffDataForKpsIccProfile_1066) {
  Exiv2::Image img = MakeImageWithDummyIo();

  MemoryIo io(MakeMinimalTiffLittleEndianWithEmptyIFD());
  io.open();

  std::ostringstream out;

  EXPECT_NO_THROW(img.printTiffStructure(io, out, Exiv2::kpsIccProfile, /*depth=*/1, /*offset=*/0));
}

// -----------------------------------------------------------------------------
// Boundary-ish: depth = 0 should be accepted (we only check it doesn't crash/throw
// when input is sufficient for initial read).
// -----------------------------------------------------------------------------

TEST_F(ImagePrintTiffStructureTest_1066, AcceptsDepthZeroWhenInputSufficient_1066) {
  Exiv2::Image img = MakeImageWithDummyIo();

  MemoryIo io(MakeMinimalTiffLittleEndianWithEmptyIFD());
  io.open();

  std::ostringstream out;

  EXPECT_NO_THROW(img.printTiffStructure(io, out, Exiv2::kpsBasic, /*depth=*/0, /*offset=*/0));
}