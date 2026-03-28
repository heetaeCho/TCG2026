// ============================================================================
// Unit tests for poppler_signature_info_get_certificate_info
// File: poppler-form-field-test-2328.cc
// ============================================================================

#include <gtest/gtest.h>

#include <glib.h>

// Only what we need from the interface shown in the prompt.
// We do NOT re-implement internal logic; we just provide the struct layout
// that the function signature relies on.
typedef struct _PopplerSignatureInfo PopplerSignatureInfo;
typedef struct _PopplerCertificateInfo PopplerCertificateInfo;
typedef int PopplerCertificateStatus;

// Matches the "Known or Inferred Dependencies (Optional)" snippet.
struct _PopplerSignatureInfo {
  int sig_status;
  PopplerCertificateStatus cert_status;
  char* signer_name;
  int* local_signing_time;
  PopplerCertificateInfo* certificate_info;
};

extern "C" {
// Function under test (implemented in poppler-form-field.cc in the real codebase).
PopplerCertificateInfo* poppler_signature_info_get_certificate_info(
    const PopplerSignatureInfo* siginfo);
}

class PopplerSignatureInfoGetCertificateInfoTest_2328 : public ::testing::Test {
};

TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, NullSiginfoReturnsNull_2328) {
  // Exceptional/error case observable via return value:
  // g_return_val_if_fail(siginfo != nullptr, NULL)
  EXPECT_EQ(poppler_signature_info_get_certificate_info(nullptr), nullptr);
}

TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, ReturnsCertificateInfoPointerWhenPresent_2328) {
  PopplerSignatureInfo siginfo{};
  PopplerCertificateInfo cert_obj{};
  siginfo.certificate_info = &cert_obj;

  EXPECT_EQ(poppler_signature_info_get_certificate_info(&siginfo), &cert_obj);
}

TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, ReturnsNullWhenCertificateInfoIsNull_2328) {
  // Boundary condition: certificate_info is nullptr but siginfo is valid.
  PopplerSignatureInfo siginfo{};
  siginfo.certificate_info = nullptr;

  EXPECT_EQ(poppler_signature_info_get_certificate_info(&siginfo), nullptr);
}

TEST_F(PopplerSignatureInfoGetCertificateInfoTest_2328, DoesNotDependOnOtherFields_2328) {
  // Observable behavior should be solely the returned certificate_info pointer.
  // We vary unrelated fields to ensure the function still returns certificate_info.
  PopplerSignatureInfo siginfo{};
  PopplerCertificateInfo cert_obj{};

  siginfo.sig_status = -123;
  siginfo.cert_status = static_cast<PopplerCertificateStatus>(999);
  siginfo.signer_name = const_cast<char*>("Some Signer");
  int local_time[6] = {2026, 2, 23, 0, 0, 0};
  siginfo.local_signing_time = local_time;
  siginfo.certificate_info = &cert_obj;

  EXPECT_EQ(poppler_signature_info_get_certificate_info(&siginfo), &cert_obj);
}