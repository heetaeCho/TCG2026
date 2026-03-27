// SPDX-License-Identifier: GPL-2.0-or-later
// TEST_ID 1041
//
// Unit tests for: Exiv2::newBmpInstance(BasicIo::UniquePtr io, bool create)
// File under test: ./TestProjects/exiv2/src/bmpimage.cpp

#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "basicio.hpp"
#include "image.hpp"

// If your build exposes the BMP image header separately, this include is usually fine.
// It isn't strictly required for calling newBmpInstance(), but it helps ensure symbols/types are available.
#include "bmpimage.hpp"

namespace {

// Minimal BasicIo test double that satisfies ownership semantics for passing into newBmpInstance.
// We avoid relying on any internal Exiv2 logic and do not attempt to emulate actual IO behavior.
class DummyBasicIo final : public Exiv2::BasicIo {
 public:
  DummyBasicIo() = default;
  ~DummyBasicIo() override = default;

  // BasicIo interface
  Exiv2::BasicIo::UniquePtr clone() const override { return std::make_unique<DummyBasicIo>(); }

  int open() override { return 0; }
  int close() override { return 0; }
  bool isopen() const override { return true; }
  int error() const override { return 0; }
  bool eof() const override { return false; }
  std::string path() const override { return std::string(); }

  long write(const Exiv2::byte* /*data*/, long /*wcount*/) override { return 0; }
  long write(Exiv2::BasicIo& /*src*/) override { return 0; }
  long read(Exiv2::byte* /*buf*/, long /*rcount*/) override { return 0; }

  int putb(Exiv2::byte /*data*/) override { return 0; }
  int getb() override { return 0; }

  Exiv2::byte* mmap(bool /*isWriteable*/ = false) override { return nullptr; }
  int munmap() override { return 0; }

  long tell() const override { return 0; }
  int seek(long /*offset*/, Exiv2::BasicIo::Position /*pos*/) override { return 0; }

  long size() const override { return 0; }

  int transfer(Exiv2::BasicIo& /*src*/) override { return 0; }
  int populateFakeData() override { return 0; }
  int temporary() const override { return 0; }
};

}  // namespace

class NewBmpInstanceTest_1041 : public ::testing::Test {};

TEST_F(NewBmpInstanceTest_1041, ReturnsNullptrWhenIoIsNull_1041) {
  // Boundary/error case: null UniquePtr passed in.
  Exiv2::BasicIo::UniquePtr io;
  auto img = Exiv2::newBmpInstance(std::move(io), /*create=*/false);
  EXPECT_EQ(img, nullptr);
}

TEST_F(NewBmpInstanceTest_1041, ReturnsNullptrOrNonNullButNeverThrowsWithDummyIo_1041) {
  // Normal-ish operation: a valid BasicIo object is passed.
  // We intentionally do NOT assume whether DummyBasicIo makes the image "good" or not.
  // The only observable contract we can assert from the interface is that it returns
  // either nullptr or a non-null UniquePtr, and should not throw.
  Exiv2::BasicIo::UniquePtr io = std::make_unique<DummyBasicIo>();

  EXPECT_NO_THROW({
    auto img = Exiv2::newBmpInstance(std::move(io), /*create=*/false);
    // Observable outcome: pointer is either null or non-null.
    // If non-null, it should behave like an Exiv2::Image polymorphic object.
    if (img) {
      // Minimal observable checks via public interface.
      EXPECT_TRUE(img->good());
      // Accessing a benign method to ensure vtable/polymorphism is intact.
      (void)img->mimeType();
    }
  });
}

TEST_F(NewBmpInstanceTest_1041, CreateFlagDoesNotBreakConstruction_1041) {
  // Boundary/compat: create flag is ignored in the implementation (commented parameter),
  // but we treat that as a black box and only check it doesn't change basic behavior.
  Exiv2::BasicIo::UniquePtr io1 = std::make_unique<DummyBasicIo>();
  Exiv2::BasicIo::UniquePtr io2 = std::make_unique<DummyBasicIo>();

  auto imgCreateFalse = Exiv2::newBmpInstance(std::move(io1), /*create=*/false);
  auto imgCreateTrue  = Exiv2::newBmpInstance(std::move(io2), /*create=*/true);

  // Both calls must be well-defined: either may be nullptr depending on "good()".
  // We don't assert equality; only that the calls completed and returned a valid UniquePtr state.
  // (UniquePtr itself is always a valid object; we check pointer value.)
  // If either is non-null, it should expose a usable Image interface.
  if (imgCreateFalse) {
    EXPECT_TRUE(imgCreateFalse->good());
    (void)imgCreateFalse->mimeType();
  }
  if (imgCreateTrue) {
    EXPECT_TRUE(imgCreateTrue->good());
    (void)imgCreateTrue->mimeType();
  }
}

TEST_F(NewBmpInstanceTest_1041, OwnershipIsTransferredFromCaller_1041) {
  // Boundary: confirm move-only ownership semantics are respected.
  auto io = std::make_unique<DummyBasicIo>();
  auto* raw = io.get();

  auto img = Exiv2::newBmpInstance(std::move(io), /*create=*/false);

  // After move, caller pointer must be null.
  EXPECT_EQ(io, nullptr);

  // We cannot observe whether the image kept/used the exact same pointer without peeking internally.
  // But we can at least ensure the call succeeded without UB, and if an image is returned,
  // it's a valid polymorphic object.
  if (img) {
    EXPECT_TRUE(img->good());
    (void)img->mimeType();
  }

  // Silence unused warning for raw (we only used it to illustrate "can't validate internal storage").
  (void)raw;
}