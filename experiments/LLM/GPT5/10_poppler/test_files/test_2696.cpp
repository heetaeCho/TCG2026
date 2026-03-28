// getImageFileName_test_2696.cc
#include <gtest/gtest.h>

#include <memory>
#include <string>

#include "TestProjects/poppler/goo/GooString.h"

// These globals are defined elsewhere (not in this TU).
extern bool singleFile;
extern bool png;
extern bool jpeg;
extern bool tiff;

// pdftocairo.cc is a utility program source file and may define `main`.
// Rename it to avoid clashing with gtest main.
#define main pdftocairo_main
#include "TestProjects/poppler/utils/pdftocairo.cc"
#undef main

namespace {

class GetImageFileNameTest_2696 : public ::testing::Test {
protected:
  void SetUp() override
  {
    saved_singleFile_ = singleFile;
    saved_png_ = png;
    saved_jpeg_ = jpeg;
    saved_tiff_ = tiff;

    // Default all flags off; each test enables what it needs.
    singleFile = false;
    png = false;
    jpeg = false;
    tiff = false;
  }

  void TearDown() override
  {
    singleFile = saved_singleFile_;
    png = saved_png_;
    jpeg = saved_jpeg_;
    tiff = saved_tiff_;
  }

  static std::string ToStdString(const std::unique_ptr<GooString> &s)
  {
    EXPECT_NE(s, nullptr);
    return s ? s->toStr() : std::string();
  }

private:
  bool saved_singleFile_ = false;
  bool saved_png_ = false;
  bool saved_jpeg_ = false;
  bool saved_tiff_ = false;
};

TEST_F(GetImageFileNameTest_2696, AppendsPageSuffixAndPngExtensionWhenNotSingleFile_2696)
{
  singleFile = false;
  png = true;

  GooString base("out");
  auto name = getImageFileName(&base, /*numDigits=*/3, /*page=*/7);

  EXPECT_EQ(ToStdString(name), "out-007.png");
}

TEST_F(GetImageFileNameTest_2696, DoesNotAppendPageSuffixWhenSingleFile_2696)
{
  singleFile = true;
  png = true;

  GooString base("out");
  auto name = getImageFileName(&base, /*numDigits=*/3, /*page=*/7);

  EXPECT_EQ(ToStdString(name), "out.png");
}

TEST_F(GetImageFileNameTest_2696, DoesNotAppendImageExtensionForFd0_2696)
{
  singleFile = false;
  png = true; // even if png is true, fd://0 should not get an extension

  GooString base("fd://0");
  auto name = getImageFileName(&base, /*numDigits=*/2, /*page=*/1);

  EXPECT_EQ(ToStdString(name), "fd://0-01");
}

TEST_F(GetImageFileNameTest_2696, NoExtensionWhenNoFormatFlagsEnabled_2696)
{
  singleFile = false;
  // png/jpeg/tiff all false

  GooString base("out");
  auto name = getImageFileName(&base, /*numDigits=*/2, /*page=*/1);

  EXPECT_EQ(ToStdString(name), "out-01");
}

TEST_F(GetImageFileNameTest_2696, PrefersPngOverJpegAndTiffWhenMultipleEnabled_2696)
{
  singleFile = false;
  png = true;
  jpeg = true;
  tiff = true;

  GooString base("out");
  auto name = getImageFileName(&base, /*numDigits=*/1, /*page=*/2);

  EXPECT_EQ(ToStdString(name), "out-2.png");
}

TEST_F(GetImageFileNameTest_2696, AppendsJpegExtensionWhenJpegEnabled_2696)
{
  singleFile = false;
  jpeg = true;

  GooString base("out");
  auto name = getImageFileName(&base, /*numDigits=*/2, /*page=*/9);

  EXPECT_EQ(ToStdString(name), "out-09.jpg");
}

TEST_F(GetImageFileNameTest_2696, AppendsTiffExtensionWhenTiffEnabled_2696)
{
  singleFile = false;
  tiff = true;

  GooString base("out");
  auto name = getImageFileName(&base, /*numDigits=*/2, /*page=*/9);

  EXPECT_EQ(ToStdString(name), "out-09.tif");
}

TEST_F(GetImageFileNameTest_2696, NumDigitsZeroProducesNoZeroPadding_2696)
{
  singleFile = false;
  jpeg = true;

  GooString base("out");
  auto name = getImageFileName(&base, /*numDigits=*/0, /*page=*/5);

  EXPECT_EQ(ToStdString(name), "out-5.jpg");
}

} // namespace