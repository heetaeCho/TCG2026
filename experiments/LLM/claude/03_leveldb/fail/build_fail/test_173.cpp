#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "table/table_cache.h"
#include "util/testutil.h"
#include "util/env.h"
#include "leveldb/options.h"
#include "leveldb/comparator.h"
#include "leveldb/cache.h"

namespace leveldb {

// Helper to create an InternalKey
static InternalKey MakeInternalKey(const std::string& user_key,
                                    SequenceNumber seq,
                                    ValueType type = kTypeValue) {
  return InternalKey(user_key, seq, type);
}

class PickCompactionTest_173 : public testing::Test {
 protected:
  PickCompactionTest_173()
      : env_(Env::Default()),
        icmp_(BytewiseComparator()),
        options_(),
        table_cache_(nullptr),
        version_set_(nullptr) {
    dbname_ = test::TmpDir() + "/pick_compaction_test";
    env_->CreateDir(dbname_);

    options_.env = env_;
    // Create a small block cache
    options_.block_cache = NewLRUCache(8 << 20);

    table_cache_ = new TableCache(dbname_, &options_, 100);
    version_set_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);
  }

  ~PickCompactionTest_173() override {
    delete version_set_;
    delete table_cache_;
    delete options_.block_cache;
    // Clean up test directory
    // (In a real test we'd remove files, but for simplicity we leave it)
  }

  // Helper: Initialize the VersionSet by recovering (creates initial state)
  void InitVersionSet() {
    bool save_manifest = false;
    Status s = version_set_->Recover(&save_manifest);
    // It's okay if recover finds no manifest - it creates a fresh state
    // We just need current_ to be set
  }

  // Helper: Apply an edit that adds files to a specific level
  void AddFilesToLevel(int level,
                       const std::vector<std::pair<std::string, std::string>>& file_ranges,
                       uint64_t start_file_number = 100) {
    VersionEdit edit;
    uint64_t file_num = start_file_number;
    for (const auto& range : file_ranges) {
      InternalKey smallest = MakeInternalKey(range.first, 100);
      InternalKey largest = MakeInternalKey(range.second, 100);
      edit.AddFile(level, file_num++, 1000 /* file_size */, smallest, largest);
    }
    port::Mutex mu;
    mu.Lock();
    Status s = version_set_->LogAndApply(&edit, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  // Helper: Apply an edit that sets compaction pointers via compact_pointer_
  // We can't directly set compact_pointer_, but we can create scenarios
  // that trigger size_compaction or seek_compaction.

  // Helper: Add many/large files to trigger size compaction
  void AddLargeFilesToLevel(int level, int count, uint64_t file_size,
                            uint64_t start_file_number = 200) {
    VersionEdit edit;
    for (int i = 0; i < count; i++) {
      char buf_small[32], buf_large[32];
      snprintf(buf_small, sizeof(buf_small), "key%06d", i * 2);
      snprintf(buf_large, sizeof(buf_large), "key%06d", i * 2 + 1);
      InternalKey smallest = MakeInternalKey(buf_small, 100);
      InternalKey largest = MakeInternalKey(buf_large, 100);
      edit.AddFile(level, start_file_number + i, file_size, smallest, largest);
    }
    port::Mutex mu;
    mu.Lock();
    Status s = version_set_->LogAndApply(&edit, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  Env* env_;
  InternalKeyComparator icmp_;
  Options options_;
  std::string dbname_;
  TableCache* table_cache_;
  VersionSet* version_set_;
};

// Test that PickCompaction returns nullptr when no compaction is needed
TEST_F(PickCompactionTest_173, NoCompactionNeeded_173) {
  InitVersionSet();
  // With a fresh/empty version set, no compaction should be needed
  Compaction* c = version_set_->PickCompaction();
  EXPECT_EQ(c, nullptr);
}

// Test NeedsCompaction returns false on empty/fresh version set
TEST_F(PickCompactionTest_173, NeedsCompactionFalseWhenEmpty_173) {
  InitVersionSet();
  EXPECT_FALSE(version_set_->NeedsCompaction());
}

// Test that adding enough files to level 0 triggers a compaction
TEST_F(PickCompactionTest_173, SizeCompactionLevel0_173) {
  InitVersionSet();

  // Level 0 compaction is triggered when there are >= 4 files (kL0_CompactionTrigger)
  // Add multiple files to level 0
  for (int i = 0; i < 5; i++) {
    VersionEdit edit;
    char buf_small[32], buf_large[32];
    snprintf(buf_small, sizeof(buf_small), "akey%06d", i * 2);
    snprintf(buf_large, sizeof(buf_large), "akey%06d", i * 2 + 1);
    InternalKey smallest = MakeInternalKey(buf_small, 100);
    InternalKey largest = MakeInternalKey(buf_large, 100);
    edit.AddFile(0, 100 + i, 1000, smallest, largest);
    port::Mutex mu;
    mu.Lock();
    Status s = version_set_->LogAndApply(&edit, &mu);
    mu.Unlock();
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  // Now compaction should be needed
  EXPECT_TRUE(version_set_->NeedsCompaction());

  Compaction* c = version_set_->PickCompaction();
  ASSERT_NE(c, nullptr);

  // Level 0 compaction
  EXPECT_EQ(c->level(), 0);
  EXPECT_GT(c->num_input_files(0), 0);

  delete c;
}

// Test that a large amount of data in a non-zero level triggers size compaction
TEST_F(PickCompactionTest_173, SizeCompactionNonZeroLevel_173) {
  InitVersionSet();

  // Level 1 size limit is 10MB. Add files exceeding that.
  // Each file is ~2MB, add 6 files = 12MB > 10MB
  VersionEdit edit;
  for (int i = 0; i < 6; i++) {
    char buf_small[32], buf_large[32];
    snprintf(buf_small, sizeof(buf_small), "bkey%06d", i * 2);
    snprintf(buf_large, sizeof(buf_large), "bkey%06d", i * 2 + 1);
    InternalKey smallest = MakeInternalKey(buf_small, 100);
    InternalKey largest = MakeInternalKey(buf_large, 100);
    edit.AddFile(1, 300 + i, 2 * 1048576 /* 2MB */, smallest, largest);
  }

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();

  EXPECT_TRUE(version_set_->NeedsCompaction());

  Compaction* c = version_set_->PickCompaction();
  ASSERT_NE(c, nullptr);

  EXPECT_EQ(c->level(), 1);
  EXPECT_GT(c->num_input_files(0), 0);

  delete c;
}

// Test that PickCompaction picks the right level based on compaction score
TEST_F(PickCompactionTest_173, CompactionSelectsHighestScoreLevel_173) {
  InitVersionSet();

  // Add many files to level 0 to trigger compaction there
  // Level 0 trigger is 4 files
  VersionEdit edit;
  for (int i = 0; i < 8; i++) {
    char buf_small[32], buf_large[32];
    snprintf(buf_small, sizeof(buf_small), "ckey%06d", i * 2);
    snprintf(buf_large, sizeof(buf_large), "ckey%06d", i * 2 + 1);
    InternalKey smallest = MakeInternalKey(buf_small, 100);
    InternalKey largest = MakeInternalKey(buf_large, 100);
    edit.AddFile(0, 400 + i, 1000, smallest, largest);
  }

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();

  Compaction* c = version_set_->PickCompaction();
  ASSERT_NE(c, nullptr);

  // With 8 files in level 0 and nothing elsewhere, level 0 should be picked
  EXPECT_EQ(c->level(), 0);

  delete c;
}

// Test compaction output properties
TEST_F(PickCompactionTest_173, CompactionHasValidOutputProperties_173) {
  InitVersionSet();

  // Trigger a level 0 compaction
  VersionEdit edit;
  for (int i = 0; i < 5; i++) {
    char buf_small[32], buf_large[32];
    snprintf(buf_small, sizeof(buf_small), "dkey%06d", i * 2);
    snprintf(buf_large, sizeof(buf_large), "dkey%06d", i * 2 + 1);
    InternalKey smallest = MakeInternalKey(buf_small, 100);
    InternalKey largest = MakeInternalKey(buf_large, 100);
    edit.AddFile(0, 500 + i, 1000, smallest, largest);
  }

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();

  Compaction* c = version_set_->PickCompaction();
  ASSERT_NE(c, nullptr);

  // MaxOutputFileSize should be positive
  EXPECT_GT(c->MaxOutputFileSize(), 0u);

  // edit() should return a valid pointer
  EXPECT_NE(c->edit(), nullptr);

  delete c;
}

// Test that PickCompaction with overlapping level 0 files expands inputs
TEST_F(PickCompactionTest_173, Level0ExpandsOverlappingInputs_173) {
  InitVersionSet();

  // Add overlapping files in level 0
  VersionEdit edit;
  // File 1: [aaa, ccc]
  edit.AddFile(0, 600, 1000,
               MakeInternalKey("aaa", 100),
               MakeInternalKey("ccc", 100));
  // File 2: [bbb, ddd] - overlaps with file 1
  edit.AddFile(0, 601, 1000,
               MakeInternalKey("bbb", 100),
               MakeInternalKey("ddd", 100));
  // File 3: [eee, fff] - no overlap
  edit.AddFile(0, 602, 1000,
               MakeInternalKey("eee", 100),
               MakeInternalKey("fff", 100));
  // File 4: [ggg, hhh]
  edit.AddFile(0, 603, 1000,
               MakeInternalKey("ggg", 100),
               MakeInternalKey("hhh", 100));
  // File 5: [iii, jjj]
  edit.AddFile(0, 604, 1000,
               MakeInternalKey("iii", 100),
               MakeInternalKey("jjj", 100));

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok()) << s.ToString();

  // 5 files in level 0 should trigger compaction
  Compaction* c = version_set_->PickCompaction();
  ASSERT_NE(c, nullptr);
  EXPECT_EQ(c->level(), 0);

  // For level 0, overlapping files should be expanded
  // At minimum, the overlapping files should all be included
  EXPECT_GE(c->num_input_files(0), 2);

  delete c;
}

// Test NumLevelFiles reflects files added
TEST_F(PickCompactionTest_173, NumLevelFilesReflectsAdds_173) {
  InitVersionSet();

  EXPECT_EQ(version_set_->NumLevelFiles(0), 0);
  EXPECT_EQ(version_set_->NumLevelFiles(1), 0);

  VersionEdit edit;
  edit.AddFile(1, 700, 1000,
               MakeInternalKey("x", 100),
               MakeInternalKey("y", 100));

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  EXPECT_EQ(version_set_->NumLevelFiles(1), 1);
  EXPECT_EQ(version_set_->NumLevelFiles(0), 0);
}

// Test that with no files and no seek compaction target, returns nullptr
TEST_F(PickCompactionTest_173, EmptyVersionSetReturnsNull_173) {
  InitVersionSet();
  Compaction* c = version_set_->PickCompaction();
  EXPECT_EQ(c, nullptr);
}

// Test compaction on level 1 with enough data
TEST_F(PickCompactionTest_173, Level1SizeCompactionInputFiles_173) {
  InitVersionSet();

  // Add files that exceed level 1 limit (10MB)
  VersionEdit edit;
  for (int i = 0; i < 12; i++) {
    char buf_small[32], buf_large[32];
    snprintf(buf_small, sizeof(buf_small), "ekey%06d", i * 2);
    snprintf(buf_large, sizeof(buf_large), "ekey%06d", i * 2 + 1);
    edit.AddFile(1, 800 + i, 1048576 /* 1MB */, 
                 MakeInternalKey(buf_small, 100),
                 MakeInternalKey(buf_large, 100));
  }

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = version_set_->PickCompaction();
  ASSERT_NE(c, nullptr);
  EXPECT_EQ(c->level(), 1);

  // There should be at least 1 input file selected
  EXPECT_GE(c->num_input_files(0), 1);

  // The input file should be accessible
  FileMetaData* f = c->input(0, 0);
  EXPECT_NE(f, nullptr);

  delete c;
}

// Test IsTrivialMove on a compaction
TEST_F(PickCompactionTest_173, TrivialMoveCheck_173) {
  InitVersionSet();

  // Add enough data to level 1 to trigger compaction, but only one small file
  // with no overlap in level 2 and no grandparent overlap
  VersionEdit edit;
  for (int i = 0; i < 12; i++) {
    char buf_small[32], buf_large[32];
    snprintf(buf_small, sizeof(buf_small), "fkey%06d", i * 2);
    snprintf(buf_large, sizeof(buf_large), "fkey%06d", i * 2 + 1);
    edit.AddFile(1, 900 + i, 1048576,
                 MakeInternalKey(buf_small, 100),
                 MakeInternalKey(buf_large, 100));
  }

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = version_set_->PickCompaction();
  ASSERT_NE(c, nullptr);

  // IsTrivialMove: true if single input file with no overlap in next level
  // and not too much grandparent overlap
  // The result depends on the actual state, but we can at least call it
  bool trivial = c->IsTrivialMove();
  // With only level 1 files and no level 2 files, and if only 1 input,
  // it could be trivial
  if (c->num_input_files(0) == 1 && c->num_input_files(1) == 0) {
    EXPECT_TRUE(trivial);
  }

  delete c;
}

// Test ReleaseInputs on a compaction
TEST_F(PickCompactionTest_173, ReleaseInputs_173) {
  InitVersionSet();

  // Create a compaction scenario
  VersionEdit edit;
  for (int i = 0; i < 5; i++) {
    char buf_small[32], buf_large[32];
    snprintf(buf_small, sizeof(buf_small), "gkey%06d", i * 2);
    snprintf(buf_large, sizeof(buf_large), "gkey%06d", i * 2 + 1);
    edit.AddFile(0, 1000 + i, 1000,
                 MakeInternalKey(buf_small, 100),
                 MakeInternalKey(buf_large, 100));
  }

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = version_set_->PickCompaction();
  ASSERT_NE(c, nullptr);

  // ReleaseInputs should not crash
  c->ReleaseInputs();

  delete c;
}

// Test that current() returns a valid version
TEST_F(PickCompactionTest_173, CurrentVersionNotNull_173) {
  InitVersionSet();
  EXPECT_NE(version_set_->current(), nullptr);
}

// Test AddLiveFiles
TEST_F(PickCompactionTest_173, AddLiveFiles_173) {
  InitVersionSet();

  VersionEdit edit;
  edit.AddFile(0, 1100, 1000,
               MakeInternalKey("hkey000000", 100),
               MakeInternalKey("hkey000001", 100));
  edit.AddFile(1, 1101, 1000,
               MakeInternalKey("hkey000002", 100),
               MakeInternalKey("hkey000003", 100));

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  std::set<uint64_t> live;
  version_set_->AddLiveFiles(&live);

  EXPECT_TRUE(live.count(1100) > 0);
  EXPECT_TRUE(live.count(1101) > 0);
}

// Test LastSequence and SetLastSequence
TEST_F(PickCompactionTest_173, LastSequenceAccessors_173) {
  InitVersionSet();

  EXPECT_EQ(version_set_->LastSequence(), 0u);
  version_set_->SetLastSequence(42);
  EXPECT_EQ(version_set_->LastSequence(), 42u);
  version_set_->SetLastSequence(1000);
  EXPECT_EQ(version_set_->LastSequence(), 1000u);
}

// Test NewFileNumber increments
TEST_F(PickCompactionTest_173, NewFileNumberIncrements_173) {
  InitVersionSet();

  uint64_t n1 = version_set_->NewFileNumber();
  uint64_t n2 = version_set_->NewFileNumber();
  EXPECT_GT(n2, n1);
}

// Test NumLevelBytes
TEST_F(PickCompactionTest_173, NumLevelBytes_173) {
  InitVersionSet();

  EXPECT_EQ(version_set_->NumLevelBytes(0), 0);

  VersionEdit edit;
  edit.AddFile(1, 1200, 5000,
               MakeInternalKey("ikey000000", 100),
               MakeInternalKey("ikey000001", 100));

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  EXPECT_EQ(version_set_->NumLevelBytes(1), 5000);
  EXPECT_EQ(version_set_->NumLevelBytes(0), 0);
}

// Test CompactRange returns nullptr when no files in range
TEST_F(PickCompactionTest_173, CompactRangeNoFiles_173) {
  InitVersionSet();

  InternalKey begin = MakeInternalKey("a", 100);
  InternalKey end = MakeInternalKey("z", 100);

  Compaction* c = version_set_->CompactRange(1, &begin, &end);
  // With no files in level 1, should return nullptr
  EXPECT_EQ(c, nullptr);
}

// Test CompactRange with files in range
TEST_F(PickCompactionTest_173, CompactRangeWithFiles_173) {
  InitVersionSet();

  VersionEdit edit;
  edit.AddFile(1, 1300, 1000,
               MakeInternalKey("ccc", 100),
               MakeInternalKey("ddd", 100));
  edit.AddFile(1, 1301, 1000,
               MakeInternalKey("eee", 100),
               MakeInternalKey("fff", 100));

  port::Mutex mu;
  mu.Lock();
  Status s = version_set_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  InternalKey begin = MakeInternalKey("bbb", 100);
  InternalKey end = MakeInternalKey("ggg", 100);

  Compaction* c = version_set_->CompactRange(1, &begin, &end);
  ASSERT_NE(c, nullptr);
  EXPECT_EQ(c->level(), 1);
  EXPECT_GT(c->num_input_files(0), 0);

  delete c;
}

}  // namespace leveldb
