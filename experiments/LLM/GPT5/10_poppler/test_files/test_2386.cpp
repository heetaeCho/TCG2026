// poppler_signing_data_set_image_path_test.cc
//
// Unit tests for:
//   void poppler_signing_data_set_image_path(PopplerSigningData *signing_data, const gchar *image_path)
//
// Constraints respected:
// - Treat implementation as black box (no reliance on internal logic beyond observable effects).
// - No access to private state (struct fields are public per provided dependency snippet; we use only
//   observable public data members as part of the interface surface provided in the prompt).
// - Include normal, boundary, and error/exceptional cases (g_return_if_fail behavior).
//
// NOTE: These tests assume GLib is available and that PopplerSigningData is a GLib-style struct.
//       g_return_if_fail() logs a critical and returns early; we validate that via g_test_expect_message.
//
// Build hint (adjust include paths as needed):
//   g++ -std=c++17 ... `pkg-config --cflags --libs glib-2.0 gobject-2.0` ... -lgtest -lgtest_main

#include <gtest/gtest.h>

#include <glib.h>

#include <cstring>

// Include the header that declares PopplerSigningData and poppler_signing_data_set_image_path.
// Adjust the include to match your codebase layout.
#include "poppler-form-field.h"

// If your project exposes PopplerSigningData via another header, replace accordingly.
// The tests rely on PopplerSigningData being a concrete type and the function being linkable.

namespace {

class PopplerSigningDataSetImagePathTest_2386 : public ::testing::Test {
protected:
  void SetUp() override {
    // Allocate a minimal PopplerSigningData instance.
    // Since we only need image_path behavior, we can zero-init the struct.
    signing_data_ = static_cast<PopplerSigningData *>(g_malloc0(sizeof(PopplerSigningData)));
    ASSERT_NE(signing_data_, nullptr);
  }

  void TearDown() override {
    if (signing_data_) {
      // Free any owned pointers we might have set via the API.
      // This is test cleanup; not asserting internal behavior, just avoiding leaks.
      if (signing_data_->image_path) {
        g_free(signing_data_->image_path);
        signing_data_->image_path = nullptr;
      }
      g_free(signing_data_);
      signing_data_ = nullptr;
    }
  }

  PopplerSigningData *signing_data_ = nullptr;
};

TEST_F(PopplerSigningDataSetImagePathTest_2386, SetsImagePathOnFreshObject_2386) {
  ASSERT_EQ(signing_data_->image_path, nullptr);

  const gchar *path = "/tmp/sig.png";
  poppler_signing_data_set_image_path(signing_data_, path);

  ASSERT_NE(signing_data_->image_path, nullptr);
  EXPECT_STREQ(signing_data_->image_path, path);
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, ReplacesExistingImagePathWithNewValue_2386) {
  poppler_signing_data_set_image_path(signing_data_, "/tmp/old.png");
  ASSERT_NE(signing_data_->image_path, nullptr);
  EXPECT_STREQ(signing_data_->image_path, "/tmp/old.png");

  // Capture old pointer to ensure replacement (observable through public member address).
  gchar *old_ptr = signing_data_->image_path;

  poppler_signing_data_set_image_path(signing_data_, "/tmp/new.png");

  ASSERT_NE(signing_data_->image_path, nullptr);
  EXPECT_STREQ(signing_data_->image_path, "/tmp/new.png");
  EXPECT_NE(signing_data_->image_path, old_ptr) << "Expected image_path storage to be replaced";
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SettingSamePointerIsNoOp_2386) {
  // Prepare a heap string we control and store it in the object as if it were already set.
  // This models the pointer-equality no-op branch in an observable way (member pointer unchanged).
  gchar *owned = g_strdup("/tmp/same.png");
  ASSERT_NE(owned, nullptr);
  signing_data_->image_path = owned;

  poppler_signing_data_set_image_path(signing_data_, owned);

  // Observable: pointer remains identical and content remains intact.
  EXPECT_EQ(signing_data_->image_path, owned);
  EXPECT_STREQ(signing_data_->image_path, "/tmp/same.png");
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, SettingEqualContentButDifferentPointerReplacesStorage_2386) {
  poppler_signing_data_set_image_path(signing_data_, "/tmp/equal.png");
  ASSERT_NE(signing_data_->image_path, nullptr);
  EXPECT_STREQ(signing_data_->image_path, "/tmp/equal.png");

  gchar *old_ptr = signing_data_->image_path;

  // Different pointer, same content.
  gchar *same_content_new_ptr = g_strdup("/tmp/equal.png");
  ASSERT_NE(same_content_new_ptr, nullptr);
  ASSERT_NE(same_content_new_ptr, old_ptr);

  poppler_signing_data_set_image_path(signing_data_, same_content_new_ptr);

  // The function takes const gchar*, does its own storage management; we can free our temp.
  g_free(same_content_new_ptr);

  ASSERT_NE(signing_data_->image_path, nullptr);
  EXPECT_STREQ(signing_data_->image_path, "/tmp/equal.png");
  EXPECT_NE(signing_data_->image_path, old_ptr)
      << "Expected replacement when pointer differs, even if content is identical";
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, AcceptsEmptyStringAsBoundaryValue_2386) {
  poppler_signing_data_set_image_path(signing_data_, "");

  ASSERT_NE(signing_data_->image_path, nullptr);
  EXPECT_STREQ(signing_data_->image_path, "");
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, NullSigningDataTriggersCriticalAndDoesNotCrash_2386) {
  // g_return_if_fail should emit a critical message and return.
  // We verify the external interaction: GLib log emission.
  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*signing_data*!=*NULL*");
  poppler_signing_data_set_image_path(nullptr, "/tmp/x.png");
  g_test_assert_expected_messages();
}

TEST_F(PopplerSigningDataSetImagePathTest_2386, NullImagePathTriggersCriticalAndLeavesValueUnchanged_2386) {
  poppler_signing_data_set_image_path(signing_data_, "/tmp/keep.png");
  ASSERT_NE(signing_data_->image_path, nullptr);
  EXPECT_STREQ(signing_data_->image_path, "/tmp/keep.png");

  gchar *old_ptr = signing_data_->image_path;

  g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, "*image_path*!=*NULL*");
  poppler_signing_data_set_image_path(signing_data_, nullptr);
  g_test_assert_expected_messages();

  // Observable: because it returned early, stored value should be unchanged.
  EXPECT_EQ(signing_data_->image_path, old_ptr);
  EXPECT_STREQ(signing_data_->image_path, "/tmp/keep.png");
}

} // namespace