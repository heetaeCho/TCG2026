// poppler-signing-data-get-signature-text-left-test.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Forward declarations matching the production interface.
typedef struct _PopplerSigningData PopplerSigningData;

const gchar *poppler_signing_data_get_signature_text_left(
    const PopplerSigningData *signing_data);

}  // extern "C"

// Minimal struct layout as provided in the prompt (dependencies section).
// This is used only to create a test instance and set observable fields.
// We do not re-implement any function logic.
struct _PopplerSigningData {
  char *destination_filename;
  char *signature_text;
  char *signature_text_left;
  // The remaining fields exist in production but are irrelevant for this getter.
  // Keep placeholders to match the provided layout (types not needed by tests here).
  // NOTE: We intentionally avoid depending on Poppler types; we won't touch these.
  char signature_rect_placeholder[sizeof(double) * 4];  // placeholder
  int left_font_size;
  char border_color_placeholder[sizeof(int) * 4];       // placeholder
  int border_width;
  char background_color_placeholder[sizeof(int) * 4];   // placeholder
  char *field_partial_name;
  char *reason;
  char *location;
  char *image_path;
  char *password;
  char *document_owner_password;
  char *document_user_password;
};

class PopplerSigningDataGetSignatureTextLeftTest_2365 : public ::testing::Test {
 protected:
  void SetUp() override { g_log_set_always_fatal(G_LOG_FATAL_MASK); }
};

TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365,
       ReturnsPointerToSignatureTextLeftWhenPresent_2365) {
  _PopplerSigningData sd{};
  sd.signature_text_left = const_cast<char *>("LEFT TEXT");

  const gchar *result =
      poppler_signing_data_get_signature_text_left(
          reinterpret_cast<const PopplerSigningData *>(&sd));

  ASSERT_NE(result, nullptr);
  // Observable behavior: returns the stored pointer/content.
  EXPECT_STREQ(result, "LEFT TEXT");
}

TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365,
       ReturnsNullWhenSignatureTextLeftIsNull_2365) {
  _PopplerSigningData sd{};
  sd.signature_text_left = nullptr;

  const gchar *result =
      poppler_signing_data_get_signature_text_left(
          reinterpret_cast<const PopplerSigningData *>(&sd));

  // Observable behavior: returns the field (null).
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365,
       ReturnsEmptyStringWhenSignatureTextLeftIsEmpty_2365) {
  _PopplerSigningData sd{};
  sd.signature_text_left = const_cast<char *>("");

  const gchar *result =
      poppler_signing_data_get_signature_text_left(
          reinterpret_cast<const PopplerSigningData *>(&sd));

  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "");
}

TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365,
       DoesNotAlterReturnedPointerAcrossMultipleCalls_2365) {
  _PopplerSigningData sd{};
  sd.signature_text_left = const_cast<char *>("SAME");

  const PopplerSigningData *psd =
      reinterpret_cast<const PopplerSigningData *>(&sd);

  const gchar *r1 = poppler_signing_data_get_signature_text_left(psd);
  const gchar *r2 = poppler_signing_data_get_signature_text_left(psd);

  // Observable behavior: repeated calls return same pointer value.
  EXPECT_EQ(r1, r2);
  ASSERT_NE(r1, nullptr);
  EXPECT_STREQ(r1, "SAME");
}

TEST_F(PopplerSigningDataGetSignatureTextLeftTest_2365,
       NullSigningDataTriggersCriticalAndReturnsNull_2365) {
  // g_return_val_if_fail emits a critical log and returns the specified value.
  // Verify observable behavior via GLib log interception.
  EXPECT_DEATH(
      {
        // Make critical logs fatal so the process terminates (death test).
        g_log_set_always_fatal(
            static_cast<GLogLevelFlags>(G_LOG_LEVEL_CRITICAL));
        (void)poppler_signing_data_get_signature_text_left(nullptr);
      },
      "");  // message text is implementation-dependent; match anything.
}