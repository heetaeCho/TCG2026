// File: terminate_number_test_272.cc
#include <gtest/gtest.h>
#include <cstring>

// Pull in the implementation so we can call the internal static function.
// Keep this include local to this test TU to avoid ODR issues.
#include "TestProjects/re2/re2/re2.cc"

using re2::re2_internal::TerminateNumber;

class TerminateNumberTest_272 : public ::testing::Test {
protected:
  // Small helper that zero-fills the buffer so we can detect writes/terminators.
  void Clear(char* buf, size_t n) {
    std::memset(buf, 0xCD, n); // poison with a non-zero pattern
  }
};

// --- Normal operation ---

TEST_F(TerminateNumberTest_272, TrimsLeadingSpacesWhenAccepted_272) {
  char buf[16]; Clear(buf, sizeof(buf));
  const char* in = "   123";
  size_t n = std::strlen(in);
  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/true);

  ASSERT_EQ(ret, buf);                // returns the output buffer on success
  EXPECT_STREQ(buf, "123");           // spaces trimmed
  EXPECT_EQ(n, 3u);                   // np updated to resulting length
  EXPECT_EQ(buf[3], '\0');            // null-terminated
}

TEST_F(TerminateNumberTest_272, PreservesNegativeSign_272) {
  char buf[16]; Clear(buf, sizeof(buf));
  const char* in = "-123";
  size_t n = std::strlen(in);
  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/false);

  ASSERT_EQ(ret, buf);
  EXPECT_STREQ(buf, "-123");
  EXPECT_EQ(n, 4u);
  EXPECT_EQ(buf[4], '\0');
}

TEST_F(TerminateNumberTest_272, CollapsesExtraLeadingZerosToAtMostTwo_272) {
  char buf[16]; Clear(buf, sizeof(buf));
  const char* in = "000123";
  size_t n = std::strlen(in);
  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/false);

  ASSERT_EQ(ret, buf);
  // Observable behavior: more than two leading zeros are reduced to two.
  EXPECT_STREQ(buf, "00123");
  EXPECT_EQ(n, 5u);
  EXPECT_EQ(buf[5], '\0');
}

TEST_F(TerminateNumberTest_272, NegativeWithLeadingZeros_272) {
  char buf[16]; Clear(buf, sizeof(buf));
  const char* in = "-000123";
  size_t n = std::strlen(in);
  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/false);

  ASSERT_EQ(ret, buf);
  EXPECT_STREQ(buf, "-00123");
  EXPECT_EQ(n, 6u);
  EXPECT_EQ(buf[6], '\0');
}

TEST_F(TerminateNumberTest_272, ExactlyTwoLeadingZerosRemain_272) {
  char buf[8]; Clear(buf, sizeof(buf));
  const char* in = "00";
  size_t n = std::strlen(in);
  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/false);

  ASSERT_EQ(ret, buf);
  EXPECT_STREQ(buf, "00");
  EXPECT_EQ(n, 2u);
  EXPECT_EQ(buf[2], '\0');
}

// --- Boundary conditions ---

TEST_F(TerminateNumberTest_272, EmptyInputReturnsEmptyAndKeepsNpZero_272) {
  char buf[8]; Clear(buf, sizeof(buf));
  const char* in = "";
  size_t n = std::strlen(in); // 0
  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/false);

  // On n == 0 the function returns the empty-string literal.
  EXPECT_NE(ret, buf);
  EXPECT_STREQ(ret, "");
  EXPECT_EQ(n, 0u); // np remains 0
}

TEST_F(TerminateNumberTest_272, AllSpacesAcceptedBecomesEmpty_272) {
  char buf[8]; Clear(buf, sizeof(buf));
  const char* in = "   ";
  size_t n = std::strlen(in);
  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/true);

  ASSERT_EQ(ret, buf);
  EXPECT_STREQ(buf, "");  // trimmed down to empty; still returns buf
  EXPECT_EQ(n, 0u);
  EXPECT_EQ(buf[0], '\0');
}

TEST_F(TerminateNumberTest_272, ExactFitBufferSucceeds_272) {
  const char* in = "1234";
  size_t n = std::strlen(in);
  // Need nbuf == n + 1 for the terminator.
  char buf[5];  // exactly fits "1234\0"
  Clear(buf, sizeof(buf));

  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/false);

  ASSERT_EQ(ret, buf);
  EXPECT_STREQ(buf, "1234");
  EXPECT_EQ(n, 4u);
  EXPECT_EQ(buf[4], '\0');
}

// --- Error/exceptional observable cases ---

TEST_F(TerminateNumberTest_272, RejectsLeadingSpacesWhenNotAccepted_272) {
  char buf[16]; Clear(buf, sizeof(buf));
  const char* in = " 42";
  size_t n = std::strlen(in);
  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/false);

  // Returns empty-string literal without modifying np.
  EXPECT_NE(ret, buf);
  EXPECT_STREQ(ret, "");
  EXPECT_EQ(n, std::strlen(in)); // unchanged
}

TEST_F(TerminateNumberTest_272, FailsWhenBufferTooSmall_272) {
  const char* in = "12345";
  size_t original_n = std::strlen(in); // 5
  size_t n = original_n;

  char buf[4]; // nbuf=4; need at least n+1=6 -> should fail
  Clear(buf, sizeof(buf));
  const char* ret = TerminateNumber(buf, sizeof(buf), in, &n, /*accept_spaces=*/false);

  EXPECT_NE(ret, buf);         // not returning our buffer
  EXPECT_STREQ(ret, "");       // signals failure
  EXPECT_EQ(n, original_n);    // np unchanged on failure
  // Buffer content is unspecified on failure; we don't assert on buf contents.
}
