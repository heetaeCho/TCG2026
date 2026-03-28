#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class VersionEditTest_339 : public ::testing::Test {
 protected:
  void SetUp() override { edit_.Clear(); }

  VersionEdit edit_;
};

// Test that a default (empty) VersionEdit can encode and decode successfully
TEST_F(VersionEditTest_339, EmptyVersionEdit_339) {
  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test encode/decode round-trip with comparator name set
TEST_F(VersionEditTest_339, SetComparatorRoundTrip_339) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify by re-encoding the decoded version and comparing
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test encode/decode round-trip with log number set
TEST_F(VersionEditTest_339, SetLogNumberRoundTrip_339) {
  edit_.SetLogNumber(42);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test encode/decode round-trip with prev log number set
TEST_F(VersionEditTest_339, SetPrevLogNumberRoundTrip_339) {
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

// Test encode/decode round-trip with next file number set
TEST_F(VersionEditTest_339, SetNextFileRoundTrip_339) {
  edit_.SetNextFile(1000);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test encode/decode round-trip with last sequence set
TEST_F(VersionEditTest_339, SetLastSequenceRoundTrip_339) {
  edit_.SetLastSequence(12345);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test encode/decode round-trip with compact pointer
TEST_F(VersionEditTest_339, SetCompactPointerRoundTrip_339) {
  InternalKey key("testkey", 100, kTypeValue);
  edit_.SetCompactPointer(3, key);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test encode/decode round-trip with deleted file
TEST_F(VersionEditTest_339, RemoveFileRoundTrip_339) {
  edit_.RemoveFile(2, 555);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test encode/decode round-trip with new file added
TEST_F(VersionEditTest_339, AddFileRoundTrip_339) {
  InternalKey smallest("abc", 1, kTypeValue);
  InternalKey largest("xyz", 2, kTypeValue);
  edit_.AddFile(3, 100, 2048, smallest, largest);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test encode/decode round-trip with all fields set
TEST_F(VersionEditTest_339, AllFieldsRoundTrip_339) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(10);
  edit_.SetPrevLogNumber(5);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(500);

  InternalKey compact_key("compact", 50, kTypeValue);
  edit_.SetCompactPointer(1, compact_key);

  edit_.RemoveFile(0, 7);
  edit_.RemoveFile(1, 8);

  InternalKey smallest1("aaa", 1, kTypeValue);
  InternalKey largest1("bbb", 2, kTypeValue);
  edit_.AddFile(0, 100, 4096, smallest1, largest1);

  InternalKey smallest2("ccc", 3, kTypeValue);
  InternalKey largest2("ddd", 4, kTypeValue);
  edit_.AddFile(1, 101, 8192, smallest2, largest2);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test that Clear resets the edit to empty state
TEST_F(VersionEditTest_339, ClearResetsState_339) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  edit_.SetLastSequence(999);
  edit_.RemoveFile(0, 5);

  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 10, 1024, smallest, largest);

  edit_.Clear();

  std::string encoded_after_clear;
  edit_.EncodeTo(&encoded_after_clear);

  VersionEdit empty_edit;
  std::string encoded_empty;
  empty_edit.EncodeTo(&encoded_empty);

  EXPECT_EQ(encoded_after_clear, encoded_empty);
}

// Test DecodeFrom with corrupted/invalid data
TEST_F(VersionEditTest_339, DecodeFromCorruptedData_339) {
  std::string bad_data = "this is not valid encoded data";
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  // The data is garbage, so decoding should fail
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty data
TEST_F(VersionEditTest_339, DecodeFromEmptyData_339) {
  std::string empty_data;
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(empty_data));
  // Empty data should decode successfully as an empty edit
  EXPECT_TRUE(s.ok());
}

// Test encode/decode with large values
TEST_F(VersionEditTest_339, LargeValuesRoundTrip_339) {
  edit_.SetLogNumber(UINT64_MAX);
  edit_.SetPrevLogNumber(UINT64_MAX - 1);
  edit_.SetNextFile(UINT64_MAX - 2);
  edit_.SetLastSequence(UINT64_MAX - 3);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test encode/decode with zero values
TEST_F(VersionEditTest_339, ZeroValuesRoundTrip_339) {
  edit_.SetLogNumber(0);
  edit_.SetPrevLogNumber(0);
  edit_.SetNextFile(0);
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

// Test multiple compact pointers
TEST_F(VersionEditTest_339, MultipleCompactPointersRoundTrip_339) {
  InternalKey key1("key1", 10, kTypeValue);
  InternalKey key2("key2", 20, kTypeValue);
  InternalKey key3("key3", 30, kTypeValue);
  edit_.SetCompactPointer(0, key1);
  edit_.SetCompactPointer(1, key2);
  edit_.SetCompactPointer(2, key3);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test multiple deleted files
TEST_F(VersionEditTest_339, MultipleDeletedFilesRoundTrip_339) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(0, 2);
  edit_.RemoveFile(1, 3);
  edit_.RemoveFile(2, 4);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

// Test multiple new files
TEST_F(VersionEditTest_339, MultipleNewFilesRoundTrip_339) {
  for (int i = 0; i < 5; ++i) {
    InternalKey smallest(std::string(1, 'a' + i), i + 1, kTypeValue);
    InternalKey largest(std::string(1, 'a' + i + 1), i + 2, kTypeValue);
    edit_.AddFile(i % 3, 100 + i, 1024 * (i + 1), smallest, largest);
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

// Test DebugString returns non-empty string when fields are set
TEST_F(VersionEditTest_339, DebugStringNonEmpty_339) {
  edit_.SetComparatorName("test_cmp");
  edit_.SetLogNumber(42);

  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test DebugString on empty edit
TEST_F(VersionEditTest_339, DebugStringEmpty_339) {
  std::string debug = edit_.DebugString();
  // Even an empty edit should produce some string (at minimum "VersionEdit {}\n" or similar)
  // We just verify it doesn't crash and returns something
  EXPECT_FALSE(debug.empty());
}

// Test EncodeTo appends to existing string
TEST_F(VersionEditTest_339, EncodeToAppendsToExistingString_339) {
  edit_.SetLogNumber(42);

  std::string prefix = "PREFIX";
  std::string dst = prefix;
  edit_.EncodeTo(&dst);

  // The encoded data should be appended after PREFIX
  EXPECT_GE(dst.size(), prefix.size());
  EXPECT_EQ(dst.substr(0, prefix.size()), prefix);

  // Decode should work from the appended portion
  Slice encoded_portion(dst.data() + prefix.size(),
                        dst.size() - prefix.size());
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded_portion);
  ASSERT_TRUE(s.ok()) << s.ToString();

  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);

  std::string original_encoded;
  edit_.EncodeTo(&original_encoded);
  EXPECT_EQ(original_encoded, re_encoded);
}

// Test DecodeFrom with truncated data (partial encoding)
TEST_F(VersionEditTest_339, DecodeFromTruncatedData_339) {
  edit_.SetComparatorName("test_comparator");
  edit_.SetLogNumber(100);
  edit_.SetNextFile(200);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  // Truncate encoded data
  ASSERT_GT(encoded.size(), 2u);
  std::string truncated = encoded.substr(0, encoded.size() / 2);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(truncated));
  // Truncated data should cause a decode error
  EXPECT_FALSE(s.ok());
}

// Test that removing the same file twice still round-trips
// (DeletedFileSet is a set, so duplicates are merged)
TEST_F(VersionEditTest_339, DuplicateRemoveFile_339) {
  edit_.RemoveFile(0, 100);
  edit_.RemoveFile(0, 100);  // duplicate

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Re-encode and verify consistency
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  // Since deleted_files_ is a set, the duplicate should be eliminated
  // Both encoded and re_encoded should be the same (set only stores unique entries)
  EXPECT_EQ(encoded, re_encoded);
}

// Test setting comparator name to empty string
TEST_F(VersionEditTest_339, EmptyComparatorName_339) {
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

// Test with an unknown tag byte injected
TEST_F(VersionEditTest_339, DecodeFromUnknownTag_339) {
  // Create a string with an unknown tag value
  std::string bad_data;
  // Tag 99 is not a known tag
  // Using PutVarint32 equivalent: varint for 99 is single byte 99
  bad_data.push_back(static_cast<char>(99));
  bad_data.push_back(0);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_FALSE(s.ok());
}

}  // namespace leveldb
