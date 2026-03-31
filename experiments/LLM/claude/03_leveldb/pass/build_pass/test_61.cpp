#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "leveldb/slice.h"
#include <string>

namespace leveldb {

class VersionEditTest_61 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test default construction and encoding/decoding of empty VersionEdit
TEST_F(VersionEditTest_61, DefaultConstructionEncodeDecode_61) {
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test SetComparatorName and round-trip encode/decode
TEST_F(VersionEditTest_61, SetComparatorName_61) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("leveldb.BytewiseComparator"), std::string::npos);
}

// Test SetLogNumber and round-trip
TEST_F(VersionEditTest_61, SetLogNumber_61) {
  edit_.SetLogNumber(42);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("42"), std::string::npos);
}

// Test SetPrevLogNumber and round-trip
TEST_F(VersionEditTest_61, SetPrevLogNumber_61) {
  edit_.SetPrevLogNumber(99);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test SetNextFile and round-trip
TEST_F(VersionEditTest_61, SetNextFile_61) {
  edit_.SetNextFile(100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test SetLastSequence and round-trip
TEST_F(VersionEditTest_61, SetLastSequence_61) {
  edit_.SetLastSequence(1000);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test AddFile and round-trip
TEST_F(VersionEditTest_61, AddFile_61) {
  InternalKey smallest, largest;
  smallest.DecodeFrom("abc\x01\x00\x00\x00\x00\x00\x00\x01");
  largest.DecodeFrom("xyz\x01\x00\x00\x00\x00\x00\x00\x02");
  
  // Only add if keys are valid
  if (!smallest.Encode().empty() && !largest.Encode().empty()) {
    edit_.AddFile(2, 10, 1024, smallest, largest);
    
    std::string encoded;
    edit_.EncodeTo(&encoded);
    
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(Slice(encoded));
    EXPECT_TRUE(s.ok());
  }
}

// Test RemoveFile and round-trip
TEST_F(VersionEditTest_61, RemoveFile_61) {
  edit_.RemoveFile(3, 15);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("15"), std::string::npos);
}

// Test SetCompactPointer
TEST_F(VersionEditTest_61, SetCompactPointer_61) {
  InternalKey key;
  key.DecodeFrom("test\x01\x00\x00\x00\x00\x00\x00\x01");
  
  if (!key.Encode().empty()) {
    edit_.SetCompactPointer(1, key);
    
    std::string encoded;
    edit_.EncodeTo(&encoded);
    
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(Slice(encoded));
    EXPECT_TRUE(s.ok());
  }
}

// Test Clear resets the edit
TEST_F(VersionEditTest_61, ClearResetsEdit_61) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  edit_.SetLastSequence(500);
  edit_.SetComparatorName("test_comparator");
  
  edit_.Clear();
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // After clear, encoding an empty edit
  VersionEdit empty_edit;
  std::string empty_encoded;
  empty_edit.EncodeTo(&empty_encoded);
  
  EXPECT_EQ(encoded, empty_encoded);
}

// Test multiple fields set simultaneously
TEST_F(VersionEditTest_61, MultipleFieldsSet_61) {
  edit_.SetComparatorName("test_cmp");
  edit_.SetLogNumber(10);
  edit_.SetPrevLogNumber(5);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("test_cmp"), std::string::npos);
}

// Test DecodeFrom with invalid/corrupt data
TEST_F(VersionEditTest_61, DecodeFromCorruptData_61) {
  std::string corrupt_data = "this is not valid encoded data";
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(corrupt_data));
  // Corrupt data should fail to decode
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty data
TEST_F(VersionEditTest_61, DecodeFromEmptyData_61) {
  std::string empty_data;
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(empty_data));
  // Empty data should decode successfully (no fields set)
  EXPECT_TRUE(s.ok());
}

// Test DebugString on empty edit
TEST_F(VersionEditTest_61, DebugStringEmpty_61) {
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString with fields set
TEST_F(VersionEditTest_61, DebugStringWithFields_61) {
  edit_.SetLogNumber(77);
  edit_.SetComparatorName("my_comparator");
  
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("my_comparator"), std::string::npos);
}

// Test EncodeTo appends to existing string
TEST_F(VersionEditTest_61, EncodeToAppendsToExistingString_61) {
  edit_.SetLogNumber(5);
  
  std::string dst = "prefix";
  edit_.EncodeTo(&dst);
  
  // The encoded data should start after "prefix"
  EXPECT_TRUE(dst.size() > 6);  // "prefix" is 6 bytes
  EXPECT_EQ(dst.substr(0, 6), "prefix");
}

// Test multiple RemoveFile calls
TEST_F(VersionEditTest_61, MultipleRemoveFiles_61) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(0, 2);
  edit_.RemoveFile(1, 3);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test boundary: log number 0
TEST_F(VersionEditTest_61, LogNumberZero_61) {
  edit_.SetLogNumber(0);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test boundary: very large numbers
TEST_F(VersionEditTest_61, LargeNumbers_61) {
  edit_.SetLogNumber(UINT64_MAX);
  edit_.SetNextFile(UINT64_MAX);
  edit_.SetLastSequence(UINT64_MAX >> 8);  // SequenceNumber uses 56 bits
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test SetComparatorName with empty name
TEST_F(VersionEditTest_61, EmptyComparatorName_61) {
  edit_.SetComparatorName("");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test encode/decode round-trip preserves DebugString
TEST_F(VersionEditTest_61, RoundTripDebugStringConsistency_61) {
  edit_.SetLogNumber(10);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(30);
  edit_.RemoveFile(0, 5);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
  
  // Re-encode the decoded version
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  
  EXPECT_EQ(encoded, re_encoded);
}

// Test DecodeFrom with truncated data
TEST_F(VersionEditTest_61, DecodeFromTruncatedData_61) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // Truncate the encoded data
  if (encoded.size() > 2) {
    std::string truncated = encoded.substr(0, encoded.size() / 2);
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(Slice(truncated));
    // Truncated data may or may not decode correctly depending on where truncation happens
    // But it should not crash
  }
}

// Test Clear followed by setting new values
TEST_F(VersionEditTest_61, ClearAndReuse_61) {
  edit_.SetLogNumber(1);
  edit_.SetComparatorName("old_name");
  
  edit_.Clear();
  
  edit_.SetLogNumber(2);
  edit_.SetComparatorName("new_name");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("new_name"), std::string::npos);
  EXPECT_EQ(debug.find("old_name"), std::string::npos);
}

}  // namespace leveldb
