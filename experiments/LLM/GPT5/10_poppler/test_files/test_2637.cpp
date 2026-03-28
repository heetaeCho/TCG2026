// File: ImageOutputDev_enablePNG_test_2637.cc

#include <gtest/gtest.h>

#include <cstring>
#include <memory>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

class ImageOutputDevTest_2637 : public ::testing::Test {
protected:
  static std::unique_ptr<ImageOutputDev> MakeDev() {
    // ImageOutputDev takes a mutable char*; keep storage alive for object lifetime.
    // Using a heap buffer avoids accidental decay of string literals to non-mutable char*.
    const char *kRoot = "imgoutdev_test_root";
    auto buf = std::make_unique<char[]>(std::strlen(kRoot) + 1);
    std::strcpy(buf.get(), kRoot);

    // NOTE: We intentionally do not assume behavior of pageNames/listImages beyond construction.
    // pageNamesA=false, listImagesA=false should be a "normal operation" configuration.
    // The ImageOutputDev is expected to manage/copy the passed-in root as needed.
    // If it stores the pointer, this buffer remains alive only during construction here,
    // so we instead keep it static for the duration of the test process.
    // To avoid lifetime assumptions, use a static buffer.
    static char staticRoot[64];
    std::strncpy(staticRoot, kRoot, sizeof(staticRoot) - 1);
    staticRoot[sizeof(staticRoot) - 1] = '\0';

    return std::make_unique<ImageOutputDev>(staticRoot, /*pageNamesA=*/false, /*listImagesA=*/false);
  }
};

TEST_F(ImageOutputDevTest_2637, EnablePNGTrueDoesNotCrash_2637) {
  auto dev = MakeDev();
  ASSERT_NE(dev, nullptr);

  // Observable behavior from the provided interface: the call should be valid.
  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(true));
}

TEST_F(ImageOutputDevTest_2637, EnablePNGFalseDoesNotCrash_2637) {
  auto dev = MakeDev();
  ASSERT_NE(dev, nullptr);

  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(false));
}

TEST_F(ImageOutputDevTest_2637, EnablePNGCanToggleMultipleTimes_2637) {
  auto dev = MakeDev();
  ASSERT_NE(dev, nullptr);

  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(true));
  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(false));
  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(true));
  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(false));
}

TEST_F(ImageOutputDevTest_2637, EnablePNGIdempotentCallsAreSafe_2637) {
  auto dev = MakeDev();
  ASSERT_NE(dev, nullptr);

  // Boundary-style coverage: repeated same-value updates should be safe.
  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(true));
  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(true));

  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(false));
  EXPECT_NO_FATAL_FAILURE(dev->enablePNG(false));
}

}  // namespace