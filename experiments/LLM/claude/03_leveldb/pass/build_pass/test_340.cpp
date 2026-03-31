#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "util/coding.h"

namespace leveldb {

// Helper function to encode a length-prefixed slice into a string
static std::string EncodeLengthPrefixedSlice(const Slice& value) {
  std::string result;
  PutLengthPrefixedSlice(&result, value);
  return result;
}

// We test the static GetInternalKey function indirectly through VersionEdit
// since it's a static function in the .cc file. However, since VersionEdit
// uses GetInternalKey internally, we test through VersionEdit's EncodeTo/DecodeFrom.

class VersionEditTest_340 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test that a VersionEdit with no changes can be encoded and decoded
TEST_F(VersionEditTest_340, EmptyVersionEdit_340) {
  VersionEdit edit;
  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test setting and getting the comparator name
TEST_F(VersionEditTest_340, SetComparatorName_340) {
  VersionEdit edit;
  edit.SetComparatorName("leveldb.BytewiseComparator");

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test setting log number
TEST_F(VersionEditTest_340, SetLogNumber_340) {
  VersionEdit edit;
  edit.SetLogNumber(42);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test setting prev log number
TEST_F(VersionEditTest_340, SetPrevLogNumber_340) {
  VersionEdit edit;
  edit.SetPrevLogNumber(10);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test setting next file number
TEST_F(VersionEditTest_340, SetNextFile_340) {
  VersionEdit edit;
  edit.SetNextFile(100);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test setting last sequence
TEST_F(VersionEditTest_340, SetLastSequence_340) {
  VersionEdit edit;
  edit.SetLastSequence(500);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test adding a file with internal keys (exercises GetInternalKey during decode)
TEST_F(VersionEditTest_340, AddFile_340) {
  VersionEdit edit;
  InternalKey smallest("abc", 100, kTypeValue);
  InternalKey largest("xyz", 200, kTypeValue);
  edit.AddFile(2, 42, 1000, smallest, largest);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test removing a file
TEST_F(VersionEditTest_340, RemoveFile_340) {
  VersionEdit edit;
  edit.RemoveFile(3, 55);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test setting compact pointer with internal key
TEST_F(VersionEditTest_340, SetCompactPointer_340) {
  VersionEdit edit;
  InternalKey key("middle_key", 50, kTypeValue);
  edit.SetCompactPointer(1, key);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test multiple operations combined
TEST_F(VersionEditTest_340, MultipleOperations_340) {
  VersionEdit edit;
  edit.SetComparatorName("leveldb.BytewiseComparator");
  edit.SetLogNumber(10);
  edit.SetNextFile(20);
  edit.SetLastSequence(100);

  InternalKey smallest1("aaa", 1, kTypeValue);
  InternalKey largest1("bbb", 2, kTypeValue);
  edit.AddFile(0, 1, 500, smallest1, largest1);

  InternalKey smallest2("ccc", 3, kTypeValue);
  InternalKey largest2("ddd", 4, kTypeValue);
  edit.AddFile(1, 2, 600, smallest2, largest2);

  edit.RemoveFile(0, 5);

  InternalKey compact_key("eee", 10, kTypeValue);
  edit.SetCompactPointer(2, compact_key);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test decoding from corrupt/empty data
TEST_F(VersionEditTest_340, DecodeFromEmptyData_340) {
  VersionEdit edit;
  std::string empty;
  Status s = edit.DecodeFrom(empty);
  // Empty data should decode successfully (no tags to process)
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test decoding from corrupt data
TEST_F(VersionEditTest_340, DecodeFromCorruptData_340) {
  VersionEdit edit;
  // Create clearly corrupt data
  std::string corrupt_data = "this is definitely not valid version edit data";
  Status s = edit.DecodeFrom(corrupt_data);
  // This should fail because the tags won't be valid
  // The exact behavior depends on implementation, but likely returns an error
  // We just check it doesn't crash
}

// Test decoding truncated data for AddFile (which uses GetInternalKey)
TEST_F(VersionEditTest_340, DecodeFromTruncatedAddFile_340) {
  VersionEdit edit;
  InternalKey smallest("abc", 100, kTypeValue);
  InternalKey largest("xyz", 200, kTypeValue);
  edit.AddFile(2, 42, 1000, smallest, largest);

  std::string encoded;
  edit.EncodeTo(&encoded);

  // Truncate the data
  std::string truncated = encoded.substr(0, encoded.size() / 2);
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(truncated);
  // Should fail due to truncated internal key data
  EXPECT_FALSE(s.ok());
}

// Test with empty user key in InternalKey
TEST_F(VersionEditTest_340, AddFileWithEmptyUserKey_340) {
  VersionEdit edit;
  InternalKey smallest("", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(0, 1, 100, smallest, largest);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test with large sequence numbers
TEST_F(VersionEditTest_340, LargeSequenceNumbers_340) {
  VersionEdit edit;
  edit.SetLastSequence(UINT64_MAX - 1);
  edit.SetLogNumber(UINT64_MAX - 2);
  edit.SetNextFile(UINT64_MAX - 3);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test adding files at various levels
TEST_F(VersionEditTest_340, AddFilesAtMultipleLevels_340) {
  VersionEdit edit;
  for (int level = 0; level < 7; level++) {
    InternalKey smallest(std::string(1, 'a' + level), level + 1, kTypeValue);
    InternalKey largest(std::string(1, 'b' + level), level + 100, kTypeValue);
    edit.AddFile(level, level + 10, (level + 1) * 1000, smallest, largest);
  }

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test with kTypeDeletion value type in internal keys
TEST_F(VersionEditTest_340, AddFileWithDeletionType_340) {
  VersionEdit edit;
  InternalKey smallest("abc", 100, kTypeDeletion);
  InternalKey largest("xyz", 200, kTypeValue);
  edit.AddFile(1, 5, 2000, smallest, largest);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test VersionEdit::Clear
TEST_F(VersionEditTest_340, ClearResetsEdit_340) {
  VersionEdit edit;
  edit.SetComparatorName("test");
  edit.SetLogNumber(42);
  edit.SetNextFile(100);
  edit.SetLastSequence(500);

  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit.AddFile(0, 1, 100, smallest, largest);
  edit.RemoveFile(1, 2);

  edit.Clear();

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test InternalKey DecodeFrom with valid data (tests the path GetInternalKey uses)
TEST_F(VersionEditTest_340, InternalKeyDecodeFrom_340) {
  InternalKey original("test_key", 42, kTypeValue);
  Slice encoded = original.Encode();

  InternalKey decoded;
  EXPECT_TRUE(decoded.DecodeFrom(encoded));
  EXPECT_EQ(original.Encode().ToString(), decoded.Encode().ToString());
}

// Test InternalKey DecodeFrom with empty slice
TEST_F(VersionEditTest_340, InternalKeyDecodeFromEmpty_340) {
  InternalKey key;
  Slice empty_slice;
  // Decoding from empty might succeed (empty rep_) or fail depending on impl
  // We just ensure it doesn't crash
  key.DecodeFrom(empty_slice);
}

// Test encoding and decoding a single compact pointer
TEST_F(VersionEditTest_340, SingleCompactPointer_340) {
  VersionEdit edit;
  InternalKey key("compact_here", 999, kTypeValue);
  edit.SetCompactPointer(3, key);

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test round-trip encoding/decoding preserves data integrity for complex edit
TEST_F(VersionEditTest_340, RoundTripComplex_340) {
  VersionEdit edit;
  edit.SetComparatorName("my_comparator");
  edit.SetLogNumber(5);
  edit.SetPrevLogNumber(4);
  edit.SetNextFile(50);
  edit.SetLastSequence(1000);

  for (int i = 0; i < 5; i++) {
    std::string key_small = "key_" + std::to_string(i * 2);
    std::string key_large = "key_" + std::to_string(i * 2 + 1);
    InternalKey smallest(key_small, i * 10, kTypeValue);
    InternalKey largest(key_large, i * 10 + 5, kTypeValue);
    edit.AddFile(i % 3, i + 100, (i + 1) * 500, smallest, largest);
  }

  for (int i = 0; i < 3; i++) {
    edit.RemoveFile(i, i + 200);
  }

  std::string encoded;
  edit.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();

  // Re-encode the decoded version and compare
  std::string re_encoded;
  decoded.EncodeTo(&re_encoded);
  EXPECT_EQ(encoded, re_encoded);
}

}  // namespace leveldb
