// File: ./TestProjects/ninja/src/util_test_truncate_159.cc

#include "util.h"

#include <gtest/gtest.h>

#include <cstdio>
#include <fstream>
#include <string>

#ifdef _WIN32
#  include <sys/stat.h>
#else
#  include <sys/types.h>
#  include <sys/stat.h>
#endif

using std::string;

// Helper to get file size in bytes.
static size_t GetFileSize(const string& path) {
#ifdef _WIN32
  struct _stat st;
  EXPECT_EQ(0, _stat(path.c_str(), &st));
#else
  struct stat st;
  EXPECT_EQ(0, stat(path.c_str(), &st));
#endif
  return static_cast<size_t>(st.st_size);
}

// TEST_ID: 159
TEST(TruncateTest_159, TruncateShrinksExistingFile_159) {
  const string path = "truncate_test_shrink_159.tmp";

  // Prepare a file with known size (10 bytes).
  {
    std::ofstream ofs(path.c_str(), std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(ofs.is_open());
    ofs << "0123456789";  // 10 bytes
  }

  ASSERT_EQ(10u, GetFileSize(path));

  string err = "previous error";
  const size_t new_size = 5;

  // Call the function under test: shrink the file.
  bool ok = Truncate(path, new_size, &err);

  EXPECT_TRUE(ok);
  // On success, implementation does not modify *err.
  EXPECT_EQ("previous error", err);
  EXPECT_EQ(new_size, GetFileSize(path));

  std::remove(path.c_str());
}

// TEST_ID: 159
TEST(TruncateTest_159, TruncateExtendsExistingFile_159) {
  const string path = "truncate_test_extend_159.tmp";

  // Prepare a file with known size (4 bytes).
  {
    std::ofstream ofs(path.c_str(), std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(ofs.is_open());
    ofs << "ABCD";  // 4 bytes
  }

  ASSERT_EQ(4u, GetFileSize(path));

  string err;
  const size_t new_size = 16;

  // Call the function under test: extend the file.
  bool ok = Truncate(path, new_size, &err);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(err.empty());  // No error message on success.
  EXPECT_EQ(new_size, GetFileSize(path));

  std::remove(path.c_str());
}

// TEST_ID: 159
TEST(TruncateTest_159, TruncateToZeroSize_159) {
  const string path = "truncate_test_zero_159.tmp";

  // Prepare a file with some content.
  {
    std::ofstream ofs(path.c_str(), std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(ofs.is_open());
    ofs << "content";
  }

  ASSERT_GT(GetFileSize(path), 0u);

  string err;
  const size_t new_size = 0;

  // Truncate to zero size (boundary condition).
  bool ok = Truncate(path, new_size, &err);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(err.empty());
  EXPECT_EQ(new_size, GetFileSize(path));

  std::remove(path.c_str());
}

// TEST_ID: 159
TEST(TruncateTest_159, TruncateWithEmptyPathFailsAndSetsError_159) {
  const string empty_path;

  string err = "no error yet";

  // Using an empty path is invalid on both Windows and POSIX and should fail.
  bool ok = Truncate(empty_path, 10, &err);

  EXPECT_FALSE(ok);
  // On failure, error string should be set to a non-empty description.
  EXPECT_FALSE(err.empty());
  EXPECT_NE("no error yet", err);
}
