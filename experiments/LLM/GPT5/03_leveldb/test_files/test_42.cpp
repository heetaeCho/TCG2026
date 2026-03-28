// File: port_stdcxx_get_heap_profile_test_42.cc

#include "port/port_stdcxx.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::Times;

namespace leveldb {
namespace port {

// A mock to verify whether a passed-in callback would be invoked.
class MockProfileFunc_42 {
 public:
  MOCK_METHOD(void, Call, (void* arg, const char* data, int len));
};

// Global forwarding hook so we can pass a plain C-style function pointer
// to GetHeapProfile and still route to our gMock-owned method.
static MockProfileFunc_42* g_mock_profile_42 = nullptr;

static void ForwardingProfileFunc_42(void* arg, const char* data, int len) {
  if (g_mock_profile_42) {
    g_mock_profile_42->Call(arg, data, len);
  }
}

class PortStdcxxHeapProfileTest_42 : public ::testing::Test {
 protected:
  void SetUp() override { g_mock_profile_42 = nullptr; }
  void TearDown() override { g_mock_profile_42 = nullptr; }
};

// Normal operation: verify the function returns a boolean and specifically false.
TEST_F(PortStdcxxHeapProfileTest_42, ReturnsFalseWhenCalled_42) {
  const bool ok = GetHeapProfile(&ForwardingProfileFunc_42, nullptr);
  EXPECT_FALSE(ok);
}

// External interaction verification: ensure the provided callback is NOT invoked.
TEST_F(PortStdcxxHeapProfileTest_42, DoesNotInvokeCallback_42) {
  MockProfileFunc_42 mock;
  g_mock_profile_42 = &mock;

  EXPECT_CALL(mock, Call).Times(0);

  const bool ok = GetHeapProfile(&ForwardingProfileFunc_42, reinterpret_cast<void*>(0x1234));
  EXPECT_FALSE(ok);
}

// Boundary condition: passing a nullptr as the function pointer should be safe and return false.
TEST_F(PortStdcxxHeapProfileTest_42, AcceptsNullCallbackPointer_42) {
  const bool ok = GetHeapProfile(nullptr, nullptr);
  EXPECT_FALSE(ok);
}

}  // namespace port
}  // namespace leveldb
