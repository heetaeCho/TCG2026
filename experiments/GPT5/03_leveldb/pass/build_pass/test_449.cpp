// File: util/coding_getvarint64_test_449.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <string>
#include "leveldb/slice.h"

// We only declare the function under test from its interface.
// No re-implementation or inference of internals.
namespace leveldb {
  bool GetVarint64(Slice* input, uint64_t* value);
}

// Small helper to build byte strings without relying on any varint encoder.
static std::string Bytes(std::initializer_list<uint8_t> v) {
  std::string s;
  s.reserve(v.size());
  for (auto b : v) s.push_back(static_cast<char>(b));
  return s;
}

namespace {

using leveldb::Slice;

// ---------- Normal operation ----------

TEST(GetVarint64Test_449, ParsesSingleByteZeroAndConsumesOneByte_449) {
  // 0 encoded as single byte 0x00
  std::string buf = Bytes({0x00, 0x11, 0x22});  // trailing bytes act as remainder
  Slice in(buf);
  uint64_t out = 12345; // sentinel

  ASSERT_TRUE(leveldb::GetVarint64(&in, &out));
  EXPECT_EQ(0u, out);
  // After success, input should advance to remainder only.
  EXPECT_EQ(2u, in.size());
  ASSERT_FALSE(in.empty());
  EXPECT_EQ('\x11', in[0]);
  EXPECT_EQ('\x22', in[1]);
}

TEST(GetVarint64Test_449, ParsesSmallSingleByteValue_449) {
  // 127 encoded as 0x7F
  std::string buf = Bytes({0x7F});
  Slice in(buf);
  uint64_t out = 0;

  EXPECT_TRUE(leveldb::GetVarint64(&in, &out));
  EXPECT_EQ(127u, out);
  EXPECT_TRUE(in.empty());  // consumed exactly one byte
}

TEST(GetVarint64Test_449, ParsesMultiByteValueAndConsumesCorrectly_449) {
  // 300 encoded in LEB128 as 0xAC 0x02
  std::string buf = Bytes({0xAC, 0x02, 0xFF}); // include one extra remainder byte
  Slice in(buf);
  uint64_t out = 0;

  ASSERT_TRUE(leveldb::GetVarint64(&in, &out));
  EXPECT_EQ(300u, out);
  EXPECT_EQ(1u, in.size());
  EXPECT_EQ('\xFF', in[0]); // remainder preserved
}

TEST(GetVarint64Test_449, ParsesMaxUint64AndConsumesTenBytes_449) {
  // (2^64 - 1) encoded in LEB128: 0xFF x9, then 0x01
  std::string buf = Bytes({0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x01, 0xAA});
  Slice in(buf);
  uint64_t out = 0;

  ASSERT_TRUE(leveldb::GetVarint64(&in, &out));
  EXPECT_EQ(std::numeric_limits<uint64_t>::max(), out);
  // Ten bytes consumed; one remainder (0xAA) left.
  EXPECT_EQ(1u, in.size());
  EXPECT_EQ('\xAA', in[0]);
}

TEST(GetVarint64Test_449, MultipleReadsAdvanceSliceSequentially_449) {
  // Sequence: 1 (0x01), 128 (0x80 0x01), 0 (0x00)
  std::string buf = Bytes({0x01, 0x80, 0x01, 0x00});
  Slice in(buf);

  uint64_t v = 0;
  ASSERT_TRUE(leveldb::GetVarint64(&in, &v));
  EXPECT_EQ(1u, v);
  EXPECT_EQ(3u, in.size()); // consumed first byte

  ASSERT_TRUE(leveldb::GetVarint64(&in, &v));
  EXPECT_EQ(128u, v);
  EXPECT_EQ(1u, in.size()); // consumed next two bytes

  ASSERT_TRUE(leveldb::GetVarint64(&in, &v));
  EXPECT_EQ(0u, v);
  EXPECT_TRUE(in.empty());  // all consumed
}

// ---------- Boundary / error behavior ----------

TEST(GetVarint64Test_449, EmptyInputReturnsFalseAndDoesNotModifySliceOrValue_449) {
  std::string buf; // empty
  Slice in(buf);
  uint64_t out = 0xDEADBEEFDEADBEEFull; // sentinel

  EXPECT_FALSE(leveldb::GetVarint64(&in, &out));
  // On failure, input should be unchanged.
  EXPECT_TRUE(in.empty());
  // The function doesn't write to out on failure.
  EXPECT_EQ(0xDEADBEEFDEADBEEFull, out);
}

TEST(GetVarint64Test_449, IncompleteContinuationReturnsFalseWithoutConsumption_449) {
  // Start of a multi-byte varint but cut off early: 0x80 indicates continuation,
  // but there is no following byte.
  std::string buf = Bytes({0x80, 0x33}); // second byte is just for "would-be remainder"
  // We'll only supply the first byte via the slice to simulate truncation.
  Slice in(buf.data(), 1);  // expose only {0x80}
  uint64_t out = 777;

  EXPECT_FALSE(leveldb::GetVarint64(&in, &out));
  // Input remains exactly as it was (size 1 with 0x80).
  EXPECT_EQ(1u, in.size());
  EXPECT_EQ('\x80', in[0]);
  EXPECT_EQ(777u, out); // unchanged on failure
}

TEST(GetVarint64Test_449, OverlongNonTerminatingSequenceReturnsFalse_449) {
  // More than enough 0x80 bytes with continuation bit set and never terminating.
  // This should fail and not consume input.
  std::string buf = Bytes({0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80});
  Slice in(buf);
  uint64_t out = 42;

  EXPECT_FALSE(leveldb::GetVarint64(&in, &out));
  EXPECT_EQ(buf.size(), in.size()); // unchanged
  EXPECT_EQ(42u, out);              // unchanged on failure
}

} // namespace
