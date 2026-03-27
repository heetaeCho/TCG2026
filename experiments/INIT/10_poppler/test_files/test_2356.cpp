// File: poppler-signing-data-set-destination-filename-test_2356.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <cstring>

extern "C" {

// Prefer including the real header if available in the build environment.
// If not available, fall back to a minimal compatible declaration for tests.
#if defined(__has_include)
#  if __has_include("poppler.h")
#    include "poppler.h"
#  elif __has_include("poppler-form-field.h")
#    include "poppler-form-field.h"
#  endif
#endif

// If PopplerSigningData isn't visible via headers, define a minimal struct
// that matches the known fields needed for this unit under test.
#ifndef POPPLER_TYPE_SIGNING_DATA
// Some builds may not define a GType macro; use a conservative check.
#endif

// Detect whether PopplerSigningData is already declared.
#ifndef __POPPLER_SIGNING_DATA_DECLARED_FOR_TEST_2356
// If the type is not declared by included headers, declare it here.
#if !defined(POPPLER_SIGNING_DATA) && !defined(_POPPLER_SIGNING_DATA) && !defined(POPPLER_TYPE_SIGNING_DATA)
struct _PopplerSigningData {
  char *destination_filename;
  char *signature_text;
  char *signature_text_left;
  // The remaining fields are not needed for these tests; keep a placeholder size.
  // In real builds, the actual struct definition should come from Poppler headers.
};
typedef struct _PopplerSigningData PopplerSigningData;
#endif
#define __POPPLER_SIGNING_DATA_DECLARED_FOR_TEST_2356 1
#endif

void poppler_signing_data_set_destination_filename(PopplerSigningData *signing_data,
                                                   const gchar *filename);
}  // extern "C"

namespace {

class PopplerSigningDataTest_2356 : public ::testing::Test {
 protected:
  void SetUp() override {
    std::memset(&data_, 0, sizeof(data_));
  }

  void TearDown() override {
    g_clear_pointer(&data_.destination_filename, g_free);
  }

  PopplerSigningData data_{};
};

TEST_F(PopplerSigningDataTest_2356, SetsDestinationFilenameCopiesString_2356) {
  const gchar *input = "output.pdf";
  ASSERT_EQ(data_.destination_filename, nullptr);

  poppler_signing_data_set_destination_filename(&data_, input);

  ASSERT_NE(data_.destination_filename, nullptr);
  EXPECT_STREQ(data_.destination_filename, input);

  // Should be a duplicate, not necessarily the same pointer as the input.
  EXPECT_NE(data_.destination_filename, input);
}

TEST_F(PopplerSigningDataTest_2356, ReplacesExistingFilenameWhenDifferentInput_2356) {
  data_.destination_filename = g_strdup("old.pdf");
  ASSERT_NE(data_.destination_filename, nullptr);
  gchar *old_ptr = data_.destination_filename;

  poppler_signing_data_set_destination_filename(&data_, "new.pdf");

  ASSERT_NE(data_.destination_filename, nullptr);
  EXPECT_STREQ(data_.destination_filename, "new.pdf");
  EXPECT_NE(data_.destination_filename, old_ptr);
}

TEST_F(PopplerSigningDataTest_2356, NoOpWhenInputPointerMatchesStoredPointer_2356) {
  data_.destination_filename = g_strdup("same.pdf");
  ASSERT_NE(data_.destination_filename, nullptr);
  gchar *stored_ptr = data_.destination_filename;

  // Pass the exact same pointer back in.
  poppler_signing_data_set_destination_filename(&data_, stored_ptr);

  EXPECT_EQ(data_.destination_filename, stored_ptr);
  EXPECT_STREQ(data_.destination_filename, "same.pdf");
}

TEST_F(PopplerSigningDataTest_2356, ReplacesWhenSameContentButDifferentPointer_2356) {
  data_.destination_filename = g_strdup("dup.pdf");
  ASSERT_NE(data_.destination_filename, nullptr);
  gchar *old_ptr = data_.destination_filename;

  gchar *different_ptr_same_content = g_strdup("dup.pdf");
  ASSERT_NE(different_ptr_same_content, nullptr);
  ASSERT_NE(different_ptr_same_content, old_ptr);

  poppler_signing_data_set_destination_filename(&data_, different_ptr_same_content);

  ASSERT_NE(data_.destination_filename, nullptr);
  EXPECT_STREQ(data_.destination_filename, "dup.pdf");
  EXPECT_NE(data_.destination_filename, old_ptr);

  // Function duplicates the provided string; we still own and must free input buffer.
  g_free(different_ptr_same_content);
}

TEST_F(PopplerSigningDataTest_2356, NullSigningDataEmitsCriticalAndReturns_2356) {
  // g_return_if_fail() should log a critical and return without crashing.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*signing_data*nullptr*");

  poppler_signing_data_set_destination_filename(nullptr, "x.pdf");

  g_test_assert_expected_messages();
}

TEST_F(PopplerSigningDataTest_2356, NullFilenameEmitsCriticalAndDoesNotModifyState_2356) {
  data_.destination_filename = g_strdup("keep.pdf");
  ASSERT_NE(data_.destination_filename, nullptr);
  gchar *old_ptr = data_.destination_filename;

  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*filename*nullptr*");

  poppler_signing_data_set_destination_filename(&data_, nullptr);

  g_test_assert_expected_messages();

  // Should be unchanged.
  EXPECT_EQ(data_.destination_filename, old_ptr);
  EXPECT_STREQ(data_.destination_filename, "keep.pdf");
}

}  // namespace