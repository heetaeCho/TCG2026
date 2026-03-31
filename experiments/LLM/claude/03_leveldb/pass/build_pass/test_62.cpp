#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "db/dbformat.h"

namespace leveldb {

class VersionEditTest_62 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test that a default-constructed VersionEdit can encode and decode successfully
TEST_F(VersionEditTest_62, DefaultConstructAndEncodeDecode_62) {
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test SetLogNumber round-trips through encode/decode
TEST_F(VersionEditTest_62, SetLogNumber_62) {
  edit_.SetLogNumber(12345);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Verify by re-encoding and comparing
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetPrevLogNumber round-trips through encode/decode
TEST_F(VersionEditTest_62, SetPrevLogNumber_62) {
  edit_.SetPrevLogNumber(99);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetNextFile round-trips through encode/decode
TEST_F(VersionEditTest_62, SetNextFile_62) {
  edit_.SetNextFile(42);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetLastSequence round-trips through encode/decode
TEST_F(VersionEditTest_62, SetLastSequence_62) {
  edit_.SetLastSequence(1000);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetComparatorName round-trips through encode/decode
TEST_F(VersionEditTest_62, SetComparatorName_62) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test AddFile round-trips through encode/decode
TEST_F(VersionEditTest_62, AddFile_62) {
  InternalKey smallest("abc", 100, kTypeValue);
  InternalKey largest("xyz", 200, kTypeValue);
  edit_.AddFile(2, 666, 1024, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test RemoveFile round-trips through encode/decode
TEST_F(VersionEditTest_62, RemoveFile_62) {
  edit_.RemoveFile(3, 777);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetCompactPointer round-trips through encode/decode
TEST_F(VersionEditTest_62, SetCompactPointer_62) {
  InternalKey key("compact_key", 50, kTypeValue);
  edit_.SetCompactPointer(1, key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test multiple fields set together
TEST_F(VersionEditTest_62, MultipleFieldsSet_62) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(100);
  edit_.SetPrevLogNumber(99);
  edit_.SetNextFile(200);
  edit_.SetLastSequence(500);
  
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 10, 4096, smallest, largest);
  edit_.RemoveFile(1, 20);
  
  InternalKey compact_key("m", 3, kTypeValue);
  edit_.SetCompactPointer(0, compact_key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test Clear resets the edit
TEST_F(VersionEditTest_62, ClearResetsEdit_62) {
  edit_.SetLogNumber(100);
  edit_.SetNextFile(200);
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 10, 4096, smallest, largest);
  
  edit_.Clear();
  
  std::string encoded_after_clear;
  edit_.EncodeTo(&encoded_after_clear);
  
  VersionEdit fresh;
  std::string encoded_fresh;
  fresh.EncodeTo(&encoded_fresh);
  
  EXPECT_EQ(encoded_after_clear, encoded_fresh);
}

// Test DecodeFrom with corrupted data returns error
TEST_F(VersionEditTest_62, DecodeFromCorruptedData_62) {
  std::string corrupted = "this is not a valid version edit encoding";
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(corrupted));
  // Corrupted data should fail to decode
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty data succeeds (no fields set)
TEST_F(VersionEditTest_62, DecodeFromEmptyData_62) {
  std::string empty;
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(empty));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test DebugString produces non-empty output
TEST_F(VersionEditTest_62, DebugStringNonEmpty_62) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString for default edit
TEST_F(VersionEditTest_62, DebugStringDefault_62) {
  std::string debug = edit_.DebugString();
  // Even an empty edit should produce some debug string
  EXPECT_FALSE(debug.empty());
}

// Test boundary: SetLogNumber with 0
TEST_F(VersionEditTest_62, SetLogNumberZero_62) {
  edit_.SetLogNumber(0);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test boundary: SetLogNumber with max uint64_t
TEST_F(VersionEditTest_62, SetLogNumberMax_62) {
  edit_.SetLogNumber(UINT64_MAX);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test adding multiple files
TEST_F(VersionEditTest_62, AddMultipleFiles_62) {
  for (int i = 0; i < 10; i++) {
    InternalKey smallest(std::string(1, 'a' + i), i * 10, kTypeValue);
    InternalKey largest(std::string(1, 'a' + i + 1), i * 10 + 9, kTypeValue);
    edit_.AddFile(i % 7, i + 100, (i + 1) * 1024, smallest, largest);
  }
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test removing multiple files
TEST_F(VersionEditTest_62, RemoveMultipleFiles_62) {
  for (int i = 0; i < 10; i++) {
    edit_.RemoveFile(i % 7, i + 100);
  }
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test adding and removing the same file
TEST_F(VersionEditTest_62, AddAndRemoveSameFile_62) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 10, 4096, smallest, largest);
  edit_.RemoveFile(0, 10);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetComparatorName with empty string
TEST_F(VersionEditTest_62, SetComparatorNameEmpty_62) {
  edit_.SetComparatorName("");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test multiple compact pointers
TEST_F(VersionEditTest_62, MultipleCompactPointers_62) {
  for (int level = 0; level < 7; level++) {
    InternalKey key(std::string(1, 'a' + level), level * 100, kTypeValue);
    edit_.SetCompactPointer(level, key);
  }
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test DecodeFrom with truncated encoded data
TEST_F(VersionEditTest_62, DecodeFromTruncatedData_62) {
  edit_.SetLogNumber(12345);
  edit_.SetNextFile(99999);
  InternalKey smallest("abc", 100, kTypeValue);
  InternalKey largest("xyz", 200, kTypeValue);
  edit_.AddFile(2, 666, 1024, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // Truncate the encoded data
  std::string truncated = encoded.substr(0, encoded.size() / 2);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(truncated));
  // Truncated data may or may not decode, but should not crash
  // If it fails, status should not be ok
  // (We just check it doesn't crash)
}

// Test EncodeTo appends to existing string
TEST_F(VersionEditTest_62, EncodeToAppendsToExistingString_62) {
  edit_.SetLogNumber(42);
  
  std::string dst = "prefix";
  edit_.EncodeTo(&dst);
  
  // The encoded data should be appended after "prefix"
  EXPECT_TRUE(dst.size() > 6);
  EXPECT_EQ(dst.substr(0, 6), "prefix");
}

// Test DebugString contains log number info when set
TEST_F(VersionEditTest_62, DebugStringContainsLogInfo_62) {
  edit_.SetLogNumber(42);
  
  std::string debug = edit_.DebugString();
  // The debug string should mention something about the log number
  EXPECT_NE(debug.find("42"), std::string::npos);
}

// Test SetLastSequence with 0
TEST_F(VersionEditTest_62, SetLastSequenceZero_62) {
  edit_.SetLastSequence(0);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test file with zero size
TEST_F(VersionEditTest_62, AddFileZeroSize_62) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("b", 2, kTypeValue);
  edit_.AddFile(0, 1, 0, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

}  // namespace leveldb
