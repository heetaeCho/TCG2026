#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "leveldb/db.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"
#include "leveldb/status.h"

#include <string>
#include <cstdlib>
#include <cstring>

// These are the C structs from db/c.cc
struct leveldb_t {
  leveldb::DB* rep;
};

struct leveldb_iterator_t {
  leveldb::Iterator* rep;
};

struct leveldb_readoptions_t {
  leveldb::ReadOptions rep;
};

// Declaration of the function under test
extern "C" {
  leveldb_iterator_t* leveldb_create_iterator(
      leveldb_t* db, const leveldb_readoptions_t* options);
}

// Actual implementation of the function under test (from c.cc)
leveldb_iterator_t* leveldb_create_iterator(
    leveldb_t* db, const leveldb_readoptions_t* options) {
  leveldb_iterator_t* result = new leveldb_iterator_t;
  result->rep = db->rep->NewIterator(options->rep);
  return result;
}

// Mock DB to control NewIterator behavior
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
              (const leveldb::WriteOptions& options, leveldb::WriteBatch* updates),
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
              (const leveldb::Range* range, int n, uint64_t* sizes), (override));
  MOCK_METHOD(void, CompactRange,
              (const leveldb::Slice* begin, const leveldb::Slice* end),
              (override));
};

// A simple mock iterator to be returned by NewIterator
class MockIterator : public leveldb::Iterator {
 public:
  MOCK_METHOD(bool, Valid, (), (const, override));
  MOCK_METHOD(void, SeekToFirst, (), (override));
  MOCK_METHOD(void, SeekToLast, (), (override));
  MOCK_METHOD(void, Seek, (const leveldb::Slice& target), (override));
  MOCK_METHOD(void, Next, (), (override));
  MOCK_METHOD(void, Prev, (), (override));
  MOCK_METHOD(leveldb::Slice, key, (), (const, override));
  MOCK_METHOD(leveldb::Slice, value, (), (const, override));
  MOCK_METHOD(leveldb::Status, status, (), (const, override));
};

class LevelDBCreateIteratorTest_226 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = new MockDB();
    db_wrapper_.rep = mock_db_;
    read_options_ = new leveldb_readoptions_t;
  }

  void TearDown() override {
    delete read_options_;
    delete mock_db_;
  }

  MockDB* mock_db_;
  leveldb_t db_wrapper_;
  leveldb_readoptions_t* read_options_;
};

TEST_F(LevelDBCreateIteratorTest_226, ReturnsNonNullResult_226) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_db_, NewIterator(::testing::_))
      .WillOnce(::testing::Return(mock_iter));

  leveldb_iterator_t* result = leveldb_create_iterator(&db_wrapper_, read_options_);

  ASSERT_NE(result, nullptr);

  delete result;
}

TEST_F(LevelDBCreateIteratorTest_226, ResultContainsIteratorFromDB_226) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_db_, NewIterator(::testing::_))
      .WillOnce(::testing::Return(mock_iter));

  leveldb_iterator_t* result = leveldb_create_iterator(&db_wrapper_, read_options_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->rep, mock_iter);

  delete result;
}

TEST_F(LevelDBCreateIteratorTest_226, NewIteratorCalledExactlyOnce_226) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_db_, NewIterator(::testing::_))
      .Times(1)
      .WillOnce(::testing::Return(mock_iter));

  leveldb_iterator_t* result = leveldb_create_iterator(&db_wrapper_, read_options_);

  ASSERT_NE(result, nullptr);
  delete result;
}

TEST_F(LevelDBCreateIteratorTest_226, PassesReadOptionsToNewIterator_226) {
  // Set a specific option to verify it gets passed through
  read_options_->rep.verify_checksums = true;
  read_options_->rep.fill_cache = false;

  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_db_, NewIterator(::testing::AllOf(
      ::testing::Field(&leveldb::ReadOptions::verify_checksums, true),
      ::testing::Field(&leveldb::ReadOptions::fill_cache, false))))
      .WillOnce(::testing::Return(mock_iter));

  leveldb_iterator_t* result = leveldb_create_iterator(&db_wrapper_, read_options_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->rep, mock_iter);

  delete result;
}

TEST_F(LevelDBCreateIteratorTest_226, DefaultReadOptions_226) {
  // Default read options: verify_checksums=false, fill_cache=true, snapshot=nullptr
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_db_, NewIterator(::testing::AllOf(
      ::testing::Field(&leveldb::ReadOptions::verify_checksums, false),
      ::testing::Field(&leveldb::ReadOptions::fill_cache, true),
      ::testing::Field(&leveldb::ReadOptions::snapshot, nullptr))))
      .WillOnce(::testing::Return(mock_iter));

  leveldb_iterator_t* result = leveldb_create_iterator(&db_wrapper_, read_options_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->rep, mock_iter);

  delete result;
}

TEST_F(LevelDBCreateIteratorTest_226, MultipleIteratorsAreIndependent_226) {
  MockIterator* mock_iter1 = new MockIterator();
  MockIterator* mock_iter2 = new MockIterator();
  EXPECT_CALL(*mock_db_, NewIterator(::testing::_))
      .WillOnce(::testing::Return(mock_iter1))
      .WillOnce(::testing::Return(mock_iter2));

  leveldb_iterator_t* result1 = leveldb_create_iterator(&db_wrapper_, read_options_);
  leveldb_iterator_t* result2 = leveldb_create_iterator(&db_wrapper_, read_options_);

  ASSERT_NE(result1, nullptr);
  ASSERT_NE(result2, nullptr);
  EXPECT_NE(result1, result2);
  EXPECT_EQ(result1->rep, mock_iter1);
  EXPECT_EQ(result2->rep, mock_iter2);
  EXPECT_NE(result1->rep, result2->rep);

  delete result1;
  delete result2;
}

TEST_F(LevelDBCreateIteratorTest_226, NullIteratorFromDB_226) {
  // If the DB returns a null iterator, the wrapper should still be created
  EXPECT_CALL(*mock_db_, NewIterator(::testing::_))
      .WillOnce(::testing::Return(nullptr));

  leveldb_iterator_t* result = leveldb_create_iterator(&db_wrapper_, read_options_);

  ASSERT_NE(result, nullptr);
  EXPECT_EQ(result->rep, nullptr);

  delete result;
}

TEST_F(LevelDBCreateIteratorTest_226, IteratorIsUsable_226) {
  MockIterator* mock_iter = new MockIterator();
  EXPECT_CALL(*mock_db_, NewIterator(::testing::_))
      .WillOnce(::testing::Return(mock_iter));

  // Expect the iterator to be usable after creation
  EXPECT_CALL(*mock_iter, SeekToFirst()).Times(1);
  EXPECT_CALL(*mock_iter, Valid()).WillOnce(::testing::Return(false));

  leveldb_iterator_t* result = leveldb_create_iterator(&db_wrapper_, read_options_);
  ASSERT_NE(result, nullptr);

  result->rep->SeekToFirst();
  EXPECT_FALSE(result->rep->Valid());

  delete result;
}
