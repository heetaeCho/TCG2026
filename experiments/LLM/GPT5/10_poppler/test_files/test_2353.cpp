// SPDX-License-Identifier: GPL-2.0-or-later
// File: poppler-signing-data-test-2353.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

namespace {

static void ExpectColorEq(const PopplerColor &actual,
                          int expected_red,
                          int expected_green,
                          int expected_blue) {
  EXPECT_EQ(actual.red, expected_red);
  EXPECT_EQ(actual.green, expected_green);
  EXPECT_EQ(actual.blue, expected_blue);
}

class PopplerSigningDataTest_2353 : public ::testing::Test {
 protected:
  void TearDown() override {
    if (data_) {
      // Poppler exposes a dedicated destructor for this struct in the GLib API.
      poppler_signing_data_free(data_);
      data_ = nullptr;
    }
  }

  PopplerSigningData *data_ = nullptr;
};

TEST_F(PopplerSigningDataTest_2353, NewReturnsNonNullAndDefaultScalars_2353) {
  data_ = poppler_signing_data_new();
  ASSERT_NE(data_, nullptr);

  const gchar *password = poppler_signing_data_get_password(data_);
  ASSERT_NE(password, nullptr);
  EXPECT_STREQ(password, "");

  EXPECT_EQ(poppler_signing_data_get_page(data_), 0);

  EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(data_), 10.0);
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(data_), 20.0);
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(data_), 1.5);
}

TEST_F(PopplerSigningDataTest_2353, NewSetsExpectedDefaultColors_2353) {
  data_ = poppler_signing_data_new();
  ASSERT_NE(data_, nullptr);

  PopplerColor bg{};
  PopplerColor border{};
  PopplerColor font{};

  poppler_signing_data_get_background_color(data_, &bg);
  poppler_signing_data_get_border_color(data_, &border);
  poppler_signing_data_get_font_color(data_, &font);

  // Grey background: 0xEF00, 0xEF00, 0xEF00
  ExpectColorEq(bg, 0xEF00, 0xEF00, 0xEF00);

  // Red border: 0xFFFF, 0x0000, 0x0000
  ExpectColorEq(border, 0xFFFF, 0x0000, 0x0000);

  // Red font: 0xFFFF, 0x0000, 0x0000
  ExpectColorEq(font, 0xFFFF, 0x0000, 0x0000);
}

TEST_F(PopplerSigningDataTest_2353, SettersRoundTripBoundaryValues_2353) {
  data_ = poppler_signing_data_new();
  ASSERT_NE(data_, nullptr);

  // Boundary-ish values: page to a large positive int; sizes to 0; width to 0.
  poppler_signing_data_set_page(data_, G_MAXINT);
  EXPECT_EQ(poppler_signing_data_get_page(data_), G_MAXINT);

  poppler_signing_data_set_font_size(data_, 0.0);
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_font_size(data_), 0.0);

  poppler_signing_data_set_left_font_size(data_, 0.0);
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_left_font_size(data_), 0.0);

  poppler_signing_data_set_border_width(data_, 0.0);
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(data_), 0.0);

  // Color boundaries: 0x0000 .. 0xFFFF per component (PopplerColor uses int).
  PopplerColor c1{};
  c1.red = 0x0000;
  c1.green = 0xFFFF;
  c1.blue = 0x0000;
  poppler_signing_data_set_background_color(data_, &c1);

  PopplerColor out{};
  poppler_signing_data_get_background_color(data_, &out);
  ExpectColorEq(out, 0x0000, 0xFFFF, 0x0000);

  PopplerColor c2{};
  c2.red = 0xFFFF;
  c2.green = 0xFFFF;
  c2.blue = 0xFFFF;
  poppler_signing_data_set_border_color(data_, &c2);

  poppler_signing_data_get_border_color(data_, &out);
  ExpectColorEq(out, 0xFFFF, 0xFFFF, 0xFFFF);
}

TEST_F(PopplerSigningDataTest_2353, FreeIsSafeAfterNew_2353) {
  // Exceptional/error-ish case: ensure cleanup path is safe after construction.
  PopplerSigningData *local = poppler_signing_data_new();
  ASSERT_NE(local, nullptr);

  // Should not crash.
  poppler_signing_data_free(local);
}

}  // namespace