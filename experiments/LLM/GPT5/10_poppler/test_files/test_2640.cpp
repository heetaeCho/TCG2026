// ImageOutputDev_enableJpeg2000_test_2640.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <memory>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

class ImageOutputDevTest_2640 : public ::testing::Test {
protected:
  static char *DupCStr(const char *s) {
#if defined(_MSC_VER)
    return _strdup(s);
#else
    return ::strdup(s);
#endif
  }

  std::unique_ptr<ImageOutputDev> MakeDev() {
    // Allocate a writable C-string because the constructor takes `char *`.
    // We avoid passing string literals in case the implementation takes ownership.
    char *root = DupCStr("imageoutputdev_test_root_2640");
    return std::unique_ptr<ImageOutputDev>(new ImageOutputDev(root, /*pageNamesA=*/false,
                                                             /*listImagesA=*/false));
  }
};

TEST_F(ImageOutputDevTest_2640, EnableJpeg2000AcceptsFalse_2640) {
  auto dev = MakeDev();

  // Snapshot observable state (if available through public interface).
  const int errBefore = dev->getErrorCode();
  const bool okBefore = dev->isOk();

  EXPECT_NO_THROW(dev->enableJpeg2000(false));

  // Enabling/disabling a feature flag should not unexpectedly break basic status.
  EXPECT_EQ(dev->getErrorCode(), errBefore);
  EXPECT_EQ(dev->isOk(), okBefore);
}

TEST_F(ImageOutputDevTest_2640, EnableJpeg2000AcceptsTrue_2640) {
  auto dev = MakeDev();

  const int errBefore = dev->getErrorCode();
  const bool okBefore = dev->isOk();

  EXPECT_NO_THROW(dev->enableJpeg2000(true));

  EXPECT_EQ(dev->getErrorCode(), errBefore);
  EXPECT_EQ(dev->isOk(), okBefore);
}

TEST_F(ImageOutputDevTest_2640, EnableJpeg2000IsIdempotentForSameValue_2640) {
  auto dev = MakeDev();

  const int errBefore = dev->getErrorCode();
  const bool okBefore = dev->isOk();

  EXPECT_NO_THROW(dev->enableJpeg2000(true));
  EXPECT_NO_THROW(dev->enableJpeg2000(true));
  EXPECT_NO_THROW(dev->enableJpeg2000(true));

  EXPECT_EQ(dev->getErrorCode(), errBefore);
  EXPECT_EQ(dev->isOk(), okBefore);
}

TEST_F(ImageOutputDevTest_2640, EnableJpeg2000CanToggleMultipleTimes_2640) {
  auto dev = MakeDev();

  const int errBefore = dev->getErrorCode();
  const bool okBefore = dev->isOk();

  EXPECT_NO_THROW(dev->enableJpeg2000(false));
  EXPECT_NO_THROW(dev->enableJpeg2000(true));
  EXPECT_NO_THROW(dev->enableJpeg2000(false));
  EXPECT_NO_THROW(dev->enableJpeg2000(true));

  EXPECT_EQ(dev->getErrorCode(), errBefore);
  EXPECT_EQ(dev->isOk(), okBefore);
}

}  // namespace