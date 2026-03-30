// poppler-signing-data-set-location-test-2384.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {

// Minimal struct definition copied from the prompt (public fields).
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

typedef struct _PopplerSigningData {
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
} PopplerSigningData;

// Function under test (implemented in the production file).
void poppler_signing_data_set_location(PopplerSigningData *signing_data, const gchar *location);

} // extern "C"

namespace {

class PopplerSigningDataSetLocationTest_2384 : public ::testing::Test {
protected:
  void SetUp() override {
    signing_data_ = g_new0(PopplerSigningData, 1);
    // All fields are zero-initialized by g_new0; in particular, location == nullptr.
  }

  void TearDown() override {
    if (signing_data_) {
      // Free any heap-owned strings we might have set during tests.
      g_free(signing_data_->destination_filename);
      g_free(signing_data_->signature_text);
      g_free(signing_data_->signature_text_left);
      g_free(signing_data_->field_partial_name);
      g_free(signing_data_->reason);
      g_free(signing_data_->location);
      g_free(signing_data_->image_path);
      g_free(signing_data_->password);
      g_free(signing_data_->document_owner_password);
      g_free(signing_data_->document_user_password);

      g_free(signing_data_);
      signing_data_ = nullptr;
    }
  }

  PopplerSigningData *signing_data_ = nullptr;
};

TEST_F(PopplerSigningDataSetLocationTest_2384, SetsLocationToDuplicatedString_2384) {
  const gchar *loc = "Seoul";
  ASSERT_EQ(signing_data_->location, nullptr);

  poppler_signing_data_set_location(signing_data_, loc);

  ASSERT_NE(signing_data_->location, nullptr);
  EXPECT_STREQ(signing_data_->location, "Seoul");
  // Must not just alias the input pointer for string literals / external buffers.
  EXPECT_NE(signing_data_->location, loc);
}

TEST_F(PopplerSigningDataSetLocationTest_2384, ReplacesPreviousLocationAndFreesOld_2384) {
  // Start with an owned location value.
  signing_data_->location = g_strdup("Old");
  char *old_ptr = signing_data_->location;
  ASSERT_NE(old_ptr, nullptr);
  ASSERT_STREQ(old_ptr, "Old");

  poppler_signing_data_set_location(signing_data_, "New");

  ASSERT_NE(signing_data_->location, nullptr);
  EXPECT_STREQ(signing_data_->location, "New");
  // Observable behavior: location pointer changes when new string provided.
  EXPECT_NE(signing_data_->location, old_ptr);
}

TEST_F(PopplerSigningDataSetLocationTest_2384, SamePointerNoOpDoesNotChangeOrFree_2384) {
  // Provide a heap-allocated string and then pass the exact same pointer back.
  signing_data_->location = g_strdup("SamePtr");
  char *same_ptr = signing_data_->location;
  ASSERT_NE(same_ptr, nullptr);

  poppler_signing_data_set_location(signing_data_, same_ptr);

  // If it is a no-op, the pointer should remain identical and content unchanged.
  EXPECT_EQ(signing_data_->location, same_ptr);
  EXPECT_STREQ(signing_data_->location, "SamePtr");
}

TEST_F(PopplerSigningDataSetLocationTest_2384, EmptyStringIsAcceptedAndStored_2384) {
  poppler_signing_data_set_location(signing_data_, "");

  ASSERT_NE(signing_data_->location, nullptr);
  EXPECT_STREQ(signing_data_->location, "");
}

TEST_F(PopplerSigningDataSetLocationTest_2384, VeryLongStringIsHandled_2384) {
  // Boundary-ish: long input string.
  gchar *long_str = g_strnfill(4096, 'A');
  ASSERT_NE(long_str, nullptr);

  poppler_signing_data_set_location(signing_data_, long_str);

  ASSERT_NE(signing_data_->location, nullptr);
  EXPECT_EQ(strlen(signing_data_->location), strlen(long_str));
  EXPECT_STREQ(signing_data_->location, long_str);
  // Should be a duplicate, not the same pointer.
  EXPECT_NE(signing_data_->location, long_str);

  g_free(long_str);
}

// Exceptional/error cases: g_return_if_fail() should not modify state.
TEST_F(PopplerSigningDataSetLocationTest_2384, NullSigningDataDoesNotCrash_2384) {
  // GLib's g_return_if_fail is expected to emit a critical and return.
  // We only assert it doesn't crash. (Not asserting logs to avoid coupling.)
  poppler_signing_data_set_location(nullptr, "X");
  SUCCEED();
}

TEST_F(PopplerSigningDataSetLocationTest_2384, NullLocationDoesNotChangeExistingValue_2384) {
  signing_data_->location = g_strdup("KeepMe");
  char *prev_ptr = signing_data_->location;
  ASSERT_NE(prev_ptr, nullptr);

  poppler_signing_data_set_location(signing_data_, nullptr);

  // Should remain unchanged if the function returns early on invalid input.
  EXPECT_EQ(signing_data_->location, prev_ptr);
  EXPECT_STREQ(signing_data_->location, "KeepMe");
}

} // namespace