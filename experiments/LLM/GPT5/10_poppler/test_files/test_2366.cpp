#include <gtest/gtest.h>

#include "poppler-form-field.h"  // poppler_signing_data_set_signature_rectangle
#include "poppler-page.h"        // PopplerRectangle

// The struct layout is provided in the prompt as "Known or Inferred Dependencies (Optional)".
// We use it only to allocate an instance and to observe the public field that is written by
// the function under test (signature_rect).
struct _PopplerSigningData {
  char* destination_filename;
  char* signature_text;
  char* signature_text_left;
  PopplerRectangle signature_rect;
  int left_font_size;
  PopplerColor border_color;
  int border_width;
  PopplerColor background_color;
  char* field_partial_name;
  char* reason;
  char* location;
  char* image_path;
  char* password;
  char* document_owner_password;
  char* document_user_password;
};

class PopplerSigningDataSetSignatureRectangleTest_2366 : public ::testing::Test {};

TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366,
       CopiesRectangleFieldsIntoSigningData_2366) {
  _PopplerSigningData signing_data{};
  signing_data.signature_rect.x2 = -1;
  signing_data.signature_rect.y2 = -2;

  PopplerRectangle rect{};
  rect.x2 = 123;
  rect.y2 = 456;

  poppler_signing_data_set_signature_rectangle(
      reinterpret_cast<PopplerSigningData*>(&signing_data), &rect);

  EXPECT_EQ(signing_data.signature_rect.x2, rect.x2);
  EXPECT_EQ(signing_data.signature_rect.y2, rect.y2);
}

TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366,
       OverwritesPreviousRectangleValues_2366) {
  _PopplerSigningData signing_data{};
  signing_data.signature_rect.x2 = 1;
  signing_data.signature_rect.y2 = 2;

  PopplerRectangle rect1{};
  rect1.x2 = 10;
  rect1.y2 = 20;

  poppler_signing_data_set_signature_rectangle(
      reinterpret_cast<PopplerSigningData*>(&signing_data), &rect1);
  EXPECT_EQ(signing_data.signature_rect.x2, 10);
  EXPECT_EQ(signing_data.signature_rect.y2, 20);

  PopplerRectangle rect2{};
  rect2.x2 = -300;
  rect2.y2 = 99999;

  poppler_signing_data_set_signature_rectangle(
      reinterpret_cast<PopplerSigningData*>(&signing_data), &rect2);

  EXPECT_EQ(signing_data.signature_rect.x2, rect2.x2);
  EXPECT_EQ(signing_data.signature_rect.y2, rect2.y2);
}

TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366,
       AcceptsZeroAndNegativeValues_2366) {
  _PopplerSigningData signing_data{};
  signing_data.signature_rect.x2 = 777;
  signing_data.signature_rect.y2 = 888;

  PopplerRectangle rect{};
  rect.x2 = 0;
  rect.y2 = -1;

  poppler_signing_data_set_signature_rectangle(
      reinterpret_cast<PopplerSigningData*>(&signing_data), &rect);

  EXPECT_EQ(signing_data.signature_rect.x2, 0);
  EXPECT_EQ(signing_data.signature_rect.y2, -1);
}

TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366,
       NullSigningDataIsRejected_2366) {
#if defined(G_DEBUG) && !defined(G_DISABLE_CHECKS)
  PopplerRectangle rect{};
  rect.x2 = 1;
  rect.y2 = 2;

  // g_return_if_fail() should log a critical and return without crashing.
  EXPECT_DEATH_IF_SUPPORTED(
      poppler_signing_data_set_signature_rectangle(nullptr, &rect), ".*");
#else
  GTEST_SKIP()
      << "GLib runtime checks not enabled; cannot reliably observe "
         "g_return_if_fail() behavior in this build.";
#endif
}

TEST_F(PopplerSigningDataSetSignatureRectangleTest_2366,
       NullRectangleIsRejected_2366) {
#if defined(G_DEBUG) && !defined(G_DISABLE_CHECKS)
  _PopplerSigningData signing_data{};

  EXPECT_DEATH_IF_SUPPORTED(
      poppler_signing_data_set_signature_rectangle(
          reinterpret_cast<PopplerSigningData*>(&signing_data), nullptr),
      ".*");
#else
  GTEST_SKIP()
      << "GLib runtime checks not enabled; cannot reliably observe "
         "g_return_if_fail() behavior in this build.";
#endif
}