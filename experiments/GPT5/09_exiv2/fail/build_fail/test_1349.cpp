// File: test_http_forgive_1349.cpp
//
// Unit tests for static forgive() in ./TestProjects/exiv2/src/http.cpp
// NOTE: Because forgive() is a TU-local static function, these tests include the .cpp
//       to access it as a black box. We only test observable behavior via inputs/outputs.

#include <gtest/gtest.h>

// ---- Fake WSAGetLastError + minimal socket constants (so we can control err) ----
namespace {
int g_fakeLastError = 0;
int g_wsaGetLastErrorCalls = 0;

int FakeWSAGetLastError() {
  ++g_wsaGetLastErrorCalls;
  return g_fakeLastError;
}

void ResetFake(int lastError) {
  g_fakeLastError = lastError;
  g_wsaGetLastErrorCalls = 0;
}
}  // namespace

// If the platform headers didn't define these, provide minimal values for testing.
// (We don't rely on the numeric values, just equality comparisons.)
#ifndef WSAEWOULDBLOCK
#define WSAEWOULDBLOCK 10035
#endif
#ifndef WSAENOTCONN
#define WSAENOTCONN 10057
#endif

// Redirect WSAGetLastError used by http.cpp to our fake.
#define WSAGetLastError FakeWSAGetLastError

// Include the implementation to access the TU-local static forgive().
// Adjust include path if your test target's include dirs differ.
#include "TestProjects/exiv2/src/http.cpp"

// ---- Tests ----

TEST(HttpForgiveTest_1349, SetsErrFromWSAGetLastError_1349) {
  ResetFake(/*lastError=*/1234);

  int err = -1;
  const int ret = forgive(/*n=*/7, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, 1234);
  EXPECT_EQ(ret, 7);
}

TEST(HttpForgiveTest_1349, ReturnsZeroWhenSocketErrorAndWouldBlock_1349) {
  ResetFake(/*lastError=*/WSAEWOULDBLOCK);

  int err = -1;
  const int ret = forgive(/*n=*/SOCKET_ERROR, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, WSAEWOULDBLOCK);
  EXPECT_EQ(ret, 0);
}

TEST(HttpForgiveTest_1349, ReturnsZeroWhenSocketErrorAndNotConnected_1349) {
  ResetFake(/*lastError=*/WSAENOTCONN);

  int err = -1;
  const int ret = forgive(/*n=*/SOCKET_ERROR, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, WSAENOTCONN);
  EXPECT_EQ(ret, 0);
}

TEST(HttpForgiveTest_1349, ReturnsSocketErrorWhenSocketErrorAndOtherError_1349) {
  ResetFake(/*lastError=*/9999);  // not WSAEWOULDBLOCK / WSAENOTCONN

  int err = 0;
  const int ret = forgive(/*n=*/SOCKET_ERROR, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, 9999);
  EXPECT_EQ(ret, SOCKET_ERROR);
}

TEST(HttpForgiveTest_1349, ReturnsNForPositiveNRegardlessOfErr_1349) {
  ResetFake(/*lastError=*/5678);

  int err = 0;
  const int ret = forgive(/*n=*/42, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, 5678);
  EXPECT_EQ(ret, 42);
}

TEST(HttpForgiveTest_1349, Boundary_ReturnsNForNegativeNonSocketErrorN_1349) {
  ResetFake(/*lastError=*/111);

  int err = 0;
  const int ret = forgive(/*n=*/-123, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, 111);
  EXPECT_EQ(ret, -123);
}

#ifdef _WIN32

TEST(HttpForgiveTest_1349, Win_ReturnsFinishWhenNZeroAndErrZero_1349) {
  ResetFake(/*lastError=*/0);

  int err = -1;
  const int ret = forgive(/*n=*/0, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, 0);
  EXPECT_EQ(ret, FINISH);
}

TEST(HttpForgiveTest_1349, Win_ReturnsZeroWhenNZeroButErrNonZero_1349) {
  // On Windows path, FINISH is only returned for (n==0 && err==0).
  ResetFake(/*lastError=*/77);

  int err = -1;
  const int ret = forgive(/*n=*/0, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, 77);
  EXPECT_EQ(ret, 0);
}

#else  // !_WIN32

TEST(HttpForgiveTest_1349, NonWin_ReturnsFinishWhenNZeroAndErrZero_1349) {
  ResetFake(/*lastError=*/0);

  int err = -1;
  const int ret = forgive(/*n=*/0, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, 0);
  EXPECT_EQ(ret, FINISH);
}

TEST(HttpForgiveTest_1349, NonWin_ReturnsFinishWhenNZeroEvenIfErrNonZero_1349) {
  // Non-Windows path treats n==0 as "server hungup" and returns FINISH.
  ResetFake(/*lastError=*/77);

  int err = -1;
  const int ret = forgive(/*n=*/0, err);

  EXPECT_EQ(g_wsaGetLastErrorCalls, 1);
  EXPECT_EQ(err, 77);
  EXPECT_EQ(ret, FINISH);
}

#endif