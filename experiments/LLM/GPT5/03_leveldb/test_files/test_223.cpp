// File: c_api_leveldb_delete_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/slice.h"
#include "leveldb/status.h"
#include "leveldb/options.h"
#include "leveldb/db.h"

// We only exercise the public C wrapper function.
// Declare the C API symbol we are testing and the C-API structs we need.
extern "C" {
// Prototype of the function under test.
void leveldb_delete(struct leveldb_t* db,
                    const struct leveldb_writeoptions_t* options,
                    const char* key, size_t keylen,
                    char** errptr);
}

// Re-create the minimal C-API structs exactly as exposed by the partial code.
// (This mirrors db/c.cc snippets provided in the prompt.)
struct leveldb_t { leveldb::DB* rep; };
struct leveldb_writeoptions_t { leveldb::WriteOptions rep; };

using ::testing::_;
using ::testing::Return;
using ::testing::Truly;

namespace {

// A lightweight mock for leveldb::DB that stubs only what we need.
// We treat DB as a black box and verify only observable calls/args.
class MockDB : public leveldb::DB {
 public:
  MOCK_METHOD(leveldb::Status, Delete,
              (const leveldb::WriteOptions& options, const leveldb::Slice& key),
              (override));

  // Provide default implementations for other virtuals we won't use.
  // They return "NotSupported" to keep the mock simple and non-intrusive.
  leveldb::Status Put(const leveldb::WriteOptions&, const leveldb::Slice&,
                      const leveldb::Slice&) override {
    return leveldb::Status::NotSupported("unused");
  }
  leveldb::Status Write(const leveldb::WriteOptions&, leveldb::WriteBatch*) override {
    return leveldb::Status::NotSupported("unused");
  }
  leveldb::Status Get(const leveldb::ReadOptions&, const leveldb::Slice&,
                      std::string*) override {
    return leveldb::Status::NotSupported("unused");
  }
  leveldb::Iterator* NewIterator(const leveldb::ReadOptions&) override { return nullptr; }
  const leveldb::Snapshot* GetSnapshot() override { return nullptr; }
  void ReleaseSnapshot(const leveldb::Snapshot*) override {}
  bool GetProperty(const leveldb::Slice&, std::string*) override { return false; }
  void GetApproximateSizes(const leveldb::Range*, int, uint64_t*) override {}
  void CompactRange(const leveldb::Slice*, const leveldb::Slice*) override {}
};

// Helpful matcher to verify the Slice matches an exact byte sequence.
::testing::Matcher<const leveldb::Slice&> SliceEq(const void* data, size_t n) {
  return Truly([data, n](const leveldb::Slice& s) {
    if (s.size() != n) return false;
    if (n == 0) return true;
    return std::memcmp(s.data(), data, n) == 0;
  });
}

class LeveldbCDeleteTest_223 : public ::testing::Test {
 protected:
  void SetUp() override {
    mock_db_ = std::make_unique<MockDB>();
    cdb_.rep = mock_db_.get();
    wopt_.rep = leveldb::WriteOptions{};  // default
    err_ = nullptr;
  }

  void TearDown() override {
    if (err_) {
      // The C-API typically allocates error strings; avoid leaks in tests.
      std::free(err_);
      err_ = nullptr;
    }
  }

  std::unique_ptr<MockDB> mock_db_;
  leveldb_t cdb_{};
  leveldb_writeoptions_t wopt_{};
  char* err_{};
};

}  // namespace

// --- Tests ---

// 1) Normal operation: forwards key/len & options to DB::Delete; on OK, errptr stays null.
TEST_F(LeveldbCDeleteTest_223, ForwardsArgs_OkLeavesErrNull_223) {
  // Arrange
  const char key[] = "alpha";
  wopt_.rep.sync = true;  // observable field in public WriteOptions

  EXPECT_CALL(*mock_db_,
              Delete(Truly([](const leveldb::WriteOptions& o){ return o.sync; }),
                     SliceEq(key, sizeof(key) - 1)))
      .WillOnce(Return(leveldb::Status::OK()));

  // Act
  leveldb_delete(&cdb_, &wopt_, key, sizeof(key) - 1, &err_);

  // Assert
  EXPECT_EQ(err_, nullptr);
}

// 2) Error case: if DB::Delete returns non-OK, errptr becomes non-null (message content is opaque).
TEST_F(LeveldbCDeleteTest_223, ErrorFromDB_SetsErrPtr_223) {
  const char key[] = "missing";

  EXPECT_CALL(*mock_db_,
              Delete(_, SliceEq(key, sizeof(key) - 1)))
      .WillOnce(Return(leveldb::Status::NotFound("nope")));

  leveldb_delete(&cdb_, &wopt_, key, sizeof(key) - 1, &err_);

  ASSERT_NE(err_, nullptr);  // presence of an error string is the observable effect
}

// 3) Boundary: empty key (keylen=0) must be passed through, and OK leaves err null.
TEST_F(LeveldbCDeleteTest_223, EmptyKey_PassedThrough_SizeZero_223) {
  const char* key = nullptr;  // allowed when keylen == 0

  EXPECT_CALL(*mock_db_,
              Delete(_, SliceEq(key, 0)))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_delete(&cdb_, &wopt_, key, 0, &err_);

  EXPECT_EQ(err_, nullptr);
}

// 4) Binary key containing NULs: ensure keylen is honored exactly (no C-string semantics).
TEST_F(LeveldbCDeleteTest_223, BinaryKey_WithEmbeddedNuls_223) {
  const unsigned char k[] = {0x00, 'A', 0x00, 'B'};  // 4 bytes

  EXPECT_CALL(*mock_db_,
              Delete(_, SliceEq(k, sizeof(k))))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_delete(&cdb_, &wopt_,
                 reinterpret_cast<const char*>(k), sizeof(k), &err_);

  EXPECT_EQ(err_, nullptr);
}
