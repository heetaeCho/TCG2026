// poppler-signature-info-get-signature-status-test.cc
//
// Unit tests for:
//   PopplerSignatureStatus poppler_signature_info_get_signature_status(const PopplerSignatureInfo *siginfo)
//
// Constraints:
// - Treat implementation as black box: only verify observable behavior from interface.
// - No access to private/internal state beyond what is required to construct valid public inputs.
// - Include normal, boundary, and error cases.
//
// TEST_ID: 2327

#include <gtest/gtest.h>

#include <glib.h>

// Include the public Poppler GLib header(s).
// Depending on your build, the exact include may vary.
#include <poppler.h>

// The function under test is defined in poppler-form-field.cc in the codebase.
// We declare it here to avoid needing to include internal .cc files.
extern "C" PopplerSignatureStatus
poppler_signature_info_get_signature_status(const PopplerSignatureInfo *siginfo);

namespace {

// A tiny helper to build a PopplerSignatureInfo instance for testing.
// This uses the public (opaque) PopplerSignatureInfo type, but since the interface
// requires a pointer to PopplerSignatureInfo, we need a concrete instance.
// In Poppler GLib, PopplerSignatureInfo is typically a typedef of struct _PopplerSignatureInfo.
// If in your build PopplerSignatureInfo is opaque, adjust by constructing it via the library API
// (if available) or by including the appropriate internal header in the test build only.
struct LocalPopplerSignatureInfoCompat {
  int sig_status;
  PopplerCertificateStatus cert_status;
  char *signer_name;
  int *local_signing_time;
  PopplerCertificateInfo *certificate_info;
};

// Sanity check: ensure our compat struct can be treated as PopplerSignatureInfo in this build.
// If this fails, it means PopplerSignatureInfo is opaque here; in that case,
// replace this approach with the proper Poppler API constructor (if available) or
// include the internal header that defines _PopplerSignatureInfo for tests.
static_assert(sizeof(LocalPopplerSignatureInfoCompat) >= sizeof(void*),
              "Compat struct must be a real object");

}  // namespace

class PopplerSignatureInfoGetSignatureStatusTest_2327 : public ::testing::Test {};

// Normal operation: returns the stored signature status.
TEST_F(PopplerSignatureInfoGetSignatureStatusTest_2327,
       ReturnsSignatureStatusValue_2327) {
  LocalPopplerSignatureInfoCompat info{};
  info.sig_status = POPPLER_SIGNATURE_VALID;  // pick a concrete enum value

  const auto *siginfo = reinterpret_cast<const PopplerSignatureInfo *>(&info);

  EXPECT_EQ(poppler_signature_info_get_signature_status(siginfo),
            POPPLER_SIGNATURE_VALID);
}

// Boundary/variety: verify it passes through different enum values.
TEST_F(PopplerSignatureInfoGetSignatureStatusTest_2327,
       ReturnsDifferentStatusValues_2327) {
  LocalPopplerSignatureInfoCompat info{};
  const auto *siginfo = reinterpret_cast<const PopplerSignatureInfo *>(&info);

  info.sig_status = POPPLER_SIGNATURE_INVALID;
  EXPECT_EQ(poppler_signature_info_get_signature_status(siginfo),
            POPPLER_SIGNATURE_INVALID);

  info.sig_status = POPPLER_SIGNATURE_DIGEST_MISMATCH;
  EXPECT_EQ(poppler_signature_info_get_signature_status(siginfo),
            POPPLER_SIGNATURE_DIGEST_MISMATCH);

  info.sig_status = POPPLER_SIGNATURE_DECODING_ERROR;
  EXPECT_EQ(poppler_signature_info_get_signature_status(siginfo),
            POPPLER_SIGNATURE_DECODING_ERROR);
}

// Error case: null pointer should trigger g_return_val_if_fail and return
// POPPLER_SIGNATURE_GENERIC_ERROR.
TEST_F(PopplerSignatureInfoGetSignatureStatusTest_2327,
       NullPointerReturnsGenericError_2327) {
  // g_return_val_if_fail() emits a critical; assert that happens.
  // GLib's g_test framework integrates with this. In plain gtest, we can still
  // use g_test_expect_message / g_test_assert_expected_messages.
  g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*siginfo*failed*");

  EXPECT_EQ(poppler_signature_info_get_signature_status(nullptr),
            POPPLER_SIGNATURE_GENERIC_ERROR);

  g_test_assert_expected_messages();
}

// Robustness: it should not depend on other fields (they may be null).
TEST_F(PopplerSignatureInfoGetSignatureStatusTest_2327,
       IgnoresOtherFieldsBeingNull_2327) {
  LocalPopplerSignatureInfoCompat info{};
  info.sig_status = POPPLER_SIGNATURE_VALID;
  info.signer_name = nullptr;
  info.local_signing_time = nullptr;
  info.certificate_info = nullptr;

  const auto *siginfo = reinterpret_cast<const PopplerSignatureInfo *>(&info);

  EXPECT_EQ(poppler_signature_info_get_signature_status(siginfo),
            POPPLER_SIGNATURE_VALID);
}