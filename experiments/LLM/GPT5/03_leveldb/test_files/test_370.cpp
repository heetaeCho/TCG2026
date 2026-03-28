// File: memenv_newmemenv_test.cc

#include "gtest/gtest.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace leveldb {

// Forward-declare NewMemEnv as exposed by memenv.cc (SUT)
Env* NewMemEnv(Env* base_env);

namespace {

class MemEnvTest_370 : public ::testing::Test {
protected:
  void SetUp() override {
    base_ = Env::Default();           // collaborator; not under test
    mem_.reset(NewMemEnv(base_));     // SUT: in-memory Env
    ASSERT_NE(mem_.get(), nullptr);
  }

  void TearDown() override {
    // The Env returned by NewMemEnv is heap-allocated and owns any resources.
    // Ensure we delete it to avoid leaks.
    mem_.reset();
  }

  // Helper: create a fresh file with given contents using WritableFile/Close.
  void CreateFile(const std::string& fname, const std::string& contents) {
    WritableFile* wf = nullptr;
    ASSERT_TRUE(mem_->NewWritableFile(fname, &wf).ok());
    std::unique_ptr<WritableFile> file(wf);
    ASSERT_TRUE(file->Append(contents).ok());
    ASSERT_TRUE(file->Close().ok());
  }

  // Helper: read whole file via SequentialFile.
  std::string ReadAllSequential(const std::string& fname) {
    SequentialFile* sf = nullptr;
    EXPECT_TRUE(mem_->NewSequentialFile(fname, &sf).ok());
    std::unique_ptr<SequentialFile> file(sf);

    std::string result;
    static const size_t kChunk = 8192;
    std::string scratch;
    scratch.resize(kChunk);

    leveldb::Slice fragment;
    // Read until EOF (Read returns OK with size < requested or returns non-OK when EOF; depends on impl)
    for (;;) {
      Status s = file->Read(kChunk, &fragment, &scratch[0]);
      if (!s.ok()) break;
      if (fragment.size() == 0) break;
      result.append(fragment.data(), fragment.size());
      if (fragment.size() < kChunk) break;
    }
    return result;
  }

  // Helper: read [offset, offset+n) via RandomAccessFile.
  std::string ReadRangeRandom(const std::string& fname, uint64_t offset, size_t n) {
    RandomAccessFile* rf = nullptr;
    EXPECT_TRUE(mem_->NewRandomAccessFile(fname, &rf).ok());
    std::unique_ptr<RandomAccessFile> file(rf);

    std::string scratch;
    scratch.resize(n);
    leveldb::Slice out;
    EXPECT_TRUE(file->Read(offset, n, &out, &scratch[0]).ok());
    return std::string(out.data(), out.size());
  }

  Env* base_ = nullptr;                    // not owned
  std::unique_ptr<Env> mem_;               // SUT
};

// --- Tests ---

TEST_F(MemEnvTest_370, ConstructsAndIsDistinctFromBase_370) {
  // NewMemEnv must return a usable Env distinct from base.
  ASSERT_NE(mem_.get(), nullptr);
  EXPECT_NE(mem_.get(), base_);
}

TEST_F(MemEnvTest_370, BasicCreateWriteReadSequential_370) {
  const std::string fname = "memenv_basic_seq.txt";
  const std::string payload = "hello, memenv\n";
  ASSERT_FALSE(mem_->FileExists(fname));

  CreateFile(fname, payload);

  // Visible in mem env
  EXPECT_TRUE(mem_->FileExists(fname));
  // Read back via SequentialFile
  EXPECT_EQ(ReadAllSequential(fname), payload);
}

TEST_F(MemEnvTest_370, RandomAccessReadRanges_370) {
  const std::string fname = "memenv_random.txt";
  const std::string payload = "abcdefghijklmnopqrstuvwxyz";
  CreateFile(fname, payload);

  // Middle slice
  EXPECT_EQ(ReadRangeRandom(fname, 5, 5), std::string("fghij"));
  // From 0
  EXPECT_EQ(ReadRangeRandom(fname, 0, 3), std::string("abc"));
  // Tail (n may be larger than remaining; we only check returned size)
  EXPECT_EQ(ReadRangeRandom(fname, 23, 10), std::string("xyz"));
}

TEST_F(MemEnvTest_370, AppendableFileAppendsData_370) {
  const std::string fname = "memenv_append.txt";
  WritableFile* wf = nullptr;
  ASSERT_TRUE(mem_->NewAppendableFile(fname, &wf).ok());
  std::unique_ptr<WritableFile> file(wf);

  ASSERT_TRUE(file->Append("first\n").ok());
  ASSERT_TRUE(file->Append("second\n").ok());
  ASSERT_TRUE(file->Close().ok());

  EXPECT_EQ(ReadAllSequential(fname), std::string("first\nsecond\n"));
}

TEST_F(MemEnvTest_370, RenameAndFileExistsBehavior_370) {
  const std::string src = "memenv_src.txt";
  const std::string dst = "memenv_dst.txt";
  CreateFile(src, "data");

  ASSERT_TRUE(mem_->FileExists(src));
  ASSERT_FALSE(mem_->FileExists(dst));

  ASSERT_TRUE(mem_->RenameFile(src, dst).ok());
  EXPECT_FALSE(mem_->FileExists(src));
  EXPECT_TRUE(mem_->FileExists(dst));
  EXPECT_EQ(ReadAllSequential(dst), "data");
}

TEST_F(MemEnvTest_370, DeleteRemovesFile_370) {
  const std::string fname = "memenv_delete.txt";
  CreateFile(fname, "x");
  ASSERT_TRUE(mem_->FileExists(fname));

  // Either RemoveFile or DeleteFile should remove. Test both if exposed.
  Status s_remove = mem_->RemoveFile(fname);
  if (s_remove.ok()) {
    EXPECT_FALSE(mem_->FileExists(fname));
  } else {
    // Some Env variants use DeleteFile; try it if RemoveFile is not supported.
    ASSERT_TRUE(mem_->DeleteFile(fname).ok());
    EXPECT_FALSE(mem_->FileExists(fname));
  }
}

TEST_F(MemEnvTest_370, GetFileSizeReflectsContentLength_370) {
  const std::string fname = "memenv_size.txt";
  const std::string body = "1234567890"; // 10 bytes
  CreateFile(fname, body);

  uint64_t sz = 0;
  ASSERT_TRUE(mem_->GetFileSize(fname, &sz).ok());
  EXPECT_EQ(sz, static_cast<uint64_t>(body.size()));
}

TEST_F(MemEnvTest_370, CreateDirAndListChildren_370) {
  const std::string dir = "memenv_dir";
  ASSERT_TRUE(mem_->CreateDir(dir).ok());

  CreateFile(dir + "/a.txt", "A");
  CreateFile(dir + "/b.log", "BB");

  std::vector<std::string> children;
  ASSERT_TRUE(mem_->GetChildren(dir, &children).ok());

  // Children should contain the entries created inside the directory.
  // We only check presence; do not assume order or additional entries.
  auto has = [&](const char* name) {
    return std::find(children.begin(), children.end(), std::string(name)) != children.end();
  };
  EXPECT_TRUE(has("a.txt"));
  EXPECT_TRUE(has("b.log"));
}

TEST_F(MemEnvTest_370, LocksCanBeAcquiredAndReleased_370) {
  const std::string fname = "memenv_lock.txt";
  CreateFile(fname, "lock_me");

  FileLock* lk = nullptr;
  ASSERT_TRUE(mem_->LockFile(fname, &lk).ok());
  ASSERT_NE(lk, nullptr);
  EXPECT_TRUE(mem_->UnlockFile(lk).ok());
}

TEST_F(MemEnvTest_370, IsolationFromBaseEnv_370) {
  // Creating a file in mem env should not require it to exist in the base env.
  // Observable check: base_->FileExists should normally be false for our test name.
  const std::string fname = "memenv_isolated.txt";
  CreateFile(fname, "isolation");

  EXPECT_TRUE(mem_->FileExists(fname));
  // The base env shouldn't suddenly see an on-disk file with the same name as a side effect.
  EXPECT_FALSE(base_->FileExists(fname));
}

}  // namespace
}  // namespace leveldb
