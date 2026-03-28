// File: test_pngimage_readmetadata_974.cpp
// Unit tests for Exiv2::PngImage::readMetadata (black-box)
// TEST_ID: 974

#include <gtest/gtest.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/pngimage.hpp"

namespace {

// A minimal in-memory BasicIo implementation for driving PngImage via its public interface.
// This is a test collaborator (dependency) and does NOT simulate any internal logic of PngImage.
class BufferIo final : public Exiv2::BasicIo {
 public:
  explicit BufferIo(std::vector<Exiv2::byte> bytes, std::string path = "buffer.png")
      : data_(std::move(bytes)), path_(std::move(path)) {}

  // Controls
  void setOpenResult(int rc) { open_rc_ = rc; }
  void setSeekForcesError(bool v) { force_seek_error_ = v; }
  void setReadForcesError(bool v) { force_read_error_ = v; }

  // Observability (optional)
  int openCalls() const { return open_calls_; }
  int seekCalls() const { return seek_calls_; }

  // BasicIo interface
  int open() override {
    ++open_calls_;
    is_open_ = (open_rc_ == 0);
    return open_rc_;
  }

  int close() override {
    is_open_ = false;
    return 0;
  }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (force_read_error_) {
      error_ = 1;
      eof_ = false;
      return 0;
    }
    if (pos_ >= data_.size()) {
      eof_ = true;
      return 0;
    }
    const size_t avail = data_.size() - pos_;
    const size_t n = (rcount < avail) ? rcount : avail;
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }
    eof_ = (pos_ >= data_.size());
    return n;
  }

  Exiv2::DataBuf read(size_t rcount) override {
    Exiv2::DataBuf buf(rcount);
    const size_t n = read(buf.data(0), rcount);
    if (n < rcount) {
      // Shrink to what we actually read, mirroring typical behavior of buffered reads.
      buf.resize(n);
    }
    return buf;
  }

  int seek(int64_t offset, Exiv2::BasicIo::Position pos) override {
    ++seek_calls_;
    if (force_seek_error_) {
      error_ = 1;
      return 1;
    }
    int64_t base = 0;
    if (pos == Exiv2::BasicIo::beg) {
      base = 0;
    } else if (pos == Exiv2::BasicIo::cur) {
      base = static_cast<int64_t>(pos_);
    } else {  // end
      base = static_cast<int64_t>(data_.size());
    }

    const int64_t newpos64 = base + offset;
    if (newpos64 < 0) {
      error_ = 1;
      return 1;
    }
    const size_t newpos = static_cast<size_t>(newpos64);
    // Allow seeking to exactly end; beyond end sets eof but no error (common behavior).
    pos_ = newpos;
    eof_ = (pos_ >= data_.size());
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return is_open_; }
  const int error() override { return error_; }
  const bool eof() override { return eof_; }
  const std::string& path() override { return path_; }

  // Not used by these tests
  size_t write(const Exiv2::byte*, size_t) override { return 0; }
  size_t write(Exiv2::BasicIo&) override { return 0; }
  int putb(Exiv2::byte) override { return -1; }
  int getb() override {
    Exiv2::byte b{};
    const size_t n = read(&b, 1);
    return (n == 1) ? static_cast<int>(b) : -1;
  }
  void transfer(Exiv2::BasicIo&) override {}
  Exiv2::byte* mmap(bool) override { return nullptr; }
  int munmap() override { return 0; }
  void populateFakeData() override {}

 private:
  std::vector<Exiv2::byte> data_;
  std::string path_;

  size_t pos_{0};
  bool eof_{false};
  bool is_open_{false};
  int error_{0};

  int open_rc_{0};
  bool force_seek_error_{false};
  bool force_read_error_{false};

  int open_calls_{0};
  int seek_calls_{0};
};

static void AppendBe32(std::vector<Exiv2::byte>& out, uint32_t v) {
  out.push_back(static_cast<Exiv2::byte>((v >> 24) & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 16) & 0xFF));
  out.push_back(static_cast<Exiv2::byte>((v >> 8) & 0xFF));
  out.push_back(static_cast<Exiv2::byte>(v & 0xFF));
}

static void AppendChunk(std::vector<Exiv2::byte>& out,
                        const char type[4],
                        const std::vector<Exiv2::byte>& data) {
  AppendBe32(out, static_cast<uint32_t>(data.size()));
  out.push_back(static_cast<Exiv2::byte>(type[0]));
  out.push_back(static_cast<Exiv2::byte>(type[1]));
  out.push_back(static_cast<Exiv2::byte>(type[2]));
  out.push_back(static_cast<Exiv2::byte>(type[3]));
  out.insert(out.end(), data.begin(), data.end());
  // CRC (4 bytes). PngImage::readMetadata seeks past it; CRC value is not asserted here.
  AppendBe32(out, 0u);
}

static std::vector<Exiv2::byte> MakePngSignature() {
  // PNG signature: 89 50 4E 47 0D 0A 1A 0A
  return {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
}

static std::vector<Exiv2::byte> MakeMinimalPngWithIHDR(uint32_t w, uint32_t h) {
  std::vector<Exiv2::byte> bytes = MakePngSignature();

  // IHDR data is 13 bytes; PngImage::readMetadata requires >= 8 for decodeIHDRChunk.
  std::vector<Exiv2::byte> ihdr;
  ihdr.reserve(13);
  AppendBe32(ihdr, w);
  AppendBe32(ihdr, h);
  // Remaining 5 fields: bit depth, color type, compression, filter, interlace.
  ihdr.push_back(8);  // bit depth
  ihdr.push_back(2);  // color type (truecolor)
  ihdr.push_back(0);  // compression
  ihdr.push_back(0);  // filter
  ihdr.push_back(0);  // interlace
  AppendChunk(bytes, "IHDR", ihdr);

  // IEND with 0 data.
  AppendChunk(bytes, "IEND", {});
  return bytes;
}

static std::vector<Exiv2::byte> MakePngWithOversizedFirstChunkLength() {
  std::vector<Exiv2::byte> bytes = MakePngSignature();
  // Create a bogus chunk header with a length that will exceed remaining bytes.
  // Length = 0xFFFFFFFF, type = "tEXt", and *no* payload/CRC beyond what's in the vector.
  AppendBe32(bytes, 0xFFFFFFFFu);
  bytes.push_back('t');
  bytes.push_back('E');
  bytes.push_back('X');
  bytes.push_back('t');
  // No data, no CRC -> should trigger "chunkLength > imgSize - io_->tell()".
  return bytes;
}

static std::vector<Exiv2::byte> MakePngWithBadIccpNoNullWithin80() {
  std::vector<Exiv2::byte> bytes = MakePngSignature();

  // iCCP chunk: profile name must be NUL-terminated, and loop enforces iccOffset < 80.
  // Build 81 bytes of non-zero data so no 0x00 appears within first 80 bytes.
  std::vector<Exiv2::byte> iccp_data(81, static_cast<Exiv2::byte>('A'));
  // Ensure also not zero at any position.
  for (auto& b : iccp_data) b = static_cast<Exiv2::byte>('A');
  AppendChunk(bytes, "iCCP", iccp_data);

  // Add IEND so parsing could continue if it didn't fail.
  AppendChunk(bytes, "IEND", {});
  return bytes;
}

class PngImageReadMetadataTest_974 : public ::testing::Test {};

}  // namespace

TEST_F(PngImageReadMetadataTest_974, ReadsValidPngSetsDimensions_974) {
  const uint32_t kW = 320;
  const uint32_t kH = 200;
  auto bytes = MakeMinimalPngWithIHDR(kW, kH);
  auto io = std::make_unique<BufferIo>(std::move(bytes), "valid.png");

  Exiv2::PngImage image(std::move(io), /*create=*/false);

  EXPECT_NO_THROW(image.readMetadata());
  EXPECT_EQ(image.pixelWidth(), kW);
  EXPECT_EQ(image.pixelHeight(), kH);
}

TEST_F(PngImageReadMetadataTest_974, OpenFailureThrows_974) {
  auto bytes = MakeMinimalPngWithIHDR(1, 1);
  auto io = std::make_unique<BufferIo>(std::move(bytes), "cannot-open.png");
  io->setOpenResult(1);  // non-zero => open failure

  Exiv2::PngImage image(std::move(io), /*create=*/false);

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);
}

TEST_F(PngImageReadMetadataTest_974, InvalidSignatureThrowsNotAnImage_974) {
  // Not a PNG signature; should fail isPngType(*io_, true) and throw.
  std::vector<Exiv2::byte> bytes = {'N', 'O', 'T', '_', 'P', 'N', 'G', '!'};
  // Provide a bit more data to avoid immediate EOF edge-cases in readers.
  bytes.insert(bytes.end(), 16, 0);

  auto io = std::make_unique<BufferIo>(std::move(bytes), "not-png.dat");
  Exiv2::PngImage image(std::move(io), /*create=*/false);

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);
}

TEST_F(PngImageReadMetadataTest_974, OversizedChunkLengthThrowsFailedToReadImageData_974) {
  auto bytes = MakePngWithOversizedFirstChunkLength();
  auto io = std::make_unique<BufferIo>(std::move(bytes), "oversize-chunk.png");

  Exiv2::PngImage image(std::move(io), /*create=*/false);

  EXPECT_THROW(image.readMetadata(), Exiv2::Error);
}

TEST_F(PngImageReadMetadataTest_974, IccpWithoutNullWithin80ThrowsCorruptedMetadata_974) {
  auto bytes = MakePngWithBadIccpNoNullWithin80();
  auto io = std::make_unique<BufferIo>(std::move(bytes), "bad-iccp.png");

  Exiv2::PngImage image(std::move(io), /*create=*/false);

  // The iCCP parsing loop uses enforce(...) with kerCorruptedMetadata when the NUL is missing
  // within the allowed limit; observable behavior is an exception.
  EXPECT_THROW(image.readMetadata(), Exiv2::Error);
}