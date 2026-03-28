// ============================================================================
// TEST_ID: 1551
// File: test_orfimage_readmetadata_1551.cpp
// ============================================================================

#include <gtest/gtest.h>

#include <exiv2/orfimage.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace {

// A minimal in-memory BasicIo test double.
// Implements only publicly observable behavior (open/close/read/seek/mmap/size/...)
// without assuming OrfImage internals beyond what is exercised through the interface.
class MemBasicIo1551 : public Exiv2::BasicIo {
 public:
  using byte = Exiv2::byte;

  explicit MemBasicIo1551(std::vector<byte> data, std::string path = "mem.orf")
      : data_(std::move(data)), path_(std::move(path)) {}

  // Controls for tests
  void setOpenReturn(int rc) { open_rc_ = rc; }
  void setError(int e) { error_ = e; }
  void setForceEof(bool v) { force_eof_ = v; }

  // Observability for tests
  int openCount() const { return open_count_; }
  int closeCount() const { return close_count_; }
  bool isOpenFlag() const { return is_open_; }

  // BasicIo overrides
  int open() override {
    ++open_count_;
    if (open_rc_ != 0) return open_rc_;
    is_open_ = true;
    eof_ = false;
    // do not clear error_ here; tests may set it intentionally
    pos_ = 0;
    return 0;
  }

  int close() override {
    ++close_count_;
    is_open_ = false;
    return 0;
  }

  size_t read(byte* buf, size_t rcount) override {
    if (!is_open_) {
      error_ = 1;
      return 0;
    }

    if (force_eof_) {
      eof_ = true;
      return 0;
    }

    const size_t avail = (pos_ < data_.size()) ? (data_.size() - static_cast<size_t>(pos_)) : 0;
    const size_t n = (rcount < avail) ? rcount : avail;

    for (size_t i = 0; i < n; ++i) {
      buf[i] = data_[static_cast<size_t>(pos_) + i];
    }
    pos_ += static_cast<int64_t>(n);

    if (n < rcount) eof_ = true;
    return n;
  }

  Exiv2::DataBuf read(size_t rcount) override {
    Exiv2::DataBuf buf(rcount);
    const size_t n = read(buf.data(), rcount);
    // DataBuf size is fixed by ctor; leave content as read.
    (void)n;
    return buf;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    int64_t base = 0;
    switch (pos) {
      case Exiv2::beg:
        base = 0;
        break;
      case Exiv2::cur:
        base = pos_;
        break;
      case Exiv2::end:
        base = static_cast<int64_t>(data_.size());
        break;
      default:
        base = pos_;
        break;
    }

    const int64_t np = base + offset;
    if (np < 0) {
      error_ = 1;
      return 1;
    }

    pos_ = np;
    eof_ = (pos_ > static_cast<int64_t>(data_.size()));
    return 0;
  }

  Exiv2::byte* mmap(bool /*isWriteable*/) override {
    if (data_.empty()) return nullptr;
    return data_.data();
  }

  int munmap() override { return 0; }

  const size_t tell() override { return static_cast<size_t>(pos_ < 0 ? 0 : pos_); }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return is_open_; }
  const int error() override { return error_; }
  const bool eof() override { return eof_; }
  const std::string& path() override { return path_; }

 private:
  std::vector<byte> data_;
  std::string path_;

  int open_rc_ = 0;
  int error_ = 0;
  bool force_eof_ = false;

  bool is_open_ = false;
  bool eof_ = false;
  int64_t pos_ = 0;

  int open_count_ = 0;
  int close_count_ = 0;
};

// Helper to create a minimal ORF-like buffer based on the documented signatures
// (e.g., "IIRO") and a TIFF-like first-IFD offset. This is only test input data.
// (If the library rejects it, the test that expects success will fail, which is fine.)
static std::vector<Exiv2::byte> MakeMinimalIiroOrf1551() {
  // Layout (little-endian):
  // 0..3  : 'I''I''R''O'
  // 4..7  : uint32 offset to first IFD (8)
  // 8..9  : uint16 number of directory entries (0)
  // 10..13: uint32 next IFD offset (0)
  std::vector<Exiv2::byte> b;
  b.push_back(static_cast<Exiv2::byte>('I'));
  b.push_back(static_cast<Exiv2::byte>('I'));
  b.push_back(static_cast<Exiv2::byte>('R'));
  b.push_back(static_cast<Exiv2::byte>('O'));
  // offset = 8
  b.push_back(0x08);
  b.push_back(0x00);
  b.push_back(0x00);
  b.push_back(0x00);
  // entry count = 0
  b.push_back(0x00);
  b.push_back(0x00);
  // next IFD = 0
  b.push_back(0x00);
  b.push_back(0x00);
  b.push_back(0x00);
  b.push_back(0x00);
  return b;
}

}  // namespace

// ----------------------------------------------------------------------------
// TESTS (TEST_ID = 1551)
// ----------------------------------------------------------------------------

TEST(OrfImageReadMetadataTest_1551, OpenFailureThrowsAndDoesNotClose_1551) {
  auto io = std::make_unique<MemBasicIo1551>(MakeMinimalIiroOrf1551(), "openfail.orf");
  MemBasicIo1551* raw = io.get();
  raw->setOpenReturn(1);  // open() fails

  Exiv2::OrfImage image(std::move(io), /*create=*/false);

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);

  // Observable interactions through our test double
  EXPECT_EQ(raw->openCount(), 1);
  EXPECT_EQ(raw->closeCount(), 0) << "close() should not be called when open() fails";
}

TEST(OrfImageReadMetadataTest_1551, NonOrfDataThrowsAndClosesAfterOpen_1551) {
  // Provide non-ORF header but enough bytes so reads needn't hit EOF immediately.
  std::vector<Exiv2::byte> data = {
      static_cast<Exiv2::byte>('N'),
      static_cast<Exiv2::byte>('O'),
      static_cast<Exiv2::byte>('T'),
      static_cast<Exiv2::byte>('!'),
      0x00, 0x00, 0x00, 0x00,
      0x00, 0x00, 0x00, 0x00,
  };

  auto io = std::make_unique<MemBasicIo1551>(data, "not_orf.bin");
  MemBasicIo1551* raw = io.get();

  Exiv2::OrfImage image(std::move(io), /*create=*/false);

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);

  EXPECT_EQ(raw->openCount(), 1);
  // readMetadata() uses an RAII closer after open succeeds; close should be observed.
  EXPECT_EQ(raw->closeCount(), 1);
  EXPECT_FALSE(raw->isOpenFlag());
}

TEST(OrfImageReadMetadataTest_1551, EmptyInputThrowsErrorCase_1551) {
  auto io = std::make_unique<MemBasicIo1551>(std::vector<Exiv2::byte>{}, "empty.orf");
  MemBasicIo1551* raw = io.get();

  Exiv2::OrfImage image(std::move(io), /*create=*/false);

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);

  EXPECT_EQ(raw->openCount(), 1);
  EXPECT_EQ(raw->closeCount(), 1);
  EXPECT_FALSE(raw->isOpenFlag());
}

TEST(OrfImageReadMetadataTest_1551, TooShortOrEofDuringTypeCheckThrows_1551) {
  // Boundary: tiny buffer + forced EOF behavior should lead to an observable exception.
  std::vector<Exiv2::byte> data = {static_cast<Exiv2::byte>('I')};
  auto io = std::make_unique<MemBasicIo1551>(data, "eof.orf");
  MemBasicIo1551* raw = io.get();
  raw->setForceEof(true);

  Exiv2::OrfImage image(std::move(io), /*create=*/false);

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);

  EXPECT_EQ(raw->openCount(), 1);
  EXPECT_EQ(raw->closeCount(), 1);
  EXPECT_FALSE(raw->isOpenFlag());
}

TEST(OrfImageReadMetadataTest_1551, MinimalIiroOrfMaySucceedAndSetsByteOrder_1551) {
  // "Normal operation" attempt with a minimal ORF-like buffer.
  // This test asserts observable post-conditions if decoding succeeds:
  // - no exception
  // - byteOrder() is no longer invalidByteOrder
  // - io is closed after returning
  auto io = std::make_unique<MemBasicIo1551>(MakeMinimalIiroOrf1551(), "minimal.orf");
  MemBasicIo1551* raw = io.get();

  Exiv2::OrfImage image(std::move(io), /*create=*/false);

  ASSERT_NO_THROW(image.readMetadata());

  // Observable through Image's public interface
  EXPECT_NE(image.byteOrder(), Exiv2::invalidByteOrder);

  // And via our BasicIo test double
  EXPECT_EQ(raw->openCount(), 1);
  EXPECT_EQ(raw->closeCount(), 1);
  EXPECT_FALSE(raw->isOpenFlag());
}