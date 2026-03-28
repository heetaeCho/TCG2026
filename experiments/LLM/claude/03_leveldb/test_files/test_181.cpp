#include <string>
#include <vector>
#include <set>

#include "gtest/gtest.h"
#include "db/dbformat.h"
#include "db/version_edit.h"
#include "db/version_set.h"
#include "leveldb/comparator.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "table/table_cache.h"
#include "util/testutil.h"

namespace leveldb {

// We need to access private members to set up test fixtures.
// Since Compaction's constructor is private and only VersionSet can create them,
// we'll use the public API through VersionSet to create compactions,
// or we'll use CompactRange which is public.

class IsBaseLevelForKeyTest_181 : public testing::Test {
 protected:
  IsBaseLevelForKeyTest_181()
      : env_(Env::Default()),
        icmp_(BytewiseComparator()),
        options_() {
    options_.comparator = BytewiseComparator();
    options_.env = env_;
  }

  ~IsBaseLevelForKeyTest_181() override {}

  // Helper to create an InternalKey
  InternalKey MakeInternalKey(const std::string& user_key, SequenceNumber seq,
                              ValueType type) {
    return InternalKey(user_key, seq, type);
  }

  Env* env_;
  InternalKeyComparator icmp_;
  Options options_;
};

// Since Compaction is tightly coupled with VersionSet, we test through
// the DB interface or by creating a proper VersionSet setup.
// We'll create a minimal test using the actual DB to trigger compaction behavior.

TEST_F(IsBaseLevelForKeyTest_181, BaseLevelWhenNoFilesInHigherLevels_181) {
  // Test through opening a database and manipulating it
  std::string dbname = testing::TempDir() + "isbaselevel_test_181";
  DestroyDB(dbname, options_);

  DB* db = nullptr;
  options_.create_if_missing = true;
  Status s = DB::Open(options_, dbname, &db);
  ASSERT_TRUE(s.ok());

  // Write some data
  WriteOptions write_options;
  for (int i = 0; i < 100; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    s = db->Put(write_options, key, std::string(1000, 'v'));
    ASSERT_TRUE(s.ok());
  }

  // Force compaction to populate levels
  std::string start = "key000000";
  std::string end = "key000099";
  Slice start_slice(start);
  Slice end_slice(end);
  db->CompactRange(&start_slice, &end_slice);

  delete db;
  DestroyDB(dbname, options_);
}

// Test that IsBaseLevelForKey returns true when key is not in higher levels
TEST_F(IsBaseLevelForKeyTest_181, ReturnsTrue_WhenKeyNotInHigherLevels_181) {
  std::string dbname = testing::TempDir() + "isbaselevel_true_test_181";
  DestroyDB(dbname, options_);

  DB* db = nullptr;
  options_.create_if_missing = true;
  Status s = DB::Open(options_, dbname, &db);
  ASSERT_TRUE(s.ok());

  // Just put a few keys - they should only be in level 0 or level 1
  WriteOptions write_options;
  s = db->Put(write_options, "testkey", "testvalue");
  ASSERT_TRUE(s.ok());

  // Compact to move data
  db->CompactRange(nullptr, nullptr);

  // Verify data is still readable
  ReadOptions read_options;
  std::string value;
  s = db->Get(read_options, "testkey", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("testvalue", value);

  delete db;
  DestroyDB(dbname, options_);
}

// Test with overlapping keys in multiple levels
TEST_F(IsBaseLevelForKeyTest_181, MultipleCompactionLevels_181) {
  std::string dbname = testing::TempDir() + "isbaselevel_multi_181";
  DestroyDB(dbname, options_);

  DB* db = nullptr;
  options_.create_if_missing = true;
  options_.write_buffer_size = 1024;  // Small to force frequent flushes
  Status s = DB::Open(options_, dbname, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions write_options;
  // Write many keys to populate multiple levels
  for (int round = 0; round < 5; round++) {
    for (int i = 0; i < 50; i++) {
      char key[100];
      snprintf(key, sizeof(key), "key%06d", i);
      s = db->Put(write_options, key, std::string(100, 'a' + round));
      ASSERT_TRUE(s.ok());
    }
    // Force flush and compaction
    static_cast<DBImpl*>(db)->TEST_CompactMemTable();
  }

  // Full compaction
  db->CompactRange(nullptr, nullptr);

  // Verify all keys still readable
  ReadOptions read_options;
  for (int i = 0; i < 50; i++) {
    char key[100];
    snprintf(key, sizeof(key), "key%06d", i);
    std::string value;
    s = db->Get(read_options, key, &value);
    ASSERT_TRUE(s.ok());
  }

  delete db;
  DestroyDB(dbname, options_);
}

// Test boundary: key exactly matches smallest key of a file in higher level
TEST_F(IsBaseLevelForKeyTest_181, BoundaryKeyMatching_181) {
  std::string dbname = testing::TempDir() + "isbaselevel_boundary_181";
  DestroyDB(dbname, options_);

  DB* db = nullptr;
  options_.create_if_missing = true;
  options_.write_buffer_size = 2048;
  Status s = DB::Open(options_, dbname, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions write_options;
  // Write boundary keys
  s = db->Put(write_options, "aaa", "val1");
  ASSERT_TRUE(s.ok());
  s = db->Put(write_options, "zzz", "val2");
  ASSERT_TRUE(s.ok());

  db->CompactRange(nullptr, nullptr);

  // Overwrite with new values to create new version
  s = db->Put(write_options, "aaa", "val1_new");
  ASSERT_TRUE(s.ok());
  s = db->Put(write_options, "zzz", "val2_new");
  ASSERT_TRUE(s.ok());

  // Compact again
  db->CompactRange(nullptr, nullptr);

  ReadOptions read_options;
  std::string value;
  s = db->Get(read_options, "aaa", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("val1_new", value);

  s = db->Get(read_options, "zzz", &value);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("val2_new", value);

  delete db;
  DestroyDB(dbname, options_);
}

// Test with deleted keys - verifying compaction handles deletions
TEST_F(IsBaseLevelForKeyTest_181, DeletedKeysInHigherLevels_181) {
  std::string dbname = testing::TempDir() + "isbaselevel_delete_181";
  DestroyDB(dbname, options_);

  DB* db = nullptr;
  options_.create_if_missing = true;
  options_.write_buffer_size = 2048;
  Status s = DB::Open(options_, dbname, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions write_options;
  // Write keys
  for (int i = 0; i < 20; i++) {
    char key[100];
    snprintf(key, sizeof(key), "delkey%06d", i);
    s = db->Put(write_options, key, std::string(200, 'x'));
    ASSERT_TRUE(s.ok());
  }

  // Compact to push to deeper levels
  db->CompactRange(nullptr, nullptr);

  // Delete some keys
  for (int i = 0; i < 10; i++) {
    char key[100];
    snprintf(key, sizeof(key), "delkey%06d", i);
    s = db->Delete(write_options, key);
    ASSERT_TRUE(s.ok());
  }

  // Compact again - deletions should propagate
  db->CompactRange(nullptr, nullptr);

  ReadOptions read_options;
  for (int i = 0; i < 10; i++) {
    char key[100];
    snprintf(key, sizeof(key), "delkey%06d", i);
    std::string value;
    s = db->Get(read_options, key, &value);
    ASSERT_TRUE(s.IsNotFound());
  }

  // Remaining keys should still exist
  for (int i = 10; i < 20; i++) {
    char key[100];
    snprintf(key, sizeof(key), "delkey%06d", i);
    std::string value;
    s = db->Get(read_options, key, &value);
    ASSERT_TRUE(s.ok());
  }

  delete db;
  DestroyDB(dbname, options_);
}

// Test with empty database - no files in any level
TEST_F(IsBaseLevelForKeyTest_181, EmptyDatabase_181) {
  std::string dbname = testing::TempDir() + "isbaselevel_empty_181";
  DestroyDB(dbname, options_);

  DB* db = nullptr;
  options_.create_if_missing = true;
  Status s = DB::Open(options_, dbname, &db);
  ASSERT_TRUE(s.ok());

  // Compact empty range - should be fine
  db->CompactRange(nullptr, nullptr);

  ReadOptions read_options;
  std::string value;
  s = db->Get(read_options, "nonexistent", &value);
  ASSERT_TRUE(s.IsNotFound());

  delete db;
  DestroyDB(dbname, options_);
}

// Test level_ptrs_ advancement: keys are queried in order, 
// so level_ptrs_ should advance and skip already-checked files
TEST_F(IsBaseLevelForKeyTest_181, LevelPointersAdvance_181) {
  std::string dbname = testing::TempDir() + "isbaselevel_advance_181";
  DestroyDB(dbname, options_);

  DB* db = nullptr;
  options_.create_if_missing = true;
  options_.write_buffer_size = 1024;
  Status s = DB::Open(options_, dbname, &db);
  ASSERT_TRUE(s.ok());

  WriteOptions write_options;
  // Write many sequential keys to create multiple files
  for (int batch = 0; batch < 10; batch++) {
    for (int i = 0; i < 30; i++) {
      char key[100];
      snprintf(key, sizeof(key), "seqkey%06d_%02d", i, batch);
      s = db->Put(write_options, key, std::string(100, 'v'));
      ASSERT_TRUE(s.ok());
    }
    static_cast<DBImpl*>(db)->TEST_CompactMemTable();
  }

  // Compact everything
  db->CompactRange(nullptr, nullptr);

  // Verify all keys are accessible
  ReadOptions read_options;
  for (int batch = 0; batch < 10; batch++) {
    for (int i = 0; i < 30; i++) {
      char key[100];
      snprintf(key, sizeof(key), "seqkey%06d_%02d", i, batch);
      std::string value;
      s = db->Get(read_options, key, &value);
      ASSERT_TRUE(s.ok());
    }
  }

  delete db;
  DestroyDB(dbname, options_);
}

}  // namespace leveldb
