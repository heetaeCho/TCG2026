// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_http_error_1350.cpp

#include <gtest/gtest.h>

#include <cerrno>
#include <string>

// The function under test is `static` inside http.cpp, so we include the translation unit
// to make it visible in this test file (white-box for linkage only; tests remain black-box
// w.r.t. behavior and do not rely on internal state).
#include "TestProjects/exiv2/src/http.cpp"

namespace {

class HttpErrorTest_1350 : public ::testing::Test {
 protected:
  void SetUp() override {
    errno = 0;
  }
};

TEST_F(HttpErrorTest_1350, ReturnsMinusOneAndAppendsMessageWithNewline_1350) {
  std::string errors = "prefix\n";

  ::testing::internal::CaptureStderr();
  const int rc = error(errors, "simple message");
  const std::string stderr_out = ::testing::internal::GetCapturedStderr();

  EXPECT_EQ(-1, rc);

  // Observable effect: errors is appended with the provided `msg` string + '\n'.
  EXPECT_EQ(std::string("prefix\n") + "simple message\n", errors);

  // Observable external interaction: something is written to stderr.
  EXPECT_FALSE(stderr_out.empty());
  EXPECT_NE(std::string::npos, stderr_out.find("simple message"));
}

TEST_F(HttpErrorTest_1350, FormatsStderrButErrorsAppendUsesOriginalMsgString_1350) {
  std::string errors;

  // Use a format string to observe formatted output on stderr.
  const char* fmt = "x=%s y=%s z=%d";
  const char* x = "AAA";
  const char* y = "BBB";
  const int z = 123;

  errno = 0;
  ::testing::internal::CaptureStderr();
  const int rc = error(errors, fmt, x, y, z);
  const std::string stderr_out = ::testing::internal::GetCapturedStderr();

  EXPECT_EQ(-1, rc);

  // Observable: stderr contains the formatted content.
  EXPECT_NE(std::string::npos, stderr_out.find("x=AAA"));
  EXPECT_NE(std::string::npos, stderr_out.find("y=BBB"));
  EXPECT_NE(std::string::npos, stderr_out.find("z=123"));

  // Observable: errors gets the *msg string itself* + '\n' (not the formatted buffer).
  EXPECT_EQ(std::string(fmt) + "\n", errors);
}

TEST_F(HttpErrorTest_1350, NullOptionalArgsWithPlainMsgDoesNotCrashAndAppends_1350) {
  std::string errors;

  errno = 0;
  ::testing::internal::CaptureStderr();
  const int rc = error(errors, "no format specifiers", nullptr, nullptr, 0);
  const std::string stderr_out = ::testing::internal::GetCapturedStderr();

  EXPECT_EQ(-1, rc);
  EXPECT_EQ(std::string("no format specifiers\n"), errors);
  EXPECT_FALSE(stderr_out.empty());
  EXPECT_NE(std::string::npos, stderr_out.find("no format specifiers"));
}

TEST_F(HttpErrorTest_1350, WhenErrnoIsSetWritesToStderrAndStillAppends_1350) {
  std::string errors;

  errno = EINVAL;  // any non-zero errno should trigger the perror path.
  ::testing::internal::CaptureStderr();
  const int rc = error(errors, "perror-path message");
  const std::string stderr_out = ::testing::internal::GetCapturedStderr();

  EXPECT_EQ(-1, rc);
  EXPECT_EQ(std::string("perror-path message\n"), errors);

  // Locale-dependent strerror text can vary; just assert our message appears.
  EXPECT_FALSE(stderr_out.empty());
  EXPECT_NE(std::string::npos, stderr_out.find("perror-path message"));
}

TEST_F(HttpErrorTest_1350, VeryLongMsgIsAppendedAndDoesNotCrash_1350) {
  // Boundary-ish: large message string.
  const std::string long_msg(2000, 'A');  // far larger than the internal buffer used for stderr.
  std::string errors;

  errno = 0;
  ::testing::internal::CaptureStderr();
  const int rc = error(errors, long_msg.c_str());
  const std::string stderr_out = ::testing::internal::GetCapturedStderr();

  EXPECT_EQ(-1, rc);

  // Observable: errors stores the provided msg string (full length) + '\n'.
  EXPECT_EQ(long_msg + "\n", errors);

  // Observable: stderr output exists (may be truncated by internal buffer, but should not be empty).
  EXPECT_FALSE(stderr_out.empty());
}

}  // namespace