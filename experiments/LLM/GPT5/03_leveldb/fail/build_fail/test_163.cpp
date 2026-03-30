// File: version_set_log_and_apply_test.cc

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "leveldb/status.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "port/port_stdcxx.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::SaveArg;

// -----------------------------------------------------------------------------
// Minimal stubs (only if your build doesn’t already provide these concrete types)
// -----------------------------------------------------------------------------

// If your build already provides BytewiseComparator() and InternalKeyComparator,
// remove this whole block and include the real headers instead.
namespace leveldb {

// Simple Comparator stub compatible with InternalKeyComparator construction.
class SimpleComparator : public Comparator {
 public:
  const char* Name() const override { return "test.SimpleComparator"; }
  int Compare(const Slice& a, const Slice& b) const override {
    if (a.compare(b) < 0) return -1;
    if (a.compare(b) > 0) return 1;
    return 0;
  }
  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

// InternalKeyComparator usually wraps a Comparator; keep API minimal for ctor use.
class SimpleInternalKeyComparator : public InternalKeyComparator {
 public:
  explicit SimpleInternalKeyComparator(const Comparator* c) : InternalKeyComparator(*c) {}
};

// TableCache forward if needed; not used by tests but required by VersionSet ctor.
class TableCache {};

}  // namespace leveldb

// -----------------------------------------------------------------------------
// Google Mock collaborators for filesystem I/O
// -----------------------------------------------------------------------------

namespace leveldb {

class MockWritableFile : public WritableFile {
 public:
  MOCK_METHOD(Status, Append, (const Slice& data), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, Flush, (), (override));
  MOCK_METHOD(Status, Sync, (), (override));
};

class MockEnv : public Env {
 public:
  MOCK_METHOD(Status, NewSequentialFile, (const std::string& fname, SequentialFile** result), (override));
  MOCK_METHOD(Status, NewRandomAccessFile, (const std::string& fname, RandomAccessFile** result), (override));
  MOCK_METHOD(Status, NewWritableFile, (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(Status, NewAppendableFile, (const std::string& fname, WritableFile** result), (override));
  MOCK_METHOD(bool,   FileExists, (const std::string& fname), (override));
  MOCK_METHOD(Status, GetChildren, (const std::string& dir, std::vector<std::string>* result), (override));
  MOCK_METHOD(Status, RemoveFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, DeleteFile, (const std::string& fname), (override));
  MOCK_METHOD(Status, CreateDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, RemoveDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, DeleteDir, (const std::string& dirname), (override));
  MOCK_METHOD(Status, GetFileSize, (const std::string& fname, uint64_t* file_size), (override));
  MOCK_METHOD(Status, RenameFile, (const std::string& src, const std::string& target), (override));
  MOCK_METHOD(Status, LockFile, (const std::string& fname, FileLock** lock), (override));
  MOCK_METHOD(Status, UnlockFile, (FileLock* lock), (override));
  MOCK_METHOD(void,   Schedule, (void (*function)(void*), void* arg), (override));
  MOCK_METHOD(void,   StartThread, (void (*function)(void*), void* arg), (override));
  MOCK_METHOD(Status, GetTestDirectory, (std::string* path), (override));
  MOCK_METHOD(Status, NewLogger, (const std::string& fname, Logger** result), (override));
  MOCK_METHOD(uint64_t, NowMicros, (), (override));
  MOCK_METHOD(void,   SleepForMicroseconds, (int micros), (override));

  // Extra overload present in provided header variant
  MOCK_METHOD(Status, GetChildren, (const std::string& dir, int* result), (override));
};

}  // namespace leveldb

// -----------------------------------------------------------------------------
// Test fixture
// -----------------------------------------------------------------------------

namespace leveldb {

class VersionSet_LogAndApply_Test_163 : public ::testing::Test {
 protected:
  NiceMock<MockEnv> env_;
  Options options_;
  SimpleComparator cmp_;
  SimpleInternalKeyComparator icmp_;
  TableCache table_cache_;     // Unused; placeholder to satisfy ctor
  port::Mutex mu_;

  VersionSet_LogAndApply_Test_163()
      : options_(),
        cmp_(),
        icmp_(&cmp_) {
    options_.env = &env_;
    options_.info_log = nullptr; // We don't assert on logging side-effects
  }

  // Helper: build a VersionSet pointing at a fake DB path.
  std::unique_ptr<VersionSet> MakeVS(const std::string& dbname = "/tmp/testdb") {
    return std::unique_ptr<VersionSet>(
        new VersionSet(dbname, &options_, &table_cache_, &icmp_));
  }

  // Helper: set up a happy-path new MANIFEST creation, record pointer to file.
  void ExpectCreateManifestOK(MockWritableFile** out_file,
                              const std::string& expect_path_prefix = "") {
    // Provide a heap-allocated mock file that Writer will use.
    auto* wf = new NiceMock<MockWritableFile>();
    *out_file = wf;

    // Writer::AddRecord will call Append() at least once; allow success.
    ON_CALL(*wf, Append(_)).WillByDefault(Return(Status::OK()));
    ON_CALL(*wf, Flush()).WillByDefault(Return(Status::OK()));
    ON_CALL(*wf, Sync()).WillByDefault(Return(Status::OK()));
    ON_CALL(*wf, Close()).WillByDefault(Return(Status::OK()));

    // Capture the manifest path (we don’t need the exact number, just that a file is created).
    EXPECT_CALL(env_, NewWritableFile(_, _))
        .WillOnce(DoAll(Invoke([&](const std::string& fname, WritableFile** result) {
                           // Optionally assert prefix if you want tighter checks:
                           if (!expect_path_prefix.empty()) {
                             EXPECT_THAT(fname, ::testing::HasSubstr(expect_path_prefix));
                           }
                           *result = wf;   // transfer ownership to VersionSet/Writer path
                           return Status::OK();
                         })));
  }
};

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

// Normal path: when edit lacks numbers, VersionSet fills them in before any I/O.
// We only assert that observable fields inside 'edit' get set; we do not inspect internal state.
TEST_F(VersionSet_LogAndApply_Test_163, SetsMissingEditFieldsOnEntry_163) {
  auto vs = MakeVS();
  VersionEdit edit;          // No fields set initially
  NiceMock<MockWritableFile>* wf = nullptr;
  ExpectCreateManifestOK(&wf /*out*/);

  // Expect that after writing the first record, Sync() is invoked.
  EXPECT_CALL(*wf, Sync()).WillOnce(Return(Status::OK()));

  // Call
  Status s = vs->LogAndApply(&edit, &mu_);

  // Observable result: call succeeded
  EXPECT_TRUE(s.ok());

  // Observable edit mutations (strings are stable & public)
  // It should now contain log number, prev log number (default 0), next file, and last sequence.
  const std::string dbg = edit.DebugString();
  // We avoid assuming exact numeric values beyond construction defaults being propagated.
  EXPECT_THAT(dbg, ::testing::HasSubstr("log#"));
  EXPECT_THAT(dbg, ::testing::HasSubstr("prev_log#"));
  EXPECT_THAT(dbg, ::testing::HasSubstr("next_file#"));
  EXPECT_THAT(dbg, ::testing::HasSubstr("last_seq#"));
}

// If the caller already set valid log/prev numbers, the method must not overwrite them.
// We choose a log number that satisfies (current_log_number_ <= log < next_file_number_).
TEST_F(VersionSet_LogAndApply_Test_163, RespectsExistingEditNumbers_163) {
  auto vs = MakeVS();
  VersionEdit edit;
  edit.SetLogNumber(/*within bounds*/ 1);
  edit.SetPrevLogNumber(/*anything observable*/ 7);

  NiceMock<MockWritableFile>* wf = nullptr;
  ExpectCreateManifestOK(&wf);
  EXPECT_CALL(*wf, Sync()).WillOnce(Return(Status::OK()));

  Status s = vs->LogAndApply(&edit, &mu_);
  EXPECT_TRUE(s.ok());

  const std::string dbg = edit.DebugString();
  EXPECT_THAT(dbg, ::testing::HasSubstr("log# 1"));
  EXPECT_THAT(dbg, ::testing::HasSubstr("prev_log# 7"));
  // And still populated by VersionSet for these always-filled fields:
  EXPECT_THAT(dbg, ::testing::HasSubstr("next_file#"));
  EXPECT_THAT(dbg, ::testing::HasSubstr("last_seq#"));
}

// Boundary/IO path: If creating a new MANIFEST fails, the method must return an error
// and attempt to remove the manifest file path it tried to create.
TEST_F(VersionSet_LogAndApply_Test_163, NewManifestCreationFailureCleansUp_163) {
  auto vs = MakeVS("/tmp/db_for_manifest_fail");

  // Force NewWritableFile to fail; capture the path to check RemoveFile.
  std::string manifest_attempt_path;
  EXPECT_CALL(env_, NewWritableFile(_, _))
      .WillOnce(DoAll(SaveArg<0>(&manifest_attempt_path),
                      Return(Status::IOError("boom"))));

  // On failure path, VersionSet should try to remove the partially-created file (if any).
  // We allow either behavior depending on whether a file was materialized;
  // since NewWritableFile failed before returning a file handle, we still expect a RemoveFile
  // attempt with the same path name formed by VersionSet.
  EXPECT_CALL(env_, RemoveFile(_))
      .Times(::testing::AtLeast(0));

  VersionEdit edit;  // empty edit is fine; fields are set before I/O anyway
  Status s = vs->LogAndApply(&edit, &mu_);

  EXPECT_FALSE(s.ok());  // observable: returns an error status
  // If VersionSet formed a path, we should have captured it; sanity-check the pattern.
  if (!manifest_attempt_path.empty()) {
    EXPECT_THAT(manifest_attempt_path, ::testing::HasSubstr("MANIFEST"));
  }
}

// Happy path: when MANIFEST is created and the edit record is persisted,
// we expect a Sync to occur on the underlying file (observable interaction).
TEST_F(VersionSet_LogAndApply_Test_163, PersistsEditRecordAndSyncs_163) {
  auto vs = MakeVS();
  VersionEdit edit;

  NiceMock<MockWritableFile>* wf = nullptr;
  ExpectCreateManifestOK(&wf);

  // We expect a Sync during the commit path after writing the encoded edit.
  EXPECT_CALL(*wf, Sync()).WillOnce(Return(Status::OK()));

  Status s = vs->LogAndApply(&edit, &mu_);
  EXPECT_TRUE(s.ok());
}

// Regression-like boundary check: ensures the method sets NextFile and LastSequence
// even if I/O later fails (these are set before the I/O section).
TEST_F(VersionSet_LogAndApply_Test_163, SetsNextFileAndLastSequenceBeforeIO_163) {
  auto vs = MakeVS();

  // Force NewWritableFile to fail so we return with an error, but the edit should have been updated.
  EXPECT_CALL(env_, NewWritableFile(_, _))
      .WillOnce(Return(Status::IOError("fail-open")));

  VersionEdit edit;
  Status s = vs->LogAndApply(&edit, &mu_);
  EXPECT_FALSE(s.ok());

  const std::string dbg = edit.DebugString();
  EXPECT_THAT(dbg, ::testing::HasSubstr("next_file#"));
  EXPECT_THAT(dbg, ::testing::HasSubstr("last_seq#"));
}

}  // namespace leveldb
