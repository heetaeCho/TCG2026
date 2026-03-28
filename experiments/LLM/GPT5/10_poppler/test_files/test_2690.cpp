// getOutputSize_test_2690.cc
#include <gtest/gtest.h>

// pdftocairo.cc (and the snippet shown) refers to these globals (defined in pdftoppm.cc).
// Provide definitions here so the test binary links, even if our test cases don't exercise
// the non-printing path that uses them.
double x_resolution = 150.0;
double y_resolution = 150.0;

// pdftocairo.cc is a utility program and commonly defines a main(). To avoid a duplicate
// symbol with gtest's main (or other test mains), rename it if present.
#define main pdftocairo_main_2690
// Include the implementation TU so we can call the `static` function as a black box.
#include "TestProjects/poppler/utils/pdftocairo.cc"
#undef main

namespace {

class GetOutputSizeTest_2690 : public ::testing::Test {
protected:
  void SetUp() override {
    saved_printing_ = printing;
    saved_usePDFPageSize_ = usePDFPageSize;
    saved_paperWidth_ = paperWidth;
    saved_paperHeight_ = paperHeight;
  }

  void TearDown() override {
    printing = saved_printing_;
    usePDFPageSize = saved_usePDFPageSize_;
    paperWidth = saved_paperWidth_;
    paperHeight = saved_paperHeight_;
  }

  bool saved_printing_{};
  bool saved_usePDFPageSize_{};
  int saved_paperWidth_{};
  int saved_paperHeight_{};
};

TEST_F(GetOutputSizeTest_2690, PrintingUsesPDFPageSizeWhenEnabled_2690) {
  printing = true;
  usePDFPageSize = true;

  // Set paper sizes to values that should be ignored on this path.
  paperWidth = 612;
  paperHeight = 792;

  double outW = -1.0, outH = -1.0;
  getOutputSize(/*page_w=*/200.5, /*page_h=*/100.25, &outW, &outH);

  EXPECT_DOUBLE_EQ(outW, 200.5);
  EXPECT_DOUBLE_EQ(outH, 100.25);
}

TEST_F(GetOutputSizeTest_2690, PrintingSwapsPaperSizeForLandscapePages_2690) {
  printing = true;
  usePDFPageSize = false;

  paperWidth = 210;
  paperHeight = 297;

  // Landscape: page_w > page_h => width=paperHeight, height=paperWidth.
  double outW = -1.0, outH = -1.0;
  getOutputSize(/*page_w=*/400.0, /*page_h=*/200.0, &outW, &outH);

  EXPECT_DOUBLE_EQ(outW, static_cast<double>(paperHeight));
  EXPECT_DOUBLE_EQ(outH, static_cast<double>(paperWidth));
}

TEST_F(GetOutputSizeTest_2690, PrintingKeepsPaperSizeForPortraitPages_2690) {
  printing = true;
  usePDFPageSize = false;

  paperWidth = 210;
  paperHeight = 297;

  // Portrait: page_w <= page_h (here strictly less) => width=paperWidth, height=paperHeight.
  double outW = -1.0, outH = -1.0;
  getOutputSize(/*page_w=*/200.0, /*page_h=*/400.0, &outW, &outH);

  EXPECT_DOUBLE_EQ(outW, static_cast<double>(paperWidth));
  EXPECT_DOUBLE_EQ(outH, static_cast<double>(paperHeight));
}

TEST_F(GetOutputSizeTest_2690, PrintingTreatsSquarePagesAsPortraitBranch_2690) {
  printing = true;
  usePDFPageSize = false;

  paperWidth = 100;
  paperHeight = 200;

  // Boundary: page_w == page_h should follow the non-landscape branch (page_w > page_h is false).
  double outW = -1.0, outH = -1.0;
  getOutputSize(/*page_w=*/300.0, /*page_h=*/300.0, &outW, &outH);

  EXPECT_DOUBLE_EQ(outW, static_cast<double>(paperWidth));
  EXPECT_DOUBLE_EQ(outH, static_cast<double>(paperHeight));
}

TEST_F(GetOutputSizeTest_2690, PrintingPropagatesNegativePaperSizesWithoutCrashing_2690) {
  printing = true;
  usePDFPageSize = false;

  // Boundary/error-like values: defaults from the file snippet are -1.
  paperWidth = -1;
  paperHeight = -1;

  double outW = 123.0, outH = 456.0;
  getOutputSize(/*page_w=*/10.0, /*page_h=*/20.0, &outW, &outH);

  // Observable behavior for this interface: width/height are assigned from paper sizes.
  EXPECT_DOUBLE_EQ(outW, -1.0);
  EXPECT_DOUBLE_EQ(outH, -1.0);
}

} // namespace