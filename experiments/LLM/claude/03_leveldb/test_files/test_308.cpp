#include "gtest/gtest.h"
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"
#include "db/db_impl.h"
#include "util/testutil.h"

#include <string>
#include <vector>
#include <memory>
#include <cstdio>

namespace leveldb {

class DBImplRecordReadSampleTest_308 : public testing::Test {
 protected:
  std::string dbname_;
  DB* db_;
  Options options_;

  void SetUp() override {
    dbname_ = testing::TempDir() + "db_impl_record_read_sample_test_308";
    options_.create_if_missing = true;
    // Destroy any previous database
    DestroyDB(dbname_, options_);
    Status s = DB::Open(options_, dbname_, &db_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  void TearDown() override {
    delete db_;
    DestroyDB(dbname_, options_);
  }

  DBImpl* impl() { return reinterpret_cast<DBImpl*>(db_); }
};

// Test RecordReadSample on an empty database with a simple key
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleOnEmptyDB_308) {
  // Should not crash when called on empty database
  impl()->RecordReadSample(Slice("testkey"));
}

// Test RecordReadSample after inserting some data
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleAfterPut_308) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "key1", "value1").ok());
  ASSERT_TRUE(db_->Put(write_opts, "key2", "value2").ok());
  ASSERT_TRUE(db_->Put(write_opts, "key3", "value3").ok());

  // RecordReadSample should not crash after data is inserted
  impl()->RecordReadSample(Slice("key1"));
  impl()->RecordReadSample(Slice("key2"));
  impl()->RecordReadSample(Slice("key3"));
}

// Test RecordReadSample with an empty key
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleEmptyKey_308) {
  impl()->RecordReadSample(Slice(""));
}

// Test RecordReadSample with a very long key
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleLongKey_308) {
  std::string long_key(10000, 'x');
  impl()->RecordReadSample(Slice(long_key));
}

// Test RecordReadSample called multiple times with the same key
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleRepeatedCalls_308) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "repeated", "val").ok());

  for (int i = 0; i < 100; i++) {
    impl()->RecordReadSample(Slice("repeated"));
  }

  // Verify the database is still functional
  std::string value;
  ReadOptions read_opts;
  ASSERT_TRUE(db_->Get(read_opts, "repeated", &value).ok());
  ASSERT_EQ("val", value);
}

// Test RecordReadSample with a key that doesn't exist in the DB
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleNonexistentKey_308) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "existing", "value").ok());

  // Should not crash with a key that doesn't exist
  impl()->RecordReadSample(Slice("nonexistent"));
}

// Test RecordReadSample after deleting keys
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleAfterDelete_308) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "delkey", "value").ok());
  ASSERT_TRUE(db_->Delete(write_opts, "delkey").ok());

  // Should not crash after deletion
  impl()->RecordReadSample(Slice("delkey"));
}

// Test RecordReadSample with binary data in key
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleBinaryKey_308) {
  std::string binary_key("\x00\x01\x02\x03", 4);
  impl()->RecordReadSample(Slice(binary_key));
}

// Test that database remains functional after RecordReadSample calls
TEST_F(DBImplRecordReadSampleTest_308, DBFunctionalAfterRecordReadSample_308) {
  WriteOptions write_opts;
  ReadOptions read_opts;

  ASSERT_TRUE(db_->Put(write_opts, "k1", "v1").ok());
  impl()->RecordReadSample(Slice("k1"));

  ASSERT_TRUE(db_->Put(write_opts, "k2", "v2").ok());
  impl()->RecordReadSample(Slice("k2"));

  std::string value;
  ASSERT_TRUE(db_->Get(read_opts, "k1", &value).ok());
  ASSERT_EQ("v1", value);

  ASSERT_TRUE(db_->Get(read_opts, "k2", &value).ok());
  ASSERT_EQ("v2", value);
}

// Test RecordReadSample with many different keys to potentially trigger compaction scheduling
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleManyKeys_308) {
  WriteOptions write_opts;
  // Insert a bunch of keys across potential level boundaries
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    std::string val = "val" + std::to_string(i);
    ASSERT_TRUE(db_->Put(write_opts, key, val).ok());
  }

  // Call RecordReadSample on many keys
  for (int i = 0; i < 1000; i++) {
    std::string key = "key" + std::to_string(i);
    impl()->RecordReadSample(Slice(key));
  }

  // Verify database is still consistent
  ReadOptions read_opts;
  std::string value;
  ASSERT_TRUE(db_->Get(read_opts, "key500", &value).ok());
  ASSERT_EQ("val500", value);
}

// Test RecordReadSample concurrent safety - calling after reopen
TEST_F(DBImplRecordReadSampleTest_308, RecordReadSampleAfterReopen_308) {
  WriteOptions write_opts;
  ASSERT_TRUE(db_->Put(write_opts, "persist", "data").ok());

  delete db_;
  db_ = nullptr;

  Status s = DB::Open(options_, dbname_, &db_);
  ASSERT_TRUE(s.ok()) << s.ToString();

  impl()->RecordReadSample(Slice("persist"));

  ReadOptions read_opts;
  std::string value;
  ASSERT_TRUE(db_->Get(read_opts, "persist", &value).ok());
  ASSERT_EQ("data", value);
}

}  // namespace leveldb
