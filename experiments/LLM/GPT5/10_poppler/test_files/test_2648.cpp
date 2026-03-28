// ImageOutputDev_test_2648.cpp
#include <gtest/gtest.h>

#include <memory>
#include <type_traits>

#include "./TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

class ImageOutputDevTest_2648 : public ::testing::Test {
protected:
  static std::unique_ptr<ImageOutputDev> MakeDev() {
    // Be resilient to either a default-constructible ImageOutputDev (per partial code)
    // or the 3-arg constructor (per dependency listing).
    if constexpr (std::is_default_constructible_v<ImageOutputDev>) {
      return std::make_unique<ImageOutputDev>();
    } else {
      // Use a writable buffer for APIs that take char* (non-const).
      static char kRoot[] = "image-output-dev-test";
      return std::make_unique<ImageOutputDev>(kRoot, /*pageNamesA=*/false, /*listImagesA=*/false);
    }
  }
};

}  // namespace

TEST_F(ImageOutputDevTest_2648, NeedNonTextReturnsTrue_2648) {
  auto dev = MakeDev();
  ASSERT_NE(dev, nullptr);

  EXPECT_TRUE(dev->needNonText());
}

TEST_F(ImageOutputDevTest_2648, NeedNonTextIsStableAcrossMultipleCalls_2648) {
  auto dev = MakeDev();
  ASSERT_NE(dev, nullptr);

  EXPECT_TRUE(dev->needNonText());
  EXPECT_TRUE(dev->needNonText());
  EXPECT_TRUE(dev->needNonText());
}

TEST_F(ImageOutputDevTest_2648, NeedNonTextViaBasePointerIfApplicable_2648) {
  auto dev = MakeDev();
  ASSERT_NE(dev, nullptr);

  // Verify external/observable interaction: virtual dispatch through OutputDev if ImageOutputDev
  // is actually derived from OutputDev in this build.
  if constexpr (std::is_base_of_v<OutputDev, ImageOutputDev>) {
    OutputDev* base = dev.get();
    ASSERT_NE(base, nullptr);
    EXPECT_TRUE(base->needNonText());
  } else {
    // If the build's "partial" declaration doesn't derive from OutputDev, this is not applicable.
    SUCCEED();
  }
}