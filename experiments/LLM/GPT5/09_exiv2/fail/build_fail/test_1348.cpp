// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_http_cpp_1348.cpp
//
// Unit tests for partial implementation in:
//   ./TestProjects/exiv2/src/http.cpp
//
// Constraints note:
// - Treat implementation as a black box.
// - This file only exposes preprocessor constants and a TU-local (static) function.
// - To test observable behavior, we include the .cpp to make the TU-local symbol
//   visible within this test translation unit (no private-state access).

#include <gtest/gtest.h>

#include <cerrno>

// Include the implementation file to access TU-local (static) entities for testing.
// This is a common technique for testing internal-linkage helpers when no public
// interface exists.
#include "http.cpp"

namespace {

class HttpCppTest_1348 : public ::testing::Test {
 protected:
  void SetUp() override {
    saved_errno_ = errno;
  }

  void TearDown() override {
    errno = saved_errno_;
  }

 private:
  int saved_errno_{0};
};

}  // namespace

TEST_F(HttpCppTest_1348, WSAGetLastErrorReturnsCurrentErrno_1348) {
  errno = 0;
  EXPECT_EQ(0, WSAGetLastError());

  errno = EINVAL;
  EXPECT_EQ(EINVAL, WSAGetLastError());

  errno = EACCES;
  EXPECT_EQ(EACCES, WSAGetLastError());
}

TEST_F(HttpCppTest_1348, WSAGetLastErrorReflectsErrnoChangesAcrossCalls_1348) {
  errno = ENOENT;
  const int first = WSAGetLastError();
  EXPECT_EQ(ENOENT, first);

  errno = EPERM;
  const int second = WSAGetLastError();
  EXPECT_EQ(EPERM, second);

  // Ensure it isn't caching the previous value (observable behavior via return value).
  EXPECT_NE(first, second);
}

TEST_F(HttpCppTest_1348, MacroConstantsHaveExpectedValues_1348) {
  // These are observable compile-time constants used by the implementation.
  EXPECT_EQ(-1, INVALID_SOCKET);
  EXPECT_EQ(-1, SOCKET_ERROR);
  EXPECT_EQ(-999, FINISH);
}