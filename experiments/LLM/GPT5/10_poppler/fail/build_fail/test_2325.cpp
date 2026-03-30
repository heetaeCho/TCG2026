// poppler_signature_info_copy_test_2325.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <string.h>

extern "C" {

// Minimal types to compile the tests (match the fields used by the API).
typedef enum {
  POPPLER_CERTIFICATE_STATUS_UNKNOWN = 0,
  POPPLER_CERTIFICATE_STATUS_TRUSTED = 1,
  POPPLER_CERTIFICATE_STATUS_UNTRUSTED = 2
} PopplerCertificateStatus;

struct _PopplerCertificateInfo {
  int magic;
};
typedef _PopplerCertificateInfo PopplerCertificateInfo;

struct _PopplerSignatureInfo {
  int sig_status;
  PopplerCertificateStatus cert_status;
  char* signer_name;
  GDateTime* local_signing_time;
  PopplerCertificateInfo* certificate_info;
};
typedef _PopplerSignatureInfo PopplerSignatureInfo;

// Function under test (implemented in the production codebase).
PopplerSignatureInfo* poppler_signature_info_copy(const PopplerSignatureInfo* siginfo);

// External collaborator used by poppler_signature_info_copy.
// We provide a test double to verify interactions.
PopplerCertificateInfo* poppler_certificate_info_copy(const PopplerCertificateInfo* certinfo);

}  // extern "C"

// ---- Test double state for poppler_certificate_info_copy ----
static int g_cert_copy_calls = 0;
static const PopplerCertificateInfo* g_cert_copy_last_arg = nullptr;

extern "C" PopplerCertificateInfo* poppler_certificate_info_copy(
    const PopplerCertificateInfo* certinfo) {
  ++g_cert_copy_calls;
  g_cert_copy_last_arg = certinfo;

  if (!certinfo) {
    return nullptr;
  }

  PopplerCertificateInfo* out = g_new0(PopplerCertificateInfo, 1);
  out->magic = certinfo->magic;
  return out;
}

static void ResetCertCopySpy() {
  g_cert_copy_calls = 0;
  g_cert_copy_last_arg = nullptr;
}

static void FreeSignatureInfoShallow(PopplerSignatureInfo* info) {
  if (!info) return;
  g_free(info->signer_name);
  if (info->local_signing_time) {
    g_date_time_unref(info->local_signing_time);
  }
  if (info->certificate_info) {
    g_free(info->certificate_info);
  }
  g_free(info);
}

class PopplerSignatureInfoCopyTest_2325 : public ::testing::Test {
 protected:
  void SetUp() override { ResetCertCopySpy(); }
};

TEST_F(PopplerSignatureInfoCopyTest_2325, NullInputReturnsNull_2325) {
  PopplerSignatureInfo* out = poppler_signature_info_copy(nullptr);
  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(g_cert_copy_calls, 0);
  EXPECT_EQ(g_cert_copy_last_arg, nullptr);
}

TEST_F(PopplerSignatureInfoCopyTest_2325, CopiesAllFieldsAndDeepCopiesName_2325) {
  PopplerCertificateInfo cert_in;
  cert_in.magic = 12345;

  PopplerSignatureInfo in;
  in.sig_status = 7;
  in.cert_status = POPPLER_CERTIFICATE_STATUS_TRUSTED;
  in.signer_name = g_strdup("Alice");
  in.local_signing_time = g_date_time_new_now_local();
  in.certificate_info = &cert_in;

  ASSERT_NE(in.local_signing_time, nullptr);

  PopplerSignatureInfo* out = poppler_signature_info_copy(&in);
  ASSERT_NE(out, nullptr);

  // New struct instance.
  EXPECT_NE(out, &in);

  // Scalar fields copied.
  EXPECT_EQ(out->sig_status, in.sig_status);
  EXPECT_EQ(out->cert_status, in.cert_status);

  // signer_name deep-copied (pointer differs, content equal).
  ASSERT_NE(out->signer_name, nullptr);
  EXPECT_NE(out->signer_name, in.signer_name);
  EXPECT_STREQ(out->signer_name, "Alice");

  // local_signing_time ref: API returns same pointer (refcount incremented).
  EXPECT_EQ(out->local_signing_time, in.local_signing_time);

  // External collaborator invoked with the original certificate_info.
  EXPECT_EQ(g_cert_copy_calls, 1);
  EXPECT_EQ(g_cert_copy_last_arg, in.certificate_info);

  // And returned cert info is a copy (not the same pointer, same contents via our stub).
  ASSERT_NE(out->certificate_info, nullptr);
  EXPECT_NE(out->certificate_info, in.certificate_info);
  EXPECT_EQ(out->certificate_info->magic, cert_in.magic);

  // Free input-owned string; copied output should remain valid.
  g_free(in.signer_name);
  in.signer_name = nullptr;
  EXPECT_STREQ(out->signer_name, "Alice");

  // Cleanup: out owns its fields.
  FreeSignatureInfoShallow(out);

  // Cleanup input: it still owns local_signing_time (copy only refs it).
  g_date_time_unref(in.local_signing_time);
  in.local_signing_time = nullptr;
}

TEST_F(PopplerSignatureInfoCopyTest_2325, HandlesNullSignerName_2325) {
  PopplerCertificateInfo cert_in;
  cert_in.magic = 99;

  PopplerSignatureInfo in;
  in.sig_status = 1;
  in.cert_status = POPPLER_CERTIFICATE_STATUS_UNTRUSTED;
  in.signer_name = nullptr;
  in.local_signing_time = g_date_time_new_now_local();
  in.certificate_info = &cert_in;

  ASSERT_NE(in.local_signing_time, nullptr);

  PopplerSignatureInfo* out = poppler_signature_info_copy(&in);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->signer_name, nullptr);

  EXPECT_EQ(g_cert_copy_calls, 1);
  EXPECT_EQ(g_cert_copy_last_arg, in.certificate_info);

  FreeSignatureInfoShallow(out);

  g_date_time_unref(in.local_signing_time);
  in.local_signing_time = nullptr;
}

TEST_F(PopplerSignatureInfoCopyTest_2325, HandlesNullCertificateInfoAndStillCallsCopy_2325) {
  PopplerSignatureInfo in;
  in.sig_status = 42;
  in.cert_status = POPPLER_CERTIFICATE_STATUS_UNKNOWN;
  in.signer_name = g_strdup("Bob");
  in.local_signing_time = g_date_time_new_now_local();
  in.certificate_info = nullptr;

  ASSERT_NE(in.local_signing_time, nullptr);

  PopplerSignatureInfo* out = poppler_signature_info_copy(&in);
  ASSERT_NE(out, nullptr);

  EXPECT_EQ(out->sig_status, 42);
  EXPECT_EQ(out->cert_status, POPPLER_CERTIFICATE_STATUS_UNKNOWN);
  ASSERT_NE(out->signer_name, nullptr);
  EXPECT_STREQ(out->signer_name, "Bob");

  // Still verifies the external interaction and the propagated result.
  EXPECT_EQ(g_cert_copy_calls, 1);
  EXPECT_EQ(g_cert_copy_last_arg, nullptr);
  EXPECT_EQ(out->certificate_info, nullptr);

  FreeSignatureInfoShallow(out);

  g_free(in.signer_name);
  in.signer_name = nullptr;
  g_date_time_unref(in.local_signing_time);
  in.local_signing_time = nullptr;
}