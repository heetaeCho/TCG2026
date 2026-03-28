// poppler-signing-data-set-field-partial-name-test.cc
#include <gtest/gtest.h>

#include <glib.h>

#include <cstring>
#include <string>

// Prefer including Poppler headers if available in your build.
// If your build uses a different umbrella header, adjust as needed.
#include <poppler.h>

extern "C" {
// Function under test (should be declared by Poppler headers in most builds,
// but we keep an explicit declaration to make this test file robust).
void poppler_signing_data_set_field_partial_name(PopplerSigningData *signing_data,
                                                 const gchar *field_partial_name);
}

namespace {

struct CapturedLog {
  int critical_count = 0;
  std::string last_message;
};

static void TestDefaultLogHandler(const gchar* log_domain,
                                  GLogLevelFlags log_level,
                                  const gchar* message,
                                  gpointer user_data) {
  (void)log_domain;
  auto* cap = static_cast<CapturedLog*>(user_data);
  if ((log_level & G_LOG_LEVEL_CRITICAL) != 0) {
    cap->critical_count++;
    cap->last_message = message ? message : "";
  }
  // Swallow logs to keep test output clean.
}

static void FreeSigningDataShallow(PopplerSigningData* sd) {
  if (!sd) return;

  // Free known string fields from the provided struct definition.
  g_free(sd->destination_filename);
  g_free(sd->signature_text);
  g_free(sd->signature_text_left);
  g_free(sd->field_partial_name);
  g_free(sd->reason);
  g_free(sd->location);
  g_free(sd->image_path);
  g_free(sd->password);
  g_free(sd->document_owner_password);
  g_free(sd->document_user_password);

  g_free(sd);
}

class PopplerSigningDataSetFieldPartialNameTest_2380 : public ::testing::Test {
protected:
  void SetUp() override {
    signing_data_ = static_cast<PopplerSigningData*>(g_malloc0(sizeof(PopplerSigningData)));
    ASSERT_NE(signing_data_, nullptr);
    signing_data_->field_partial_name = g_strdup("orig");
    ASSERT_NE(signing_data_->field_partial_name, nullptr);
  }

  void TearDown() override { FreeSigningDataShallow(signing_data_); }

  PopplerSigningData* signing_data_ = nullptr;
};

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, SetsNewValue_2380) {
  poppler_signing_data_set_field_partial_name(signing_data_, "fieldA");

  ASSERT_NE(signing_data_->field_partial_name, nullptr);
  EXPECT_STREQ(signing_data_->field_partial_name, "fieldA");
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, OverwritesExistingValue_2380) {
  ASSERT_NE(signing_data_->field_partial_name, nullptr);
  EXPECT_STREQ(signing_data_->field_partial_name, "orig");

  poppler_signing_data_set_field_partial_name(signing_data_, "fieldB");

  ASSERT_NE(signing_data_->field_partial_name, nullptr);
  EXPECT_STREQ(signing_data_->field_partial_name, "fieldB");
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, AcceptsEmptyString_2380) {
  poppler_signing_data_set_field_partial_name(signing_data_, "");

  ASSERT_NE(signing_data_->field_partial_name, nullptr);
  EXPECT_STREQ(signing_data_->field_partial_name, "");
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, AcceptsLongString_2380) {
  std::string long_name(4096, 'a');

  poppler_signing_data_set_field_partial_name(signing_data_, long_name.c_str());

  ASSERT_NE(signing_data_->field_partial_name, nullptr);
  EXPECT_EQ(std::strlen(signing_data_->field_partial_name), long_name.size());
  EXPECT_EQ(std::string(signing_data_->field_partial_name), long_name);
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380, NullSigningDataEmitsCriticalAndReturns_2380) {
  CapturedLog cap;

  auto prev_handler = g_log_set_default_handler(TestDefaultLogHandler, &cap);

  // Should not crash; should emit a critical log and return.
  poppler_signing_data_set_field_partial_name(nullptr, "fieldC");

  // Restore handler.
  g_log_set_default_handler(prev_handler, nullptr);

  EXPECT_GE(cap.critical_count, 1);
}

TEST_F(PopplerSigningDataSetFieldPartialNameTest_2380,
       NullFieldPartialNameEmitsCriticalAndDoesNotChangeExisting_2380) {
  CapturedLog cap;

  ASSERT_NE(signing_data_->field_partial_name, nullptr);
  EXPECT_STREQ(signing_data_->field_partial_name, "orig");

  auto prev_handler = g_log_set_default_handler(TestDefaultLogHandler, &cap);

  // Should not crash; should emit a critical log and return (no observable change expected).
  poppler_signing_data_set_field_partial_name(signing_data_, nullptr);

  g_log_set_default_handler(prev_handler, nullptr);

  EXPECT_GE(cap.critical_count, 1);

  // Observable state through the public struct field should remain unchanged.
  ASSERT_NE(signing_data_->field_partial_name, nullptr);
  EXPECT_STREQ(signing_data_->field_partial_name, "orig");
}

}  // namespace