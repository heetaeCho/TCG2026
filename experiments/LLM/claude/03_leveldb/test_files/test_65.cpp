#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/status.h"
#include "util/coding.h"

namespace leveldb {

class VersionEditTest_65 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test default construction and Clear
TEST_F(VersionEditTest_65, DefaultConstruction_65) {
  VersionEdit edit;
  std::string encoded;
  edit.EncodeTo(&encoded);
  // A default edit should encode/decode successfully
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

TEST_F(VersionEditTest_65, Clear_65) {
  edit_.SetLogNumber(100);
  edit_.SetLastSequence(200);
  edit_.SetNextFile(300);
  edit_.Clear();

  std::string encoded;
  edit_.EncodeTo(&encoded);

  // After Clear, should encode as empty/default edit
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  // Verify by comparing with a fresh VersionEdit
  VersionEdit fresh;
  std::string fresh_encoded;
  fresh.EncodeTo(&fresh_encoded);
  EXPECT_EQ(encoded, fresh_encoded);
}

// Test SetLastSequence
TEST_F(VersionEditTest_65, SetLastSequence_65) {
  edit_.SetLastSequence(12345);
  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  // Re-encode to verify round-trip
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetLogNumber
TEST_F(VersionEditTest_65, SetLogNumber_65) {
  edit_.SetLogNumber(42);
  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetPrevLogNumber
TEST_F(VersionEditTest_65, SetPrevLogNumber_65) {
  edit_.SetPrevLogNumber(7);
  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetNextFile
TEST_F(VersionEditTest_65, SetNextFile_65) {
  edit_.SetNextFile(999);
  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetComparatorName
TEST_F(VersionEditTest_65, SetComparatorName_65) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test AddFile
TEST_F(VersionEditTest_65, AddFile_65) {
  InternalKey smallest("abc", 100, kTypeValue);
  InternalKey largest("xyz", 200, kTypeValue);
  edit_.AddFile(2, 10, 1024, smallest, largest);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test RemoveFile
TEST_F(VersionEditTest_65, RemoveFile_65) {
  edit_.RemoveFile(3, 15);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetCompactPointer
TEST_F(VersionEditTest_65, SetCompactPointer_65) {
  InternalKey key("compact_key", 500, kTypeValue);
  edit_.SetCompactPointer(1, key);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test multiple fields set together
TEST_F(VersionEditTest_65, MultipleFieldsRoundTrip_65) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(100);
  edit_.SetPrevLogNumber(99);
  edit_.SetNextFile(200);
  edit_.SetLastSequence(1000);

  InternalKey smallest("aaa", 1, kTypeValue);
  InternalKey largest("zzz", 2, kTypeValue);
  edit_.AddFile(0, 50, 2048, smallest, largest);
  edit_.AddFile(1, 51, 4096, smallest, largest);

  edit_.RemoveFile(0, 49);

  InternalKey compact_key("mmm", 3, kTypeValue);
  edit_.SetCompactPointer(0, compact_key);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test DecodeFrom with corrupted data
TEST_F(VersionEditTest_65, DecodeFromCorruptedData_65) {
  std::string corrupted = "this is not valid encoded data";
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(corrupted));
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty data
TEST_F(VersionEditTest_65, DecodeFromEmptyData_65) {
  std::string empty;
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(empty));
  EXPECT_TRUE(s.ok());
}

// Test DebugString
TEST_F(VersionEditTest_65, DebugStringNonEmpty_65) {
  edit_.SetLogNumber(42);
  edit_.SetLastSequence(100);
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

TEST_F(VersionEditTest_65, DebugStringDefault_65) {
  std::string debug = edit_.DebugString();
  // Even a default edit should produce some debug output
  EXPECT_FALSE(debug.empty());
}

// Test boundary: sequence number 0
TEST_F(VersionEditTest_65, SetLastSequenceZero_65) {
  edit_.SetLastSequence(0);
  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test boundary: large numbers
TEST_F(VersionEditTest_65, LargeNumbers_65) {
  edit_.SetLogNumber(UINT64_MAX);
  edit_.SetNextFile(UINT64_MAX);
  edit_.SetLastSequence(UINT64_MAX >> 8);  // SequenceNumber is 56 bits
  edit_.SetPrevLogNumber(UINT64_MAX);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test AddFile with multiple files on same level
TEST_F(VersionEditTest_65, MultipleFilesOnSameLevel_65) {
  InternalKey s1("a", 1, kTypeValue);
  InternalKey l1("b", 2, kTypeValue);
  InternalKey s2("c", 3, kTypeValue);
  InternalKey l2("d", 4, kTypeValue);

  edit_.AddFile(0, 1, 100, s1, l1);
  edit_.AddFile(0, 2, 200, s2, l2);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test RemoveFile with multiple removes
TEST_F(VersionEditTest_65, MultipleRemoveFiles_65) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(0, 2);
  edit_.RemoveFile(1, 3);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test EncodeTo appends to existing string
TEST_F(VersionEditTest_65, EncodeToAppendsToString_65) {
  edit_.SetLogNumber(10);

  std::string prefix = "PREFIX";
  std::string dst = prefix;
  edit_.EncodeTo(&dst);

  // Should have appended, not replaced
  EXPECT_GE(dst.size(), prefix.size());
  EXPECT_EQ(dst.substr(0, prefix.size()), prefix);
}

// Test DebugString contains relevant info
TEST_F(VersionEditTest_65, DebugStringContainsComparator_65) {
  edit_.SetComparatorName("MyComparator");
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("MyComparator"), std::string::npos);
}

// Test that setting values and clearing, then encoding gives default
TEST_F(VersionEditTest_65, SetThenClearGivesDefault_65) {
  edit_.SetLogNumber(100);
  edit_.SetLastSequence(200);
  InternalKey s("a", 1, kTypeValue);
  InternalKey l("z", 2, kTypeValue);
  edit_.AddFile(0, 1, 100, s, l);
  edit_.RemoveFile(1, 5);
  edit_.Clear();

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit fresh;
  std::string fresh_encoded;
  fresh.EncodeTo(&fresh_encoded);

  EXPECT_EQ(encoded, fresh_encoded);
}

// Test DecodeFrom with truncated valid data
TEST_F(VersionEditTest_65, DecodeFromTruncatedData_65) {
  edit_.SetLogNumber(42);
  edit_.SetLastSequence(100);
  edit_.SetNextFile(200);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  // Truncate the encoded data
  if (encoded.size() > 2) {
    std::string truncated = encoded.substr(0, encoded.size() / 2);
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(Slice(truncated));
    // Truncated data should likely fail to decode properly
    // (it may or may not, depending on where the truncation happens)
    // We just ensure it doesn't crash
  }
}

// Test multiple compact pointers
TEST_F(VersionEditTest_65, MultipleCompactPointers_65) {
  InternalKey k1("key1", 1, kTypeValue);
  InternalKey k2("key2", 2, kTypeValue);
  edit_.SetCompactPointer(0, k1);
  edit_.SetCompactPointer(1, k2);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetComparatorName with empty name
TEST_F(VersionEditTest_65, SetComparatorNameEmpty_65) {
  edit_.SetComparatorName("");
  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test AddFile with zero file size
TEST_F(VersionEditTest_65, AddFileZeroSize_65) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("b", 2, kTypeValue);
  edit_.AddFile(0, 1, 0, smallest, largest);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

}  // namespace leveldb
