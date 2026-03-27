// parse_jpeg_options_test_2653.cc
#include <gtest/gtest.h>

#include <string>

// pdftoppm.cc is a utility with its own main(). Rename it to avoid clashing
// with gtest_main (or any other test runner main).
#define main pdftoppm_main
#include "utils/pdftoppm.cc"
#undef main

namespace {

class ParseJpegOptionsTest_2653 : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset globals to documented defaults before each test.
    jpegOpt = GooString("");
    jpegQuality = -1;
    jpegProgressive = false;
    jpegOptimize = false;
  }

  static std::string CaptureParseStderrAndRun(bool *result_out) {
    testing::internal::CaptureStderr();
    const bool r = parseJpegOptions();
    std::string err = testing::internal::GetCapturedStderr();
    if (result_out) {
      *result_out = r;
    }
    return err;
  }
};

TEST_F(ParseJpegOptionsTest_2653, EmptyOptionsReturnsTrue_2653) {
  jpegOpt = GooString("");
  bool ok = false;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(err.empty());

  EXPECT_EQ(jpegQuality, -1);
  EXPECT_FALSE(jpegProgressive);
  EXPECT_FALSE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, QualityValidSetsQuality_2653) {
  jpegOpt = GooString("quality=90");
  bool ok = false;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(jpegQuality, 90);
  EXPECT_FALSE(jpegProgressive);
  EXPECT_FALSE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, QualityBoundaryValuesAccepted_2653) {
  jpegOpt = GooString("quality=0");
  bool ok0 = false;
  std::string err0 = CaptureParseStderrAndRun(&ok0);
  EXPECT_TRUE(ok0);
  EXPECT_TRUE(err0.empty());
  EXPECT_EQ(jpegQuality, 0);

  // Reset for the second boundary check.
  jpegOpt = GooString("quality=100");
  jpegQuality = -1;
  bool ok100 = false;
  std::string err100 = CaptureParseStderrAndRun(&ok100);
  EXPECT_TRUE(ok100);
  EXPECT_TRUE(err100.empty());
  EXPECT_EQ(jpegQuality, 100);
}

TEST_F(ParseJpegOptionsTest_2653, QualityNonIntegerRejected_2653) {
  jpegOpt = GooString("quality=abc");
  bool ok = true;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("Invalid jpeg quality"), std::string::npos);
  EXPECT_EQ(jpegQuality, -1);
}

TEST_F(ParseJpegOptionsTest_2653, QualityOutOfRangeRejected_2653) {
  jpegOpt = GooString("quality=-1");
  bool ok_neg = true;
  const std::string err_neg = CaptureParseStderrAndRun(&ok_neg);
  EXPECT_FALSE(ok_neg);
  EXPECT_NE(err_neg.find("jpeg quality must be between 0 and 100"), std::string::npos);

  // Reset and test > 100.
  jpegOpt = GooString("quality=101");
  jpegQuality = -1;
  bool ok_hi = true;
  const std::string err_hi = CaptureParseStderrAndRun(&ok_hi);
  EXPECT_FALSE(ok_hi);
  EXPECT_NE(err_hi.find("jpeg quality must be between 0 and 100"), std::string::npos);
}

TEST_F(ParseJpegOptionsTest_2653, MissingEqualsRejected_2653) {
  jpegOpt = GooString("quality");
  bool ok = true;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("Unknown jpeg option"), std::string::npos);
}

TEST_F(ParseJpegOptionsTest_2653, UnknownOptionKeyRejected_2653) {
  jpegOpt = GooString("bogus=1");
  bool ok = true;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("Unknown jpeg option"), std::string::npos);
}

TEST_F(ParseJpegOptionsTest_2653, ProgressiveYAndNAreHandled_2653) {
  jpegOpt = GooString("progressive=y");
  bool ok_y = false;
  std::string err_y = CaptureParseStderrAndRun(&ok_y);
  EXPECT_TRUE(ok_y);
  EXPECT_TRUE(err_y.empty());
  EXPECT_TRUE(jpegProgressive);

  // Reset for "n".
  jpegOpt = GooString("progressive=n");
  jpegProgressive = true;
  bool ok_n = false;
  std::string err_n = CaptureParseStderrAndRun(&ok_n);
  EXPECT_TRUE(ok_n);
  EXPECT_TRUE(err_n.empty());
  EXPECT_FALSE(jpegProgressive);
}

TEST_F(ParseJpegOptionsTest_2653, ProgressiveInvalidValueRejected_2653) {
  jpegOpt = GooString("progressive=maybe");
  bool ok = true;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("jpeg progressive option must be \"y\" or \"n\""), std::string::npos);
}

TEST_F(ParseJpegOptionsTest_2653, OptimizeAndOptimiseAreAliases_2653) {
  jpegOpt = GooString("optimize=y");
  bool ok_opt = false;
  std::string err_opt = CaptureParseStderrAndRun(&ok_opt);
  EXPECT_TRUE(ok_opt);
  EXPECT_TRUE(err_opt.empty());
  EXPECT_TRUE(jpegOptimize);

  // Reset and test "optimise".
  jpegOpt = GooString("optimise=y");
  jpegOptimize = false;
  bool ok_optimise = false;
  std::string err_optimise = CaptureParseStderrAndRun(&ok_optimise);
  EXPECT_TRUE(ok_optimise);
  EXPECT_TRUE(err_optimise.empty());
  EXPECT_TRUE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, OptimizeInvalidValueRejected_2653) {
  jpegOpt = GooString("optimize=1");
  bool ok = true;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("jpeg optimize option must be \"y\" or \"n\""), std::string::npos);
}

TEST_F(ParseJpegOptionsTest_2653, MultipleOptionsApplyAllWhenValid_2653) {
  jpegOpt = GooString("quality=85,progressive=y,optimize=n");
  bool ok = false;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(jpegQuality, 85);
  EXPECT_TRUE(jpegProgressive);
  EXPECT_FALSE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, StopsAndReturnsFalseOnFirstError_2653) {
  jpegOpt = GooString("quality=80,unknown=1,progressive=y");
  bool ok = true;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_FALSE(ok);
  EXPECT_NE(err.find("Unknown jpeg option"), std::string::npos);

  // Observable side-effect from the first (valid) option may still be applied.
  EXPECT_EQ(jpegQuality, 80);
  // Subsequent options should not be relied upon; ensure defaults remain for others.
  EXPECT_FALSE(jpegProgressive);
  EXPECT_FALSE(jpegOptimize);
}

TEST_F(ParseJpegOptionsTest_2653, TrailingCommaIsTolerated_2653) {
  jpegOpt = GooString("quality=75,");
  bool ok = false;
  const std::string err = CaptureParseStderrAndRun(&ok);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(jpegQuality, 75);
}

} // namespace