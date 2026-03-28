#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class VersionEditTest_64 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test that a default-constructed VersionEdit can encode and decode successfully
TEST_F(VersionEditTest_64, DefaultConstructAndEncodeDecode_64) {
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetComparatorName roundtrip through encode/decode
TEST_F(VersionEditTest_64, SetComparatorName_64) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // Verify through DebugString that comparator name is present
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("BytewiseComparator"), std::string::npos);
}

// Test SetLogNumber roundtrip
TEST_F(VersionEditTest_64, SetLogNumber_64) {
  edit_.SetLogNumber(42);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("42"), std::string::npos);
}

// Test SetPrevLogNumber roundtrip
TEST_F(VersionEditTest_64, SetPrevLogNumber_64) {
  edit_.SetPrevLogNumber(100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetNextFile roundtrip
TEST_F(VersionEditTest_64, SetNextFile_64) {
  edit_.SetNextFile(999);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("999"), std::string::npos);
}

// Test SetLastSequence roundtrip
TEST_F(VersionEditTest_64, SetLastSequence_64) {
  edit_.SetLastSequence(12345);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test AddFile roundtrip
TEST_F(VersionEditTest_64, AddFile_64) {
  InternalKey smallest("abc", 1, kTypeValue);
  InternalKey largest("xyz", 2, kTypeValue);
  edit_.AddFile(2, 100, 2048, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("abc"), std::string::npos);
  EXPECT_NE(debug.find("xyz"), std::string::npos);
}

// Test RemoveFile roundtrip
TEST_F(VersionEditTest_64, RemoveFile_64) {
  edit_.RemoveFile(3, 55);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("55"), std::string::npos);
}

// Test SetCompactPointer roundtrip
TEST_F(VersionEditTest_64, SetCompactPointer_64) {
  InternalKey key("compact_key", 10, kTypeValue);
  edit_.SetCompactPointer(1, key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("compact_key"), std::string::npos);
}

// Test multiple fields together
TEST_F(VersionEditTest_64, MultipleFieldsRoundtrip_64) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(10);
  edit_.SetPrevLogNumber(5);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(100);
  
  InternalKey smallest("aaa", 1, kTypeValue);
  InternalKey largest("zzz", 2, kTypeValue);
  edit_.AddFile(0, 1, 1024, smallest, largest);
  edit_.RemoveFile(1, 50);
  
  InternalKey compact_key("mmm", 5, kTypeValue);
  edit_.SetCompactPointer(2, compact_key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("BytewiseComparator"), std::string::npos);
  EXPECT_NE(debug.find("aaa"), std::string::npos);
  EXPECT_NE(debug.find("zzz"), std::string::npos);
  EXPECT_NE(debug.find("mmm"), std::string::npos);
}

// Test Clear resets the edit
TEST_F(VersionEditTest_64, ClearResetsEdit_64) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  InternalKey smallest("foo", 1, kTypeValue);
  InternalKey largest("bar", 2, kTypeValue);
  edit_.AddFile(0, 1, 512, smallest, largest);
  
  edit_.Clear();
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // After clear, debug string should not contain the previously set values
  // (or at least should be minimal)
  std::string debug = decoded.DebugString();
  EXPECT_EQ(debug.find("foo"), std::string::npos);
}

// Test DecodeFrom with corrupted/invalid data
TEST_F(VersionEditTest_64, DecodeFromCorruptedData_64) {
  std::string corrupted = "this is not a valid encoded version edit";
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(corrupted));
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty data
TEST_F(VersionEditTest_64, DecodeFromEmptyData_64) {
  std::string empty;
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(empty));
  // Empty data should be valid (no fields set)
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test DecodeFrom with truncated data
TEST_F(VersionEditTest_64, DecodeFromTruncatedData_64) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // Truncate the encoded data
  std::string truncated = encoded.substr(0, encoded.size() / 2);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(truncated));
  // Truncated data might fail to decode
  // We can't guarantee which way it goes, but it shouldn't crash
}

// Test encoding to non-empty string appends
TEST_F(VersionEditTest_64, EncodeToAppendsToString_64) {
  edit_.SetLogNumber(42);
  
  std::string dst = "prefix";
  edit_.EncodeTo(&dst);
  
  // The encoded data should start with "prefix"
  EXPECT_EQ(dst.substr(0, 6), "prefix");
  EXPECT_GT(dst.size(), 6u);
}

// Test boundary values for file numbers
TEST_F(VersionEditTest_64, BoundaryLargeFileNumber_64) {
  edit_.SetNextFile(UINT64_MAX);
  edit_.SetLogNumber(UINT64_MAX);
  edit_.SetLastSequence(UINT64_MAX);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test boundary value zero
TEST_F(VersionEditTest_64, BoundaryZeroValues_64) {
  edit_.SetNextFile(0);
  edit_.SetLogNumber(0);
  edit_.SetPrevLogNumber(0);
  edit_.SetLastSequence(0);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test multiple AddFile calls
TEST_F(VersionEditTest_64, MultipleAddFiles_64) {
  for (int i = 0; i < 10; i++) {
    InternalKey smallest(std::string(1, 'a' + i), i + 1, kTypeValue);
    InternalKey largest(std::string(1, 'a' + i + 1), i + 2, kTypeValue);
    edit_.AddFile(i % 7, i + 1, 1024 * (i + 1), smallest, largest);
  }
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test multiple RemoveFile calls
TEST_F(VersionEditTest_64, MultipleRemoveFiles_64) {
  for (int i = 0; i < 10; i++) {
    edit_.RemoveFile(i % 7, i + 1);
  }
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test DebugString on empty edit
TEST_F(VersionEditTest_64, DebugStringEmpty_64) {
  std::string debug = edit_.DebugString();
  // Should return some valid string representation
  EXPECT_FALSE(debug.empty());
}

// Test DebugString on populated edit
TEST_F(VersionEditTest_64, DebugStringPopulated_64) {
  edit_.SetComparatorName("test_comparator");
  edit_.SetLogNumber(7);
  edit_.SetNextFile(15);
  edit_.SetLastSequence(200);
  
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("test_comparator"), std::string::npos);
}

// Test encode-decode preserves identity (double roundtrip)
TEST_F(VersionEditTest_64, DoubleRoundtrip_64) {
  edit_.SetComparatorName("test_cmp");
  edit_.SetLogNumber(7);
  edit_.SetNextFile(15);
  edit_.SetLastSequence(200);
  
  InternalKey smallest("aaa", 1, kTypeValue);
  InternalKey largest("zzz", 2, kTypeValue);
  edit_.AddFile(0, 1, 1024, smallest, largest);
  
  // First roundtrip
  std::string encoded1;
  edit_.EncodeTo(&encoded1);
  
  VersionEdit decoded1;
  ASSERT_TRUE(decoded1.DecodeFrom(Slice(encoded1)).ok());
  
  // Second roundtrip
  std::string encoded2;
  decoded1.EncodeTo(&encoded2);
  
  VersionEdit decoded2;
  ASSERT_TRUE(decoded2.DecodeFrom(Slice(encoded2)).ok());
  
  // Both encoded forms should be identical
  EXPECT_EQ(encoded1, encoded2);
}

// Test that AddFile and RemoveFile for same file can coexist
TEST_F(VersionEditTest_64, AddAndRemoveSameFile_64) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 5, 1024, smallest, largest);
  edit_.RemoveFile(0, 5);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetComparatorName with empty name
TEST_F(VersionEditTest_64, EmptyComparatorName_64) {
  edit_.SetComparatorName("");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test multiple compact pointers
TEST_F(VersionEditTest_64, MultipleCompactPointers_64) {
  for (int i = 0; i < 7; i++) {
    InternalKey key(std::string(1, 'a' + i), i + 1, kTypeValue);
    edit_.SetCompactPointer(i, key);
  }
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

}  // namespace leveldb
