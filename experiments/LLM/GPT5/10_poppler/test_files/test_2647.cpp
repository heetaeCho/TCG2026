// File: ImageOutputDev_test_2647.cpp

#include <gtest/gtest.h>

#include "TestProjects/poppler/utils/ImageOutputDev.h"

namespace {

class ImageOutputDevTest_2647 : public ::testing::Test {
protected:
  // Helper to build a mutable C-string since the ctor takes char*.
  static char *MakeFileRoot(const char *s, std::array<char, 64> &buf) {
    std::snprintf(buf.data(), buf.size(), "%s", s ? s : "");
    return buf.data();
  }
};

TEST_F(ImageOutputDevTest_2647, InterpretType3CharsAlwaysFalse_DefaultFlags_2647) {
  std::array<char, 64> rootBuf{};
  char *root = MakeFileRoot("img-output", rootBuf);

  ImageOutputDev dev(root, /*pageNamesA=*/false, /*listImagesA=*/false);

  EXPECT_FALSE(dev.interpretType3Chars());
}

TEST_F(ImageOutputDevTest_2647, InterpretType3CharsAlwaysFalse_WithDifferentCtorArgs_2647) {
  std::array<char, 64> rootBuf{};
  char *root = MakeFileRoot("img-output-other", rootBuf);

  ImageOutputDev dev(root, /*pageNamesA=*/true, /*listImagesA=*/true);

  EXPECT_FALSE(dev.interpretType3Chars());
}

TEST_F(ImageOutputDevTest_2647, InterpretType3CharsFalseViaBasePointerVirtualDispatch_2647) {
  std::array<char, 64> rootBuf{};
  char *root = MakeFileRoot("img-output-base", rootBuf);

  ImageOutputDev dev(root, /*pageNamesA=*/false, /*listImagesA=*/true);

  OutputDev *base = &dev;
  ASSERT_NE(base, nullptr);

  EXPECT_FALSE(base->interpretType3Chars());
}

}  // namespace