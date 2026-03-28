// File: ./TestProjects/ninja/src/util_unittest_160.cc

#include "gtest/gtest.h"
#include "util.h"

#include <cstdio>   // std::fopen, std::fclose
#include <cstring>  // std::strlen

// Simple helper to create a small temporary file with the given name.
static void CreateTempFile(const char* filename) {
  FILE* f = std::fopen(filename, "wb");
  ASSERT_NE(nullptr, f) << "Failed to create temp file for test";
  std::fputs("temp", f);
  std::fclose(f);
}

class PlatformAwareUnlinkTest_160 : public ::testing::Test {
 protected:
  // Utility to check whether a file exists by trying to open it.
  static bool FileExists(const char* filename) {
    FILE* f = std::fopen(filename, "rb");
    if (f) {
      std::fclose(f);
      return true;
    }
    return false;
  }
};

// Normal operation: unlinking an existing file should succeed and remove it.
TEST_F(PlatformAwareUnlinkTest_160, RemoveExistingFile_160) {
  const char* kFilename = "platform_aware_unlink_existing_160.tmp";

  // Arrange: create the file
  CreateTempFile(kFilename);
  ASSERT_TRUE(FileExists(kFilename));

  // Act
  int result = platformAwareUnlink(kFilename);

  // Assert: function reports success and file is gone
  EXPECT_EQ(0, result);
  EXPECT_FALSE(FileExists(kFilename));
}

// Error case: unlinking a non-existing file should fail (non-zero return).
TEST_F(PlatformAwareUnlinkTest_160, RemoveNonExistingFile_ReturnsError_160) {
  const char* kFilename = "platform_aware_unlink_non_existing_160.tmp";

  // Ensure the file does not exist before the test observation
  if (FileExists(kFilename)) {
    // Best-effort cleanup; we don't assert here because setup should not fail the test.
    platformAwareUnlink(kFilename);
  }
  ASSERT_FALSE(FileExists(kFilename));

  // Act
  int result = platformAwareUnlink(kFilename);

  // Assert: should indicate failure with non-zero return value.
  EXPECT_NE(0, result);
  EXPECT_FALSE(FileExists(kFilename));
}

// Boundary/invalid input: empty filename should not succeed.
TEST_F(PlatformAwareUnlinkTest_160, EmptyFilename_ReturnsError_160) {
  const char* kEmpty = "";

  // Act
  int result = platformAwareUnlink(kEmpty);

  // Assert: the call should not report success.
  EXPECT_NE(0, result);
}
