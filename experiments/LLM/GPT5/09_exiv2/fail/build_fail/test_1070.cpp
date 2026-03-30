// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include "basicio.hpp"
#include "image.hpp"
#include "xmp.hpp"

#include <cstdint>
#include <memory>

namespace {

// Minimal concrete Image we can instantiate for accessor tests.
class TestImage1070 final : public Exiv2::Image {
 public:
  explicit TestImage1070(Exiv2::BasicIo::UniquePtr io)
      : Exiv2::Image(Exiv2::ImageType::none, /*supportedMetadata=*/0, std::move(io)) {}
  ~TestImage1070() override = default;
};

class ImageXmpDataTest_1070 : public ::testing::Test {
 protected:
  static std::unique_ptr<TestImage1070> makeImage() {
    Exiv2::BasicIo::UniquePtr io(new Exiv2::MemIo());
    return std::make_unique<TestImage1070>(std::move(io));
  }
};

}  // namespace

TEST_F(ImageXmpDataTest_1070, ReturnsReferenceStableAcrossCalls_1070) {
  auto img = makeImage();
  ASSERT_NE(img, nullptr);

  Exiv2::XmpData& x1 = img->xmpData();
  Exiv2::XmpData& x2 = img->xmpData();

  EXPECT_EQ(&x1, &x2);  // Same underlying object returned each time.
}

TEST_F(ImageXmpDataTest_1070, AllowsMutationThroughReturnedReference_1070) {
  auto img = makeImage();
  ASSERT_NE(img, nullptr);

  Exiv2::XmpData& x1 = img->xmpData();
  EXPECT_NO_THROW({
    // Use a common XMP key; XmpData supports operator[] in Exiv2.
    x1["Xmp.dc.title"] = "UnitTestTitle";
  });

  Exiv2::XmpData& x2 = img->xmpData();
  EXPECT_EQ(&x1, &x2);

  // Observable effect: the datum exists and matches what we set.
  ASSERT_FALSE(x2.empty());
  EXPECT_EQ(x2["Xmp.dc.title"].toString(), "UnitTestTitle");
}

TEST_F(ImageXmpDataTest_1070, InitiallyEmptyXmpDataOnFreshInstance_1070) {
  auto img = makeImage();
  ASSERT_NE(img, nullptr);

  Exiv2::XmpData& x = img->xmpData();
  EXPECT_TRUE(x.empty());
}

TEST_F(ImageXmpDataTest_1070, AccessDoesNotThrowOnRepeatedCalls_1070) {
  auto img = makeImage();
  ASSERT_NE(img, nullptr);

  EXPECT_NO_THROW({
    for (int i = 0; i < 100; ++i) {
      (void)img->xmpData();
    }
  });
}