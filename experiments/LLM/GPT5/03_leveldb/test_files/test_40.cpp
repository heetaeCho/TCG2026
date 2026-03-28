// File: zstd_get_uncompressed_length_test.cc

#include <gtest/gtest.h>
#include <cstddef>

// We need the header under test. To safely "mock" the external collaborator
// ZSTD_getFrameContentSize without re-implementing internal logic, we
// redirect the symbol inside the header to a test stub when HAVE_ZSTD=1.
#if HAVE_ZSTD
// Redirect the function name used in the header to our test stub.
#define ZSTD_getFrameContentSize test_ZSTD_getFrameContentSize
#endif

#include "port/port_stdcxx.h"  // contains leveldb::port::Zstd_GetUncompressedLength

using leveldb::port::Zstd_GetUncompressedLength;

class ZstdGetUncompressedLengthTest_40 : public ::testing::Test {};

// -----------------------------
// Tests when HAVE_ZSTD is OFF
// -----------------------------
#if !HAVE_ZSTD

TEST_F(ZstdGetUncompressedLengthTest_40, ReturnsFalseAndDoesNotWriteResult_40) {
  const char kInput[] = "anything";
  size_t result = 12345;  // sentinel
  const size_t before = result;

  const bool ok = Zstd_GetUncompressedLength(kInput, sizeof(kInput), &result);

  EXPECT_FALSE(ok);
  // Interface-observable effect: result must remain untouched on failure.
  EXPECT_EQ(result, before);
}

TEST_F(ZstdGetUncompressedLengthTest_40, HandlesNullInputPointerGracefully_40) {
  // Even though input is unused in this configuration, ensure call does not crash
  // and obeys the contract (returns false, does not write).
  size_t result = 999;
  const size_t before = result;

  const bool ok = Zstd_GetUncompressedLength(nullptr, 0u, &result);

  EXPECT_FALSE(ok);
  EXPECT_EQ(result, before);
}

#else  // HAVE_ZSTD

// ----------------------------------------
// Test stub for external collaborator
// ----------------------------------------
namespace {
// Capture the last arguments to verify parameter forwarding (external interaction).
static const void* g_last_input_ptr = nullptr;
static size_t g_last_length = 0;
static size_t g_next_size_to_return = 0;  // Controls stub behavior

extern "C" size_t test_ZSTD_getFrameContentSize(const void* src, size_t srcSize) {
  g_last_input_ptr = src;
  g_last_length = srcSize;
  return g_next_size_to_return;
}
}  // namespace

TEST_F(ZstdGetUncompressedLengthTest_40, ForwardsParametersToZstd_40) {
  const char kData[] = "abcdef";
  size_t out = 0;

  g_next_size_to_return = 1;  // ensure "success" path so the call is exercised
  const bool ok = Zstd_GetUncompressedLength(kData, sizeof(kData), &out);

  EXPECT_TRUE(ok);
  // Verify external interaction: parameters are forwarded as-is.
  EXPECT_EQ(g_last_input_ptr, static_cast<const void*>(kData));
  EXPECT_EQ(g_last_length, sizeof(kData));
}

TEST_F(ZstdGetUncompressedLengthTest_40, ReturnsFalseWhenZstdReportsUnknownSize_40) {
  const char kFrame[] = "frame";
  size_t result = 777;    // sentinel to check non-write
  const size_t before = result;

  g_next_size_to_return = 0;  // Header treats 0 as "unknown"/failure
  const bool ok = Zstd_GetUncompressedLength(kFrame, sizeof(kFrame), &result);

  EXPECT_FALSE(ok);
  // On failure path, result must remain unchanged (observable behavior).
  EXPECT_EQ(result, before);
}

TEST_F(ZstdGetUncompressedLengthTest_40, WritesResultAndReturnsTrueOnValidSize_40) {
  const char kFrame[] = "compressed data bytes";
  size_t result = 0;

  g_next_size_to_return = 123456;  // arbitrary "valid" size
  const bool ok = Zstd_GetUncompressedLength(kFrame, sizeof(kFrame), &result);

  EXPECT_TRUE(ok);
  EXPECT_EQ(result, static_cast<size_t>(123456));
}

TEST_F(ZstdGetUncompressedLengthTest_40, HandlesVeryLargeValidSize_40) {
  const char kFrame[] = "x";
  size_t result = 0;

  g_next_size_to_return = static_cast<size_t>(~static_cast<size_t>(0));  // SIZE_MAX
  const bool ok = Zstd_GetUncompressedLength(kFrame, sizeof(kFrame), &result);

  EXPECT_TRUE(ok);
  EXPECT_EQ(result, static_cast<size_t>(~static_cast<size_t>(0)));
}

#endif  // HAVE_ZSTD
