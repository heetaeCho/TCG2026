// =================================================================================================
// TEST_ID: 660
// File: test_quicktimevideo_tagdecoder_660.cpp
// Unit tests for Exiv2::QuickTimeVideo::tagDecoder (black-box via public interface / observable effects)
// =================================================================================================

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/quicktimevideo.hpp"
#include "exiv2/types.hpp"
#include "exiv2/xmp_exiv2.hpp"

namespace {

// A tiny memory-backed BasicIo for deterministic reads (enough for tagDecoder paths we test).
class MemBasicIo final : public Exiv2::BasicIo {
 public:
  explicit MemBasicIo(std::vector<Exiv2::byte> data = {}) : data_(std::move(data)) {}

  int open() override {
    open_ = true;
    pos_ = 0;
    return 0;
  }

  int close() override {
    open_ = false;
    return 0;
  }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    if (!buf) return 0;
    const size_t avail = (pos_ <= data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = (rcount < avail) ? rcount : avail;
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
    }
    return n;
  }

  Exiv2::DataBuf read(size_t rcount) override {
    Exiv2::DataBuf b(rcount);
    const size_t n = read(b.data(), rcount);
    b.resize(n);
    return b;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    int64_t base = 0;
    if (pos == Exiv2::beg) base = 0;
    else if (pos == Exiv2::cur) base = static_cast<int64_t>(pos_);
    else if (pos == Exiv2::end) base = static_cast<int64_t>(data_.size());
    else return 1;

    const int64_t np = base + offset;
    if (np < 0) return 1;
    pos_ = static_cast<size_t>(np);
    if (pos_ > data_.size()) pos_ = data_.size();
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return open_; }

  // Minimal stubs (unused by these tests but required for link/override completeness).
  size_t write(const Exiv2::byte*, size_t) override { return 0; }
  size_t write(Exiv2::BasicIo&) override { return 0; }
  int putb(Exiv2::byte) override { return EOF; }
  int getb() override {
    Exiv2::byte b{};
    return read(&b, 1) == 1 ? b : EOF;
  }
  void transfer(Exiv2::BasicIo&) override {}
  Exiv2::byte* mmap(bool) override { return nullptr; }
  int munmap() override { return 0; }
  const int error() override { return 0; }
  const bool eof() override { return pos_ >= data_.size(); }
  const std::string& path() override { return path_; }

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_{0};
  bool open_{true};
  std::string path_{"mem"};
};

// Expose tagDecoder for testing (it is protected).
class QuickTimeVideo_ExposeTagDecoder final : public Exiv2::QuickTimeVideo {
 public:
  QuickTimeVideo_ExposeTagDecoder(std::unique_ptr<Exiv2::BasicIo> io, size_t max_depth)
      : Exiv2::QuickTimeVideo(std::move(io), max_depth) {}

  using Exiv2::QuickTimeVideo::tagDecoder;
};

// Build a DataBuf that should satisfy `assert(buf.size() > 4)` and include the 4-char atom/tag.
// Many QuickTime/MP4 parsers store size(4) + type(4), so we place tag at bytes[4..7].
Exiv2::DataBuf MakeAtomHeaderBuf(const char (&tag4)[5]) {
  Exiv2::DataBuf buf(8);
  buf.write_uint32(0, 8u, Exiv2::bigEndian);  // nominal atom size
  buf.write_uint8(4, static_cast<uint8_t>(tag4[0]));
  buf.write_uint8(5, static_cast<uint8_t>(tag4[1]));
  buf.write_uint8(6, static_cast<uint8_t>(tag4[2]));
  buf.write_uint8(7, static_cast<uint8_t>(tag4[3]));
  return buf;
}

class QuickTimeVideoTagDecoderTest_660 : public ::testing::Test {
 protected:
  static std::unique_ptr<QuickTimeVideo_ExposeTagDecoder> MakeSut(std::vector<Exiv2::byte> io_data,
                                                                  size_t max_depth = 8) {
    auto io = std::make_unique<MemBasicIo>(std::move(io_data));
    return std::make_unique<QuickTimeVideo_ExposeTagDecoder>(std::move(io), max_depth);
  }

  static bool HasXmpKey(Exiv2::XmpData& xmp, const std::string& key) {
    // `operator[]` will create entries, so we use findKey.
    Exiv2::XmpKey xk(key);
    return xmp.findKey(xk) != xmp.end();
  }
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// Normal operation: "dcom" sets Xmp.video.Compressor from the IO stream content.
// -------------------------------------------------------------------------------------------------
TEST_F(QuickTimeVideoTagDecoderTest_660, DcomSetsVideoCompressorFromIo_660) {
  auto sut = MakeSut(std::vector<Exiv2::byte>{'a', 'b', 'c'}, /*max_depth=*/8);
  Exiv2::DataBuf atom = MakeAtomHeaderBuf("dcom");

  ASSERT_FALSE(HasXmpKey(sut->xmpData(), "Xmp.video.Compressor"));

  EXPECT_NO_THROW(sut->tagDecoder(atom, /*size=*/3, /*recursion_depth=*/0));

  ASSERT_TRUE(HasXmpKey(sut->xmpData(), "Xmp.video.Compressor"));
  EXPECT_EQ(sut->xmpData()["Xmp.video.Compressor"].toString(), std::string("abc"));
}

// Boundary: "dcom" with size=0 should be handled without crashing; resulting string may be empty.
TEST_F(QuickTimeVideoTagDecoderTest_660, DcomWithZeroSizeDoesNotCrashAndStoresEmptyOrPresent_660) {
  auto sut = MakeSut(/*io_data=*/{}, /*max_depth=*/8);
  Exiv2::DataBuf atom = MakeAtomHeaderBuf("dcom");

  EXPECT_NO_THROW(sut->tagDecoder(atom, /*size=*/0, /*recursion_depth=*/0));

  // Observable: key should exist (operator[] path in implementation assigns).
  ASSERT_TRUE(HasXmpKey(sut->xmpData(), "Xmp.video.Compressor"));
  EXPECT_EQ(sut->xmpData()["Xmp.video.Compressor"].toString(), std::string(""));
}

// -------------------------------------------------------------------------------------------------
// Normal operation: "smhd" reads 8 bytes (two 4-byte reads) and sets Xmp.audio.Balance from uint16 BE.
// -------------------------------------------------------------------------------------------------
TEST_F(QuickTimeVideoTagDecoderTest_660, SmhdReadsTwoDwordsAndSetsAudioBalance_660) {
  // tagDecoder does two readOrThrow(...,4) calls, then interprets buf[0..1] big-endian.
  // Provide 8 bytes; the second 4 bytes will be the final content in buf.
  // Use 0x12 0x34 => 4660.
  std::vector<Exiv2::byte> io_data{
      0x00, 0x00, 0x00, 0x00,  // first read (ignored/overwritten)
      0x12, 0x34, 0x00, 0x00   // second read, balance in first two bytes
  };

  auto sut = MakeSut(std::move(io_data), /*max_depth=*/8);
  Exiv2::DataBuf atom = MakeAtomHeaderBuf("smhd");

  ASSERT_FALSE(HasXmpKey(sut->xmpData(), "Xmp.audio.Balance"));

  EXPECT_NO_THROW(sut->tagDecoder(atom, /*size=*/123 /*ignored by this branch*/, /*recursion_depth=*/0));

  ASSERT_TRUE(HasXmpKey(sut->xmpData(), "Xmp.audio.Balance"));
  EXPECT_EQ(sut->xmpData()["Xmp.audio.Balance"].toInt64(0), 0x1234);
}

// Error case: "smhd" requires 8 bytes of IO; insufficient data should throw via readOrThrow.
TEST_F(QuickTimeVideoTagDecoderTest_660, SmhdWithInsufficientIoDataThrows_660) {
  // Only 4 bytes available, but code reads 8 via readOrThrow.
  auto sut = MakeSut(std::vector<Exiv2::byte>{0x00, 0x00, 0x00, 0x00}, /*max_depth=*/8);
  Exiv2::DataBuf atom = MakeAtomHeaderBuf("smhd");

  EXPECT_ANY_THROW(sut->tagDecoder(atom, /*size=*/8, /*recursion_depth=*/0));
}

// -------------------------------------------------------------------------------------------------
// Recursion depth enforcement (observable as exception).
// -------------------------------------------------------------------------------------------------
TEST_F(QuickTimeVideoTagDecoderTest_660, RecursionDepthAtLimitThrows_660) {
  auto sut = MakeSut(/*io_data=*/{}, /*max_depth=*/1);
  Exiv2::DataBuf atom = MakeAtomHeaderBuf("dcom");

  // Enforced condition: recursion_depth < max_recursion_depth_
  EXPECT_ANY_THROW(sut->tagDecoder(atom, /*size=*/0, /*recursion_depth=*/1));
}

TEST_F(QuickTimeVideoTagDecoderTest_660, RecursionDepthBelowLimitDoesNotThrowForUnknownTag_660) {
  auto sut = MakeSut(/*io_data=*/{}, /*max_depth=*/1);
  Exiv2::DataBuf atom = MakeAtomHeaderBuf("zzzz");  // should fall to discard(size)

  EXPECT_NO_THROW(sut->tagDecoder(atom, /*size=*/0, /*recursion_depth=*/0));
}

// -------------------------------------------------------------------------------------------------
// Assertion contract: buf.size() must be > 4 (only testable in debug builds).
// -------------------------------------------------------------------------------------------------
#ifndef NDEBUG
TEST_F(QuickTimeVideoTagDecoderTest_660, BufSizeLessOrEqualFourTriggersAssert_660) {
  auto sut = MakeSut(/*io_data=*/{}, /*max_depth=*/8);
  Exiv2::DataBuf small(4);
  // tagDecoder has: assert(buf.size() > 4);
  EXPECT_DEATH(sut->tagDecoder(small, /*size=*/0, /*recursion_depth=*/0), ".*");
}
#endif