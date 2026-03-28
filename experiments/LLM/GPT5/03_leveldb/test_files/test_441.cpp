// File: util/coding_putvarint32_test.cc

#include <gtest/gtest.h>
#include <string>
#include "util/coding.h"
#include "util/slice.h"

using leveldb::PutVarint32;
using leveldb::GetVarint32;
using leveldb::Slice;
using leveldb::VarintLength;

class PutVarint32Test_441 : public ::testing::Test {};

// Verifies round-trip encode/decode for a variety of values.
TEST_F(PutVarint32Test_441, RoundTrip_SingleValues_441) {
  const uint32_t values[] = {
      0u, 1u, 127u, 128u, 129u, 255u, 256u, 300u, 16383u, 16384u,
      65535u, 65536u, 2097151u, 2097152u, 268435455u, 268435456u,
      0xFFFFFFFFu
  };

  for (uint32_t v : values) {
    std::string dst;
    PutVarint32(&dst, v);

    // Decoding via public interface should succeed and match.
    Slice in(dst);
    uint32_t out = 0;
    ASSERT_TRUE(GetVarint32(&in, &out)) << "Failed to decode value " << v;
    EXPECT_EQ(out, v) << "Decoded value mismatch for " << v;

    // All bytes should be consumed by a single decode.
    EXPECT_TRUE(in.empty()) << "Extra bytes remained after decoding " << v;
  }
}

// Ensures the number of appended bytes matches VarintLength(v).
TEST_F(PutVarint32Test_441, SizeIncreaseMatchesVarintLength_441) {
  const uint32_t values[] = {
      0u, 1u, 127u, 128u, 16383u, 16384u, 2097151u, 2097152u,
      268435455u, 268435456u, 0xFFFFFFFFu
  };

  std::string dst;
  for (uint32_t v : values) {
    const size_t before = dst.size();
    PutVarint32(&dst, v);
    const size_t after = dst.size();
    const int expected = VarintLength(static_cast<uint64_t>(v));
    ASSERT_GE(expected, 1);
    ASSERT_LE(expected, 5);
    EXPECT_EQ(after - before, static_cast<size_t>(expected))
        << "Unexpected encoded length for " << v;
  }
}

// Confirms multiple encodes concatenate correctly and decode in sequence.
TEST_F(PutVarint32Test_441, ConcatenationAndSequentialDecode_441) {
  const uint32_t seq[] = {0u, 1u, 127u, 128u, 300u, 16384u, 65535u,
                          268435456u, 0xFFFFFFFFu};

  std::string dst;
  for (uint32_t v : seq) {
    PutVarint32(&dst, v);
  }

  Slice in(dst);
  for (uint32_t expected : seq) {
    uint32_t decoded = 0;
    ASSERT_TRUE(GetVarint32(&in, &decoded))
        << "Failed to decode next value in sequence";
    EXPECT_EQ(decoded, expected);
  }
  EXPECT_TRUE(in.empty()) << "Did not consume all concatenated encodings";
}

// Verifies PutVarint32 appends to (does not overwrite) existing string content.
TEST_F(PutVarint32Test_441, AppendsToExistingString_PreservesPrefix_441) {
  std::string dst = "prefix:";
  const size_t prefix_len = dst.size();
  const uint32_t v = 300u;

  PutVarint32(&dst, v);
  ASSERT_GE(dst.size(), prefix_len);

  // Prefix must remain unchanged.
  EXPECT_EQ(dst.substr(0, prefix_len), std::string("prefix:"));

  // Decoding from the appended region should yield the value and consume all.
  Slice in(dst.data() + prefix_len, dst.size() - prefix_len);
  uint32_t out = 0;
  ASSERT_TRUE(GetVarint32(&in, &out));
  EXPECT_EQ(out, v);
  EXPECT_TRUE(in.empty());
}

// Extreme boundary: max uint32_t encodes and decodes correctly; length within 1..5 bytes.
TEST_F(PutVarint32Test_441, EncodesMaxUint32Boundary_441) {
  const uint32_t v = 0xFFFFFFFFu;
  std::string dst;

  PutVarint32(&dst, v);

  const int expected_len = VarintLength(static_cast<uint64_t>(v));
  ASSERT_GE(expected_len, 1);
  ASSERT_LE(expected_len, 5);
  EXPECT_EQ(dst.size(), static_cast<size_t>(expected_len));

  Slice in(dst);
  uint32_t out = 0;
  ASSERT_TRUE(GetVarint32(&in, &out));
  EXPECT_EQ(out, v);
  EXPECT_TRUE(in.empty());
}
