// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::ImageFactory::checkType
// TEST_ID: 1101
// *****************************************************************

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/types.hpp>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace {

/*!
 * A minimal in-memory BasicIo implementation for driving ImageFactory::checkType
 * through only the public BasicIo interface.
 *
 * This is a test double for an external collaborator (BasicIo).
 */
class MemoryBasicIo final : public Exiv2::BasicIo {
 public:
  explicit MemoryBasicIo(std::vector<Exiv2::byte> data)
      : data_(std::move(data)), pos_(0), isOpen_(false), eof_(false), err_(0) {}

  int open() override {
    isOpen_ = true;
    eof_ = false;
    err_ = 0;
    pos_ = std::min<Exiv2::size_type>(pos_, static_cast<Exiv2::size_type>(data_.size()));
    return 0;
  }

  int close() override {
    isOpen_ = false;
    return 0;
  }

  Exiv2::DataBuf read(size_t rcount) override {
    std::vector<Exiv2::byte> tmp(rcount);
    const size_t n = read(tmp.data(), rcount);
    Exiv2::DataBuf buf(n);
    if (n != 0) {
      std::memcpy(buf.pData_, tmp.data(), n);
    }
    return buf;
  }

  size_t read(Exiv2::byte* buf, size_t rcount) override {
    ++readCalls_;
    if (!isOpen_) {
      err_ = 1;
      return 0;
    }
    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = std::min(rcount, avail);
    if (n > 0) {
      std::memcpy(buf, data_.data() + pos_, n);
      pos_ += n;
      eof_ = (pos_ >= data_.size());
    } else {
      eof_ = true;
    }
    return n;
  }

  int getb() override {
    ++getbCalls_;
    Exiv2::byte b = 0;
    const size_t n = read(&b, 1);
    return (n == 1) ? static_cast<int>(b) : EOF;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    ++seekCalls_;
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
        base = 0;
        break;
    }

    const int64_t target = base + offset;
    if (target < 0) {
      err_ = 1;
      return 1;
    }
    pos_ = static_cast<size_t>(std::min<int64_t>(target, static_cast<int64_t>(data_.size())));
    eof_ = (pos_ >= data_.size());
    err_ = 0;
    return 0;
  }

  Exiv2::byte* mmap(bool /*isWriteable*/) override {
    ++mmapCalls_;
    if (!isOpen_) {
      err_ = 1;
      return nullptr;
    }
    err_ = 0;
    return data_.empty() ? nullptr : data_.data();
  }

  int munmap() override {
    ++munmapCalls_;
    return 0;
  }

  const size_t tell() override {
    ++tellCalls_;
    return pos_;
  }

  const size_t size() override {
    ++sizeCalls_;
    return data_.size();
  }

  const bool isopen() override {
    ++isopenCalls_;
    return isOpen_;
  }

  const int error() override { return err_; }

  const bool eof() override { return eof_; }

  const std::string& path() override { return path_; }

  // Intentionally keep write/transfer as defaults; checkType is expected to be read-only.

  // Observable interaction counters (public API via this test double).
  int readCalls() const { return readCalls_; }
  int getbCalls() const { return getbCalls_; }
  int seekCalls() const { return seekCalls_; }
  int mmapCalls() const { return mmapCalls_; }
  int munmapCalls() const { return munmapCalls_; }
  int tellCalls() const { return tellCalls_; }
  int sizeCalls() const { return sizeCalls_; }
  int isopenCalls() const { return isopenCalls_; }
  int totalIoCalls() const {
    return readCalls_ + getbCalls_ + seekCalls_ + mmapCalls_ + munmapCalls_ + tellCalls_ + sizeCalls_ +
           isopenCalls_;
  }

 private:
  std::vector<Exiv2::byte> data_;
  size_t pos_;
  bool isOpen_;
  bool eof_;
  int err_;
  std::string path_{"<memory>"};

  int readCalls_{0};
  int getbCalls_{0};
  int seekCalls_{0};
  int mmapCalls_{0};
  int munmapCalls_{0};
  int tellCalls_{0};
  int sizeCalls_{0};
  int isopenCalls_{0};
};

class ImageFactoryCheckTypeTest_1101 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> MakeJpegHeader() {
    // Minimal JPEG SOI + marker prefix
    return {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 'J', 'F', 'I', 'F', 0x00};
  }

  static std::vector<Exiv2::byte> MakePngHeader() {
    // PNG signature
    return {0x89, 'P', 'N', 'G', 0x0D, 0x0A, 0x1A, 0x0A};
  }

  static std::vector<Exiv2::byte> MakeGifHeader() {
    // GIF89a signature
    return {'G', 'I', 'F', '8', '9', 'a'};
  }

  static bool CheckType(Exiv2::ImageType type, Exiv2::BasicIo& io, bool advance) {
    // The implementation exists in the codebase; we only call the public interface.
    Exiv2::ImageFactory f;
    return f.checkType(type, io, advance);
  }
};

}  // namespace

// --- Normal operation --------------------------------------------------------

TEST_F(ImageFactoryCheckTypeTest_1101, JpegHeaderRecognizedAsJpeg_1101) {
  MemoryBasicIo io(MakeJpegHeader());
  ASSERT_EQ(0, io.open());

  const bool ok = CheckType(Exiv2::ImageType::jpeg, io, /*advance=*/false);

  EXPECT_TRUE(ok);

  // External interaction should be observable through BasicIo usage for known types.
  EXPECT_GT(io.totalIoCalls(), 0);

  (void)io.close();
}

TEST_F(ImageFactoryCheckTypeTest_1101, PngHeaderRecognizedAsPng_1101) {
  MemoryBasicIo io(MakePngHeader());
  ASSERT_EQ(0, io.open());

  const bool ok = CheckType(Exiv2::ImageType::png, io, /*advance=*/false);

  EXPECT_TRUE(ok);
  EXPECT_GT(io.totalIoCalls(), 0);

  (void)io.close();
}

// --- Negative / mismatch cases ----------------------------------------------

TEST_F(ImageFactoryCheckTypeTest_1101, JpegHeaderNotRecognizedAsPng_1101) {
  MemoryBasicIo io(MakeJpegHeader());
  ASSERT_EQ(0, io.open());

  const bool ok = CheckType(Exiv2::ImageType::png, io, /*advance=*/false);

  EXPECT_FALSE(ok);
  EXPECT_GT(io.totalIoCalls(), 0);

  (void)io.close();
}

TEST_F(ImageFactoryCheckTypeTest_1101, PngHeaderNotRecognizedAsGif_1101) {
  MemoryBasicIo io(MakePngHeader());
  ASSERT_EQ(0, io.open());

  const bool ok = CheckType(Exiv2::ImageType::gif, io, /*advance=*/false);

  EXPECT_FALSE(ok);
  EXPECT_GT(io.totalIoCalls(), 0);

  (void)io.close();
}

// --- Boundary conditions -----------------------------------------------------

TEST_F(ImageFactoryCheckTypeTest_1101, EmptyInputReturnsFalseForKnownType_1101) {
  MemoryBasicIo io(std::vector<Exiv2::byte>{});
  ASSERT_EQ(0, io.open());

  const bool ok = CheckType(Exiv2::ImageType::jpeg, io, /*advance=*/false);

  EXPECT_FALSE(ok);
  // Still may attempt to read/mmap; just ensure it doesn't crash and is observable.
  EXPECT_GE(io.totalIoCalls(), 0);

  (void)io.close();
}

TEST_F(ImageFactoryCheckTypeTest_1101, VeryShortInputReturnsFalseForKnownType_1101) {
  MemoryBasicIo io(std::vector<Exiv2::byte>{0xFF});  // too short to be JPEG
  ASSERT_EQ(0, io.open());

  const bool ok = CheckType(Exiv2::ImageType::jpeg, io, /*advance=*/false);

  EXPECT_FALSE(ok);
  EXPECT_GT(io.totalIoCalls(), 0);

  (void)io.close();
}

// --- Exceptional / error cases (observable) ---------------------------------
//
// From the provided implementation snippet:
//   if (auto r = Exiv2::find(registry, type)) return r->isThisType_(io, advance);
//   return false;
// If the type isn't in the registry, the function returns false and should not
// invoke the isThisType_ callback, hence should not need to touch io at all.
//
// We verify this purely through observable I/O interactions on our test double.

TEST_F(ImageFactoryCheckTypeTest_1101, UnknownTypeReturnsFalseWithoutTouchingIo_1101) {
  MemoryBasicIo io(MakeJpegHeader());
  ASSERT_EQ(0, io.open());

  // Use an ImageType value that is very likely not present in the registry.
  // This test is about observable behavior: returning false and not touching BasicIo.
  const auto unknownType = static_cast<Exiv2::ImageType>(-1);

  const bool ok = CheckType(unknownType, io, /*advance=*/false);

  EXPECT_FALSE(ok);
  EXPECT_EQ(io.totalIoCalls(), 0);

  (void)io.close();
}

// --- Advance flag behavior (observable, non-prescriptive) --------------------
//
// We do NOT assume what "advance" does internally; we only check that the API
// remains usable and that calls return consistent booleans for the same input.

TEST_F(ImageFactoryCheckTypeTest_1101, AdvanceFlagDoesNotChangeRecognitionResultForSameInput_1101) {
  const auto bytes = MakeGifHeader();

  MemoryBasicIo io1(bytes);
  ASSERT_EQ(0, io1.open());
  const bool r1 = CheckType(Exiv2::ImageType::gif, io1, /*advance=*/false);
  (void)io1.close();

  MemoryBasicIo io2(bytes);
  ASSERT_EQ(0, io2.open());
  const bool r2 = CheckType(Exiv2::ImageType::gif, io2, /*advance=*/true);
  (void)io2.close();

  EXPECT_EQ(r1, r2);
}