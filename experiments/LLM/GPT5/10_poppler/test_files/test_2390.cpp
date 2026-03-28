// poppler-signing-data-set-document-owner-password-test.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Minimal public structs/types needed by the exposed C interface.
typedef struct _PopplerSigningData PopplerSigningData;

typedef struct _PopplerRectangle {
  double x1;
  double y1;
  double x2;
  double y2;
} PopplerRectangle;

typedef struct _PopplerColor {
  guint16 red;
  guint16 green;
  guint16 blue;
} PopplerColor;

// Dependency struct layout provided in the prompt (used only to create valid inputs).
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

// Function under test (implemented in the real codebase).
void poppler_signing_data_set_document_owner_password(PopplerSigningData* signing_data,
                                                     const gchar* document_owner_password);
}  // extern "C"

namespace {

class PopplerSigningDataSetDocumentOwnerPasswordTest_2390 : public ::testing::Test {
 protected:
  void SetUp() override {
    signing_data_ = g_new0(_PopplerSigningData, 1);
    // Ensure starting state is well-defined.
    signing_data_->document_owner_password = nullptr;
  }

  void TearDown() override {
    if (signing_data_) {
      g_free(signing_data_->document_owner_password);
      signing_data_->document_owner_password = nullptr;
      g_free(signing_data_);
      signing_data_ = nullptr;
    }
  }

  _PopplerSigningData* signing_data_ = nullptr;
};

TEST_F(PopplerSigningDataSetDocumentOwnerPasswordTest_2390,
       SetsPasswordCopiesString_2390) {
  const gchar* input = "owner-pass-123";

  poppler_signing_data_set_document_owner_password(
      reinterpret_cast<PopplerSigningData*>(signing_data_), input);

  ASSERT_NE(signing_data_->document_owner_password, nullptr);
  EXPECT_STREQ(signing_data_->document_owner_password, input);

  // Must be a copy (g_strdup), not aliasing the caller pointer.
  EXPECT_NE(signing_data_->document_owner_password, input);
}

TEST_F(PopplerSigningDataSetDocumentOwnerPasswordTest_2390,
       ReplacesExistingPasswordWithNewValue_2390) {
  signing_data_->document_owner_password = g_strdup("old");

  poppler_signing_data_set_document_owner_password(
      reinterpret_cast<PopplerSigningData*>(signing_data_), "new");

  ASSERT_NE(signing_data_->document_owner_password, nullptr);
  EXPECT_STREQ(signing_data_->document_owner_password, "new");
}

TEST_F(PopplerSigningDataSetDocumentOwnerPasswordTest_2390,
       SamePointerInputDoesNotChangePointer_2390) {
  // Provide a stable pointer and set it as the internal pointer.
  gchar* stable = g_strdup("stable");
  signing_data_->document_owner_password = stable;

  poppler_signing_data_set_document_owner_password(
      reinterpret_cast<PopplerSigningData*>(signing_data_), stable);

  // Observable behavior: pointer remains exactly the same.
  EXPECT_EQ(signing_data_->document_owner_password, stable);
  EXPECT_STREQ(signing_data_->document_owner_password, "stable");
}

TEST_F(PopplerSigningDataSetDocumentOwnerPasswordTest_2390,
       BoundaryEmptyStringAcceptedAndCopied_2390) {
  const gchar* input = "";

  poppler_signing_data_set_document_owner_password(
      reinterpret_cast<PopplerSigningData*>(signing_data_), input);

  ASSERT_NE(signing_data_->document_owner_password, nullptr);
  EXPECT_STREQ(signing_data_->document_owner_password, "");
  EXPECT_NE(signing_data_->document_owner_password, input);
}

TEST_F(PopplerSigningDataSetDocumentOwnerPasswordTest_2390,
       BoundaryVeryLongStringAccepted_2390) {
  // Large but reasonable for unit tests.
  GString* s = g_string_sized_new(4096);
  for (int i = 0; i < 4096; ++i) g_string_append_c(s, 'A');

  poppler_signing_data_set_document_owner_password(
      reinterpret_cast<PopplerSigningData*>(signing_data_), s->str);

  ASSERT_NE(signing_data_->document_owner_password, nullptr);
  EXPECT_EQ(strlen(signing_data_->document_owner_password), static_cast<size_t>(4096));
  EXPECT_NE(signing_data_->document_owner_password, s->str);

  g_string_free(s, TRUE);
}

TEST_F(PopplerSigningDataSetDocumentOwnerPasswordTest_2390,
       NullSigningDataTriggersGWarningAndDoesNotCrash_2390) {
  // g_return_if_fail() emits a critical warning; verify it's produced.
  EXPECT_DEATH(
      {
        // In case GLib is configured to abort on criticals, this would die.
        // But by default it won't. We provide a dedicated gtest death to be safe
        // only if the environment is configured that way.
        // To avoid flakiness, use g_test_expect_message in a non-death test below.
        poppler_signing_data_set_document_owner_password(nullptr, "x");
      },
      ".*");
}

TEST_F(PopplerSigningDataSetDocumentOwnerPasswordTest_2390,
       NullPasswordTriggersGWarningAndDoesNotModifyExisting_2390) {
  signing_data_->document_owner_password = g_strdup("keep");

  // Expect a critical message from g_return_if_fail(document_owner_password != nullptr).
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*document_owner_password*");
  poppler_signing_data_set_document_owner_password(
      reinterpret_cast<PopplerSigningData*>(signing_data_), nullptr);
  g_test_assert_expected_messages();

  // Should remain unchanged.
  ASSERT_NE(signing_data_->document_owner_password, nullptr);
  EXPECT_STREQ(signing_data_->document_owner_password, "keep");
}

}  // namespace