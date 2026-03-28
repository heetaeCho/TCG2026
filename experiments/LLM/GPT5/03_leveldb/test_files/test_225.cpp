// db_c_get_test.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdlib>
#include <cstring>
#include <string>

// LevelDB headers (paths may vary by your repo layout)
#include "leveldb/db.h"
#include "leveldb/status.h"
#include "leveldb/slice.h"
#include "leveldb/options.h"  // for ReadOptions

using ::testing::_;
using ::testing::DoAll;
using ::testing::Return;
using ::testing::SetArgPointee;

extern "C" {
// C API structs and function under test (as provided in the prompt)
struct leveldb_t { leveldb::DB* rep; };
struct leveldb_readoptions_t { leveldb::ReadOptions rep; };

// Provided function under test
char* leveldb_get(leveldb_t* db,
                  const leveldb_readoptions_t* options,
                  const char* key,
                  size_t keylen,
                  size_t* vallen,
                  char** errptr);
}

// ---- Mock for external collaborator: leveldb::DB ----
class MockDB_225 : public leveldb::DB {
public:
  MOCK_METHOD(leveldb::Status, Get,
              (const leveldb::ReadOptions& options,
               const leveldb::Slice& key,
               std::string* value),
              (override));

  // The remaining virtuals aren’t used by these tests; provide stubs to satisfy linker.
  MOCK_METHOD(leveldb::Status, Put,
              (const leveldb::WriteOptions&, const leveldb::Slice&, const leveldb::Slice&),
              (override));
  MOCK_METHOD(leveldb::Status, Delete,
              (const leveldb::WriteOptions&, const leveldb::Slice&),
              (override));
  MOCK_METHOD(leveldb::Status, Write,
              (const leveldb::WriteOptions&, leveldb::WriteBatch*),
              (override));
  MOCK_METHOD(leveldb::Iterator*, NewIterator,
              (const leveldb::ReadOptions&), (override));
  MOCK_METHOD(const leveldb::Snapshot*, GetSnapshot, (), (override));
  MOCK_METHOD(void, ReleaseSnapshot, (const leveldb::Snapshot*), (override));
  MOCK_METHOD(bool, GetProperty, (const leveldb::Slice&, std::string*), (override));
  MOCK_METHOD(void, GetApproximateSizes,
              (const leveldb::Range*, int, uint64_t*), (override));
  MOCK_METHOD(void, CompactRange,
              (const leveldb::Slice*, const leveldb::Slice*), (override));

  // Ensure a virtual destructor
  ~MockDB_225() override = default;
};

class LeveldbGetTest_225 : public ::testing::Test {
protected:
  void SetUp() override {
    mock_db_ = new MockDB_225();
    cdb_.rep = mock_db_;
    // Default: err_ is null and vallen_ = some sentinel
    err_ = nullptr;
    vallen_ = 777; // sentinel to ensure it’s overwritten appropriately
  }

  void TearDown() override {
    // If an error string was set by the C API, free it per LevelDB C API convention.
    if (err_) {
      std::free(err_);
      err_ = nullptr;
    }
    // mock_db_ owned by test; delete it after test completes
    delete mock_db_;
    mock_db_ = nullptr;
    cdb_.rep = nullptr;
  }

  MockDB_225* mock_db_ = nullptr;
  leveldb_t cdb_{};
  leveldb_readoptions_t ro_{};
  char* err_ = nullptr;
  size_t vallen_ = 0;
};

// Normal operation: OK -> returns allocated copy, sets *vallen to size, leaves errptr untouched.
TEST_F(LeveldbGetTest_225, Ok_ReturnsValueAndSetsVallen_225) {
  const std::string kKey = "my-key";
  const std::string kValue = "hello-world";

  EXPECT_CALL(*mock_db_, Get(_, _, _))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(kValue), Return(leveldb::Status::OK())));

  char* out = leveldb_get(&cdb_, &ro_, kKey.data(), kKey.size(), &vallen_, &err_);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(vallen_, kValue.size());
  EXPECT_EQ(std::string(out, out + vallen_), kValue);
  EXPECT_EQ(err_, nullptr);

  std::free(out);
}

// Boundary: OK with empty value -> returns non-null (allocated), *vallen == 0, no error.
TEST_F(LeveldbGetTest_225, Ok_EmptyValue_VallenZero_NoError_225) {
  const std::string kKey = "k";

  EXPECT_CALL(*mock_db_, Get(_, _, _))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(std::string()), Return(leveldb::Status::OK())));

  char* out = leveldb_get(&cdb_, &ro_, kKey.data(), kKey.size(), &vallen_, &err_);

  ASSERT_NE(out, nullptr);        // CopyString("") should still return a valid C string
  EXPECT_EQ(vallen_, 0u);
  EXPECT_EQ(std::string(out), ""); // zero-length
  EXPECT_EQ(err_, nullptr);

  std::free(out);
}

// NotFound case: returns nullptr, *vallen == 0, errptr remains null.
TEST_F(LeveldbGetTest_225, NotFound_ReturnsNull_VallenZero_NoError_225) {
  const std::string kKey = "absent";

  EXPECT_CALL(*mock_db_, Get(_, _, _))
      .Times(1)
      .WillOnce(Return(leveldb::Status::NotFound("nope")));

  char* out = leveldb_get(&cdb_, &ro_, kKey.data(), kKey.size(), &vallen_, &err_);

  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(vallen_, 0u);
  EXPECT_EQ(err_, nullptr);
}

// General error (e.g., IOError): returns nullptr, *vallen == 0, errptr becomes non-null.
TEST_F(LeveldbGetTest_225, IOError_ReturnsNull_VallenZero_ErrptrSet_225) {
  const std::string kKey = "k";

  EXPECT_CALL(*mock_db_, Get(_, _, _))
      .Times(1)
      .WillOnce(Return(leveldb::Status::IOError("boom")));

  char* out = leveldb_get(&cdb_, &ro_, kKey.data(), kKey.size(), &vallen_, &err_);

  EXPECT_EQ(out, nullptr);
  EXPECT_EQ(vallen_, 0u);
  ASSERT_NE(err_, nullptr);  // SaveError should have populated this for non-NotFound errors
}

// Success path must not touch errptr (even if it’s already non-null).
// We pre-populate err_ and ensure it remains unchanged after success.
TEST_F(LeveldbGetTest_225, Ok_DoesNotModifyExistingErrptr_225) {
  // Pre-populate err_ with some memory the API didn’t allocate.
  // To keep things simple and safe to free, allocate a small buffer here.
  err_ = static_cast<char*>(std::malloc(8));
  ASSERT_NE(err_, nullptr);
  std::memcpy(err_, "x", 2); // small sentinel content

  const std::string kKey = "k";
  const std::string kValue = "v";

  EXPECT_CALL(*mock_db_, Get(_, _, _))
      .Times(1)
      .WillOnce(DoAll(SetArgPointee<2>(kValue), Return(leveldb::Status::OK())));

  char* out = leveldb_get(&cdb_, &ro_, kKey.data(), kKey.size(), &vallen_, &err_);

  ASSERT_NE(out, nullptr);
  EXPECT_EQ(vallen_, 1u);
  // err_ pointer should be unchanged (function doesn’t touch it on success)
  ASSERT_NE(err_, nullptr);

  std::free(out);
}
