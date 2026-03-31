#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table.h"
#include "db/dbformat.h"
#include "util/testutil.h"

#include <string>
#include <vector>

namespace leveldb {

// Helper to create a minimal VersionSet for testing
class VersionSetTestHelper_178 {
 public:
  VersionSetTestHelper_178()
      : db_name_(testing::TempDir() + "version_set_test_178"),
        env_(Env::Default()),
        table_cache_(nullptr),
        versions_(nullptr) {
    DestroyDB(db_name_, Options());
    env_->CreateDir(db_name_);

    options_.env = env_;
    options_.comparator = BytewiseComparator();

    const InternalKeyComparator icmp(options_.comparator);
    table_cache_ = new TableCache(db_name_, options_, 100);
    versions_ = new VersionSet(db_name_, &options_, table_cache_, &icmp);

    // Recover or create the version set
    bool save_manifest = false;
    Status s = versions_->Recover(&save_manifest);
    assert(s.ok());
  }

  ~VersionSetTestHelper_178() {
    delete versions_;
    delete table_cache_;
    DestroyDB(db_name_, Options());
  }

  VersionSet* versions() { return versions_; }
  const Options& options() const { return options_; }
  const std::string& db_name() const { return db_name_; }

 private:
  std::string db_name_;
  Env* env_;
  Options options_;
  TableCache* table_cache_;
  VersionSet* versions_;
};

// ============================================================
// Tests for Compaction
// ============================================================

class CompactionTest_178 : public ::testing::Test {
 protected:
  void SetUp() override {
    helper_ = new VersionSetTestHelper_178();
  }

  void TearDown() override {
    delete helper_;
  }

  VersionSetTestHelper_178* helper_;
};

TEST_F(CompactionTest_178, CompactionDestructorUnrefsInputVersion_178) {
  // When a Compaction is destroyed, it should Unref the input_version_ if set.
  // We test this indirectly by creating a compaction via the VersionSet
  // and then destroying it without crashing.
  Compaction* c = helper_->versions()->CompactRange(0, nullptr, nullptr);
  // c may be nullptr if there are no files, that's fine
  delete c;
  // If we get here without crash, the destructor handled nullptr input_version_ properly
}

TEST_F(CompactionTest_178, LevelAccessor_178) {
  // Test that level() returns the correct level
  Compaction* c = helper_->versions()->CompactRange(0, nullptr, nullptr);
  if (c != nullptr) {
    EXPECT_EQ(0, c->level());
    delete c;
  }
}

TEST_F(CompactionTest_178, EditAccessor_178) {
  // Test that edit() returns a non-null VersionEdit pointer
  Compaction* c = helper_->versions()->CompactRange(0, nullptr, nullptr);
  if (c != nullptr) {
    EXPECT_NE(nullptr, c->edit());
    delete c;
  }
}

TEST_F(CompactionTest_178, MaxOutputFileSize_178) {
  // Test that MaxOutputFileSize returns a positive value
  Compaction* c = helper_->versions()->CompactRange(0, nullptr, nullptr);
  if (c != nullptr) {
    EXPECT_GT(c->MaxOutputFileSize(), 0u);
    delete c;
  }
}

TEST_F(CompactionTest_178, NumInputFilesEmpty_178) {
  // If compaction is created on an empty level, num_input_files may be 0
  Compaction* c = helper_->versions()->CompactRange(0, nullptr, nullptr);
  if (c != nullptr) {
    // inputs_[0] and inputs_[1] should have valid counts (>= 0)
    EXPECT_GE(c->num_input_files(0), 0);
    EXPECT_GE(c->num_input_files(1), 0);
    delete c;
  }
}

TEST_F(CompactionTest_178, ReleaseInputs_178) {
  // Test that ReleaseInputs doesn't crash
  Compaction* c = helper_->versions()->CompactRange(0, nullptr, nullptr);
  if (c != nullptr) {
    c->ReleaseInputs();
    // After releasing inputs, deleting should still be safe
    delete c;
  }
}

TEST_F(CompactionTest_178, IsTrivialMoveOnEmpty_178) {
  // On an empty database, if compaction exists, test IsTrivialMove
  Compaction* c = helper_->versions()->CompactRange(0, nullptr, nullptr);
  if (c != nullptr) {
    // Just verify it returns a bool without crashing
    bool trivial = c->IsTrivialMove();
    (void)trivial;
    delete c;
  }
}

// ============================================================
// Tests for Version
// ============================================================

class VersionTest_178 : public ::testing::Test {
 protected:
  void SetUp() override {
    helper_ = new VersionSetTestHelper_178();
  }

  void TearDown() override {
    delete helper_;
  }

  VersionSetTestHelper_178* helper_;
};

TEST_F(VersionTest_178, NumFilesOnEmptyVersion_178) {
  // On a fresh database, all levels should have 0 files
  Version* v = helper_->versions()->current();
  v->Ref();
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(0, v->NumFiles(level));
  }
  v->Unref();
}

TEST_F(VersionTest_178, DebugString_178) {
  // DebugString should return a non-empty string
  Version* v = helper_->versions()->current();
  v->Ref();
  std::string debug = v->DebugString();
  EXPECT_FALSE(debug.empty());
  v->Unref();
}

TEST_F(VersionTest_178, OverlapInLevelEmptyDatabase_178) {
  // On an empty database, no level should have overlapping files
  Version* v = helper_->versions()->current();
  v->Ref();
  Slice small_key("a");
  Slice large_key("z");
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_FALSE(v->OverlapInLevel(level, &small_key, &large_key));
  }
  v->Unref();
}

TEST_F(VersionTest_178, PickLevelForMemTableOutputEmpty_178) {
  // On an empty database, PickLevelForMemTableOutput should return a valid level
  Version* v = helper_->versions()->current();
  v->Ref();
  Slice small_key("a");
  Slice large_key("z");
  int level = v->PickLevelForMemTableOutput(small_key, large_key);
  EXPECT_GE(level, 0);
  EXPECT_LT(level, config::kNumLevels);
  v->Unref();
}

TEST_F(VersionTest_178, GetOverlappingInputsEmpty_178) {
  // On an empty database, GetOverlappingInputs should return no files
  Version* v = helper_->versions()->current();
  v->Ref();
  std::vector<FileMetaData*> inputs;
  InternalKey begin("a", 100, kTypeValue);
  InternalKey end("z", 100, kTypeValue);
  v->GetOverlappingInputs(0, &begin, &end, &inputs);
  EXPECT_TRUE(inputs.empty());
  v->Unref();
}

TEST_F(VersionTest_178, GetOverlappingInputsNullBeginEnd_178) {
  // GetOverlappingInputs with null begin/end should not crash
  Version* v = helper_->versions()->current();
  v->Ref();
  std::vector<FileMetaData*> inputs;
  v->GetOverlappingInputs(0, nullptr, nullptr, &inputs);
  EXPECT_TRUE(inputs.empty());
  v->Unref();
}

TEST_F(VersionTest_178, RefUnref_178) {
  // Test that Ref/Unref don't crash and work correctly
  Version* v = helper_->versions()->current();
  v->Ref();
  v->Ref();
  v->Unref();
  v->Unref();
  // Should not crash; the version is still alive because VersionSet holds a ref
}

TEST_F(VersionTest_178, AddIteratorsEmpty_178) {
  // On an empty database, AddIterators should not add any iterators
  Version* v = helper_->versions()->current();
  v->Ref();
  ReadOptions roptions;
  std::vector<Iterator*> iters;
  v->AddIterators(roptions, &iters);
  // Clean up iterators
  for (auto* it : iters) {
    delete it;
  }
  v->Unref();
}

TEST_F(VersionTest_178, UpdateStatsWithEmptyStats_178) {
  // Test UpdateStats with a default GetStats
  Version* v = helper_->versions()->current();
  v->Ref();
  Version::GetStats stats;
  stats.seek_file = nullptr;
  stats.seek_file_level = -1;
  bool result = v->UpdateStats(stats);
  EXPECT_FALSE(result);
  v->Unref();
}

// ============================================================
// Integration-style test with actual DB operations
// ============================================================

class CompactionIntegrationTest_178 : public ::testing::Test {
 protected:
  void SetUp() override {
    db_name_ = testing::TempDir() + "compaction_integration_test_178";
    DestroyDB(db_name_, Options());
    Options options;
    options.create_if_missing = true;
    Status s = DB::Open(options, db_name_, &db_);
    ASSERT_TRUE(s.ok());
  }

  void TearDown() override {
    delete db_;
    DestroyDB(db_name_, Options());
  }

  std::string db_name_;
  DB* db_;
};

TEST_F(CompactionIntegrationTest_178, CompactRangeDoesNotCrash_178) {
  // Write some data and compact
  WriteOptions woptions;
  for (int i = 0; i < 100; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    ASSERT_TRUE(db_->Put(woptions, key, val).ok());
  }
  // Compact the entire range
  db_->CompactRange(nullptr, nullptr);

  // Verify data is still readable
  ReadOptions roptions;
  std::string val;
  Status s = db_->Get(roptions, "key50", &val);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("value50", val);
}

TEST_F(CompactionIntegrationTest_178, CompactSpecificRange_178) {
  WriteOptions woptions;
  for (int i = 0; i < 200; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "value" + std::to_string(i);
    ASSERT_TRUE(db_->Put(woptions, key, val).ok());
  }

  Slice begin("key100");
  Slice end("key199");
  db_->CompactRange(&begin, &end);

  ReadOptions roptions;
  std::string val;
  Status s = db_->Get(roptions, "key150", &val);
  ASSERT_TRUE(s.ok());
  EXPECT_EQ("value150", val);
}

}  // namespace leveldb
