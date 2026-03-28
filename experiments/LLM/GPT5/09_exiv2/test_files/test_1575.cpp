// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/rw2image.hpp>

#include <memory>
#include <string>

namespace {

class Rw2ImageTest_1575 : public ::testing::Test {
 protected:
  static Exiv2::BasicIo::UniquePtr makeIo() {
    // Use an in-memory IO to avoid filesystem dependencies.
    return Exiv2::BasicIo::UniquePtr(new Exiv2::MemIo());
  }
};

TEST_F(Rw2ImageTest_1575, MimeTypeReturnsExpectedString_1575) {
  Exiv2::Rw2Image image(makeIo());
  EXPECT_EQ(image.mimeType(), std::string("image/x-panasonic-rw2"));
}

TEST_F(Rw2ImageTest_1575, MimeTypeCallableOnConst_1575) {
  const Exiv2::Rw2Image image(makeIo());
  EXPECT_NO_THROW({
    const std::string mt = image.mimeType();
    EXPECT_EQ(mt, std::string("image/x-panasonic-rw2"));
  });
}

TEST_F(Rw2ImageTest_1575, MimeTypeStableAcrossMultipleCalls_1575) {
  Exiv2::Rw2Image image(makeIo());

  const std::string first = image.mimeType();
  const std::string second = image.mimeType();
  const std::string third = image.mimeType();

  EXPECT_EQ(first, std::string("image/x-panasonic-rw2"));
  EXPECT_EQ(second, first);
  EXPECT_EQ(third, first);
}

TEST_F(Rw2ImageTest_1575, MimeTypeViaBaseClassPointer_1575) {
  std::unique_ptr<Exiv2::Image> img = std::make_unique<Exiv2::Rw2Image>(makeIo());

  EXPECT_NO_THROW({
    const std::string mt = img->mimeType();
    EXPECT_EQ(mt, std::string("image/x-panasonic-rw2"));
  });
}

}  // namespace