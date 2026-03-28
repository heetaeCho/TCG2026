// File: port_snappy_uncompressed_length_test_37.cc

#include <gtest/gtest.h>
#include <cstddef>

// We write tests that adapt to the build configuration.
// If HAVE_SNAPPY is defined, we provide a small test-only fake for snappy::GetUncompressedLength
// (external collaborator) to verify forwarding and parameter passthrough.
// If HAVE_SNAPPY is not defined, we only verify the documented observable behavior (returns false).

#if HAVE_SNAPPY

namespace {
// ---- Test-only fake & probes for snappy::GetUncompressedLength ----
// This is an external collaborator; providing a fake is allowed by the constraints.
namespace snappy {
  // Probes to assert that the wrapper forwards parameters as-is.
  static const char* g_last_input = nullptr;
  static size_t g_last_length = static_cast<size_t>(-1);
  static size_t* g_last_result_ptr = reinterpret_cast<size_t*>(0x1);

  // Controls for the fake's behavior.
  static bool g_next_return = true;
  static bool g_write_result = false;
  static size_t g_value_to_write = 0;

  inline void ResetProbes() {
    g_last_input = nullptr;
    g_last_length = static_cast<size_t>(-1);
    g_last_result_ptr = reinterpret_cast<size_t*>(0x1);
    g_next_return = true;
    g_write_result = false;
    g_value_to_write = 0;
  }

  // The fake function that the wrapper under test will call.
  bool GetUncompressedLength(const char* input, size_t length, size_t* result) {
    g_last_input = input;
    g_last_length = length;
    g_last_result_ptr = result;
    if (g_write_result && result) {
      *result = g_value_to_write;
    }
    return g_next_return;
  }
}  // namespace snappy
}  // anonymous namespace

// Include header after the fake is available so the inline wrapper can call it.
#include "port/port_stdcxx.h"

using leveldb::port::Snappy_GetUncompressedLength;

TEST(PortSnappyTest_37, ForwardsCallAndReturnsTrue_37) {
  snappy::ResetProbes();
  const char payload[] = "abc";
  size_t out = 0;

  snappy::g_next_return = true;
  snappy::g_write_result = true;
  snappy::g_value_to_write = 123u;

  const bool ok = Snappy_GetUncompressedLength(payload, sizeof(payload), &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(123u, out);
  EXPECT_EQ(static_cast<const char*>(payload), snappy::g_last_input);
  EXPECT_EQ(sizeof(payload), snappy::g_last_length);
  EXPECT_EQ(&out, snappy::g_last_result_ptr);
}

TEST(PortSnappyTest_37, PropagatesFalseReturn_37) {
  snappy::ResetProbes();
  const char payload[] = "xyz";
  size_t out = 777u;  // sentinel

  snappy::g_next_return = false;    // make collaborator fail
  snappy::g_write_result = false;   // collaborator does not write

  const bool ok = Snappy_GetUncompressedLength(payload, sizeof(payload), &out);

  EXPECT_FALSE(ok);
  // When collaborator returns false and doesn't write, value should remain unchanged.
  EXPECT_EQ(777u, out);
  EXPECT_EQ(static_cast<const char*>(payload), snappy::g_last_input);
  EXPECT_EQ(sizeof(payload), snappy::g_last_length);
  EXPECT_EQ(&out, snappy::g_last_result_ptr);
}

TEST(PortSnappyTest_37, PassesThroughNullResultPointer_37) {
  snappy::ResetProbes();
  const char payload[] = "data";

  snappy::g_next_return = false;   // arbitrary
  snappy::g_write_result = true;   // even if set, fake guards against nullptr

  const bool ok = Snappy_GetUncompressedLength(payload, sizeof(payload), /*result=*/nullptr);

  EXPECT_FALSE(ok);
  EXPECT_EQ(static_cast<const char*>(payload), snappy::g_last_input);
  EXPECT_EQ(sizeof(payload), snappy::g_last_length);
  EXPECT_EQ(nullptr, snappy::g_last_result_ptr);
}

TEST(PortSnappyTest_37, ZeroLengthIsForwarded_37) {
  snappy::ResetProbes();
  const char* payload = nullptr;  // pointer value itself should be forwarded as-is

  snappy::g_next_return = true;

  size_t out = 0;
  const bool ok = Snappy_GetUncompressedLength(payload, /*length=*/0, &out);

  EXPECT_TRUE(ok);
  EXPECT_EQ(payload, snappy::g_last_input);
  EXPECT_EQ(0u, snappy::g_last_length);
  EXPECT_EQ(&out, snappy::g_last_result_ptr);
}

#else  // !HAVE_SNAPPY

#include "port/port_stdcxx.h"
using leveldb::port::Snappy_GetUncompressedLength;

TEST(PortSnappyTest_37, ReturnsFalseWhenSnappyUnavailable_37) {
  const char payload[] = "abc";
  size_t out = 999u;  // sentinel
  const bool ok = Snappy_GetUncompressedLength(payload, sizeof(payload), &out);
  EXPECT_FALSE(ok);
  // Observable behavior: result should remain unchanged (function ignores args).
  EXPECT_EQ(999u, out);
}

TEST(PortSnappyTest_37, AllowsNullResultPointerWhenUnavailable_37) {
  const char payload[] = "any";
  // Should not crash; should simply return false.
  const bool ok = Snappy_GetUncompressedLength(payload, sizeof(payload), /*result=*/nullptr);
  EXPECT_FALSE(ok);
}

TEST(PortSnappyTest_37, ZeroLengthWhenUnavailable_37) {
  // Should still return false regardless of inputs.
  const bool ok = Snappy_GetUncompressedLength(/*input=*/nullptr, /*length=*/0, /*result=*/nullptr);
  EXPECT_FALSE(ok);
}

#endif  // HAVE_SNAPPY
