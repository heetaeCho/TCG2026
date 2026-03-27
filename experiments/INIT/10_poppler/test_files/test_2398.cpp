// poppler-certificate-info-get-subject-email-test.cc
#include <gtest/gtest.h>

#include "poppler-form-field.h"  // Provides PopplerCertificateInfo and poppler_certificate_info_get_subject_email()

TEST(PopplerCertificateInfoGetSubjectEmailTest_2398, NullCertificateInfoReturnsNull_2398) {
  EXPECT_EQ(poppler_certificate_info_get_subject_email(nullptr), nullptr);
}

TEST(PopplerCertificateInfoGetSubjectEmailTest_2398, ReturnsExactPointerStoredInStruct_2398) {
  // Black-box observable behavior: function returns certificate_info->subject_email
  // (as per provided interface snippet).
  PopplerCertificateInfo info{};
  const char kEmail[] = "alice@example.com";
  info.subject_email = const_cast<char*>(kEmail);

  const char* result = poppler_certificate_info_get_subject_email(&info);
  EXPECT_EQ(result, kEmail);
}

TEST(PopplerCertificateInfoGetSubjectEmailTest_2398, ReturnsNullWhenSubjectEmailIsNull_2398) {
  PopplerCertificateInfo info{};
  info.subject_email = nullptr;

  EXPECT_EQ(poppler_certificate_info_get_subject_email(&info), nullptr);
}

TEST(PopplerCertificateInfoGetSubjectEmailTest_2398, DoesNotModifyStoredEmailString_2398) {
  PopplerCertificateInfo info{};
  char email_buf[] = "bob@example.com";
  info.subject_email = email_buf;

  const char* result = poppler_certificate_info_get_subject_email(&info);
  ASSERT_NE(result, nullptr);
  EXPECT_STREQ(result, "bob@example.com");

  // Ensure the call didn't mutate the buffer (observable through buffer content).
  EXPECT_STREQ(email_buf, "bob@example.com");
}