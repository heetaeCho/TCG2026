// File: util/coding_putfixed64_test.cc

#include "gtest/gtest.h"
#include <string>
#include <climits>

#include "util/coding.h"   // for DecodeFixed64 (public API used for verification)
#include "util/coding.cc"  // under test: PutFixed64

namespace leveldb {
namespace {

// Helper to decode a uint64_t from a std::string at a byte offset using the public API.
static uint64_t DecodeAt(const std::string& s, size_t offset) {
  // Precondition checks purely for test robustness (observable contract checks are below).
  EXPECT_LE(offset + sizeof(uint64_t), s.size());
  return DecodeFixed64(s.data() + offset);
}

// Normal operation: appends 8 bytes and round-trips a value.
TEST(PutFixed64Test_439, AppendsEightBytesAndEncodesRoundTrip_439) {
  std::string dst;
  const uint64_t value = 0x0102030405060708ULL;

  PutFixed64(&dst, value);

  EXPECT_EQ(dst.size(), sizeof(uint64_t));
  EXPECT_EQ(DecodeAt(dst, 0), value);
}

// Boundary condition: preserves existing prefix data while appending.
TEST(PutFixed64Test_439, PreservesExistingDataPrefix_439) {
  std::string dst = "abcd";  // 4-byte prefix
  const std::string prefix = dst;
  const uint64_t value = 0xA1A2A3A4A5A6A7A8ULL;

  PutFixed64(&dst, value);

  ASSERT_EQ(dst.substr(0, prefix.size()), prefix);                 // prefix unchanged
  ASSERT_EQ(dst.size(), prefix.size() + sizeof(uint64_t));         // grew by 8
  EXPECT_EQ(DecodeAt(dst, prefix.size()), value);                  // value at the end
}

// Normal operation: supports multiple appends; order is preserved.
TEST(PutFixed64Test_439, MultipleAppendsConcatenateInOrder_439) {
  std::string dst;
  const uint64_t v1 = 0x0000000000000000ULL;
  const uint64_t v2 = 0xFFFFFFFFFFFFFFFFULL;

  PutFixed64(&dst, v1);
  PutFixed64(&dst, v2);

  ASSERT_EQ(dst.size(), 2 * sizeof(uint64_t));
  EXPECT_EQ(DecodeAt(dst, 0), v1);
  EXPECT_EQ(DecodeAt(dst, sizeof(uint64_t)), v2);
}

// Boundary values: zero and max should round-trip correctly.
TEST(PutFixed64Test_439, BoundaryValuesZeroAndMax_439) {
  std::string dst;

  const uint64_t zero = 0ULL;
  const uint64_t maxv = std::numeric_limits<uint64_t>::max();

  PutFixed64(&dst, zero);
  PutFixed64(&dst, maxv);

  ASSERT_EQ(dst.size(), 2 * sizeof(uint64_t));
  EXPECT_EQ(DecodeAt(dst, 0), zero);
  EXPECT_EQ(DecodeAt(dst, sizeof(uint64_t)), maxv);
}

// Larger buffer: appending to a large string still grows by exactly 8 bytes
// and places the encoded value at the end.
TEST(PutFixed64Test_439, AppendsToLargeString_439) {
  std::string dst(100000, 'x');  // large pre-filled buffer
  const size_t old_size = dst.size();
  const uint64_t value = 0x1122334455667788ULL;

  PutFixed64(&dst, value);

  ASSERT_EQ(dst.size(), old_size + sizeof(uint64_t));
  EXPECT_EQ(DecodeAt(dst, old_size), value);
}

}  // namespace
}  // namespace leveldb
