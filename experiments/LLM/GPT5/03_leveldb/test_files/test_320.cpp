// File: util/crc32c_value_test_320.cc
#include "gtest/gtest.h"
#include "util/crc32c.h"

#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

namespace {

using leveldb::crc32c::Value;

// ---- Normal operation ----

TEST(CRC32CValueTest_320, EmptyInputReturnsZero_320) {
  // Empty buffer via empty string
  const std::string s;
  EXPECT_EQ(0u, Value(s.data(), s.size()));

  // Empty buffer via nullptr + length 0 (should be safe and also return 0)
  const char* p = nullptr;
  EXPECT_EQ(0u, Value(p, 0));
}

TEST(CRC32CValueTest_320, KnownVector_123456789_320) {
  // Standard CRC32C test vector: "123456789" -> 0xE3069283
  const char* msg = "123456789";
  const uint32_t expected = 0xE3069283u;
  EXPECT_EQ(expected, Value(msg, std::strlen(msg)));
}

TEST(CRC32CValueTest_320, DeterministicForSameInput_320) {
  const std::string s = "the quick brown fox jumps over the lazy dog";
  const uint32_t c1 = Value(s.data(), s.size());
  const uint32_t c2 = Value(s.data(), s.size());
  EXPECT_EQ(c1, c2);
}

// ---- Boundary & edge conditions ----

TEST(CRC32CValueTest_320, HandlesEmbeddedNullBytes_320) {
  // Ensure length is honored (not C-string semantics).
  const char with_null[] = {'a', 'b', '\0', 'c'};
  const uint32_t crc_with_null = Value(with_null, sizeof(with_null));

  const char ab_only[] = {'a', 'b'};
  const uint32_t crc_ab_only = Value(ab_only, sizeof(ab_only));

  // With embedded NUL and longer length, CRC should differ from just "ab".
  EXPECT_NE(crc_with_null, crc_ab_only);

  // Also confirm that slicing to first two bytes matches "ab".
  const uint32_t crc_prefix2 = Value(with_null, 2);
  EXPECT_EQ(crc_prefix2, crc_ab_only);
}

TEST(CRC32CValueTest_320, OrderMatters_320) {
  const std::string a = "ab";
  const std::string b = "ba";
  EXPECT_NE(Value(a.data(), a.size()), Value(b.data(), b.size()));
}

// ---- Larger input / robustness ----

TEST(CRC32CValueTest_320, LargeBufferConsistency_320) {
  // 1MB buffer of 'x'
  const size_t N = 1 << 20;
  std::vector<char> buf(N, 'x');

  const uint32_t c1 = Value(buf.data(), buf.size());
  const uint32_t c2 = Value(buf.data(), buf.size());

  // Non-zero is not guaranteed by interface, but typical for non-empty inputs.
  // We assert determinism; non-zero is a weak additional signal. If your
  // environment requires strict interface-only behavior, you may remove the
  // non-zero check.
  EXPECT_EQ(c1, c2);
  EXPECT_NE(0u, c1);
}

}  // namespace
