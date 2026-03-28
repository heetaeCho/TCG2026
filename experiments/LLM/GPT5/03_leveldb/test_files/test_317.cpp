// db_delete_test_317.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/write_batch.h"
#include "leveldb/slice.h"

using ::testing::_;
using ::testing::Invoke;
using ::testing::Return;

namespace {

// A mock DB that overrides only Write(). We deliberately DO NOT override Delete()
// so that the test exercises the real implementation from db_impl.cc.
class MockDB_317 : public leveldb::DB {
public:
  MOCK_METHOD(leveldb::Status, Write,
              (const leveldb::WriteOptions& options, leveldb::WriteBatch* updates),
              (override));
  // Silence pure-virtual destructor linkers on some toolchains.
  ~MockDB_317() override = default;
};

// Helper: Iterate over the batch and count how many deletes it contains for easy assertions.
struct CountingHandler_317 : public leveldb::WriteBatch::Handler {
  size_t put_count = 0;
  size_t delete_count = 0;
  std::vector<std::string> deleted_keys;

  void Put(const leveldb::Slice& /*key*/, const leveldb::Slice& /*value*/) override {
    ++put_count;
  }
  void Delete(const leveldb::Slice& key) override {
    ++delete_count;
    deleted_keys.emplace_back(key.ToString());
  }
};

}  // namespace

// --- Tests ---

// Verifies: Delete delegates to Write exactly once and passes a batch that contains
// exactly one deletion of the provided key. (_317)
TEST(DBDeleteTest_317, DelegatesToWriteWithSingleDelete_317) {
  MockDB_317 db;

  const std::string kKeyStr = "k1";
  const leveldb::Slice key(kKeyStr);
  leveldb::WriteOptions opts;  // default options

  EXPECT_CALL(db, Write(_, _))
      .WillOnce(Invoke([&](const leveldb::WriteOptions& got_opts,
                           leveldb::WriteBatch* batch) -> leveldb::Status {
        // Inspect batch via the public Iterate API (black-box).
        CountingHandler_317 handler;
        leveldb::Status it_s = batch->Iterate(&handler);
        EXPECT_TRUE(it_s.ok());
        EXPECT_EQ(handler.put_count, 0u);
        ASSERT_EQ(handler.delete_count, 1u);
        ASSERT_EQ(handler.deleted_keys.size(), 1u);
        EXPECT_EQ(handler.deleted_keys[0], kKeyStr);

        // Also ensure options were forwarded (no mutation expected).
        EXPECT_EQ(got_opts.sync, opts.sync);

        // Return OK so Delete() should return OK.
        return leveldb::Status::OK();
      }));

  leveldb::Status s = db.Delete(opts, key);
  EXPECT_TRUE(s.ok());
}

// Verifies: Delete propagates the exact Status returned by Write (error path). (_317)
TEST(DBDeleteTest_317, PropagatesWriteErrorStatus_317) {
  MockDB_317 db;

  leveldb::WriteOptions opts;
  const leveldb::Slice key("missing");

  // Create a non-OK status to propagate. (Use a common LevelDB factory.)
  const leveldb::Status kError = leveldb::Status::NotFound("no such key");

  EXPECT_CALL(db, Write(_, _))
      .WillOnce(Invoke([&](const leveldb::WriteOptions& /*got_opts*/,
                           leveldb::WriteBatch* batch) -> leveldb::Status {
        // Batch should still be well-formed: exactly one delete for "missing".
        CountingHandler_317 handler;
        leveldb::Status it_s = batch->Iterate(&handler);
        EXPECT_TRUE(it_s.ok());
        EXPECT_EQ(handler.put_count, 0u);
        ASSERT_EQ(handler.delete_count, 1u);
        ASSERT_EQ(handler.deleted_keys.size(), 1u);
        EXPECT_EQ(handler.deleted_keys[0], "missing");
        return kError;  // Simulate underlying write failure.
      }));

  leveldb::Status s = db.Delete(opts, key);
  EXPECT_FALSE(s.ok());
  // Optional sanity check that it's the same category (string content may vary by impl).
  EXPECT_EQ(s.code(), kError.code());
}

// Verifies: Delete forwards WriteOptions as-is (e.g., sync flag), and still builds a correct batch. (_317)
TEST(DBDeleteTest_317, ForwardsWriteOptions_317) {
  MockDB_317 db;

  leveldb::WriteOptions opts;
  opts.sync = true;  // non-default to verify passthrough
  const leveldb::Slice key("k-sync");

  EXPECT_CALL(db, Write(_, _))
      .WillOnce(Invoke([&](const leveldb::WriteOptions& got_opts,
                           leveldb::WriteBatch* batch) -> leveldb::Status {
        // Options forwarded unchanged.
        EXPECT_TRUE(got_opts.sync);

        // And batch contains the single delete for "k-sync".
        CountingHandler_317 handler;
        leveldb::Status it_s = batch->Iterate(&handler);
        EXPECT_TRUE(it_s.ok());
        EXPECT_EQ(handler.put_count, 0u);
        ASSERT_EQ(handler.delete_count, 1u);
        ASSERT_EQ(handler.deleted_keys.size(), 1u);
        EXPECT_EQ(handler.deleted_keys[0], "k-sync");

        return leveldb::Status::OK();
      }));

  leveldb::Status s = db.Delete(opts, key);
  EXPECT_TRUE(s.ok());
}

// Boundary case: empty key Slice is accepted; batch still contains exactly one delete with empty key. (_317)
TEST(DBDeleteTest_317, AllowsEmptyKey_317) {
  MockDB_317 db;

  leveldb::WriteOptions opts;
  const leveldb::Slice empty_key("");  // empty

  EXPECT_CALL(db, Write(_, _))
      .WillOnce(Invoke([&](const leveldb::WriteOptions& /*got_opts*/,
                           leveldb::WriteBatch* batch) -> leveldb::Status {
        CountingHandler_317 handler;
        leveldb::Status it_s = batch->Iterate(&handler);
        EXPECT_TRUE(it_s.ok());
        EXPECT_EQ(handler.put_count, 0u);
        ASSERT_EQ(handler.delete_count, 1u);
        ASSERT_EQ(handler.deleted_keys.size(), 1u);
        EXPECT_EQ(handler.deleted_keys[0], std::string());  // empty string
        return leveldb::Status::OK();
      }));

  leveldb::Status s = db.Delete(opts, empty_key);
  EXPECT_TRUE(s.ok());
}
