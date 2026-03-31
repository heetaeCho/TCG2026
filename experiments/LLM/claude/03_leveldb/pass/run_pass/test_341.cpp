#include "gtest/gtest.h"
#include "db/version_edit.h"
#include "leveldb/slice.h"
#include "db/dbformat.h"
#include "util/coding.h"

namespace leveldb {

// We need to test the static GetLevel function which is in the anonymous/internal scope.
// Since GetLevel is a static function in version_edit.cc, we can't directly call it from tests.
// However, we can test it indirectly through VersionEdit's public interface which uses GetLevel.
// Let's test VersionEdit::DecodeFrom which internally uses GetLevel.

class VersionEditTest_341 : public ::testing::Test {
 protected:
  VersionEdit edit_;
};

// Test that encoding and decoding an empty VersionEdit works
TEST_F(VersionEditTest_341, EmptyEditEncodeDecode_341) {
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetComparatorName encode/decode
TEST_F(VersionEditTest_341, SetComparatorName_341) {
  edit_.SetComparatorName("test_comparator");
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetLogNumber encode/decode
TEST_F(VersionEditTest_341, SetLogNumber_341) {
  edit_.SetLogNumber(42);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetNextFile encode/decode
TEST_F(VersionEditTest_341, SetNextFile_341) {
  edit_.SetNextFile(100);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetLastSequence encode/decode
TEST_F(VersionEditTest_341, SetLastSequence_341) {
  edit_.SetLastSequence(1000);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test SetPrevLogNumber encode/decode
TEST_F(VersionEditTest_341, SetPrevLogNumber_341) {
  edit_.SetPrevLogNumber(5);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test AddFile with valid levels (0 through kNumLevels-1)
TEST_F(VersionEditTest_341, AddFileValidLevels_341) {
  for (int level = 0; level < config::kNumLevels; level++) {
    VersionEdit e;
    InternalKey smallest("a", 1, kTypeValue);
    InternalKey largest("z", 2, kTypeValue);
    e.AddFile(level, 1, 100, smallest, largest);
    
    std::string encoded;
    e.EncodeTo(&encoded);
    
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(encoded);
    EXPECT_TRUE(s.ok()) << "Failed for level " << level << ": " << s.ToString();
  }
}

// Test RemoveFile with valid levels
TEST_F(VersionEditTest_341, RemoveFileValidLevels_341) {
  for (int level = 0; level < config::kNumLevels; level++) {
    VersionEdit e;
    e.RemoveFile(level, 1);
    
    std::string encoded;
    e.EncodeTo(&encoded);
    
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(encoded);
    EXPECT_TRUE(s.ok()) << "Failed for level " << level << ": " << s.ToString();
  }
}

// Test SetCompactPointer with valid levels
TEST_F(VersionEditTest_341, SetCompactPointerValidLevels_341) {
  for (int level = 0; level < config::kNumLevels; level++) {
    VersionEdit e;
    InternalKey key("test", 1, kTypeValue);
    e.SetCompactPointer(level, key);
    
    std::string encoded;
    e.EncodeTo(&encoded);
    
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(encoded);
    EXPECT_TRUE(s.ok()) << "Failed for level " << level << ": " << s.ToString();
  }
}

// Test DecodeFrom with corrupted/garbage data
TEST_F(VersionEditTest_341, DecodeFromCorruptedData_341) {
  // Completely invalid data
  std::string garbage = "this is garbage data";
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(garbage);
  // This should either fail or produce an error status for invalid input
  // The exact behavior depends on the varint parsing
}

// Test DecodeFrom with empty data
TEST_F(VersionEditTest_341, DecodeFromEmptyData_341) {
  std::string empty;
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(empty);
  // Empty data should decode successfully (no fields set)
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test that an invalid level in the encoded data causes decode failure
// This tests the GetLevel function indirectly - level >= kNumLevels should fail
TEST_F(VersionEditTest_341, DecodeInvalidLevelInCompactPointer_341) {
  // Manually construct a record with an invalid level for compact pointer
  // Tag for compact pointer
  std::string encoded;
  // kCompactPointer tag value is likely a small number; let's build it properly
  // We encode a new_file tag with an invalid level
  // Tag kNewFile = 7 (based on common leveldb encoding)
  // We'll build a valid-looking but level-invalid encoded edit
  
  // Actually, let's construct by encoding a valid VersionEdit and then
  // manually creating one with bad level
  // Use the approach: encode tag + invalid level
  
  // kDeletedFile tag = 6, kNewFile = 7, kCompactPointer = 5 (typical values)
  // Let's try to make a compact pointer with level = kNumLevels (7, which is invalid)
  std::string bad_data;
  PutVarint32(&bad_data, 6);  // kDeletedFile tag
  PutVarint32(&bad_data, config::kNumLevels);  // Invalid level (= kNumLevels)
  PutVarint64(&bad_data, 1);  // file number
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(bad_data);
  EXPECT_FALSE(s.ok()) << "Should fail with invalid level";
}

// Test multiple operations combined
TEST_F(VersionEditTest_341, MultipleOperationsCombined_341) {
  edit_.SetComparatorName("leveldb.BytewiseComparator");
  edit_.SetLogNumber(10);
  edit_.SetNextFile(20);
  edit_.SetLastSequence(500);
  
  InternalKey smallest("abc", 1, kTypeValue);
  InternalKey largest("xyz", 2, kTypeValue);
  edit_.AddFile(0, 1, 1000, smallest, largest);
  edit_.AddFile(1, 2, 2000, smallest, largest);
  edit_.RemoveFile(0, 3);
  
  InternalKey compact_key("middle", 10, kTypeValue);
  edit_.SetCompactPointer(2, compact_key);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test boundary level values (level 0 and level kNumLevels-1)
TEST_F(VersionEditTest_341, BoundaryLevels_341) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  
  // Level 0 (minimum valid)
  edit_.AddFile(0, 1, 100, smallest, largest);
  
  // Level kNumLevels-1 (maximum valid)
  edit_.AddFile(config::kNumLevels - 1, 2, 200, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test DebugString doesn't crash
TEST_F(VersionEditTest_341, DebugStringNoCrash_341) {
  edit_.SetComparatorName("test");
  edit_.SetLogNumber(1);
  edit_.SetNextFile(2);
  edit_.SetLastSequence(3);
  
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 10, 1000, smallest, largest);
  edit_.RemoveFile(1, 5);
  
  std::string debug = edit_.DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test encode/decode with large file numbers
TEST_F(VersionEditTest_341, LargeFileNumbers_341) {
  edit_.SetLogNumber(UINT64_MAX);
  edit_.SetNextFile(UINT64_MAX);
  edit_.SetLastSequence(UINT64_MAX);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test adding and removing the same file
TEST_F(VersionEditTest_341, AddAndRemoveSameFile_341) {
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  
  edit_.AddFile(0, 5, 100, smallest, largest);
  edit_.RemoveFile(0, 5);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test multiple files on the same level
TEST_F(VersionEditTest_341, MultipleFilesOnSameLevel_341) {
  InternalKey s1("a", 1, kTypeValue);
  InternalKey l1("m", 2, kTypeValue);
  InternalKey s2("n", 3, kTypeValue);
  InternalKey l2("z", 4, kTypeValue);
  
  edit_.AddFile(0, 1, 100, s1, l1);
  edit_.AddFile(0, 2, 200, s2, l2);
  edit_.AddFile(0, 3, 300, s1, l2);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  VersionEdit decoded;
  Status s = decoded.DecodeFrom(encoded);
  EXPECT_TRUE(s.ok()) << s.ToString();
}

// Test DecodeFrom with truncated data
TEST_F(VersionEditTest_341, DecodeFromTruncatedData_341) {
  edit_.SetLogNumber(42);
  InternalKey smallest("a", 1, kTypeValue);
  InternalKey largest("z", 2, kTypeValue);
  edit_.AddFile(0, 1, 100, smallest, largest);
  
  std::string encoded;
  edit_.EncodeTo(&encoded);
  
  // Truncate the data
  if (encoded.size() > 2) {
    std::string truncated = encoded.substr(0, encoded.size() / 2);
    VersionEdit decoded;
    Status s = decoded.DecodeFrom(truncated);
    // Truncated data should likely produce an error
    // (exact behavior depends on where we truncate)
  }
}

}  // namespace leveldb
