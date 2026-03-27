// version_edit_encode_to_test_339.cc
#include "db/version_edit.h"

#include <gtest/gtest.h>
#include <string>

#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class VersionEditTest_339 : public ::testing::Test {
 protected:
  // Helper: encode -> decode into a fresh object -> encode again.
  static std::string Reencode(const VersionEdit& src) {
    std::string first;
    src.EncodeTo(&first);

    VersionEdit round_tripped;
    Status s = round_tripped.DecodeFrom(Slice(first));
    // Decoding must succeed for a valid self-encoding.
    EXPECT_TRUE(s.ok()) << "DecodeFrom failed: " << s.ToString();

    std::string second;
    round_tripped.EncodeTo(&second);
    return second;
  }
};

// 1) Empty edit encodes to empty string (observable: output bytes)
TEST_F(VersionEditTest_339, EncodeEmptyProducesEmpty_339) {
  VersionEdit edit;
  std::string out;
  edit.EncodeTo(&out);
  EXPECT_TRUE(out.empty());

  // Determinism: re-encoding remains empty.
  EXPECT_EQ(out, Reencode(edit));
}

// 2) Scalar fields round-trip and encoding is deterministic/non-empty.
TEST_F(VersionEditTest_339, ScalarsRoundTripAndDeterministic_339) {
  VersionEdit edit;
  edit.SetComparatorName(Slice("bytewise"));
  edit.SetLogNumber(17);
  edit.SetPrevLogNumber(16);
  edit.SetNextFile(999);
  edit.SetLastSequence(static_cast<SequenceNumber>(123456));

  std::string encoded1;
  edit.EncodeTo(&encoded1);
  EXPECT_FALSE(encoded1.empty());

  // Round-trip equality of bytes.
  std::string encoded2 = Reencode(edit);
  EXPECT_EQ(encoded1, encoded2);
}

// 3) Compact pointers (with empty InternalKey) round-trip & deterministic.
TEST_F(VersionEditTest_339, CompactPointersRoundTrip_339) {
  VersionEdit edit;
  InternalKey empty_key_a;  // default-constructed; treat as black box
  InternalKey empty_key_b;

  edit.SetCompactPointer(/*level=*/0, empty_key_a);
  edit.SetCompactPointer(/*level=*/3, empty_key_b);

  std::string encoded1;
  edit.EncodeTo(&encoded1);
  EXPECT_FALSE(encoded1.empty());

  EXPECT_EQ(encoded1, Reencode(edit));
}

// 4) Deleted files round-trip (order is internal; we only check determinism).
TEST_F(VersionEditTest_339, DeletedFilesRoundTrip_339) {
  VersionEdit edit;
  edit.RemoveFile(/*level=*/0, /*file=*/11);
  edit.RemoveFile(/*level=*/2, /*file=*/7);
  edit.RemoveFile(/*level=*/2, /*file=*/1000);

  std::string encoded1;
  edit.EncodeTo(&encoded1);
  EXPECT_FALSE(encoded1.empty());

  EXPECT_EQ(encoded1, Reencode(edit));
}

// 5) New files round-trip with sizes and (empty) key bounds.
TEST_F(VersionEditTest_339, NewFilesRoundTrip_339) {
  VersionEdit edit;
  InternalKey smallest_a, largest_a;
  InternalKey smallest_b, largest_b;

  edit.AddFile(/*level=*/1, /*file=*/42, /*file_size=*/4096, smallest_a, largest_a);
  edit.AddFile(/*level=*/0, /*file=*/7,  /*file_size=*/0,    smallest_b, largest_b);

  std::string encoded1;
  edit.EncodeTo(&encoded1);
  EXPECT_FALSE(encoded1.empty());

  EXPECT_EQ(encoded1, Reencode(edit));
}

// 6) Mixed content: scalars + compaction pointers + deletions + new files.
TEST_F(VersionEditTest_339, MixedContentRoundTrip_339) {
  VersionEdit edit;
  edit.SetComparatorName(Slice("bytewise"));
  edit.SetLogNumber(1);
  edit.SetPrevLogNumber(0);
  edit.SetNextFile(12345);
  edit.SetLastSequence(static_cast<SequenceNumber>(999));

  InternalKey k1, k2, ks, kl;
  edit.SetCompactPointer(/*level=*/2, k1);
  edit.SetCompactPointer(/*level=*/4, k2);

  edit.RemoveFile(/*level=*/3, /*file=*/777);
  edit.RemoveFile(/*level=*/1, /*file=*/8);

  edit.AddFile(/*level=*/0, /*file=*/55, /*size=*/8192, ks, kl);

  std::string encoded1;
  edit.EncodeTo(&encoded1);
  EXPECT_FALSE(encoded1.empty());

  EXPECT_EQ(encoded1, Reencode(edit));
}

// 7) Boundary values for 64-bit fields (0 and max) round-trip.
TEST_F(VersionEditTest_339, BoundaryValuesUint64RoundTrip_339) {
  VersionEdit edit;
  const uint64_t kZero = 0;
  const uint64_t kMax  = std::numeric_limits<uint64_t>::max();

  edit.SetLogNumber(kZero);
  edit.SetPrevLogNumber(kMax);
  edit.SetNextFile(kMax);
  edit.SetLastSequence(static_cast<SequenceNumber>(kMax));

  InternalKey s, l;
  edit.AddFile(/*level=*/6, /*file=*/kMax, /*file_size=*/kZero, s, l);

  std::string encoded1;
  edit.EncodeTo(&encoded1);
  EXPECT_FALSE(encoded1.empty());

  EXPECT_EQ(encoded1, Reencode(edit));
}

// 8) Clear resets to empty-encoding state (observable: output bytes change to empty).
TEST_F(VersionEditTest_339, ClearResetsToEmpty_339) {
  VersionEdit edit;
  edit.SetLogNumber(123);
  InternalKey k;
  edit.SetCompactPointer(/*level=*/1, k);

  std::string before_clear;
  edit.EncodeTo(&before_clear);
  EXPECT_FALSE(before_clear.empty());

  edit.Clear();
  std::string after_clear;
  edit.EncodeTo(&after_clear);
  EXPECT_TRUE(after_clear.empty());

  // After clear, round-trip of empty stays empty.
  EXPECT_EQ(after_clear, Reencode(edit));
}

}  // namespace leveldb
