// File: ./TestProjects/ninja/tests/GetWorkingDirectoryTest_158.cc

#include "gtest/gtest.h"

#include <limits.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>

#include "util.h"  // Declaration of GetWorkingDirectory()

// Test fixture for GetWorkingDirectory-related tests.
class GetWorkingDirectoryTest_158 : public ::testing::Test {
 protected:
  std::string original_dir_;

  void SetUp() override {
    char buf[PATH_MAX];
    // Record the original working directory so we can restore it in TearDown.
    char* cwd = ::getcwd(buf, sizeof(buf));
    ASSERT_NE(cwd, nullptr);
    original_dir_ = buf;
  }

  void TearDown() override {
    // Best effort to restore original directory; if this fails, other tests
    // may be impacted, so we assert success.
    ASSERT_EQ(::chdir(original_dir_.c_str()), 0);
  }
};

// Verifies that GetWorkingDirectory returns the same path as ::getcwd
// for the current process directory.
TEST_F(GetWorkingDirectoryTest_158, ReturnsSameAsGetcwd_158) {
  std::string from_util = GetWorkingDirectory();

  char buf[PATH_MAX];
  char* cwd = ::getcwd(buf, sizeof(buf));
  ASSERT_NE(cwd, nullptr) << "getcwd failed in test environment";

  std::string from_system(buf);

  // Observable behavior: GetWorkingDirectory should report the current
  // working directory as seen by the system call.
  EXPECT_EQ(from_util, from_system);
  EXPECT_FALSE(from_util.empty());
}

// Verifies that GetWorkingDirectory reflects changes to the process
// working directory (after a successful chdir).
TEST_F(GetWorkingDirectoryTest_158, ReflectsChangedDirectory_158) {
  // Create a temporary directory under /tmp (or current working directory,
  // depending on the platform and environment).
  char tmpl[] = "/tmp/getwd_test_XXXXXX";
  char* temp_dir = ::mkdtemp(tmpl);
  ASSERT_NE(temp_dir, nullptr) << "mkdtemp failed in test environment";

  // Change the process working directory.
  ASSERT_EQ(::chdir(temp_dir), 0) << "chdir to temp dir failed";

  // Now GetWorkingDirectory should return this new directory.
  std::string from_util = GetWorkingDirectory();

  char buf[PATH_MAX];
  char* cwd = ::getcwd(buf, sizeof(buf));
  ASSERT_NE(cwd, nullptr) << "getcwd failed after chdir";

  std::string from_system(buf);

  EXPECT_EQ(from_util, from_system);
  EXPECT_EQ(from_util, std::string(temp_dir));
}

// Verifies that multiple calls to GetWorkingDirectory are consistent
// when the working directory has not changed.
TEST_F(GetWorkingDirectoryTest_158, MultipleCallsConsistent_158) {
  std::string first = GetWorkingDirectory();
  std::string second = GetWorkingDirectory();

  // As long as the process working directory is unchanged, repeated
  // calls should produce the same observable result.
  EXPECT_EQ(first, second);
  EXPECT_FALSE(first.empty());
}
