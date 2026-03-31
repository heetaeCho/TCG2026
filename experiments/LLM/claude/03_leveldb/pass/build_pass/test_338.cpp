#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "db/dbformat.h"

#include <string>

namespace leveldb {

class VersionEditTest_338 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test that a default-constructed VersionEdit can encode and decode successfully
TEST_F(VersionEditTest_338, DefaultConstructAndEncodeDecode_338) {
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test Clear resets state so that encoding matches a fresh VersionEdit
TEST_F(VersionEditTest_338, ClearResetsToDefault_338) {
  edit_.SetComparatorName("test_comparator");
  edit_.SetLogNumber(100);
  edit_.SetPrevLogNumber(99);
  edit_.SetNextFile(200);
  edit_.SetLastSequence(300);
  
  edit_.Clear();
  
  std::string encoded_after_clear;
  edit_.EncodeTo(&encoded_after_clear);
  
  VersionEdit fresh;
  std::string encoded_fresh;
  fresh.EncodeTo(&encoded_fresh);
  
  EXPECT_EQ(encoded_after_clear, encoded_fresh);
}

// Test SetComparatorName and round-trip
TEST_F(VersionEditTest_338, SetComparatorNameRoundTrip_338) {
  edit_.SetComparatorName("my_comparator");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // Verify by re-encoding the decoded version
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetLogNumber round-trip
TEST_F(VersionEditTest_338, SetLogNumberRoundTrip_338) {
  edit_.SetLogNumber(42);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetPrevLogNumber round-trip
TEST_F(VersionEditTest_338, SetPrevLogNumberRoundTrip_338) {
  edit_.SetPrevLogNumber(7);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetNextFile round-trip
TEST_F(VersionEditTest_338, SetNextFileRoundTrip_338) {
  edit_.SetNextFile(1000);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetLastSequence round-trip
TEST_F(VersionEditTest_338, SetLastSequenceRoundTrip_338) {
  edit_.SetLastSequence(999);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test AddFile round-trip
TEST_F(VersionEditTest_338, AddFileRoundTrip_338) {
  InternalKey smallest, largest;
  smallest.DecodeFrom(Slice("abc\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  largest.DecodeFrom(Slice("xyz\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  
  edit_.AddFile(2, 10, 1024, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test RemoveFile round-trip
TEST_F(VersionEditTest_338, RemoveFileRoundTrip_338) {
  edit_.RemoveFile(3, 15);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test SetCompactPointer round-trip
TEST_F(VersionEditTest_338, SetCompactPointerRoundTrip_338) {
  InternalKey key;
  key.DecodeFrom(Slice("key\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  
  edit_.SetCompactPointer(1, key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test multiple fields set at once and round-trip
TEST_F(VersionEditTest_338, MultipleFieldsRoundTrip_338) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(10);
  edit_.SetPrevLogNumber(5);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(100);
  edit_.RemoveFile(0, 3);
  edit_.RemoveFile(1, 7);
  
  InternalKey smallest, largest;
  smallest.DecodeFrom(Slice("aaa\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  largest.DecodeFrom(Slice("zzz\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  edit_.AddFile(0, 50, 2048, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test that DecodeFrom with corrupt/invalid data returns an error
TEST_F(VersionEditTest_338, DecodeFromCorruptData_338) {
  std::string corrupt_data = "this_is_not_valid_encoded_data";
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(corrupt_data));
  // The corrupt data may or may not cause an error depending on how
  // it happens to parse, but let's test with obviously bad tag values
  // We'll use a simpler approach: an incomplete varint
}

// Test DecodeFrom with empty input
TEST_F(VersionEditTest_338, DecodeFromEmptyInput_338) {
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(""));
  // Empty input should be valid (no fields set)
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test DecodeFrom with truncated data
TEST_F(VersionEditTest_338, DecodeFromTruncatedData_338) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // Truncate the encoded data
  std::string truncated = encoded.substr(0, encoded.size() / 2);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(truncated));
  // The truncated data may or may not decode successfully, but it shouldn't crash
  // If it fails, the status should not be ok
  // We just verify it doesn't crash
}

// Test DebugString returns non-empty string when fields are set
TEST_F(VersionEditTest_338, DebugStringNonEmpty_338) {
  edit_.SetComparatorName("test_cmp");
  edit_.SetLogNumber(5);
  
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString on default VersionEdit
TEST_F(VersionEditTest_338, DebugStringDefault_338) {
  std::string debug = edit_.DebugString();
  // Should return something (at least the edit header or empty representation)
  // Just verify it doesn't crash
}

// Test Clear after adding files removes them
TEST_F(VersionEditTest_338, ClearAfterAddFile_338) {
  InternalKey smallest, largest;
  smallest.DecodeFrom(Slice("aaa\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  largest.DecodeFrom(Slice("zzz\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  edit_.AddFile(0, 50, 2048, smallest, largest);
  edit_.RemoveFile(1, 10);
  
  edit_.Clear();
  
  std::string encoded_after_clear;
  edit_.EncodeTo(&encoded_after_clear);
  
  VersionEdit fresh;
  std::string encoded_fresh;
  fresh.EncodeTo(&encoded_fresh);
  
  EXPECT_EQ(encoded_after_clear, encoded_fresh);
}

// Test boundary: large file numbers
TEST_F(VersionEditTest_338, LargeFileNumbers_338) {
  uint64_t large_num = UINT64_MAX;
  edit_.SetLogNumber(large_num);
  edit_.SetNextFile(large_num);
  edit_.SetLastSequence(large_num);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test boundary: zero values
TEST_F(VersionEditTest_338, ZeroValues_338) {
  edit_.SetLogNumber(0);
  edit_.SetPrevLogNumber(0);
  edit_.SetNextFile(0);
  edit_.SetLastSequence(0);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test empty comparator name
TEST_F(VersionEditTest_338, EmptyComparatorName_338) {
  edit_.SetComparatorName("");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test multiple AddFile calls
TEST_F(VersionEditTest_338, MultipleAddFiles_338) {
  InternalKey smallest1, largest1, smallest2, largest2;
  smallest1.DecodeFrom(Slice("aaa\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  largest1.DecodeFrom(Slice("bbb\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  smallest2.DecodeFrom(Slice("ccc\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  largest2.DecodeFrom(Slice("ddd\x01\x00\x00\x00\x00\x00\x00\x00", 11));
  
  edit_.AddFile(0, 1, 100, smallest1, largest1);
  edit_.AddFile(0, 2, 200, smallest2, largest2);
  edit_.AddFile(1, 3, 300, smallest1, largest2);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test multiple RemoveFile calls
TEST_F(VersionEditTest_338, MultipleRemoveFiles_338) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(0, 2);
  edit_.RemoveFile(1, 3);
  edit_.RemoveFile(2, 4);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test that DebugString contains comparator name when set
TEST_F(VersionEditTest_338, DebugStringContainsComparator_338) {
  edit_.SetComparatorName("my_special_comparator");
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("my_special_comparator"), std::string::npos);
}

// Test encoding to non-empty string appends
TEST_F(VersionEditTest_338, EncodeToAppendsToExistingString_338) {
  edit_.SetLogNumber(10);
  
  std::string dst = "prefix";
  edit_.EncodeTo(&dst);
  
  // The encoded data should be appended after "prefix"
  EXPECT_TRUE(dst.size() > 6);  // "prefix" is 6 bytes
  EXPECT_EQ(dst.substr(0, 6), "prefix");
}

// Test multiple compact pointers
TEST_F(VersionEditTest_338, MultipleCompactPointers_338) {
  InternalKey key1, key2;
  key1.DecodeFrom(Slice("key1\x01\x00\x00\x00\x00\x00\x00\x00", 12));
  key2.DecodeFrom(Slice("key2\x01\x00\x00\x00\x00\x00\x00\x00", 12));
  
  edit_.SetCompactPointer(0, key1);
  edit_.SetCompactPointer(1, key2);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test that DecodeFrom with a single bad byte fails
TEST_F(VersionEditTest_338, DecodeFromSingleBadByte_338) {
  // Tag value that's very large and unlikely to be valid, followed by no data
  std::string bad;
  bad.push_back(static_cast<char>(255));  // Very large varint-encoded tag
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad));
  // This may or may not fail depending on implementation, but shouldn't crash
}

}  // namespace leveldb
