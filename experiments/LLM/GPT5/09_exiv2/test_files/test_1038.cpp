// ***************************************************************** -*- C++ -*-
// Unit tests for Exiv2::BmpImage (bmpimage.cpp)
// TEST_ID: 1038
// *****************************************************************

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>

// Exiv2 headers
#include "exiv2/bmpimage.hpp"
#include "exiv2/basicio.hpp"

namespace {

// A minimal BasicIo implementation for constructing BmpImage in tests.
// We keep behavior intentionally trivial: this is only a collaborator to allow
// object construction; tests do not depend on any internal BmpImage logic.
class DummyBasicIo final : public Exiv2::BasicIo {
 public:
  DummyBasicIo() = default;
  ~DummyBasicIo() override = default;

  // --- BasicIo interface ---
  int open() override { return 0; }
  int close() override { return 0; }
  int munmap() override { return 0; }

  long write(const Exiv2::byte* /*data*/, long /*wcount*/) override { return 0; }
  long write(Exiv2::BasicIo& /*src*/) override { return 0; }

  long read(Exiv2::byte* /*buf*/, long /*rcount*/) override { return 0; }

  int putb(Exiv2::byte /*data*/) override { return 0; }
  Exiv2::DataBuf read(long /*rcount*/) override { return Exiv2::DataBuf(); }

  int getb() override { return EOF; }

  void transfer(Exiv2::BasicIo& /*src*/) override {}

  Exiv2::size_t size() const override { return 0; }

  int seek(long /*offset*/, Exiv2::BasicIo::Position /*pos*/) override { return 0; }
  long tell() const override { return 0; }

  bool isopen() const override { return true; }
  int error() const override { return 0; }
  bool eof() const override { return true; }
  std::string path() const override { return std::string(); }

  Exiv2::BasicIo::AutoPtr temporary() const override {
    return Exiv2::BasicIo::AutoPtr(new DummyBasicIo());
  }

  Exiv2::byte* mmap(bool /*isWriteable*/ = false) override { return nullptr; }
  const Exiv2::byte* mmap(bool /*isWriteable*/ = false) const override { return nullptr; }
};

class BmpImageTest_1038 : public ::testing::Test {
 protected:
  static std::unique_ptr<Exiv2::BmpImage> makeBmpImage() {
    // Construct with a valid BasicIo::UniquePtr.
    Exiv2::BasicIo::UniquePtr io(new DummyBasicIo());
    return std::unique_ptr<Exiv2::BmpImage>(new Exiv2::BmpImage(std::move(io)));
  }
};

}  // namespace

// Normal operation: mimeType should match the implementation contract in bmpimage.cpp.
TEST_F(BmpImageTest_1038, MimeType_ReturnsExpectedMimeType_1038) {
  auto img = BmpImageTest_1038::makeBmpImage();
  ASSERT_NE(img, nullptr);

  const std::string mt = img->mimeType();
  EXPECT_EQ("image/x-ms-bmp", mt);
}

// Boundary-ish: repeated calls should be stable and not mutate observable state.
TEST_F(BmpImageTest_1038, MimeType_IsStableAcrossMultipleCalls_1038) {
  auto img = BmpImageTest_1038::makeBmpImage();
  ASSERT_NE(img, nullptr);

  const std::string a = img->mimeType();
  const std::string b = img->mimeType();
  const std::string c = img->mimeType();

  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
  EXPECT_EQ("image/x-ms-bmp", a);
}

// Boundary: ensure it works through base-class polymorphism (override is honored).
TEST_F(BmpImageTest_1038, MimeType_ThroughImageBasePointer_1038) {
  std::unique_ptr<Exiv2::Image> base = BmpImageTest_1038::makeBmpImage();
  ASSERT_NE(base, nullptr);

  EXPECT_EQ("image/x-ms-bmp", base->mimeType());
}