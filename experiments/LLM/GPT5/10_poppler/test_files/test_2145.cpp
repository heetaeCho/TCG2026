// handle-save-error-test-2145.cc
//
// Unit tests for handle_save_error() in poppler-document.cc
// TEST_ID: 2145

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

// Expose file-local (static) symbols for testing by including the .cc directly.
// This test is intended to be built as a standalone TU that compiles poppler-document.cc
// exactly once (i.e., do not also link the separately-compiled poppler-document.o).
#define static /* expose internal linkage for tests */
#include "poppler-document.cc"
#undef static

class HandleSaveErrorTest_2145 : public ::testing::Test {
protected:
  void TearDown() override {
    // Nothing to clean up globally.
  }
};

TEST_F(HandleSaveErrorTest_2145, ErrNoneReturnsTrueAndLeavesErrorNull_2145) {
  GError *err = nullptr;

  const gboolean ok = handle_save_error(errNone, &err);

  EXPECT_TRUE(ok);
  EXPECT_EQ(err, nullptr);
}

TEST_F(HandleSaveErrorTest_2145, ErrOpenFileSetsOpenFileErrorAndReturnsFalse_2145) {
  GError *err = nullptr;

  const gboolean ok = handle_save_error(errOpenFile, &err);

  EXPECT_FALSE(ok);
  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->domain, POPPLER_ERROR);
  EXPECT_EQ(err->code, POPPLER_ERROR_OPEN_FILE);
  EXPECT_STREQ(err->message, "Failed to open file for writing");

  g_clear_error(&err);
}

TEST_F(HandleSaveErrorTest_2145, ErrEncryptedSetsEncryptedErrorAndReturnsFalse_2145) {
  GError *err = nullptr;

  const gboolean ok = handle_save_error(errEncrypted, &err);

  EXPECT_FALSE(ok);
  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->domain, POPPLER_ERROR);
  EXPECT_EQ(err->code, POPPLER_ERROR_ENCRYPTED);
  EXPECT_STREQ(err->message, "Document is encrypted");

  g_clear_error(&err);
}

TEST_F(HandleSaveErrorTest_2145, UnknownErrorCodeSetsInvalidErrorAndReturnsFalse_2145) {
  GError *err = nullptr;

  // Pick a value not covered by the switch cases in the provided implementation.
  const int unknown_code = 999999;

  const gboolean ok = handle_save_error(unknown_code, &err);

  EXPECT_FALSE(ok);
  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->domain, POPPLER_ERROR);
  EXPECT_EQ(err->code, POPPLER_ERROR_INVALID);
  EXPECT_STREQ(err->message, "Failed to save document");

  g_clear_error(&err);
}

TEST_F(HandleSaveErrorTest_2145, NullErrorOutParameterDoesNotCrashAndReturnsStatus_2145) {
  // When error == nullptr, the function should still return success/failure
  // without attempting to write through the error pointer.

  EXPECT_TRUE(handle_save_error(errNone, nullptr));
  EXPECT_FALSE(handle_save_error(errOpenFile, nullptr));
  EXPECT_FALSE(handle_save_error(errEncrypted, nullptr));
  EXPECT_FALSE(handle_save_error(123456, nullptr));
}

TEST_F(HandleSaveErrorTest_2145, OverwritesExistingGErrorWhenProvided_2145) {
  // Start with a pre-existing error to ensure the function sets a new one.
  GError *err = g_error_new_literal(POPPLER_ERROR, POPPLER_ERROR_INVALID, "old error");
  ASSERT_NE(err, nullptr);
  ASSERT_STREQ(err->message, "old error");

  const gboolean ok = handle_save_error(errOpenFile, &err);

  EXPECT_FALSE(ok);
  ASSERT_NE(err, nullptr);
  EXPECT_EQ(err->domain, POPPLER_ERROR);
  EXPECT_EQ(err->code, POPPLER_ERROR_OPEN_FILE);
  EXPECT_STREQ(err->message, "Failed to open file for writing");

  g_clear_error(&err);
}