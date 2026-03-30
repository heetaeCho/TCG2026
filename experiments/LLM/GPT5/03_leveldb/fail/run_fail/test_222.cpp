// File: leveldb_c_put_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstring>
#include <string>

#include "leveldb/db.h"   // For leveldb::DB, Status, Slice, WriteOptions

using ::testing::_;
using ::testing::Return;
using ::testing::Truly;

extern "C" {
// Forward declare the C API under test (provided by db/c.cc)
struct leveldb_t { leveldb::DB* rep; };
struct leveldb_writeoptions_t { leveldb::WriteOptions rep; };

void leveldb_put(leveldb_t* db,
                 const leveldb_writeoptions_t* options,
                 const char* key, size_t keylen,
                 const char* val, size_t vallen,
                 char** errptr);
}

// ---- Test doubles & helpers ----

class MockDB : public leveldb::DB {
public:
  MOCK_METHOD(leveldb::Status, Put,
              (const leveldb::WriteOptions&,
               const leveldb::Slice& key,
               const leveldb::Slice& value),
              (override));

  // Provide default (unused) overrides to satisfy linker if needed.
  MOCK_METHOD(leveldb::Status, Delete,
              (const leveldb::WriteOptions&, const leveldb::Slice&), (override));
  MOCK_METHOD(leveldb::Status, Write,
              (const leveldb::WriteOptions&, leveldb::WriteBatch*), (override));
  MOCK_METHOD(leveldb::Status, Get,
              (const leveldb::ReadOptions&, const leveldb::Slice&, std::string*),
              (override));
  MOCK_METHOD(leveldb::Iterator*, NewIterator,
              (const leveldb::ReadOptions&), (override));
  MOCK_METHOD(const leveldb::Snapshot*, GetSnapshot, (), (override));
  MOCK_METHOD(void, ReleaseSnapshot, (const leveldb::Snapshot*), (override));
  MOCK_METHOD(bool, GetProperty,
              (const leveldb::Slice&, std::string*), (override));
  MOCK_METHOD(void, GetApproximateSizes,
              (const leveldb::Range*, int, uint64_t*), (override));
  MOCK_METHOD(void, CompactRange,
              (const leveldb::Slice*, const leveldb::Slice*), (override));
};

// Slice content matcher: compares size and bytes.
static auto SliceEq(const char* data, size_t len) {
  return Truly([data, len](const leveldb::Slice& s) {
    return s.size() == len &&
           ((len == 0) || std::memcmp(s.data(), data, len) == 0);
  });
}

// ---- Test fixture ----

class LeveldbCPutTest_222 : public ::testing::Test {
protected:
  MockDB mock_db_;
  leveldb_t c_db_;
  leveldb_writeoptions_t c_wopt_;

  void SetUp() override {
    c_db_.rep = &mock_db_;
    c_wopt_.rep = leveldb::WriteOptions{};
  }
};

// ---- Tests ----

// Verifies normal operation: forwards WriteOptions/key/value to DB::Put.
TEST_F(LeveldbCPutTest_222, ForwardsArgsAndCallsPut_222) {
  const char kKey[] = "alpha";
  const char kVal[] = "bravo";
  c_wopt_.rep.sync = true;  // Distinctive option to verify forwarding

  EXPECT_CALL(mock_db_,
              Put(Truly([this](const leveldb::WriteOptions& got) {
                     return got.sync == c_wopt_.rep.sync;
                   }),
                  SliceEq(kKey, sizeof(kKey) - 1),
                  SliceEq(kVal, sizeof(kVal) - 1)))
      .WillOnce(Return(leveldb::Status::OK()));

  // errptr is optional; passing nullptr must be safe/observable (no crash).
  leveldb_put(&c_db_, &c_wopt_, kKey, sizeof(kKey) - 1,
              kVal, sizeof(kVal) - 1, /*errptr=*/nullptr);
}

// Zero-length key/value boundary: still forwarded exactly to DB::Put.
TEST_F(LeveldbCPutTest_222, ZeroLengthKeyAndValueAreForwarded_222) {
  const char* kKey = "";
  const char* kVal = "";

  EXPECT_CALL(mock_db_,
              Put(_, SliceEq(kKey, 0), SliceEq(kVal, 0)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&c_db_, &c_wopt_, kKey, 0, kVal, 0, /*errptr=*/nullptr);
}

// errptr handling boundary: providing a non-null errptr must be safe.
// When DB::Put returns OK, many C APIs leave errptr as nullptr.
// We assert only that the call doesn't write a non-null error on success.
TEST_F(LeveldbCPutTest_222, ErrptrRemainsNullOnSuccess_222) {
  const char kKey[] = "k";
  const char kVal[] = "v";
  char* err = nullptr;

  EXPECT_CALL(mock_db_, Put(_, _, _))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_put(&c_db_, &c_wopt_, kKey, 1, kVal, 1, &err);

  // Observable effect: for success, err should remain nullptr.
  // (If the actual SaveError differs, this will reflect real behavior.)
  EXPECT_EQ(err, nullptr);
}

// Non-OK status path: providing errptr should allow an error to be surfaced.
// We only assert that a non-null is possible/observable when Put fails.
TEST_F(LeveldbCPutTest_222, ErrptrMayBeSetOnFailure_222) {
  const char kKey[] = "fail-key";
  const char kVal[] = "fail-val";
  char* err = nullptr;

  // Construct a generic non-OK status; message content is not asserted.
  leveldb::Status not_ok = leveldb::Status::IOError("boom");

  EXPECT_CALL(mock_db_, Put(_, _, _))
      .WillOnce(Return(not_ok));

  leveldb_put(&c_db_, &c_wopt_, kKey, sizeof(kKey) - 1,
              kVal, sizeof(kVal) - 1, &err);

  // We do not assert the message; only that an error pointer may be produced.
  // (If SaveError clears/allocates differently, this expectation will capture it.)
  EXPECT_NE(err, nullptr);

  // If an allocation occurred, test code that owns err should free it if required
  // by your project's conventions. If not applicable, remove the free.
  if (err) {
    // Many LevelDB C APIs allocate with malloc; free is typically appropriate.
    free(err);
  }
}

// Defensive/death tests for invalid pointers (observable crash behavior).
// If your test environment doesn't support death tests or treats UB differently,
// you can conditionally disable these.
#ifndef NDEBUG
TEST_F(LeveldbCPutTest_222, DiesOnNullDb_222) {
  const char k[] = "k";
  const char v[] = "v";
  EXPECT_DEATH(
      { leveldb_put(nullptr, &c_wopt_, k, 1, v, 1, nullptr); }, "");
}

TEST_F(LeveldbCPutTest_222, DiesOnNullWriteOptions_222) {
  const char k[] = "k";
  const char v[] = "v";
  EXPECT_DEATH(
      { leveldb_put(&c_db_, nullptr, k, 1, v, 1, nullptr); }, "");
}
#endif
