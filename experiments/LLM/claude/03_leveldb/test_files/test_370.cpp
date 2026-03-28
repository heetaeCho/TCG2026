#include "gtest/gtest.h"
#include "leveldb/env.h"
#include "helpers/memenv/memenv.h"
#include <string>
#include <vector>
#include <algorithm>

namespace leveldb {

class MemEnvTest_370 : public ::testing::Test {
 protected:
  void SetUp() override {
    env_ = NewMemEnv(Env::Default());
  }

  void TearDown() override {
    delete env_;
  }

  Env* env_;
};

TEST_F(MemEnvTest_370, CreateAndExistsFile_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/test_file", &writable_file);
  ASSERT_TRUE(s.ok());
  delete writable_file;

  ASSERT_TRUE(env_->FileExists("/test_file"));
}

TEST_F(MemEnvTest_370, FileDoesNotExist_370) {
  ASSERT_FALSE(env_->FileExists("/nonexistent_file"));
}

TEST_F(MemEnvTest_370, WriteAndReadSequentialFile_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/test_seq", &writable_file);
  ASSERT_TRUE(s.ok());

  s = writable_file->Append("hello world");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  SequentialFile* seq_file;
  s = env_->NewSequentialFile("/test_seq", &seq_file);
  ASSERT_TRUE(s.ok());

  Slice result;
  char scratch[100];
  s = seq_file->Read(11, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("hello world", result.ToString());
  delete seq_file;
}

TEST_F(MemEnvTest_370, WriteAndReadRandomAccessFile_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/test_rand", &writable_file);
  ASSERT_TRUE(s.ok());

  s = writable_file->Append("hello world");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  RandomAccessFile* rand_file;
  s = env_->NewRandomAccessFile("/test_rand", &rand_file);
  ASSERT_TRUE(s.ok());

  Slice result;
  char scratch[100];
  s = rand_file->Read(6, 5, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("world", result.ToString());
  delete rand_file;
}

TEST_F(MemEnvTest_370, GetFileSize_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/test_size", &writable_file);
  ASSERT_TRUE(s.ok());

  s = writable_file->Append("12345");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  uint64_t file_size;
  s = env_->GetFileSize("/test_size", &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(5u, file_size);
}

TEST_F(MemEnvTest_370, GetFileSizeNonexistent_370) {
  uint64_t file_size;
  Status s = env_->GetFileSize("/nonexistent", &file_size);
  ASSERT_FALSE(s.ok());
}

TEST_F(MemEnvTest_370, RemoveFile_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/to_remove", &writable_file);
  ASSERT_TRUE(s.ok());
  delete writable_file;

  ASSERT_TRUE(env_->FileExists("/to_remove"));

  s = env_->RemoveFile("/to_remove");
  ASSERT_TRUE(s.ok());

  ASSERT_FALSE(env_->FileExists("/to_remove"));
}

TEST_F(MemEnvTest_370, RemoveNonexistentFile_370) {
  Status s = env_->RemoveFile("/nonexistent");
  ASSERT_FALSE(s.ok());
}

TEST_F(MemEnvTest_370, RenameFile_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/src_file", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("data");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  s = env_->RenameFile("/src_file", "/dst_file");
  ASSERT_TRUE(s.ok());

  ASSERT_FALSE(env_->FileExists("/src_file"));
  ASSERT_TRUE(env_->FileExists("/dst_file"));

  uint64_t file_size;
  s = env_->GetFileSize("/dst_file", &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(4u, file_size);
}

TEST_F(MemEnvTest_370, RenameNonexistentFile_370) {
  Status s = env_->RenameFile("/nonexistent", "/dst");
  ASSERT_FALSE(s.ok());
}

TEST_F(MemEnvTest_370, GetChildren_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/dir/file1", &writable_file);
  ASSERT_TRUE(s.ok());
  delete writable_file;

  s = env_->NewWritableFile("/dir/file2", &writable_file);
  ASSERT_TRUE(s.ok());
  delete writable_file;

  std::vector<std::string> children;
  s = env_->GetChildren("/dir", &children);
  ASSERT_TRUE(s.ok());

  std::sort(children.begin(), children.end());
  ASSERT_EQ(2u, children.size());
  ASSERT_EQ("file1", children[0]);
  ASSERT_EQ("file2", children[1]);
}

TEST_F(MemEnvTest_370, CreateDir_370) {
  Status s = env_->CreateDir("/mydir");
  ASSERT_TRUE(s.ok());
}

TEST_F(MemEnvTest_370, RemoveDir_370) {
  Status s = env_->CreateDir("/mydir2");
  ASSERT_TRUE(s.ok());
  s = env_->RemoveDir("/mydir2");
  ASSERT_TRUE(s.ok());
}

TEST_F(MemEnvTest_370, NewSequentialFileNonexistent_370) {
  SequentialFile* seq_file;
  Status s = env_->NewSequentialFile("/nonexistent", &seq_file);
  ASSERT_FALSE(s.ok());
}

TEST_F(MemEnvTest_370, NewRandomAccessFileNonexistent_370) {
  RandomAccessFile* rand_file;
  Status s = env_->NewRandomAccessFile("/nonexistent", &rand_file);
  ASSERT_FALSE(s.ok());
}

TEST_F(MemEnvTest_370, AppendableFile_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/appendable", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("hello");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  s = env_->NewAppendableFile("/appendable", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Append(" world");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  uint64_t file_size;
  s = env_->GetFileSize("/appendable", &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(11u, file_size);

  SequentialFile* seq_file;
  s = env_->NewSequentialFile("/appendable", &seq_file);
  ASSERT_TRUE(s.ok());

  Slice result;
  char scratch[100];
  s = seq_file->Read(11, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("hello world", result.ToString());
  delete seq_file;
}

TEST_F(MemEnvTest_370, AppendableFileCreatesNewIfNotExist_370) {
  WritableFile* writable_file;
  Status s = env_->NewAppendableFile("/new_appendable", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("data");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  uint64_t file_size;
  s = env_->GetFileSize("/new_appendable", &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(4u, file_size);
}

TEST_F(MemEnvTest_370, EmptyFileSize_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/empty", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  uint64_t file_size;
  s = env_->GetFileSize("/empty", &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, file_size);
}

TEST_F(MemEnvTest_370, OverwriteExistingFile_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/overwrite", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("first");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  s = env_->NewWritableFile("/overwrite", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("second");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  uint64_t file_size;
  s = env_->GetFileSize("/overwrite", &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(6u, file_size);

  SequentialFile* seq_file;
  s = env_->NewSequentialFile("/overwrite", &seq_file);
  ASSERT_TRUE(s.ok());

  Slice result;
  char scratch[100];
  s = seq_file->Read(6, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("second", result.ToString());
  delete seq_file;
}

TEST_F(MemEnvTest_370, LockAndUnlockFile_370) {
  FileLock* lock;
  Status s = env_->LockFile("/lock_file", &lock);
  ASSERT_TRUE(s.ok());

  s = env_->UnlockFile(lock);
  ASSERT_TRUE(s.ok());
}

TEST_F(MemEnvTest_370, GetTestDirectory_370) {
  std::string path;
  Status s = env_->GetTestDirectory(&path);
  ASSERT_TRUE(s.ok());
  ASSERT_FALSE(path.empty());
}

TEST_F(MemEnvTest_370, NewLogger_370) {
  Logger* logger;
  Status s = env_->NewLogger("/test_log", &logger);
  ASSERT_TRUE(s.ok());
  ASSERT_NE(nullptr, logger);
  delete logger;
}

TEST_F(MemEnvTest_370, SequentialFileMultipleReads_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/multi_read", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("abcdefghij");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  SequentialFile* seq_file;
  s = env_->NewSequentialFile("/multi_read", &seq_file);
  ASSERT_TRUE(s.ok());

  Slice result;
  char scratch[100];

  s = seq_file->Read(5, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("abcde", result.ToString());

  s = seq_file->Read(5, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("fghij", result.ToString());

  // Read past end
  s = seq_file->Read(5, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(0u, result.size());

  delete seq_file;
}

TEST_F(MemEnvTest_370, SequentialFileSkip_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/skip_file", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("abcdefghij");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  SequentialFile* seq_file;
  s = env_->NewSequentialFile("/skip_file", &seq_file);
  ASSERT_TRUE(s.ok());

  s = seq_file->Skip(3);
  ASSERT_TRUE(s.ok());

  Slice result;
  char scratch[100];
  s = seq_file->Read(4, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("defg", result.ToString());

  delete seq_file;
}

TEST_F(MemEnvTest_370, RandomAccessReadBeyondEnd_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/beyond_end", &writable_file);
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("short");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  RandomAccessFile* rand_file;
  s = env_->NewRandomAccessFile("/beyond_end", &rand_file);
  ASSERT_TRUE(s.ok());

  Slice result;
  char scratch[100];
  // Read starting at offset 3, requesting 10 bytes (only 2 available)
  s = rand_file->Read(3, 10, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("rt", result.ToString());

  delete rand_file;
}

TEST_F(MemEnvTest_370, LargeFileWriteAndRead_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/large_file", &writable_file);
  ASSERT_TRUE(s.ok());

  std::string large_data(100000, 'x');
  s = writable_file->Append(large_data);
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  uint64_t file_size;
  s = env_->GetFileSize("/large_file", &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(100000u, file_size);

  SequentialFile* seq_file;
  s = env_->NewSequentialFile("/large_file", &seq_file);
  ASSERT_TRUE(s.ok());

  Slice result;
  char* scratch = new char[100000];
  s = seq_file->Read(100000, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(large_data, result.ToString());

  delete[] scratch;
  delete seq_file;
}

TEST_F(MemEnvTest_370, MultipleAppends_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/multi_append", &writable_file);
  ASSERT_TRUE(s.ok());

  s = writable_file->Append("a");
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("b");
  ASSERT_TRUE(s.ok());
  s = writable_file->Append("c");
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;

  uint64_t file_size;
  s = env_->GetFileSize("/multi_append", &file_size);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ(3u, file_size);

  SequentialFile* seq_file;
  s = env_->NewSequentialFile("/multi_append", &seq_file);
  ASSERT_TRUE(s.ok());

  Slice result;
  char scratch[10];
  s = seq_file->Read(3, &result, scratch);
  ASSERT_TRUE(s.ok());
  ASSERT_EQ("abc", result.ToString());
  delete seq_file;
}

TEST_F(MemEnvTest_370, GetChildrenEmptyDir_370) {
  std::vector<std::string> children;
  Status s = env_->GetChildren("/empty_dir", &children);
  // Even if the directory doesn't "exist", the operation may succeed with empty results
  // or it may fail - we just test the interface
  if (s.ok()) {
    ASSERT_TRUE(children.empty());
  }
}

TEST_F(MemEnvTest_370, WritableFileSync_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/sync_file", &writable_file);
  ASSERT_TRUE(s.ok());

  s = writable_file->Append("sync_data");
  ASSERT_TRUE(s.ok());
  s = writable_file->Sync();
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;
}

TEST_F(MemEnvTest_370, WritableFileFlush_370) {
  WritableFile* writable_file;
  Status s = env_->NewWritableFile("/flush_file", &writable_file);
  ASSERT_TRUE(s.ok());

  s = writable_file->Append("flush_data");
  ASSERT_TRUE(s.ok());
  s = writable_file->Flush();
  ASSERT_TRUE(s.ok());
  s = writable_file->Close();
  ASSERT_TRUE(s.ok());
  delete writable_file;
}

}  // namespace leveldb
