// pdfsig_getReadableCertState_test_2677.cc
#include <gtest/gtest.h>

// Treat the implementation as a black box: we only use the observable mapping
// implied by the function signature + enum values.
//
// NOTE: The production function is `static` in pdfsig.cc, so to test it without
// re-implementing its logic, we compile the implementation into this test TU.
// This is a common pattern for testing file-local helpers.
#include "TestProjects/poppler/utils/pdfsig.cc"

#include "TestProjects/poppler/poppler/SignatureInfo.h"

namespace {

TEST(getReadableCertStateTest_2677, Trusted_ReturnsReadableMessage_2677) {
  EXPECT_STREQ("Certificate is Trusted.", getReadableCertState(CERTIFICATE_TRUSTED));
}

TEST(getReadableCertStateTest_2677, UntrustedIssuer_ReturnsReadableMessage_2677) {
  EXPECT_STREQ("Certificate issuer isn't Trusted.",
               getReadableCertState(CERTIFICATE_UNTRUSTED_ISSUER));
}

TEST(getReadableCertStateTest_2677, UnknownIssuer_ReturnsReadableMessage_2677) {
  EXPECT_STREQ("Certificate issuer is unknown.",
               getReadableCertState(CERTIFICATE_UNKNOWN_ISSUER));
}

TEST(getReadableCertStateTest_2677, Revoked_ReturnsReadableMessage_2677) {
  EXPECT_STREQ("Certificate has been Revoked.", getReadableCertState(CERTIFICATE_REVOKED));
}

TEST(getReadableCertStateTest_2677, Expired_ReturnsReadableMessage_2677) {
  EXPECT_STREQ("Certificate has Expired", getReadableCertState(CERTIFICATE_EXPIRED));
}

TEST(getReadableCertStateTest_2677, NotVerified_ReturnsReadableMessage_2677) {
  EXPECT_STREQ("Certificate has not yet been verified.",
               getReadableCertState(CERTIFICATE_NOT_VERIFIED));
}

TEST(getReadableCertStateTest_2677, GenericError_FallsBackToUnknownIssueMessage_2677) {
  // Boundary/error case that is observable through the interface:
  // an enum value not explicitly handled in the switch should yield the default string.
  EXPECT_STREQ("Unknown issue with Certificate or corrupted data.",
               getReadableCertState(CERTIFICATE_GENERIC_ERROR));
}

TEST(getReadableCertStateTest_2677, OutOfRangeEnum_FallsBackToUnknownIssueMessage_2677) {
  // Boundary/error case: pass an out-of-range value via static_cast.
  const auto invalid = static_cast<CertificateValidationStatus>(-1);
  EXPECT_STREQ("Unknown issue with Certificate or corrupted data.",
               getReadableCertState(invalid));
}

TEST(getReadableCertStateTest_2677, HighOutOfRangeEnum_FallsBackToUnknownIssueMessage_2677) {
  // Another boundary: very large out-of-range value.
  const auto invalid = static_cast<CertificateValidationStatus>(999999);
  EXPECT_STREQ("Unknown issue with Certificate or corrupted data.",
               getReadableCertState(invalid));
}

}  // namespace