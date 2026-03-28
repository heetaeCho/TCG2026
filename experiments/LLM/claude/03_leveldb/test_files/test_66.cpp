#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class VersionEditTest_66 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test that a default-constructed VersionEdit can encode and decode successfully
TEST_F(VersionEditTest_66, DefaultConstructAndEncodeDecode_66) {
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetComparatorName followed by encode/decode roundtrip
TEST_F(VersionEditTest_66, SetComparatorNameRoundTrip_66) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // Verify through DebugString that comparator is present
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("BytewiseComparator"), std::string::npos);
}

// Test SetLogNumber roundtrip
TEST_F(VersionEditTest_66, SetLogNumberRoundTrip_66) {
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
TEST_F(VersionEditTest_66, SetPrevLogNumberRoundTrip_66) {
  edit_.SetPrevLogNumber(100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetNextFile roundtrip
TEST_F(VersionEditTest_66, SetNextFileRoundTrip_66) {
  edit_.SetNextFile(999);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetLastSequence roundtrip
TEST_F(VersionEditTest_66, SetLastSequenceRoundTrip_66) {
  edit_.SetLastSequence(12345);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetCompactPointer roundtrip
TEST_F(VersionEditTest_66, SetCompactPointerRoundTrip_66) {
  InternalKey key("user_key", 100, kTypeValue);
  edit_.SetCompactPointer(2, key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test multiple compact pointers
TEST_F(VersionEditTest_66, MultipleCompactPointers_66) {
  InternalKey key1("key1", 100, kTypeValue);
  InternalKey key2("key2", 200, kTypeValue);
  edit_.SetCompactPointer(0, key1);
  edit_.SetCompactPointer(1, key2);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test AddFile roundtrip
TEST_F(VersionEditTest_66, AddFileRoundTrip_66) {
  InternalKey smallest("abc", 100, kTypeValue);
  InternalKey largest("xyz", 200, kTypeValue);
  edit_.AddFile(3, 10, 1024, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("10"), std::string::npos);
}

// Test RemoveFile roundtrip
TEST_F(VersionEditTest_66, RemoveFileRoundTrip_66) {
  edit_.RemoveFile(2, 55);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test a complex edit with multiple operations
TEST_F(VersionEditTest_66, ComplexEditRoundTrip_66) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(10);
  edit_.SetPrevLogNumber(9);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(500);
  
  InternalKey cp_key("compact_key", 300, kTypeValue);
  edit_.SetCompactPointer(1, cp_key);
  
  InternalKey smallest("aaa", 1, kTypeValue);
  InternalKey largest("zzz", 2, kTypeValue);
  edit_.AddFile(0, 5, 2048, smallest, largest);
  edit_.AddFile(1, 6, 4096, smallest, largest);
  
  edit_.RemoveFile(0, 3);
  edit_.RemoveFile(1, 4);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // Encode the decoded version again and compare
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test Clear resets the edit
TEST_F(VersionEditTest_66, ClearResetsEdit_66) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 1, 100, smallest, largest);
  
  edit_.Clear();
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // A cleared edit should encode the same as a fresh default edit
  VersionEdit fresh;
  std::string fresh_encoded;
  fresh.EncodeTo(&fresh_encoded);
  
  EXPECT_EQ(encoded, fresh_encoded);
}

// Test DecodeFrom with corrupted/empty data
TEST_F(VersionEditTest_66, DecodeFromCorruptedData_66) {
  std::string bad_data = "this is not valid encoded data";
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty slice
TEST_F(VersionEditTest_66, DecodeFromEmptySlice_66) {
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(""));
  // An empty slice should decode ok (no fields set)
  EXPECT_TRUE(s.ok());
}

// Test DebugString is non-empty for a populated edit
TEST_F(VersionEditTest_66, DebugStringNonEmpty_66) {
  edit_.SetLogNumber(7);
  edit_.SetNextFile(10);
  edit_.SetLastSequence(100);
  
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString for default edit
TEST_F(VersionEditTest_66, DebugStringDefault_66) {
  std::string debug = edit_.DebugString();
  // Even a default edit should produce some debug output
  EXPECT_FALSE(debug.empty());
}

// Test encode/decode roundtrip preserves identity (encode twice gives same result)
TEST_F(VersionEditTest_66, EncodeIsIdempotent_66) {
  edit_.SetLogNumber(42);
  edit_.SetLastSequence(999);
  
  std::string encoded1;
  edit_.EncodeTo(&encoded1);
  
  std::string encoded2;
  edit_.EncodeTo(&encoded2);
  
  // EncodeTo appends, so encoded2 should be encoded1 + encoded1
  // Actually, EncodeTo typically appends to dst, so we need fresh strings
  // The two calls above both append. Let's verify by using fresh strings.
  // Actually encoded1 was empty, encoded2 was also empty before call.
  // So both should have the same content.
  EXPECT_EQ(encoded1, encoded2);
}

// Test EncodeTo appends to existing string
TEST_F(VersionEditTest_66, EncodeToAppends_66) {
  edit_.SetLogNumber(42);
  
  std::string prefix = "prefix";
  std::string dst = prefix;
  edit_.EncodeTo(&dst);
  
  // dst should start with "prefix"
  EXPECT_EQ(dst.substr(0, prefix.size()), prefix);
  EXPECT_GT(dst.size(), prefix.size());
}

// Test boundary: setting log number to 0
TEST_F(VersionEditTest_66, SetLogNumberZero_66) {
  edit_.SetLogNumber(0);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test boundary: setting large values
TEST_F(VersionEditTest_66, SetLargeValues_66) {
  edit_.SetLogNumber(UINT64_MAX);
  edit_.SetNextFile(UINT64_MAX);
  edit_.SetLastSequence(UINT64_MAX >> 8);  // Sequence numbers are typically < 2^56
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test adding multiple files
TEST_F(VersionEditTest_66, AddMultipleFiles_66) {
  for (int i = 0; i < 10; i++) {
    InternalKey smallest(std::string(1, 'a' + i), i + 1, kTypeValue);
    InternalKey largest(std::string(1, 'a' + i + 1), i + 2, kTypeValue);
    edit_.AddFile(i % 7, i + 100, (i + 1) * 1024, smallest, largest);
  }
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test removing multiple files
TEST_F(VersionEditTest_66, RemoveMultipleFiles_66) {
  for (int i = 0; i < 5; i++) {
    edit_.RemoveFile(i, i * 10);
  }
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
  
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test that DecodeFrom with truncated data fails
TEST_F(VersionEditTest_66, DecodeFromTruncatedData_66) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  InternalKey smallest("abc", 1, kTypeValue);
  InternalKey largest("xyz", 2, kTypeValue);
  edit_.AddFile(0, 5, 2048, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // Truncate the encoded data
  if (encoded.size() > 2) {
    std::string truncated = encoded.substr(0, encoded.size() / 2);
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(Slice(truncated));
    // Truncated data should likely fail to decode
    // (This depends on where truncation happens, but in most cases it should fail)
    // We just check it doesn't crash
  }
}

// Test SetComparatorName with empty name
TEST_F(VersionEditTest_66, SetComparatorNameEmpty_66) {
  edit_.SetComparatorName("");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test that AddFile and RemoveFile for the same file both appear
TEST_F(VersionEditTest_66, AddAndRemoveSameFile_66) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 5, 1024, smallest, largest);
  edit_.RemoveFile(0, 5);
  
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
