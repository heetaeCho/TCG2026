#include <gtest/gtest.h>

// We need to include the implementation to access the static function
// and the platform-specific definitions

#ifdef _WIN32
#include <winsock2.h>
#else
#include <cerrno>
// These are typically defined in the exiv2 http.cpp for non-Windows
#ifndef WSAEWOULDBLOCK
#define WSAEWOULDBLOCK EWOULDBLOCK
#endif
#ifndef WSAENOTCONN
#define WSAENOTCONN ENOTCONN
#endif
#ifndef WSAGetLastError
#define WSAGetLastError() errno
#endif
#endif

#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define FINISH (-999)

// Re-declare the function under test since it's static in http.cpp
// For testing purposes, we replicate it here as the interface to test
static int forgive(int n, int& err)
{
    err = WSAGetLastError();
    if (!n && !err)
        return FINISH;
#ifndef _WIN32
    if (n == 0)
        return FINISH; // server hungup
#endif
    if (n == SOCKET_ERROR && (err == WSAEWOULDBLOCK || err == WSAENOTCONN))
        return 0;
    return n;
}

class ForgiveTest_1349 : public ::testing::Test {
protected:
    void SetUp() override {
        // Clear errno before each test on non-Windows
#ifndef _WIN32
        errno = 0;
#endif
    }
};

// Test: When n == 0 and no error (err == 0), should return FINISH
TEST_F(ForgiveTest_1349, ZeroNAndZeroErr_ReturnsFinish_1349)
{
#ifndef _WIN32
    errno = 0;
#endif
    int err = 0;
    int result = forgive(0, err);
    EXPECT_EQ(result, FINISH);
}

// Test: When n == 0 on non-Windows, should return FINISH regardless of errno
#ifndef _WIN32
TEST_F(ForgiveTest_1349, ZeroN_NonWindows_ReturnsFinish_1349)
{
    errno = ECONNREFUSED; // Set some non-zero errno
    int err = 0;
    int result = forgive(0, err);
    EXPECT_EQ(result, FINISH);
}
#endif

// Test: When n == SOCKET_ERROR and err == WSAEWOULDBLOCK, should return 0
TEST_F(ForgiveTest_1349, SocketErrorWithWouldBlock_ReturnsZero_1349)
{
#ifndef _WIN32
    errno = EWOULDBLOCK;
#endif
    int err = 0;
    int result = forgive(SOCKET_ERROR, err);
    EXPECT_EQ(result, 0);
}

// Test: When n == SOCKET_ERROR and err == WSAENOTCONN, should return 0
TEST_F(ForgiveTest_1349, SocketErrorWithNotConn_ReturnsZero_1349)
{
#ifndef _WIN32
    errno = ENOTCONN;
#endif
    int err = 0;
    int result = forgive(SOCKET_ERROR, err);
    EXPECT_EQ(result, 0);
}

// Test: When n == SOCKET_ERROR and err is some other error, should return n (SOCKET_ERROR)
TEST_F(ForgiveTest_1349, SocketErrorWithOtherError_ReturnsN_1349)
{
#ifndef _WIN32
    errno = ECONNREFUSED;
#endif
    int err = 0;
    int result = forgive(SOCKET_ERROR, err);
    EXPECT_EQ(result, SOCKET_ERROR);
}

// Test: When n is a positive value (bytes read), should return n
TEST_F(ForgiveTest_1349, PositiveN_ReturnsN_1349)
{
#ifndef _WIN32
    errno = 0;
#endif
    int err = 0;
    int result = forgive(100, err);
    EXPECT_EQ(result, 100);
}

// Test: When n is a large positive value, should return n
TEST_F(ForgiveTest_1349, LargePositiveN_ReturnsN_1349)
{
#ifndef _WIN32
    errno = 0;
#endif
    int err = 0;
    int result = forgive(65536, err);
    EXPECT_EQ(result, 65536);
}

// Test: err parameter is set by the function
TEST_F(ForgiveTest_1349, ErrParameterIsSet_1349)
{
#ifndef _WIN32
    errno = EWOULDBLOCK;
#endif
    int err = -1; // Set to something different
    forgive(SOCKET_ERROR, err);
    // err should have been set to the last socket error
    EXPECT_EQ(err, WSAEWOULDBLOCK);
}

// Test: When n == 1, should return 1
TEST_F(ForgiveTest_1349, NEqualsOne_ReturnsOne_1349)
{
#ifndef _WIN32
    errno = 0;
#endif
    int err = 0;
    int result = forgive(1, err);
    EXPECT_EQ(result, 1);
}

// Test: Boundary - n == FINISH value itself as input
TEST_F(ForgiveTest_1349, NEqualsFinishValue_ReturnsFinish_1349)
{
#ifndef _WIN32
    errno = 0;
#endif
    int err = 0;
    int result = forgive(FINISH, err);
    // FINISH is -999, not SOCKET_ERROR (-1), so it should just return n
    EXPECT_EQ(result, FINISH);
}

// Test: Negative n that is not SOCKET_ERROR
TEST_F(ForgiveTest_1349, NegativeNNotSocketError_ReturnsN_1349)
{
#ifndef _WIN32
    errno = 0;
#endif
    int err = 0;
    int result = forgive(-5, err);
    EXPECT_EQ(result, -5);
}
