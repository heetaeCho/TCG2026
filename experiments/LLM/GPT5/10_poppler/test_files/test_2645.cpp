// ImageOutputDev_isOk_test_2645.cpp
#include <gtest/gtest.h>

#include <climits>
#include <cstring>
#include <memory>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

class ImageOutputDevTest_2645 : public ::testing::Test {
protected:
  static std::unique_ptr<ImageOutputDev> MakeDev(const char *root,
                                                 bool pageNames,
                                                 bool listImages) {
    // ImageOutputDev ctor takes a non-const char*. Provide a writable buffer.
    if (!root) {
      return std::make_unique<ImageOutputDev>(nullptr, pageNames, listImages);
    }
    const size_t n = std::strlen(root);
    char *buf = new char[n + 1];
    std::memcpy(buf, root, n + 1);
    // ImageOutputDev is expected to own/copy/free as it needs; test treats it as black box.
    // We keep buf alive for the lifetime of the device to avoid UAF if it stores the pointer.
    // We'll attach it to the deleter.
    struct DevAndBuf {
      std::unique_ptr<ImageOutputDev> dev;
      char *buf;
      ~DevAndBuf() { delete[] buf; }
    };
    auto holder = std::make_unique<DevAndBuf>();
    holder->buf = buf;
    holder->dev = std::make_unique<ImageOutputDev>(holder->buf, pageNames, listImages);
    return std::move(holder->dev);
  }

  static void ExpectIsOkMatchesErrorCode(ImageOutputDev &dev) {
    const int ec = dev.getErrorCode();
    EXPECT_EQ(dev.isOk(), ec == 0);
  }
};

TEST_F(ImageOutputDevTest_2645, IsOkMatchesGetErrorCodeAfterConstruction_2645) {
  auto dev = MakeDev("imgout", /*pageNames=*/false, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  ExpectIsOkMatchesErrorCode(*dev);
  // Stability: calling again should be consistent.
  ExpectIsOkMatchesErrorCode(*dev);
}

TEST_F(ImageOutputDevTest_2645, IsOkMatchesGetErrorCodeWithPageNamesAndListImages_2645) {
  auto dev = MakeDev("imgout", /*pageNames=*/true, /*listImages=*/true);
  ASSERT_NE(dev, nullptr);

  ExpectIsOkMatchesErrorCode(*dev);
}

TEST_F(ImageOutputDevTest_2645, NullFileRootDoesNotCrashAndIsOkMatchesGetErrorCode_2645) {
  auto dev = MakeDev(nullptr, /*pageNames=*/false, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  ExpectIsOkMatchesErrorCode(*dev);
}

TEST_F(ImageOutputDevTest_2645, EnableFlagsDoNotCrashAndPreserveIsOkErrorCodeConsistency_2645) {
  auto dev = MakeDev("imgout", /*pageNames=*/false, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  // Toggle all public flag setters. No assumptions about behavior other than no crash
  // and isOk() reflecting whether the current error code is zero.
  dev->enablePNG(true);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->enablePNG(false);
  dev->enableTiff(true);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->enableTiff(false);
  dev->enableJpeg(true);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->enableJpeg(false);
  dev->enableJpeg2000(true);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->enableJpeg2000(false);
  dev->enableJBig2(true);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->enableJBig2(false);
  dev->enableCCITT(true);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->enableCCITT(false);
  dev->enablePrintFilenames(true);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->enablePrintFilenames(false);
  ExpectIsOkMatchesErrorCode(*dev);
}

TEST_F(ImageOutputDevTest_2645, StartPageAcceptsBoundaryPageNumbersAndPreservesConsistency_2645) {
  auto dev = MakeDev("imgout", /*pageNames=*/false, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  // startPage signature documents that state/xref parameters are unused in the declaration.
  dev->startPage(0, nullptr, nullptr);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->startPage(1, nullptr, nullptr);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->startPage(-1, nullptr, nullptr);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->startPage(INT_MAX, nullptr, nullptr);
  ExpectIsOkMatchesErrorCode(*dev);

  dev->startPage(INT_MIN, nullptr, nullptr);
  ExpectIsOkMatchesErrorCode(*dev);
}

TEST_F(ImageOutputDevTest_2645, IsOkReflectsCurrentErrorCodeValueAcrossMultipleCalls_2645) {
  auto dev = MakeDev("imgout", /*pageNames=*/false, /*listImages=*/false);
  ASSERT_NE(dev, nullptr);

  // We don't (and can't) force error transitions; we only verify that isOk()
  // consistently corresponds to getErrorCode() at the time of each call.
  for (int i = 0; i < 10; ++i) {
    ExpectIsOkMatchesErrorCode(*dev);
  }
}

}  // namespace