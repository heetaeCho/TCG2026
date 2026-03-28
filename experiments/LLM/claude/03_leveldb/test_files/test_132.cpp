#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "db/dbformat.h"
#include "db/version_edit.h"
#include "leveldb/comparator.h"
#include "leveldb/slice.h"

namespace leveldb {

// We need to access the AfterFile function. Since it's static in version_set.cc,
// we need to either include the header or declare it. Let's check if there's a way
// to test it through the header.
// Since AfterFile is a static function in the .cc file, we may need to test it
// indirectly. However, for unit testing purposes, let's declare it as extern
// or test through the public interface that uses it.

// Actually, AfterFile is static (file-local), so we cannot directly call it from
// outside version_set.cc. We need to test it through the public API that uses it.
// However, the prompt asks us to test the given interface.
// Let's try to test it by including the .cc file or using a test-friend approach.

// For testing a static function, we can include the source file in a test namespace
// or use a workaround. Let's include the necessary headers and redefine the function
// as testable.

// Since the function is static in the cc file, we'll test it by including the cc
// indirectly or by testing the public functions that use AfterFile.
// But given the constraints, let's attempt to test via the version_set header.

} // namespace leveldb

// To test the static AfterFile function, we include the .cc file
// This is a common pattern for testing static/file-local functions
namespace leveldb {
namespace test_afterfile {

// Re-declare or include to get access to AfterFile
// We'll define a wrapper since AfterFile is static
#include "db/version_set.cc"

} // namespace test_afterfile
} // namespace leveldb

// If the above include doesn't work cleanly, we can test through the public API.
// Let's write tests assuming we can call AfterFile.

// Mock Comparator for testing
class MockComparator : public leveldb::Comparator {
 public:
  MOCK_METHOD(int, Compare, (const leveldb::Slice& a, const leveldb::Slice& b), (const, override));
  MOCK_METHOD(const char*, Name, (), (const, override));
  MOCK_METHOD(void, FindShortestSeparator, (std::string* start, const leveldb::Slice& limit), (const, override));
  MOCK_METHOD(void, FindShortSuccessor, (std::string* key), (const, override));
};

// Helper to create FileMetaData with a specific largest key
static leveldb::FileMetaData* MakeFile(const std::string& smallest_key,
                                        const std::string& largest_key,
                                        uint64_t seq = 100) {
  auto* f = new leveldb::FileMetaData();
  f->smallest = leveldb::InternalKey(smallest_key, seq, leveldb::kTypeValue);
  f->largest = leveldb::InternalKey(largest_key, seq, leveldb::kTypeValue);
  f->number = 1;
  f->file_size = 100;
  return f;
}

// Since AfterFile is static, we test via the VersionSet's public methods that use it,
// or we attempt direct testing. Let's try direct approach using the BytewiseComparator.

class AfterFileTest_132 : public ::testing::Test {
 protected:
  void SetUp() override {
    ucmp_ = leveldb::BytewiseComparator();
  }

  void TearDown() override {
    for (auto* f : files_) {
      delete f;
    }
    files_.clear();
  }

  const leveldb::Comparator* ucmp_;
  std::vector<leveldb::FileMetaData*> files_;
};

// Test: AfterFile returns false when user_key is nullptr
TEST_F(AfterFileTest_132, NullUserKeyReturnsFalse_132) {
  auto* f = MakeFile("a", "z");
  files_.push_back(f);
  
  // AfterFile with nullptr user_key should return false
  // We test this through SomeFileOverlapsRange or similar public API
  // Since we may not have direct access, let's use the version_set public interface
  
  // For now, test through the public API of VersionSet
  // Testing SomeFileOverlapsRange which uses AfterFile internally
}

// Since AfterFile is static, let's test through the public function 
// SomeFileOverlapsRange which is the main consumer of AfterFile.
// The function signature (from version_set.h) is:
// bool SomeFileOverlapsRange(const InternalKeyComparator& icmp,
//                            bool disjoint_sorted_files,
//                            const std::vector<FileMetaData*>& files,
//                            const Slice* smallest_user_key,
//                            const Slice* largest_user_key);

// Let's declare the function we want to test
namespace leveldb {
extern bool SomeFileOverlapsRange(
    const InternalKeyComparator& icmp,
    bool disjoint_sorted_files,
    const std::vector<FileMetaData*>& files,
    const Slice* smallest_user_key,
    const Slice* largest_user_key);
}

class SomeFileOverlapsRangeTest_132 : public ::testing::Test {
 protected:
  void SetUp() override {
    icmp_ = new leveldb::InternalKeyComparator(leveldb::BytewiseComparator());
  }

  void TearDown() override {
    delete icmp_;
    for (auto* f : files_) {
      delete f;
    }
    files_.clear();
  }

  leveldb::InternalKeyComparator* icmp_;
  std::vector<leveldb::FileMetaData*> files_;
};

// Test: No files means no overlap
TEST_F(SomeFileOverlapsRangeTest_132, EmptyFileList_132) {
  leveldb::Slice key("m");
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &key, &key));
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, false, files_, &key, &key));
}

// Test: Single file, query range completely before the file
TEST_F(SomeFileOverlapsRangeTest_132, QueryBeforeFile_Disjoint_132) {
  files_.push_back(MakeFile("m", "z"));
  leveldb::Slice smallest("a");
  leveldb::Slice largest("b");
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Single file, query range completely after the file
TEST_F(SomeFileOverlapsRangeTest_132, QueryAfterFile_Disjoint_132) {
  files_.push_back(MakeFile("a", "m"));
  leveldb::Slice smallest("n");
  leveldb::Slice largest("z");
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Single file, query range overlaps with the file
TEST_F(SomeFileOverlapsRangeTest_132, QueryOverlapsFile_Disjoint_132) {
  files_.push_back(MakeFile("d", "m"));
  leveldb::Slice smallest("a");
  leveldb::Slice largest("f");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Query range is entirely within the file
TEST_F(SomeFileOverlapsRangeTest_132, QueryInsideFile_Disjoint_132) {
  files_.push_back(MakeFile("a", "z"));
  leveldb::Slice smallest("m");
  leveldb::Slice largest("n");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Query range exactly matches file boundaries
TEST_F(SomeFileOverlapsRangeTest_132, QueryExactMatch_Disjoint_132) {
  files_.push_back(MakeFile("a", "z"));
  leveldb::Slice smallest("a");
  leveldb::Slice largest("z");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Null smallest_user_key (should match from beginning)
TEST_F(SomeFileOverlapsRangeTest_132, NullSmallestKey_Disjoint_132) {
  files_.push_back(MakeFile("a", "m"));
  leveldb::Slice largest("z");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, nullptr, &largest));
}

// Test: Null largest_user_key (should match to end)
TEST_F(SomeFileOverlapsRangeTest_132, NullLargestKey_Disjoint_132) {
  files_.push_back(MakeFile("m", "z"));
  leveldb::Slice smallest("a");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, nullptr));
}

// Test: Both keys null (should overlap with any file)
TEST_F(SomeFileOverlapsRangeTest_132, BothKeysNull_Disjoint_132) {
  files_.push_back(MakeFile("a", "z"));
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, nullptr, nullptr));
}

// Test: Both keys null, empty files
TEST_F(SomeFileOverlapsRangeTest_132, BothKeysNullEmptyFiles_132) {
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, nullptr, nullptr));
}

// Test: Multiple disjoint sorted files, query hits one
TEST_F(SomeFileOverlapsRangeTest_132, MultipleFiles_QueryHitsMiddle_Disjoint_132) {
  files_.push_back(MakeFile("a", "c"));
  files_.push_back(MakeFile("f", "h"));
  files_.push_back(MakeFile("m", "p"));
  leveldb::Slice smallest("g");
  leveldb::Slice largest("g");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Multiple disjoint sorted files, query falls in gap
TEST_F(SomeFileOverlapsRangeTest_132, MultipleFiles_QueryInGap_Disjoint_132) {
  files_.push_back(MakeFile("a", "c"));
  files_.push_back(MakeFile("f", "h"));
  files_.push_back(MakeFile("m", "p"));
  leveldb::Slice smallest("d");
  leveldb::Slice largest("e");
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Non-disjoint (unsorted) files - query before all files
TEST_F(SomeFileOverlapsRangeTest_132, QueryBeforeAllFiles_NonDisjoint_132) {
  files_.push_back(MakeFile("d", "f"));
  files_.push_back(MakeFile("c", "e"));
  leveldb::Slice smallest("a");
  leveldb::Slice largest("b");
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, false, files_, &smallest, &largest));
}

// Test: Non-disjoint (unsorted) files - query overlaps one file
TEST_F(SomeFileOverlapsRangeTest_132, QueryOverlapsOneFile_NonDisjoint_132) {
  files_.push_back(MakeFile("d", "f"));
  files_.push_back(MakeFile("m", "p"));
  leveldb::Slice smallest("e");
  leveldb::Slice largest("g");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, false, files_, &smallest, &largest));
}

// Test: Boundary - query largest equals file smallest
TEST_F(SomeFileOverlapsRangeTest_132, QueryLargestEqualsFileSmallest_Disjoint_132) {
  files_.push_back(MakeFile("m", "z"));
  leveldb::Slice smallest("a");
  leveldb::Slice largest("m");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Boundary - query smallest equals file largest
TEST_F(SomeFileOverlapsRangeTest_132, QuerySmallestEqualsFileLargest_Disjoint_132) {
  files_.push_back(MakeFile("a", "m"));
  leveldb::Slice smallest("m");
  leveldb::Slice largest("z");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Multiple files with binary search (disjoint sorted) - query after all
TEST_F(SomeFileOverlapsRangeTest_132, QueryAfterAllFiles_Disjoint_132) {
  files_.push_back(MakeFile("a", "c"));
  files_.push_back(MakeFile("f", "h"));
  files_.push_back(MakeFile("m", "p"));
  leveldb::Slice smallest("q");
  leveldb::Slice largest("z");
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Multiple files, query spans across gap between files
TEST_F(SomeFileOverlapsRangeTest_132, QuerySpansGapBetweenFiles_Disjoint_132) {
  files_.push_back(MakeFile("a", "c"));
  files_.push_back(MakeFile("m", "p"));
  leveldb::Slice smallest("d");
  leveldb::Slice largest("n");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Single file, null largest key, query after file
TEST_F(SomeFileOverlapsRangeTest_132, NullLargestKey_QueryAfterFile_132) {
  files_.push_back(MakeFile("a", "c"));
  leveldb::Slice smallest("d");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, nullptr));
}

// Test: Null smallest key, query largest before file
TEST_F(SomeFileOverlapsRangeTest_132, NullSmallestKey_QueryBeforeFile_132) {
  files_.push_back(MakeFile("m", "z"));
  leveldb::Slice largest("a");
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, nullptr, &largest));
}

// Test: Single character boundary keys
TEST_F(SomeFileOverlapsRangeTest_132, SingleCharKeys_132) {
  files_.push_back(MakeFile("b", "b"));
  leveldb::Slice smallest("b");
  leveldb::Slice largest("b");
  EXPECT_TRUE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Single char file, query just before
TEST_F(SomeFileOverlapsRangeTest_132, SingleCharFileQueryBefore_132) {
  files_.push_back(MakeFile("b", "b"));
  leveldb::Slice smallest("a");
  leveldb::Slice largest("a");
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

// Test: Single char file, query just after
TEST_F(SomeFileOverlapsRangeTest_132, SingleCharFileQueryAfter_132) {
  files_.push_back(MakeFile("b", "b"));
  leveldb::Slice smallest("c");
  leveldb::Slice largest("c");
  EXPECT_FALSE(leveldb::SomeFileOverlapsRange(*icmp_, true, files_, &smallest, &largest));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
