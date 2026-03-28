#include "gtest/gtest.h"
#include "leveldb/env.h"
#include "leveldb/status.h"

#include <string>
#include <vector>
#include <cstdint>

namespace leveldb {

// Test fixture using the default Env implementation
class EnvTest_466 : public ::testing::Test {
 protected:
  Env* env_;
  std::string test_dir_;

  void SetUp() override {
    env_ = Env::Default();
    ASSERT_TRUE(env_ != nullptr);
    Status s = env_->GetTestDirectory(&test_dir_);
    ASSERT_TRUE(s.ok()) << s.ToString();
  }

  std::string TestFileName(const std::string& name) {
    return test_dir_ + "/" + name;
  }

  // Helper to create a file with some content
  Status WriteStringToFile(const std::string& fname, const std::string& data) {
    WritableFile* file;
    Status s = env_->NewWritableFile(fname, &file);
    if (!s.ok()) return s;
    s = file->Append(data);
    if (s.ok()) {
      s = file->Close();
    }
    delete file;
    return s;
  }
};

// Test that Default() returns a non-null Env
TEST_F(EnvTest_466, DefaultEnvIsNotNull_466) {
  ASSERT_TRUE(Env::Default() != nullptr);
}

// Test that Default() returns the same instance on multiple calls
TEST_F(EnvTest_466, DefaultEnvIsSingleton_466) {
  Env* env1 = Env::Default();
  Env* env2 = Env::Default();
  ASSERT_EQ(env1, env2);
}

// Test GetTestDirectory returns ok status and non-empty path
TEST_F(EnvTest_466, GetTestDirectoryReturnsValidPath_466) {
  std::string path;
  Status s = env_->GetTestDirectory(&path);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_FALSE(path.empty());
}

// Test creating and writing a new file
TEST_F(EnvTest_466, NewWritableFileCreatesFile_466) {
  std::string fname = TestFileName("writable_test_466");
  WritableFile* file;
  Status s = env_->NewWritableFile(fname, &file);
  ASSERT_TRUE(s.ok()) << s.ToString();
  s = file->Append("hello");
  ASSERT_TRUE(s.ok()) << s.ToString();
  s = file->Close();
  ASSERT_TRUE(s.ok()) << s.ToString();
  delete file;

  ASSERT_TRUE(env_->FileExists(fname));

  // Cleanup
  env_->RemoveFile(fname);
}

// Test FileExists returns false for non-existent file
TEST_F(EnvTest_466, FileExistsReturnsFalseForNonExistent_466) {
  std::string fname = TestFileName("nonexistent_file_466");
  ASSERT_FALSE(env_->FileExists(fname));
}

// Test FileExists returns true for existing file
TEST_F(EnvTest_466, FileExistsReturnsTrueForExistingFile_466) {
  std::string fname = TestFileName("exists_test_466");
  Status s = WriteStringToFile(fname, "data");
  ASSERT_TRUE(s.ok()) << s.ToString();

  ASSERT_TRUE(env_->FileExists(fname));

  // Cleanup
  env_->RemoveFile(fname);
}

// Test DeleteFile delegates to RemoveFile - file should be removed
TEST_F(EnvTest_466, DeleteFileRemovesFile_466) {
  std::string fname = TestFileName("delete_test_466");
  Status s = WriteStringToFile(fname, "data");
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_TRUE(env_->FileExists(fname));

  s = env_->DeleteFile(fname);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_FALSE(env_->FileExists(fname));
}

// Test RemoveFile removes an existing file
TEST_F(EnvTest_466, RemoveFileRemovesFile_466) {
  std::string fname = TestFileName("remove_test_466");
  Status s = WriteStringToFile(fname, "data");
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_TRUE(env_->FileExists(fname));

  s = env_->RemoveFile(fname);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_FALSE(env_->FileExists(fname));
}

// Test DeleteFile and RemoveFile behave the same way
TEST_F(EnvTest_466, DeleteFileAndRemoveFileAreEquivalent_466) {
  std::string fname1 = TestFileName("equiv_delete_466");
  std::string fname2 = TestFileName("equiv_remove_466");

  ASSERT_TRUE(WriteStringToFile(fname1, "data1").ok());
  ASSERT_TRUE(WriteStringToFile(fname2, "data2").ok());

  Status s1 = env_->DeleteFile(fname1);
  Status s2 = env_->RemoveFile(fname2);

  ASSERT_TRUE(s1.ok()) << s1.ToString();
  ASSERT_TRUE(s2.ok()) << s2.ToString();

  ASSERT_FALSE(env_->FileExists(fname1));
  ASSERT_FALSE(env_->FileExists(fname2));
}

// Test RemoveFile on non-existent file returns error
TEST_F(EnvTest_466, RemoveFileNonExistentReturnsError_466) {
  std::string fname = TestFileName("no_such_file_remove_466");
  Status s = env_->RemoveFile(fname);
  ASSERT_FALSE(s.ok());
}

// Test DeleteFile on non-existent file returns error
TEST_F(EnvTest_466, DeleteFileNonExistentReturnsError_466) {
  std::string fname = TestFileName("no_such_file_delete_466");
  Status s = env_->DeleteFile(fname);
  ASSERT_FALSE(s.ok());
}

// Test GetFileSize returns correct size
TEST_F(EnvTest_466, GetFileSizeReturnsCorrectSize_466) {
  std::string fname = TestFileName("filesize_test_466");
  std::string content = "hello world";
  ASSERT_TRUE(WriteStringToFile(fname, content).ok());

  uint64_t size;
  Status s = env_->GetFileSize(fname, &size);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_EQ(size, content.size());

  // Cleanup
  env_->RemoveFile(fname);
}

// Test GetFileSize for non-existent file
TEST_F(EnvTest_466, GetFileSizeNonExistentReturnsError_466) {
  std::string fname = TestFileName("no_such_filesize_466");
  uint64_t size;
  Status s = env_->GetFileSize(fname, &size);
  ASSERT_FALSE(s.ok());
}

// Test CreateDir and RemoveDir
TEST_F(EnvTest_466, CreateAndRemoveDir_466) {
  std::string dirname = TestFileName("testdir_466");
  Status s = env_->CreateDir(dirname);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_TRUE(env_->FileExists(dirname));

  s = env_->RemoveDir(dirname);
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test DeleteDir (alias for RemoveDir)
TEST_F(EnvTest_466, DeleteDirRemovesDirectory_466) {
  std::string dirname = TestFileName("testdir_deletedir_466");
  Status s = env_->CreateDir(dirname);
  ASSERT_TRUE(s.ok()) << s.ToString();

  s = env_->DeleteDir(dirname);
  ASSERT_TRUE(s.ok()) << s.ToString();
}

// Test GetChildren lists files in directory
TEST_F(EnvTest_466, GetChildrenListsFiles_466) {
  std::string subdir = TestFileName("children_test_466");
  ASSERT_TRUE(env_->CreateDir(subdir).ok());

  std::string f1 = subdir + "/file1";
  std::string f2 = subdir + "/file2";
  ASSERT_TRUE(WriteStringToFile(f1, "a").ok());
  ASSERT_TRUE(WriteStringToFile(f2, "b").ok());

  std::vector<std::string> children;
  Status s = env_->GetChildren(subdir, &children);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Should contain at least file1 and file2
  bool found1 = false, found2 = false;
  for (const auto& c : children) {
    if (c == "file1") found1 = true;
    if (c == "file2") found2 = true;
  }
  ASSERT_TRUE(found1);
  ASSERT_TRUE(found2);

  // Cleanup
  env_->RemoveFile(f1);
  env_->RemoveFile(f2);
  env_->RemoveDir(subdir);
}

// Test NewSequentialFile reads data correctly
TEST_F(EnvTest_466, NewSequentialFileReadsData_466) {
  std::string fname = TestFileName("seq_read_466");
  std::string content = "sequential read test";
  ASSERT_TRUE(WriteStringToFile(fname, content).ok());

  SequentialFile* file;
  Status s = env_->NewSequentialFile(fname, &file);
  ASSERT_TRUE(s.ok()) << s.ToString();

  char buf[100];
  Slice result;
  s = file->Read(content.size(), &result, buf);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_EQ(result.ToString(), content);

  delete file;
  env_->RemoveFile(fname);
}

// Test NewSequentialFile on non-existent file
TEST_F(EnvTest_466, NewSequentialFileNonExistentReturnsError_466) {
  std::string fname = TestFileName("no_seq_file_466");
  SequentialFile* file;
  Status s = env_->NewSequentialFile(fname, &file);
  ASSERT_FALSE(s.ok());
}

// Test NewRandomAccessFile reads data correctly
TEST_F(EnvTest_466, NewRandomAccessFileReadsData_466) {
  std::string fname = TestFileName("rand_read_466");
  std::string content = "random access test data";
  ASSERT_TRUE(WriteStringToFile(fname, content).ok());

  RandomAccessFile* file;
  Status s = env_->NewRandomAccessFile(fname, &file);
  ASSERT_TRUE(s.ok()) << s.ToString();

  char buf[100];
  Slice result;
  s = file->Read(0, content.size(), &result, buf);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_EQ(result.ToString(), content);

  // Read a portion from offset
  s = file->Read(7, 6, &result, buf);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_EQ(result.ToString(), "access");

  delete file;
  env_->RemoveFile(fname);
}

// Test NewRandomAccessFile on non-existent file
TEST_F(EnvTest_466, NewRandomAccessFileNonExistentReturnsError_466) {
  std::string fname = TestFileName("no_rand_file_466");
  RandomAccessFile* file;
  Status s = env_->NewRandomAccessFile(fname, &file);
  ASSERT_FALSE(s.ok());
}

// Test RenameFile
TEST_F(EnvTest_466, RenameFileWorks_466) {
  std::string src = TestFileName("rename_src_466");
  std::string target = TestFileName("rename_target_466");
  std::string content = "rename test";
  ASSERT_TRUE(WriteStringToFile(src, content).ok());

  Status s = env_->RenameFile(src, target);
  ASSERT_TRUE(s.ok()) << s.ToString();

  ASSERT_FALSE(env_->FileExists(src));
  ASSERT_TRUE(env_->FileExists(target));

  uint64_t size;
  ASSERT_TRUE(env_->GetFileSize(target, &size).ok());
  ASSERT_EQ(size, content.size());

  // Cleanup
  env_->RemoveFile(target);
}

// Test NewAppendableFile appends to existing file
TEST_F(EnvTest_466, NewAppendableFileAppendsData_466) {
  std::string fname = TestFileName("appendable_466");
  ASSERT_TRUE(WriteStringToFile(fname, "hello").ok());

  WritableFile* file;
  Status s = env_->NewAppendableFile(fname, &file);
  ASSERT_TRUE(s.ok()) << s.ToString();
  s = file->Append(" world");
  ASSERT_TRUE(s.ok()) << s.ToString();
  s = file->Close();
  ASSERT_TRUE(s.ok()) << s.ToString();
  delete file;

  uint64_t size;
  ASSERT_TRUE(env_->GetFileSize(fname, &size).ok());
  ASSERT_EQ(size, 11u);  // "hello world"

  // Cleanup
  env_->RemoveFile(fname);
}

// Test NowMicros returns reasonable values
TEST_F(EnvTest_466, NowMicrosReturnsIncreasingValues_466) {
  uint64_t t1 = env_->NowMicros();
  env_->SleepForMicroseconds(1000);  // Sleep 1ms
  uint64_t t2 = env_->NowMicros();
  ASSERT_GE(t2, t1);
}

// Test LockFile and UnlockFile
TEST_F(EnvTest_466, LockAndUnlockFile_466) {
  std::string fname = TestFileName("lock_test_466");
  FileLock* lock = nullptr;
  Status s = env_->LockFile(fname, &lock);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_TRUE(lock != nullptr);

  s = env_->UnlockFile(lock);
  ASSERT_TRUE(s.ok()) << s.ToString();

  // Cleanup
  env_->RemoveFile(fname);
}

// Test NewLogger
TEST_F(EnvTest_466, NewLoggerCreatesLogger_466) {
  std::string fname = TestFileName("logger_test_466");
  Logger* logger = nullptr;
  Status s = env_->NewLogger(fname, &logger);
  ASSERT_TRUE(s.ok()) << s.ToString();
  ASSERT_TRUE(logger != nullptr);
  delete logger;

  // Cleanup
  env_->RemoveFile(fname);
}

// Test writing empty file
TEST_F(EnvTest_466, WriteEmptyFile_466) {
  std::string fname = TestFileName("empty_file_466");
  ASSERT_TRUE(WriteStringToFile(fname, "").ok());

  uint64_t size;
  ASSERT_TRUE(env_->GetFileSize(fname, &size).ok());
  ASSERT_EQ(size, 0u);

  ASSERT_TRUE(env_->FileExists(fname));

  // Cleanup
  env_->RemoveFile(fname);
}

// Test GetChildren on empty directory
TEST_F(EnvTest_466, GetChildrenOnEmptyDir_466) {
  std::string dirname = TestFileName("empty_dir_466");
  ASSERT_TRUE(env_->CreateDir(dirname).ok());

  std::vector<std::string> children;
  Status s = env_->GetChildren(dirname, &children);
  ASSERT_TRUE(s.ok()) << s.ToString();
  // May contain "." and ".." on some systems, but no actual files
  for (const auto& c : children) {
    ASSERT_TRUE(c == "." || c == "..");
  }

  // Cleanup
  env_->RemoveDir(dirname);
}

// Test RemoveDir on non-existent directory returns error
TEST_F(EnvTest_466, RemoveDirNonExistentReturnsError_466) {
  std::string dirname = TestFileName("no_such_dir_466");
  Status s = env_->RemoveDir(dirname);
  ASSERT_FALSE(s.ok());
}

// Test DeleteDir on non-existent directory returns error
TEST_F(EnvTest_466, DeleteDirNonExistentReturnsError_466) {
  std::string dirname = TestFileName("no_such_deletedir_466");
  Status s = env_->DeleteDir(dirname);
  ASSERT_FALSE(s.ok());
}

// Test that NewWritableFile overwrites existing content
TEST_F(EnvTest_466, NewWritableFileOverwritesExisting_466) {
  std::string fname = TestFileName("overwrite_466");
  ASSERT_TRUE(WriteStringToFile(fname, "long initial content here").ok());
  ASSERT_TRUE(WriteStringToFile(fname, "short").ok());

  uint64_t size;
  ASSERT_TRUE(env_->GetFileSize(fname, &size).ok());
  ASSERT_EQ(size, 5u);

  // Cleanup
  env_->RemoveFile(fname);
}

// Test Schedule runs a function
TEST_F(EnvTest_466, ScheduleRunsFunction_466) {
  struct State {
    int val;
    port::Mutex mu;
    port::CondVar cv;
    bool done;
    State() : val(0), cv(&mu), done(false) {}
  };

  // Use a simpler approach - just sleep and check
  static int schedule_result_466 = 0;
  auto callback = [](void* arg) {
    int* p = reinterpret_cast<int*>(arg);
    *p = 42;
  };

  schedule_result_466 = 0;
  env_->Schedule(callback, &schedule_result_466);
  // Give it time to run
  env_->SleepForMicroseconds(100000);  // 100ms
  ASSERT_EQ(schedule_result_466, 42);
}

}  // namespace leveldb
