// File: version_set_recover_test_164.cc
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "db/version_set.h"
#include "db/dbformat.h"
#include "leveldb/options.h"
#include "leveldb/status.h"
#include "leveldb/env.h"

// -------------------- Minimal test doubles (black-box friendly) --------------------

namespace {

using ::leveldb::Env;
using ::leveldb::SequentialFile;
using ::leveldb::Status;
using ::leveldb::Slice;
using ::testing::_;
using ::testing::HasSubstr;

// A minimal in-memory SequentialFile that returns preloaded content.
class MemSequentialFile : public SequentialFile {
 public:
  explicit MemSequentialFile(std::string data) : data_(std::move(data)), pos_(0) {}

  // leveldb::SequentialFile API in upstream LevelDB:
  // virtual Status Read(size_t n, Slice* result, char* scratch) = 0;
  Status Read(size_t n, Slice* result, char* scratch) override {
    const size_t avail = (pos_ < data_.size()) ? (data_.size() - pos_) : 0;
    const size_t to_read = std::min(n, avail);
    if (to_read > 0) {
      std::memcpy(scratch, data_.data() + pos_, to_read);
      *result = Slice(scratch, to_read);
      pos_ += to_read;
    } else {
      *result = Slice();
    }
    return Status::OK();
  }

  Status Skip(uint64_t n) override {
    uint64_t new_pos = pos_ + n;
    if (new_pos > data_.size()) new_pos = data_.size();
    pos_ = static_cast<size_t>(new_pos);
    return Status::OK();
  }

 private:
  std::string data_;
  size_t pos_;
};

// A minimal fake Env that lets us register files and statuses.
class FakeEnv : public Env {
 public:
  FakeEnv() = default;

  struct Entry {
    bool exists = false;
    Status open_status = Status::OK();
    std::string data;  // file content for SequentialFile
  };

  // Register a file that should open OK and provide given content.
  void AddReadableFile(const std::string& fname, const std::string& content) {
    auto& e = files_[fname];
    e.exists = true;
    e.open_status = Status::OK();
    e.data = content;
  }

  // Register a file open result (e.g., NotFound).
  void AddOpenStatus(const std::string& fname, const Status& st) {
    auto& e = files_[fname];
    e.exists = false;   // for our purposes; open returns st anyway
    e.open_status = st;
    e.data.clear();
  }

  Status NewSequentialFile(const std::string& fname, SequentialFile** result) override {
    auto it = files_.find(fname);
    if (it == files_.end()) {
      // Treat unknown file as NotFound (consistent with LevelDB behavior)
      *result = nullptr;
      return Status::NotFound(fname);
    }
    const Entry& e = it->second;
    if (!e.open_status.ok()) {
      *result = nullptr;
      return e.open_status;
    }
    *result = new MemSequentialFile(e.data);
    return Status::OK();
  }

  // Unused overrides for this test — keep default no-op / OK behavior.
  Status NewRandomAccessFile(const std::string&, leveldb::RandomAccessFile**) override {
    return Status::OK();
  }
  Status NewWritableFile(const std::string&, leveldb::WritableFile**) override {
    return Status::OK();
  }
  Status NewAppendableFile(const std::string&, leveldb::WritableFile**) override {
    return Status::OK();
  }
  bool FileExists(const std::string&) override { return true; }
  Status GetChildren(const std::string&, std::vector<std::string>*) override { return Status::OK(); }
  Status RemoveFile(const std::string&) override { return Status::OK(); }
  Status DeleteFile(const std::string&) override { return Status::OK(); }
  Status CreateDir(const std::string&) override { return Status::OK(); }
  Status RemoveDir(const std::string&) override { return Status::OK(); }
  Status DeleteDir(const std::string&) override { return Status::OK(); }
  Status GetFileSize(const std::string&, uint64_t*) override { return Status::OK(); }
  Status RenameFile(const std::string&, const std::string&) override { return Status::OK(); }
  Status LockFile(const std::string&, leveldb::FileLock**) override { return Status::OK(); }
  Status UnlockFile(leveldb::FileLock*) override { return Status::OK(); }
  void Schedule(void (*)(void*), void*) override {}
  void StartThread(void (*)(void*), void*) override {}
  Status GetTestDirectory(std::string* path) override { path->assign("/tmp"); return Status::OK(); }
  Status NewLogger(const std::string&, leveldb::Logger**) override { return Status::OK(); }
  uint64_t NowMicros() override { return 0; }
  void SleepForMicroseconds(int) override {}

 private:
  std::unordered_map<std::string, Entry> files_;
};

// Very small Comparator stub (only Name() is observed in Recover via icmp_.user_comparator()->Name()).
class StubComparator : public leveldb::Comparator {
 public:
  const char* Name() const override { return "test.Stub"; }
  int Compare(const Slice&, const Slice&) const override { return 0; }
  void FindShortestSeparator(std::string*, const Slice&) const override {}
  void FindShortSuccessor(std::string*) const override {}
};

struct VersionSetRecoverTest : public ::testing::Test {
  FakeEnv env;
  StubComparator user_cmp;
  leveldb::InternalKeyComparator ikc{&user_cmp};
  leveldb::Options opts;
  leveldb::TableCache* table_cache = nullptr;  // not used by Recover
  std::string dbname = "/db";

  void SetUp() override {
    opts.env = &env;
    opts.comparator = &user_cmp;
  }

  // Helpers to shape the filesystem view for Recover()
  std::string CurrentFilePath() const { return dbname + "/CURRENT"; }
  std::string ManifestFilePath(const std::string& base) const { return dbname + "/" + base; }

  // Write CURRENT pointing to |manifest_base| (e.g., "MANIFEST-000001"), with or without trailing newline.
  void WriteCurrent(const std::string& manifest_base, bool with_newline) {
    std::string content = manifest_base;
    if (with_newline) content.push_back('\n');
    env.AddReadableFile(CurrentFilePath(), content);
  }
};

} // namespace

// -------------------- Tests (TEST_ID = 164) --------------------

// 1) If CURRENT cannot be read (e.g., NotFound/IOError), Recover should return that error.
TEST_F(VersionSetRecoverTest, Recover_ReturnsErrorWhenCurrentUnreadable_164) {
  // Arrange: CURRENT open fails.
  env.AddOpenStatus(CurrentFilePath(), Status::IOError("boom"));

  leveldb::VersionSet vs(dbname, &opts, table_cache, &ikc);
  bool save_manifest = false;

  // Act
  Status s = vs.Recover(&save_manifest);

  // Assert
  EXPECT_TRUE(s.IsIOError());
  // No further observable state changes guaranteed/required by interface.
}

// 2) If CURRENT exists but does NOT end with '\n', Recover returns Corruption with the documented message.
TEST_F(VersionSetRecoverTest, Recover_CorruptionWhenCurrentMissingTrailingNewline_164) {
  // Arrange: CURRENT has no newline.
  WriteCurrent("MANIFEST-000001", /*with_newline=*/false);

  leveldb::VersionSet vs(dbname, &opts, table_cache, &ikc);
  bool save_manifest = false;

  // Act
  Status s = vs.Recover(&save_manifest);

  // Assert
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_THAT(s.ToString(), HasSubstr("CURRENT file does not end with newline"));
}

// 3) If CURRENT points to an absent manifest, Recover returns Corruption with the documented message.
TEST_F(VersionSetRecoverTest, Recover_CorruptionWhenCurrentPointsToMissingManifest_164) {
  // Arrange: CURRENT -> MANIFEST-000007\n ; opening that manifest returns NotFound.
  const std::string manifest_base = "MANIFEST-000007";
  WriteCurrent(manifest_base, /*with_newline=*/true);
  env.AddOpenStatus(ManifestFilePath(manifest_base), Status::NotFound("nope"));

  leveldb::VersionSet vs(dbname, &opts, table_cache, &ikc);
  bool save_manifest = false;

  // Act
  Status s = vs.Recover(&save_manifest);

  // Assert
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_THAT(s.ToString(), HasSubstr("CURRENT points to a non-existent file"));
}

// 4) If CURRENT and manifest open fine but manifest has zero readable records,
// Recover should report the missing meta-nextfile entry (first required one).
TEST_F(VersionSetRecoverTest, Recover_CorruptionWhenDescriptorHasNoRecords_164) {
  // Arrange:
  // CURRENT -> MANIFEST-000001\n
  // MANIFEST-000001 is an empty file (Reader will find no records).
  const std::string manifest_base = "MANIFEST-000001";
  WriteCurrent(manifest_base, /*with_newline=*/true);
  env.AddReadableFile(ManifestFilePath(manifest_base), std::string() /*empty*/);

  leveldb::VersionSet vs(dbname, &opts, table_cache, &ikc);
  bool save_manifest = false;

  // Act
  Status s = vs.Recover(&save_manifest);

  // Assert
  EXPECT_TRUE(s.IsCorruption());
  EXPECT_THAT(s.ToString(), HasSubstr("no meta-nextfile entry in descriptor"));
  // Also ensure we didn't claim a new manifest is needed (since we failed).
  // (No interface guarantee on save_manifest in failure path, so we don't assert its value.)
}
