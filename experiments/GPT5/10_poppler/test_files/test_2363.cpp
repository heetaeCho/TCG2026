// Copyright (C) 2026
// Unit tests for poppler_signing_data_get_signature_text()
// File: poppler-signing-data-get-signature-text-test-2363.cc

#include <glib.h>

#include <gtest/gtest.h>

#include "poppler.h"

// The function under test is implemented in poppler-form-field.cc (already in the codebase).
// We treat it as a black box and test only observable behavior via its interface:
//   const gchar *poppler_signing_data_get_signature_text(const PopplerSigningData *signing_data);

namespace {

class PopplerSigningDataGetSignatureTextTest_2363 : public ::testing::Test {
protected:
  void SetUp() override {
    // Ensure GLib warnings/criticals don't abort the test process.
    // (Some test runners set G_DEBUG=fatal-warnings; this is a defensive measure.)
    g_log_set_always_fatal(static_cast<GLogLevelFlags>(G_LOG_FATAL_MASK & ~(G_LOG_LEVEL_WARNING | G_LOG_LEVEL_CRITICAL)));
  }
};

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, NullSigningDataReturnsNull_2363) {
  const gchar* text = poppler_signing_data_get_signature_text(nullptr);
  EXPECT_EQ(text, nullptr);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsSamePointerWhenSignatureTextSet_2363) {
  PopplerSigningData signing_data{};
  gchar signature_text[] = "Signed by Unit Test";

  // We only rely on public/inferred struct layout provided in the prompt:
  // signature_text is a char* field.
  signing_data.signature_text = signature_text;

  const gchar* text = poppler_signing_data_get_signature_text(&signing_data);

  // Observable behavior: should return the signature_text pointer.
  EXPECT_EQ(text, signature_text);
  EXPECT_STREQ(text, "Signed by Unit Test");
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnsNullWhenSignatureTextIsNull_2363) {
  PopplerSigningData signing_data{};
  signing_data.signature_text = nullptr;

  const gchar* text = poppler_signing_data_get_signature_text(&signing_data);

  EXPECT_EQ(text, nullptr);
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, WorksWithEmptyStringSignatureText_2363) {
  PopplerSigningData signing_data{};
  gchar empty_text[] = "";

  signing_data.signature_text = empty_text;

  const gchar* text = poppler_signing_data_get_signature_text(&signing_data);

  EXPECT_EQ(text, empty_text);
  EXPECT_STREQ(text, "");
}

TEST_F(PopplerSigningDataGetSignatureTextTest_2363, ReturnedPointerReflectsUnderlyingBufferMutation_2363) {
  PopplerSigningData signing_data{};
  gchar signature_text[] = "ABC";

  signing_data.signature_text = signature_text;

  const gchar* text1 = poppler_signing_data_get_signature_text(&signing_data);
  ASSERT_NE(text1, nullptr);
  EXPECT_STREQ(text1, "ABC");

  // Mutate the backing buffer (observable via returned pointer).
  signature_text[0] = 'X';

  const gchar* text2 = poppler_signing_data_get_signature_text(&signing_data);
  ASSERT_NE(text2, nullptr);

  // Still returns the same pointer; contents changed because caller mutated buffer.
  EXPECT_EQ(text2, signature_text);
  EXPECT_STREQ(text2, "XBC");
}

}  // namespace