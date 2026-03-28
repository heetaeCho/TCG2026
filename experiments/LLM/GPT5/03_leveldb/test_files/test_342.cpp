// File: version_edit_decodefrom_test_342.cc
#include "db/version_edit.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "gtest/gtest.h"

using namespace leveldb;

namespace {

// Small helper: check corruption with an expected phrase in Status::ToString()
void ExpectCorruptionWithPhrase(const std::string& bytes, const char* phrase) {
  VersionEdit ve;
  Status s = ve.DecodeFrom(Slice(bytes));
  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
  std::string msg = s.ToString();
  // Don't assert exact formatting; just ensure the observable phrase appears.
  EXPECT_NE(msg.find(phrase), std::string::npos) << "Full status: " << msg;
}

} // namespace

// Normal operation: round-trip encode/decode for simple fields (no InternalKey usage).
TEST(VersionEditDecodeFromTest_342, RoundTripBasicFields_342) {
  VersionEdit src;
  src.SetComparatorName("bytewise");
  src.SetLogNumber(17);
  src.SetPrevLogNumber(9);
  src.SetNextFile(123456789ULL);
  src.SetLastSequence(42);

  std::string encoded_src;
  src.EncodeTo(&encoded_src);

  VersionEdit dst;
  Status st = dst.DecodeFrom(Slice(encoded_src));
  EXPECT_TRUE(st.ok()) << st.ToString();

  std::string encoded_dst;
  dst.EncodeTo(&encoded_dst);

  // Deterministic re-encoding should match exactly.
  EXPECT_EQ(encoded_src, encoded_dst);
}

// Verify that DecodeFrom() clears any prior state (observable by re-encoding
// exactly to the incoming payload, not retaining old fields).
TEST(VersionEditDecodeFromTest_342, DecodeClearsPreviousState_342) {
  // Start with a VE that has some fields.
  VersionEdit pre;
  pre.SetComparatorName("will_be_cleared");
  pre.SetLogNumber(999);
  std::string garbage_encoded;
  pre.EncodeTo(&garbage_encoded);

  // Prepare a minimal, valid payload with different fields.
  VersionEdit src;
  src.SetComparatorName("bytewise");
  src.SetLastSequence(777);
  std::string encoded_src;
  src.EncodeTo(&encoded_src);

  // Decode into an instance that already has state set.
  VersionEdit dst_with_state;
  dst_with_state.SetComparatorName("old_name");
  dst_with_state.SetLogNumber(1);

  Status st = dst_with_state.DecodeFrom(Slice(encoded_src));
  EXPECT_TRUE(st.ok()) << st.ToString();

  // Re-encoding must match exactly the payload we provided (i.e., old fields cleared).
  std::string encoded_dst;
  dst_with_state.EncodeTo(&encoded_dst);
  EXPECT_EQ(encoded_src, encoded_dst);
}

// Unknown tag should produce corruption with "unknown tag".
TEST(VersionEditDecodeFromTest_342, UnknownTag_342) {
  // Single byte that decodes as a varint32 = 255, which is not any known Tag.
  const std::string bytes(1, static_cast<char>(0xFF));
  ExpectCorruptionWithPhrase(bytes, "unknown tag");
}

// "invalid tag" occurs when a tag varint is *incomplete* (partial varint).
TEST(VersionEditDecodeFromTest_342, InvalidTag_PartialVarint_342) {
  // 0x80 => continuation bit set but no following byte to complete varint32
  const std::string partial_varint_tag(1, static_cast<char>(0x80));
  ExpectCorruptionWithPhrase(partial_varint_tag, "invalid tag");
}

// Missing payload for comparator name.
TEST(VersionEditDecodeFromTest_342, ComparatorTagMissingPayload_342) {
  // kComparator = 1 (single-byte varint), followed by nothing for length-prefixed slice
  const std::string bytes(1, static_cast<char>(1));
  ExpectCorruptionWithPhrase(bytes, "comparator name");
}

// Missing payload for log number.
TEST(VersionEditDecodeFromTest_342, LogNumberTagMissingPayload_342) {
  // kLogNumber = 2
  const std::string bytes(1, static_cast<char>(2));
  ExpectCorruptionWithPhrase(bytes, "log number");
}

// Missing payload for previous log number.
TEST(VersionEditDecodeFromTest_342, PrevLogNumberTagMissingPayload_342) {
  // kPrevLogNumber = 9
  const std::string bytes(1, static_cast<char>(9));
  ExpectCorruptionWithPhrase(bytes, "previous log number");
}

// Missing payload for next file number.
TEST(VersionEditDecodeFromTest_342, NextFileNumberTagMissingPayload_342) {
  // kNextFileNumber = 3
  const std::string bytes(1, static_cast<char>(3));
  ExpectCorruptionWithPhrase(bytes, "next file number");
}

// Missing payload for last sequence number.
TEST(VersionEditDecodeFromTest_342, LastSequenceTagMissingPayload_342) {
  // kLastSequence = 4
  const std::string bytes(1, static_cast<char>(4));
  ExpectCorruptionWithPhrase(bytes, "last sequence number");
}

// Missing payload for compaction pointer (needs level + internal key).
TEST(VersionEditDecodeFromTest_342, CompactPointerTagMissingPayload_342) {
  // kCompactPointer = 5
  const std::string bytes(1, static_cast<char>(5));
  ExpectCorruptionWithPhrase(bytes, "compaction pointer");
}

// Missing payload for deleted file (needs level + file number).
TEST(VersionEditDecodeFromTest_342, DeletedFileTagMissingPayload_342) {
  // kDeletedFile = 6
  const std::string bytes(1, static_cast<char>(6));
  ExpectCorruptionWithPhrase(bytes, "deleted file");
}

// Missing payload for new-file entry (needs level, number, size, smallest, largest).
TEST(VersionEditDecodeFromTest_342, NewFileTagMissingPayload_342) {
  // kNewFile = 7
  const std::string bytes(1, static_cast<char>(7));
  ExpectCorruptionWithPhrase(bytes, "new-file entry");
}
