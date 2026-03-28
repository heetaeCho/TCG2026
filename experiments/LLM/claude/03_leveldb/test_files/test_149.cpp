#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"

namespace leveldb {

// We need to create a Version object, but its constructor is private and requires a VersionSet*.
// Since we're testing UpdateStats which is fully provided, we need to work around construction.
// We'll use a test fixture that can create Version objects appropriately.

// Since Version constructor is private and requires VersionSet*, and we can't easily construct
// a full VersionSet, we'll test UpdateStats by directly examining its logic through the
// provided interface. We need to find a way to construct Version objects.

// Looking at the code, Version's constructor is private but VersionSet is a friend.
// We'll need to create a minimal setup. However, since we must treat implementation as black box,
// let's focus on what we can test.

// For testing UpdateStats, we can observe:
// 1. It returns true/false based on conditions
// 2. It modifies FileMetaData::allowed_seeks
// 3. It sets file_to_compact_ (observable indirectly)

// Since Version constructor is private, we need VersionSet to create versions.
// Let's create a minimal test environment.

#include "db/dbformat.h"
#include "util/logging.h"
#include "table/merger.h"

// Forward declaration for test access
class VersionSetTest;

class UpdateStatsTest_149 : public ::testing::Test {
 protected:
  // We'll test UpdateStats logic directly using the provided code snippet.
  // Since Version requires VersionSet and has private constructor, we'll
  // create a test helper.
  
  // Actually, looking more carefully at the interface, let's try to create
  // a proper environment.
  
  Env* env_;
  Options options_;
  std::string dbname_;
  InternalKeyComparator icmp_;
  InternalFilterPolicy ipolicy_;
  TableCache* table_cache_;
  VersionSet* vset_;
  
  UpdateStatsTest_149()
      : env_(Env::Default()),
        dbname_(testing::TempDir() + "/version_update_stats_test_149"),
        icmp_(BytewiseComparator()),
        ipolicy_(nullptr),
        table_cache_(nullptr),
        vset_(nullptr) {}

  void SetUp() override {
    options_.comparator = BytewiseComparator();
    env_->CreateDir(dbname_);
    table_cache_ = new TableCache(dbname_, options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    DestroyDB(dbname_, options_);
  }
};

// Test: UpdateStats returns false when seek_file is nullptr
TEST_F(UpdateStatsTest_149, ReturnsfalseWhenSeekFileIsNull_149) {
  Version* v = vset_->current();
  v->Ref();
  
  Version::GetStats stats;
  stats.seek_file = nullptr;
  stats.seek_file_level = 0;
  
  bool result = v->UpdateStats(stats);
  EXPECT_FALSE(result);
  
  v->Unref();
}

// Test: UpdateStats decrements allowed_seeks on valid file
TEST_F(UpdateStatsTest_149, DecrementsAllowedSeeks_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file;
  file.allowed_seeks = 10;
  file.number = 1;
  file.file_size = 100;
  
  Version::GetStats stats;
  stats.seek_file = &file;
  stats.seek_file_level = 0;
  
  v->UpdateStats(stats);
  EXPECT_EQ(9, file.allowed_seeks);
  
  v->Unref();
}

// Test: UpdateStats returns false when allowed_seeks > 1 (still positive after decrement)
TEST_F(UpdateStatsTest_149, ReturnsFalseWhenAllowedSeeksStillPositive_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file;
  file.allowed_seeks = 5;
  file.number = 1;
  file.file_size = 100;
  
  Version::GetStats stats;
  stats.seek_file = &file;
  stats.seek_file_level = 0;
  
  bool result = v->UpdateStats(stats);
  EXPECT_FALSE(result);
  EXPECT_EQ(4, file.allowed_seeks);
  
  v->Unref();
}

// Test: UpdateStats returns true when allowed_seeks drops to 0
TEST_F(UpdateStatsTest_149, ReturnsTrueWhenAllowedSeeksDropsToZero_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file;
  file.allowed_seeks = 1;  // Will become 0 after decrement
  file.number = 1;
  file.file_size = 100;
  
  Version::GetStats stats;
  stats.seek_file = &file;
  stats.seek_file_level = 0;
  
  bool result = v->UpdateStats(stats);
  EXPECT_TRUE(result);
  EXPECT_EQ(0, file.allowed_seeks);
  
  v->Unref();
}

// Test: UpdateStats returns true when allowed_seeks is already 0 (drops to -1)
TEST_F(UpdateStatsTest_149, ReturnsTrueWhenAllowedSeeksAlreadyZero_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file;
  file.allowed_seeks = 0;  // Will become -1 after decrement
  file.number = 1;
  file.file_size = 100;
  
  Version::GetStats stats;
  stats.seek_file = &file;
  stats.seek_file_level = 0;
  
  // First call should return true since allowed_seeks becomes <= 0
  bool result = v->UpdateStats(stats);
  EXPECT_TRUE(result);
  EXPECT_EQ(-1, file.allowed_seeks);
  
  v->Unref();
}

// Test: UpdateStats returns false on second call (file_to_compact_ already set)
TEST_F(UpdateStatsTest_149, ReturnsFalseOnSecondCallWhenCompactAlreadySet_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file1;
  file1.allowed_seeks = 1;
  file1.number = 1;
  file1.file_size = 100;
  
  Version::GetStats stats1;
  stats1.seek_file = &file1;
  stats1.seek_file_level = 0;
  
  // First call: triggers compaction
  bool result1 = v->UpdateStats(stats1);
  EXPECT_TRUE(result1);
  
  FileMetaData file2;
  file2.allowed_seeks = 1;
  file2.number = 2;
  file2.file_size = 200;
  
  Version::GetStats stats2;
  stats2.seek_file = &file2;
  stats2.seek_file_level = 1;
  
  // Second call: file_to_compact_ is already set, so returns false
  bool result2 = v->UpdateStats(stats2);
  EXPECT_FALSE(result2);
  // But allowed_seeks is still decremented
  EXPECT_EQ(0, file2.allowed_seeks);
  
  v->Unref();
}

// Test: UpdateStats with negative allowed_seeks
TEST_F(UpdateStatsTest_149, NegativeAllowedSeeksStillDecrements_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file;
  file.allowed_seeks = -5;
  file.number = 1;
  file.file_size = 100;
  
  Version::GetStats stats;
  stats.seek_file = &file;
  stats.seek_file_level = 0;
  
  bool result = v->UpdateStats(stats);
  // allowed_seeks becomes -6, which is <= 0, but if file_to_compact_ is null, returns true
  EXPECT_TRUE(result);
  EXPECT_EQ(-6, file.allowed_seeks);
  
  v->Unref();
}

// Test: UpdateStats with exactly allowed_seeks = 2 (boundary: stays positive after decrement)
TEST_F(UpdateStatsTest_149, AllowedSeeksExactlyTwo_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file;
  file.allowed_seeks = 2;
  file.number = 1;
  file.file_size = 100;
  
  Version::GetStats stats;
  stats.seek_file = &file;
  stats.seek_file_level = 0;
  
  bool result = v->UpdateStats(stats);
  EXPECT_FALSE(result);  // allowed_seeks becomes 1, still > 0
  EXPECT_EQ(1, file.allowed_seeks);
  
  v->Unref();
}

// Test: Multiple calls progressively decrement allowed_seeks until trigger
TEST_F(UpdateStatsTest_149, MultipleCallsProgressivelyDecrement_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file;
  file.allowed_seeks = 3;
  file.number = 1;
  file.file_size = 100;
  
  Version::GetStats stats;
  stats.seek_file = &file;
  stats.seek_file_level = 0;
  
  EXPECT_FALSE(v->UpdateStats(stats));  // 3 -> 2
  EXPECT_EQ(2, file.allowed_seeks);
  
  EXPECT_FALSE(v->UpdateStats(stats));  // 2 -> 1
  EXPECT_EQ(1, file.allowed_seeks);
  
  EXPECT_TRUE(v->UpdateStats(stats));   // 1 -> 0, triggers compaction
  EXPECT_EQ(0, file.allowed_seeks);
  
  // Now file_to_compact_ is set, further calls return false
  EXPECT_FALSE(v->UpdateStats(stats));  // 0 -> -1, but file_to_compact_ already set
  EXPECT_EQ(-1, file.allowed_seeks);
  
  v->Unref();
}

// Test: UpdateStats with large allowed_seeks (default value from FileMetaData)
TEST_F(UpdateStatsTest_149, DefaultAllowedSeeksValue_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file;  // Default: allowed_seeks = 1 << 30
  
  Version::GetStats stats;
  stats.seek_file = &file;
  stats.seek_file_level = 0;
  
  int original = file.allowed_seeks;
  bool result = v->UpdateStats(stats);
  EXPECT_FALSE(result);
  EXPECT_EQ(original - 1, file.allowed_seeks);
  
  v->Unref();
}

// Test: UpdateStats preserves seek_file_level in stats struct
TEST_F(UpdateStatsTest_149, SeekFileLevelPreserved_149) {
  Version* v = vset_->current();
  v->Ref();
  
  FileMetaData file;
  file.allowed_seeks = 1;
  file.number = 42;
  file.file_size = 500;
  
  Version::GetStats stats;
  stats.seek_file = &file;
  stats.seek_file_level = 3;
  
  bool result = v->UpdateStats(stats);
  EXPECT_TRUE(result);
  // stats struct itself should not be modified
  EXPECT_EQ(3, stats.seek_file_level);
  EXPECT_EQ(&file, stats.seek_file);
  
  v->Unref();
}

}  // namespace leveldb
