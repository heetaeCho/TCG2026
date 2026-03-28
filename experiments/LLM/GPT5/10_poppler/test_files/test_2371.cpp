// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for poppler_signing_data_get_font_size()
// File-under-test: ./TestProjects/poppler/glib/poppler-form-field.cc

#include <gtest/gtest.h>

#include <cmath>
#include <limits>

extern "C" {
#include <glib.h>

// Include the implementation unit to access PopplerSigningData definition used by the function.
// This keeps the test black-box w.r.t. logic (we only exercise the public C API), while still
// allowing construction of a valid instance.
#include "poppler-form-field.cc"
}

namespace {

class PopplerSigningDataFontSizeTest_2371 : public ::testing::Test {
 protected:
  static PopplerSigningData* MakeSigningDataWithFontSize(double font_size) {
    auto* sd = static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData)));
    // Only set the field that the API under test reads.
    sd->font_size = font_size;
    return sd;
  }

  static void FreeSigningData(PopplerSigningData* sd) { g_free(sd); }
};

TEST_F(PopplerSigningDataFontSizeTest_2371, NullSigningDataReturnsDefault_2371) {
  // Observable behavior from g_return_val_if_fail: returns 20.0F on nullptr.
  const gdouble v = poppler_signing_data_get_font_size(nullptr);
  EXPECT_DOUBLE_EQ(v, 20.0);
}

TEST_F(PopplerSigningDataFontSizeTest_2371, ReturnsStoredFontSize_NormalValue_2371) {
  PopplerSigningData* sd = MakeSigningDataWithFontSize(12.5);
  ASSERT_NE(sd, nullptr);

  const gdouble v = poppler_signing_data_get_font_size(sd);
  EXPECT_DOUBLE_EQ(v, 12.5);

  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataFontSizeTest_2371, ReturnsStoredFontSize_Zero_2371) {
  PopplerSigningData* sd = MakeSigningDataWithFontSize(0.0);
  ASSERT_NE(sd, nullptr);

  const gdouble v = poppler_signing_data_get_font_size(sd);
  EXPECT_DOUBLE_EQ(v, 0.0);

  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataFontSizeTest_2371, ReturnsStoredFontSize_Negative_2371) {
  // No contract is exposed via the interface that negative values are rejected,
  // so we only verify the observable return value.
  PopplerSigningData* sd = MakeSigningDataWithFontSize(-3.25);
  ASSERT_NE(sd, nullptr);

  const gdouble v = poppler_signing_data_get_font_size(sd);
  EXPECT_DOUBLE_EQ(v, -3.25);

  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataFontSizeTest_2371, ReturnsStoredFontSize_LargeValue_2371) {
  const double large = 1.0e9;
  PopplerSigningData* sd = MakeSigningDataWithFontSize(large);
  ASSERT_NE(sd, nullptr);

  const gdouble v = poppler_signing_data_get_font_size(sd);
  EXPECT_DOUBLE_EQ(v, large);

  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataFontSizeTest_2371, ReturnsStoredFontSize_Infinity_2371) {
  const double inf = std::numeric_limits<double>::infinity();
  PopplerSigningData* sd = MakeSigningDataWithFontSize(inf);
  ASSERT_NE(sd, nullptr);

  const gdouble v = poppler_signing_data_get_font_size(sd);
  EXPECT_TRUE(std::isinf(v));
  EXPECT_GT(v, 0);

  FreeSigningData(sd);
}

TEST_F(PopplerSigningDataFontSizeTest_2371, ReturnsStoredFontSize_NaN_2371) {
  const double nanv = std::numeric_limits<double>::quiet_NaN();
  PopplerSigningData* sd = MakeSigningDataWithFontSize(nanv);
  ASSERT_NE(sd, nullptr);

  const gdouble v = poppler_signing_data_get_font_size(sd);
  EXPECT_TRUE(std::isnan(v));

  FreeSigningData(sd);
}

}  // namespace