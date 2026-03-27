// poppler_signing_data_get_password_test_2389.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler-form-field.h"  // Provides PopplerSigningData and poppler_signing_data_get_password()

TEST(PopplerSigningDataGetPasswordTest_2389, NullSigningDataReturnsNull_2389) {
  EXPECT_EQ(poppler_signing_data_get_password(nullptr), nullptr);
}

TEST(PopplerSigningDataGetPasswordTest_2389, PasswordUnsetReturnsNull_2389) {
  PopplerSigningData signing_data{};
  signing_data.password = nullptr;

  EXPECT_EQ(poppler_signing_data_get_password(&signing_data), nullptr);
}

TEST(PopplerSigningDataGetPasswordTest_2389, ReturnsExactPointerStoredInStruct_2389) {
  PopplerSigningData signing_data{};
  const gchar *pw = "secret";
  signing_data.password = const_cast<gchar *>(pw);  // API returns const gchar*

  const gchar *out = poppler_signing_data_get_password(&signing_data);
  EXPECT_EQ(out, pw);
}

TEST(PopplerSigningDataGetPasswordTest_2389, ReturnsEmptyStringWhenStoredAsEmpty_2389) {
  PopplerSigningData signing_data{};
  const gchar *pw = "";
  signing_data.password = const_cast<gchar *>(pw);

  const gchar *out = poppler_signing_data_get_password(&signing_data);
  ASSERT_NE(out, nullptr);
  EXPECT_STREQ(out, "");
}

TEST(PopplerSigningDataGetPasswordTest_2389, DoesNotModifyReturnedString_2389) {
  PopplerSigningData signing_data{};
  gchar pw[] = "mutable";
  signing_data.password = pw;

  const gchar *out1 = poppler_signing_data_get_password(&signing_data);
  ASSERT_NE(out1, nullptr);
  EXPECT_STREQ(out1, "mutable");

  // Mutate the underlying buffer to ensure function simply returns the stored pointer.
  pw[0] = 'M';

  const gchar *out2 = poppler_signing_data_get_password(&signing_data);
  ASSERT_NE(out2, nullptr);
  EXPECT_STREQ(out2, "Mutable");
}