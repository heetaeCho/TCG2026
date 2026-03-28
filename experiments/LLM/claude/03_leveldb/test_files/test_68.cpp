#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "db/dbformat.h"

#include <string>
#include <vector>

namespace leveldb {

class VersionEditTest_68 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test that a default-constructed VersionEdit can encode and decode successfully
TEST_F(VersionEditTest_68, DefaultConstructEncodeDecodeRoundTrip_68) {
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test RemoveFile with a single file
TEST_F(VersionEditTest_68, RemoveFileSingle_68) {
  edit_.RemoveFile(1, 100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Verify through DebugString that the deleted file info is present
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("DeleteFile"), std::string::npos);
}

// Test RemoveFile with multiple files at different levels
TEST_F(VersionEditTest_68, RemoveFileMultipleLevels_68) {
  edit_.RemoveFile(0, 10);
  edit_.RemoveFile(1, 20);
  edit_.RemoveFile(2, 30);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("DeleteFile"), std::string::npos);
}

// Test RemoveFile with duplicate entries (same level and file)
TEST_F(VersionEditTest_68, RemoveFileDuplicate_68) {
  edit_.RemoveFile(1, 100);
  edit_.RemoveFile(1, 100);  // Duplicate; set should deduplicate
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test RemoveFile with same file number on different levels
TEST_F(VersionEditTest_68, RemoveFileSameFileNumberDifferentLevels_68) {
  edit_.RemoveFile(0, 42);
  edit_.RemoveFile(3, 42);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test RemoveFile with level 0 boundary
TEST_F(VersionEditTest_68, RemoveFileLevelZero_68) {
  edit_.RemoveFile(0, 1);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test RemoveFile with large file number
TEST_F(VersionEditTest_68, RemoveFileLargeFileNumber_68) {
  edit_.RemoveFile(5, UINT64_MAX);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test SetComparatorName and encode/decode
TEST_F(VersionEditTest_68, SetComparatorName_68) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("Comparator"), std::string::npos);
}

// Test SetLogNumber and encode/decode
TEST_F(VersionEditTest_68, SetLogNumber_68) {
  edit_.SetLogNumber(42);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("LogNumber"), std::string::npos);
}

// Test SetPrevLogNumber and encode/decode
TEST_F(VersionEditTest_68, SetPrevLogNumber_68) {
  edit_.SetPrevLogNumber(7);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("PrevLogNumber"), std::string::npos);
}

// Test SetNextFile and encode/decode
TEST_F(VersionEditTest_68, SetNextFile_68) {
  edit_.SetNextFile(1000);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("NextFile"), std::string::npos);
}

// Test SetLastSequence and encode/decode
TEST_F(VersionEditTest_68, SetLastSequence_68) {
  edit_.SetLastSequence(9999);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("LastSeq"), std::string::npos);
}

// Test AddFile and encode/decode
TEST_F(VersionEditTest_68, AddFile_68) {
  InternalKey smallest, largest;
  smallest.DecodeFrom(Slice("abc\x01\x00\x00\x00\x00\x00\x00\x01", 11));
  largest.DecodeFrom(Slice("xyz\x01\x00\x00\x00\x00\x00\x00\x02", 11));
  
  edit_.AddFile(2, 50, 1024, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("AddFile"), std::string::npos);
}

// Test AddFile and RemoveFile together
TEST_F(VersionEditTest_68, AddFileAndRemoveFile_68) {
  InternalKey smallest, largest;
  smallest.DecodeFrom(Slice("abc\x01\x00\x00\x00\x00\x00\x00\x01", 11));
  largest.DecodeFrom(Slice("xyz\x01\x00\x00\x00\x00\x00\x00\x02", 11));
  
  edit_.AddFile(2, 50, 1024, smallest, largest);
  edit_.RemoveFile(1, 49);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("AddFile"), std::string::npos);
  EXPECT_NE(debug.find("DeleteFile"), std::string::npos);
}

// Test Clear resets the edit
TEST_F(VersionEditTest_68, ClearResetsEdit_68) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  edit_.RemoveFile(1, 10);
  
  edit_.Clear();
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit fresh;
  std::string fresh_encoded;
  fresh.EncodeTo(&fresh_encoded);
  
  // After Clear, the encoded form should be same as a fresh VersionEdit
  EXPECT_EQ(encoded, fresh_encoded);
}

// Test DecodeFrom with corrupted data
TEST_F(VersionEditTest_68, DecodeFromCorruptedData_68) {
  std::string corrupted = "this is not valid encoded data";
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(corrupted));
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty data
TEST_F(VersionEditTest_68, DecodeFromEmptyData_68) {
  std::string empty;
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(empty));
  // Empty data should decode successfully (no fields set)
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test DebugString on empty edit
TEST_F(VersionEditTest_68, DebugStringEmpty_68) {
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test full round-trip with all fields set
TEST_F(VersionEditTest_68, FullRoundTrip_68) {
  edit_.SetComparatorName("test_comparator");
  edit_.SetLogNumber(100);
  edit_.SetPrevLogNumber(99);
  edit_.SetNextFile(200);
  edit_.SetLastSequence(5000);
  
  InternalKey smallest, largest;
  smallest.DecodeFrom(Slice("aaa\x01\x00\x00\x00\x00\x00\x00\x01", 11));
  largest.DecodeFrom(Slice("zzz\x01\x00\x00\x00\x00\x00\x00\x02", 11));
  
  edit_.AddFile(0, 10, 512, smallest, largest);
  edit_.AddFile(1, 11, 1024, smallest, largest);
  edit_.RemoveFile(0, 5);
  edit_.RemoveFile(2, 8);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  // Re-encode and compare
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetCompactPointer and encode/decode
TEST_F(VersionEditTest_68, SetCompactPointer_68) {
  InternalKey key;
  key.DecodeFrom(Slice("key\x01\x00\x00\x00\x00\x00\x00\x01", 11));
  
  edit_.SetCompactPointer(2, key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("CompactPointer"), std::string::npos);
}

// Test multiple RemoveFile calls at same level with different files
TEST_F(VersionEditTest_68, RemoveFileMultipleSameLevel_68) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(0, 2);
  edit_.RemoveFile(0, 3);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test that encoding is deterministic (encode twice gives same result)
TEST_F(VersionEditTest_68, EncodingDeterministic_68) {
  edit_.SetLogNumber(42);
  edit_.RemoveFile(1, 10);
  
  std::string encoded1, encoded2;
  edit_.EncodeTo(&encoded1);
  edit_.EncodeTo(&encoded2);
  
  // Note: EncodeTo appends to dst, so encoding twice to same string would differ.
  // But encoding to two separate strings should give identical results.
  EXPECT_EQ(encoded1, encoded2);
}

// Test RemoveFile with file number 0
TEST_F(VersionEditTest_68, RemoveFileZeroFileNumber_68) {
  edit_.RemoveFile(0, 0);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test that EncodeTo appends to existing string
TEST_F(VersionEditTest_68, EncodeToAppends_68) {
  edit_.SetLogNumber(42);
  
  std::string dst = "prefix";
  edit_.EncodeTo(&dst);
  
  EXPECT_TRUE(dst.size() > 6);  // Should have content beyond "prefix"
  EXPECT_EQ(dst.substr(0, 6), "prefix");
}

}  // namespace leveldb
