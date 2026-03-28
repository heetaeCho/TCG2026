#include "gtest/gtest.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"
#include "util/testutil.h"
#include "util/testharness.h"

#include <string>
#include <vector>

namespace leveldb {

class VersionSetBuilderTest_158 : public testing::Test {
 protected:
  void SetUp() override {
    // Create a minimal environment for VersionSet
    env_ = Env::Default();
    dbname_ = test::TmpDir() + "/version_set_builder_test";
    DestroyDB(dbname_, Options());
    
    Options options;
    options.create_if_missing = true;
    
    // We need to create the database directory and necessary files
    env_->CreateDir(dbname_);
    
    // Create a proper VersionSet
    const InternalKeyComparator cmp(BytewiseComparator());
    options_ = options;
    icmp_ = new InternalKeyComparator(BytewiseComparator());
    
    table_cache_ = new TableCache(dbname_, options, 100);
    vset_ = new VersionSet(dbname_, &options_, table_cache_, icmp_);
    
    Status s = vset_->Recover(nullptr);
    // If recovery fails, we still have a valid vset_ with a current version
  }

  void TearDown() override {
    delete vset_;
    delete table_cache_;
    delete icmp_;
    DestroyDB(dbname_, Options());
  }

  // Helper to create an InternalKey
  InternalKey MakeInternalKey(const std::string& user_key, uint64_t seq,
                               ValueType type) {
    InternalKey ik;
    ik.DecodeFrom(
        InternalKey(user_key, seq, type).Encode());
    return ik;
  }

  std::string dbname_;
  Env* env_;
  Options options_;
  const InternalKeyComparator* icmp_;
  TableCache* table_cache_;
  VersionSet* vset_;
};

// Test that Builder can be created and destroyed without any edits applied
TEST_F(VersionSetBuilderTest_158, ConstructAndDestruct_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    // Builder should be constructable and destructable without issues
  }
  base->Unref();
}

// Test Apply with an empty VersionEdit
TEST_F(VersionSetBuilderTest_158, ApplyEmptyEdit_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    VersionEdit edit;
    builder.Apply(&edit);
  }
  base->Unref();
}

// Test Apply with a new file added
TEST_F(VersionSetBuilderTest_158, ApplyWithNewFile_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    VersionEdit edit;
    InternalKey smallest = MakeInternalKey("a", 100, kTypeValue);
    InternalKey largest = MakeInternalKey("z", 100, kTypeValue);
    edit.AddFile(1, 1, 1000, smallest, largest);
    builder.Apply(&edit);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    // The new version should have the file at level 1
    EXPECT_EQ(1, v->NumFiles(1));
    EXPECT_EQ(0, v->NumFiles(0));
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

// Test Apply with file deletion
TEST_F(VersionSetBuilderTest_158, ApplyWithDeletedFile_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    VersionEdit edit;
    InternalKey smallest = MakeInternalKey("a", 100, kTypeValue);
    InternalKey largest = MakeInternalKey("z", 100, kTypeValue);
    edit.AddFile(2, 5, 2000, smallest, largest);
    builder.Apply(&edit);
    
    // Now delete the same file
    VersionEdit edit2;
    edit2.RemoveFile(2, 5);
    builder.Apply(&edit2);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    // The file was added then deleted, so level 2 should be empty
    EXPECT_EQ(0, v->NumFiles(2));
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

// Test SaveTo with multiple files at the same level
TEST_F(VersionSetBuilderTest_158, SaveToMultipleFilesInLevel_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    VersionEdit edit;
    
    InternalKey s1 = MakeInternalKey("a", 100, kTypeValue);
    InternalKey l1 = MakeInternalKey("c", 100, kTypeValue);
    edit.AddFile(3, 10, 1000, s1, l1);
    
    InternalKey s2 = MakeInternalKey("d", 100, kTypeValue);
    InternalKey l2 = MakeInternalKey("f", 100, kTypeValue);
    edit.AddFile(3, 11, 1500, s2, l2);
    
    InternalKey s3 = MakeInternalKey("g", 100, kTypeValue);
    InternalKey l3 = MakeInternalKey("z", 100, kTypeValue);
    edit.AddFile(3, 12, 2000, s3, l3);
    
    builder.Apply(&edit);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    EXPECT_EQ(3, v->NumFiles(3));
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

// Test Apply with files in multiple levels
TEST_F(VersionSetBuilderTest_158, ApplyFilesAcrossMultipleLevels_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    VersionEdit edit;
    
    for (int level = 0; level < config::kNumLevels; level++) {
      InternalKey s = MakeInternalKey("a", 100, kTypeValue);
      InternalKey l = MakeInternalKey("z", 100, kTypeValue);
      edit.AddFile(level, 100 + level, 1000, s, l);
    }
    
    builder.Apply(&edit);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    for (int level = 0; level < config::kNumLevels; level++) {
      EXPECT_EQ(1, v->NumFiles(level)) << "Level " << level;
    }
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

// Test multiple Apply calls accumulate correctly
TEST_F(VersionSetBuilderTest_158, MultipleApplyCalls_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    
    VersionEdit edit1;
    InternalKey s1 = MakeInternalKey("a", 100, kTypeValue);
    InternalKey l1 = MakeInternalKey("c", 100, kTypeValue);
    edit1.AddFile(2, 20, 1000, s1, l1);
    builder.Apply(&edit1);
    
    VersionEdit edit2;
    InternalKey s2 = MakeInternalKey("d", 100, kTypeValue);
    InternalKey l2 = MakeInternalKey("f", 100, kTypeValue);
    edit2.AddFile(2, 21, 1500, s2, l2);
    builder.Apply(&edit2);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    EXPECT_EQ(2, v->NumFiles(2));
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

// Test that adding and then deleting all files results in empty version
TEST_F(VersionSetBuilderTest_158, AddThenDeleteAllFiles_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    
    VersionEdit edit1;
    InternalKey s1 = MakeInternalKey("a", 100, kTypeValue);
    InternalKey l1 = MakeInternalKey("z", 100, kTypeValue);
    edit1.AddFile(1, 50, 1000, s1, l1);
    edit1.AddFile(1, 51, 2000,
                  MakeInternalKey("aa", 99, kTypeValue),
                  MakeInternalKey("zz", 99, kTypeValue));
    builder.Apply(&edit1);
    
    VersionEdit edit2;
    edit2.RemoveFile(1, 50);
    edit2.RemoveFile(1, 51);
    builder.Apply(&edit2);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    EXPECT_EQ(0, v->NumFiles(1));
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

// Test SaveTo preserves base version files
TEST_F(VersionSetBuilderTest_158, SaveToPreservesBaseFiles_158) {
  // First, create a base version with some files
  Version* base = vset_->current();
  base->Ref();
  
  Version* v1 = new Version(vset_);
  {
    VersionSet::Builder builder1(vset_, base);
    VersionEdit edit;
    InternalKey s = MakeInternalKey("a", 100, kTypeValue);
    InternalKey l = MakeInternalKey("m", 100, kTypeValue);
    edit.AddFile(2, 30, 5000, s, l);
    builder1.Apply(&edit);
    builder1.SaveTo(v1);
  }
  base->Unref();
  
  // Now use v1 as base and add more files
  v1->Ref();
  {
    VersionSet::Builder builder2(vset_, v1);
    VersionEdit edit;
    InternalKey s = MakeInternalKey("n", 100, kTypeValue);
    InternalKey l = MakeInternalKey("z", 100, kTypeValue);
    edit.AddFile(2, 31, 3000, s, l);
    builder2.Apply(&edit);
    
    Version* v2 = new Version(vset_);
    builder2.SaveTo(v2);
    
    // v2 should have both the original file and the new one
    EXPECT_EQ(2, v2->NumFiles(2));
    
    v2->Ref();
    v2->Unref();
  }
  v1->Unref();
}

// Test that deleting a non-existent file from base doesn't crash
TEST_F(VersionSetBuilderTest_158, DeleteNonExistentFile_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    VersionEdit edit;
    edit.RemoveFile(0, 9999);  // File that doesn't exist
    builder.Apply(&edit);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    EXPECT_EQ(0, v->NumFiles(0));
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

// Test SaveTo with no Apply calls produces version matching base
TEST_F(VersionSetBuilderTest_158, SaveToWithoutApply_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    // New version should match base (which is initially empty)
    for (int level = 0; level < config::kNumLevels; level++) {
      EXPECT_EQ(base->NumFiles(level), v->NumFiles(level));
    }
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

// Test boundary: add file at level 0 (which may have overlapping keys)
TEST_F(VersionSetBuilderTest_158, Level0OverlappingFiles_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    VersionEdit edit;
    
    // Level 0 files can have overlapping key ranges
    edit.AddFile(0, 1, 1000,
                 MakeInternalKey("a", 100, kTypeValue),
                 MakeInternalKey("z", 100, kTypeValue));
    edit.AddFile(0, 2, 2000,
                 MakeInternalKey("b", 200, kTypeValue),
                 MakeInternalKey("y", 200, kTypeValue));
    
    builder.Apply(&edit);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    EXPECT_EQ(2, v->NumFiles(0));
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

// Test boundary: add file at the highest level
TEST_F(VersionSetBuilderTest_158, AddFileAtMaxLevel_158) {
  Version* base = vset_->current();
  base->Ref();
  {
    VersionSet::Builder builder(vset_, base);
    VersionEdit edit;
    
    int max_level = config::kNumLevels - 1;
    edit.AddFile(max_level, 99, 5000,
                 MakeInternalKey("abc", 50, kTypeValue),
                 MakeInternalKey("xyz", 50, kTypeValue));
    
    builder.Apply(&edit);
    
    Version* v = new Version(vset_);
    builder.SaveTo(v);
    
    EXPECT_EQ(1, v->NumFiles(max_level));
    
    v->Ref();
    v->Unref();
  }
  base->Unref();
}

}  // namespace leveldb
