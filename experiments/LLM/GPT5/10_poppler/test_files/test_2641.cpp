// ImageOutputDev_enableJBig2_test_2641.cpp
#include <gtest/gtest.h>

#include <cstring>
#include <memory>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

class ImageOutputDevTest_2641 : public ::testing::Test {
protected:
  static std::unique_ptr<ImageOutputDev> MakeDev(const char *root,
                                                 bool pageNames,
                                                 bool listImages) {
    // Constructor takes char*, so provide an owned writable buffer.
    // We intentionally do not free this buffer here because ownership/copying
    // semantics are not part of the provided interface.
    char *buf = ::strdup(root ? root : "");
    return std::make_unique<ImageOutputDev>(buf, pageNames, listImages);
  }
};

TEST_F(ImageOutputDevTest_2641, EnableJBig2_TogglesWithoutChangingStatus_2641) {
  auto dev = MakeDev("imgoutdev_test_root_2641", /*pageNames=*/false, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  const int initialErr = dev->getErrorCode();
  const bool initialOk = dev->isOk();

  EXPECT_NO_THROW(dev->enableJBig2(true));
  EXPECT_EQ(dev->getErrorCode(), initialErr);
  EXPECT_EQ(dev->isOk(), initialOk);

  EXPECT_NO_THROW(dev->enableJBig2(false));
  EXPECT_EQ(dev->getErrorCode(), initialErr);
  EXPECT_EQ(dev->isOk(), initialOk);
}

TEST_F(ImageOutputDevTest_2641, EnableJBig2_RepeatedCallsSameValueAreSafe_2641) {
  auto dev = MakeDev("imgoutdev_test_root_2641_repeat", /*pageNames=*/true, /*listImages=*/true);
  ASSERT_NE(dev, nullptr);

  const int initialErr = dev->getErrorCode();
  const bool initialOk = dev->isOk();

  EXPECT_NO_THROW(dev->enableJBig2(true));
  EXPECT_NO_THROW(dev->enableJBig2(true));
  EXPECT_NO_THROW(dev->enableJBig2(true));
  EXPECT_EQ(dev->getErrorCode(), initialErr);
  EXPECT_EQ(dev->isOk(), initialOk);

  EXPECT_NO_THROW(dev->enableJBig2(false));
  EXPECT_NO_THROW(dev->enableJBig2(false));
  EXPECT_EQ(dev->getErrorCode(), initialErr);
  EXPECT_EQ(dev->isOk(), initialOk);
}

TEST_F(ImageOutputDevTest_2641, EnableJBig2_DoesNotAffectOtherFormatEnables_2641) {
  auto dev = MakeDev("imgoutdev_test_root_2641_formats", /*pageNames=*/false, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  const int initialErr = dev->getErrorCode();
  const bool initialOk = dev->isOk();

  // Exercise in combination with other public toggles (observable stability only).
  EXPECT_NO_THROW(dev->enablePNG(true));
  EXPECT_NO_THROW(dev->enableTiff(true));
  EXPECT_NO_THROW(dev->enableJpeg(true));
  EXPECT_NO_THROW(dev->enableJpeg2000(true));
  EXPECT_NO_THROW(dev->enableCCITT(true));

  EXPECT_EQ(dev->getErrorCode(), initialErr);
  EXPECT_EQ(dev->isOk(), initialOk);

  EXPECT_NO_THROW(dev->enableJBig2(true));
  EXPECT_EQ(dev->getErrorCode(), initialErr);
  EXPECT_EQ(dev->isOk(), initialOk);

  EXPECT_NO_THROW(dev->enableJBig2(false));
  EXPECT_EQ(dev->getErrorCode(), initialErr);
  EXPECT_EQ(dev->isOk(), initialOk);
}

TEST_F(ImageOutputDevTest_2641, EnableJBig2_CanBeCalledEvenIfDeviceNotOk_2641) {
  // We don't assume what makes the device "ok" or not. We only require that
  // calling enableJBig2 is safe and does not introduce new observable errors.
  auto dev = MakeDev("", /*pageNames=*/false, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  const int beforeErr = dev->getErrorCode();
  const bool beforeOk = dev->isOk();

  EXPECT_NO_THROW(dev->enableJBig2(true));
  EXPECT_NO_THROW(dev->enableJBig2(false));

  // Observable behavior requirement: enabling/disabling should not, by itself,
  // change the error/status immediately.
  EXPECT_EQ(dev->getErrorCode(), beforeErr);
  EXPECT_EQ(dev->isOk(), beforeOk);
}

}  // namespace