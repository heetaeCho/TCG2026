// File: db_c_leveldb_write_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "leveldb/status.h"

// The C wrapper function under test.
// (If the declaration lives in a header in your tree, include that instead.)
extern "C" {
  struct leveldb_t;
  struct leveldb_writeoptions_t;
  struct leveldb_writebatch_t;
  void leveldb_write(leveldb_t* db,
                     const leveldb_writeoptions_t* options,
                     leveldb_writebatch_t* batch,
                     char** errptr);
  // If your build provides leveldb_free for C API-allocated strings, declare it:
  void leveldb_free(void* ptr);
}

using ::testing::_;
using ::testing::Eq;
using ::testing::Ref;
using ::testing::Return;

namespace {

// Mirror the minimal layout shown in the prompt so we can construct the C types.
// (If your project exposes these via a header, include that header instead.)
struct leveldb_t { leveldb::DB* rep; };
struct leveldb_writeoptions_t { leveldb::WriteOptions rep; };
struct leveldb_writebatch_t { leveldb::WriteBatch rep; };

// Google Mock for leveldb::DB focusing only on Write (the collaborator we verify).
class MockDB : public leveldb::DB {
 public:
  MOCK_METHOD(leveldb::Status, Write,
              (const leveldb::WriteOptions& options, leveldb::WriteBatch* updates),
              (override));

  // We don’t use other virtuals in these tests; provide safe stubs to satisfy linker
  // only if your build requires them. Otherwise, omit to keep tests minimal.
};

class LeveldbWriteTest_224 : public ::testing::Test {
 protected:
  LeveldbWriteTest_224() {
    cdb_.rep = &mock_db_;
    err_ = nullptr;
  }

  // Helper to free C-API error strings if leveldb_free exists in your build.
  static void MaybeFree(char* p) {
#ifdef leveldb_free  // If a macro/decl is available; otherwise try a weak pattern if needed.
    if (p) leveldb_free(p);
#else
    // In many trees, err strings are malloc’ed. If your build guarantees leveldb_free,
    // prefer that. Otherwise, skip freeing to avoid mismatch.
    (void)p;
#endif
  }

  MockDB mock_db_;
  leveldb_t cdb_{};
  leveldb_writeoptions_t copt_{};
  leveldb_writebatch_t cbatch_{};
  char* err_{nullptr};
};

// ------------------------ Tests ------------------------

TEST_F(LeveldbWriteTest_224, CallsWriteWithProvidedArgs_OKLeavesErrNull_224) {
  // Expect DB::Write to be called with the *exact* WriteOptions object we pass
  // and the pointer to the underlying WriteBatch.
  EXPECT_CALL(mock_db_, Write(Ref(copt_.rep), &cbatch_.rep))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_write(&cdb_, &copt_, &cbatch_, &err_);

  // Observable behavior: on OK status, C API convention keeps errptr == nullptr.
  EXPECT_EQ(err_, nullptr);
}

TEST_F(LeveldbWriteTest_224, PropagatesNonOKStatusIntoErrptr_224) {
  // Return a failing status from DB::Write.
  const auto kMsg = "simulated-io-error";
  EXPECT_CALL(mock_db_, Write(Ref(copt_.rep), &cbatch_.rep))
      .WillOnce(Return(leveldb::Status::IOError(kMsg)));

  leveldb_write(&cdb_, &copt_, &cbatch_, &err_);

  // Observable behavior: errptr should be set (non-null) when Write fails.
  ASSERT_NE(err_, nullptr);

  // Best-effort content check: error string usually contains the status message.
  // (We avoid assuming exact formatting.)
  std::string errstr(err_);
  EXPECT_NE(errstr.find(kMsg), std::string::npos);

  MaybeFree(err_);
  err_ = nullptr;
}

TEST_F(LeveldbWriteTest_224, NullErrptrIsHandled_NoCrashAndWriteStillCalled_224) {
  // Verify we still call Write even if caller passes a null errptr sink.
  EXPECT_CALL(mock_db_, Write(Ref(copt_.rep), &cbatch_.rep))
      .WillOnce(Return(leveldb::Status::IOError("anything")));

  // Pass nullptr for errptr; test asserts no crash and interaction occurred.
  leveldb_write(&cdb_, &copt_, &cbatch_, /*errptr=*/nullptr);
  SUCCEED();  // If we reached here, wrapper handled null errptr gracefully.
}

TEST_F(LeveldbWriteTest_224, WorksWithEmptyBatch_CallsWriteOnce_224) {
  // Without adding any ops to cbatch_.rep, Write should still be invoked.
  EXPECT_CALL(mock_db_, Write(Ref(copt_.rep), &cbatch_.rep))
      .WillOnce(Return(leveldb::Status::OK()));

  leveldb_write(&cdb_, &copt_, &cbatch_, &err_);
  EXPECT_EQ(err_, nullptr);
}

}  // namespace
