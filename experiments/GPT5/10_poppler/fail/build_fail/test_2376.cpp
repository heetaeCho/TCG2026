// SPDX-License-Identifier: GPL-2.0-or-later
//
// Unit tests for poppler_signing_data_set_border_width()
// File under test: ./TestProjects/poppler/glib/poppler-form-field.cc

#include <gtest/gtest.h>

#include <glib.h>

// Include the implementation unit to access the concrete PopplerSigningData
// definition used by this test project build and to link the function under test.
#include "poppler-form-field.cc"

namespace {

class PopplerSigningDataSetBorderWidthTest_2376 : public ::testing::Test {
protected:
  static PopplerSigningData* NewSigningData() {
    // Use GLib allocator and zero-init to keep fields in a known state.
    return g_new0(PopplerSigningData, 1);
  }

  static void FreeSigningData(PopplerSigningData* data) {
    g_free(data);
  }
};

} // namespace

TEST_F(PopplerSigningDataSetBorderWidthTest_2376, NullSigningDataDoesNotCrash_2376) {
  // Error/exceptional case: g_return_if_fail() should safely return.
  EXPECT_NO_FATAL_FAILURE(poppler_signing_data_set_border_width(nullptr, 1.0));
}

TEST_F(PopplerSigningDataSetBorderWidthTest_2376, NegativeWidthDoesNotModifyExistingValue_2376) {
  PopplerSigningData* data = NewSigningData();
  ASSERT_NE(data, nullptr);

  data->border_width = 7;

  poppler_signing_data_set_border_width(data, -1.0);

  // Observable behavior: negative input should not change stored width.
  EXPECT_EQ(data->border_width, 7);

  FreeSigningData(data);
}

TEST_F(PopplerSigningDataSetBorderWidthTest_2376, ZeroWidthSetsValueToZero_2376) {
  PopplerSigningData* data = NewSigningData();
  ASSERT_NE(data, nullptr);

  data->border_width = 9;

  poppler_signing_data_set_border_width(data, 0.0);

  EXPECT_EQ(data->border_width, 0);

  FreeSigningData(data);
}

TEST_F(PopplerSigningDataSetBorderWidthTest_2376, PositiveWidthSetsValue_2376) {
  PopplerSigningData* data = NewSigningData();
  ASSERT_NE(data, nullptr);

  data->border_width = 1;

  poppler_signing_data_set_border_width(data, 3.0);

  EXPECT_EQ(data->border_width, 3);

  FreeSigningData(data);
}

TEST_F(PopplerSigningDataSetBorderWidthTest_2376, MultipleCallsLastValidCallWins_2376) {
  PopplerSigningData* data = NewSigningData();
  ASSERT_NE(data, nullptr);

  data->border_width = 2;

  poppler_signing_data_set_border_width(data, 4.0);
  EXPECT_EQ(data->border_width, 4);

  // Negative call should not overwrite.
  poppler_signing_data_set_border_width(data, -5.0);
  EXPECT_EQ(data->border_width, 4);

  // Another valid call should overwrite.
  poppler_signing_data_set_border_width(data, 10.0);
  EXPECT_EQ(data->border_width, 10);

  FreeSigningData(data);
}