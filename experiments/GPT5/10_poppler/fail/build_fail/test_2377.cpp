// poppler-signing-data-get-border-width-test.cc
#include <gtest/gtest.h>

#include "poppler-form-field.h" // Provides PopplerSigningData and poppler_signing_data_get_border_width()

namespace {

class PopplerSigningDataGetBorderWidthTest_2377 : public ::testing::Test {};

TEST_F(PopplerSigningDataGetBorderWidthTest_2377, NullSigningDataReturnsDefault_2377) {
  // Observable behavior via g_return_val_if_fail(): returns 12 when signing_data is null.
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(nullptr), 12.0);
}

TEST_F(PopplerSigningDataGetBorderWidthTest_2377, ReturnsValueFromStructWhenNonNull_2377) {
  PopplerSigningData signing_data{};
  // Field is declared as int border_width in the known struct.
  signing_data.border_width = 0;

  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(&signing_data), 0.0);

  signing_data.border_width = 1;
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(&signing_data), 1.0);

  signing_data.border_width = 12;
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(&signing_data), 12.0);

  signing_data.border_width = 13;
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(&signing_data), 13.0);
}

TEST_F(PopplerSigningDataGetBorderWidthTest_2377, HandlesNegativeBorderWidth_2377) {
  PopplerSigningData signing_data{};
  signing_data.border_width = -1;

  // The function returns signing_data->border_width as gdouble.
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(&signing_data), -1.0);

  signing_data.border_width = -123456;
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(&signing_data), -123456.0);
}

TEST_F(PopplerSigningDataGetBorderWidthTest_2377, HandlesLargeBorderWidth_2377) {
  PopplerSigningData signing_data{};
  signing_data.border_width = 2147483647; // INT_MAX for 32-bit int

  // Ensure the value is carried through the conversion to gdouble.
  EXPECT_DOUBLE_EQ(poppler_signing_data_get_border_width(&signing_data), 2147483647.0);
}

TEST_F(PopplerSigningDataGetBorderWidthTest_2377, DoesNotModifyInputStruct_2377) {
  PopplerSigningData signing_data{};
  signing_data.border_width = 7;

  const int before = signing_data.border_width;
  const double ret = poppler_signing_data_get_border_width(&signing_data);

  EXPECT_DOUBLE_EQ(ret, 7.0);
  EXPECT_EQ(signing_data.border_width, before);
}

}  // namespace