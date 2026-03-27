// File: poppler-certificate-info-get-expiration-time-test.cc

#include <gtest/gtest.h>

#include <glib.h>

extern "C" {
#include <poppler.h>
}

// poppler_certificate_info_get_expiration_time(const PopplerCertificateInfo *certificate_info)
// Behavior (black-box, from interface):
// - Returns nullptr if certificate_info is nullptr (g_return_val_if_fail)
// - Otherwise returns certificate_info->expires (may be nullptr)

class PopplerCertificateInfoGetExpirationTimeTest_2403 : public ::testing::Test {
protected:
  static void ExpectGlibCritical(const char *expected_substring)
  {
    // g_return_val_if_fail typically logs a CRITICAL containing "assertion '... != NULL' failed"
    // We only assert module + level and a substring to avoid depending on exact wording.
    g_test_expect_message(G_LOG_DOMAIN, G_LOG_LEVEL_CRITICAL, expected_substring);
  }

  static void AssertExpectedGlibMessages()
  {
    g_test_assert_expected_messages();
  }
};

TEST_F(PopplerCertificateInfoGetExpirationTimeTest_2403,
       NullCertificateInfoReturnsNullAndEmitsCritical_2403)
{
  ExpectGlibCritical("*assertion*failed*");

  GDateTime *result = poppler_certificate_info_get_expiration_time(nullptr);
  EXPECT_EQ(result, nullptr);

  AssertExpectedGlibMessages();
}

TEST_F(PopplerCertificateInfoGetExpirationTimeTest_2403, ExpiresNullReturnsNull_2403)
{
  PopplerCertificateInfo info{};
  // The API returns certificate_info->expires as-is; boundary case is expires == nullptr.
  info.expires = nullptr;

  GDateTime *result = poppler_certificate_info_get_expiration_time(&info);
  EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerCertificateInfoGetExpirationTimeTest_2403, ReturnsSamePointerForValidExpires_2403)
{
  PopplerCertificateInfo info{};

  GDateTime *dt = g_date_time_new_utc(2020, 1, 2, 3, 4, 5.0);
  ASSERT_NE(dt, nullptr);

  info.expires = dt;

  GDateTime *result = poppler_certificate_info_get_expiration_time(&info);
  EXPECT_EQ(result, dt);

  g_date_time_unref(dt);
}

TEST_F(PopplerCertificateInfoGetExpirationTimeTest_2403, ReturnedExpirationTimeIsUsable_2403)
{
  PopplerCertificateInfo info{};

  // Pick a known time and verify we can use the returned pointer as a GDateTime.
  GDateTime *dt = g_date_time_new_utc(1970, 1, 1, 0, 0, 0.0);
  ASSERT_NE(dt, nullptr);

  info.expires = dt;

  GDateTime *result = poppler_certificate_info_get_expiration_time(&info);
  ASSERT_NE(result, nullptr);

  // This should be 0 for the Unix epoch (UTC).
  gint64 unix_seconds = g_date_time_to_unix(result);
  EXPECT_EQ(unix_seconds, 0);

  g_date_time_unref(dt);
}