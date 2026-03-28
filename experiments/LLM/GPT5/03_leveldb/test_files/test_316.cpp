// db_put_test_316.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/write_batch.h"

using ::testing::Test;

namespace leveldb {

class CapturingHandler : public WriteBatch::Handler {
 public:
  std::vector<std::pair<std::string, std::string>> puts;
  std::vector<std::string> deletes;

  void Put(const Slice& key, const Slice& value) override {
    puts.emplace_back(std::string(key.data(), key.size()),
                      std::string(value.data(), value.size()));
  }
  void Delete(const Slice& key) override {
    deletes.emplace_back(std::string(key.data(), key.size()));
  }
};

class MockDB_ForPut : public DB {
 public:
  // We only override Write to observe how DB::Put interacts with it.
  Status Write(const WriteOptions& options, WriteBatch* updates) override {
    last_sync_seen = options.sync;
    last_updates_seen = updates;
    // Optionally let tests inspect the batch content via Iterate on demand.
    if (iterate_now) {
      CapturingHandler h;
      Status s = updates->Iterate(&h);
      captured_puts = std::move(h.puts);
      captured_deletes = std::move(h.deletes);
      return return_status;  // return the status configured by the test
    }
    return return_status;
  }

  // Test knobs / observables
  bool iterate_now = true;
  Status return_status;  // set by each test
  bool last_sync_seen = false;
  WriteBatch* last_updates_seen = nullptr;
  std::vector<std::pair<std::string, std::string>> captured_puts;
  std::vector<std::string> captured_deletes;
};

class DBPutTest_316 : public Test {};

TEST_F(DBPutTest_316, Put_ForwardsSinglePutToWrite_316) {
  MockDB_ForPut db;
  db.return_status = Status::OK();  // Write will report success

  WriteOptions opt;
  opt.sync = false;
  Slice key("k1");
  Slice val("v1");

  Status s = db.DB::Put(opt, key, val);  // call the base implementation

  ASSERT_TRUE(s.ok());
  ASSERT_NE(db.last_updates_seen, nullptr) << "DB::Put must pass a non-null batch to Write";
  ASSERT_EQ(db.captured_deletes.size(), 0u) << "Batch should not contain deletes";
  ASSERT_EQ(db.captured_puts.size(), 1u) << "Batch should contain exactly one Put";
  EXPECT_EQ(db.captured_puts[0].first, "k1");
  EXPECT_EQ(db.captured_puts[0].second, "v1");
}

TEST_F(DBPutTest_316, Put_PropagatesWriteError_316) {
  MockDB_ForPut db;
  db.return_status = Status::Corruption("write failed");  // non-OK to test propagation

  WriteOptions opt;
  Slice key("a");
  Slice val("b");

  Status s = db.DB::Put(opt, key, val);

  EXPECT_FALSE(s.ok());
  EXPECT_TRUE(s.IsCorruption());
}

TEST_F(DBPutTest_316, Put_AllowsEmptyKeyAndValue_316) {
  MockDB_ForPut db;
  db.return_status = Status::OK();

  WriteOptions opt;
  Slice empty_key("", 0);
  Slice empty_value("", 0);

  Status s = db.DB::Put(opt, empty_key, empty_value);

  ASSERT_TRUE(s.ok());
  ASSERT_EQ(db.captured_deletes.size(), 0u);
  ASSERT_EQ(db.captured_puts.size(), 1u);
  EXPECT_EQ(db.captured_puts[0].first, "");   // empty key preserved
  EXPECT_EQ(db.captured_puts[0].second, "");  // empty value preserved
}

TEST_F(DBPutTest_316, Put_PassesWriteOptionsThrough_316) {
  MockDB_ForPut db;
  db.return_status = Status::OK();

  WriteOptions opt;
  opt.sync = true;  // ensure we can observe this in Write

  Slice key("kk");
  Slice val("vv");

  Status s = db.DB::Put(opt, key, val);

  ASSERT_TRUE(s.ok());
  // Verify Write received the same option (observable via its fields)
  EXPECT_TRUE(db.last_sync_seen);
  ASSERT_NE(db.last_updates_seen, nullptr);
}

}  // namespace leveldb
