#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class VersionEditTest_342 : public ::testing::Test {
 protected:
  VersionEdit edit_;

  // Helper: encode a VersionEdit, then decode it and check round-trip
  void TestEncodeDecode(const VersionEdit& edit) {
    std::string encoded;
    edit.EncodeTo(&encoded);
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(Slice(encoded));
    ASSERT_TRUE(s.ok()) << s.ToString();

    // Re-encode decoded and compare
    std::string re_encoded;
    decoded.EncodeTo(&re_encoded);
    EXPECT_EQ(encoded, re_encoded);
  }
};

// Test that a default (empty) VersionEdit encodes and decodes successfully
TEST_F(VersionEditTest_342, EmptyEditEncodeDecode_342) {
  TestEncodeDecode(edit_);
}

// Test that setting comparator name round-trips correctly
TEST_F(VersionEditTest_342, ComparatorRoundTrip_342) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  TestEncodeDecode(edit_);
}

// Test that setting log number round-trips correctly
TEST_F(VersionEditTest_342, LogNumberRoundTrip_342) {
  edit_.SetLogNumber(123);
  TestEncodeDecode(edit_);
}

// Test that setting prev log number round-trips correctly
TEST_F(VersionEditTest_342, PrevLogNumberRoundTrip_342) {
  edit_.SetPrevLogNumber(456);
  TestEncodeDecode(edit_);
}

// Test that setting next file number round-trips correctly
TEST_F(VersionEditTest_342, NextFileNumberRoundTrip_342) {
  edit_.SetNextFile(789);
  TestEncodeDecode(edit_);
}

// Test that setting last sequence round-trips correctly
TEST_F(VersionEditTest_342, LastSequenceRoundTrip_342) {
  edit_.SetLastSequence(1000);
  TestEncodeDecode(edit_);
}

// Test that compact pointers round-trip correctly
TEST_F(VersionEditTest_342, CompactPointerRoundTrip_342) {
  InternalKey key("foo", 100, kTypeValue);
  edit_.SetCompactPointer(2, key);
  TestEncodeDecode(edit_);
}

// Test that adding a deleted file round-trips correctly
TEST_F(VersionEditTest_342, DeletedFileRoundTrip_342) {
  edit_.RemoveFile(3, 42);
  TestEncodeDecode(edit_);
}

// Test that adding a new file round-trips correctly
TEST_F(VersionEditTest_342, NewFileRoundTrip_342) {
  InternalKey smallest("bar", 50, kTypeValue);
  InternalKey largest("foo", 100, kTypeValue);
  edit_.AddFile(2, 10, 12345, smallest, largest);
  TestEncodeDecode(edit_);
}

// Test setting all fields at once
TEST_F(VersionEditTest_342, AllFieldsRoundTrip_342) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(10);
  edit_.SetPrevLogNumber(5);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(500);

  InternalKey cp_key("compact", 200, kTypeValue);
  edit_.SetCompactPointer(1, cp_key);

  edit_.RemoveFile(3, 42);

  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 999, kTypeValue);
  edit_.AddFile(4, 100, 65536, smallest, largest);

  TestEncodeDecode(edit_);
}

// Test that decoding an empty slice succeeds (empty edit)
TEST_F(VersionEditTest_342, DecodeEmptySlice_342) {
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(""));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test that decoding garbage data returns corruption
TEST_F(VersionEditTest_342, DecodeGarbageData_342) {
  VersionEdit decoded;
  // A tag value that is unknown (e.g., 255) encoded as a varint
  // 255 in varint32 is: 0xFF 0x01
  std::string bad_data;
  bad_data.push_back(static_cast<char>(0xFF));
  bad_data.push_back(static_cast<char>(0x01));
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that trailing bytes after valid data cause corruption
TEST_F(VersionEditTest_342, TrailingBytesCorruption_342) {
  std::string encoded;
  edit_.SetLogNumber(42);
  edit_.EncodeTo(&encoded);
  // Append extra invalid bytes
  encoded.push_back('\x00');
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that a truncated log number field causes corruption
TEST_F(VersionEditTest_342, TruncatedLogNumber_342) {
  // kLogNumber = 2 as a varint is just byte 0x02
  // After the tag, we need a varint64 for the log number but provide nothing
  std::string bad_data;
  bad_data.push_back(0x02);  // tag = kLogNumber
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that a truncated comparator field causes corruption
TEST_F(VersionEditTest_342, TruncatedComparator_342) {
  // kComparator = 1
  std::string bad_data;
  bad_data.push_back(0x01);  // tag = kComparator
  // Length-prefixed slice expects a length varint, but we provide nothing
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that a truncated next file number causes corruption
TEST_F(VersionEditTest_342, TruncatedNextFileNumber_342) {
  // kNextFileNumber = 3
  std::string bad_data;
  bad_data.push_back(0x03);  // tag = kNextFileNumber
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that a truncated last sequence causes corruption
TEST_F(VersionEditTest_342, TruncatedLastSequence_342) {
  // kLastSequence = 4
  std::string bad_data;
  bad_data.push_back(0x04);  // tag = kLastSequence
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that a truncated compact pointer causes corruption
TEST_F(VersionEditTest_342, TruncatedCompactPointer_342) {
  // kCompactPointer = 5
  std::string bad_data;
  bad_data.push_back(0x05);  // tag = kCompactPointer
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that a truncated deleted file causes corruption
TEST_F(VersionEditTest_342, TruncatedDeletedFile_342) {
  // kDeletedFile = 6
  std::string bad_data;
  bad_data.push_back(0x06);  // tag = kDeletedFile
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that a truncated new file causes corruption
TEST_F(VersionEditTest_342, TruncatedNewFile_342) {
  // kNewFile = 7
  std::string bad_data;
  bad_data.push_back(0x07);  // tag = kNewFile
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that a truncated prev log number causes corruption
TEST_F(VersionEditTest_342, TruncatedPrevLogNumber_342) {
  // kPrevLogNumber = 9
  std::string bad_data;
  bad_data.push_back(0x09);  // tag = kPrevLogNumber
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that multiple files can be added and round-trip
TEST_F(VersionEditTest_342, MultipleNewFiles_342) {
  InternalKey s1("a", 1, kTypeValue);
  InternalKey l1("b", 2, kTypeValue);
  InternalKey s2("c", 3, kTypeValue);
  InternalKey l2("d", 4, kTypeValue);
  edit_.AddFile(0, 1, 100, s1, l1);
  edit_.AddFile(1, 2, 200, s2, l2);
  TestEncodeDecode(edit_);
}

// Test that multiple deleted files can be added and round-trip
TEST_F(VersionEditTest_342, MultipleDeletedFiles_342) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(1, 2);
  edit_.RemoveFile(2, 3);
  TestEncodeDecode(edit_);
}

// Test large values for numeric fields
TEST_F(VersionEditTest_342, LargeNumericValues_342) {
  edit_.SetLogNumber(UINT64_MAX);
  edit_.SetPrevLogNumber(UINT64_MAX - 1);
  edit_.SetNextFile(UINT64_MAX - 2);
  edit_.SetLastSequence(UINT64_MAX - 3);
  TestEncodeDecode(edit_);
}

// Test that Clear resets the edit so it encodes as empty
TEST_F(VersionEditTest_342, ClearResetsEdit_342) {
  edit_.SetComparatorName("test");
  edit_.SetLogNumber(100);
  edit_.SetNextFile(200);
  edit_.SetLastSequence(300);

  edit_.Clear();

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit empty_edit;
  std::string empty_encoded;
  empty_edit.EncodeTo(&empty_encoded);

  EXPECT_EQ(encoded, empty_encoded);
}

// Test that DebugString returns a non-empty string for a populated edit
TEST_F(VersionEditTest_342, DebugStringNonEmpty_342) {
  edit_.SetComparatorName("test_comparator");
  edit_.SetLogNumber(42);
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test that DebugString works for an empty edit
TEST_F(VersionEditTest_342, DebugStringEmpty_342) {
  std::string debug = edit_.DebugString();
  // Should at least produce something (like "VersionEdit {}\n" or similar)
  // Just verify it doesn't crash
  EXPECT_FALSE(debug.empty());
}

// Test that zero values for numbers round-trip correctly
TEST_F(VersionEditTest_342, ZeroValues_342) {
  edit_.SetLogNumber(0);
  edit_.SetPrevLogNumber(0);
  edit_.SetNextFile(0);
  edit_.SetLastSequence(0);
  TestEncodeDecode(edit_);
}

// Test unknown tag (tag = 8 is not defined in the enum)
TEST_F(VersionEditTest_342, UnknownTag_342) {
  std::string bad_data;
  bad_data.push_back(0x08);  // tag = 8, which is not in the enum
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(bad_data));
  EXPECT_TRUE(s.IsCorruption()) << s.ToString();
}

// Test that encoding then decoding preserves the debug string
TEST_F(VersionEditTest_342, DebugStringPreservedAfterRoundTrip_342) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(10);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(500);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_EQ(edit_.DebugString(), decoded.DebugString());
}

// Test multiple compact pointers
TEST_F(VersionEditTest_342, MultipleCompactPointers_342) {
  InternalKey key1("abc", 100, kTypeValue);
  InternalKey key2("xyz", 200, kTypeValue);
  edit_.SetCompactPointer(0, key1);
  edit_.SetCompactPointer(3, key2);
  TestEncodeDecode(edit_);
}

// Test that a new file with file_size = 0 round-trips
TEST_F(VersionEditTest_342, NewFileZeroSize_342) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 1, 0, smallest, largest);
  TestEncodeDecode(edit_);
}

}  // namespace leveldb
