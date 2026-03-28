// poppler-signing-data-set-signature-text-test.cc
// Unit tests for poppler_signing_data_set_signature_text()
// TEST_ID: 2362

#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>

// ---- Minimal type definitions (from provided snippet / common Poppler-GLib shapes) ----
typedef struct {
  double x1;
  double y1;
  double x2;
  double y2;
} PopplerRectangle;

typedef struct {
  guint16 red;
  guint16 green;
  guint16 blue;
} PopplerColor;

struct _PopplerSigningData {
public:
  char *destination_filename;
  char *signature_text;
  char *signature_text_left;
  PopplerRectangle signature_rect;
  int left_font_size;
  PopplerColor border_color;
  int border_width;
  PopplerColor background_color;
  char *field_partial_name;
  char *reason;
  char *location;
  char *image_path;
  char *password;
  char *document_owner_password;
  char *document_user_password;
};

using PopplerSigningData = _PopplerSigningData;

// Function under test (implemented in production codebase).
extern "C" void poppler_signing_data_set_signature_text(PopplerSigningData *signing_data,
                                                        const gchar *signature_text);

// ---- Test Fixture ----
class PopplerSigningDataTest_2362 : public ::testing::Test {
protected:
  void SetUp() override { std::memset(&data_, 0, sizeof(data_)); }

  void TearDown() override {
    // Clean up any allocations we might have created in tests.
    g_clear_pointer(&data_.destination_filename, g_free);
    g_clear_pointer(&data_.signature_text, g_free);
    g_clear_pointer(&data_.signature_text_left, g_free);
    g_clear_pointer(&data_.field_partial_name, g_free);
    g_clear_pointer(&data_.reason, g_free);
    g_clear_pointer(&data_.location, g_free);
    g_clear_pointer(&data_.image_path, g_free);
    g_clear_pointer(&data_.password, g_free);
    g_clear_pointer(&data_.document_owner_password, g_free);
    g_clear_pointer(&data_.document_user_password, g_free);
  }

  PopplerSigningData data_;
};

// ---- Normal operation ----

TEST_F(PopplerSigningDataTest_2362, SetsSignatureTextToNewValue_2362) {
  ASSERT_EQ(data_.signature_text, nullptr);

  poppler_signing_data_set_signature_text(&data_, "Hello, signature!");

  ASSERT_NE(data_.signature_text, nullptr);
  EXPECT_STREQ(data_.signature_text, "Hello, signature!");
}

TEST_F(PopplerSigningDataTest_2362, ReplacesExistingSignatureText_2362) {
  data_.signature_text = g_strdup("old");
  char *old_ptr = data_.signature_text;
  ASSERT_NE(old_ptr, nullptr);

  poppler_signing_data_set_signature_text(&data_, "new");

  ASSERT_NE(data_.signature_text, nullptr);
  EXPECT_STREQ(data_.signature_text, "new");
  EXPECT_NE(data_.signature_text, old_ptr) << "Expected replacement to result in a different pointer.";
}

TEST_F(PopplerSigningDataTest_2362, PassingSamePointerDoesNotChangePointer_2362) {
  // The function explicitly checks pointer equality.
  const gchar *same_ptr = "literal";
  data_.signature_text = const_cast<char *>(same_ptr);

  poppler_signing_data_set_signature_text(&data_, same_ptr);

  EXPECT_EQ(data_.signature_text, same_ptr);
  EXPECT_STREQ(data_.signature_text, "literal");

  // Avoid freeing a string literal in TearDown().
  data_.signature_text = nullptr;
}

TEST_F(PopplerSigningDataTest_2362, DifferentPointerSameContentsStillUpdates_2362) {
  data_.signature_text = g_strdup("abc");
  char *old_ptr = data_.signature_text;
  ASSERT_NE(old_ptr, nullptr);

  // Create a different pointer with the same contents.
  gchar *incoming = g_strdup("abc");
  ASSERT_NE(incoming, nullptr);
  ASSERT_NE(incoming, old_ptr);

  poppler_signing_data_set_signature_text(&data_, incoming);

  ASSERT_NE(data_.signature_text, nullptr);
  EXPECT_STREQ(data_.signature_text, "abc");
  EXPECT_NE(data_.signature_text, old_ptr);

  g_free(incoming);
}

// ---- Boundary conditions ----

TEST_F(PopplerSigningDataTest_2362, AcceptsEmptyString_2362) {
  poppler_signing_data_set_signature_text(&data_, "");

  ASSERT_NE(data_.signature_text, nullptr);
  EXPECT_STREQ(data_.signature_text, "");
}

TEST_F(PopplerSigningDataTest_2362, AcceptsLongString_2362) {
  std::string long_text(8192, 'A');

  poppler_signing_data_set_signature_text(&data_, long_text.c_str());

  ASSERT_NE(data_.signature_text, nullptr);
  EXPECT_EQ(std::strlen(data_.signature_text), long_text.size());
  EXPECT_STREQ(data_.signature_text, long_text.c_str());
}

// ---- Exceptional / error cases (observable via GLib log messages) ----

TEST_F(PopplerSigningDataTest_2362, NullSigningDataTriggersCriticalAndReturns_2362) {
  // g_return_if_fail() emits a CRITICAL log and returns.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*signing_data*");

  poppler_signing_data_set_signature_text(nullptr, "anything");

  g_test_assert_expected_messages();
}

TEST_F(PopplerSigningDataTest_2362, NullSignatureTextTriggersCriticalAndDoesNotModifyExisting_2362) {
  data_.signature_text = g_strdup("keep");
  ASSERT_NE(data_.signature_text, nullptr);

  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*signature_text*");

  poppler_signing_data_set_signature_text(&data_, nullptr);

  g_test_assert_expected_messages();

  // Should still be the old value (function returns early).
  ASSERT_NE(data_.signature_text, nullptr);
  EXPECT_STREQ(data_.signature_text, "keep");
}