// poppler_signing_data_set_reason_test_2382.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>

extern "C" {

// Minimal structs/types to compile the tests (matching the provided snippet).
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

struct _PopplerSigningData {
public:
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

// Function under test (implemented in the production library/object file).
void poppler_signing_data_set_reason(PopplerSigningData* signing_data, const gchar* reason);

}  // extern "C"

namespace {

class PopplerSigningDataSetReasonTest_2382 : public ::testing::Test {
protected:
  void SetUp() override { data_ = static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData))); }

  void TearDown() override {
    if (data_) {
      // Only free what we may have allocated via the setter(s) we exercised.
      g_free(data_->reason);
      data_->reason = nullptr;
      g_free(data_);
      data_ = nullptr;
    }
  }

  PopplerSigningData* data_ = nullptr;
};

TEST_F(PopplerSigningDataSetReasonTest_2382, SetsReasonOnFreshObject_2382) {
  ASSERT_NE(data_, nullptr);
  ASSERT_EQ(data_->reason, nullptr);

  poppler_signing_data_set_reason(data_, "Because I said so");

  ASSERT_NE(data_->reason, nullptr);
  EXPECT_STREQ(data_->reason, "Because I said so");
}

TEST_F(PopplerSigningDataSetReasonTest_2382, AcceptsEmptyString_2382) {
  ASSERT_NE(data_, nullptr);

  poppler_signing_data_set_reason(data_, "");

  ASSERT_NE(data_->reason, nullptr);
  EXPECT_STREQ(data_->reason, "");
}

TEST_F(PopplerSigningDataSetReasonTest_2382, ReplacesExistingReasonWithNewValue_2382) {
  ASSERT_NE(data_, nullptr);

  poppler_signing_data_set_reason(data_, "first");
  ASSERT_NE(data_->reason, nullptr);
  char* first_ptr = data_->reason;
  EXPECT_STREQ(first_ptr, "first");

  poppler_signing_data_set_reason(data_, "second");

  ASSERT_NE(data_->reason, nullptr);
  EXPECT_STREQ(data_->reason, "second");
  EXPECT_NE(data_->reason, first_ptr) << "Reason pointer should change when a new value is set";
  EXPECT_NE(data_->reason, "second") << "Setter should not alias the caller's string pointer";
}

TEST_F(PopplerSigningDataSetReasonTest_2382, DuplicatesInputSoCallerCanFreeOriginal_2382) {
  ASSERT_NE(data_, nullptr);

  gchar* input = g_strdup("dynamic");
  ASSERT_NE(input, nullptr);

  poppler_signing_data_set_reason(data_, input);

  // Free caller-owned buffer; stored value should remain valid if duplicated.
  g_free(input);
  input = nullptr;

  ASSERT_NE(data_->reason, nullptr);
  EXPECT_STREQ(data_->reason, "dynamic");
}

TEST_F(PopplerSigningDataSetReasonTest_2382, PassingSamePointerDoesNotChangeStoredPointer_2382) {
  ASSERT_NE(data_, nullptr);

  // Use a heap string so we can pass the exact same pointer back in.
  gchar* heap_str = g_strdup("same-pointer");
  ASSERT_NE(heap_str, nullptr);

  poppler_signing_data_set_reason(data_, heap_str);
  ASSERT_NE(data_->reason, nullptr);

  // Overwrite stored reason to be exactly the same pointer, simulating a scenario
  // where the internal field already equals the provided pointer.
  // (We free the old one first to avoid leaking it.)
  g_free(data_->reason);
  data_->reason = heap_str;

  char* before = data_->reason;
  poppler_signing_data_set_reason(data_, heap_str);

  EXPECT_EQ(data_->reason, before);
  EXPECT_STREQ(data_->reason, "same-pointer");

  // TearDown will free data_->reason; avoid double-free by not freeing heap_str here.
}

TEST_F(PopplerSigningDataSetReasonTest_2382, NullSigningDataEmitsCriticalAndReturns_2382) {
  // g_return_if_fail should log a critical message and return.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*signing_data*");
  poppler_signing_data_set_reason(nullptr, "reason");
  g_test_assert_expected_messages();
}

TEST_F(PopplerSigningDataSetReasonTest_2382, NullReasonEmitsCriticalAndDoesNotModify_2382) {
  ASSERT_NE(data_, nullptr);

  poppler_signing_data_set_reason(data_, "initial");
  ASSERT_NE(data_->reason, nullptr);
  char* before = data_->reason;

  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*reason*");
  poppler_signing_data_set_reason(data_, nullptr);
  g_test_assert_expected_messages();

  // Should remain unchanged (function returns early).
  EXPECT_EQ(data_->reason, before);
  EXPECT_STREQ(data_->reason, "initial");
}

}  // namespace