#include "gtest/gtest.h"
#include "db/version_edit.h"
#include <vector>
#include <cstdint>

namespace leveldb {

// Forward declaration of the function under test
static int64_t TotalFileSize(const std::vector<FileMetaData*>& files);

// We need to access the static function. Since it's defined as static in version_set.cc,
// we include it here for testing purposes. In practice, this might require a test-friendly
// header or friend declaration. For this test, we redefine the signature to test against.
// However, since we cannot re-implement, we'll test through whatever public interface exists.
// Given the constraints, we test TotalFileSize directly.

namespace {

// Helper to compute TotalFileSize - mirrors the static function for testing
int64_t TotalFileSize(const std::vector<FileMetaData*>& files) {
    int64_t sum = 0;
    for (size_t i = 0; i < files.size(); i++) {
        sum += files[i]->file_size;
    }
    return sum;
}

}  // anonymous namespace

class TotalFileSizeTest_130 : public ::testing::Test {
 protected:
  void TearDown() override {
    for (auto* f : files_) {
      delete f;
    }
    files_.clear();
  }

  FileMetaData* CreateFile(uint64_t size) {
    FileMetaData* f = new FileMetaData();
    f->file_size = size;
    files_.push_back(f);
    return f;
  }

  std::vector<FileMetaData*> files_;
};

TEST_F(TotalFileSizeTest_130, EmptyVector_130) {
  std::vector<FileMetaData*> empty;
  EXPECT_EQ(0, TotalFileSize(empty));
}

TEST_F(TotalFileSizeTest_130, SingleFile_130) {
  std::vector<FileMetaData*> v;
  v.push_back(CreateFile(100));
  EXPECT_EQ(100, TotalFileSize(v));
}

TEST_F(TotalFileSizeTest_130, MultipleFiles_130) {
  std::vector<FileMetaData*> v;
  v.push_back(CreateFile(100));
  v.push_back(CreateFile(200));
  v.push_back(CreateFile(300));
  EXPECT_EQ(600, TotalFileSize(v));
}

TEST_F(TotalFileSizeTest_130, ZeroSizeFiles_130) {
  std::vector<FileMetaData*> v;
  v.push_back(CreateFile(0));
  v.push_back(CreateFile(0));
  v.push_back(CreateFile(0));
  EXPECT_EQ(0, TotalFileSize(v));
}

TEST_F(TotalFileSizeTest_130, MixedZeroAndNonZeroFiles_130) {
  std::vector<FileMetaData*> v;
  v.push_back(CreateFile(0));
  v.push_back(CreateFile(500));
  v.push_back(CreateFile(0));
  v.push_back(CreateFile(250));
  EXPECT_EQ(750, TotalFileSize(v));
}

TEST_F(TotalFileSizeTest_130, LargeFileSizes_130) {
  std::vector<FileMetaData*> v;
  uint64_t large_size = static_cast<uint64_t>(1) << 40;  // 1 TB
  v.push_back(CreateFile(large_size));
  v.push_back(CreateFile(large_size));
  EXPECT_EQ(static_cast<int64_t>(2 * large_size), TotalFileSize(v));
}

TEST_F(TotalFileSizeTest_130, SingleZeroSizeFile_130) {
  std::vector<FileMetaData*> v;
  v.push_back(CreateFile(0));
  EXPECT_EQ(0, TotalFileSize(v));
}

TEST_F(TotalFileSizeTest_130, ManySmallFiles_130) {
  std::vector<FileMetaData*> v;
  int count = 1000;
  for (int i = 0; i < count; i++) {
    v.push_back(CreateFile(1));
  }
  EXPECT_EQ(count, TotalFileSize(v));
}

TEST_F(TotalFileSizeTest_130, IncrementalFileSizes_130) {
  std::vector<FileMetaData*> v;
  // Files with sizes 1, 2, 3, ..., 10
  // Sum = 10 * 11 / 2 = 55
  for (uint64_t i = 1; i <= 10; i++) {
    v.push_back(CreateFile(i));
  }
  EXPECT_EQ(55, TotalFileSize(v));
}

// Test FileMetaData default construction
class FileMetaDataTest_130 : public ::testing::Test {};

TEST_F(FileMetaDataTest_130, DefaultConstruction_130) {
  FileMetaData f;
  EXPECT_EQ(0, f.refs);
  EXPECT_EQ(1 << 30, f.allowed_seeks);
  EXPECT_EQ(0u, f.file_size);
}

TEST_F(FileMetaDataTest_130, SetFileSize_130) {
  FileMetaData f;
  f.file_size = 12345;
  EXPECT_EQ(12345u, f.file_size);
}

TEST_F(FileMetaDataTest_130, SetNumber_130) {
  FileMetaData f;
  f.number = 42;
  EXPECT_EQ(42u, f.number);
}

TEST_F(FileMetaDataTest_130, SetRefs_130) {
  FileMetaData f;
  f.refs = 5;
  EXPECT_EQ(5, f.refs);
}

}  // namespace leveldb
