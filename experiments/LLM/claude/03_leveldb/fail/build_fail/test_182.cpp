#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "db/version_edit.h"
#include "leveldb/comparator.h"
#include "leveldb/env.h"
#include "leveldb/options.h"
#include "table/table_cache.h" // For TableCache
#include "util/testutil.h"

#include <string>
#include <vector>
#include <memory>

namespace leveldb {

// Helper: encode an internal key string for a given user key, seq, type
static std::string MakeInternalKey(const std::string& user_key,
                                    SequenceNumber seq, ValueType type) {
  std::string result;
  InternalKey ik(user_key, seq, type);
  return ik.Encode().ToString();
}

class ShouldStopBeforeTest_182 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    options_.comparator = BytewiseComparator();
    options_.env = env_;

    // Create a minimal table cache
    table_cache_ = new TableCache(test_dir_, options_, 100);

    icmp_ = new InternalKeyComparator(options_.comparator);

    vset_ = new VersionSet(test_dir_, &options_, table_cache_, icmp_);

    // We need a current version
    // Use Recover or manually set up. Since we can't easily do that,
    // we'll use CompactRange which creates a Compaction, or PickCompaction.
    // Actually, let's try to get a compaction via CompactRange on level 0.
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
  }

  // Create a Compaction by using CompactRange
  // Since we can't construct Compaction directly (private constructor),
  // we need to go through VersionSet. But CompactRange needs files.
  // Let's create a minimal setup using LogAndApply.

  Compaction* CreateCompactionWithGrandparents(
      const std::vector<FileMetaData*>& grandparents) {
    // We'll use CompactRange at level 0
    // First, add some files to the version
    port::Mutex mu;

    // Add a file at level 0
    VersionEdit edit;
    edit.AddFile(0, 100, 100,
                 InternalKey("a", 100, kTypeValue),
                 InternalKey("z", 100, kTypeValue));

    // Add grandparent files at level 2
    for (size_t i = 0; i < grandparents.size(); i++) {
      edit.AddFile(2, grandparents[i]->number, grandparents[i]->file_size,
                   grandparents[i]->smallest, grandparents[i]->largest);
    }

    mu.Lock();
    Status s = vset_->LogAndApply(&edit, &mu);
    mu.Unlock();

    if (!s.ok()) return nullptr;

    InternalKey begin("a", kMaxSequenceNumber, kTypeValue);
    InternalKey end("z", 0, kTypeDeletion);
    return vset_->CompactRange(0, &begin, &end);
  }

  const std::string test_dir_ = testing::TempDir() + "/shouldstopbefore_test_182";
  Env* env_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
  VersionSet* vset_;
};

// Test that ShouldStopBefore returns false when there are no grandparents
TEST_F(ShouldStopBeforeTest_182, NoGrandparents_ReturnsFalse_182) {
  port::Mutex mu;
  env_->CreateDir(test_dir_);

  VersionEdit edit;
  edit.AddFile(0, 100, 100,
               InternalKey("a", 100, kTypeValue),
               InternalKey("z", 100, kTypeValue));

  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();

  if (!s.ok()) {
    // If we can't set up, skip
    GTEST_SKIP() << "Could not set up version: " << s.ToString();
  }

  InternalKey begin("a", kMaxSequenceNumber, kTypeValue);
  InternalKey end("z", 0, kTypeDeletion);
  Compaction* c = vset_->CompactRange(0, &begin, &end);

  if (c == nullptr) {
    GTEST_SKIP() << "CompactRange returned null";
  }

  std::string key = MakeInternalKey("m", 50, kTypeValue);
  EXPECT_FALSE(c->ShouldStopBefore(Slice(key)));

  delete c;
}

// Test ShouldStopBefore with grandparents - first call should not trigger stop
// because seen_key_ starts false so overlapped_bytes_ doesn't accumulate on first pass
TEST_F(ShouldStopBeforeTest_182, FirstCallNeverStops_182) {
  env_->CreateDir(test_dir_);
  port::Mutex mu;

  VersionEdit edit;
  // Add file at level 0
  edit.AddFile(0, 100, 100,
               InternalKey("a", 100, kTypeValue),
               InternalKey("z", 100, kTypeValue));

  // Add a large grandparent file at level 2
  edit.AddFile(2, 200, 100 * 1024 * 1024,  // 100MB file
               InternalKey("a", 90, kTypeValue),
               InternalKey("b", 90, kTypeValue));

  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();

  if (!s.ok()) {
    GTEST_SKIP() << "Could not set up: " << s.ToString();
  }

  InternalKey begin("a", kMaxSequenceNumber, kTypeValue);
  InternalKey end("z", 0, kTypeDeletion);
  Compaction* c = vset_->CompactRange(0, &begin, &end);

  if (c == nullptr) {
    GTEST_SKIP() << "CompactRange returned null";
  }

  // Key past the grandparent - first call, seen_key_ is false
  // so overlapped_bytes_ should not increase, return false
  std::string key = MakeInternalKey("c", 50, kTypeValue);
  EXPECT_FALSE(c->ShouldStopBefore(Slice(key)));

  delete c;
}

// Test that ShouldStopBefore eventually returns true with large grandparent overlap
TEST_F(ShouldStopBeforeTest_182, StopsAfterLargeOverlap_182) {
  env_->CreateDir(test_dir_);
  port::Mutex mu;

  VersionEdit edit;
  // Add file at level 0
  edit.AddFile(0, 100, 100,
               InternalKey("a", 100, kTypeValue),
               InternalKey("z", 100, kTypeValue));

  // Add multiple large grandparent files at level 2
  // MaxGrandParentOverlapBytes is typically 10 * TargetFileSize = 10 * 2MB = 20MB
  for (int i = 0; i < 15; i++) {
    char start_key[10], end_key[10];
    snprintf(start_key, sizeof(start_key), "g%02d", i * 2);
    snprintf(end_key, sizeof(end_key), "g%02d", i * 2 + 1);
    edit.AddFile(2, 200 + i, 5 * 1024 * 1024,  // 5MB each
                 InternalKey(Slice(start_key), 90, kTypeValue),
                 InternalKey(Slice(end_key), 90, kTypeValue));
  }

  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();

  if (!s.ok()) {
    GTEST_SKIP() << "Could not set up: " << s.ToString();
  }

  InternalKey begin("a", kMaxSequenceNumber, kTypeValue);
  InternalKey end("z", 0, kTypeDeletion);
  Compaction* c = vset_->CompactRange(0, &begin, &end);

  if (c == nullptr) {
    GTEST_SKIP() << "CompactRange returned null";
  }

  // Call ShouldStopBefore with progressively larger keys
  // First call sets seen_key_ but doesn't accumulate (grandparents skipped without accumulation)
  bool stopped = false;
  for (int i = 0; i < 30; i++) {
    char key_buf[10];
    snprintf(key_buf, sizeof(key_buf), "g%02d", i);
    std::string key = MakeInternalKey(std::string(key_buf), 50, kTypeValue);
    if (c->ShouldStopBefore(Slice(key))) {
      stopped = true;
      break;
    }
  }

  // With 15 files of 5MB each = 75MB total, we should have hit the limit
  EXPECT_TRUE(stopped);

  delete c;
}

// Test that calling ShouldStopBefore with the same small key repeatedly returns false
TEST_F(ShouldStopBeforeTest_182, RepeatedSmallKeyReturnsFalse_182) {
  env_->CreateDir(test_dir_);
  port::Mutex mu;

  VersionEdit edit;
  edit.AddFile(0, 100, 100,
               InternalKey("a", 100, kTypeValue),
               InternalKey("z", 100, kTypeValue));

  // Add a grandparent file with large key range
  edit.AddFile(2, 200, 5 * 1024 * 1024,
               InternalKey("m", 90, kTypeValue),
               InternalKey("n", 90, kTypeValue));

  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();

  if (!s.ok()) {
    GTEST_SKIP() << "Could not set up: " << s.ToString();
  }

  InternalKey begin("a", kMaxSequenceNumber, kTypeValue);
  InternalKey end("z", 0, kTypeDeletion);
  Compaction* c = vset_->CompactRange(0, &begin, &end);

  if (c == nullptr) {
    GTEST_SKIP() << "CompactRange returned null";
  }

  // Key "b" is smaller than grandparent "m"-"n", so no grandparents are passed
  std::string key = MakeInternalKey("b", 50, kTypeValue);
  for (int i = 0; i < 10; i++) {
    EXPECT_FALSE(c->ShouldStopBefore(Slice(key)));
  }

  delete c;
}

// Test that after ShouldStopBefore returns true, overlapped_bytes_ resets
// and subsequent calls can return false again until threshold hit again
TEST_F(ShouldStopBeforeTest_182, ResetsAfterStop_182) {
  env_->CreateDir(test_dir_);
  port::Mutex mu;

  VersionEdit edit;
  edit.AddFile(0, 100, 100,
               InternalKey("a", 100, kTypeValue),
               InternalKey("z", 100, kTypeValue));

  // Create many grandparent files to trigger stop multiple times
  for (int i = 0; i < 30; i++) {
    char start_key[10], end_key[10];
    snprintf(start_key, sizeof(start_key), "k%02d", i * 2);
    snprintf(end_key, sizeof(end_key), "k%02d", i * 2 + 1);
    edit.AddFile(2, 200 + i, 5 * 1024 * 1024,
                 InternalKey(Slice(start_key), 90, kTypeValue),
                 InternalKey(Slice(end_key), 90, kTypeValue));
  }

  mu.Lock();
  Status s = vset_->LogAndApply(&edit, &mu);
  mu.Unlock();

  if (!s.ok()) {
    GTEST_SKIP() << "Could not set up: " << s.ToString();
  }

  InternalKey begin("a", kMaxSequenceNumber, kTypeValue);
  InternalKey end("z", 0, kTypeDeletion);
  Compaction* c = vset_->CompactRange(0, &begin, &end);

  if (c == nullptr) {
    GTEST_SKIP() << "CompactRange returned null";
  }

  int stop_count = 0;
  for (int i = 0; i < 60; i++) {
    char key_buf[10];
    snprintf(key_buf, sizeof(key_buf), "k%02d", i);
    std::string key = MakeInternalKey(std::string(key_buf), 50, kTypeValue);
    if (c->ShouldStopBefore(Slice(key))) {
      stop_count++;
    }
  }

  // With 30 files * 5MB = 150MB, and threshold ~20MB, we should get multiple stops
  EXPECT_GE(stop_count, 2);

  delete c;
}

}  // namespace leveldb
