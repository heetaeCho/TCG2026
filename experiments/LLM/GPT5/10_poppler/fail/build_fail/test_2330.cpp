// poppler-signature-info-get-signer-name-test_2330.cc
#include <gtest/gtest.h>

#include <glib.h>

// Include the public Poppler GLib header (path may vary by project layout).
// If your project exposes poppler-form-field.h via a different include path,
// adjust this include accordingly.
#include <poppler.h>

// We only rely on the interface contract:
//   const gchar *poppler_signature_info_get_signer_name(const PopplerSignatureInfo *siginfo);
//
// And the fact that passing NULL should return NULL (g_return_val_if_fail).
// We do NOT inspect or depend on any private/internal state besides constructing
// a PopplerSignatureInfo instance in a minimal way for tests that need a non-null pointer.

class PopplerSignatureInfoGetSignerNameTest_2330 : public ::testing::Test {
protected:
  void TearDown() override { g_free(signer_name_); }

  // We create a PopplerSignatureInfo object as an opaque struct instance for testing.
  // This is necessary to pass a non-null pointer into the function under test.
  // We only set the signer_name field because that's the observable behavior returned.
  PopplerSignatureInfo siginfo_{}; // Zero-init for safety
  gchar* signer_name_ = nullptr;
};

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, NullSigInfoReturnsNull_2330) {
  const gchar* name = poppler_signature_info_get_signer_name(nullptr);
  EXPECT_EQ(name, nullptr);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsSignerNamePointerWhenPresent_2330) {
  signer_name_ = g_strdup("Alice Example");
  // We assume PopplerSignatureInfo is compatible with being stack-allocated in tests
  // in this codebase (as is typical for these GLib wrapper structs in the repo).
  // Only set what we need for the observable behavior.
  siginfo_.signer_name = signer_name_;

  const gchar* name = poppler_signature_info_get_signer_name(&siginfo_);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "Alice Example");

  // Also verify it returns the same pointer (observable through interface).
  EXPECT_EQ(name, siginfo_.signer_name);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, ReturnsNullWhenSignerNameIsNull_2330) {
  siginfo_.signer_name = nullptr;

  const gchar* name = poppler_signature_info_get_signer_name(&siginfo_);
  EXPECT_EQ(name, nullptr);
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, EmptyStringIsReturnedAsEmptyString_2330) {
  signer_name_ = g_strdup("");
  siginfo_.signer_name = signer_name_;

  const gchar* name = poppler_signature_info_get_signer_name(&siginfo_);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "");
}

TEST_F(PopplerSignatureInfoGetSignerNameTest_2330, NonAsciiUtf8StringIsReturnedUnmodified_2330) {
  // GLib strings are typically UTF-8. This verifies the function doesn't mangle bytes.
  signer_name_ = g_strdup("홍길동");
  siginfo_.signer_name = signer_name_;

  const gchar* name = poppler_signature_info_get_signer_name(&siginfo_);
  ASSERT_NE(name, nullptr);
  EXPECT_STREQ(name, "홍길동");
}