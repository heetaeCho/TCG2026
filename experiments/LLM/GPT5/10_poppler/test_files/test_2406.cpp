// File: poppler_certificate_info_free_test_2406.cc
#include <gtest/gtest.h>

#include <glib.h>

// The production code is C, so ensure we use C linkage for the symbol.
extern "C" {

// Forward declaration matching the GLib-facing type name.
typedef struct _PopplerCertificateInfo PopplerCertificateInfo;

// Function under test (implemented in the production codebase).
void poppler_certificate_info_free(PopplerCertificateInfo *certificate_info);
}

// NOTE: The real project will already have this struct definition in headers.
// We only mirror the public fields shown in the prompt so we can construct
// observable inputs for the black-box function.
struct _PopplerCertificateInfo {
  char *id;
  char *subject_common_name;
  char *subject_organization;
  char *subject_email;
  char *issuer_common_name;
  char *issuer_organization;
  char *issuer_email;
  // In the implementation snippet, these are treated as GDateTime* (unref'd).
  GDateTime *issued;
  GDateTime *expires;
};

namespace {

class PopplerCertificateInfoFreeTest_2406 : public ::testing::Test {
 protected:
  static PopplerCertificateInfo *NewZeroed() {
    // Use GLib allocation to match typical ownership patterns.
    return static_cast<PopplerCertificateInfo *>(g_malloc0(sizeof(PopplerCertificateInfo)));
  }
};

TEST_F(PopplerCertificateInfoFreeTest_2406, NullPointerNoCrash_2406) {
  // Normal/defensive operation: freeing nullptr should be a no-op.
  ASSERT_NO_FATAL_FAILURE(poppler_certificate_info_free(nullptr));
}

TEST_F(PopplerCertificateInfoFreeTest_2406, AllNullFieldsNoCrash_2406) {
  // Boundary: all fields are null pointers.
  PopplerCertificateInfo *info = NewZeroed();
  ASSERT_NE(info, nullptr);

  ASSERT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

TEST_F(PopplerCertificateInfoFreeTest_2406, FreesWhenOnlyStringsAreSet_2406) {
  // Normal operation: strings set, date fields null.
  PopplerCertificateInfo *info = NewZeroed();
  ASSERT_NE(info, nullptr);

  info->id = g_strdup("cert-id-123");
  info->subject_common_name = g_strdup("Subject CN");
  info->subject_organization = g_strdup("Subject Org");
  info->subject_email = g_strdup("subject@example.com");
  info->issuer_common_name = g_strdup("Issuer CN");
  info->issuer_organization = g_strdup("Issuer Org");
  info->issuer_email = g_strdup("issuer@example.com");
  info->issued = nullptr;
  info->expires = nullptr;

  ASSERT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

TEST_F(PopplerCertificateInfoFreeTest_2406, HandlesEmptyAndLongStrings_2406) {
  // Boundary conditions for string fields: empty strings and a very long string.
  PopplerCertificateInfo *info = NewZeroed();
  ASSERT_NE(info, nullptr);

  info->id = g_strdup("");  // empty string
  info->subject_common_name = g_strdup("A");

  // Long string boundary (still valid input): allocate a large buffer.
  const gsize kLen = 64 * 1024;
  gchar *long_str = static_cast<gchar *>(g_malloc0(kLen + 1));
  ASSERT_NE(long_str, nullptr);
  for (gsize i = 0; i < kLen; ++i) long_str[i] = 'x';
  long_str[kLen] = '\0';
  info->issuer_common_name = long_str;

  ASSERT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));
}

TEST_F(PopplerCertificateInfoFreeTest_2406, UnrefsDateTimesWithoutDestroyingExternalRefs_2406) {
  // Observable behavior: if we hold our own ref to a GDateTime, freeing the
  // certificate info should drop only its reference (unref once), leaving our
  // external ref still usable.
  PopplerCertificateInfo *info = NewZeroed();
  ASSERT_NE(info, nullptr);

  GDateTime *issued = g_date_time_new_now_utc();
  ASSERT_NE(issued, nullptr);
  GDateTime *expires = g_date_time_new_now_utc();
  ASSERT_NE(expires, nullptr);

  // Take external references we will keep after free() is called.
  GDateTime *issued_keep = g_date_time_ref(issued);
  ASSERT_NE(issued_keep, nullptr);
  GDateTime *expires_keep = g_date_time_ref(expires);
  ASSERT_NE(expires_keep, nullptr);

  // CertificateInfo owns one ref (the original pointers).
  info->issued = issued;
  info->expires = expires;

  ASSERT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));

  // If poppler_certificate_info_free unref'd its refs correctly, our kept refs
  // should still be valid to use.
  ASSERT_NO_FATAL_FAILURE((void)g_date_time_to_unix(issued_keep));
  ASSERT_NO_FATAL_FAILURE((void)g_date_time_to_unix(expires_keep));

  g_date_time_unref(issued_keep);
  g_date_time_unref(expires_keep);
}

TEST_F(PopplerCertificateInfoFreeTest_2406, MixedNullAndNonNullFieldsNoCrash_2406) {
  // Boundary: mixture of null/non-null across all fields.
  PopplerCertificateInfo *info = NewZeroed();
  ASSERT_NE(info, nullptr);

  info->id = g_strdup("id");
  info->subject_common_name = nullptr;
  info->subject_organization = g_strdup("org");
  info->subject_email = nullptr;
  info->issuer_common_name = g_strdup("issuer");
  info->issuer_organization = nullptr;
  info->issuer_email = g_strdup("issuer@example.com");

  info->issued = g_date_time_new_now_utc();
  ASSERT_NE(info->issued, nullptr);
  info->expires = nullptr;

  // Keep an external ref to verify issued isn't over-freed.
  GDateTime *issued_keep = g_date_time_ref(info->issued);
  ASSERT_NE(issued_keep, nullptr);

  ASSERT_NO_FATAL_FAILURE(poppler_certificate_info_free(info));

  ASSERT_NO_FATAL_FAILURE((void)g_date_time_to_unix(issued_keep));
  g_date_time_unref(issued_keep);
}

}  // namespace