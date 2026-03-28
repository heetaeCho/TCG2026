#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/dbformat.h"
#include "util/testutil.h"
#include "util/env.h"
#include "table/table_cache.h"
#include "db/version_edit.h"

#include <string>
#include <cstring>

namespace leveldb {

class VersionSetLevelSummaryTest_167 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_level_summary_test";
    env_->CreateDir(dbname_);

    options_.env = env_;
    table_cache_ = new TableCache(dbname_, &options_, 100);
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    versions_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
  }

  void TearDown() override {
    delete versions_;
    delete table_cache_;
    delete icmp_;
    // Clean up the test directory
    env_->RemoveDir(dbname_);
  }

  Env* env_;
  std::string dbname_;
  Options options_;
  TableCache* table_cache_;
  InternalKeyComparator* icmp_;
  VersionSet* versions_;
};

// Test that LevelSummary returns a non-null string
TEST_F(VersionSetLevelSummaryTest_167, LevelSummaryReturnsNonNull_167) {
  VersionSet::LevelSummaryStorage scratch;
  const char* result = versions_->LevelSummary(&scratch);
  ASSERT_NE(result, nullptr);
}

// Test that LevelSummary returns a pointer to the scratch buffer
TEST_F(VersionSetLevelSummaryTest_167, LevelSummaryReturnsScratchBuffer_167) {
  VersionSet::LevelSummaryStorage scratch;
  const char* result = versions_->LevelSummary(&scratch);
  EXPECT_EQ(result, scratch.buffer);
}

// Test that LevelSummary output contains "files[" prefix
TEST_F(VersionSetLevelSummaryTest_167, LevelSummaryContainsFilesPrefix_167) {
  VersionSet::LevelSummaryStorage scratch;
  const char* result = versions_->LevelSummary(&scratch);
  std::string summary(result);
  EXPECT_NE(summary.find("files["), std::string::npos);
}

// Test that LevelSummary output contains closing bracket
TEST_F(VersionSetLevelSummaryTest_167, LevelSummaryContainsClosingBracket_167) {
  VersionSet::LevelSummaryStorage scratch;
  const char* result = versions_->LevelSummary(&scratch);
  std::string summary(result);
  EXPECT_NE(summary.find("]"), std::string::npos);
}

// Test that LevelSummary output fits within the buffer
TEST_F(VersionSetLevelSummaryTest_167, LevelSummaryFitsInBuffer_167) {
  VersionSet::LevelSummaryStorage scratch;
  const char* result = versions_->LevelSummary(&scratch);
  size_t len = std::strlen(result);
  EXPECT_LT(len, sizeof(scratch.buffer));
}

// Test that calling LevelSummary multiple times with same scratch gives consistent results
TEST_F(VersionSetLevelSummaryTest_167, LevelSummaryConsistentResults_167) {
  VersionSet::LevelSummaryStorage scratch1;
  VersionSet::LevelSummaryStorage scratch2;
  const char* result1 = versions_->LevelSummary(&scratch1);
  const char* result2 = versions_->LevelSummary(&scratch2);
  EXPECT_STREQ(result1, result2);
}

// Test that on a fresh VersionSet (no files), summary shows all zeros
TEST_F(VersionSetLevelSummaryTest_167, LevelSummaryEmptyVersionSet_167) {
  // After construction without Recover, if current_ is set up,
  // we need to first recover or set up current_. 
  // For a fresh DB, let's create manifest and recover.
  // Create a fresh database first
  Status s;
  
  // Write a new manifest
  std::string manifest = dbname_ + "/MANIFEST-000001";
  WritableFile* file;
  s = env_->NewWritableFile(manifest, &file);
  if (s.ok()) {
    log::Writer writer(file);
    VersionEdit edit;
    edit.SetComparatorName(icmp_->user_comparator()->Name());
    edit.SetLogNumber(0);
    edit.SetNextFile(2);
    edit.SetLastSequence(0);
    std::string record;
    edit.EncodeTo(&record);
    s = writer.AddRecord(record);
    if (s.ok()) {
      s = file->Sync();
    }
    delete file;
  }
  
  if (s.ok()) {
    // Write CURRENT file
    s = SetCurrentFile(env_, dbname_, 1);
  }
  
  if (s.ok()) {
    bool save_manifest = false;
    s = versions_->Recover(&save_manifest);
  }
  
  if (s.ok()) {
    VersionSet::LevelSummaryStorage scratch;
    const char* result = versions_->LevelSummary(&scratch);
    std::string summary(result);
    // All levels should have 0 files
    EXPECT_EQ(summary, "files[ 0 0 0 0 0 0 0 ]");
  }
}

// Test LevelSummaryStorage buffer size is at least 100
TEST_F(VersionSetLevelSummaryTest_167, LevelSummaryStorageBufferSize_167) {
  VersionSet::LevelSummaryStorage scratch;
  EXPECT_GE(sizeof(scratch.buffer), 100u);
}

// Test that different scratch buffers produce independent results
TEST_F(VersionSetLevelSummaryTest_167, LevelSummaryDifferentScratchBuffers_167) {
  VersionSet::LevelSummaryStorage scratch1;
  VersionSet::LevelSummaryStorage scratch2;
  
  // Fill scratch2 with garbage first
  std::memset(scratch2.buffer, 'X', sizeof(scratch2.buffer));
  
  const char* result1 = versions_->LevelSummary(&scratch1);
  const char* result2 = versions_->LevelSummary(&scratch2);
  
  // Both should have the same content
  EXPECT_STREQ(result1, result2);
  // But at different addresses
  EXPECT_NE(result1, result2);
}

// Test kNumLevels is 7 (as asserted in the implementation)
TEST_F(VersionSetLevelSummaryTest_167, NumLevelsIsSeven_167) {
  EXPECT_EQ(config::kNumLevels, 7);
}

}  // namespace leveldb
