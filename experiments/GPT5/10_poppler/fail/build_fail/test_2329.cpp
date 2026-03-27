// poppler_signature_info_get_certificate_status_test_2329.cc
#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include "poppler-form-field.h"
}

// The production code defines PopplerSignatureInfo as an opaque-ish type in the
// public header, but the snippet shows the struct layout used by the function.
// We only use it to construct inputs and observe outputs via the public API.
struct _PopplerSignatureInfo {
  int sig_status;
  PopplerCertificateStatus cert_status;
  char* signer_name;
  int* local_signing_time;
  PopplerCertificateInfo* certificate_info;
};

extern "C" PopplerCertificateStatus
poppler_signature_info_get_certificate_status(const PopplerSignatureInfo* siginfo);

class PopplerSignatureInfoGetCertificateStatusTest_2329 : public ::testing::Test {};

// Normal operation: returns the exact cert_status stored in the struct.
TEST_F(PopplerSignatureInfoGetCertificateStatusTest_2329,
       ReturnsCertStatusTrusted_2329) {
  _PopplerSignatureInfo info{};
  info.cert_status = POPPLER_CERTIFICATE_TRUSTED;

  EXPECT_EQ(poppler_signature_info_get_certificate_status(
                reinterpret_cast<const PopplerSignatureInfo*>(&info)),
            POPPLER_CERTIFICATE_TRUSTED);
}

TEST_F(PopplerSignatureInfoGetCertificateStatusTest_2329,
       ReturnsCertStatusUntrustedIssuer_2329) {
  _PopplerSignatureInfo info{};
  info.cert_status = POPPLER_CERTIFICATE_UNTRUSTED_ISSUER;

  EXPECT_EQ(poppler_signature_info_get_certificate_status(
                reinterpret_cast<const PopplerSignatureInfo*>(&info)),
            POPPLER_CERTIFICATE_UNTRUSTED_ISSUER);
}

TEST_F(PopplerSignatureInfoGetCertificateStatusTest_2329,
       ReturnsCertStatusUnknownIssuer_2329) {
  _PopplerSignatureInfo info{};
  info.cert_status = POPPLER_CERTIFICATE_UNKNOWN_ISSUER;

  EXPECT_EQ(poppler_signature_info_get_certificate_status(
                reinterpret_cast<const PopplerSignatureInfo*>(&info)),
            POPPLER_CERTIFICATE_UNKNOWN_ISSUER);
}

TEST_F(PopplerSignatureInfoGetCertificateStatusTest_2329,
       ReturnsCertStatusRevoked_2329) {
  _PopplerSignatureInfo info{};
  info.cert_status = POPPLER_CERTIFICATE_REVOKED;

  EXPECT_EQ(poppler_signature_info_get_certificate_status(
                reinterpret_cast<const PopplerSignatureInfo*>(&info)),
            POPPLER_CERTIFICATE_REVOKED);
}

TEST_F(PopplerSignatureInfoGetCertificateStatusTest_2329,
       ReturnsCertStatusExpired_2329) {
  _PopplerSignatureInfo info{};
  info.cert_status = POPPLER_CERTIFICATE_EXPIRED;

  EXPECT_EQ(poppler_signature_info_get_certificate_status(
                reinterpret_cast<const PopplerSignatureInfo*>(&info)),
            POPPLER_CERTIFICATE_EXPIRED);
}

TEST_F(PopplerSignatureInfoGetCertificateStatusTest_2329,
       ReturnsCertStatusGenericError_2329) {
  _PopplerSignatureInfo info{};
  info.cert_status = POPPLER_CERTIFICATE_GENERIC_ERROR;

  EXPECT_EQ(poppler_signature_info_get_certificate_status(
                reinterpret_cast<const PopplerSignatureInfo*>(&info)),
            POPPLER_CERTIFICATE_GENERIC_ERROR);
}

TEST_F(PopplerSignatureInfoGetCertificateStatusTest_2329,
       ReturnsCertStatusNotVerified_2329) {
  _PopplerSignatureInfo info{};
  info.cert_status = POPPLER_CERTIFICATE_NOT_VERIFIED;

  EXPECT_EQ(poppler_signature_info_get_certificate_status(
                reinterpret_cast<const PopplerSignatureInfo*>(&info)),
            POPPLER_CERTIFICATE_NOT_VERIFIED);
}

// Boundary: ensure other fields don't affect the observable behavior.
TEST_F(PopplerSignatureInfoGetCertificateStatusTest_2329,
       IgnoresOtherFields_2329) {
  _PopplerSignatureInfo info{};
  info.sig_status = 12345;
  info.cert_status = POPPLER_CERTIFICATE_REVOKED;
  info.signer_name = const_cast<char*>("Signer");
  int local_time = 42;
  info.local_signing_time = &local_time;
  info.certificate_info = reinterpret_cast<PopplerCertificateInfo*>(0x1);

  EXPECT_EQ(poppler_signature_info_get_certificate_status(
                reinterpret_cast<const PopplerSignatureInfo*>(&info)),
            POPPLER_CERTIFICATE_REVOKED);
}

// Error case: null input is observable through the return value.
// (The underlying g_return_val_if_fail may also emit a critical log; we only
// assert the observable return value here.)
TEST_F(PopplerSignatureInfoGetCertificateStatusTest_2329,
       NullSiginfoReturnsGenericError_2329) {
  EXPECT_EQ(poppler_signature_info_get_certificate_status(nullptr),
            POPPLER_CERTIFICATE_GENERIC_ERROR);
}