#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

namespace leveldb {

class VersionEditTest_343 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test that a default-constructed VersionEdit produces a minimal DebugString
TEST_F(VersionEditTest_343, DefaultDebugString_343) {
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("VersionEdit {"), std::string::npos);
  EXPECT_NE(debug.find("}"), std::string::npos);
  // Should not contain any fields
  EXPECT_EQ(debug.find("Comparator:"), std::string::npos);
  EXPECT_EQ(debug.find("LogNumber:"), std::string::npos);
  EXPECT_EQ(debug.find("PrevLogNumber:"), std::string::npos);
  EXPECT_EQ(debug.find("NextFile:"), std::string::npos);
  EXPECT_EQ(debug.find("LastSeq:"), std::string::npos);
  EXPECT_EQ(debug.find("CompactPointer:"), std::string::npos);
  EXPECT_EQ(debug.find("RemoveFile:"), std::string::npos);
  EXPECT_EQ(debug.find("AddFile:"), std::string::npos);
}

// Test SetComparatorName appears in DebugString
TEST_F(VersionEditTest_343, SetComparatorName_343) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("Comparator: leveldb.BytewiseComparator"), std::string::npos);
}

// Test SetLogNumber appears in DebugString
TEST_F(VersionEditTest_343, SetLogNumber_343) {
  edit_.SetLogNumber(42);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("LogNumber: 42"), std::string::npos);
}

// Test SetPrevLogNumber appears in DebugString
TEST_F(VersionEditTest_343, SetPrevLogNumber_343) {
  edit_.SetPrevLogNumber(10);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("PrevLogNumber: 10"), std::string::npos);
}

// Test SetNextFile appears in DebugString
TEST_F(VersionEditTest_343, SetNextFile_343) {
  edit_.SetNextFile(100);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("NextFile: 100"), std::string::npos);
}

// Test SetLastSequence appears in DebugString
TEST_F(VersionEditTest_343, SetLastSequence_343) {
  edit_.SetLastSequence(999);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("LastSeq: 999"), std::string::npos);
}

// Test RemoveFile appears in DebugString
TEST_F(VersionEditTest_343, RemoveFile_343) {
  edit_.RemoveFile(3, 55);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("RemoveFile:"), std::string::npos);
  EXPECT_NE(debug.find("3"), std::string::npos);
  EXPECT_NE(debug.find("55"), std::string::npos);
}

// Test AddFile appears in DebugString
TEST_F(VersionEditTest_343, AddFile_343) {
  InternalKey smallest("abc", 1, kTypeValue);
  InternalKey largest("xyz", 2, kTypeValue);
  edit_.AddFile(2, 100, 2048, smallest, largest);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("AddFile:"), std::string::npos);
  EXPECT_NE(debug.find("100"), std::string::npos);
  EXPECT_NE(debug.find("2048"), std::string::npos);
}

// Test EncodeTo and DecodeFrom round-trip with all fields set
TEST_F(VersionEditTest_343, EncodeDecodeRoundTrip_343) {
  edit_.SetComparatorName("test_comparator");
  edit_.SetLogNumber(123);
  edit_.SetPrevLogNumber(122);
  edit_.SetNextFile(456);
  edit_.SetLastSequence(789);
  
  InternalKey smallest("aaa", 1, kTypeValue);
  InternalKey largest("zzz", 2, kTypeValue);
  edit_.AddFile(1, 10, 1024, smallest, largest);
  edit_.RemoveFile(2, 20);

  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Verify by comparing debug strings
  EXPECT_EQ(edit_.DebugString(), decoded.DebugString());
}

// Test Clear resets all fields
TEST_F(VersionEditTest_343, ClearResetsAllFields_343) {
  edit_.SetComparatorName("test");
  edit_.SetLogNumber(1);
  edit_.SetPrevLogNumber(2);
  edit_.SetNextFile(3);
  edit_.SetLastSequence(4);
  InternalKey k1("a", 1, kTypeValue);
  InternalKey k2("z", 2, kTypeValue);
  edit_.AddFile(0, 5, 100, k1, k2);
  edit_.RemoveFile(0, 6);

  edit_.Clear();

  std::string debug = edit_.DebugString();
  EXPECT_EQ(debug.find("Comparator:"), std::string::npos);
  EXPECT_EQ(debug.find("LogNumber:"), std::string::npos);
  EXPECT_EQ(debug.find("PrevLogNumber:"), std::string::npos);
  EXPECT_EQ(debug.find("NextFile:"), std::string::npos);
  EXPECT_EQ(debug.find("LastSeq:"), std::string::npos);
  EXPECT_EQ(debug.find("AddFile:"), std::string::npos);
  EXPECT_EQ(debug.find("RemoveFile:"), std::string::npos);
}

// Test DecodeFrom with empty data returns error
TEST_F(VersionEditTest_343, DecodeFromEmptyData_343) {
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(""));
  // Empty data should decode ok since there are no required tags
  // (just end of input)
  EXPECT_TRUE(s.ok());
}

// Test DecodeFrom with corrupted data returns error
TEST_F(VersionEditTest_343, DecodeFromCorruptedData_343) {
  VersionEdit decoded;
  // Provide some garbage data
  std::string bad_data = "\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff";
  Status s = decoded.DecodeFrom(Slice(bad_data));
  // This should likely fail
  EXPECT_FALSE(s.ok());
}

// Test EncodeTo and DecodeFrom with only comparator
TEST_F(VersionEditTest_343, EncodeDecodeComparatorOnly_343) {
  edit_.SetComparatorName("my_cmp");
  std::string encoded;
  edit_.EncodeTo(&encoded);

  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(s.ok());
  EXPECT_NE(decoded.DebugString().find("Comparator: my_cmp"), std::string::npos);
}

// Test multiple AddFile calls
TEST_F(VersionEditTest_343, MultipleAddFiles_343) {
  InternalKey s1("a", 1, kTypeValue);
  InternalKey l1("b", 2, kTypeValue);
  InternalKey s2("c", 3, kTypeValue);
  InternalKey l2("d", 4, kTypeValue);

  edit_.AddFile(0, 1, 100, s1, l1);
  edit_.AddFile(1, 2, 200, s2, l2);

  std::string debug = edit_.DebugString();
  // Should have two AddFile entries
  size_t first = debug.find("AddFile:");
  EXPECT_NE(first, std::string::npos);
  size_t second = debug.find("AddFile:", first + 1);
  EXPECT_NE(second, std::string::npos);
}

// Test multiple RemoveFile calls
TEST_F(VersionEditTest_343, MultipleRemoveFiles_343) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(1, 2);
  edit_.RemoveFile(2, 3);

  std::string debug = edit_.DebugString();
  size_t count = 0;
  size_t pos = 0;
  while ((pos = debug.find("RemoveFile:", pos)) != std::string::npos) {
    count++;
    pos++;
  }
  EXPECT_EQ(count, 3u);
}

// Test duplicate RemoveFile entries (same level and file)
TEST_F(VersionEditTest_343, DuplicateRemoveFile_343) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(0, 1);  // duplicate

  std::string debug = edit_.DebugString();
  // DeletedFileSet is a set, so duplicates should be removed
  size_t count = 0;
  size_t pos = 0;
  while ((pos = debug.find("RemoveFile:", pos)) != std::string::npos) {
    count++;
    pos++;
  }
  EXPECT_EQ(count, 1u);
}

// Test SetLogNumber with zero
TEST_F(VersionEditTest_343, SetLogNumberZero_343) {
  edit_.SetLogNumber(0);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("LogNumber: 0"), std::string::npos);
}

// Test SetLastSequence with max value
TEST_F(VersionEditTest_343, SetLastSequenceMaxValue_343) {
  edit_.SetLastSequence(UINT64_MAX);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("LastSeq:"), std::string::npos);
}

// Test round-trip with all fields populated
TEST_F(VersionEditTest_343, FullRoundTrip_343) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(100);
  edit_.SetPrevLogNumber(99);
  edit_.SetNextFile(200);
  edit_.SetLastSequence(5000);

  InternalKey ck("compact_key", 10, kTypeValue);
  edit_.SetCompactPointer(3, ck);

  InternalKey s1("start", 1, kTypeValue);
  InternalKey l1("end", 2, kTypeValue);
  edit_.AddFile(0, 50, 4096, s1, l1);

  edit_.RemoveFile(1, 30);

  std::string encoded;
  edit_.EncodeTo(&encoded);
  EXPECT_FALSE(encoded.empty());

  VersionEdit decoded;
  Status status = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(status.ok()) << status.ToString();

  EXPECT_EQ(edit_.DebugString(), decoded.DebugString());
}

// Test EncodeTo produces non-empty output for empty edit
TEST_F(VersionEditTest_343, EncodeToEmpty_343) {
  std::string encoded;
  edit_.EncodeTo(&encoded);
  // Even an empty edit might produce some bytes or might be empty
  // We just verify it doesn't crash and can be decoded back
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok());
}

// Test SetCompactPointer appears in DebugString
TEST_F(VersionEditTest_343, SetCompactPointer_343) {
  InternalKey key("test_key", 100, kTypeValue);
  edit_.SetCompactPointer(5, key);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("CompactPointer:"), std::string::npos);
  EXPECT_NE(debug.find("5"), std::string::npos);
}

// Test multiple compact pointers
TEST_F(VersionEditTest_343, MultipleCompactPointers_343) {
  InternalKey k1("a", 1, kTypeValue);
  InternalKey k2("b", 2, kTypeValue);
  edit_.SetCompactPointer(0, k1);
  edit_.SetCompactPointer(1, k2);

  std::string debug = edit_.DebugString();
  size_t count = 0;
  size_t pos = 0;
  while ((pos = debug.find("CompactPointer:", pos)) != std::string::npos) {
    count++;
    pos++;
  }
  EXPECT_EQ(count, 2u);
}

// Test AddFile with file_size zero
TEST_F(VersionEditTest_343, AddFileZeroSize_343) {
  InternalKey s("a", 1, kTypeValue);
  InternalKey l("z", 2, kTypeValue);
  edit_.AddFile(0, 1, 0, s, l);
  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("AddFile:"), std::string::npos);

  // Round-trip test
  std::string encoded;
  edit_.EncodeTo(&encoded);
  VersionEdit decoded;
  Status status = decoded.DecodeFrom(Slice(encoded));
  ASSERT_TRUE(status.ok());
  EXPECT_EQ(edit_.DebugString(), decoded.DebugString());
}

// Test Clear followed by setting new values
TEST_F(VersionEditTest_343, ClearThenSet_343) {
  edit_.SetLogNumber(100);
  edit_.Clear();
  edit_.SetLogNumber(200);

  std::string debug = edit_.DebugString();
  EXPECT_NE(debug.find("LogNumber: 200"), std::string::npos);
  EXPECT_EQ(debug.find("LogNumber: 100"), std::string::npos);
}

}  // namespace leveldb
