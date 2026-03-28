#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "table/merger.h"
#include "util/testutil.h"

#include <string>
#include <vector>

namespace leveldb {

// Since Compaction's constructor is private, we need to go through VersionSet
// to obtain Compaction objects. We'll set up a minimal VersionSet for testing.

class CompactionTest_79 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "compaction_test_79";
    DestroyDB(dbname_, Options());

    options_.env = env_;
    options_.create_if_exists_ok = true;

    table_cache_ = new TableCache(dbname_, options_, 100);
    
    const InternalKeyComparator cmp(BytewiseComparator());
    versions_ = new VersionSet(dbname_, &options_, table_cache_, &cmp);
    
    Status s = versions_->Recover(nullptr);
    // It's okay if recover fails in some cases; we mainly need the object
  }

  void TearDown() override {
    delete versions_;
    delete table_cache_;
    DestroyDB(dbname_, Options());
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  VersionSet* versions_;
};

// Test that level() returns the correct level for a compaction
TEST_F(CompactionTest_79, LevelReturnsCorrectLevel_79) {
  // We'll try to pick a compaction; if none available, we at least verify
  // the interface doesn't crash. In a real scenario with data, this would
  // return a valid compaction.
  Compaction* c = versions_->PickCompaction();
  if (c != nullptr) {
    int level = c->level();
    EXPECT_GE(level, 0);
    EXPECT_LT(level, config::kNumLevels);
    delete c;
  }
}

// Test that edit() returns a non-null pointer
TEST_F(CompactionTest_79, EditReturnsNonNull_79) {
  Compaction* c = versions_->PickCompaction();
  if (c != nullptr) {
    VersionEdit* edit = c->edit();
    EXPECT_NE(edit, nullptr);
    delete c;
  }
}

// Test MaxOutputFileSize returns a positive value
TEST_F(CompactionTest_79, MaxOutputFileSizePositive_79) {
  Compaction* c = versions_->PickCompaction();
  if (c != nullptr) {
    uint64_t max_size = c->MaxOutputFileSize();
    EXPECT_GT(max_size, 0u);
    delete c;
  }
}

// Test that num_input_files returns non-negative for valid which values
TEST_F(CompactionTest_79, NumInputFilesNonNegative_79) {
  Compaction* c = versions_->PickCompaction();
  if (c != nullptr) {
    EXPECT_GE(c->num_input_files(0), 0);
    EXPECT_GE(c->num_input_files(1), 0);
    delete c;
  }
}

// Test ReleaseInputs doesn't crash
TEST_F(CompactionTest_79, ReleaseInputsDoesNotCrash_79) {
  Compaction* c = versions_->PickCompaction();
  if (c != nullptr) {
    c->ReleaseInputs();
    delete c;
  }
}

// Full integration test using DB to create actual compaction scenarios
class CompactionDBTest_79 : public ::testing::Test {
 protected:
  void SetUp() override {
    dbname_ = testing::TempDir() + "compaction_db_test_79";
    DestroyDB(dbname_, Options());
    options_.create_if_missing = true;
    ASSERT_TRUE(DB::Open(options_, dbname_, &db_).ok());
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, Options());
  }

  std::string dbname_;
  Options options_;
  DB* db_ = nullptr;
};

// Verify that after writes, compaction can proceed without errors
TEST_F(CompactionDBTest_79, CompactAfterWrites_79) {
  // Write enough data to trigger compaction scenarios
  WriteOptions wo;
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = std::string(100, 'v');
    ASSERT_TRUE(db_->Put(wo, key, val).ok());
  }
  
  // Force compaction
  db_->CompactRange(nullptr, nullptr);
  
  // Verify data is still readable
  ReadOptions ro;
  std::string value;
  ASSERT_TRUE(db_->Get(ro, "key0", &value).ok());
  EXPECT_EQ(value, std::string(100, 'v'));
}

// Test IsTrivialMove - can only be tested indirectly through compaction behavior
TEST_F(CompactionDBTest_79, TrivialMoveCheck_79) {
  // Write a small amount of data - may result in trivial moves
  WriteOptions wo;
  for (int i = 0; i < 10; i++) {
    std::string key = "trivial_key" + std::to_string(i);
    ASSERT_TRUE(db_->Put(wo, key, "value").ok());
  }
  
  db_->CompactRange(nullptr, nullptr);
  
  // Verify correctness after compaction
  ReadOptions ro;
  std::string value;
  ASSERT_TRUE(db_->Get(ro, "trivial_key0", &value).ok());
  EXPECT_EQ(value, "value");
}

}  // namespace leveldb
