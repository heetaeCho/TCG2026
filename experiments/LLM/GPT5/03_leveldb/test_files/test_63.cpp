// File: version_edit_set_prev_log_number_test.cc

#include "db/version_edit.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <gtest/gtest.h>
#include <limits>
#include <string>

using leveldb::Slice;
using leveldb::Status;
using leveldb::VersionEdit;

namespace {

// Helper that asserts round-trip encode/decode preserves the serialization.
void ExpectRoundTripEqual(const VersionEdit& original) {
  std::string encoded1;
  original.EncodeTo(&encoded1);
  ASSERT_FALSE(encoded1.empty()) << "Encoded edit should not be empty";

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded1));
  ASSERT_TRUE(s.ok()) << "DecodeFrom failed for a previously-encoded edit";

  std::string encoded2;
  decoded.EncodeTo(&encoded2);
  EXPECT_EQ(encoded1, encoded2) << "Re-encoding after decode should be identical";
}

}  // namespace

// Normal operation: setting a typical prev log number should be reflected in
// the encoded form and survive a decode/encode round-trip.
TEST(VersionEditTest_63, SetPrevLogNumber_RoundTrips_63) {
  VersionEdit edit;
  edit.SetPrevLogNumber(123456789ULL);
  ExpectRoundTripEqual(edit);
}

// Boundary: setting prev log number to 0 should produce a different encoding
// than an empty edit, and round-trip successfully.
TEST(VersionEditTest_63, SetPrevLogNumber_Zero_Behavior_63) {
  VersionEdit empty_edit;
  std::string empty_encoded;
  empty_edit.EncodeTo(&empty_encoded);

  VersionEdit with_zero;
  with_zero.SetPrevLogNumber(0ULL);
  std::string zero_encoded;
  with_zero.EncodeTo(&zero_encoded);

  // Observable difference: including a field should change the serialized form.
  EXPECT_NE(empty_encoded, zero_encoded);
  EXPECT_GT(zero_encoded.size(), empty_encoded.size());
  ExpectRoundTripEqual(with_zero);
}

// Boundary: setting prev log number to max uint64_t should round-trip and the
// debug string should include its decimal representation (public API).
TEST(VersionEditTest_63, SetPrevLogNumber_MaxUint64_RoundTrips_And_DebugString_63) {
  const uint64_t max_u64 = std::numeric_limits<uint64_t>::max();

  VersionEdit edit;
  edit.SetPrevLogNumber(max_u64);
  ExpectRoundTripEqual(edit);

  // Check observable textual representation via public DebugString().
  const std::string dbg = edit.DebugString();
  const std::string max_str = std::to_string(max_u64);
  EXPECT_NE(dbg.find(max_str), std::string::npos)
      << "DebugString should include the prev log number value";
}

// Overwrite behavior: setting the field twice should reflect the last call in
// the observable output (serialization and DebugString).
TEST(VersionEditTest_63, SetPrevLogNumber_Overwrite_UsesLastValue_63) {
  const uint64_t first = 7ULL;
  const uint64_t second = 999999ULL;

  VersionEdit edit;
  edit.SetPrevLogNumber(first);
  edit.SetPrevLogNumber(second);

  // Round-trip should succeed.
  ExpectRoundTripEqual(edit);

  // DebugString should include the last value; this is an observable behavior.
  const std::string dbg = edit.DebugString();
  EXPECT_NE(dbg.find(std::to_string(second)), std::string::npos);
  // It's reasonable (and observable) to expect the earlier value not to appear.
  EXPECT_EQ(dbg.find(std::to_string(first)), std::string::npos);
}

// Exceptional case (decode): a clearly invalid buffer should fail to decode;
// this guards against false positives around SetPrevLogNumber serialization.
TEST(VersionEditTest_63, DecodeFrom_InvalidInput_Fails_63) {
  VersionEdit decoded;
  // Use some garbage that should not be a valid VersionEdit serialization.
  const std::string garbage = "not-a-valid-version-edit";
  Status s = decoded.DecodeFrom(Slice(garbage));
  EXPECT_FALSE(s.ok()) << "Decoding arbitrary garbage should fail";
}

