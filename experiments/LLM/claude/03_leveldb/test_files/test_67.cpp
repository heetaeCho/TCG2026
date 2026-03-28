#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "leveldb/slice.h"

namespace leveldb {

class VersionEditTest_67 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test that a freshly constructed VersionEdit can encode/decode without error
TEST_F(VersionEditTest_67, DefaultConstructionEncodeDecode_67) {
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test AddFile and round-trip through EncodeTo/DecodeFrom
TEST_F(VersionEditTest_67, AddFileSingleEntry_67) {
  InternalKey smallest("abc", 1, kTypeValue);
  InternalKey largest("xyz", 2, kTypeValue);
  
  edit_.AddFile(2, 100, 2048, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // Verify via DebugString that the file info is preserved
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("100"), std::string::npos);
  EXPECT_NE(debug.find("2048"), std::string::npos);
}

// Test AddFile with multiple files
TEST_F(VersionEditTest_67, AddFileMultipleEntries_67) {
  InternalKey smallest1("a", 1, kTypeValue);
  InternalKey largest1("b", 2, kTypeValue);
  InternalKey smallest2("c", 3, kTypeValue);
  InternalKey largest2("d", 4, kTypeValue);
  
  edit_.AddFile(0, 10, 1000, smallest1, largest1);
  edit_.AddFile(1, 20, 2000, smallest2, largest2);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("10"), std::string::npos);
  EXPECT_NE(debug.find("20"), std::string::npos);
}

// Test RemoveFile and round-trip
TEST_F(VersionEditTest_67, RemoveFile_67) {
  edit_.RemoveFile(3, 42);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("42"), std::string::npos);
}

// Test SetComparatorName round-trip
TEST_F(VersionEditTest_67, SetComparatorName_67) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("leveldb.BytewiseComparator"), std::string::npos);
}

// Test SetLogNumber round-trip
TEST_F(VersionEditTest_67, SetLogNumber_67) {
  edit_.SetLogNumber(123);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("123"), std::string::npos);
}

// Test SetPrevLogNumber round-trip
TEST_F(VersionEditTest_67, SetPrevLogNumber_67) {
  edit_.SetPrevLogNumber(456);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetNextFile round-trip
TEST_F(VersionEditTest_67, SetNextFile_67) {
  edit_.SetNextFile(789);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("789"), std::string::npos);
}

// Test SetLastSequence round-trip
TEST_F(VersionEditTest_67, SetLastSequence_67) {
  edit_.SetLastSequence(999);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("999"), std::string::npos);
}

// Test SetCompactPointer round-trip
TEST_F(VersionEditTest_67, SetCompactPointer_67) {
  InternalKey key("compact_key", 10, kTypeValue);
  edit_.SetCompactPointer(3, key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test Clear resets the edit
TEST_F(VersionEditTest_67, Clear_67) {
  edit_.SetLogNumber(100);
  edit_.SetNextFile(200);
  edit_.SetLastSequence(300);
  
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 50, 500, smallest, largest);
  edit_.RemoveFile(1, 60);
  
  edit_.Clear();
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  // After clear, debug string should be minimal
  std::string debug = decoded.DebugString();
  // The file number 50 and log number 100 should not appear
  EXPECT_EQ(debug.find("50"), std::string::npos);
}

// Test DecodeFrom with corrupt/empty data
TEST_F(VersionEditTest_67, DecodeFromCorruptData_67) {
  std::string corrupt_data = "this is not valid encoded data";
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(corrupt_data));
  EXPECT_FALSE(s.ok());
}

// Test DecodeFrom with empty slice
TEST_F(VersionEditTest_67, DecodeFromEmptySlice_67) {
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(""));
  // Empty data should decode as an empty edit successfully
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test DebugString is non-empty
TEST_F(VersionEditTest_67, DebugStringNonEmpty_67) {
  edit_.SetLogNumber(42);
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test adding a file at level 0 boundary
TEST_F(VersionEditTest_67, AddFileLevel0_67) {
  InternalKey smallest("key1", 1, kTypeValue);
  InternalKey largest("key2", 2, kTypeValue);
  edit_.AddFile(0, 1, 100, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test adding file with zero file size
TEST_F(VersionEditTest_67, AddFileZeroSize_67) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("b", 2, kTypeValue);
  edit_.AddFile(0, 5, 0, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test setting all fields at once
TEST_F(VersionEditTest_67, SetAllFields_67) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(10);
  edit_.SetPrevLogNumber(9);
  edit_.SetNextFile(100);
  edit_.SetLastSequence(500);
  
  InternalKey cp_key("cp", 5, kTypeValue);
  edit_.SetCompactPointer(2, cp_key);
  
  InternalKey smallest("aaa", 1, kTypeValue);
  InternalKey largest("zzz", 100, kTypeValue);
  edit_.AddFile(3, 77, 4096, smallest, largest);
  
  edit_.RemoveFile(1, 55);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
  
  std::string debug = decoded.DebugString();
  EXPECT_NE(debug.find("leveldb.BytewiseComparator"), std::string::npos);
  EXPECT_NE(debug.find("77"), std::string::npos);
  EXPECT_NE(debug.find("55"), std::string::npos);
}

// Test multiple encode/decode cycles produce consistent results
TEST_F(VersionEditTest_67, MultipleEncodeDecodeCycles_67) {
  edit_.SetLogNumber(42);
  edit_.SetNextFile(100);
  
  InternalKey smallest("start", 1, kTypeValue);
  InternalKey largest("end", 2, kTypeValue);
  edit_.AddFile(1, 33, 1024, smallest, largest);
  
  std::string encoded1;
  edit_.EncodeTo(&encoded1);
  
  VersionEdit decoded1;
  ASSERT_TRUE(decoded1.DecodeFrom(Slice(encoded1)).ok());
  
  std::string encoded2;
  decoded1.EncodeTo(&encoded2);
  
  // The two encodings should be identical
  EXPECT_EQ(encoded1, encoded2);
}

// Test adding file with large file number and size
TEST_F(VersionEditTest_67, AddFileLargeValues_67) {
  InternalKey smallest("min", 1, kTypeValue);
  InternalKey largest("max", UINT64_MAX >> 8, kTypeValue);
  
  uint64_t large_file_num = 1ULL << 40;
  uint64_t large_file_size = 1ULL << 50;
  
  edit_.AddFile(6, large_file_num, large_file_size, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test RemoveFile called multiple times for different files
TEST_F(VersionEditTest_67, RemoveMultipleFiles_67) {
  edit_.RemoveFile(0, 1);
  edit_.RemoveFile(0, 2);
  edit_.RemoveFile(1, 3);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(Slice(encoded));
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test that DebugString of default edit is valid
TEST_F(VersionEditTest_67, DefaultDebugString_67) {
  std::string debug = edit_.DebugString();
  // Should not crash and should return something
  EXPECT_FALSE(debug.empty());
}

}  // namespace leveldb
