// File: test_imagefactory_open_1108.cpp
// Unit tests for Exiv2::ImageFactory::open(BasicIo::UniquePtr)
//
// Constraints respected:
// - Treat ImageFactory::open as a black box (no internal logic reimplementation).
// - Use only observable behavior (return value / exception).
// - Provide external collaborators via BasicIo subclasses / mocks.

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <exiv2/image.hpp>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace {

// A minimal in-memory BasicIo implementation to feed deterministic bytes to type sniffers.
// This is an external collaborator used only to provide observable input to ImageFactory::open.
class BufferIo final : public Exiv2::BasicIo {
 public:
  using byte = Exiv2::byte;

  explicit BufferIo(std::vector<byte> data, std::string path = "buffer://mem")
      : data_(std::move(data)), path_(std::move(path)) {}

  void setOpenRc(int rc) { open_rc_ = rc; }

  int open() override {
    opened_ = (open_rc_ == 0);
    pos_ = 0;
    return open_rc_;
  }

  int close() override {
    opened_ = false;
    return 0;
  }

  size_t read(byte* buf, size_t rcount) override {
    if (!opened_) return 0;
    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t n = std::min(rcount, avail);
    if (n > 0) {
      std::copy_n(data_.data() + pos_, n, buf);
      pos_ += n;
    }
    return n;
  }

  Exiv2::DataBuf read(size_t rcount) override {
    // Use the other read() to keep behavior consistent.
    Exiv2::DataBuf buf(rcount);
    const size_t n = read(buf.data(), rcount);
    if (n < rcount) {
      // DataBuf will still have size rcount, but only first n bytes are meaningful;
      // this is acceptable for our external collaborator.
    }
    return buf;
  }

  int seek(int64_t offset, Exiv2::Position pos) override {
    if (!opened_) return 1;

    int64_t base = 0;
    switch (pos) {
      case Exiv2::Position::beg:
        base = 0;
        break;
      case Exiv2::Position::cur:
        base = static_cast<int64_t>(pos_);
        break;
      case Exiv2::Position::end:
        base = static_cast<int64_t>(data_.size());
        break;
      default:
        return 1;
    }

    const int64_t np = base + offset;
    if (np < 0) return 1;
    pos_ = static_cast<size_t>(np);
    return 0;
  }

  const size_t tell() override { return pos_; }
  const size_t size() override { return data_.size(); }
  const bool isopen() override { return opened_; }
  const int error() override { return 0; }
  const bool eof() override { return opened_ && pos_ >= data_.size(); }
  const std::string& path() override { return path_; }

 private:
  std::vector<byte> data_;
  std::string path_;
  int open_rc_{0};
  bool opened_{false};
  size_t pos_{0};
};

class ImageFactoryOpenTest_1108 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> MakeJpegHeaderBytes() {
    // A common minimal JPEG signature: SOI (FF D8) followed by marker (FF E0) and "JFIF\0".
    return {
        static_cast<Exiv2::byte>(0xFF), static_cast<Exiv2::byte>(0xD8),
        static_cast<Exiv2::byte>(0xFF), static_cast<Exiv2::byte>(0xE0),
        static_cast<Exiv2::byte>('J'),  static_cast<Exiv2::byte>('F'),
        static_cast<Exiv2::byte>('I'),  static_cast<Exiv2::byte>('F'),
        static_cast<Exiv2::byte>(0x00),
    };
  }
};

// TEST_ID 1108
TEST_F(ImageFactoryOpenTest_1108, ThrowsOnOpenFailure_1108) {
  auto io = std::make_unique<BufferIo>(std::vector<Exiv2::byte>{}, "buffer://open-fails");
  io->setOpenRc(1);  // Non-zero means open() failed.

  Exiv2::ImageFactory factory;
  EXPECT_THROW(
      {
        auto img = factory.open(std::move(io));
        (void)img;
      },
      Exiv2::Error);
}

// TEST_ID 1108
TEST_F(ImageFactoryOpenTest_1108, ReturnsNullptrWhenNoRegisteredTypeMatches_1108) {
  // Provide bytes unlikely to match any supported image type.
  // Empty input should generally not match any magic.
  auto io = std::make_unique<BufferIo>(std::vector<Exiv2::byte>{}, "buffer://unknown");

  Exiv2::ImageFactory factory;
  Exiv2::Image::UniquePtr img = factory.open(std::move(io));

  EXPECT_EQ(img.get(), nullptr);
}

// TEST_ID 1108
TEST_F(ImageFactoryOpenTest_1108, ReturnsNonNullptrForRecognizedType_JpegLikeHeader_1108) {
  auto io = std::make_unique<BufferIo>(MakeJpegHeaderBytes(), "buffer://jpeg-like");

  Exiv2::ImageFactory factory;
  Exiv2::Image::UniquePtr img = factory.open(std::move(io));

  ASSERT_NE(img.get(), nullptr);
}

// TEST_ID 1108
TEST_F(ImageFactoryOpenTest_1108, ReturnsNonNullptrForRecognizedType_EvenWithExtraTrailingBytes_1108) {
  auto bytes = MakeJpegHeaderBytes();
  // Boundary-ish: ensure additional trailing bytes don't prevent recognition.
  bytes.insert(bytes.end(), 64, static_cast<Exiv2::byte>(0x00));

  auto io = std::make_unique<BufferIo>(bytes, "buffer://jpeg-like-with-padding");

  Exiv2::ImageFactory factory;
  Exiv2::Image::UniquePtr img = factory.open(std::move(io));

  ASSERT_NE(img.get(), nullptr);
}

}  // namespace