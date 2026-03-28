// File: poppler-set-nss-dir-test-2409.cc

#include <gtest/gtest.h>

#include <string>

#include "poppler/NSSCryptoSignBackend.h"

// The function under test is implemented in glib/poppler-form-field.cc.
// In many Poppler GLib builds this is exposed as a C API symbol; forward-declare
// to avoid relying on a specific header name here.
extern "C" void poppler_set_nss_dir(const char *path);

class PopplerSetNSSDirTest_2409 : public ::testing::Test {};

// Normal operation: set a directory and observe it via NSSSignatureConfiguration.
TEST_F(PopplerSetNSSDirTest_2409, SetsDirectory_2409) {
#if ENABLE_NSS3
  const char *dir = "/tmp/nss";
  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir(dir));

  const std::string got = NSSSignatureConfiguration::getNSSDir();
  EXPECT_EQ(got, std::string(dir));
#else
  // In non-NSS builds, this is a no-op; just ensure it is callable.
  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir("/tmp/nss"));
#endif
}

// Boundary: empty string should be accepted (if NSS is enabled) and be observable.
TEST_F(PopplerSetNSSDirTest_2409, AcceptsEmptyString_2409) {
#if ENABLE_NSS3
  const char *dir = "";
  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir(dir));

  const std::string got = NSSSignatureConfiguration::getNSSDir();
  EXPECT_EQ(got, std::string(dir));
#else
  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir(""));
#endif
}

// Boundary: a long-ish path should round-trip.
TEST_F(PopplerSetNSSDirTest_2409, AcceptsLongPath_2409) {
#if ENABLE_NSS3
  const std::string long_dir =
      "/this/is/a/very/long/path/for/testing/nss/dir/configuration/"
      "with/many/components/and_characters_0123456789";
  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir(long_dir.c_str()));

  const std::string got = NSSSignatureConfiguration::getNSSDir();
  EXPECT_EQ(got, long_dir);
#else
  const std::string long_dir =
      "/this/is/a/very/long/path/for/testing/nss/dir/configuration/"
      "with/many/components/and_characters_0123456789";
  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir(long_dir.c_str()));
#endif
}

// Normal operation: multiple calls should update the configured dir (if NSS enabled).
TEST_F(PopplerSetNSSDirTest_2409, LastCallWins_2409) {
#if ENABLE_NSS3
  const char *dir1 = "/tmp/nss1";
  const char *dir2 = "/tmp/nss2";

  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir(dir1));
  EXPECT_EQ(NSSSignatureConfiguration::getNSSDir(), std::string(dir1));

  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir(dir2));
  EXPECT_EQ(NSSSignatureConfiguration::getNSSDir(), std::string(dir2));
#else
  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir("/tmp/nss1"));
  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir("/tmp/nss2"));
#endif
}

// Exceptional / error case (observable): nullptr must not crash in non-NSS builds
// (path is unused there). In NSS builds, passing nullptr would likely be invalid
// for GooString(path), so we do not exercise it.
TEST_F(PopplerSetNSSDirTest_2409, NullptrDoesNotCrashWhenNSSDisabled_2409) {
#if ENABLE_NSS3
  GTEST_SKIP() << "nullptr input is not a safe/valid observable case when ENABLE_NSS3 is on.";
#else
  ASSERT_NO_FATAL_FAILURE(poppler_set_nss_dir(nullptr));
#endif
}