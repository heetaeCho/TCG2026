// File: db/version_edit_remove_file_test.cc

#include "db/version_edit.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include <gtest/gtest.h>
#include <cstdint>
#include <string>

namespace leveldb {

class VersionEditTest_68 : public ::testing::Test {};

// [Normal] A single RemoveFile survives Encode/Decode round-trip.
TEST_F(VersionEditTest_68, RemoveFile_EncodeDecodeRoundTrip_68) {
  VersionEdit edit;
  edit.RemoveFile(/*level=*/1, /*file=*/123u);

  std::string encoded1;
  edit.EncodeTo(&encoded1);
  ASSERT_FALSE(encoded1.empty()) << "Encoding after RemoveFile should not be empty";

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded1));
  ASSERT_TRUE(s.ok()) << "DecodeFrom should succeed for its own encoding";

  std::string encoded2;
  decoded.EncodeTo(&encoded2);
  EXPECT_EQ(encoded1, encoded2) << "Re-encoding decoded edit should be stable";
  EXPECT_EQ(edit.DebugString(), decoded.DebugString())
      << "DebugString should match after round-trip";
}

// [Idempotence] Removing the same (level, file) pair twice should not change observable encoding.
TEST_F(VersionEditTest_68, RemoveFile_DuplicateIdempotentEncoding_68) {
  VersionEdit once;
  once.RemoveFile(2, 999u);

  VersionEdit twice;
  twice.RemoveFile(2, 999u);
  twice.RemoveFile(2, 999u);  // duplicate

  std::string enc_once, enc_twice;
  once.EncodeTo(&enc_once);
  twice.EncodeTo(&enc_twice);

  EXPECT_EQ(enc_once, enc_twice)
      << "Encoding should be identical whether removed once or twice";
}

// [Boundary] Removing a file with boundary values encodes/decodes successfully.
TEST_F(VersionEditTest_68, RemoveFile_BoundaryValues_Uint64Max_68) {
  VersionEdit edit;
  edit.RemoveFile(/*level=*/0, /*file=*/std::numeric_limits<uint64_t>::max());

  std::string encoded;
  edit.EncodeTo(&encoded);
  ASSERT_FALSE(encoded.empty());

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << "DecodeFrom should succeed for boundary values";

  // Re-encode to ensure stability.
  std::string reencoded;
  decoded.EncodeTo(&reencoded);
  EXPECT_EQ(encoded, reencoded);
}

// [Clear] After Clear(), previous RemoveFile effects are no longer present in observable state.
TEST_F(VersionEditTest_68, RemoveFile_ClearRemovesDeletion_68) {
  VersionEdit edit_with_delete;
  edit_with_delete.RemoveFile(3, 777u);

  // Encode before Clear()
  std::string before_clear;
  edit_with_delete.EncodeTo(&before_clear);
  ASSERT_FALSE(before_clear.empty()) << "Sanity check: encoding should reflect the deletion";

  // Clear and compare to a fresh edit's encoding
  edit_with_delete.Clear();

  VersionEdit fresh;
  std::string after_clear, fresh_encoded;
  edit_with_delete.EncodeTo(&after_clear);
  fresh.EncodeTo(&fresh_encoded);

  EXPECT_EQ(after_clear, fresh_encoded)
      << "After Clear(), encoding should match a fresh VersionEdit";
}

}  // namespace leveldb
