// File: version_edit_addfile_test.cc

#include "db/version_edit.h"
#include "db/dbformat.h"
#include <gtest/gtest.h>
#include <string>

namespace leveldb {

class VersionEditTest_67 : public ::testing::Test {
protected:
  // Helper: encode -> decode round-trip and compare DebugString
  static std::string RoundTripDebugString(const VersionEdit& src) {
    std::string encoded;
    src.EncodeTo(&encoded);

    VersionEdit decoded;
    // DecodeFrom returns Status; rely on observable behavior through
    // DebugString equality regardless of exact Status internals.
    Slice s(encoded);
    (void)decoded.DecodeFrom(s);

    return decoded.DebugString();
  }
};

// Normal operation: single AddFile results survive encode/decode.
TEST_F(VersionEditTest_67, AddFile_SingleFile_RoundTrip_67) {
  VersionEdit ve;
  InternalKey smallest;   // default-constructed keys (no assumptions)
  InternalKey largest;

  ve.AddFile(/*level=*/0, /*file=*/123, /*file_size=*/456, smallest, largest);

  const std::string original = ve.DebugString();
  const std::string roundtripped = VersionEditTest_67::RoundTripDebugString(ve);

  EXPECT_EQ(original, roundtripped);
}

// Normal operation: multiple files across multiple levels round-trip intact.
TEST_F(VersionEditTest_67, AddFile_MultipleFilesAcrossLevels_RoundTrip_67) {
  VersionEdit ve;
  InternalKey k;  // reuse a default key for simplicity

  ve.AddFile(0, 10, 100, k, k);
  ve.AddFile(1, 11, 200, k, k);
  ve.AddFile(2, 12, 300, k, k);

  const std::string original = ve.DebugString();
  const std::string roundtripped = VersionEditTest_67::RoundTripDebugString(ve);

  EXPECT_EQ(original, roundtripped);
}

// Boundary conditions: large file number / size should still round-trip.
TEST_F(VersionEditTest_67, AddFile_BoundaryValues_RoundTrip_67) {
  VersionEdit ve;
  InternalKey k;

  const uint64_t big_num = std::numeric_limits<uint64_t>::max();
  ve.AddFile(/*level=*/6, /*file=*/big_num, /*file_size=*/big_num, k, k);
  ve.AddFile(/*level=*/0, /*file=*/0, /*file_size=*/0, k, k);  // zeros

  const std::string original = ve.DebugString();
  const std::string roundtripped = VersionEditTest_67::RoundTripDebugString(ve);

  EXPECT_EQ(original, roundtripped);
}

// Exceptional-ish but interface-allowed: negative level accepted and preserved.
TEST_F(VersionEditTest_67, AddFile_NegativeLevel_RoundTrip_67) {
  VersionEdit ve;
  InternalKey k;

  ve.AddFile(/*level=*/-1, /*file=*/42, /*file_size=*/1, k, k);

  const std::string original = ve.DebugString();
  const std::string roundtripped = VersionEditTest_67::RoundTripDebugString(ve);

  EXPECT_EQ(original, roundtripped);
}

// Sanity: EncodeTo should emit something once AddFile is used (observable effect).
TEST_F(VersionEditTest_67, AddFile_ProducesEncodableOutput_67) {
  VersionEdit ve;
  InternalKey k;

  ve.AddFile(0, 7, 77, k, k);

  std::string encoded;
  ve.EncodeTo(&encoded);

  EXPECT_FALSE(encoded.empty());
}

} // namespace leveldb
