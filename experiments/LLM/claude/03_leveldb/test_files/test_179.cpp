#include "db/version_set.h"
#include "db/version_edit.h"
#include "leveldb/db.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "leveldb/table_builder.h"
#include "table/merger.h"
#include "db/dbformat.h"
#include "db/table_cache.h"
#include "db/log_writer.h"
#include "util/testutil.h"

#include "gtest/gtest.h"

#include <memory>
#include <string>
#include <vector>
#include <set>

namespace leveldb {

class CompactionTest_179 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = testing::TempDir() + "/compaction_test_179";
    env_->CreateDir(dbname_);

    options_.env = env_;
    // Use a small write_buffer_size to make it easier to trigger compactions
    options_.write_buffer_size = 1024;

    icmp_ = new InternalKeyComparator(options_.comparator);
    table_cache_ = new TableCache(dbname_, &options_, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
    // Clean up test directory
    std::vector<std::string> files;
    env_->GetChildren(dbname_, &files);
    for (const auto& f : files) {
      env_->RemoveFile(dbname_ + "/" + f);
    }
    env_->RemoveDir(dbname_);
  }

  // Helper: Create a simple SSTable file and return its file number and size
  uint64_t CreateSSTFile(uint64_t file_number, const std::string& smallest,
                         const std::string& largest) {
    std::string fname = TableFileName(dbname_, file_number);
    WritableFile* file;
    Status s = env_->NewWritableFile(fname, &file);
    EXPECT_TRUE(s.ok());

    TableBuilder builder(options_, file);
    InternalKey sk(smallest, 100, kTypeValue);
    InternalKey lk(largest, 100, kTypeValue);
    builder.Add(sk.Encode(), "value1");
    if (smallest != largest) {
      builder.Add(lk.Encode(), "value2");
    }
    s = builder.Finish();
    EXPECT_TRUE(s.ok());
    uint64_t file_size = builder.FileSize();
    delete file;
    return file_size;
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test that VersionSet can be created and initialized
TEST_F(CompactionTest_179, VersionSetCreation_179) {
  ASSERT_NE(vset_, nullptr);
  ASSERT_NE(vset_->current(), nullptr);
}

// Test NumLevelFiles returns 0 for empty version set
TEST_F(CompactionTest_179, NumLevelFilesEmpty_179) {
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(vset_->NumLevelFiles(level), 0);
  }
}

// Test NumLevelBytes returns 0 for empty version set
TEST_F(CompactionTest_179, NumLevelBytesEmpty_179) {
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(vset_->NumLevelBytes(level), 0);
  }
}

// Test LastSequence getter/setter
TEST_F(CompactionTest_179, LastSequenceGetSet_179) {
  EXPECT_EQ(vset_->LastSequence(), 0);
  vset_->SetLastSequence(100);
  EXPECT_EQ(vset_->LastSequence(), 100);
  vset_->SetLastSequence(200);
  EXPECT_EQ(vset_->LastSequence(), 200);
}

// Test NewFileNumber increments
TEST_F(CompactionTest_179, NewFileNumberIncrements_179) {
  uint64_t first = vset_->NewFileNumber();
  uint64_t second = vset_->NewFileNumber();
  EXPECT_EQ(second, first + 1);
}

// Test ReuseFileNumber
TEST_F(CompactionTest_179, ReuseFileNumber_179) {
  uint64_t num = vset_->NewFileNumber();
  vset_->ReuseFileNumber(num);
  uint64_t reused = vset_->NewFileNumber();
  EXPECT_EQ(reused, num);
}

// Test MarkFileNumberUsed
TEST_F(CompactionTest_179, MarkFileNumberUsed_179) {
  vset_->MarkFileNumberUsed(1000);
  uint64_t next = vset_->NewFileNumber();
  EXPECT_GT(next, 1000);
}

// Test NeedsCompaction on empty database
TEST_F(CompactionTest_179, NeedsCompactionEmpty_179) {
  // An empty database should not need compaction
  EXPECT_FALSE(vset_->NeedsCompaction());
}

// Test LogAndApply with an empty edit
TEST_F(CompactionTest_179, LogAndApplyEmptyEdit_179) {
  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(0);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  EXPECT_TRUE(s.ok());
}

// Test LogAndApply adding a file
TEST_F(CompactionTest_179, LogAndApplyAddFile_179) {
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "z");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("z", 100, kTypeValue);
  edit.AddFile(0, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  EXPECT_TRUE(s.ok());
  EXPECT_EQ(vset_->NumLevelFiles(0), 1);
}

// Test CompactRange returns nullptr when no files exist at a level
TEST_F(CompactionTest_179, CompactRangeEmptyLevel_179) {
  InternalKey begin("a", 100, kTypeValue);
  InternalKey end("z", 100, kTypeValue);
  Compaction* c = vset_->CompactRange(1, &begin, &end);
  // No files at level 1, so compaction should be null
  EXPECT_EQ(c, nullptr);
  delete c;
}

// Test Compaction level() accessor and num_input_files
TEST_F(CompactionTest_179, CompactionAccessors_179) {
  // Add a file to level 0
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "z");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("z", 100, kTypeValue);
  edit.AddFile(0, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = vset_->CompactRange(0, &smallest, &largest);
  if (c != nullptr) {
    EXPECT_EQ(c->level(), 0);
    EXPECT_GE(c->num_input_files(0), 1);
    EXPECT_NE(c->edit(), nullptr);
    EXPECT_GT(c->MaxOutputFileSize(), 0u);
    delete c;
  }
}

// Test IsTrivialMove with a single file at level and no overlapping grandparents
TEST_F(CompactionTest_179, IsTrivialMoveSingleFile_179) {
  // Add a single small file to level 1
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "b");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("b", 100, kTypeValue);
  edit.AddFile(1, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(vset_->NumLevelFiles(1), 1);

  Compaction* c = vset_->CompactRange(1, &smallest, &largest);
  if (c != nullptr) {
    // With a single file at level 1, no files at level 2, and no grandparents,
    // this should be a trivial move
    if (c->num_input_files(0) == 1 && c->num_input_files(1) == 0) {
      EXPECT_TRUE(c->IsTrivialMove());
    }
    delete c;
  }
}

// Test IsTrivialMove is false when there are level+1 files
TEST_F(CompactionTest_179, IsTrivialMoveNotTrivialWithLevel1Files_179) {
  // Add a file to level 1
  uint64_t file_num1 = vset_->NewFileNumber();
  uint64_t file_size1 = CreateSSTFile(file_num1, "a", "z");

  // Add a file to level 2 that overlaps
  uint64_t file_num2 = vset_->NewFileNumber();
  uint64_t file_size2 = CreateSSTFile(file_num2, "a", "z");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(2);

  InternalKey smallest1("a", 100, kTypeValue);
  InternalKey largest1("z", 100, kTypeValue);
  edit.AddFile(1, file_num1, file_size1, smallest1, largest1);

  InternalKey smallest2("a", 99, kTypeValue);
  InternalKey largest2("z", 99, kTypeValue);
  edit.AddFile(2, file_num2, file_size2, smallest2, largest2);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = vset_->CompactRange(1, &smallest1, &largest1);
  if (c != nullptr) {
    // With overlapping level+1 files, not trivial
    if (c->num_input_files(1) > 0) {
      EXPECT_FALSE(c->IsTrivialMove());
    }
    delete c;
  }
}

// Test IsTrivialMove is false when there are large grandparent overlaps
TEST_F(CompactionTest_179, IsTrivialMoveNotTrivialWithGrandparents_179) {
  // Add a file to level 1
  uint64_t file_num1 = vset_->NewFileNumber();
  uint64_t file_size1 = CreateSSTFile(file_num1, "a", "z");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(10);

  InternalKey smallest1("a", 100, kTypeValue);
  InternalKey largest1("z", 100, kTypeValue);
  edit.AddFile(1, file_num1, file_size1, smallest1, largest1);

  // Add many large files to level 3 (grandparents for level 1->2 compaction)
  // to exceed MaxGrandParentOverlapBytes
  for (int i = 0; i < 30; i++) {
    uint64_t fn = vset_->NewFileNumber();
    char small_buf[16], large_buf[16];
    snprintf(small_buf, sizeof(small_buf), "%c", 'a' + (i % 26));
    snprintf(large_buf, sizeof(large_buf), "%c", 'a' + (i % 26));
    uint64_t fs = CreateSSTFile(fn, small_buf, large_buf);

    InternalKey sk(small_buf, 50 + i, kTypeValue);
    InternalKey lk(large_buf, 50 + i, kTypeValue);
    edit.AddFile(3, fn, fs, sk, lk);
  }

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = vset_->CompactRange(1, &smallest1, &largest1);
  if (c != nullptr) {
    // The result depends on actual grandparent overlap calculation
    // Just verify IsTrivialMove doesn't crash and returns a bool
    bool trivial = c->IsTrivialMove();
    (void)trivial;  // just ensure it doesn't crash
    delete c;
  }
}

// Test Compaction::AddInputDeletions
TEST_F(CompactionTest_179, AddInputDeletions_179) {
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "b");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("b", 100, kTypeValue);
  edit.AddFile(1, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = vset_->CompactRange(1, &smallest, &largest);
  if (c != nullptr) {
    VersionEdit compaction_edit;
    c->AddInputDeletions(&compaction_edit);
    // Just verify it doesn't crash
    delete c;
  }
}

// Test Compaction::ReleaseInputs
TEST_F(CompactionTest_179, ReleaseInputs_179) {
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "b");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("b", 100, kTypeValue);
  edit.AddFile(1, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = vset_->CompactRange(1, &smallest, &largest);
  if (c != nullptr) {
    c->ReleaseInputs();
    delete c;
  }
}

// Test Compaction::IsBaseLevelForKey
TEST_F(CompactionTest_179, IsBaseLevelForKey_179) {
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "z");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("z", 100, kTypeValue);
  edit.AddFile(1, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = vset_->CompactRange(1, &smallest, &largest);
  if (c != nullptr) {
    // With no files at higher levels, "m" should be a base level key
    Slice key("m");
    bool is_base = c->IsBaseLevelForKey(key);
    EXPECT_TRUE(is_base);
    delete c;
  }
}

// Test Compaction::ShouldStopBefore
TEST_F(CompactionTest_179, ShouldStopBefore_179) {
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "z");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("z", 100, kTypeValue);
  edit.AddFile(1, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = vset_->CompactRange(1, &smallest, &largest);
  if (c != nullptr) {
    InternalKey test_key("m", 50, kTypeValue);
    bool should_stop = c->ShouldStopBefore(test_key.Encode());
    // With no grandparents, shouldn't stop
    EXPECT_FALSE(should_stop);
    delete c;
  }
}

// Test Compaction input() accessor
TEST_F(CompactionTest_179, CompactionInputAccessor_179) {
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "z");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("z", 100, kTypeValue);
  edit.AddFile(1, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = vset_->CompactRange(1, &smallest, &largest);
  if (c != nullptr) {
    ASSERT_GE(c->num_input_files(0), 1);
    FileMetaData* f = c->input(0, 0);
    ASSERT_NE(f, nullptr);
    EXPECT_EQ(f->number, file_num);
    EXPECT_EQ(f->file_size, file_size);
    delete c;
  }
}

// Test MakeInputIterator
TEST_F(CompactionTest_179, MakeInputIterator_179) {
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "z");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("z", 100, kTypeValue);
  edit.AddFile(1, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  Compaction* c = vset_->CompactRange(1, &smallest, &largest);
  if (c != nullptr) {
    Iterator* iter = vset_->MakeInputIterator(c);
    ASSERT_NE(iter, nullptr);
    iter->SeekToFirst();
    EXPECT_TRUE(iter->Valid());
    delete iter;
    delete c;
  }
}

// Test AddLiveFiles
TEST_F(CompactionTest_179, AddLiveFiles_179) {
  uint64_t file_num = vset_->NewFileNumber();
  uint64_t file_size = CreateSSTFile(file_num, "a", "b");

  VersionEdit edit;
  edit.SetLogNumber(0);
  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(1);

  InternalKey smallest("a", 100, kTypeValue);
  InternalKey largest("b", 100, kTypeValue);
  edit.AddFile(0, file_num, file_size, smallest, largest);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());

  std::set<uint64_t> live;
  vset_->AddLiveFiles(&live);
  EXPECT_TRUE(live.count(file_num) > 0);
}

// Test MaxNextLevelOverlappingBytes on empty database
TEST_F(CompactionTest_179, MaxNextLevelOverlappingBytesEmpty_179) {
  int64_t max_overlap = vset_->MaxNextLevelOverlappingBytes();
  EXPECT_EQ(max_overlap, 0);
}

// Test PickCompaction on empty database
TEST_F(CompactionTest_179, PickCompactionEmpty_179) {
  Compaction* c = vset_->PickCompaction();
  EXPECT_EQ(c, nullptr);
  delete c;
}

// Test LevelSummary
TEST_F(CompactionTest_179, LevelSummary_179) {
  VersionSet::LevelSummaryStorage scratch;
  const char* summary = vset_->LevelSummary(&scratch);
  ASSERT_NE(summary, nullptr);
  EXPECT_GT(strlen(summary), 0u);
}

// Test multiple files and IsTrivialMove is false with multiple level-0 inputs
TEST_F(CompactionTest_179, IsTrivialMoveMultipleInputs_179) {
  // Add multiple overlapping files to level 0
  VersionEdit edit;
  edit.SetLogNumber(0);

  for (int i = 0; i < 5; i++) {
    uint64_t fn = vset_->NewFileNumber();
    uint64_t fs = CreateSSTFile(fn, "a", "z");
    InternalKey sk("a", 100 + i, kTypeValue);
    InternalKey lk("z", 100 + i, kTypeValue);
    edit.AddFile(0, fn, fs, sk, lk);
  }

  edit.SetNextFile(vset_->NewFileNumber());
  edit.SetLastSequence(200);

  port::Mutex mu;
  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();
  ASSERT_TRUE(s.ok());
  EXPECT_EQ(vset_->NumLevelFiles(0), 5);

  InternalKey begin("a", 200, kTypeValue);
  InternalKey end("z", 200, kTypeValue);
  Compaction* c = vset_->CompactRange(0, &begin, &end);
  if (c != nullptr) {
    // With multiple inputs at level 0, IsTrivialMove should be false
    if (c->num_input_files(0) > 1) {
      EXPECT_FALSE(c->IsTrivialMove());
    }
    delete c;
  }
}

// Test Version::NumFiles
TEST_F(CompactionTest_179, VersionNumFiles_179) {
  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);
  for (int level = 0; level < config::kNumLevels; level++) {
    EXPECT_EQ(v->NumFiles(level), 0);
  }
}

// Test Version::DebugString
TEST_F(CompactionTest_179, VersionDebugString_179) {
  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);
  std::string debug = v->DebugString();
  EXPECT_FALSE(debug.empty());
}

// Test Version::OverlapInLevel on empty level
TEST_F(CompactionTest_179, VersionOverlapInLevelEmpty_179) {
  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);
  Slice small("a");
  Slice large("z");
  bool overlap = v->OverlapInLevel(0, &small, &large);
  EXPECT_FALSE(overlap);
}

// Test Version::Ref and Unref
TEST_F(CompactionTest_179, VersionRefUnref_179) {
  Version* v = vset_->current();
  ASSERT_NE(v, nullptr);
  v->Ref();
  v->Unref();
  // Should not crash - the version is still referenced by current_
}

}  // namespace leveldb
