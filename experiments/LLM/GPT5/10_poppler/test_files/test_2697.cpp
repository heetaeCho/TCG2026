// getOutputFileName_test_2697.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>

// Pull in GooString.
#include "goo/GooString.h"

// The function under test is a static function in pdftocairo.cc.
// Include the .cc into this test TU so we can call it, while renaming main
// to avoid ODR conflicts if pdftocairo.cc defines one.
#define main pdftocairo_main_2697
#include "utils/pdftocairo.cc"
#undef main

using ::testing::ExitedWithCode;
using ::testing::HasSubstr;

namespace {

class GetOutputFileNameTest_2697 : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset globals to a known baseline before each test.
    ps = false;
    eps = false;
    pdf = false;
    svg = false;
    printToWin32 = false;
    printing = false;
    singleFile = false;
  }

  static std::unique_ptr<GooString> Call(GooString *fileName, GooString *outputName) {
    return getOutputFileName(fileName, outputName);
  }

  static std::string ToStd(const std::unique_ptr<GooString> &s) {
    return s ? s->toStr() : std::string();
  }
};

TEST_F(GetOutputFileNameTest_2697, OutputNameDashAllowedWhenPrinting_2697) {
  // stdout allowed when printing==true (and not printToWin32).
  printing = true;
  singleFile = false;
  printToWin32 = false;

  GooString in("input.pdf");
  GooString out("-");

  auto name = Call(&in, &out);
  ASSERT_NE(name, nullptr);
  EXPECT_EQ(ToStd(name), "fd://0");
}

TEST_F(GetOutputFileNameTest_2697, OutputNameDashAllowedWhenSingleFile_2697) {
  // stdout allowed when -singlefile is used.
  printing = false;
  singleFile = true;
  printToWin32 = false;

  GooString in("input.pdf");
  GooString out("-");

  auto name = Call(&in, &out);
  ASSERT_NE(name, nullptr);
  EXPECT_EQ(ToStd(name), "fd://0");
}

TEST_F(GetOutputFileNameTest_2697, OutputNameDashErrorsWhenNotPrintingAndNotSingleFile_2697) {
  printing = false;
  singleFile = false;
  printToWin32 = false;

  GooString in("input.pdf");
  GooString out("-");

  EXPECT_EXIT(
      {
        (void)Call(&in, &out);
      },
      ExitedWithCode(99),
      "stdout may only be used");
}

TEST_F(GetOutputFileNameTest_2697, OutputNameDashErrorsWhenPrintToWin32_2697) {
  // Even if printing/singleFile would allow, printToWin32 forbids '-'.
  printing = true;
  singleFile = true;
  printToWin32 = true;

  GooString in("input.pdf");
  GooString out("-");

  EXPECT_EXIT(
      {
        (void)Call(&in, &out);
      },
      ExitedWithCode(99),
      "stdout may only be used");
}

TEST_F(GetOutputFileNameTest_2697, OutputNameNonDashReturnsCopy_2697) {
  GooString in("input.pdf");
  GooString out("explicit-name.out");

  auto name = Call(&in, &out);
  ASSERT_NE(name, nullptr);
  EXPECT_EQ(ToStd(name), "explicit-name.out");

  // Observable behavior: should be a copy, not the same pointer.
  EXPECT_NE(name.get(), &out);
}

TEST_F(GetOutputFileNameTest_2697, NoOutputNamePrintToWin32ReturnsNull_2697) {
  printToWin32 = true;

  GooString in("input.pdf");

  auto name = Call(&in, nullptr);
  EXPECT_EQ(name, nullptr);
}

TEST_F(GetOutputFileNameTest_2697, NoOutputNameInputIsStdinErrors_2697) {
  // fileName == "fd://0" and no outputName -> error.
  GooString in("fd://0");

  EXPECT_EXIT(
      {
        (void)Call(&in, nullptr);
      },
      ExitedWithCode(99),
      "PDF file is stdin");
}

TEST_F(GetOutputFileNameTest_2697, NoOutputNamePdfOutputWithLocalInputErrors_2697) {
  // pdf output + local input path requires explicit output filename.
  pdf = true;

  GooString in("localfile.pdf");

  EXPECT_EXIT(
      {
        (void)Call(&in, nullptr);
      },
      ExitedWithCode(99),
      "output format is PDF");
}

TEST_F(GetOutputFileNameTest_2697, NoOutputNamePdfOutputWithHttpInputAllowed_2697) {
  // pdf output + http input is allowed by the interface logic.
  pdf = true;

  GooString in("http://example.com/dir/in.pdf");

  auto name = Call(&in, nullptr);
  ASSERT_NE(name, nullptr);
  // Basename "in.pdf" -> strip ".pdf" -> append ".pdf" => "in.pdf"
  EXPECT_EQ(ToStd(name), "in.pdf");
}

TEST_F(GetOutputFileNameTest_2697, NoOutputNameInvalidWhenPathEndsWithSlash_2697) {
  GooString in("/tmp/somedir/");

  EXPECT_EXIT(
      {
        (void)Call(&in, nullptr);
      },
      ExitedWithCode(99),
      "invalid output filename");
}

TEST_F(GetOutputFileNameTest_2697, DerivesBasenameFromPathAndAppendsPs_2697) {
  ps = true;

  GooString in("/tmp/a/b/input.pdf");

  auto name = Call(&in, nullptr);
  ASSERT_NE(name, nullptr);
  // "input.pdf" -> strip ".pdf" -> append ".ps"
  EXPECT_EQ(ToStd(name), "input.ps");
}

TEST_F(GetOutputFileNameTest_2697, StripsPdfExtensionCaseInsensitive_2697) {
  eps = true;

  GooString in("Report.PDF");

  auto name = Call(&in, nullptr);
  ASSERT_NE(name, nullptr);
  // "Report.PDF" -> strip -> "Report" -> append ".eps"
  EXPECT_EQ(ToStd(name), "Report.eps");
}

TEST_F(GetOutputFileNameTest_2697, DoesNotStripWhenNotEndingWithPdfExtension_2697) {
  svg = true;

  GooString in("file.pdf.backup");

  auto name = Call(&in, nullptr);
  ASSERT_NE(name, nullptr);
  // Not ending in ".pdf" so no strip; append ".svg".
  EXPECT_EQ(ToStd(name), "file.pdf.backup.svg");
}

TEST_F(GetOutputFileNameTest_2697, AppendsAccordingToFirstMatchingFlagPriority_2697) {
  // Priority in code: ps, else eps, else pdf, else svg.
  ps = true;
  eps = true;
  pdf = true;
  svg = true;

  GooString in("x.pdf");

  auto name = Call(&in, nullptr);
  ASSERT_NE(name, nullptr);
  EXPECT_EQ(ToStd(name), "x.ps");
}

TEST_F(GetOutputFileNameTest_2697, NoFormatFlagReturnsBasenamePossiblyStripped_2697) {
  // No ps/eps/pdf/svg set: the function returns base name with ".pdf" stripped if present.
  GooString in("/home/user/doc.pdf");

  auto name = Call(&in, nullptr);
  ASSERT_NE(name, nullptr);
  EXPECT_EQ(ToStd(name), "doc");
}

} // namespace