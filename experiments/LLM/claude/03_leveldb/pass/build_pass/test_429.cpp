#include "gtest/gtest.h"
#include "leveldb/env.h"
#include <string>
#include <vector>
#include <cstdint>
#include <thread>
#include <atomic>
#include <algorithm>

namespace leveldb {

class EnvPosixTest_429 : public ::testing::Test {
 protected:
  Env* env_;

  void SetUp() override {
    env_ = Env::Default();
    ASSERT_NE(env_, nullptr);
  }

  void TearDown() override {
    // Cleanup is handled per-test as needed
  }

  std::string TestDir() {
    std::string dir;
    EXPECT_TRUE(env_->GetTestDirectory(&dir).ok());
    return dir;
  }
};

// Test that Default() returns a non-null pointer
TEST_F(EnvPosixTest_429, DefaultReturnsNonNull_429) {
  Env* env = Env::Default();
  ASSERT_NE(env, nullptr);
}

// Test that Default() returns the same instance (singleton)
TEST_F(EnvPosixTest_429, DefaultReturnsSameInstance_429) {
  Env* env1 = Env::Default();
  Env* env2 = Env::Default();
  ASSERT_EQ(env1, env2);
}

// Test GetTestDirectory returns a valid path
TEST_F(EnvPosixTest_429, GetTestDirectoryReturnsOk_429) {
  std::string path;
  Status s = env_->GetTestDirectory(&path);
  ASSERT_TRUE(s.ok());
  ASSERT_FALSE(path.empty());
}

// Test creating and writing to a new writable file
TEST_F(EnvPosixTest_429, NewWritableFileAndWrite_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/env_posix_test_writable_429";

  WritableFile* writable_file = nullptr;
  Status s = env_->NewWritableFile(fname, &writable_file);
  ASSERT_TRUE(s.ok());
  ASSERT_NE(writable_file, nullptr);

  s = writable_file->Append("hello world");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  // Verify the file exists
  ASSERT_TRUE(env_->FileExists(fname));

  // Verify file size
  uint64_t file_size;
  s = env_->GetFileSize(fname, &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(file_size, 11u);

  // Cleanup
  env_->RemoveFile(fname);
}

// Test NewSequentialFile reads correctly
TEST_F(EnvPosixTest_429, NewSequentialFileReadsData_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/env_posix_test_seq_429";

  // Write data
  WritableFile* writable_file = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname, &writable_file).ok());
  ASSERT_TRUE(writable_file->Append("test data 429").ok());
  ASSERT_TRUE(writable_file->Close().ok());
  delete writable_file;

  // Read data sequentially
  SequentialFile* seq_file = nullptr;
  Status s = env_->NewSequentialFile(fname, &seq_file);
  ASSERT_TRUE(s.ok());
  ASSERT_NE(seq_file, nullptr);

  char buf[100];
  Slice result;
  s = seq_file->Read(13, &result, buf);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(result.ToString(), "test data 429");

  delete seq_file;
  env_->RemoveFile(fname);
}

// Test NewRandomAccessFile reads correctly
TEST_F(EnvPosixTest_429, NewRandomAccessFileReadsData_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/env_posix_test_rand_429";

  // Write data
  WritableFile* writable_file = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname, &writable_file).ok());
  ASSERT_TRUE(writable_file->Append("random access test").ok());
  ASSERT_TRUE(writable_file->Close().ok());
  delete writable_file;

  // Read data randomly
  RandomAccessFile* rand_file = nullptr;
  Status s = env_->NewRandomAccessFile(fname, &rand_file);
  ASSERT_TRUE(s.ok());
  ASSERT_NE(rand_file, nullptr);

  char buf[100];
  Slice result;
  s = rand_file->Read(7, 6, &result, buf);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(result.ToString(), "access");

  delete rand_file;
  env_->RemoveFile(fname);
}

// Test FileExists for non-existent file
TEST_F(EnvPosixTest_429, FileExistsReturnsFalseForNonExistent_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/nonexistent_file_429";
  ASSERT_FALSE(env_->FileExists(fname));
}

// Test FileExists for existing file
TEST_F(EnvPosixTest_429, FileExistsReturnsTrueForExistingFile_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/existing_file_429";

  WritableFile* writable_file = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname, &writable_file).ok());
  ASSERT_TRUE(writable_file->Close().ok());
  delete writable_file;

  ASSERT_TRUE(env_->FileExists(fname));

  env_->RemoveFile(fname);
}

// Test CreateDir and RemoveDir
TEST_F(EnvPosixTest_429, CreateAndRemoveDir_429) {
  std::string dir = TestDir();
  std::string new_dir = dir + "/test_dir_429";

  Status s = env_->CreateDir(new_dir);
  ASSERT_TRUE(s.ok());

  s = env_->RemoveDir(new_dir);
  ASSERT_TRUE(s.ok());
}

// Test GetChildren lists files
TEST_F(EnvPosixTest_429, GetChildrenListsFiles_429) {
  std::string dir = TestDir();
  std::string subdir = dir + "/children_test_429";
  env_->CreateDir(subdir);

  // Create files
  std::string fname1 = subdir + "/file1";
  std::string fname2 = subdir + "/file2";

  WritableFile* wf = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname1, &wf).ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  ASSERT_TRUE(env_->NewWritableFile(fname2, &wf).ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  std::vector<std::string> children;
  Status s = env_->GetChildren(subdir, &children);
  ASSERT_TRUE(s.ok());

  // Should contain at least the two files we created
  bool found1 = std::find(children.begin(), children.end(), "file1") != children.end();
  bool found2 = std::find(children.begin(), children.end(), "file2") != children.end();
  ASSERT_TRUE(found1);
  ASSERT_TRUE(found2);

  // Cleanup
  env_->RemoveFile(fname1);
  env_->RemoveFile(fname2);
  env_->RemoveDir(subdir);
}

// Test RemoveFile
TEST_F(EnvPosixTest_429, RemoveFileDeletesFile_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/remove_test_429";

  WritableFile* wf = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname, &wf).ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  ASSERT_TRUE(env_->FileExists(fname));

  Status s = env_->RemoveFile(fname);
  ASSERT_TRUE(s.ok());

  ASSERT_FALSE(env_->FileExists(fname));
}

// Test RenameFile
TEST_F(EnvPosixTest_429, RenameFileWorks_429) {
  std::string dir = TestDir();
  std::string src = dir + "/rename_src_429";
  std::string target = dir + "/rename_target_429";

  WritableFile* wf = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(src, &wf).ok());
  ASSERT_TRUE(wf->Append("rename test").ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  Status s = env_->RenameFile(src, target);
  ASSERT_TRUE(s.ok());

  ASSERT_FALSE(env_->FileExists(src));
  ASSERT_TRUE(env_->FileExists(target));

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(target, &file_size).ok());
  ASSERT_EQ(file_size, 11u);

  env_->RemoveFile(target);
}

// Test GetFileSize on empty file
TEST_F(EnvPosixTest_429, GetFileSizeEmptyFile_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/empty_file_429";

  WritableFile* wf = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname, &wf).ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  uint64_t file_size;
  Status s = env_->GetFileSize(fname, &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(file_size, 0u);

  env_->RemoveFile(fname);
}

// Test GetFileSize on non-existent file returns error
TEST_F(EnvPosixTest_429, GetFileSizeNonExistentFile_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/nonexistent_size_429";

  uint64_t file_size;
  Status s = env_->GetFileSize(fname, &file_size);
  ASSERT_FALSE(s.ok());
}

// Test LockFile and UnlockFile
TEST_F(EnvPosixTest_429, LockAndUnlockFile_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/lock_test_429";

  FileLock* lock = nullptr;
  Status s = env_->LockFile(fname, &lock);
  ASSERT_TRUE(s.ok());
  ASSERT_NE(lock, nullptr);

  s = env_->UnlockFile(lock);
  ASSERT_TRUE(s.ok());

  env_->RemoveFile(fname);
}

// Test NewAppendableFile
TEST_F(EnvPosixTest_429, NewAppendableFileAppends_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/appendable_429";

  // Write initial data
  WritableFile* wf = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname, &wf).ok());
  ASSERT_TRUE(wf->Append("hello").ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  // Append more data
  ASSERT_TRUE(env_->NewAppendableFile(fname, &wf).ok());
  ASSERT_TRUE(wf->Append(" world").ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  // Verify total content
  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname, &file_size).ok());
  ASSERT_EQ(file_size, 11u);

  // Read and verify
  SequentialFile* sf = nullptr;
  ASSERT_TRUE(env_->NewSequentialFile(fname, &sf).ok());
  char buf[100];
  Slice result;
  ASSERT_TRUE(sf->Read(11, &result, buf).ok());
  ASSERT_EQ(result.ToString(), "hello world");
  delete sf;

  env_->RemoveFile(fname);
}

// Test NowMicros returns increasing values
TEST_F(EnvPosixTest_429, NowMicrosIncreases_429) {
  uint64_t t1 = env_->NowMicros();
  env_->SleepForMicroseconds(1000);  // Sleep 1ms
  uint64_t t2 = env_->NowMicros();
  ASSERT_GT(t2, t1);
}

// Test SleepForMicroseconds actually sleeps
TEST_F(EnvPosixTest_429, SleepForMicrosecondsSleeps_429) {
  uint64_t start = env_->NowMicros();
  int sleep_micros = 10000;  // 10ms
  env_->SleepForMicroseconds(sleep_micros);
  uint64_t elapsed = env_->NowMicros() - start;
  // Allow some tolerance; at least half the requested time should have passed
  ASSERT_GE(elapsed, static_cast<uint64_t>(sleep_micros / 2));
}

// Test NewLogger creates a logger
TEST_F(EnvPosixTest_429, NewLoggerCreatesLogger_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/logger_test_429";

  Logger* logger = nullptr;
  Status s = env_->NewLogger(fname, &logger);
  ASSERT_TRUE(s.ok());
  ASSERT_NE(logger, nullptr);

  delete logger;
  env_->RemoveFile(fname);
}

// Test Schedule runs a function
TEST_F(EnvPosixTest_429, ScheduleRunsFunction_429) {
  std::atomic<int> counter(0);

  struct Arg {
    std::atomic<int>* counter;
  };

  Arg arg;
  arg.counter = &counter;

  env_->Schedule([](void* a) {
    Arg* arg = static_cast<Arg*>(a);
    arg->counter->fetch_add(1);
  }, &arg);

  // Wait for the scheduled function to complete
  env_->SleepForMicroseconds(100000);  // 100ms
  ASSERT_EQ(counter.load(), 1);
}

// Test StartThread runs a function in a new thread
TEST_F(EnvPosixTest_429, StartThreadRunsFunction_429) {
  std::atomic<int> counter(0);

  struct Arg {
    std::atomic<int>* counter;
  };

  Arg arg;
  arg.counter = &counter;

  env_->StartThread([](void* a) {
    Arg* arg = static_cast<Arg*>(a);
    arg->counter->fetch_add(1);
  }, &arg);

  // Wait for the thread to complete
  env_->SleepForMicroseconds(100000);  // 100ms
  ASSERT_EQ(counter.load(), 1);
}

// Test opening a non-existent file for sequential read fails
TEST_F(EnvPosixTest_429, NewSequentialFileNonExistent_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/nonexistent_seq_429";

  SequentialFile* sf = nullptr;
  Status s = env_->NewSequentialFile(fname, &sf);
  ASSERT_FALSE(s.ok());
}

// Test opening a non-existent file for random access fails
TEST_F(EnvPosixTest_429, NewRandomAccessFileNonExistent_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/nonexistent_rand_429";

  RandomAccessFile* rf = nullptr;
  Status s = env_->NewRandomAccessFile(fname, &rf);
  ASSERT_FALSE(s.ok());
}

// Test RemoveFile on non-existent file returns error
TEST_F(EnvPosixTest_429, RemoveFileNonExistent_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/nonexistent_remove_429";

  Status s = env_->RemoveFile(fname);
  ASSERT_FALSE(s.ok());
}

// Test RemoveDir on non-existent directory returns error
TEST_F(EnvPosixTest_429, RemoveDirNonExistent_429) {
  std::string dir = TestDir();
  std::string dirname = dir + "/nonexistent_dir_429";

  Status s = env_->RemoveDir(dirname);
  ASSERT_FALSE(s.ok());
}

// Test writing large data
TEST_F(EnvPosixTest_429, WriteLargeData_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/large_data_429";

  std::string large_data(1024 * 1024, 'x');  // 1MB of 'x'

  WritableFile* wf = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname, &wf).ok());
  ASSERT_TRUE(wf->Append(large_data).ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname, &file_size).ok());
  ASSERT_EQ(file_size, 1024u * 1024u);

  env_->RemoveFile(fname);
}

// Test multiple Schedule calls
TEST_F(EnvPosixTest_429, MultipleScheduleCalls_429) {
  std::atomic<int> counter(0);

  struct Arg {
    std::atomic<int>* counter;
  };

  Arg arg;
  arg.counter = &counter;

  auto fn = [](void* a) {
    Arg* arg = static_cast<Arg*>(a);
    arg->counter->fetch_add(1);
  };

  for (int i = 0; i < 5; i++) {
    env_->Schedule(fn, &arg);
  }

  // Wait for all scheduled functions to complete
  env_->SleepForMicroseconds(200000);  // 200ms
  ASSERT_EQ(counter.load(), 5);
}

// Test GetChildren on non-existent directory
TEST_F(EnvPosixTest_429, GetChildrenNonExistentDir_429) {
  std::string dir = TestDir();
  std::string dirname = dir + "/nonexistent_children_429";

  std::vector<std::string> children;
  Status s = env_->GetChildren(dirname, &children);
  ASSERT_FALSE(s.ok());
}

// Test double lock fails
TEST_F(EnvPosixTest_429, DoubleLockFails_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/double_lock_429";

  FileLock* lock1 = nullptr;
  Status s = env_->LockFile(fname, &lock1);
  ASSERT_TRUE(s.ok());

  FileLock* lock2 = nullptr;
  s = env_->LockFile(fname, &lock2);
  ASSERT_FALSE(s.ok());

  s = env_->UnlockFile(lock1);
  ASSERT_TRUE(s.ok());

  env_->RemoveFile(fname);
}

// Test Sync on writable file
TEST_F(EnvPosixTest_429, WritableFileSyncWorks_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/sync_test_429";

  WritableFile* wf = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname, &wf).ok());
  ASSERT_TRUE(wf->Append("sync data").ok());
  ASSERT_TRUE(wf->Sync().ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  uint64_t file_size;
  ASSERT_TRUE(env_->GetFileSize(fname, &file_size).ok());
  ASSERT_EQ(file_size, 9u);

  env_->RemoveFile(fname);
}

// Test SequentialFile Skip
TEST_F(EnvPosixTest_429, SequentialFileSkip_429) {
  std::string dir = TestDir();
  std::string fname = dir + "/skip_test_429";

  WritableFile* wf = nullptr;
  ASSERT_TRUE(env_->NewWritableFile(fname, &wf).ok());
  ASSERT_TRUE(wf->Append("abcdefghij").ok());
  ASSERT_TRUE(wf->Close().ok());
  delete wf;

  SequentialFile* sf = nullptr;
  ASSERT_TRUE(env_->NewSequentialFile(fname, &sf).ok());

  ASSERT_TRUE(sf->Skip(5).ok());

  char buf[10];
  Slice result;
  ASSERT_TRUE(sf->Read(5, &result, buf).ok());
  ASSERT_EQ(result.ToString(), "fghij");

  delete sf;
  env_->RemoveFile(fname);
}

}  // namespace leveldb
