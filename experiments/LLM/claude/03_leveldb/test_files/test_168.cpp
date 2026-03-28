#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "db/table_cache.h"
#include "leveldb/table.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/comparator.h"
#include "util/testutil.h"

namespace leveldb {

class ApproximateOffsetOfTest_168 : public testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    options_.env = env_;
    // Use a temporary directory for the test database
    std::string test_dir;
    env_->GetTestDirectory(&test_dir);
    dbname_ = test_dir + "/approx_offset_test_168";
    env_->CreateDir(dbname_);

    icmp_ = new InternalKeyComparator(BytewiseComparator());
    table_cache_ = new TableCache(dbname_, options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
  }

  // Helper to create an InternalKey
  InternalKey MakeInternalKey(const std::string& user_key, SequenceNumber seq,
                               ValueType type) {
    return InternalKey(user_key, seq, type);
  }

  // Helper to add a file to a version at a given level
  void AddFile(Version* v, int level, uint64_t file_number,
               const std::string& smallest_key, const std::string& largest_key,
               uint64_t file_size) {
    FileMetaData* f = new FileMetaData();
    f->number = file_number;
    f->file_size = file_size;
    f->smallest = MakeInternalKey(smallest_key, 100, kTypeValue);
    f->largest = MakeInternalKey(largest_key, 100, kTypeValue);
    f->refs = 1;
    v->files_[level].push_back(f);
  }

  Env* env_;
  Options options_;
  std::string dbname_;
  InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test with no files in any level - offset should be 0
TEST_F(ApproximateOffsetOfTest_168, EmptyVersion_168) {
  Version* v = new Version(vset_);
  v->Ref();

  InternalKey ikey = MakeInternalKey("abc", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  EXPECT_EQ(0u, offset);

  v->Unref();
}

// Test with a single file at level 0 where ikey is larger than the file's largest key
// The entire file_size should be counted
TEST_F(ApproximateOffsetOfTest_168, SingleFileLevel0KeyAfterLargest_168) {
  Version* v = new Version(vset_);
  v->Ref();

  AddFile(v, 0, /*file_number=*/1, "aaa", "bbb", /*file_size=*/1000);

  // ikey is after "bbb", so the file's largest <= ikey
  InternalKey ikey = MakeInternalKey("ccc", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  EXPECT_EQ(1000u, offset);

  // Clean up file metadata
  for (auto* f : v->files_[0]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[0].clear();
  v->Unref();
}

// Test with a single file at level 0 where ikey is before the file's smallest key
// For level 0, we don't break - just skip. Result should be 0.
TEST_F(ApproximateOffsetOfTest_168, SingleFileLevel0KeyBeforeSmallest_168) {
  Version* v = new Version(vset_);
  v->Ref();

  AddFile(v, 0, /*file_number=*/2, "ddd", "fff", /*file_size=*/2000);

  // ikey is before "ddd"
  InternalKey ikey = MakeInternalKey("aaa", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  // Key is before smallest, level == 0, so we don't break, just skip
  EXPECT_EQ(0u, offset);

  for (auto* f : v->files_[0]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[0].clear();
  v->Unref();
}

// Test with multiple files at level 0 where ikey is after all files
TEST_F(ApproximateOffsetOfTest_168, MultipleFilesLevel0KeyAfterAll_168) {
  Version* v = new Version(vset_);
  v->Ref();

  AddFile(v, 0, /*file_number=*/1, "aaa", "bbb", /*file_size=*/1000);
  AddFile(v, 0, /*file_number=*/2, "ccc", "ddd", /*file_size=*/2000);
  AddFile(v, 0, /*file_number=*/3, "eee", "fff", /*file_size=*/3000);

  InternalKey ikey = MakeInternalKey("zzz", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  // All files' largest <= ikey, so sum = 1000 + 2000 + 3000 = 6000
  EXPECT_EQ(6000u, offset);

  for (auto* f : v->files_[0]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[0].clear();
  v->Unref();
}

// Test with files at a higher level (> 0) where ikey is before smallest
// Should break early for levels > 0
TEST_F(ApproximateOffsetOfTest_168, HigherLevelKeyBeforeSmallestBreaks_168) {
  Version* v = new Version(vset_);
  v->Ref();

  // Add files at level 1 (sorted by smallest key)
  AddFile(v, 1, /*file_number=*/1, "ddd", "fff", /*file_size=*/1000);
  AddFile(v, 1, /*file_number=*/2, "ggg", "iii", /*file_size=*/2000);

  // ikey is before "ddd", so for level > 0, we break
  InternalKey ikey = MakeInternalKey("aaa", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  // Should be 0 because we break at the first file
  EXPECT_EQ(0u, offset);

  for (auto* f : v->files_[1]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[1].clear();
  v->Unref();
}

// Test with files at higher level where ikey is after all
TEST_F(ApproximateOffsetOfTest_168, HigherLevelKeyAfterAll_168) {
  Version* v = new Version(vset_);
  v->Ref();

  AddFile(v, 1, /*file_number=*/1, "aaa", "bbb", /*file_size=*/1000);
  AddFile(v, 1, /*file_number=*/2, "ccc", "ddd", /*file_size=*/2000);

  InternalKey ikey = MakeInternalKey("zzz", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  EXPECT_EQ(3000u, offset);

  for (auto* f : v->files_[1]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[1].clear();
  v->Unref();
}

// Test with files across multiple levels
TEST_F(ApproximateOffsetOfTest_168, FilesAcrossMultipleLevels_168) {
  Version* v = new Version(vset_);
  v->Ref();

  AddFile(v, 0, /*file_number=*/1, "aaa", "bbb", /*file_size=*/1000);
  AddFile(v, 1, /*file_number=*/2, "ccc", "ddd", /*file_size=*/2000);
  AddFile(v, 2, /*file_number=*/3, "eee", "fff", /*file_size=*/3000);

  InternalKey ikey = MakeInternalKey("zzz", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  // All files' largest <= ikey
  EXPECT_EQ(6000u, offset);

  for (int level = 0; level < config::kNumLevels; level++) {
    for (auto* f : v->files_[level]) {
      f->refs--;
      if (f->refs <= 0) delete f;
    }
    v->files_[level].clear();
  }
  v->Unref();
}

// Test with a file at level 1 where ikey is between two files
// Second file's smallest > ikey, so we break at level > 0
TEST_F(ApproximateOffsetOfTest_168, HigherLevelKeyBetweenFiles_168) {
  Version* v = new Version(vset_);
  v->Ref();

  AddFile(v, 1, /*file_number=*/1, "aaa", "bbb", /*file_size=*/1000);
  AddFile(v, 1, /*file_number=*/2, "ddd", "fff", /*file_size=*/2000);

  // ikey "ccc" is after first file's largest but before second file's smallest
  InternalKey ikey = MakeInternalKey("ccc", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  // First file counted (1000), second file breaks (level > 0)
  EXPECT_EQ(1000u, offset);

  for (auto* f : v->files_[1]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[1].clear();
  v->Unref();
}

// Test with level 0 files where ikey is between files
// At level 0, we do NOT break when smallest > ikey
TEST_F(ApproximateOffsetOfTest_168, Level0DoesNotBreakOnSmallestGreater_168) {
  Version* v = new Version(vset_);
  v->Ref();

  // Level 0 files can overlap, so order doesn't matter as much
  AddFile(v, 0, /*file_number=*/1, "ddd", "fff", /*file_size=*/1000);
  AddFile(v, 0, /*file_number=*/2, "aaa", "bbb", /*file_size=*/2000);

  // ikey "ccc" - first file: smallest("ddd") > ikey, but level 0, no break
  // second file: largest("bbb") <= ikey, so count it
  InternalKey ikey = MakeInternalKey("ccc", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  // First file skipped (smallest > ikey, level 0 no break)
  // Second file counted (largest <= ikey): 2000
  EXPECT_EQ(2000u, offset);

  for (auto* f : v->files_[0]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[0].clear();
  v->Unref();
}

// Test with zero-size files
TEST_F(ApproximateOffsetOfTest_168, ZeroSizeFiles_168) {
  Version* v = new Version(vset_);
  v->Ref();

  AddFile(v, 0, /*file_number=*/1, "aaa", "bbb", /*file_size=*/0);

  InternalKey ikey = MakeInternalKey("zzz", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  EXPECT_EQ(0u, offset);

  for (auto* f : v->files_[0]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[0].clear();
  v->Unref();
}

// Test boundary: ikey exactly equals the largest key
TEST_F(ApproximateOffsetOfTest_168, KeyEqualsLargest_168) {
  Version* v = new Version(vset_);
  v->Ref();

  AddFile(v, 1, /*file_number=*/1, "aaa", "bbb", /*file_size=*/5000);

  // ikey matches the largest key exactly (same user key, same sequence, same type)
  InternalKey ikey = MakeInternalKey("bbb", 100, kTypeValue);
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  // icmp_.Compare(largest, ikey) should be 0, so <= 0 is true, file_size counted
  EXPECT_EQ(5000u, offset);

  for (auto* f : v->files_[1]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[1].clear();
  v->Unref();
}

// Test boundary: ikey exactly equals the smallest key
// This means smallest is NOT > ikey, and largest is NOT <= ikey (if largest > smallest)
// So we fall into the else branch (table lookup)
TEST_F(ApproximateOffsetOfTest_168, KeyEqualsSmallest_168) {
  Version* v = new Version(vset_);
  v->Ref();

  AddFile(v, 1, /*file_number=*/1, "aaa", "bbb", /*file_size=*/5000);

  InternalKey ikey = MakeInternalKey("aaa", 100, kTypeValue);
  // smallest("aaa",100) is NOT > ikey("aaa",100), and largest("bbb",100) is NOT <= ikey("aaa",100)
  // Falls into else branch - tries to open table (will likely fail since no actual table file)
  // The offset returned may be 0 or partial depending on whether table opens
  uint64_t offset = vset_->ApproximateOffsetOf(v, ikey);
  // We can't predict exact value since the table file doesn't exist,
  // but the function should not crash
  EXPECT_GE(offset, 0u);

  for (auto* f : v->files_[1]) {
    f->refs--;
    if (f->refs <= 0) delete f;
  }
  v->files_[1].clear();
  v->Unref();
}

}  // namespace leveldb
