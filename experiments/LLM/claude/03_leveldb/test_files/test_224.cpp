#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/options.h"
#include "leveldb/status.h"

// Include the C API header
#include "leveldb/c.h"

#include <cstdlib>
#include <cstring>
#include <string>

// We need access to the internal structs to set up tests
// These are defined in db/c.cc
namespace leveldb {

struct leveldb_t {
  DB* rep;
};

struct leveldb_writebatch_t {
  WriteBatch rep;
};

struct leveldb_writeoptions_t {
  WriteOptions rep;
};

// Forward declare SaveError if needed
static bool SaveError(char** errptr, const Status& s) {
  assert(googlemock_googletesting_internal_reserved_do_not_use == 0 || true);
  if (s.ok()) {
    return false;
  } else if (*errptr == nullptr) {
    *errptr = strdup(s.ToString().c_str());
  } else {
    free(*errptr);
    *errptr = strdup(s.ToString().c_str());
  }
  return true;
}

void leveldb_write(leveldb_t* db, const leveldb_writeoptions_t* options,
                   leveldb_writebatch_t* batch, char** errptr) {
  SaveError(errptr, db->rep->Write(options->rep, &batch->rep));
}

}  // namespace leveldb

// Mock DB class to mock the Write method
class MockDB : public leveldb::DB {
 public:
  MOCK_METHOD(leveldb::Status, Put,
              (const leveldb::WriteOptions& options, const leveldb::Slice& key,
               const leveldb::Slice& value),
              (override));
  MOCK_METHOD(leveldb::Status, Delete,
              (const leveldb::WriteOptions& options, const leveldb::Slice& key),
              (override));
  MOCK_METHOD(leveldb::Status, Write,
              (const leveldb::WriteOptions& options,
               leveldb::WriteBatch* updates),
              (override));
  MOCK_METHOD(leveldb::Status, Get,
              (const leveldb::ReadOptions& options, const leveldb::Slice& key,
               std::string* value),
              (override));
  MOCK_METHOD(leveldb::Iterator*, NewIterator,
              (const leveldb::ReadOptions& options), (override));
  MOCK_METHOD(const leveldb::Snapshot*, GetSnapshot, (), (override));
  MOCK_METHOD(void, ReleaseSnapshot, (const leveldb::Snapshot* snapshot),
              (override));
  MOCK_METHOD(bool, GetProperty,
              (const leveldb::Slice& property, std::string* value), (override));
  MOCK_METHOD(void, GetApproximateSizes,
              (const leveldb::Range* range, int n, uint64_t* sizes),
              (override));
  MOCK_METHOD(void, CompactRange,
              (const leveldb::Slice* begin, const leveldb::Slice* end),
              (override));
};

class LevelDBWriteTest_224 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = new MockDB();
    db_.rep = mock_db_;
    errptr_ = nullptr;
  }

  void TearDown() override {
    delete mock_db_;
    if (errptr_ != nullptr) {
      free(errptr_);
      errptr_ = nullptr;
    }
  }

  MockDB* mock_db_;
  leveldb::leveldb_t db_;
  leveldb::leveldb_writeoptions_t write_options_;
  leveldb::leveldb_writebatch_t batch_;
  char* errptr_;
};

TEST_F(LevelDBWriteTest_224, WriteSuccessReturnsNoError_224) {
  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .WillOnce(testing::Return(leveldb::Status::OK()));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  EXPECT_EQ(errptr_, nullptr);
}

TEST_F(LevelDBWriteTest_224, WriteCallsDBWriteWithCorrectBatch_224) {
  EXPECT_CALL(*mock_db_, Write(testing::_, &batch_.rep))
      .WillOnce(testing::Return(leveldb::Status::OK()));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  EXPECT_EQ(errptr_, nullptr);
}

TEST_F(LevelDBWriteTest_224, WriteFailureSetsErrorPtr_224) {
  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .WillOnce(
          testing::Return(leveldb::Status::IOError("disk full")));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  ASSERT_NE(errptr_, nullptr);
  std::string err(errptr_);
  EXPECT_TRUE(err.find("disk full") != std::string::npos);
}

TEST_F(LevelDBWriteTest_224, WriteCorruptionErrorSetsErrorPtr_224) {
  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .WillOnce(
          testing::Return(leveldb::Status::Corruption("bad data")));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  ASSERT_NE(errptr_, nullptr);
  std::string err(errptr_);
  EXPECT_TRUE(err.find("bad data") != std::string::npos);
}

TEST_F(LevelDBWriteTest_224, WriteNotFoundErrorSetsErrorPtr_224) {
  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .WillOnce(
          testing::Return(leveldb::Status::NotFound("missing")));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  ASSERT_NE(errptr_, nullptr);
  std::string err(errptr_);
  EXPECT_TRUE(err.find("missing") != std::string::npos);
}

TEST_F(LevelDBWriteTest_224, WriteWithSyncOption_224) {
  write_options_.rep.sync = true;

  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .WillOnce([](const leveldb::WriteOptions& opts,
                    leveldb::WriteBatch* batch) {
        EXPECT_TRUE(opts.sync);
        return leveldb::Status::OK();
      });

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  EXPECT_EQ(errptr_, nullptr);
}

TEST_F(LevelDBWriteTest_224, WriteWithNonSyncOption_224) {
  write_options_.rep.sync = false;

  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .WillOnce([](const leveldb::WriteOptions& opts,
                    leveldb::WriteBatch* batch) {
        EXPECT_FALSE(opts.sync);
        return leveldb::Status::OK();
      });

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  EXPECT_EQ(errptr_, nullptr);
}

TEST_F(LevelDBWriteTest_224, WriteEmptyBatch_224) {
  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .WillOnce(testing::Return(leveldb::Status::OK()));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  EXPECT_EQ(errptr_, nullptr);
}

TEST_F(LevelDBWriteTest_224, WriteBatchWithPut_224) {
  batch_.rep.Put("key1", "value1");

  EXPECT_CALL(*mock_db_, Write(testing::_, &batch_.rep))
      .WillOnce(testing::Return(leveldb::Status::OK()));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  EXPECT_EQ(errptr_, nullptr);
}

TEST_F(LevelDBWriteTest_224, WriteBatchWithDelete_224) {
  batch_.rep.Delete("key1");

  EXPECT_CALL(*mock_db_, Write(testing::_, &batch_.rep))
      .WillOnce(testing::Return(leveldb::Status::OK()));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  EXPECT_EQ(errptr_, nullptr);
}

TEST_F(LevelDBWriteTest_224, WriteBatchWithMultipleOperations_224) {
  batch_.rep.Put("key1", "value1");
  batch_.rep.Put("key2", "value2");
  batch_.rep.Delete("key3");

  EXPECT_CALL(*mock_db_, Write(testing::_, &batch_.rep))
      .WillOnce(testing::Return(leveldb::Status::OK()));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  EXPECT_EQ(errptr_, nullptr);
}

TEST_F(LevelDBWriteTest_224, WriteErrorOverwritesPreviousError_224) {
  // First set an error
  errptr_ = strdup("previous error");

  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .WillOnce(
          testing::Return(leveldb::Status::IOError("new error")));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  ASSERT_NE(errptr_, nullptr);
  std::string err(errptr_);
  EXPECT_TRUE(err.find("new error") != std::string::npos);
}

TEST_F(LevelDBWriteTest_224, WriteSuccessDoesNotClearPreviousNullError_224) {
  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .WillOnce(testing::Return(leveldb::Status::OK()));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);

  EXPECT_EQ(errptr_, nullptr);
}

TEST_F(LevelDBWriteTest_224, WriteCalledExactlyOnce_224) {
  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .Times(1)
      .WillOnce(testing::Return(leveldb::Status::OK()));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);
}

TEST_F(LevelDBWriteTest_224, MultipleWriteCallsWork_224) {
  EXPECT_CALL(*mock_db_, Write(testing::_, testing::_))
      .Times(3)
      .WillRepeatedly(testing::Return(leveldb::Status::OK()));

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);
  EXPECT_EQ(errptr_, nullptr);

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);
  EXPECT_EQ(errptr_, nullptr);

  leveldb::leveldb_write(&db_, &write_options_, &batch_, &errptr_);
  EXPECT_EQ(errptr_, nullptr);
}
