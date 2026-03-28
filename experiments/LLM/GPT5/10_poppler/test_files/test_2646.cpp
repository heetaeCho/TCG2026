// ImageOutputDev_useTilingPatternFill_test_2646.cpp

#include <gtest/gtest.h>

#include <cstring>
#include <memory>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

// Small helper to provide a mutable, NUL-terminated char* as required by the ctor.
struct MutableCString {
  explicit MutableCString(const char *s) {
    const size_t n = std::strlen(s);
    buf.reset(new char[n + 1]);
    std::memcpy(buf.get(), s, n + 1);
  }
  char *get() const { return buf.get(); }
  std::unique_ptr<char[]> buf;
};

} // namespace

class ImageOutputDevTest_2646 : public ::testing::Test {
protected:
  void SetUp() override {
    // Use a simple valid root; we do not assume ownership semantics, so keep it alive.
    root = std::make_unique<MutableCString>("imgout");
    dev = std::make_unique<ImageOutputDev>(root->get(), /*pageNamesA=*/false, /*listImagesA=*/false);
  }

  std::unique_ptr<MutableCString> root;
  std::unique_ptr<ImageOutputDev> dev;
};

TEST_F(ImageOutputDevTest_2646, UseTilingPatternFillReturnsTrue_2646) {
  ASSERT_NE(dev, nullptr);
  EXPECT_TRUE(dev->useTilingPatternFill());
}

TEST_F(ImageOutputDevTest_2646, UseTilingPatternFillStableAcrossMultipleCalls_2646) {
  ASSERT_NE(dev, nullptr);
  EXPECT_TRUE(dev->useTilingPatternFill());
  EXPECT_TRUE(dev->useTilingPatternFill());
  EXPECT_TRUE(dev->useTilingPatternFill());
}

TEST_F(ImageOutputDevTest_2646, UseTilingPatternFillWorksViaBaseClassPointer_2646) {
  ASSERT_NE(dev, nullptr);
  OutputDev *base = dev.get();
  ASSERT_NE(base, nullptr);
  EXPECT_TRUE(base->useTilingPatternFill());
}

TEST_F(ImageOutputDevTest_2646, UseTilingPatternFillReturnsTrueWithPageNamesEnabled_2646) {
  auto root2 = std::make_unique<MutableCString>("imgout_pn");
  ImageOutputDev dev2(root2->get(), /*pageNamesA=*/true, /*listImagesA=*/false);
  EXPECT_TRUE(dev2.useTilingPatternFill());
}

TEST_F(ImageOutputDevTest_2646, UseTilingPatternFillReturnsTrueWithListImagesEnabled_2646) {
  auto root2 = std::make_unique<MutableCString>("imgout_li");
  ImageOutputDev dev2(root2->get(), /*pageNamesA=*/false, /*listImagesA=*/true);
  EXPECT_TRUE(dev2.useTilingPatternFill());
}