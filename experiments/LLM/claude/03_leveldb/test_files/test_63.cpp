#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"

namespace leveldb {

class VersionEditTest_63 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test default construction and Clear
TEST_F(VersionEditTest_63, DefaultConstruction_63) {
  // A freshly constructed VersionEdit should encode and decode successfully
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

TEST_F(VersionEditTest_63, Clear_63) {
  edit_.SetLogNumber(100);
  edit_.SetNextFile(200);
  edit_.SetLastSequence(300);
  edit_.Clear();
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // After clear, should encode as a minimal/empty edit
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // The debug string after clear should not contain the previously set values
  std::string debug = decoded.DebugString();
  EXPECT_EQ(debug.find("LogNumber"), std::string::npos);
}

// Test SetComparatorName
TEST_F(VersionEditTest_63, SetComparatorName_63) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("BytewiseComparator"), std::string::npos);
}

// Test SetLogNumber
TEST_F(VersionEditTest_63, SetLogNumber_63) {
  edit_.SetLogNumber(42);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("LogNumber"), std::string::npos);
}

// Test SetPrevLogNumber
TEST_F(VersionEditTest_63, SetPrevLogNumber_63) {
  edit_.SetPrevLogNumber(99);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("PrevLogNumber"), std::string::npos);
}

// Test SetNextFile
TEST_F(VersionEditTest_63, SetNextFile_63) {
  edit_.SetNextFile(500);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("NextFile"), std::string::npos);
}

// Test SetLastSequence
TEST_F(VersionEditTest_63, SetLastSequence_63) {
  edit_.SetLastSequence(1000);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("LastSeq"), std::string::npos);
}

// Test AddFile
TEST_F(VersionEditTest_63, AddFile_63) {
  InternalKey smallest("abc", 1, kTypeValue);
  InternalKey largest("xyz", 2, kTypeValue);
  edit_.AddFile(2, 10, 1024, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("AddFile"), std::string::npos);
}

// Test RemoveFile
TEST_F(VersionEditTest_63, RemoveFile_63) {
  edit_.RemoveFile(3, 15);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("RemoveFile"), std::string::npos);
}

// Test SetCompactPointer
TEST_F(VersionEditTest_63, SetCompactPointer_63) {
  InternalKey key("middle", 50, kTypeValue);
  edit_.SetCompactPointer(1, key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("CompactPointer"), std::string::npos);
}

// Test encoding and decoding all fields together
TEST_F(VersionEditTest_63, EncodeDecodeAllFields_63) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(10);
  edit_.SetPrevLogNumber(5);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(100);
  
  InternalKey compact_key("compact", 10, kTypeValue);
  edit_.SetCompactPointer(0, compact_key);
  
  InternalKey smallest("aaa", 1, kTypeValue);
  InternalKey largest("zzz", 2, kTypeValue);
  edit_.AddFile(0, 1, 2048, smallest, largest);
  
  edit_.RemoveFile(1, 5);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("BytewiseComparator"), std::string::npos);
  EXPECT_NE(debug.find("LogNumber"), std::string::npos);
  EXPECT_NE(debug.find("PrevLogNumber"), std::string::npos);
  EXPECT_NE(debug.find("NextFile"), std::string::npos);
  EXPECT_NE(debug.find("LastSeq"), std::string::npos);
  EXPECT_NE(debug.find("CompactPointer"), std::string::npos);
  EXPECT_NE(debug.find("AddFile"), std::string::npos);
  EXPECT_NE(debug.find("RemoveFile"), std::string::npos);
}

// Test DecodeFrom with invalid/corrupt data
TEST_F(VersionEditTest_63, DecodeFromCorruptData_63) {
  std::string corrupt_data = "this is not valid encoded data";
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(corrupt_data));
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty data
TEST_F(VersionEditTest_63, DecodeFromEmptyData_63) {
  std::string empty_data;
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(empty_data));
  EXPECT_TRUE(s.ok());
}

// Test multiple AddFile calls
TEST_F(VersionEditTest_63, MultipleAddFiles_63) {
  InternalKey s1("a", 1, kTypeValue);
  InternalKey l1("b", 2, kTypeValue);
  InternalKey s2("c", 3, kTypeValue);
  InternalKey l2("d", 4, kTypeValue);
  InternalKey s3("e", 5, kTypeValue);
  InternalKey l3("f", 6, kTypeValue);
  
  edit_.AddFile(0, 1, 100, s1, l1);
  edit_.AddFile(0, 2, 200, s2, l2);
  edit_.AddFile(1, 3, 300, s3, l3);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  // Should have multiple AddFile entries
  size_t pos = 0;
  int count = 0;
  while ((pos = debug.find("AddFile", pos)) != std::string::npos) {
    count++;
    pos++;
  }
  EXPECT_EQ(count, 3);
}

// Test multiple RemoveFile calls
TEST_F(VersionEditTest_63, MultipleRemoveFiles_63) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(0, 2);
  edit_.RemoveFile(1, 3);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  size_t pos = 0;
  int count = 0;
  while ((pos = debug.find("RemoveFile", pos)) != std::string::npos) {
    count++;
    pos++;
  }
  EXPECT_EQ(count, 3);
}

// Test boundary: SetPrevLogNumber with 0
TEST_F(VersionEditTest_63, SetPrevLogNumberZero_63) {
  edit_.SetPrevLogNumber(0);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test boundary: SetLogNumber with max uint64
TEST_F(VersionEditTest_63, SetLogNumberMaxValue_63) {
  edit_.SetLogNumber(UINT64_MAX);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test boundary: SetNextFile with max uint64
TEST_F(VersionEditTest_63, SetNextFileMaxValue_63) {
  edit_.SetNextFile(UINT64_MAX);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test boundary: SetLastSequence with max value
TEST_F(VersionEditTest_63, SetLastSequenceMaxValue_63) {
  edit_.SetLastSequence(UINT64_MAX);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test EncodeTo appends to existing string
TEST_F(VersionEditTest_63, EncodeToAppendsToString_63) {
  edit_.SetLogNumber(7);
  
  std::string dst = "prefix";
  edit_.EncodeTo(&dst);
  
  // The encoded data should be appended after "prefix"
  EXPECT_GE(dst.size(), 7u);  // "prefix" is 6 chars, plus at least 1 byte of encoding
  EXPECT_EQ(dst.substr(0, 6), "prefix");
}

// Test DebugString on empty VersionEdit
TEST_F(VersionEditTest_63, DebugStringEmpty_63) {
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
  // Should contain "VersionEdit" or similar header
  EXPECT_NE(debug.find("VersionEdit"), std::string::npos);
}

// Test encode-decode roundtrip preserves equality via DebugString
TEST_F(VersionEditTest_63, EncodeDecodeRoundtrip_63) {
  edit_.SetComparatorName("test_comparator");
  edit_.SetLogNumber(42);
  edit_.SetPrevLogNumber(41);
  edit_.SetNextFile(100);
  edit_.SetLastSequence(999);
  
  InternalKey smallest("hello", 10, kTypeValue);
  InternalKey largest("world", 20, kTypeValue);
  edit_.AddFile(3, 55, 4096, smallest, largest);
  edit_.RemoveFile(2, 33);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // Re-encode the decoded version and compare
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test DecodeFrom with truncated data
TEST_F(VersionEditTest_63, DecodeFromTruncatedData_63) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // Truncate the encoded data
  if (encoded.size() > 1) {
    std::string truncated = encoded.substr(0, encoded.size() / 2);
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(Slice(truncated));
    // May or may not be ok depending on where we truncated, but shouldn't crash
    // We just ensure no crash; the status tells us if it succeeded
    (void)s;
  }
}

// Test AddFile with file_size of 0
TEST_F(VersionEditTest_63, AddFileZeroSize_63) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("b", 2, kTypeValue);
  edit_.AddFile(0, 1, 0, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetComparatorName with empty name
TEST_F(VersionEditTest_63, SetComparatorNameEmpty_63) {
  edit_.SetComparatorName("");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test Clear then re-use
TEST_F(VersionEditTest_63, ClearAndReuse_63) {
  edit_.SetLogNumber(100);
  edit_.Clear();
  edit_.SetLogNumber(200);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  // Should only reflect the second SetLogNumber(200)
  EXPECT_NE(debug.find("200"), std::string::npos);
}

// Test multiple compact pointers
TEST_F(VersionEditTest_63, MultipleCompactPointers_63) {
  InternalKey k1("a", 1, kTypeValue);
  InternalKey k2("m", 2, kTypeValue);
  InternalKey k3("z", 3, kTypeValue);
  
  edit_.SetCompactPointer(0, k1);
  edit_.SetCompactPointer(1, k2);
  edit_.SetCompactPointer(2, k3);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  size_t pos = 0;
  int count = 0;
  while ((pos = debug.find("CompactPointer", pos)) != std::string::npos) {
    count++;
    pos++;
  }
  EXPECT_EQ(count, 3);
}

}  // namespace leveldb
