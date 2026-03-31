#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/status.h"
#include "util/coding.h"

namespace leveldb {

class VersionEditTest_476 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a default-constructed VersionEdit can encode and decode successfully
TEST_F(VersionEditTest_476, DefaultConstructAndEncodeDecode_476) {
  VersionEdit edit;
  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test Clear resets the state
TEST_F(VersionEditTest_476, ClearResetsState_476) {
  VersionEdit edit;
  edit.SetLogNumber(42);
  edit.SetNextFile(100);
  edit.SetLastSequence(200);
  edit.SetComparatorName("test_comparator");

  edit.Clear();

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  // After Clear, DebugString should not contain the previously set values
  std::string debug = decoded.DebugString();
  EXPECT_EQ(debug.find("test_comparator"), std::string::npos);
}

// Test SetComparatorName
TEST_F(VersionEditTest_476, SetComparatorName_476) {
  VersionEdit edit;
  edit.SetComparatorName("leveldb.BytewiseComparator");

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("leveldb.BytewiseComparator"), std::string::npos);
}

// Test SetLogNumber
TEST_F(VersionEditTest_476, SetLogNumber_476) {
  VersionEdit edit;
  edit.SetLogNumber(123);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("LogNumber"), std::string::npos);
}

// Test SetPrevLogNumber
TEST_F(VersionEditTest_476, SetPrevLogNumber_476) {
  VersionEdit edit;
  edit.SetPrevLogNumber(99);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("PrevLogNumber"), std::string::npos);
}

// Test SetNextFile
TEST_F(VersionEditTest_476, SetNextFile_476) {
  VersionEdit edit;
  edit.SetNextFile(500);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("NextFile"), std::string::npos);
}

// Test SetLastSequence
TEST_F(VersionEditTest_476, SetLastSequence_476) {
  VersionEdit edit;
  edit.SetLastSequence(1000);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("LastSeq"), std::string::npos);
}

// Test AddFile
TEST_F(VersionEditTest_476, AddFile_476) {
  VersionEdit edit;
  InternalKey smallest, largest;
  smallest.DecodeFrom(Slice("abc\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  largest.DecodeFrom(Slice("xyz\x01\x00\x00\x00\x00\x00\x00\x00", 11));

  edit.AddFile(2, 100, 4096, smallest, largest);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("AddFile"), std::string::npos);
}

// Test RemoveFile
TEST_F(VersionEditTest_476, RemoveFile_476) {
  VersionEdit edit;
  edit.RemoveFile(3, 200);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("RemoveFile"), std::string::npos);
}

// Test SetCompactPointer
TEST_F(VersionEditTest_476, SetCompactPointer_476) {
  VersionEdit edit;
  InternalKey key;
  key.DecodeFrom(Slice("test\x01\x00\x00\x00\x00\x00\x00\x00", 12));
  edit.SetCompactPointer(1, key);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("CompactPointer"), std::string::npos);
}

// Test all fields set together
TEST_F(VersionEditTest_476, AllFieldsSet_476) {
  VersionEdit edit;
  edit.SetComparatorName("leveldb.BytewiseComparator");
  edit.SetLogNumber(10);
  edit.SetPrevLogNumber(5);
  edit.SetNextFile(20);
  edit.SetLastSequence(100);

  InternalKey smallest, largest;
  smallest.DecodeFrom(Slice("aaa\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  largest.DecodeFrom(Slice("zzz\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  edit.AddFile(0, 1, 1024, smallest, largest);
  edit.RemoveFile(1, 2);

  InternalKey compactKey;
  compactKey.DecodeFrom(Slice("mmm\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  edit.SetCompactPointer(0, compactKey);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("leveldb.BytewiseComparator"), std::string::npos);
  EXPECT_NE(debug.find("LogNumber"), std::string::npos);
  EXPECT_NE(debug.find("PrevLogNumber"), std::string::npos);
  EXPECT_NE(debug.find("NextFile"), std::string::npos);
  EXPECT_NE(debug.find("LastSeq"), std::string::npos);
  EXPECT_NE(debug.find("AddFile"), std::string::npos);
  EXPECT_NE(debug.find("RemoveFile"), std::string::npos);
  EXPECT_NE(debug.find("CompactPointer"), std::string::npos);
}

// Test that encoding and decoding round-trip produces same encoding
TEST_F(VersionEditTest_476, EncodeDecodeRoundTrip_476) {
  VersionEdit edit;
  edit.SetLogNumber(42);
  edit.SetNextFile(100);
  edit.SetLastSequence(200);

  std::string encoded1;
  edit.EncodeTo(&encoded1);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded1));
  ASSERT_TRUE(s.ok());

  std::string encoded2;
  decoded.EncodeTo(&encoded2);

  EXPECT_EQ(encoded1, encoded2);
}

// Test DecodeFrom with corrupted/invalid data
TEST_F(VersionEditTest_476, DecodeFromCorruptedData_476) {
  VersionEdit edit;
  std::string corrupted_data = "this is definitely not valid encoded data";
  Status s = edit.DecodeFrom(Slice(corrupted_data));
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty data
TEST_F(VersionEditTest_476, DecodeFromEmptyData_476) {
  VersionEdit edit;
  std::string empty_data;
  Status s = edit.DecodeFrom(Slice(empty_data));
  // Empty data should be valid (no fields set)
  EXPECT_TRUE(s.ok());
}

// Test DecodeFrom with truncated data
TEST_F(VersionEditTest_476, DecodeFromTruncatedData_476) {
  VersionEdit edit;
  edit.SetLogNumber(42);
  edit.SetNextFile(100);

  std::string encoded;
  edit.EncodeTo(&encoded);

  // Truncate the encoded data
  std::string truncated = encoded.substr(0, encoded.size() / 2);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(truncated));
  // May or may not be ok depending on where truncation happens,
  // but if it fails it should return a non-ok status
  // We just verify it doesn't crash
}

// Test multiple AddFile operations
TEST_F(VersionEditTest_476, MultipleAddFiles_476) {
  VersionEdit edit;

  InternalKey smallest1, largest1, smallest2, largest2;
  smallest1.DecodeFrom(Slice("aaa\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  largest1.DecodeFrom(Slice("bbb\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  smallest2.DecodeFrom(Slice("ccc\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  largest2.DecodeFrom(Slice("ddd\x01\x00\x00\x00\x00\x00\x00\x00", 11));

  edit.AddFile(0, 1, 1024, smallest1, largest1);
  edit.AddFile(1, 2, 2048, smallest2, largest2);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  // Should contain references to both files
  EXPECT_NE(debug.find("AddFile"), std::string::npos);
}

// Test multiple RemoveFile operations
TEST_F(VersionEditTest_476, MultipleRemoveFiles_476) {
  VersionEdit edit;
  edit.RemoveFile(0, 1);
  edit.RemoveFile(1, 2);
  edit.RemoveFile(2, 3);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());

  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("RemoveFile"), std::string::npos);
}

// Test boundary values for log number
TEST_F(VersionEditTest_476, BoundaryLogNumber_476) {
  VersionEdit edit;
  edit.SetLogNumber(0);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());
}

// Test large values
TEST_F(VersionEditTest_476, LargeValues_476) {
  VersionEdit edit;
  edit.SetLogNumber(UINT64_MAX);
  edit.SetNextFile(UINT64_MAX);
  edit.SetLastSequence(UINT64_MAX >> 8);  // SequenceNumber is typically smaller

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());
}

// Test DebugString on empty edit
TEST_F(VersionEditTest_476, DebugStringEmpty_476) {
  VersionEdit edit;
  std::string debug = edit.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test EncodeTo appends to existing string
TEST_F(VersionEditTest_476, EncodeToAppendsToString_476) {
  VersionEdit edit;
  edit.SetLogNumber(42);

  std::string dst = "prefix";
  edit.EncodeTo(&dst);

  EXPECT_TRUE(dst.size() > 6);  // Should be longer than "prefix"
  EXPECT_EQ(dst.substr(0, 6), "prefix");
}

// Test that encoding empty edit produces non-empty string
// (at minimum there should be some encoded data)
TEST_F(VersionEditTest_476, EncodeEmptyEdit_476) {
  VersionEdit edit;
  std::string encoded;
  edit.EncodeTo(&encoded);
  // Even an empty edit should produce valid encodable data
  // (could be empty or have minimal encoding)

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());
}

// Test DecodeFrom with a single invalid tag byte
TEST_F(VersionEditTest_476, DecodeFromInvalidTag_476) {
  std::string data;
  // Use a very high varint value that doesn't correspond to any valid tag
  data.push_back(static_cast<char>(0x7f));  // varint for 127
  
  VersionEdit edit;
  Status s = edit.DecodeFrom(Slice(data));
  // This should fail since 127 is not a valid tag
  EXPECT_FALSE(s.ok());
}

// Test that RemoveFile for same file twice still encodes/decodes
TEST_F(VersionEditTest_476, RemoveSameFileTwice_476) {
  VersionEdit edit;
  edit.RemoveFile(0, 1);
  edit.RemoveFile(0, 1);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());
}

// Test comparator name with empty string
TEST_F(VersionEditTest_476, EmptyComparatorName_476) {
  VersionEdit edit;
  edit.SetComparatorName("");

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());
}

}  // namespace leveldb
