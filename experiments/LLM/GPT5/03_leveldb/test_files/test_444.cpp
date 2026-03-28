// File: util/coding_put_length_prefixed_slice_test.cc

#include "gtest/gtest.h"

// Assume these are declared in the project's public headers:
#include "util/coding.h"     // PutLengthPrefixedSlice, PutVarint32
#include "leveldb/slice.h"   // leveldb::Slice

using leveldb::Slice;
using leveldb::PutLengthPrefixedSlice;
using leveldb::PutVarint32;

namespace {

// Helper that builds the expected wire image using only public functions.
static std::string BuildExpected(const Slice& s) {
  std::string out;
  PutVarint32(&out, static_cast<uint32_t>(s.size()));
  out.append(s.data(), s.size());
  return out;
}

}  // namespace

// Normal operation: encodes a small ASCII string (single-byte varint length).
TEST(PutLengthPrefixedSliceTest_444, EncodesSmallAscii_444) {
  const std::string input = "hello";
  const Slice slice(input);

  std::string dst;
  PutLengthPrefixedSlice(&dst, slice);

  EXPECT_EQ(dst, BuildExpected(slice));
}

// Boundary condition: size == 0 (empty slice).
TEST(PutLengthPrefixedSliceTest_444, EncodesEmptySlice_444) {
  const std::string input = "";
  const Slice slice(input);

  std::string dst = "prefix";  // ensure it appends and does not clear
  const std::string before = dst;

  PutLengthPrefixedSlice(&dst, slice);

  const std::string expected_after = before + BuildExpected(slice);
  EXPECT_EQ(dst, expected_after);
}

// Boundary condition around varint32 one-byte/two-byte transition.
// 127 should use a 1-byte length; 128 should require more than 1 byte.
// (We do NOT assert the internal encoding; we validate full output via
// the public PutVarint32 used to construct expected.)
TEST(PutLengthPrefixedSliceTest_444, Length127And128Boundaries_444) {
  std::string s127(127, 'a');
  std::string s128(128, 'b');

  Slice slice127(s127);
  Slice slice128(s128);

  std::string dst;
  PutLengthPrefixedSlice(&dst, slice127);
  PutLengthPrefixedSlice(&dst, slice128);

  std::string expected;
  expected += BuildExpected(slice127);
  expected += BuildExpected(slice128);

  EXPECT_EQ(dst, expected);
}

// Supports arbitrary binary data including NUL bytes and high-bit values.
TEST(PutLengthPrefixedSliceTest_444, EncodesBinaryDataWithNulls_444) {
  const char raw[] = {'\0', 'x', '\xff', '\0', 'y'};
  const Slice slice(raw, sizeof(raw));

  std::string dst;
  PutLengthPrefixedSlice(&dst, slice);

  EXPECT_EQ(dst, BuildExpected(slice));

  // Also verify payload portion is exactly what we provided (by slicing).
  // Find the length prefix size by separately encoding the length.
  std::string len_prefix_only;
  PutVarint32(&len_prefix_only, static_cast<uint32_t>(slice.size()));
  const size_t prefix_len = len_prefix_only.size();

  ASSERT_GE(dst.size(), prefix_len + slice.size());
  EXPECT_EQ(0, std::memcmp(dst.data() + prefix_len, raw, sizeof(raw)));
}

// Appends multiple records sequentially without overwriting previous content.
TEST(PutLengthPrefixedSliceTest_444, AppendsMultipleRecords_444) {
  Slice s1("foo");
  Slice s2("bar");
  Slice s3("baz");

  std::string dst = "X";  // pre-fill with a marker
  PutLengthPrefixedSlice(&dst, s1);
  PutLengthPrefixedSlice(&dst, s2);
  PutLengthPrefixedSlice(&dst, s3);

  std::string expected = "X";
  expected += BuildExpected(s1);
  expected += BuildExpected(s2);
  expected += BuildExpected(s3);

  EXPECT_EQ(dst, expected);
}

// Works with large payloads (thousands of bytes) — stress basic behavior.
TEST(PutLengthPrefixedSliceTest_444, LargePayload_444) {
  std::string large(8192, '\x7f');  // 8 KB of 0x7f
  Slice slice(large);

  std::string dst;
  PutLengthPrefixedSlice(&dst, slice);

  EXPECT_EQ(dst, BuildExpected(slice));
  // Quick sanity: resulting size is prefix + payload.
  std::string len_prefix_only;
  PutVarint32(&len_prefix_only, static_cast<uint32_t>(slice.size()));
  EXPECT_EQ(dst.size(), len_prefix_only.size() + slice.size());
}

// Non-ASCII UTF-8 content is treated as raw bytes; should round-trip unchanged.
TEST(PutLengthPrefixedSliceTest_444, Utf8ContentAsBytes_444) {
  const std::string utf8 = u8"안녕하세요 😊 테스트";  // arbitrary UTF-8
  const Slice slice(utf8);

  std::string dst;
  PutLengthPrefixedSlice(&dst, slice);

  EXPECT_EQ(dst, BuildExpected(slice));
}

