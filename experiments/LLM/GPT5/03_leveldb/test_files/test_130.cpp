// File: version_set_total_file_size_test.cc
#include <gtest/gtest.h>
#include <vector>
#include <cstdint>

// Minimal type to satisfy FileMetaData's members in the provided header.
// We don't rely on any InternalKey behavior.
namespace leveldb {
struct InternalKey {};
}

// Use the provided dependency interface exactly as given.
#include "db/version_edit.h"

// Forward declaration of the function under test (implemented in version_set.cc).
namespace leveldb {
int64_t TotalFileSize(const std::vector<FileMetaData*>& files);
}

// Test fixture (keeps naming convention with TEST_ID)
class TotalFileSizeTest_130 : public ::testing::Test {
protected:
  // Utility to allocate a FileMetaData and set its observable field: file_size.
  leveldb::FileMetaData* NewFile(uint64_t size, uint64_t number = 0) {
    auto* f = new leveldb::FileMetaData();
    f->file_size = size;
    f->number = number;
    return f;
  }

  // Helper to clean up allocated pointers in a vector.
  static void DestroyAll(std::vector<leveldb::FileMetaData*>& files) {
    for (auto* f : files) delete f;
    files.clear();
  }
};

// Normal operation: empty input returns 0
TEST_F(TotalFileSizeTest_130, EmptyVectorReturnsZero_130) {
  std::vector<leveldb::FileMetaData*> files;
  EXPECT_EQ(0, leveldb::TotalFileSize(files));
}

// Normal operation: single element returns that file's size
TEST_F(TotalFileSizeTest_130, SingleFileReturnsItsSize_130) {
  std::vector<leveldb::FileMetaData*> files;
  files.push_back(NewFile(/*size=*/12345));
  EXPECT_EQ(12345, leveldb::TotalFileSize(files));
  DestroyAll(files);
}

// Normal operation: multiple elements sum correctly
TEST_F(TotalFileSizeTest_130, MultipleFilesAreSummed_130) {
  std::vector<leveldb::FileMetaData*> files;
  files.push_back(NewFile(100));
  files.push_back(NewFile(200));
  files.push_back(NewFile(700));
  EXPECT_EQ(1000, leveldb::TotalFileSize(files));
  DestroyAll(files);
}

// Boundary-ish case: large but safe sizes (stay within int64_t range)
TEST_F(TotalFileSizeTest_130, LargeButSafeTotals_130) {
  // Choose values whose sum is below INT64_MAX to avoid overflow assumptions.
  const uint64_t a = static_cast<uint64_t>(1) << 60; // 2^60
  const uint64_t b = static_cast<uint64_t>(1) << 60; // 2^60
  const uint64_t c = static_cast<uint64_t>(1) << 58; // 2^58
  // Sum = 2^61 + 2^58 = 2,306,843,009,213,693,952 < INT64_MAX (9,223,372,036,854,775,807)

  std::vector<leveldb::FileMetaData*> files;
  files.push_back(NewFile(a));
  files.push_back(NewFile(b));
  files.push_back(NewFile(c));

  const int64_t expected =
      static_cast<int64_t>(a + b + c);  // stays within int64_t domain

  EXPECT_EQ(expected, leveldb::TotalFileSize(files));
  DestroyAll(files);
}

// Non-mutating behavior: inputs are not modified by the function
TEST_F(TotalFileSizeTest_130, DoesNotModifyInputMetadata_130) {
  auto* f1 = NewFile(10, /*number=*/1);
  auto* f2 = NewFile(20, /*number=*/2);
  std::vector<leveldb::FileMetaData*> files{f1, f2};

  // Capture observable fields before call
  const uint64_t f1_size_before = f1->file_size;
  const uint64_t f2_size_before = f2->file_size;
  const uint64_t f1_number_before = f1->number;
  const uint64_t f2_number_before = f2->number;

  // Call function under test
  (void)leveldb::TotalFileSize(files);

  // Verify observable fields unchanged
  EXPECT_EQ(f1_size_before, f1->file_size);
  EXPECT_EQ(f2_size_before, f2->file_size);
  EXPECT_EQ(f1_number_before, f1->number);
  EXPECT_EQ(f2_number_before, f2->number);

  DestroyAll(files);
}
