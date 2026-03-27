// windows_logger_test_452.cc
#include <gtest/gtest.h>

#include <cstdio>
#include <cerrno>
#include <filesystem>
#include <fstream>
#include <random>
#include <string>

#include "util/windows_logger.h"  // Uses the provided interface

namespace {

std::string MakeTempFilePath() {
  namespace fs = std::filesystem;
  auto dir = fs::temp_directory_path();
  // Generate a pseudo-random filename to avoid collisions.
  std::mt19937_64 rng{static_cast<uint64_t>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count())};
  std::uniform_int_distribution<uint64_t> dist;
  std::string name = "windows_logger_test_" + std::to_string(dist(rng)) + ".log";
  return (dir / name).string();
}

// Creates a file at `path` and returns a FILE* opened in write mode.
std::FILE* CreateFileAt(const std::string& path) {
  std::FILE* fp = std::fopen(path.c_str(), "w");
  if (fp) {
    std::fputs("hello\n", fp);
    std::fflush(fp);
  }
  return fp;
}

}  // namespace

// Fixture kept minimal for clarity and consistency of naming.
class WindowsLoggerTest_452 : public ::testing::Test {};

// Verifies that while the logger (and thus the FILE*) is alive, attempting to
// remove the file fails on Windows, and after destruction (scope exit) the
// removal succeeds — observable evidence that the destructor closed the FILE*.
TEST_F(WindowsLoggerTest_452, DestructorClosesFile_AllowsDeletion_452) {
  const std::string path = MakeTempFilePath();
  std::FILE* fp = CreateFileAt(path);
  ASSERT_NE(fp, nullptr) << "Failed to create/open temp file: " << path;

  {
    leveldb::WindowsLogger logger(fp);

    // Attempt to remove while file is open.
    // On Windows, removing an open file should fail (non-zero return).
    errno = 0;
    int remove_result_while_open = std::remove(path.c_str());

    if (remove_result_while_open == 0) {
      // Some environments may permit removal of an open file (e.g., non-Windows).
      // Skip rather than fail to keep the test black-box and portable-friendly.
      GTEST_SKIP() << "Removal of open files succeeded in this environment; "
                      "cannot reliably assert close-on-destruction via deletion.";
    } else {
      // On Windows, we expect failure here.
      EXPECT_NE(remove_result_while_open, 0)
          << "Expected removal to fail while file is open";
      // No strong assertion on errno value; behavior can vary.
    }
  }  // logger goes out of scope; destructor should close fp

  // Now the file should be deletable after destruction.
  // Re-create the file if a prior environment allowed deletion to proceed.
  // (If the earlier remove succeeded and we didn't skip, ensure file exists.)
  // In the non-skipped Windows case above, file still exists here.
  int final_remove_result = std::remove(path.c_str());
  EXPECT_EQ(final_remove_result, 0) << "Expected removal to succeed after logger destruction";
}

// Smoke test: RAII behavior over a nested scope with a fresh file.
// Ensures no crash on destruction and that post-destruction deletion succeeds.
TEST_F(WindowsLoggerTest_452, DestructorExecutesOnScopeExit_452) {
  const std::string path = MakeTempFilePath();
  {
    std::FILE* fp = CreateFileAt(path);
    ASSERT_NE(fp, nullptr) << "Failed to create/open temp file: " << path;

    // Construct logger; no further interactions needed for this test.
    leveldb::WindowsLogger logger(fp);

    // Do not attempt to close or use fp directly; treat class as a black box.
  }  // logger destroyed here; should have closed the FILE*

  // After scope exit, the file should no longer be held open and can be removed.
  EXPECT_EQ(std::remove(path.c_str()), 0)
      << "File should be deletable after WindowsLogger destruction";
}
