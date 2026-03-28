// poppler-signing-data-get-reason-test.cc
#include <gtest/gtest.h>

#include <glib.h>

#include "poppler.h"

// We only rely on the public API signature under test.
// The implementation uses g_return_val_if_fail(signing_data != nullptr, nullptr)
// and returns signing_data->reason otherwise.

TEST(PopplerSigningDataGetReasonTest_2383, NullSigningDataReturnsNull_2383) {
  // This should not crash; GLib macro returns nullptr for invalid input.
  const gchar* reason = poppler_signing_data_get_reason(nullptr);
  EXPECT_EQ(reason, nullptr);
}

TEST(PopplerSigningDataGetReasonTest_2383, ValidSigningDataWithNullReasonReturnsNull_2383) {
  // Create a PopplerSigningData object without relying on any internal logic.
  // We treat the implementation as a black box, but the public getter returns
  // a const gchar* that can be nullptr when unset.
  PopplerSigningData signing_data{};
  // Ensure reason is null.
  signing_data.reason = nullptr;

  const gchar* reason = poppler_signing_data_get_reason(&signing_data);
  EXPECT_EQ(reason, nullptr);
}

TEST(PopplerSigningDataGetReasonTest_2383, ValidSigningDataReturnsExactPointer_2383) {
  PopplerSigningData signing_data{};

  // Use a stable string with static storage duration so the returned pointer
  // remains valid for the duration of the test.
  static const gchar kReason[] = "Signing reason: approval";
  signing_data.reason = const_cast<char*>(kReason);

  const gchar* reason = poppler_signing_data_get_reason(&signing_data);

  // Observable behavior: should return the stored pointer (no copying implied by signature).
  EXPECT_EQ(reason, kReason);
  EXPECT_STREQ(reason, "Signing reason: approval");
}

TEST(PopplerSigningDataGetReasonTest_2383, EmptyStringReasonIsReturned_2383) {
  PopplerSigningData signing_data{};

  static const gchar kEmpty[] = "";
  signing_data.reason = const_cast<char*>(kEmpty);

  const gchar* reason = poppler_signing_data_get_reason(&signing_data);
  ASSERT_NE(reason, nullptr);
  EXPECT_EQ(reason, kEmpty);
  EXPECT_STREQ(reason, "");
}

TEST(PopplerSigningDataGetReasonTest_2383, ReturnedPointerReflectsExternalMutation_2383) {
  PopplerSigningData signing_data{};

  // Use a mutable buffer to verify the getter returns a pointer into the underlying storage.
  // This checks observable pointer semantics without assuming internal behavior beyond "returns signing_data->reason".
  gchar buf[] = "Initial";
  signing_data.reason = buf;

  const gchar* reason1 = poppler_signing_data_get_reason(&signing_data);
  ASSERT_NE(reason1, nullptr);
  EXPECT_STREQ(reason1, "Initial");

  // Mutate the underlying storage.
  buf[0] = 'F';  // "Fnitial"
  const gchar* reason2 = poppler_signing_data_get_reason(&signing_data);

  // Same pointer and updated contents should be observed.
  EXPECT_EQ(reason2, reason1);
  EXPECT_STREQ(reason2, "Fnitial");
}