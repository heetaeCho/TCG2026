// poppler-ps-file-set-paper-size-test-2258.cc
#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>
#include <limits>

#include "poppler-private.h"

// This function is implemented in poppler-document.cc (GLib binding).
extern "C" void poppler_ps_file_set_paper_size(PopplerPSFile *ps_file, double width, double height);

namespace {

class PopplerPSFileSetPaperSizeTest_2258 : public ::testing::Test {
protected:
  void SetUp() override { std::memset(&ps_, 0, sizeof(ps_)); }

  PopplerPSFile ps_;
};

} // namespace

TEST_F(PopplerPSFileSetPaperSizeTest_2258, SetsPaperSizeWhenOutIsNull_2258) {
  ASSERT_EQ(ps_.out, nullptr);

  poppler_ps_file_set_paper_size(&ps_, 612.0, 792.0);

  EXPECT_DOUBLE_EQ(ps_.paper_width, 612.0);
  EXPECT_DOUBLE_EQ(ps_.paper_height, 792.0);
}

TEST_F(PopplerPSFileSetPaperSizeTest_2258, AllowsZeroSizes_2258) {
  ASSERT_EQ(ps_.out, nullptr);

  poppler_ps_file_set_paper_size(&ps_, 0.0, 0.0);

  EXPECT_DOUBLE_EQ(ps_.paper_width, 0.0);
  EXPECT_DOUBLE_EQ(ps_.paper_height, 0.0);
}

TEST_F(PopplerPSFileSetPaperSizeTest_2258, AllowsNegativeSizes_2258) {
  ASSERT_EQ(ps_.out, nullptr);

  poppler_ps_file_set_paper_size(&ps_, -1.0, -123.456);

  EXPECT_DOUBLE_EQ(ps_.paper_width, -1.0);
  EXPECT_DOUBLE_EQ(ps_.paper_height, -123.456);
}

TEST_F(PopplerPSFileSetPaperSizeTest_2258, AcceptsVeryLargeValues_2258) {
  ASSERT_EQ(ps_.out, nullptr);

  const double w = 1e308;
  const double h = 1e307;

  poppler_ps_file_set_paper_size(&ps_, w, h);

  EXPECT_DOUBLE_EQ(ps_.paper_width, w);
  EXPECT_DOUBLE_EQ(ps_.paper_height, h);
}

TEST_F(PopplerPSFileSetPaperSizeTest_2258, PropagatesNaNInputs_2258) {
  ASSERT_EQ(ps_.out, nullptr);

  const double nan = std::numeric_limits<double>::quiet_NaN();
  poppler_ps_file_set_paper_size(&ps_, nan, nan);

  EXPECT_TRUE(std::isnan(ps_.paper_width));
  EXPECT_TRUE(std::isnan(ps_.paper_height));
}

TEST_F(PopplerPSFileSetPaperSizeTest_2258, DoesNotChangePaperSizeWhenOutIsNonNull_2258) {
  // Simulate an "already started" PS output device (non-null out).
  ps_.out = reinterpret_cast<PSOutputDev*>(static_cast<std::uintptr_t>(0x1));

  ps_.paper_width = 100.0;
  ps_.paper_height = 200.0;

  poppler_ps_file_set_paper_size(&ps_, 300.0, 400.0);

  // Observable behavior: function should early-return and not modify paper size.
  EXPECT_DOUBLE_EQ(ps_.paper_width, 100.0);
  EXPECT_DOUBLE_EQ(ps_.paper_height, 200.0);
}

TEST_F(PopplerPSFileSetPaperSizeTest_2258, DoesNotChangePaperSizeWhenOutIsNonNullEvenForBoundaryValues_2258) {
  ps_.out = reinterpret_cast<PSOutputDev*>(static_cast<std::uintptr_t>(0x2));

  ps_.paper_width = -10.0;
  ps_.paper_height = 0.0;

  poppler_ps_file_set_paper_size(&ps_, 0.0, -0.0);

  EXPECT_DOUBLE_EQ(ps_.paper_width, -10.0);
  EXPECT_DOUBLE_EQ(ps_.paper_height, 0.0);
}