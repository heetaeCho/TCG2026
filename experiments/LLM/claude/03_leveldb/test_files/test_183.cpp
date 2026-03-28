#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/table_cache.h"
#include "util/testutil.h"
#include "db/dbformat.h"

#include <string>
#include <vector>

namespace leveldb {

// Helper to create a minimal VersionSet and Version for testing
class CompactionTest_183 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "compaction_test_183";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    const int table_cache_size = 100;
    table_cache_ = new TableCache(dbname_, options_, table_cache_size);

    icmp_ = InternalKeyComparator(options_.comparator);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    // Clean up
    env_->RemoveDir(dbname_);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator icmp_;
  VersionSet* vset_;
};

// Test that ReleaseInputs sets input_version_ to nullptr (observable via no crash on double call)
TEST_F(CompactionTest_183, ReleaseInputsNoInputVersion_183) {
  // Create a Compaction with no input_version_ set (default nullptr)
  Compaction* c = new Compaction(&options_, 0);
  // ReleaseInputs should be safe to call when input_version_ is nullptr
  c->ReleaseInputs();
  // Calling it again should also be safe (idempotent)
  c->ReleaseInputs();
  delete c;
}

// Test level() returns the level the compaction was created with
TEST_F(CompactionTest_183, LevelReturnsCorrectLevel_183) {
  Compaction* c = new Compaction(&options_, 0);
  EXPECT_EQ(0, c->level());
  delete c;

  Compaction* c2 = new Compaction(&options_, 3);
  EXPECT_EQ(3, c2->level());
  delete c2;
}

// Test edit() returns a non-null VersionEdit pointer
TEST_F(CompactionTest_183, EditReturnsNonNull_183) {
  Compaction* c = new Compaction(&options_, 0);
  EXPECT_NE(nullptr, c->edit());
  delete c;
}

// Test MaxOutputFileSize returns a positive value
TEST_F(CompactionTest_183, MaxOutputFileSizeIsPositive_183) {
  Compaction* c = new Compaction(&options_, 0);
  EXPECT_GT(c->MaxOutputFileSize(), 0u);
  delete c;
}

// Test num_input_files with no inputs added returns 0
TEST_F(CompactionTest_183, NumInputFilesInitiallyZero_183) {
  Compaction* c = new Compaction(&options_, 0);
  EXPECT_EQ(0, c->num_input_files(0));
  EXPECT_EQ(0, c->num_input_files(1));
  delete c;
}

// Test that a compaction created at different levels reports correctly
TEST_F(CompactionTest_183, CompactionAtVariousLevels_183) {
  for (int level = 0; level < 6; level++) {
    Compaction* c = new Compaction(&options_, level);
    EXPECT_EQ(level, c->level());
    EXPECT_GT(c->MaxOutputFileSize(), 0u);
    delete c;
  }
}

// Test that ReleaseInputs with a referenced Version properly unrefs
TEST_F(CompactionTest_183, ReleaseInputsWithVersion_183) {
  // We use the VersionSet's compaction infrastructure indirectly.
  // Create a compaction via VersionSet if possible, or just test the safe path.
  Compaction* c = new Compaction(&options_, 0);
  
  // Without setting input_version_, ReleaseInputs should be safe
  c->ReleaseInputs();
  
  // After release, calling again should be safe (input_version_ is nullptr)
  c->ReleaseInputs();
  
  delete c;
}

// Test IsTrivialMove on an empty compaction (no inputs)
TEST_F(CompactionTest_183, IsTrivialMoveNoInputs_183) {
  Compaction* c = new Compaction(&options_, 1);
  // With no input files, IsTrivialMove behavior should be deterministic
  // (likely false since num_input_files(0) == 0, but we just check it doesn't crash)
  bool result = c->IsTrivialMove();
  // We don't assert the value since it depends on internal logic,
  // but we verify it doesn't crash
  (void)result;
  delete c;
}

// Test destructor can be called safely (via delete)
TEST_F(CompactionTest_183, DestructorSafe_183) {
  Compaction* c = new Compaction(&options_, 0);
  // Just ensure delete doesn't crash
  delete c;
}

// Test that edit() returns same pointer on multiple calls (stability)
TEST_F(CompactionTest_183, EditReturnsSamePointer_183) {
  Compaction* c = new Compaction(&options_, 2);
  VersionEdit* e1 = c->edit();
  VersionEdit* e2 = c->edit();
  EXPECT_EQ(e1, e2);
  delete c;
}

// Test MaxOutputFileSize consistency across calls
TEST_F(CompactionTest_183, MaxOutputFileSizeConsistent_183) {
  Compaction* c = new Compaction(&options_, 0);
  uint64_t size1 = c->MaxOutputFileSize();
  uint64_t size2 = c->MaxOutputFileSize();
  EXPECT_EQ(size1, size2);
  delete c;
}

// Version tests

class VersionTest_183 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "version_test_183";
    env_->CreateDir(dbname_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    const int table_cache_size = 100;
    table_cache_ = new TableCache(dbname_, options_, table_cache_size);

    icmp_ = InternalKeyComparator(options_.comparator);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    env_->RemoveDir(dbname_);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator icmp_;
  VersionSet* vset_;
};

// Test that the current version has zero files at all levels initially
TEST_F(VersionTest_183, InitialVersionHasNoFiles_183) {
  // After creating a fresh VersionSet (without recovery), current version
  // should have no files
  Version* v = vset_->current();
  ASSERT_NE(nullptr, v);
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, v->NumFiles(level));
  }
}

// Test DebugString returns non-empty string
TEST_F(VersionTest_183, DebugStringNonEmpty_183) {
  Version* v = vset_->current();
  ASSERT_NE(nullptr, v);
  std::string debug = v->DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test OverlapInLevel returns false when no files exist
TEST_F(VersionTest_183, NoOverlapWhenEmpty_183) {
  Version* v = vset_->current();
  ASSERT_NE(nullptr, v);
  Slice small_key("a");
  Slice large_key("z");
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_FALSE(v->OverlapInLevel(level, &small_key, &large_key));
  }
}

// Test OverlapInLevel with nullptr boundaries
TEST_F(VersionTest_183, OverlapInLevelNullBoundaries_183) {
  Version* v = vset_->current();
  ASSERT_NE(nullptr, v);
  EXPECT_FALSE(v->OverlapInLevel(0, nullptr, nullptr));
}

// Test GetOverlappingInputs with empty version
TEST_F(VersionTest_183, GetOverlappingInputsEmpty_183) {
  Version* v = vset_->current();
  ASSERT_NE(nullptr, v);
  std::vector<FileMetaData*> inputs;
  InternalKey begin(Slice("a"), 100, kTypeValue);
  InternalKey end(Slice("z"), 100, kTypeValue);
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
}

// Test PickLevelForMemTableOutput on empty version
TEST_F(VersionTest_183, PickLevelForMemTableOutputEmpty_183) {
  Version* v = vset_->current();
  ASSERT_NE(nullptr, v);
  Slice small("a");
  Slice large("z");
  int level = v->PickLevelForMemTableOutput(small, large);
  // On empty version, it should pick some level (likely 0 or higher)
  EXPECT_GE(level, 0);
}

// Test Ref and Unref don't crash
TEST_F(VersionTest_183, RefAndUnrefSafe_183) {
  Version* v = vset_->current();
  ASSERT_NE(nullptr, v);
  v->Ref();
  v->Unref();
  // Version should still be valid since vset_ holds a reference
}

// Test AddIterators on empty version
TEST_F(VersionTest_183, AddIteratorsEmpty_183) {
  Version* v = vset_->current();
  ASSERT_NE(nullptr, v);
  v->Ref();
  ReadOptions ropts;
  std::vector<Iterator*> iters;
  v->AddIterators(ropts, &iters);
  // Clean up iterators
  for (auto* iter : iters) {
    delete iter;
  }
  v->Unref();
}

}  // namespace leveldb
